# Design a Search Ranking System -- Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] What type of search: web search, e-commerce product search, enterprise document search?
  - [ ] What is the query intent distribution: navigational, informational, transactional?
  - [ ] Does the system need LLM-augmented answers (RAG) or just ranked links?
  - [ ] What is the latency budget: traditional SERP (~150ms) or LLM-augmented (2-5s acceptable)?
- [ ] List functional requirements (3-5 items):
  - [ ] Accept free-text queries and return ranked results
  - [ ] Support spell correction, query expansion, and intent classification
  - [ ] Multi-stage ranking: retrieval -> ML ranking -> business re-ranking
  - [ ] Optionally support LLM-augmented answers with citations (RAG)
  - [ ] Pagination and infinite scroll
- [ ] List non-functional requirements (latency, availability, scale):
  - [ ] P99 latency under 150ms for traditional search
  - [ ] Support millions to billions of documents
  - [ ] Graceful degradation with fallback chain
  - [ ] High recall at retrieval, high precision at ranking
- [ ] State your scale estimates (documents, queries, latency):
  - [ ] Corpus size: ~100M to 1B+ documents
  - [ ] Query volume: ~10K-100K QPS
  - [ ] Read:write ratio heavily read-dominated
  - [ ] Retrieval: top-1000 candidates -> rank to top-100 -> re-rank to top-10

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw a simple box diagram: Client -> LB -> [Query Understanding] -> [Lexical Retriever + Semantic Retriever] -> [Light Ranker] -> [Cross-Encoder Re-Ranker] -> [Business Re-Ranker] -> Results
- [ ] Identify the main operations and their access patterns:
  - [ ] `GET /api/search?q=...` -- search query (read, highest QPS)
  - [ ] `POST /api/documents` -- index new document (write, lower QPS, async)
  - [ ] `GET /api/search/llm?q=...` -- LLM-augmented search (read, expensive, lower volume)
- [ ] Note where latency is spent and where caching helps:
  - [ ] BM25 retrieval: ~20ms on inverted index
  - [ ] ANN search: ~20-50ms for 100M+ documents
  - [ ] Light ranker (LambdaMART): ~15ms for 1000 candidates
  - [ ] Cross-encoder re-ranker: ~50ms for 50 candidates on GPU
  - [ ] Total budget: ~150ms P99
- [ ] Present the diagram and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain the retrieval strategy and justify:
  - [ ] BM25 for lexical precision: exact keyword matches, brand names, technical terms
  - [ ] Dense bi-encoder for semantic recall: paraphrases, synonyms, conceptual queries
  - [ ] SPLADE as the third path: learned sparse expansion, inverted-index compatible, explainable
  - [ ] Hybrid union: merge top-K from each, deduplicate, pass to ranking
  - [ ] NOT "replace BM25 with dense" -- they are complementary
- [ ] Explain query understanding:
  - [ ] Spell correction with confidence threshold (avoid over-correcting rare terms)
  - [ ] Intent classification: navigational / informational / transactional
  - [ ] Query expansion for tail queries only; skip for navigational queries
- [ ] Explain the learning-to-rank formulation:
  - [ ] Pointwise (LightGBM baseline): fast, debuggable, good starting point
  - [ ] Pairwise (RankNet): robust to label noise, quadratic pair growth
  - [ ] Listwise (LambdaMART): optimizes NDCG directly, production gold standard
- [ ] Define API endpoints with method, path, request/response:
  - [ ] `GET /api/search?q=...&page=n` -> `[{"doc_id": "...", "title": "...", "score": "..."}]`
  - [ ] `GET /api/search/llm?q=...` -> `{"answer": "...", "citations": [...], "links": [...]}`
  - [ ] `POST /api/documents` -> `{"doc_id": "...", "indexed": true}`
- [ ] Sketch the database schema:
  - [ ] Table `documents`: `doc_id`, `title`, `content`, `embedding` (vector), `sparse_vector` (SPLADE), `category`, `seller_id`, `in_stock`, `click_count`, `freshness`, `created_at`
  - [ ] Inverted index for BM25 (Elasticsearch/Lucene)
  - [ ] ANN index for dense embeddings (FAISS/HNSW/ScaNN)
  - [ ] Feature store for real-time ranking features (Redis)
- [ ] Walk through the main flow end-to-end:
  - [ ] Query flow: user types query -> spell correction + intent classification -> parallel retrieval (BM25 + ANN + SPLADE) -> merge + deduplicate -> light ranker (LambdaMART on top-1000) -> cross-encoder re-ranker (top-50) -> business re-ranker (diversity, freshness, fairness) -> return top-10
  - [ ] Indexing flow: new document -> generate dense embedding -> generate SPLADE sparse vector -> update inverted index + ANN index -> done

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss position bias and label quality:
  - [ ] Click labels inherit position bias: users click top results regardless of relevance
  - [ ] Inverse Propensity Scoring (IPS) to debias labels
  - [ ] Exploration traffic: 5-10% randomized results to gather unbiased signal
- [ ] Explain offline vs. online evaluation:
  - [ ] Offline: NDCG@10 (graded labels), MRR (navigational), MAP (comprehensive recall)
  - [ ] Online: CTR, long-click rate (>30s dwell time), query reformulation rate, conversion rate, session success rate
  - [ ] Guardrails: freshness, diversity, zero-result rate
  - [ ] Common gap: +2% NDCG offline may show 0% online lift
- [ ] Address the re-ranking layer:
  - [ ] Diversity: MMR or DPP to avoid 10 variants of the same result
  - [ ] Freshness: recency multiplier for trending queries, not evergreen
  - [ ] Seller fairness: minimum distinct sellers in top-10 (regulatory requirement)
  - [ ] Timeout fallback chain: cross-encoder -> light ranker -> BM25
- [ ] Handle LLM-augmented search:
  - [ ] Passage-level chunking (200-1000 tokens), not document-level
  - [ ] New metrics: citation faithfulness, hallucination rate, answer relevance
  - [ ] Cost: 100-1000x more expensive; routing logic needed
  - [ ] Streaming responses for 2-5s latency
- [ ] Discuss scaling and drift:
  - [ ] Query distribution drift requires weekly retraining and drift alerts
  - [ ] Cold-start for new documents: content features until behavioral signals accumulate
  - [ ] Hard negative sampling: BM25-retrieved but unclicked docs as training negatives

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made and why (hybrid retrieval cost, ranking stage complexity, LLM routing)
- [ ] Mention what you would improve with more time
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
