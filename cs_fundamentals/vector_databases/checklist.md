# Vector Databases — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Fundamentals (2-3 min)
- [ ] Define what a vector database does: stores high-dimensional embeddings, retrieves nearest neighbors by similarity metric
- [ ] Explain the three parts of a vector record: vector (embedding), payload (metadata), ID
- [ ] Name and explain the three similarity metrics:
  - [ ] Cosine similarity: `cos(A,B) = (A.B) / (||A|| * ||B||)`, direction only, range [-1,1], most common for text
  - [ ] Dot product: `A.B = sum(a_i * b_i)`, direction + magnitude. Equals cosine for unit vectors
  - [ ] Euclidean (L2): `sqrt(sum((a_i - b_i)^2))`, range [0, inf), for image/spatial
- [ ] Explain when to use a vector DB vs traditional DB:
  - [ ] Vector DB: semantic search, recommendations, RAG, image similarity
  - [ ] Traditional DB: ACID transactions, joins, structured queries, exact matches
- [ ] State your scale estimates:
  - [ ] 1M vectors x 1024 dims x 4 bytes (float32) = 4GB raw vectors
  - [ ] With HNSW (M=16): ~4.5-5GB total memory
  - [ ] With scalar quantization: ~1.2GB total
  - [ ] pgvector works up to ~1M vectors, dedicated vector DB needed beyond that

## Phase 2: ANN Algorithm Internals (5-8 min)
- [ ] Explain why ANN is needed: brute force is O(n) per query, too slow for millions of vectors
- [ ] **HNSW** — explain the full algorithm:
  - [ ] Multi-layer proximity graph inspired by skip lists and navigable small world graphs
  - [ ] Layer 0: every vector, 2M connections. Higher layers: fewer nodes, M connections, longer edges
  - [ ] Layer assignment: probabilistic, `floor(-ln(uniform(0,1)) * mL)` where mL = 1/ln(M)
  - [ ] Search: start at entry point (top layer) -> greedy traversal -> drop layers -> wide beam search at layer 0
  - [ ] Time complexity: O(log n) per query
- [ ] **HNSW parameters** — explain each and the trade-off:
  - [ ] M (max connections): higher = better recall, more memory, faster search (more edges = fewer hops)
  - [ ] M_max0 = 2*M (layer 0 connections)
  - [ ] efConstruction (build beam width): higher = better graph quality, slower build, no effect on search time (for small batches)
  - [ ] efSearch (search beam width): higher = better recall, slower search. Must be >= k
  - [ ] Typical values: M=16-32, efConstruction=100-200, efSearch=40-128
- [ ] **HNSW memory**: N * (d * 4 + M * 4) bytes approximately. Biggest weakness is memory usage.
- [ ] **IVF** — explain the algorithm:
  - [ ] Partition vector space into nlist cells using k-means
  - [ ] Search: find nprobe nearest centroids, search only those partitions
  - [ ] Parameters: nlist (partitions), nprobe (partitions to search)
  - [ ] Best for: >10M vectors, batch-indexed, memory-constrained
- [ ] **Product Quantization (PQ)** — explain the algorithm:
  - [ ] Split d-dim vector into m subvectors
  - [ ] K-means per sub-dimension -> m codebooks of 256 centroids each
  - [ ] Encode: each subvector -> 1 byte centroid index. Total: m bytes per vector
  - [ ] Search: asymmetric distance computation (ADC) with pre-computed lookup tables
  - [ ] Trade-off: 30-100x memory reduction, 5-10% recall loss
- [ ] **Scalar Quantization (SQ)**: float32 -> uint8 per dimension, 4x compression, minimal recall loss
- [ ] **Flat (brute force)**: O(n) per query, 100% recall, acceptable for <100K vectors
- [ ] **ScaNN**: Google's anisotropic quantization, better recall at same compression as PQ
- [ ] Compare algorithms in a table:
  - [ ] Flat: 100% recall, ~50 QPS (1M), 3GB
  - [ ] HNSW M=16: 97% recall, 5000 QPS, 4GB
  - [ ] IVF nprobe=32: 93% recall, 3000 QPS, 3GB
  - [ ] IVF-PQ: 90% recall, 5000 QPS, 100MB

## Phase 3: Vector DB Selection (3-5 min)
- [ ] Compare Pinecone vs Qdrant vs Weaviate vs Milvus vs pgvector:
  - [ ] Pinecone: managed SaaS only, easiest DX, $70-200/pod/month
  - [ ] Qdrant: Rust-based, best filterable HNSW, fastest latency, open-source + cloud
  - [ ] Weaviate: Go-based, good hybrid search, open-source + cloud
  - [ ] Milvus: most index types (HNSW, IVF, IVF-PQ, DiskANN), best for 10M+ vectors
  - [ ] pgvector: PostgreSQL extension, ACID, joins, best for <1M vectors
  - [ ] Chroma: embedded, Python-native, good for prototyping
  - [ ] FAISS: in-process library, no server, fastest raw search
- [ ] Walk through the decision guide:
  - [ ] < 100K vectors / already on Postgres: pgvector
  - [ ] Startup, growing corpus: Pinecone (managed) or Qdrant
  - [ ] 1-50M vectors, hybrid search: Qdrant
  - [ ] 10M+ vectors, maximum scale: Milvus
  - [ ] Prototype: Chroma
  - [ ] Batch/in-process: FAISS
- [ ] Compare hosted vs self-hosted:
  - [ ] Hosted: zero ops burden, $200-5000/month
  - [ ] Self-hosted: full control, $50-800/month, needs 2-3 engineers

