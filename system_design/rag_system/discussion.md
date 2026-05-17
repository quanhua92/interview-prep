# Design a RAG System

Source: [RAG System Design (CalibreOS)](https://www.calibreos.com/learn/mlsd-rag-system-design)

## One-Liner
Build a Retrieval-Augmented Generation system that retrieves relevant passages from a document corpus and feeds them to an LLM for grounded, cited answers with sub-2s p95 latency.

## Functional Requirements
- Ingest and index a document corpus (100K to 100M+ documents) with incremental updates
- Accept natural-language queries and return grounded answers with source citations
- Support chunk-level passage retrieval with configurable overlap
- Provide hybrid retrieval (BM25 + dense vector search) fused into a single ranked list
- Rerank retrieved passages with a cross-encoder for higher precision
- Stream generated answers to the client with time-to-first-token under 500ms
- Detect and mitigate hallucinations through layered defenses

## Non-Functional Requirements
- End-to-end p95 latency under 1500ms for chat, under 800ms for autocomplete
- Faithfulness score above 0.85 (claims traceable to retrieved passages)
- Citation precision above 0.90 on sampled queries
- Handle concurrent QPS with elastic reranker GPU pool (cross-encoder at 100 QPS = 1 GPU)
- Incremental indexing for high-churn corpora (50K+ new docs/day)
- Streaming support: TTFT under 500ms matters more than total latency

## Key Scale Questions
- Corpus size: 100K docs (pgvector works) vs 100M (need Qdrant cluster + IVF-PQ)
- Update cadence: static quarterly rebuilds vs 50K new docs/day requiring online-updatable HNSW
- Concurrent QPS determines reranker GPU sizing (A10 handles ~12-15 rerank QPS for top-100 batches)
- Embedding storage: float32 at 1536 dims = ~6KB/vector; PQ compression reduces to ~64 bytes (100x)
- Re-embedding cost on model upgrade: must plan multi-day dual-index migration for 10M+ docs
- Query distribution: lookup-style (RAG sweet spot) vs analytical (needs query decomposition or agentic retrieval)

## Core Components
- **Document Ingestion Service**: parse, chunk, and embed documents; maintain chunk-level metadata and lineage
- **Embedding Service**: encode queries and chunks using a bi-encoder model (BGE, E5, OpenAI)
- **Vector Store**: HNSW-based ANN index (Qdrant, Weaviate, pgvector) for dense retrieval
- **BM25 / Sparse Retriever**: Elasticsearch or Lucene-based lexical search for exact-match queries
- **RRF Fusion Layer**: combine dense and sparse ranked lists using Reciprocal Rank Fusion (k=60)
- **Cross-Encoder Reranker**: BGE-reranker-large or Cohere rerank-3 to score query-document pairs jointly
- **LLM Generator**: GPT-4o / Claude Sonnet for grounded answer generation with streaming
- **Hallucination Guard**: per-claim NLI entailment check + relevance gate for abstention
- **Evaluation Pipeline**: RAGAS metrics + human gold set for continuous quality monitoring

## Key Design Decisions

### Chunking Strategy
- **Fixed-size sliding window (256-512 tokens, 50-token overlap)**: default for most prose. Snap boundaries to sentence ends to avoid splitting mid-sentence
- **Semantic chunking**: split on embedding-similarity drops between consecutive sentences. ~10% retrieval lift on heterogeneous corpora, 2-3x indexing cost
- **Hierarchical parent-child**: index 128-token chunks for precision, return 1024-token parent for context. 2x storage, big win for legal/research docs
- **Document-aware (Markdown/HTML)**: respect section headers as chunk boundaries. Critical for technical documentation
- **Contextual retrieval (Anthropic 2024)**: prepend LLM-generated context to each chunk before embedding. 49% reduction in retrieval failures, ~$1/M tokens

### Retrieval Approach
- **Pure dense (HNSW)**: misses exact-match queries ("CUDA error code 11", invoice numbers)
- **Pure BM25**: misses paraphrase queries ("cancel subscription" vs "terminating membership")
- **Hybrid BM25 + Dense + RRF**: parallel execution, fuse with Reciprocal Rank Fusion. Lifts recall@10 by 5-15% over best-single retriever. Always run in parallel, not sequentially

### Reranking Funnel
- **Retrieve top-100 via hybrid, rerank to top-5 to 10 with cross-encoder**: bi-encoder is fast but loses query-document interaction signal; cross-encoder is accurate but too slow over full corpus. Two-stage funnel gives cross-encoder accuracy at bi-encoder scale (~95ms combined)
- Skip reranking only for ultra-low-latency autocomplete (<200ms budget) or when precision@10 is already >95%

### Embedding Model Selection
- **BGE-large-en-v1.5** (1024-dim): de facto open default, single A10/L4 GPU, Apache 2.0
- **E5-mistral-7b-instruct** (4096-dim): top MTEB retrieval, slower and 4x storage
- **BGE-M3**: multi-lingual, multi-granularity (dense + sparse + multi-vector in one model)
- **OpenAI text-embedding-3-large** (3072-dim, truncatable): $0.13/M tokens, convenient if already on OpenAI
- Never mix embedding models in one index; upgrades require full re-embed + dual-index migration

### Hallucination Mitigation (Defense in Depth)
- **Layer 1 - Prompt grounding**: explicit system prompt constraining answers to retrieved context only (~30-40% hallucination reduction)
- **Layer 2 - Per-claim citation grounding**: NLI entailment check (DeBERTa-v3) on each claim vs retrieved passages
- **Layer 3 - Relevance gate**: if top-1 reranker score is below threshold, abstain rather than generate from weak context
- **Layer 4 - Output abstention**: prompt or train model to say "I don't know" when context is ambiguous
- **Layer 5 - Async audit loop**: sample 1-5% of traffic for human review, build regression suite from confirmed hallucinations

## API Endpoints
| Method | Path | Description |
|--------|------|-------------|
| POST | /api/documents | Ingest and index a document |
| POST | /api/query | Submit a natural-language query, get grounded answer with citations |
| GET | /api/query/{id}/stream | Stream the generated answer (SSE) |
| GET | /api/documents/{id}/chunks | List chunks for a document (debugging) |
| GET | /api/eval/metrics | Fetch latest RAGAS evaluation scores |

## Database Schema
| Column | Type | Notes |
|--------|------|-------|
| doc_id | UUID | PK, document identifier |
| title | TEXT | Document title |
| source_url | TEXT | Original source |
| embedding_model_version | VARCHAR | Model + version used for indexing |
| created_at | TIMESTAMP | Ingestion timestamp |

| Column | Type | Notes |
|--------|------|-------|
| chunk_id | UUID | PK, chunk identifier |
| doc_id | UUID | FK to documents |
| chunk_text | TEXT | Chunk content |
| chunk_index | INT | Position within document |
| parent_chunk_id | UUID | For hierarchical chunking, FK to parent |
| embedding | VECTOR(1024) | Dense embedding (or PQ-compressed) |
| sparse_vector | SPARSE | BM25/learned sparse features |

## Deep Dive Topics
- Embedding model version drift: upgrading models requires re-embedding the entire corpus; plan dual-index serving with atomic swap
- Multi-hop queries: "compare Q3 vs Q4 revenue" requires query decomposition or iterative retrieval, single-shot retrieval fails
- Cross-lingual retrieval: monolingual models fail on mismatched query-corpus languages; use BGE-M3 or mE5 instead of translating queries
- Recency bias: without recency boosting, LLM may cite outdated documents; add recency score to rerank output
- Prompt injection via retrieved content: malicious docs can hijack the LLM; sanitize at ingestion, isolate untrusted content in prompt
- Build vs buy for vector DB: Pinecone (managed) vs self-hosted Qdrant vs pgvector (cheapest) depends on corpus size, team capacity, and cost tolerance
- ColBERT late interaction: stores per-token vectors instead of one per doc, 50-100x storage but captures fine-grained match signal; use only after maxing out other techniques
- HyDE (Hypothetical Document Embeddings): LLM generates a hypothetical answer, embed that instead of the query; ~10-20% recall lift on conversational queries at cost of an extra LLM call

## Follow-Up Variations
- How would you handle a multi-tenant RAG system with strict data isolation between customers?
- What changes when the corpus is 100M documents and you need sub-500ms retrieval?
- How do you design RAG for analytical queries that require reasoning across multiple documents?
- How would you implement agentic RAG where the LLM issues its own retrieval tool calls?
- What is your strategy for re-embedding the corpus when upgrading the embedding model?
- How do you handle queries in a language different from the corpus language?
