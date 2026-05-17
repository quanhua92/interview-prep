# Back-of-Envelope Estimation

Source: [Back-of-Envelope Estimation (CalibreOS)](https://www.calibreos.com/learn/hld-back-of-envelope-estimation)
Supplement: [Numbers Every Engineer Should Know (CalibreOS)](https://www.calibreos.com/learn/hld-numbers-cheat-sheet)

## One-Liner
Use quick arithmetic on DAU, action rates, and data sizes to derive QPS, server count, and storage -- then connect every number to a concrete architecture decision.

## Functional Requirements
- Derive traffic (avg + peak QPS) from DAU and per-user action rates
- Estimate capacity: how many servers, what cache hit rate is needed
- Estimate storage: raw data size plus replication, indexes, and encoding multipliers
- Connect each estimate to a specific design constraint (caching, sharding, CDN, etc.)

## Non-Functional Requirements
- Get the exponent right -- order of magnitude matters, not the coefficient
- Complete estimation in 3-5 minutes during an interview
- Always distinguish average QPS from peak QPS (3x multiplier)
- Always apply replication factor (3x) to storage estimates
- Sanity-check from two independent directions when possible

## Key Scale Questions
- What is the DAU? (If not given, estimate from MAU x 0.3-0.5)
- What is the per-user action rate for reads vs writes?
- What is the read:write ratio? (Consumer social ~100:1, messaging ~1:1, e-commerce ~1000:1)
- What is the peak-to-average multiplier? (Consumer apps 3x, B2B 5-10x)
- What are the three storage multipliers? (Replication x3, Index overhead x1.5-2x, Encoding variants x2-4x for video)

## Core Components

### The Three-Step Drill
1. **Traffic**: DAU -> actions/user/day -> avg QPS (divide by 86,400) -> peak QPS (multiply by 3)
2. **Capacity**: peak QPS / single-server throughput -> server count. For caching: required hit rate = (peak QPS - DB capacity) / peak QPS
3. **Storage**: daily raw = writes/sec x bytes/record x 86,400. Apply multipliers for replication, indexes, encoding. Extrapolate to 5-year total.

### Key Benchmarks

**Latency numbers to memorize:**
- L1 cache: 0.5 ns | L2 cache: 7 ns | DRAM: 100 ns
- SSD random read (4KB): 150 us | SSD sequential read (1MB): 1 ms
- Intra-datacenter RTT: 500 us | Cross-continent RTT: ~150 ms
- HDD seek: 10 ms (cold storage only)

**Data object sizes:**
- int64 ID: 8 bytes | UUID: 16 bytes | SHA-256: 32 bytes
- Tweet (text + metadata): ~1 KB | User profile row: 500B-1KB
- Thumbnail (100x100 JPEG): 5-15 KB | Full photo (400x400): 50-150 KB
- 1 min 720p video: 30-60 MB | 1 min 1080p: 60-100 MB | 1 min 4K: 200-400 MB

**Single-node throughput:**
- PostgreSQL complex queries: 1K-5K QPS (simple SELECT: 10K-50K)
- Redis GET/SET: 100K-300K ops/sec
- Kafka broker (1KB msgs): ~500K msgs/sec
- Go/Java app server: 10K-30K RPS
- Nginx/HAProxy: 50K-100K RPS
- Python/Django (per process): 500-2K RPS

## Key Design Decisions

### Peak QPS = Avg QPS x 3
Consumer traffic concentrates in a 6-8 hour daytime window. Distributing 24-hour activity over 8 hours yields a 3x multiplier. B2B apps concentrate in business hours (5-10x). Breaking news events can spike 50x. Always state the multiplier explicitly.

### Required Cache Hit Rate
Formula: (peak QPS - DB capacity) / peak QPS. Example: 70K peak QPS with a 5K QPS Postgres -> need 93% cache hit rate to keep DB load at ~4.9K QPS. If you cannot achieve that hit rate, you need multiple DB replicas or sharding.

### Storage Tier Selection
- <1 TB: single DB instance
- 1-100 TB: object storage (S3) for blobs, DB for structured data
- 100 TB - 1 PB: tiered retention (hot/warm/cold), add analytics layer
- >1 PB: distributed file system (GFS/Colossus/HDFS), multi-DC replication

### QPS-Driven Architecture
- <1K QPS: single server + single DB, no caching
- 1K-10K QPS: LB + 2-5 app servers + DB read replicas, light caching
- 10K-100K QPS: Redis mandatory (93%+ hit rate), horizontal fleet, DB sharding
- 100K-1M QPS: CDN, multi-tier caching, Cassandra/sharded Postgres, ~100 app servers
- >1M QPS: distributed cache clusters, multi-region active-active, purpose-built storage

## API Endpoints
Not applicable -- this is a estimation methodology, not a specific service. The estimation outputs (QPS, storage, server count) become inputs to whatever system you are designing.

## Database Schema
Not applicable -- but remember: index overhead adds 1.5-2x to raw storage for relational DBs. Plan schema + indexes together.

## Deep Dive Topics

### Worked Example: Twitter Timeline (200M DAU)
- Read: 10 loads/day/user -> avg 23K reads/sec -> peak ~70K
- Write: 0.1 tweets/day/user -> avg 231 tweets/sec -> peak ~700
- Read:write ratio ~100:1 -> architecture challenge is all on the read path
- Cache at 95% hit rate reduces DB load from 70K to 3.5K QPS (single-instance range)
- Storage: 700 tweets/sec x 1KB x 86,400 = ~60 GB/day raw -> ~330 TB over 5 years (with replication)
- Media: 20% of tweets have photos (~300KB each) = ~3.6 TB/day -- dwarfs text storage

### Worked Example: WhatsApp (1B DAU)
- 40 msgs/day/user -> 463K msgs/sec avg -> 1.4M peak
- Read:write ~1:1 (every message sent is delivered)
- Non-obvious constraint: 1B persistent TCP connections. At 65K/server -> ~15K servers just for connection state
- Storage: 500 bytes/msg x 463K x 86,400 = ~20 TB/day. E2E encryption means only metadata is server-side.

### Worked Example: YouTube (500 hours uploaded/min)
- 30,000 min of video/min x 60 MB/min (1080p) = ~2.6 PB/day raw
- Encoding multiplier (5 tiers: 4K+1080p+720p+480p+360p) ~4x -> ~10 PB/day
- With 3x replication -> ~30 PB/day. 5-year total: ~55 EB (exabyte-scale)
- Sanity check from corpus size: 800M videos x 7 min avg x 60 MB = 336 PB in 1080p tier. Historical average ~46 TB/day vs current ~10 PB/day -- gap explained by upload growth acceleration.

### The Two-Direction Sanity Check
Derive estimates via two independent approaches. If they agree within 10x, your math is sound. If they disagree by >100x, find the units error. In interviews: "Let me sanity-check this from a different angle..." signals systematic thinking.

## Extended Latency Hierarchy

Source: [Numbers Every Engineer Should Know (CalibreOS)](https://www.calibreos.com/learn/hld-numbers-cheat-sheet)

| Operation | Latency | If 1ns = 1sec | Architectural Implication |
|---|---|---|---|
| L1 cache read | ~1 ns | 1 second | Hot loop inner data; CPU-bound code lives here |
| L2 cache read | ~4 ns | 4 seconds | 4x L1 penalty; still fast enough for tight inner loops |
| L3 cache read | ~10 ns | 10 seconds | 10x L1; shared across cores; NUMA-aware code avoids cross-socket misses |
| Mutex lock/unlock (uncontended) | ~25 ns | 25 seconds | Contended mutex is 10-100x worse; use lock-free or per-CPU data structures |
| Main memory (DRAM) | ~100 ns | 1.7 minutes | 200x L1; reason columnar formats outperform row formats for analytics |
| SSD random read (4 KB) | ~100 us | 1.7 hours | Avoid random reads on p99-sensitive paths; LSM-trees batch writes to make reads sequential |
| Intra-DC RTT (same datacenter) | ~500 us | ~8 minutes | Every microservice call costs this minimum; a chain of 5 sync hops = ~2.5 ms before business logic |
| Inter-AZ RTT (same region) | ~2 ms | ~33 minutes | Sync replication across AZs adds ~2 ms per write; most systems use async cross-AZ replication |
| SSD sequential read (1 MB) | ~1 ms | 16.7 hours | ~1 GB/s sequential; columnar on SSD beats row by 10-50x via sequential reads |
| HDD random seek | ~10 ms | ~4 months | Cold/archival storage only; no low-latency app should rely on random HDD reads |
| Cross-region US-EU RTT | ~100 ms | ~1.9 years | User-perceivable; serve from regional CDN/edge or replicate data into region |
| Cross-region US-Asia RTT | ~200 ms | ~3.8 years | Hard UX cliff; multi-region active-active or local read replicas mandatory for APAC |

Key insight: six orders of magnitude separate L1 (~1 ns) from cross-continental RTT (~200 ms). Intra-DC network (500 us) is faster than SSD sequential read of 1 MB (1 ms) -- distributed in-memory caches outperform local SSD caches for latency-sensitive workloads.

## Extended Throughput Benchmarks

| Component | Throughput (Single Node) | Key Caveat |
|---|---|---|
| PostgreSQL -- complex OLTP (joins, filters) | ~1K-5K QPS | Drops sharply with full-table scans or N+1 queries |
| PostgreSQL -- simple PK selects | ~50K QPS | Single-row indexed lookups only; rare in real OLTP workloads |
| MySQL (InnoDB) -- simple indexed reads | ~5K-20K QPS | Buffer pool hit rate must be ~99%; cold starts catastrophically slower |
| Redis GET/SET (single-threaded) | ~100K-300K ops/sec | Command execution is single-threaded regardless of CPU cores |
| Redis pipeline mode (batch GETs) | ~1M+ ops/sec | Only for independent batchable operations |
| Memcached GET/SET | ~100K-200K ops/sec | Multi-threaded; better than Redis for pure in-memory caching at high concurrency |
| Cassandra per node -- writes (LOCAL_QUORUM, RF=3) | ~20K-50K ops/sec | LSM-tree append; write perf stable under load |
| Cassandra per node -- reads (LOCAL_QUORUM, RF=3) | ~10K-20K ops/sec | Read amplification on LSM compaction; hot partitions degrade faster |
| Kafka broker (1 KB msgs, RF=3) | ~500K msgs/sec; ~1 GB/s | Optimized for 1 KB-100 KB messages; smaller/larger msgs change throughput |
| Nginx HTTP (reverse proxy, no TLS) | ~50K-100K req/sec | TLS termination adds ~20% CPU; WebSocket proxying throughput is lower |
| Go/Java app server (stateless JSON API) | ~10K-30K RPS | Drops 5-10x if each request makes synchronous DB calls |
| Python/Django (Gunicorn, 4 workers/CPU) | ~500-2K RPS | Use FastAPI + uvicorn for I/O-bound to reach ~5K-10K RPS |
| Elasticsearch -- full-text search | ~1K-5K queries/sec/shard | Heavily dependent on index size and JVM heap; cold starts cause 10-50x degradation |
| ZooKeeper -- reads / writes | ~60K-80K TPS reads; ~10K-15K TPS writes | Writes go through leader; use etcd for better write scaling |
| gRPC server (Go, simple unary) | ~100K-200K RPC/sec | HTTP/2 multiplexing; streaming RPCs have different characteristics |
| S3 (per key prefix) | ~3.5K PUT/sec; ~5.5K GET/sec | Limit is per prefix; randomize key prefixes to distribute across S3 partitions |

### Dangerous Throughput Misconceptions
- **Postgres 50K QPS is a trap**: that number is for `SELECT * FROM table WHERE id = $1` only. Add one JOIN -> drop to ~10K. Add ORDER BY on non-indexed column -> drop to hundreds.
- **Redis is NOT multi-threaded for commands**: Redis 6+ has threaded I/O but command execution is single-threaded. Throughput plateaus at ~300K ops/sec regardless of CPU cores.
- **Kafka throughput assumes 1 KB messages**: very small messages (100 B) reduce throughput because protocol overhead dominates; very large messages (10 MB) fill network buffers.
- **Elasticsearch 5K QPS assumes warm JVM and hot OS page cache**: cold starts cause 10-50x latency degradation. A node restart takes 15-30 min for page cache warmup.

## Connection & Concurrency Limits

| Connection Type | Default Limit | Tuned Maximum | Implication |
|---|---|---|---|
| Linux TCP (ephemeral ports) | ~28K outbound per IP pair | ~65K with full port range; ~1M+ with SO_REUSEPORT | Never design one server making >10K concurrent outbound TCP without connection pooling |
| WebSocket -- Node.js (libuv) | ~65K per server (fd default) | ~1M with ulimit -n 1048576 + kernel tuning | 1B connections needs ~1K servers at 1M/server |
| WebSocket -- Go (goroutine/connection) | ~100K concurrent (~8 KB/goroutine) | ~1M+ with careful memory management | Go is preferred for high-connection gateways; 1M goroutines = ~8 GB RAM |
| Java Tomcat -- thread-per-request (BIO) | ~200 threads (1 MB stack each) | ~5K-10K before OOM | Wrong model for WebSocket; use NIO connector or async frameworks |
| Java Netty / Spring WebFlux (NIO) | ~65K fd per process | ~1M with OS tuning | Production-grade Java async I/O; used by Cassandra, ES, gRPC Java |
| Nginx worker connections | 1,024 per worker | ~65K per worker; 4-8 workers typical | 4 workers x 65K = 260K concurrent per Nginx instance |
| PostgreSQL connections | 100 max_connections | ~500 with pgBouncer; hard limit ~1,000 | Always use pgBouncer or RDS Proxy at scale |
| Redis connections | ~10K concurrent (default) | ~65K with tcp-backlog tuning | Connection count rarely the bottleneck; command throughput and memory matter more |

### The Connection Count Trap
High-connection-count services have a fundamentally different scaling problem: the binding resource is file descriptors and kernel connection state, not CPU or disk I/O.

WhatsApp example: ~1B DAU with persistent TCP connections. At 65K connections/server -> ~15,385 servers. With tuning to 1M/server -> ~1,000 servers dedicated purely to connection state.

This forces a dedicated connection tier:
- **Connection tier**: stateless TCP/WebSocket gateways maintaining only connection state. No DB calls. Routes messages via message broker. Go preferred (goroutines ~8 KB vs ~1 MB Java threads).
- **Message broker**: Kafka or Redis Pub/Sub for fan-out and delivery guarantees.
- **Routing index**: Redis hash of `user_id -> connection_server_id`, updated on connect/disconnect.

## Network Bandwidth Reference

| Instance / NIC | Nominal Bandwidth | Actual TCP Throughput | Notes |
|---|---|---|---|
| t3.medium (AWS burstable) | Up to 5 Gbps (burst) | ~300 MB/s burst; ~30 MB/s baseline | Dangerous for steady-state workloads; baseline exhausts quickly |
| m5.xlarge (4 vCPU, 16 GB) | Up to 10 Gbps | ~1.2 GB/s | Sufficient for most microservices |
| c5n.2xlarge (network-optimized) | Up to 25 Gbps | ~3 GB/s | Kafka brokers and large Redis nodes should use c5n family |
| c5n.18xlarge (72 vCPU) | 100 Gbps | ~12 GB/s | Inter-broker Kafka replication at scale |
| Standard 1 Gbps NIC | 1 Gbps | ~125 MB/s | Minimum for any production DB; Kafka replication can saturate it |
| Typical 10 Gbps NIC | 10 Gbps | ~1.25 GB/s | Kafka at 1 GB/s ingress + 3x replication = ~4 GB/s total -> already at ~40% line rate |

Network is the bottleneck candidates forget: `1 Gbps = 125 MB/s` (divide by 8, subtract ~5% TCP overhead). For write-heavy distributed systems, compute `writes/sec x record_size x replication_factor` and compare to NIC throughput. If result exceeds ~50% of NIC capacity, use network-optimized instances or reduce replication fan-out.

## Storage Multipliers (Extended)

| Multiplier | Factor | Applies To |
|---|---|---|
| Replication factor | x3 | All durable distributed storage (Kafka RF=3, HDFS RF=3, S3 3+ AZs, Postgres primary+2 replicas, Cassandra RF=3) |
| Index overhead (relational DB) | x1.5-2x | Postgres/MySQL with B-tree indexes; 3-4 indexes can equal table size |
| Encoding variants (video) | x2-4x | Video platforms: 5 tiers (4K, 1080p, 720p, 480p, 360p) = ~4.1x total relative to 1080p |
| Compression (text/logs) | x0.1-0.3x (reduction) | gzip/Snappy/Zstd; Kafka segments compressed; Parquet files 5-10x smaller than raw JSON |
| CDN edge caching | x0 for cached content | Static assets served 90-99% from CDN POPs; origin accessed rarely |

## Quick Volume-to-Architecture Reference

| Daily Volume | Avg QPS | Peak QPS (3x) | Architecture Trigger |
|---|---|---|---|
| 100K req/day | ~1.2 QPS | ~3.5 QPS | Single server; no caching; focus on correctness |
| 1M req/day | ~12 QPS | ~35 QPS | Single app server + single DB; light monitoring |
| 10M req/day | ~116 QPS | ~347 QPS | LB + 2-3 app servers; DB read replica worth considering |
| 100M req/day | ~1.2K QPS | ~3.5K QPS | Redis caching beneficial; DB read replicas; ~5 app servers |
| 1B req/day | ~11.6K QPS | ~34.7K QPS | Redis mandatory; 3-5 DB read replicas; ~30 app servers; CDN for static |
| 10B req/day | ~115.7K QPS | ~347K QPS | Multi-tier caching; DB sharding or Cassandra; ~350 app servers; multi-AZ |
| 100B req/day | ~1.16M QPS | ~3.47M QPS | Google-scale; multi-region active-active; custom storage; CDN for everything |

## The 10 Numbers to Internalize

1. **L1 cache: ~1 ns** -- in-process hot data; 6 orders of magnitude faster than cross-region
2. **DRAM: ~100 ns** -- in-process cold data; basis of all in-memory caches
3. **SSD random read: ~100 us** -- local disk; fast for warm data but 1,000x slower than DRAM
4. **Intra-DC RTT: ~500 us** -- every microservice call costs this minimum
5. **Cross-region RTT: ~100-200 ms** -- forces CDN, regional deployments, or async patterns
6. **Postgres complex QPS: ~1K-5K** -- the ceiling that makes caching mandatory
7. **Redis ops/sec: ~100K-300K** -- the ceiling that makes Redis Cluster necessary
8. **Kafka throughput: ~500K msgs/sec at ~1 GB/s** -- the broker throughput anchor
9. **1 day = ~86,400 seconds (use 10^5)** -- the denominator for every QPS calculation
10. **Replication factor: x3** -- the multiplier that converts raw storage to true infrastructure cost

## Architectural Thresholds

- **5K QPS (Postgres complex query limit)**: above this, add Redis caching. Target hit rate = `(peak QPS - DB capacity) / peak QPS`. Below 5K QPS, caching adds complexity without solving a real bottleneck.
- **300K ops/sec (Redis single-node limit)**: above this, use Redis Cluster or application-level pipelining. Pipelining only works when operations are independent.
- **1M connections (connection tier limit)**: above this, need a fleet of connection-handling servers with a routing index (Redis `user_id -> server_id`). Connection tier must be separate from business logic.
- **100 TB (single DB limit)**: above this, Postgres becomes operationally impractical (backup/restore time, WAL volume, vacuum). Shard, migrate to Cassandra/DynamoDB, or move blobs to S3/GCS.
- **1 PB (distributed FS required)**: above this, structured data needs distributed DB (Cassandra, Bigtable, DynamoDB). HDFS/Colossus for batch processing (ML training, analytics).

## How to Cite Numbers in an Interview

Good pattern: **cite the number -> apply to your estimated QPS -> conclude with the architectural decision**.

- "A single Postgres handles ~1K-5K complex QPS -- at our 30K peak, we need caching or 6-30 read replicas."
- "Redis handles ~100K-300K ops/sec. Our peak cache load is 28K -- well within single-node, no cluster needed."
- "Each connection server handles ~65K WebSocket connections default, ~1M with tuning. At 50M concurrent users, that's 50-800 servers."

Never cite a benchmark as a constant. Always add: "for this workload shape" or "for simple indexed reads" or "this drops 5x with joins."

## Follow-Up Variations
- How would you estimate for a real-time multiplayer game (state sync, not request-response)?
- What changes if the system is write-heavy (1:1 or write-dominated) instead of read-heavy?
- How do you estimate bandwidth cost when serving video at scale?
- What if the interviewer gives you MAU instead of DAU?
- How do encoding choices (H.264 vs H.265 vs AV1) change the storage multiplier?
