# Design a RAG System — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] What is the corpus size (100K, 10M, 100M documents) and growth rate?
  - [ ] What is the update cadence: static quarterly, daily, or real-time (50K+ new docs/day)?
  - [ ] What is the latency budget: chat (2-3s end-to-end) or autocomplete (<800ms)?
  - [ ] Are citation and source attribution required (legal/medical/enterprise)?
  - [ ] Is this single-tenant or multi-tenant with data isolation requirements?
  - [ ] What is the query distribution: lookup-style or analytical (multi-hop)?
- [ ] List functional requirements (3-5 items):
  - [ ] Ingest and chunk documents from a corpus
  - [ ] Embed chunks and index in a vector store
  - [ ] Accept natural-language queries and retrieve relevant passages
  - [ ] Generate grounded answers with source citations
  - [ ] Detect and mitigate hallucinations
- [ ] List non-functional requirements (latency, availability, scale):
  - [ ] End-to-end p95 latency under 1500ms (chat) or 800ms (autocomplete)
  - [ ] Faithfulness score >0.85, citation precision >0.90
  - [ ] Support incremental indexing for high-churn corpora
  - [ ] Streaming support with TTFT under 500ms
- [ ] State your scale estimates (corpus size, QPS, storage):
  - [ ] Corpus: 10M documents, ~500 tokens/chunk average
  - [ ] ~50K new documents/day requiring incremental indexing
  - [ ] ~1K QPS at peak; reranker GPU pool sized accordingly (~1 GPU per 12-15 QPS)
  - [ ] Embedding storage: ~6KB/vector (float32) or ~64 bytes/vector (PQ compressed)

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw a simple box diagram: Client -> LB -> [Query Service] -> [Embedding Service + BM25 Retriever + Dense Retriever] -> [RRF Fusion] -> [Reranker] -> [LLM Generator] -> [Hallucination Guard]
- [ ] Identify the main operations and their access patterns:
  - [ ] `POST /api/documents` — ingest a document (write, async batch processing)
  - [ ] `POST /api/query` — submit a query (read-heavy, latency-sensitive)
  - [ ] `GET /api/query/{id}/stream` — stream generated answer (SSE)
  - [ ] `GET /api/eval/metrics` — fetch evaluation scores (low QPS, monitoring)
- [ ] Note the retrieval pipeline stages and latency contributions:
  - [ ] Query embedding (~30ms) + dense retrieval (~15ms) parallel with BM25 (~10ms)
  - [ ] RRF fusion (~2ms) + cross-encoder rerank (~80ms)
  - [ ] LLM first-token (~400ms) + streaming generation (~900ms)
  - [ ] Total p95 budget: ~1500ms with ~50ms headroom
- [ ] Present the diagram and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain chunking strategy choice and justify:
  - [ ] Fixed-size sliding window (256-512 tokens, 50 overlap): default, simple, works for most prose
  - [ ] Semantic chunking: better topical coherence, 2-3x indexing cost, for heterogeneous corpora
  - [ ] Hierarchical parent-child: index small chunks, return parent for context; 2x storage
  - [ ] Document-aware (Markdown/HTML headers): for structured technical docs
  - [ ] State your choice and when you would use alternatives
- [ ] Explain retrieval approach and justify:
  - [ ] Hybrid BM25 + Dense + RRF (k=60): parallel execution, fuses rank positions
  - [ ] Pure dense misses exact matches; pure BM25 misses paraphrases
  - [ ] Hybrid lifts recall@10 by 5-15% over best-single retriever
  - [ ] Always parallelize BM25 and dense, never sequential
- [ ] Define API endpoints with method, path, request/response:
  - [ ] `POST /api/documents` -> `{"doc_id": "...", "chunk_count": 42, "status": "indexed"}`
  - [ ] `POST /api/query` -> `{"query_id": "...", "answer": "...", "citations": [...]}`
  - [ ] `GET /api/query/{id}/stream` -> SSE stream of answer tokens
- [ ] Sketch the database schema:
  - [ ] Table `documents`: `doc_id` (UUID PK), `title`, `source_url`, `embedding_model_version`, `created_at`
  - [ ] Table `chunks`: `chunk_id` (UUID PK), `doc_id` (FK), `chunk_text`, `chunk_index`, `parent_chunk_id`, `embedding` (VECTOR), `sparse_vector`
  - [ ] Table `query_logs`: `query_id`, `query_text`, `retrieved_chunk_ids`, `reranker_scores`, `answer`, `faithfulness_score`, `created_at`
- [ ] Discuss vector store trade-offs:
  - [ ] pgvector: simplest, works for <10M chunks, PostgreSQL ecosystem
  - [ ] Qdrant: online-updatable HNSW, payload filtering for multi-tenancy, self-hosted
  - [ ] Pinecone: fully managed, namespaces for isolation, higher cost
  - [ ] Weaviate: hybrid search built-in (BM25 + dense), good for teams wanting integrated solution
- [ ] Walk through the main flow end-to-end:
  - [ ] Ingestion: document -> parse -> chunk -> embed -> store in vector DB + sparse index
  - [ ] Query: user query -> embed query -> parallel BM25 + dense retrieval -> RRF fusion -> cross-encoder rerank top-100 to top-10 -> prompt assembly -> LLM generation (streamed) -> faithfulness check (async)

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss hallucination mitigation (defense in depth):
  - [ ] Layer 1: Prompt grounding — constrain LLM to answer only from retrieved context
  - [ ] Layer 2: Per-claim NLI entailment check (DeBERTa-v3) against retrieved passages
  - [ ] Layer 3: Relevance gate — abstain if top-1 reranker score is below threshold
  - [ ] Layer 4: Output abstention — prompt model to say "I don't know" when uncertain
  - [ ] Layer 5: Async audit loop — sample 1-5% of traffic for human review
  - [ ] Combined layers reduce hallucination from ~5-10% to <1%
- [ ] Explain evaluation strategy:
  - [ ] RAGAS metrics (faithfulness, answer relevancy, context precision, context recall)
  - [ ] LLM-as-judge with bias mitigation (randomize order, penalize verbosity, use different model family)
  - [ ] Human gold set: 500-1000 queries, labeled quarterly, ground truth for shipping decisions
  - [ ] Never ship a RAG change based on RAGAS alone
- [ ] Address scaling and embedding model lifecycle:
  - [ ] PQ compression for large corpora (64 bytes/vector vs 6KB)
  - [ ] Embedding model versioning: never mix models in one index
  - [ ] Dual-index migration strategy: build new index while old serves, atomic swap
  - [ ] Reranker GPU sizing: ~12-15 QPS per A10 for BGE-reranker-large top-100 batches
- [ ] Discuss advanced techniques (when to use each):
  - [ ] HyDE: for conversational queries, ~10-20% recall lift, costs an extra LLM call
  - [ ] ColBERT late interaction: per-token vectors, 50-100x storage, only after maxing out other options
  - [ ] Contextual retrieval (Anthropic 2024): LLM-generated context prefix per chunk, 49% fewer retrieval failures
  - [ ] Query decomposition: for multi-hop analytical questions, iterative retrieval passes
- [ ] Handle production failure modes:
  - [ ] Stale index after embedding upgrade: version the index, CI check model version match
  - [ ] Multi-hop questions missed: query decomposition or agentic retrieval
  - [ ] Recency bias: add recency score to rerank output for policy-style queries
  - [ ] Long-tail entity queries: BM25 catches rare entities that dense retrieval misses
  - [ ] Prompt injection via retrieved content: sanitize at ingestion, isolate untrusted content

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made and why
- [ ] Mention what you would improve with more time
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