## Phase 4: Hybrid Search & Filtering (5-8 min)
- [ ] Explain hybrid search architecture:
  - [ ] Dense retriever (HNSW) -> top-50
  - [ ] Sparse retriever (BM25) -> top-50
  - [ ] RRF fusion -> top-100
  - [ ] Cross-encoder reranker -> top-10
- [ ] **Reciprocal Rank Fusion (RRF)**:
  - [ ] Formula: `RRF(d) = sum over rankers r: 1 / (k + rank_r(d))`
  - [ ] k=60 (standard constant)
  - [ ] No training required, no score normalization needed, handles missing docs
- [ ] **Cross-encoder reranking**:
  - [ ] Joint query-document scoring (vs bi-encoder's independent encoding)
  - [ ] 5-10% precision@10 lift
  - [ ] ~5ms/doc on GPU, ~50ms/doc on CPU
  - [ ] Retrieve top-100, rerank to top-5-10
- [ ] **Query routing**: not all queries need hybrid. Classify queries -> route to dense, sparse, or hybrid.
- [ ] **Filtering approaches**:
  - [ ] Pre-filter: filter first, search filtered subset. Precise, slow for unselective filters
  - [ ] Post-filter: search all, filter results. Fast, may return < k results for selective filters
  - [ ] Filterable HNSW (Qdrant): extra edges between same-filter nodes. Best general-purpose
  - [ ] Rule of thumb: post-filter for >10% match rate, pre-filter for <1%, filterable HNSW in between
- [ ] **Multi-tenancy patterns**:
  - [ ] Collection per tenant (<100 tenants)
  - [ ] Partition per tenant (100-10K tenants)
  - [ ] Payload filtering by tenant_id (10K+ tenants)
  - [ ] Row-level security (Postgres) for sensitive data

## Phase 5: Embedding Models & RAG Integration (3-5 min)
- [ ] **Embedding model options**:
  - [ ] OpenAI text-embedding-3-small (1536d, $0.02/M tokens, Matryoshka truncatable)
  - [ ] OpenAI text-embedding-3-large (3072d, $0.13/M tokens)
  - [ ] BGE-large-en-v1.5 (1024d, Apache 2.0, top open-source)
  - [ ] BGE-M3 (1024d, multi-lingual, multi-granularity: dense + sparse)
- [ ] **Dimension trade-offs**: 768 -> 1024 -> 1536 -> 3072. Doubling dims doubles memory/distance computation with diminishing quality returns
- [ ] **Matryoshka embeddings**: first 512 dims carry ~90-95% of quality for supported models
- [ ] **Never mix embedding models** in one index. Upgrades require full re-embed.
- [ ] **RAG pipeline**: Documents -> Chunking -> Embedding -> Indexing -> Vector DB
  - [ ] Retrieval: Query -> Embed -> Vector Search -> Rerank -> LLM -> Answer
- [ ] **Re-embedding on model upgrade**:
  - [ ] Dual-index migration (new index alongside old, atomic cutover)
  - [ ] Cost example: 10M chunks x 512 tokens = 5B tokens at $0.02/M = $100

## Phase 6: Scaling & Production (3-5 min)
- [ ] **Sharding**: key-based (tenant_id), range (timestamp), random
- [ ] **Replication**: Raft-based (Qdrant), leader-follower (Milvus), pod replicas (Pinecone)
- [ ] **Consistency models**:
  - [ ] Pinecone: eventual (default) or strong (per-request)
  - [ ] Qdrant: read-after-write (Raft-based, same shard)
  - [ ] pgvector: strong (PostgreSQL ACID)
- [ ] **Monitoring metrics**: search latency (p50/p95/p99), QPS, recall@k, index size, uptime, ingestion lag, error rate
- [ ] **Backup**: snapshots (Qdrant/Milvus), pg_dump (pgvector), API-only export (Pinecone)
- [ ] **Versioning**: track embedding_model_version in metadata, dual-index migration
- [ ] **Index lifecycle**: upserts, deletions, soft-delete + compaction, HNSW stale edges

## Phase 7: Interview Math (2-3 min)
- [ ] Cosine similarity: `cos(A,B) = (A.B) / (||A|| * ||B||)`
- [ ] For unit vectors: cosine == dot product
- [ ] Index size estimation: N * (d * 4 + M * 4) bytes (HNSW + raw vectors)
- [ ] With SQ: N * (d * 1 + M * 4) bytes
- [ ] With PQ (m subvectors): N * (m + M * 4) bytes
- [ ] Recall@k: `|relevant in top-k| / |total relevant|`
- [ ] Curse of dimensionality: distances converge, ratio max(d)/min(d) -> 1 as d increases
- [ ] Practical example sizing: 5M vectors, 1024d, HNSW M=16, SQ = 5M * (1024 + 64) = ~5.4GB

## Phase 8: Practice Questions (5-10 min, self-test)
- [ ] Walk through HNSW search step-by-step for a single query
- [ ] Compare HNSW vs IVF-PQ for a 50M vector corpus with tight memory budget
- [ ] Design multi-tenant vector DB for 5,000-tenant SaaS with data isolation
- [ ] Explain hybrid search pipeline from query to final results
- [ ] Size infrastructure for 10M vectors, 1024 dims, 500 QPS, < 10ms p99
- [ ] Explain how PQ compresses a 768-dim vector to 12 bytes and how ADC search works
- [ ] Walk through re-embedding migration: dual index, validation, cutover, cleanup

## Phase 9: Wrap-Up (1-2 min)
- [ ] Summarize: vector DBs trade exact recall for speed via ANN algorithms
- [ ] Key trade-offs: recall vs speed vs memory (HNSW: best recall/speed, IVF-PQ: best memory)
- [ ] Production essentials: filtering, multi-tenancy, monitoring, embedding model versioning
- [ ] Mention cross-references: RAG system design, databases, distributed systems

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
