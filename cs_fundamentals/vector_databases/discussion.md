# Vector Databases

Vector storage, approximate nearest neighbor (ANN) search, HNSW internals, embedding models, hybrid retrieval, and production vector database operations for AI engineering interviews.

## Sources
- [Pinecone: HNSW Explained](https://www.pinecone.io/learn/series/faiss/hnsw/)
- [Qdrant: Indexing & Quantization Documentation](https://qdrant.tech/documentation/manage-data/indexing/)
- [ANN Benchmarks](https://github.com/erikbern/ann-benchmarks)
- [Faiss GitHub (Facebook Research)](https://github.com/facebookresearch/faiss)
- [Milvus Documentation](https://milvus.io/docs)
- [pgvector GitHub](https://github.com/pgvector/pgvector)

## One-Liner
Vector databases store high-dimensional embeddings and retrieve the most semantically similar items via approximate nearest neighbor search -- the backbone of every RAG, recommendation, and semantic search system.

## Core Competencies

| Competency | Why It Matters | Interview Depth |
|---|---|---|
| ANN Algorithm Internals | Explain HNSW, IVF, PQ trade-offs without hand-waving | Deep |
| Similarity Metrics | Cosine, dot product, Euclidean -- when and why | Medium |
| Vector DB Selection | Pinecone vs Qdrant vs Weaviate vs pgvector for a given use case | High |
| Hybrid Search | BM25 + dense retrieval + RRF fusion | Deep |
| Filtering & Multi-tenancy | Pre-filter vs post-filter, tenant isolation | Medium |
| Embedding Model Selection | Dimension, quality, cost trade-offs | Medium |
| Production Operations | Indexing, consistency, monitoring, scaling | Medium |

---

## 1. Vector Database Fundamentals

### What Vector DBs Do
A vector database stores vectors (arrays of floating-point numbers, typically 128-3072 dimensions) alongside optional metadata (payloads). It provides a `search(query_vector, k)` API that returns the `k` nearest vectors by a similarity metric -- typically in single-digit milliseconds for millions of vectors.

### Embedding Storage Model
Each "record" (point) has three parts:
1. **Vector**: the embedding itself (e.g., `float32[1536]` = 6KB per vector)
2. **Payload/Metadata**: structured or semi-structured key-value data (e.g., `{"doc_id": "abc", "category": "finance"}`)
3. **ID**: unique identifier for the point

### Similarity Metrics
| Metric | Formula | Range | Use Case |
|---|---|---|---|
| Cosine Similarity | `(A . B) / (||A|| * ||B||)` | [-1, 1] | Most common; direction-only (ignores magnitude). Use for text embeddings, semantic search |
| Dot Product | `A . B = sum(a_i * b_i)` | (-inf, inf) | Faster than cosine (no normalization). Use when vectors are pre-normalized (cosine == dot product for unit vectors) |
| Euclidean Distance (L2) | `sqrt(sum((a_i - b_i)^2))` | [0, inf) | Use for image embeddings, spatial data. Lower = more similar |

**Interview tip**: Most text embedding models (OpenAI, BGE, E5) produce L2-normalized vectors. For L2-normalized vectors, cosine similarity == dot product. This means you can use the faster dot-product index without any quality loss.

### When to Use a Vector DB vs Traditional DB
| Scenario | Vector DB | Traditional DB |
|---|---|---|
| Semantic search ("find documents about ML") | Yes | No |
| Keyword/exact-match search ("find order #12345") | No | Yes |
| Recommendation ("users similar to X") | Yes | No |
| RAG retrieval for LLMs | Yes | No |
| CRUD with structured joins | No | Yes |
| Image similarity search | Yes | No |

**Never use a vector DB for**: ACID transactions, complex joins, structured queries, low-dimensional data (< 16 dims). Use PostgreSQL + pgvector instead if you already have Postgres and your corpus is under 1M vectors.

---

## 2. ANN Algorithms Deep-Dive

Exact nearest neighbor search (brute force) is O(n) per query -- too slow for millions of vectors. ANN algorithms trade a small amount of recall (accuracy) for massive speedup: O(log n) or O(sqrt(n)) per query.

### HNSW (Hierarchical Navigable Small World)

HNSW is a multi-layer proximity graph. It is the gold-standard ANN algorithm in 2025-2026, used by Qdrant, Weaviate, Milvus, Pinecone, pgvector, and most production systems.

#### Structure
HNSW builds a **hierarchical graph with multiple layers**:
- **Layer 0 (bottom)**: every vector is a node. Each node connects to `M_max0 = 2*M` neighbors.
- **Layer 1, 2, ..., L (top)**: exponentially fewer nodes per layer. Each node connects to `M` neighbors. Long-range edges enable fast "zoom out" traversal.
- **Entry point**: a single node at the top layer that acts as the search starting point.

The number of layers L is probabilistic: each vector is assigned a random layer using `floor(-ln(uniform(0,1)) * mL)` where `mL = 1/ln(M)`. Most vectors (~96% for M=32) end up at layer 0. Only a handful reach the top layers.

#### Search Algorithm
1. Start at the entry point on the top layer L.
2. **Greedy traversal**: at each node, check all neighbor distances to the query. Move to the nearest unvisited neighbor. Repeat until reaching a local minimum (no neighbor is closer than current node).
3. **Drop to next layer**: at the local minimum, move to the same node in the next layer down. Repeat greedy traversal.
4. At layer 0: perform a more thorough search using `efSearch` beam width.
5. Return the top-k closest vectors found.

**Time complexity**: O(log n) -- logarithmic in the number of vectors, independent of dimensionality (though higher dimensions mean each distance computation is slower).

#### Key Parameters

| Parameter | Full Name | Controls | Effect of Increasing | Typical Values |
|---|---|---|---|---|
| `M` | Max connections per node (layer 1+) | Graph density at upper layers | Higher recall, higher memory, faster search (more edges = fewer hops) | 16-64 (default: 16 in Qdrant, 32 in Faiss) |
| `M_max0` | Max connections at layer 0 | Graph density at bottom layer | Higher recall, higher memory. Default = 2*M | 32-128 |
| `efConstruction` | Beam width during index build | Build quality | Higher recall, slower build time. No effect on search time for small batches | 100-500 (default: 100 in Qdrant) |
| `efSearch` | Beam width during search | Search quality vs speed | Higher recall, slower search. Must be >= k | 40-256 (default: 40 in Qdrant) |
| `mL` | Level multiplier | Layer distribution | Lower mL = fewer layers, more nodes per layer. Optimal: `1/ln(M)` | 1/ln(M) ~ 0.28 for M=32 |

#### HNSW Memory Formula
Memory per vector = `M * 8 * (average_layers - 0.5)` bytes (for float32 IDs + distance values)
- For 1M vectors, M=32, avg 1.03 layers: ~1M * 32 * 8 * 0.53 = ~135MB just for graph edges
- Plus raw vectors: 1M * 1536 * 4 = ~6GB
- Total: ~6.1GB for 1M vectors at 1536 dimensions

**This is the biggest weakness of HNSW**: memory usage scales linearly with both vector count and M. At 10M vectors, expect 60+ GB of RAM.

#### HNSW with Quantization (HNSW-PQ)
Combine HNSW graph structure with product-quantized vectors:
- Graph edges store quantized (compressed) vectors instead of full float32
- Memory reduced by 4-32x
- Recall drops 2-5%, search adds ~1ms for PQ decoding
- Available in Qdrant (scalar/x/binary quantization), Milvus (PQ + SQ), Weaviate

#### Filterable HNSW
Standard HNSW ignores metadata during graph traversal -- filtering is done post-search, which can cause very low recall when filters are selective (e.g., "find docs about ML where category=finance" and only 0.1% of nodes match the filter).
- **Solution**: Qdrant's "filterable HNSW" adds extra edges between nodes that share metadata values, ensuring the graph can route through filter-matching nodes. Payload indexes must be created before data ingestion for this to work.
- **Pre-filter**: apply filter before search (only search matching vectors). Precise but slow when filter is unselective.
- **Post-filter**: search all vectors, then filter results. Fast but may return fewer than k results when filter is selective.

### IVF (Inverted File Index)

IVF partitions the vector space into `nlist` Voronoi cells using k-means clustering. Each partition has a centroid; vectors are assigned to their nearest centroid.

#### Search Algorithm
1. **Training**: run k-means on a sample of vectors to find `nlist` centroids.
2. **Assignment**: assign each vector to its nearest centroid.
3. **Search**: find the `nprobe` nearest centroids to the query vector. Search only those `nprobe` partitions exhaustively.

#### Key Parameters
| Parameter | Controls | Effect |
|---|---|---|
| `nlist` | Number of partitions | Higher = finer granularity, better recall, slower training |
| `nprobe` | Partitions searched per query | Higher = more recall, slower search. nprobe=1 is fastest, nprobe=nlist is brute force |

#### IVF Characteristics
- **Memory**: raw vectors only (no graph overhead) -- much lower than HNSW
- **Build time**: O(n * nlist * d) for k-means training
- **Search time**: O(nprobe * (n/nlist) * d) -- linear in partition size
- **Recall**: good at nprobe=10-32, excellent at nprobe=nlist (brute force)
- **Online updates**: requires retraining centroids periodically. Not ideal for high-churn data.
- **Best for**: large-scale batch-indexed data (>10M vectors), memory-constrained environments

### IVF-PQ (IVF + Product Quantization)
IVF for coarse search + PQ for fine-grained distance computation within each partition:
- Vectors compressed to 32-128 bytes each (vs 6KB for float32 at 1536 dims)
- 95-98% recall at 50-100x memory reduction
- Search: O(nprobe * n * (subquantizer_dim / 256))
- Build time longer (PQ training + k-means)
- **Best for**: >10M vectors where memory is the bottleneck

### Flat Index (Brute Force)
Exhaustive scan of all vectors. O(n) per query.
- **100% recall** -- always finds true nearest neighbors
- Used as ground truth for measuring ANN recall
- Acceptable for <100K vectors (query in ~10-50ms on single CPU)
- pgvector's default index type
- **When to use**: small corpora, when recall must be perfect, development/testing

### Product Quantization (PQ)

PQ compresses high-dimensional vectors by splitting them into subvectors and quantizing each independently.

#### Algorithm
1. Split d-dimensional vector into `m` subvectors of dimension `d/m` (e.g., 768-dim vector split into 12 subvectors of 64 dims each).
2. Run k-means on each sub-dimension across all vectors to build `m` codebooks, each with 256 centroids (stored as `uint8`).
3. Each subvector is replaced by the index of its nearest centroid.
4. Result: each vector encoded as `m * 1 byte` (e.g., 12 bytes for 768 dims).

#### Distance Computation (Asymmetric Distance Computation, ADC)
To compute distance between query vector q and database vector x (PQ-encoded):
1. Pre-compute distance from q to all centroids in all codebooks: `m * 256` distance lookups (done once per query).
2. For each database vector, look up m centroid distances and sum them. This is a lookup table operation -- extremely fast.

#### PQ Parameters
| Parameter | Controls | Effect |
|---|---|---|
| `m` (subvectors) | Compression granularity | Higher m = more codebooks, finer quantization, better recall, larger codebooks |
| `nbits` | Bits per subvector code | Typically 8 (256 centroids). Higher = better recall, larger codebooks |
| Compression ratio | `d * 4 / m` bytes per vector | 768 float32 (3072 bytes) -> 12 bytes PQ = 256x compression |

#### PQ Limitations
- Recall degradation is higher for high-dimensional vectors (768+ dims)
- Cannot be used with inner-product metric directly (must convert to L2 via sqrt(x . x + y . y - 2x . y))
- Re-encoding required when changing PQ parameters
- No native support for real-time updates

### Scalar Quantization (SQ)
Simpler alternative to PQ: converts float32 to uint8 by computing per-dimension min/max across the corpus and linearly mapping values.
- 4x compression (float32 -> uint8)
- Minimal recall loss (1-2%)
- Much simpler than PQ
- Available in Qdrant, Milvus, Weaviate
- **When to use**: 2-4x memory reduction is enough (most production cases)

### ScaNN (Scalable Nearest Neighbors)
Google's ANN library. Uses **anisotropic vector quantization** -- rotates vectors before quantization to minimize quantization error along principal components.
- Better recall at same compression as PQ/SQ
- AVX2/AVX-512 optimized distance kernels
- Used internally at Google for Search and YouTube
- Available as open-source library; used in Vertex AI Vector Search
- **When to use**: when you need maximum recall at minimum memory on x86 hardware

### ANN Algorithm Comparison

| Algorithm | Recall@10 | QPS (1M vectors) | Memory (1M x 768d) | Build Time | Online Updates | Best For |
|---|---|---|---|---|---|---|
| Flat (Brute Force) | 100% | 50-200 | 3GB | 0 (no build) | Yes | < 100K vectors, dev/test |
| HNSW (M=16, efSearch=40) | 95-99% | 500-2000 | 3.5-4GB | 5-30 min | Yes (incremental) | General-purpose, < 10M vectors |
| HNSW (M=32, efSearch=128) | 98-99.5% | 200-800 | 5-6GB | 10-60 min | Yes (incremental) | High-recall, < 10M vectors |
| IVF (nlist=1024, nprobe=32) | 90-95% | 1000-5000 | 3GB | 2-10 min | Periodic retrain | 10M+ vectors, batch indexing |
| IVF-PQ (nlist=1024, nprobe=32, m=64) | 85-93% | 2000-10000 | 50-100MB | 10-30 min | Periodic retrain | 100M+ vectors, memory-limited |
| ScaNN | 93-97% | 3000-15000 | 100-500MB | 5-20 min | Periodic rebuild | Google Cloud, max throughput |

---

## 3. Embedding Models & Dimensions

### OpenAI Embeddings
| Model | Dimensions | Context | Cost | Quality (MTEB) |
|---|---|---|---|---|
| text-embedding-3-small | 1536 (truncatable to 512) | 8191 tokens | $0.02/M tokens | Good |
| text-embedding-3-large | 3072 (truncatable to 1024, 1536, 2048) | 8191 tokens | $0.13/M tokens | Excellent |

**Matryoshka embeddings**: OpenAI's v3 models support truncation. The first 512/1024 dimensions carry ~90-95% of the retrieval quality. This means you can store vectors at half or quarter size with minimal recall loss.

### Open-Source Embedding Models
| Model | Dimensions | Context | License | Quality (MTEB) |
|---|---|---|---|---|
| BGE-large-en-v1.5 | 1024 | 512 tokens | Apache 2.0 | Top-tier open |
| BGE-M3 | 1024 | 8192 tokens | Apache 2.0 | Top open, multi-lingual, multi-granularity (dense + sparse) |
| E5-large-v2 | 1024 | 512 tokens | MIT | Excellent |
| GTE-large | 1024 | 512 tokens | Apache 2.0 | Excellent |
| Nomic-embed-text-v1.5 | 768 (Matryoshka: 256/512/768) | 8192 tokens | Apache 2.0 | Good, long context |
| Cohere embed-v3 | 1024 | 512 tokens | CC-BY-NC | Top-tier, commercial |

### Dimension Trade-offs
| Dimension | Bytes/Vector (float32) | Memory (1M vectors) | Quality | Search Speed |
|---|---|---|---|---|
| 256 | 1KB | 1GB | Good (for Matryoshka models) | Fastest |
| 512 | 2KB | 2GB | Good | Fast |
| 768 | 3KB | 3GB | Very Good | Medium |
| 1024 | 4KB | 4GB | Excellent | Medium |
| 1536 | 6KB | 6GB | Excellent | Slow |
| 3072 | 12KB | 12GB | Best | Slowest |

**Rule of thumb**: doubling dimensions doubles memory and roughly doubles distance computation time, but provides diminishing quality returns above ~1024 dims for most retrieval tasks.

### Binary Quantization
Convert float32 vectors to binary (1 bit per dimension) using sign of each dimension value:
- 32x compression (1536 dims: 6KB -> 192 bytes)
- Recall drops to ~70-80% for most tasks
- Can be used as a "coarse re-ranker" before exact HNSW search
- Supported by Qdrant (over-sampling to compensate for recall loss)

### Never Mix Embedding Models
All vectors in one index/collection must use the same embedding model. Different models produce vectors in different latent spaces -- cosine similarity between cross-model vectors is meaningless. Upgrading models requires re-embedding the entire corpus.

---

## 4. Vector Database Comparison (2025-2026)

### Feature Matrix

| Feature | Pinecone | Qdrant | Weaviate | Milvus | pgvector | Chroma | FAISS |
|---|---|---|---|---|---|---|---|
| **Type** | Managed SaaS | Open-source + Cloud | Open-source + Cloud | Open-source + Cloud/Zilliz | PostgreSQL Extension | Open-source | Library (no server) |
| **Language** | Proprietary (Go/C++) | Rust | Go | Go + C++ | C (PostgreSQL extension) | Python | C++ |
| **Deployment** | Cloud only | Self-hosted + Cloud | Self-hosted + Cloud | Self-hosted + Zilliz Cloud | Self-hosted (via PostgreSQL) | Self-hosted (embedded) | In-process library |
| ** ANN Index** | Proprietary (serverless) | HNSW (filterable) | HNSW | HNSW, IVF, IVF-PQ, HNSW-PQ, DiskANN | HNSW, IVF | HNSW | HNSW, IVF, IVF-PQ, Flat |
| **Quantization** | SQ, PQ | Scalar, Binary, Product | Binary, PQ | Scalar, Product, BF16 | None | None | PQ, SQ |
| **Hybrid Search** | Yes (sparse + dense) | Yes (BM25 + dense + fusion) | Yes (BM25 + dense + fusion) | Yes (BM25 + dense + rerank) | No (requires pg_bm25 extension) | No | No (external) |
| **Metadata Filtering** | Yes | Yes (payload indexes, geo, full-text) | Yes | Yes | Yes (PostgreSQL WHERE) | Yes | No (filter externally) |
| **Multi-tenancy** | Namespaces | Payload filtering + tenant index | Collections / tenants | Partitions | Row-level (PostgreSQL RLS) | Collections | Not built-in |
| **Streaming Upserts** | Yes | Yes | Yes | Yes | Yes (INSERT/UPDATE) | Yes | Manual rebuild |
| **ACID Transactions** | No (eventual) | No (eventual) | No (eventual) | No (eventual) | Yes (PostgreSQL ACID) | No | N/A |
| **Scaling** | Horizontal (serverless) | Horizontal (sharding) | Horizontal (replication) | Horizontal (sharding) | Vertical (PostgreSQL) | Single-node only | Single-node only |
| **Max Vectors (docs)** | Billions | Billions | Billions | Billions | ~10M (before perf degrades) | ~1M | Millions (RAM-limited) |
| **Typical Latency (p99)** | 5-50ms | 1-10ms | 2-15ms | 2-10ms | 5-50ms | 2-10ms | < 1ms |
| **Typical QPS** | 100-5000 | 1000-20000 | 500-5000 | 1000-10000 | 100-2000 | 100-1000 | 10000-100000 |
| **Pricing** | Free (Starter), $50/mo min (Standard, pay-as-you-go: $0.33/GB storage, $4-4.50/M writes, $16-18/M reads) | Free (self-hosted), $25+/node (cloud) | Free (self-hosted), $25+ (cloud) | Free (self-hosted), Zilliz pricing | Free (PostgreSQL cost) | Free | Free |
| **SDK Languages** | Python, Node, Java, Go, .NET | Python, JS, Rust, Go, Java, C#, Ruby | Python, JS, Go, Java | Python, Java, Go, Node, C# | Any PostgreSQL client | Python, JS | Python, C++ |

### Decision Guide

| Scenario | Best Choice | Why |
|---|---|---|
| Startup, small corpus (<1M), want minimal infra | pgvector | Already using Postgres, zero extra infra |
| Startup, growing corpus (1-10M), want managed | Pinecone | Easiest managed option, good DX |
| Mid-size (1-50M), need hybrid search + filtering | Qdrant | Best filterable HNSW, fastest search latency, Rust-based |
| Enterprise (10M+), need maximum scale + flexibility | Milvus | Most index types, best for very large corpora |
| Prototype / local dev | Chroma | Embedded, zero config, Python-native |
| In-process, serverless, batch processing | FAISS | Library (no server), fastest raw search, zero infra |
| Multi-lingual RAG with hybrid search | Weaviate or Qdrant | Both have excellent BM25 + dense fusion |
| Cost-sensitive, already on PostgreSQL | pgvector | Free extension on existing Postgres |

### Hosted vs Self-Hosted Decision

| Factor | Hosted (Pinecone, Zilliz, Qdrant Cloud) | Self-Hosted (Qdrant, Milvus, pgvector) |
|---|---|---|
| Ops burden | Zero | High (deploy, monitor, backup, scale) |
| Cost at 10M vectors | $200-1000/month | $50-200/month (compute only) |
| Cost at 100M+ vectors | $1000-5000/month | $200-800/month |
| Data sovereignty | Data lives in provider region | Full control |
| Customization | Limited | Full (config, plugins, tuning) |
| Team size needed | 1 engineer | 2-3 engineers (including infra) |
| Time to production | Hours | Days to weeks |

---

## 5. Hybrid Search Architecture

Pure dense retrieval misses exact-match queries ("CUDA error 11", "invoice #INV-2024-001"). Pure BM25 misses semantic paraphrases ("cancel subscription" vs "terminate membership"). Hybrid search combines both.

### Architecture

```
Query ──┬──> Dense Retriever (HNSW) ──> top-k1 results ──┐
        │                                                  ├──> RRF Fusion ──> top-100 ──> Cross-Encoder Reranker ──> top-10
        └──> Sparse Retriever (BM25) ──> top-k2 results ──┘
```

### Step 1: Dense Retrieval
- Embed query with the same model used for corpus
- Search HNSW index with `efSearch` for high recall
- Return top-50 to top-100 candidates

### Step 2: Sparse Retrieval (BM25)
- Tokenize query
- Score against inverted index using BM25 formula: `IDF(q) * (f(q,D) * (k1+1)) / (f(q,D) + k1 * (1 - b + b * |D|/avgdl))`
- Return top-50 to top-100 candidates

### Step 3: Reciprocal Rank Fusion (RRF)
Combine two ranked lists into one. RRF score for document d:
```
RRF(d) = sum over all rankers r: 1 / (k + rank_r(d))
```
Where `k` is a smoothing constant (typically k=60, the value from the original paper). RRF is remarkably effective because:
- No training required (unlike learned fusion)
- Robust to different score scales (BM25 scores ~0-30, cosine scores ~0.3-0.95)
- Handles missing documents (doc in one list but not the other)

**Interview tip**: Always run dense and sparse retrieval in parallel, not sequentially. The total latency is `max(dense_latency, sparse_latency) + fusion_time`, not the sum.

### Step 4: Cross-Encoder Reranking
- Bi-encoder (embedding model) encodes query and documents independently -- loses interaction signal.
- Cross-encoder takes the (query, document) pair as input and produces a single relevance score.
- Much more accurate (~5-10% precision@10 lift) but 100-1000x slower.
- **Practical approach**: retrieve top-100 with hybrid, rerank to top-5-10 with cross-encoder.
- Reranker latency: ~5ms/doc on GPU (A10), ~50ms/doc on CPU.
- Popular models: BGE-reranker-large, Cohere rerank-3, cross-encoder/ms-marco-MiniLM-L-12-v2.

### Query Routing
Not every query needs hybrid search:
- **Keyword queries** (invoice numbers, error codes, exact names) -> BM25 only
- **Semantic queries** ("how does authentication work?") -> dense only
- **Mixed/ambiguous queries** -> hybrid

A lightweight classifier (fastText, small BERT) can route queries to the appropriate retriever, saving compute for the ~30% of queries that benefit from both.

---

## 6. Filtering

### Metadata Filtering
All production vector DBs support filtering by metadata attached to vectors. Common patterns:
- Tenant isolation: `WHERE tenant_id = "acme-corp"`
- Date filtering: `WHERE created_at > "2025-01-01"`
- Category filtering: `WHERE category IN ["finance", "legal"]`
- Geo filtering: `WHERE location WITHIN 10km OF (51.5, -0.1)`

### Pre-filter vs Post-filter

| Strategy | How | Pros | Cons |
|---|---|---|---|
| **Pre-filter** | Apply filter before ANN search. Only search vectors matching filter. | Precise recall -- guaranteed to find k results if k matching vectors exist | Slow when filter is unselective (matches >50% of vectors) -- search space is large |
| **Post-filter** | Run ANN search on all vectors, then filter results. | Fast search regardless of filter selectivity | May return fewer than k results when filter is selective (matching vectors may not be in ANN top-k) |
| **Filterable HNSW** (Qdrant) | Build extra edges between same-filter nodes during index construction | Good recall for both selective and unselective filters | Slightly more memory; requires payload indexes before ingestion |

**When to use which**:
- Pre-filter: when filter is selective (<5% match rate) and you must return exactly k results
- Post-filter: when filter is unselective (>50% match rate) or latency matters more than exact count
- Filterable HNSW: production default in Qdrant for most cases

### Performance Impact
- Filtering adds ~0.5-5ms latency depending on selectivity and whether payload is indexed
- Unindexed field filtering requires full scan of payloads -- potentially milliseconds to tens of milliseconds
- Always create payload indexes on fields used in search filters

---

## 7. Scaling & Performance

### Sharding Strategies

| Strategy | How | Best For |
|---|---|---|
| **Key-based sharding** | Shard by tenant_id or a partition key. Router routes query to correct shard(s). | Multi-tenant SaaS. Simple routing for per-tenant queries. |
| **Range sharding** | Shard by vector ID ranges or timestamp ranges. | Time-based data (news, logs). |
| **Random/round-robin** | Distribute vectors randomly across shards. | Write-heavy ingestion with even query distribution. |

### Replication
- **Qdrant**: Raft-based replication with configurable replication factor (RF=1, 3, 5). Reads can be served from any replica. Consistency: read-after-write guaranteed for same-shard reads.
- **Milvus**: Leader-follower replication within a shard. Read from followers for read scaling.
- **Pinecone**: Serverless with Dedicated Read Nodes (DRN) for read scaling. Replicas (via DRN) increase QPS linearly.

### Multi-tenancy Patterns

| Pattern | Implementation | Pros | Cons |
|---|---|---|---|
| **Collection per tenant** | Separate collection/namespace per tenant | Strongest isolation, per-tenant tuning | Doesn't scale past ~1000 tenants (too many collections) |
| **Partition per tenant** | Partition/shard by tenant_id within one collection | Scales to 10K+ tenants | Must ensure even partition distribution |
| **Payload filtering** | Single collection, filter by `tenant_id` field | Simplest, scales to millions of tenants | Must index tenant_id; larger collection = slightly slower |
| **Row-level security** | Postgres RLS on pgvector | Strongest data isolation | Postgres-only; adds query overhead |

**Qdrant tenant index**: marks a field as `is_tenant: true`, which optimizes storage locality so tenant-specific data is co-located on disk. Reduces disk reads during tenant-scoped search.

### Indexing Strategies for Scale

| Corpus Size | Strategy | Index Type | Memory Requirement |
|---|---|---|---|
| < 100K vectors | pgvector (flat) or Chroma | Flat (brute force) | < 1GB |
| 100K - 1M | pgvector (HNSW) or Qdrant | HNSW (M=16-32) | 4-12GB |
| 1M - 10M | Qdrant or Weaviate cluster | HNSW + scalar quantization | 8-30GB |
| 10M - 100M | Milvus or Qdrant cluster | IVF-PQ or HNSW-PQ | 2-20GB (with PQ) |
| 100M+ | Milvus distributed or Qdrant sharded | IVF-PQ + sharding | 10-100GB (distributed) |

### Benchmark Numbers (Typical, Single Node)

| System | Corpus | Index | QPS | p99 Latency | Recall@10 |
|---|---|---|---|---|---|
| Qdrant | 1M x 768d | HNSW M=16 efSearch=40 | 3000-8000 | 2-5ms | 97% |
| Qdrant | 10M x 768d | HNSW M=16 efSearch=40 + SQ | 1000-3000 | 3-8ms | 94% |
| Milvus | 10M x 768d | IVF-PQ nprobe=32 | 2000-5000 | 2-5ms | 90% |
| Pinecone | 1M x 768d | Managed index | 500-2000 | 10-50ms | 95% |
| pgvector | 1M x 768d | HNSW M=16 efSearch=40 | 200-1000 | 5-30ms | 95% |
| FAISS | 1M x 768d | HNSW M=32 efSearch=128 | 10000-50000 | 0.1-1ms | 99% |

---

## 8. Production Patterns

### Index Management

**Upserts** (insert or update):
- Qdrant: `upsert()` -- idempotent, replaces by point ID
- Pinecone: `upsert()` -- batch upserts in 100-1000 vector batches
- Milvus: `upsert()` (native since v2.3.0, 2023)
- pgvector: `INSERT ... ON CONFLICT (id) DO UPDATE`

**Deletions**:
- Most vector DBs support soft-delete (mark as deleted) and periodic compaction
- HNSW graph retains edges to deleted nodes until compaction -- stale edges can degrade search quality over time
- Milvus supports time-travel queries (search at a specific timestamp)

**Versioning / Index Migration**:
- When upgrading embedding models, you must re-embed the entire corpus
- Strategy: build new index alongside old index (dual-index), cut over traffic atomically
- For large corpora (10M+), migration can take hours to days
- Track `embedding_model_version` as metadata on every vector for auditability

### Consistency Models

| Vector DB | Consistency | Details |
|---|---|---|
| Pinecone | Eventual (default) or Strong (per-request) | Strong consistency doubles write latency |
| Qdrant | Read-after-write (same shard) | Raft-based; reads from leader guaranteed consistent |
| Weaviate | Eventual | Replication lag typically < 100ms |
| Milvus | Eventual | Default; can force flush for stronger guarantees |
| pgvector | Strong (PostgreSQL ACID) | Full transactional guarantees |

### Monitoring
Key metrics to track:
- **Search latency (p50/p95/p99)**: target < 10ms p99 for most use cases
- **QPS**: track per-collection and per-endpoint
- **Recall@k**: run periodic evaluation with ground-truth labeled data
- **Index size**: memory and disk usage per collection
- **Uptime**: vector DB availability (target 99.9%+)
- **Ingestion lag**: time between document creation and searchability
- **Error rate**: 4xx/5xx on search and upsert endpoints

### Backup & Recovery
- **Snapshots**: Qdrant and Milvus support creating storage snapshots (copy-on-write). Can be restored to a point in time.
- **pgvector**: standard PostgreSQL `pg_dump` / `pg_restore` or WAL-based replication.
- **Pinecone**: automatic backups, but data extraction is API-only (no raw data access).
- **FAISS**: save index to disk with `faiss.write_index()`. Load with `faiss.read_index()`.
- **RPO target**: determine acceptable data loss. For most RAG systems, RPO of seconds is fine (eventual consistency).

---

## 9. RAG Integration

For the full RAG pipeline (chunking strategies, retrieval, generation, hallucination mitigation), see **system_design/rag_system**. This section covers vector-DB-specific concerns when building RAG.

### Chunk Count Sizing
A 100-page document might produce 200-400 chunks (256-512 tokens each, 50 overlap). A corpus of 10K documents = 2-4M chunks. Each chunk becomes one vector.

### Embedding Cost Calculation
OpenAI text-embedding-3-small at $0.02/M tokens: 10K docs x 5K tokens = 50M tokens = $1 one-time cost. For larger models (text-embedding-3-large at $0.13/M tokens), the same corpus costs ~$6.50.

### Index Sizing for RAG
4M chunks x 1024 dims x 4 bytes = ~16GB raw vectors. With HNSW overhead (M=32): ~20GB. With scalar quantization: ~5GB. With PQ (m=128): ~512MB.

### Re-embedding on Model Upgrade
When upgrading embedding models, you must re-embed all chunks. Plan a dual-index migration: build the new index alongside the old one, re-embed in batches, validate with evaluation queries, then cut over traffic atomically. Track `embedding_model_version` as metadata on every vector.

---

## 10. Interview-Level Math

### Cosine Similarity Formula
```
cos(A, B) = (A . B) / (||A|| * ||B||)

Where:
  A . B = sum(a_i * b_i)         -- dot product
  ||A|| = sqrt(sum(a_i^2))       -- L2 norm (magnitude)
```

For unit vectors (L2-normalized, where ||A|| = ||B|| = 1): cos(A, B) = A . B

### Euclidean Distance (L2)
```
d(A, B) = sqrt(sum((a_i - b_i)^2))

Relationship to cosine (for non-normalized vectors):
d_L2^2 = ||A||^2 + ||B||^2 - 2 * (A . B)
```

### Index Size Estimation
For a collection of N vectors with d dimensions:
- **Raw vectors (float32)**: N * d * 4 bytes
- **HNSW graph edges**: N * M * 8 * avg_layers bytes (each edge = 1 ID (4B) + 1 distance (4B))
  - Approximation: ~N * M * 4 bytes (most edges are in layer 0)
- **Scalar quantization**: N * d * 1 byte (4x reduction)
- **Product quantization (m subvectors, 8-bit)**: N * m bytes
- **Total with HNSW + raw vectors**: N * (d * 4 + M * 4)

**Example**: 5M vectors, 1024 dimensions, M=32, HNSW + scalar quantization
- Raw vectors with SQ: 5M * 1024 * 1 = 5GB
- HNSW edges: 5M * 32 * 4 = 640MB
- Payload (avg 200 bytes/record): 5M * 200 = 1GB
- Total: ~6.6GB

### Recall@k Calculation
```
Recall@k = |relevant docs in top-k results| / |total relevant docs|

Example: 100 relevant documents for a query, k=10, found 9 of them
Recall@10 = 9/100 = 0.90 = 90%
```

### Curse of Dimensionality
In high dimensions, the concept of "nearest neighbor" breaks down:
- As d increases, distances between any two points converge toward the same value
- The ratio of nearest-neighbor distance to farthest-neighbor distance approaches 1
- This makes distance-based search less discriminative
- **Practical impact**: above ~1000 dimensions, most ANN algorithms degrade. Dimensionality reduction (PCA, autoencoders, or using lower-dim embedding models) can help.
- **Mitigation**: modern embedding models (768-3072 dims) are trained to produce well-separated clusters despite high dimensions. HNSW still works well up to ~2048 dims. Above that, consider dimensionality reduction.

---

## 11. Interview Questions with Model Answers

**Q1: Explain how HNSW works and why it's the most popular ANN algorithm.**

HNSW builds a multi-layer proximity graph. Each vector is a node. At layer 0 (the bottom), every vector exists and connects to ~2M neighbors (M is the parameter). Higher layers have exponentially fewer nodes with M neighbors each, connected by longer-range edges.

Search starts at the entry point on the top layer. At each node, it greedily moves to the nearest neighbor. When it hits a local minimum (no neighbor is closer), it drops to the same node in the next layer and continues. At layer 0, it uses a wider beam search (controlled by efSearch) to find the nearest neighbors.

Key parameters: M controls graph density (higher = better recall, more memory). efConstruction controls build quality (higher = better graph, slower build). efSearch controls search quality (higher = better recall, slower search). HNSW is popular because it gives the best recall-speed trade-off and supports incremental insertion (online updates).

---

**Q2: When would you choose HNSW vs IVF vs brute force?**

**Brute force (Flat)**: < 100K vectors or when 100% recall is required. No build time, simplest.

**HNSW**: 100K to 10M vectors. Best recall-speed trade-off. Supports real-time updates (insert new vectors without rebuilding). Higher memory usage (graph edges). Default choice for most production systems.

**IVF / IVF-PQ**: 10M+ vectors. Better memory efficiency. Requires periodic k-means retraining. Better for batch-indexed, read-heavy workloads where memory is the bottleneck. IVF-PQ adds quantization for extreme memory savings (50-100x) with 5-10% recall loss.

---

**Q3: How does product quantization work, and what are the trade-offs?**

PQ splits a d-dimensional vector into m subvectors of dimension d/m. For each sub-dimension, it runs k-means to build a codebook of 256 centroids. Each subvector is replaced by the index of its nearest centroid (1 byte). So a 768-dim vector (3072 bytes as float32) becomes m bytes (e.g., 96 bytes with m=96).

For search, asymmetric distance computation (ADC) pre-computes the query's distance to all centroids in all codebooks (m * 256 lookups). Then for each database vector, the distance is computed by summing m lookups -- extremely fast.

Trade-offs: massive memory savings (30-100x), reasonable recall loss (85-95%), no support for native real-time updates, requires re-training when data distribution changes.

---

**Q4: How would you design a vector DB strategy for a multi-tenant SaaS product?**

It depends on the number of tenants and data distribution:

**< 100 tenants**: separate collection per tenant. Strongest isolation, per-tenant tuning.

**100-10K tenants**: Qdrant with payload filtering. Single collection with `tenant_id` indexed. Use `is_tenant: true` index for storage locality optimization. Queries filter by `WHERE tenant_id = ?`.

**10K+ tenants**: single collection with tenant_id filtering is the only option that scales. Ensure tenant_id is indexed. Monitor per-tenant QPS to detect noisy neighbors (one tenant monopolizing resources). Consider rate limiting per tenant.

For data isolation requirements (e.g., HIPAA, SOC2): collection-per-tenant with encryption at rest, even if it limits tenant count. Never rely solely on application-level filtering for sensitive data.

---

**Q5: Explain hybrid search and Reciprocal Rank Fusion. Why not just use dense search?**

Pure dense search misses exact-match queries (product IDs, error codes, proper nouns). Pure BM25 misses semantic paraphrases. Hybrid search runs both in parallel and fuses results.

Reciprocal Rank Fusion (RRF) is the standard fusion method: for each document, sum 1/(k + rank) across all rankers, where k=60 is the smoothing constant. RRF doesn't require score normalization (BM25 and cosine have different scales), handles missing documents gracefully, and needs no training.

In practice, hybrid search with RRF lifts recall@10 by 5-15% over the best single retriever. Dense and sparse run in parallel, so latency = max(dense_time, sparse_time) + fusion_overhead (~1ms).

---

**Q6: What happens when you need to re-embed your corpus with a new embedding model?**

This is a major operational challenge. Steps:

1. **Dual-index migration**: spin up a new index/collection with the new embedding model. Keep the old one serving traffic.
2. **Batch re-embed**: send all documents through the new embedding model. For 10M chunks at 512 tokens each = 5B tokens. At OpenAI's $0.02/M tokens, that's $100 -- cheap. At $0.13/M tokens (text-embedding-3-large), it's $650.
3. **Validation**: run evaluation queries against both indexes, compare recall and end-to-end answer quality.
4. **Cutover**: switch traffic to the new index atomically.
5. **Cleanup**: delete the old index after validation period.

Time estimate: 10M chunks, batch of 2048, ~5000 API calls. At ~100ms per call = ~8 minutes compute time, plus network overhead = ~30-60 minutes total.

---

**Q7: How do you handle filtering in a vector database? What are the trade-offs?**

Three approaches:

1. **Post-filter**: run ANN search first, then filter results by metadata. Fast search, but when the filter is selective (matches <1% of vectors), the top-k ANN results may not contain any matching documents. You get fewer than k results.

2. **Pre-filter**: apply the metadata filter first, then run ANN search on the filtered subset. Guarantees k results if k matching vectors exist, but when the filter is unselective (>50%), the search space is nearly the full corpus -- no speedup from the index.

3. **Filterable HNSW** (Qdrant): during index construction, add extra edges between nodes that share metadata values. This lets the graph navigate through filter-matching nodes, maintaining recall even with selective filters. Requires payload indexes to be created before data ingestion.

In practice: use post-filter for unselective filters (>10% match rate), pre-filter for highly selective filters (<1%), and filterable HNSW for the middle ground.

---

**Q8: Estimate the infrastructure cost for a vector DB serving 10M vectors.**

10M vectors, 1024 dimensions, M=32, HNSW with scalar quantization:

**Memory**:
- Vectors (SQ uint8): 10M * 1024 * 1 = 10GB
- HNSW edges: 10M * 32 * 4 = 1.3GB
- Payload (avg 200 bytes): 10M * 200 = 2GB
- OS + overhead: ~2GB
- Total: ~15GB

**Hardware**: A single r5.2xlarge (64GB RAM, 8 vCPU) on AWS = ~$600/month. Or 3-node Qdrant cluster with r5.xlarge (32GB each) = ~$900/month.

**Hosted alternative**: Qdrant Cloud 3-node cluster (32GB each) = ~$300-500/month. Zilliz Cloud = ~$500-800/month.

**Self-hosted with quantization (PQ)**: vectors compressed to ~100MB. Total ~2GB. Fits on a t3.large = ~$50/month.

---

**Q9: What is the difference between cosine similarity and dot product? When does it matter?**

Cosine similarity = dot(A, B) / (||A|| * ||B||). Measures the angle between vectors, ignoring magnitude.

Dot product = sum(a_i * b_i). Measures both direction AND magnitude.

For L2-normalized vectors (||A|| = ||B|| = 1), cosine similarity equals dot product exactly. Most text embedding models produce L2-normalized vectors, so the choice doesn't matter.

When it matters: if vectors are not normalized, a vector with large magnitude will have higher dot products with everything. Use dot product for recommendation systems where magnitude encodes "popularity" or "confidence". Use cosine for pure semantic similarity.

In practice: most vector DBs use dot-product distance internally because it's faster (no division/norm computation). If vectors are pre-normalized, the results are identical.

---

**Q10: How does pgvector compare to a purpose-built vector DB like Qdrant?**

**pgvector advantages**: zero additional infrastructure (Postgres extension), ACID transactions, joins between vectors and metadata, familiar SQL tooling, strong consistency. Best for: < 1M vectors, teams already on Postgres, when you need joins with relational data.

**Qdrant advantages**: 5-10x faster search, lower latency, filterable HNSW, native quantization, built-in hybrid search (BM25), multi-tenancy support, horizontal scaling, dedicated payload indexes. Best for: > 1M vectors, high QPS, low latency requirements.

**Crossover point**: around 1M vectors, pgvector HNSW search latency exceeds 10ms and QPS drops below 1000. At 10M+ vectors, pgvector becomes impractical without external solutions (e.g., using TimescaleDB + pgvector with disk-based HNSW).

**Rule**: start with pgvector if you already have Postgres and corpus < 500K. Migrate to Qdrant when you hit latency/performance limits.

---

**Q11: What is the curse of dimensionality and how does it affect vector search?**

As dimensions increase, two problems arise:

1. **Distance concentration**: all pairwise distances converge to the same value. The ratio max(d)/min(d) -> 1. This means "nearest neighbor" becomes meaningless -- every point is roughly equally far from every other point.

2. **Volume grows exponentially**: the volume of a d-dimensional unit ball shrinks to zero as d increases. Data becomes increasingly sparse.

Impact on vector search:
- Higher dimensions = slower distance computation (O(d) per pair)
- HNSW graph quality degrades slightly above ~2048 dims
- IVF k-means clustering becomes less stable
- Quantization error increases with PQ

Mitigations: use lower-dimensional embedding models when possible (768-1024 is usually enough), use PCA to reduce dimensions (e.g., 1536 -> 512 with minimal quality loss), or use models trained for high-dimensional separability (OpenAI's embedding models handle this well).

---

**Q12: Design the vector storage layer for a RAG system with 5M documents.**

**Scale**: 5M documents, avg 3 pages each -> ~15M chunks at 256 tokens/chunk.

**Embedding model**: BGE-large-en-v1.5 (1024 dims, Apache 2.0, open-source). Host on a single A10 GPU for embedding, ~2000 chunks/sec.

**Storage sizing**:
- Vectors: 15M * 1024 * 4 = 60GB raw (too large for single node)
- With scalar quantization: 15M * 1024 * 1 = 15GB
- With PQ (m=128): 15M * 128 = 1.9GB
- HNSW edges (M=16): 15M * 16 * 4 = 960MB
- Payload: 15M * 200 = 3GB

**Decision**: use IVF-PQ or HNSW with scalar quantization on a 3-node Qdrant cluster (64GB each).

**Hybrid search**: Qdrant's built-in BM25 + dense + RRF fusion.

**Reranking**: cross-encoder on a single A10 GPU, ~15 QPS for top-100 -> top-10.

**Ingestion pipeline**: batch 2048 chunks, embed, upsert to Qdrant. Full corpus embedding: 15M chunks / 2000 chunks/sec = ~2 hours one-time. Incremental: stream new docs through same pipeline.

---

## Key Terminology

| Term | Definition |
|---|---|
| **Embedding** | Dense vector representation of text/image/audio in latent space |
| **ANN** | Approximate Nearest Neighbor -- fast search that trades recall for speed |
| **HNSW** | Hierarchical Navigable Small World -- multi-layer proximity graph ANN algorithm |
| **IVF** | Inverted File Index -- partition-based ANN using k-means clustering |
| **PQ** | Product Quantization -- compress vectors by splitting into subvectors and codebooking |
| **SQ** | Scalar Quantization -- compress float32 to uint8 per dimension |
| **Flat Index** | Brute-force exact search, O(n) per query, 100% recall |
| **efSearch** | HNSW search beam width -- higher = more recall, slower |
| **efConstruction** | HNSW build beam width -- higher = better graph quality |
| **M** | HNSW max connections per node -- higher = better recall, more memory |
| **nprobe** | IVF search parameter -- number of partitions to search |
| **nlist** | IVF parameter -- number of partitions/centroids |
| **Cosine Similarity** | Dot product of normalized vectors, measures angle [-1, 1] |
| **Dot Product** | Sum of element-wise products, measures direction + magnitude |
| **Recall@k** | Fraction of true nearest neighbors found in top-k results |
| **BM25** | TF-IDF-based sparse retrieval algorithm using inverted index |
| **RRF** | Reciprocal Rank Fusion -- combines ranked lists using 1/(k+rank) |
| **Cross-Encoder** | Joint query-document scoring model, more accurate but slower than bi-encoder |
| **Matryoshka** | Embedding dimension truncation technique (first N dims carry most signal) |
| **Upsert** | Insert-or-update operation, idempotent by vector ID |
| **Tenant Isolation** | Ensuring one customer's data is never visible to another |

---

## Cross-References

- **system_design/rag_system**: Full RAG architecture -- chunking, embedding, retrieval, generation pipeline. Vector DB is the retrieval backbone.
- **cs_fundamentals/databases**: SQL vs NoSQL, ACID, B-tree indexes. Vector DBs complement traditional DBs -- use both.
- **cs_fundamentals/caching_strategies**: Cache vector DB results for repeated queries. Redis as L2 cache for hot vector search results.
- **cs_fundamentals/distributed_systems**: Sharding, replication, consistency models apply directly to distributed vector DBs.
- **cs_fundamentals/cdn**: CDN as L3 cache for pre-computed search results or popular documents.
- **ai_assisted/**: Vector DB as tool for AI agent memory and retrieval.

## Follow-Up Variations
- How would you design vector search for a recommendation system (user-item embeddings) instead of RAG?
- What changes when your vector DB needs to serve 100K QPS instead of 1K QPS?
- How do you debug poor retrieval quality? What metrics and tools do you use?
- Design a vector DB migration plan from pgvector to Qdrant with zero downtime.
- How does ColBERT (late interaction) differ from single-vector retrieval, and when would you use it?
