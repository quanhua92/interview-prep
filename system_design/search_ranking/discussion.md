# Design a Search Ranking System

Source: [Search Ranking (CalibreOS)](https://www.calibreos.com/learn/mlsd-search-ranking)

## One-Liner
Design a multi-stage search ranking pipeline that combines lexical (BM25) and semantic (dense) retrieval, followed by learning-to-rank and business-rule re-ranking, to deliver relevant results within a tight latency budget (~150ms P99).

## Functional Requirements
- Accept free-text queries and return ranked results from a document/product corpus
- Support multiple query intents: navigational (specific page), informational (learn), transactional (buy/download)
- Handle spell correction, query expansion, and intent classification before retrieval
- Apply multi-stage ranking: retrieval, ML ranking, then re-ranking with business rules
- Support LLM-augmented answers (RAG-style) alongside traditional ranked results
- Pagination and infinite scroll through results

## Non-Functional Requirements
- P99 latency under 150ms for traditional SERP; 2-5s acceptable for LLM-augmented responses (streamed)
- Support millions to billions of documents with near-real-time indexing
- Read-heavy workload (search queries dominate over document ingestion)
- High recall at retrieval stage, high precision at ranking stage
- Graceful degradation: if re-ranker times out, fall back to lighter ranker; if that fails, serve BM25 results

## Key Scale Questions
- Query distribution: 10-20% navigational, 50-60% informational, 20-30% transactional
- Retrieval stage fetches top-1000 candidates; ranking narrows to top-100; re-ranking selects top-10
- BM25 handles ~100M+ documents in under 50ms using inverted index
- ANN search over dense embeddings: ~20-50ms for 100M+ documents (FAISS, ScaNN, HNSW)
- Cross-encoder re-ranks 50 candidates in ~50ms on GPU (1ms per candidate)
- LLM-augmented queries cost 100-1000x more than traditional ranking ($0.001-$0.01 vs $0.0001)

## Core Components
- **Query Understanding Service**: spell correction, intent classification, query expansion, normalization
- **Lexical Retriever (BM25)**: inverted-index-based exact-match retrieval using Elasticsearch/Vespa/Lucene
- **Semantic Retriever (Dense)**: two-tower bi-encoder with ANN index (FAISS, ScaNN, HNSW)
- **Neural Sparse Retriever (SPLADE)**: learned sparse expansion compatible with inverted indexes
- **Light Ranker (GBDT)**: LambdaMART or LightGBM pointwise baseline, scores top-1000 candidates in ~15ms
- **Cross-Encoder Re-Ranker**: BERT-style cross-encoder for top-50 to top-100 candidates, ~50ms on GPU
- **Business Re-Ranker**: applies diversity (MMR/DPP), freshness boosting, seller fairness, policy rules
- **LLM Answer Generator**: RAG pipeline for passage-level retrieval and synthesized answers with citations
- **Evaluation Pipeline**: offline (NDCG, MRR, MAP) and online (CTR, long-click rate, conversion, zero-result rate)

## Key Design Decisions

### Hybrid Retrieval: BM25 + Dense + SPLADE
- **BM25**: irreplaceable for exact-match precision (brand names, technical terms, identifiers). Uses term frequency saturation (k1) and document length normalization (b). Cannot handle synonyms or paraphrases.
- **Dense bi-encoder**: excels at semantic/paraphrase queries. Precomputed document embeddings, fast ANN search. Lower precision than BM25 for exact-match queries.
- **SPLADE**: bridges the gap -- learned sparse expansion over vocabulary, compatible with inverted index, explainable. Expands "cancel membership" to include "terminate," "subscription," "unsubscribe."
- **Production architecture**: union top-K from BM25 + top-K from ANN + SPLADE, deduplicate, then rank. NOT replacement of one with another.

### Learning to Rank Formulation
- **Pointwise (regression/classification)**: independent relevance score per query-doc pair. Fast to train, easy to debug, but does not optimize relative ordering. Good baseline (LightGBM).
- **Pairwise (RankNet)**: trains on doc pairs, learns relative ordering. Robust to label noise but pair count grows quadratically.
- **Listwise (LambdaMART)**: optimizes entire ranked list, gradients weighted by NDCG change. Gold standard for production. LambdaMART at 150 trees scores 1000 candidates in ~15ms.

### Re-Ranking: Decoupling ML from Business Logic
- Re-ranking applies after ML ranking: diversity (MMR), freshness boosting (recency multiplier), seller fairness (min distinct sellers in top-10), out-of-stock demotion, promoted insertion
- Keeping ML and business rules separate allows each to iterate independently
- Timeout fallback chain: cross-encoder -> light ranker -> BM25 results

### LLM-Augmented Search (2024+ Shift)
- Traditional search presents ranked links; LLM-augmented search synthesizes answers via RAG with citations
- Requires passage-level (200-1000 token chunks) retrieval, not document-level
- New metrics: citation faithfulness, hallucination rate, answer relevance
- Routing: head queries with simple intent get traditional SERP (cheap); long-form questions get RAG pipeline (expensive)
- Streaming responses required as latency rises to 2-5s

## API Endpoints
| Method | Path | Description |
|--------|------|-------------|
| GET | /api/search?q={query}&page={n} | Search with ranked results |
| GET | /api/search/llm?q={query} | LLM-augmented search with synthesized answer |
| GET | /api/search/suggestions?q={prefix} | Query autocomplete/suggestions |
| POST | /api/documents | Index a new document |
| GET | /api/search/analytics?q={query} | Debug: show retrieval + ranking scores per stage |

## Database Schema
| Column | Type | Notes |
|--------|------|-------|
| doc_id | BIGINT | PK, document identifier |
| title | TEXT | Document/product title |
| content | TEXT | Full document content |
| embedding | VECTOR(768) | Dense embedding for ANN search |
| sparse_vector | JSON | SPLADE expanded sparse representation |
| category | VARCHAR | Document category/type |
| freshness | TIMESTAMP | Last updated timestamp |
| seller_id | BIGINT | Seller/owner (for fairness re-ranking) |
| in_stock | BOOLEAN | Availability flag |
| click_count | INT | Denormalized behavioral signal |
| created_at | TIMESTAMP | Ingestion time |

## Deep Dive Topics
- Position bias correction: click-derived labels inherit ranking position bias; use Inverse Propensity Scoring (IPS) and exploration traffic (5-10% randomized results) to debias
- Hard negative sampling for dense retrieval: use BM25-retrieved but unclicked documents as negatives to force semantic distinction learning
- Cold-start for new documents: no click history available; rely on content features and embedding similarity until behavioral signals accumulate
- Offline-online metric gap: +2% NDCG offline may show 0% online impact due to label coverage (<1% of query-doc pairs labeled), business logic interference, and position bias
- Query distribution drift: requires weekly retraining and drift monitoring alerts
- SPLADE vs dense tradeoff: SPLADE offers explainability and inverted-index compatibility; dense offers better recall for tail semantic queries
- ColBERT late interaction: per-token embeddings with MaxSim scoring, bridges gap between bi-encoder speed and cross-encoder accuracy for top-100 re-ranking

## Follow-Up Variations
- How would you handle a query that mixes navigational and informational intent (e.g., "Nike Air Max")?
- What happens when a trending query has no historical engagement data for freshness boosting?
- How would you design the evaluation pipeline to detect the offline-online metric gap?
- How do you prevent feedback loops where the ranker's output shapes future training labels?
- What changes to the indexing pipeline are needed to support passage-level retrieval for RAG?
- How would you route queries between traditional SERP and LLM-augmented answers to control cost?
