# Caching Strategies

Source: [Caching Strategies (CalibreOS)](https://www.calibreos.com/learn/hld-caching-strategies)

## One-Liner
Caching is a 10-100x read throughput multiplier at 1-5% of the cost of more database hardware -- and the most tested topic in HLD interviews.

## Functional Requirements
- Choose the right cache write strategy for your consistency requirement
- Select the appropriate eviction policy for your access pattern
- Handle cache failures, stampedes, and invalidation correctly
- Size and architect a distributed cache
- Pick the right Redis data structure for each use case

## Non-Functional Requirements
- Cache reads in ~1ms (Redis) vs ~5-50ms (DB)
- Handle 100,000+ QPS from a single Redis node (vs 1,000-5,000 QPS per DB node)
- Target 95%+ cache hit rate for L2 distributed cache
- Survive cache node failures without overwhelming the database

## Key Scale Questions
- Database: 1,000-5,000 QPS per node
- Redis: 100,000+ QPS from a single node
- 10-100x read throughput multiplier at 1-5% of database hardware cost
- L2 cache at 95%+ hit rate means DB only handles 5% of read traffic (20x reduction)

## Core Components
- **Cache Write Strategy**: cache-aside, write-through, write-behind, read-through, refresh-ahead
- **Eviction Policy**: LRU, LFU, TTL, FIFO, random, noeviction
- **Redis Data Structures**: Strings, Hashes, Lists, Sets, Sorted Sets, HyperLogLog, Streams, Bitmaps
- **Cache Invalidation**: TTL-based, event-driven, write-through, versioned keys
- **Anti-Stampede Mechanisms**: mutex lock, probabilistic early expiration (PER), background refresh
- **Multi-Level Cache**: L1 (in-process), L2 (distributed Redis/Memcached), L3 (CDN), L4 (browser)

## Key Design Decisions

### Cache Write Strategy
- **Cache-Aside (Lazy Loading)**: Read: check cache -> miss -> read DB -> write cache -> return. Write: DB only -> optionally invalidate cache key. Only caches what is actually requested (no wasted space); tolerates cache crashes. Cache miss penalty = 3 network hops; risk of stale data. Use for: read-heavy workloads (>80% reads) where milliseconds of staleness is acceptable. Most common pattern.
- **Write-Through**: Every write goes to both cache and DB synchronously before returning success. Reads after writes always see current data (strong consistency). Write latency doubles; cache fills with data that may never be read. Use for: payment systems, inventory counts, any data where reads must reflect the latest write immediately.
- **Write-Behind (Write-Back)**: Write to cache only, return immediately. Async process flushes dirty keys to DB in background. Lowest write latency -- no DB in the hot path. Risk of data loss if cache node crashes before flush; complex recovery. Use for: counters (likes, view counts), leaderboards, shopping carts where eventual persistence is fine. Never for financial transactions.
- **Read-Through**: Cache sits in front of DB. On miss, the cache itself loads from DB -- application never talks to DB directly. Simpler application code; cache is always pre-populated after first access. Cold-start: first request for any new key always misses; less control over what gets cached. Use for: content delivery using a managed cache tier (e.g. ElastiCache with read-through).
- **Refresh-Ahead (Speculative Prefetch)**: When a cached item approaches its TTL expiry, proactively refresh it before it expires. Eliminates most cache misses. May refresh items that won't be requested again (wasted compute). Use for: session data, user preferences, content with predictable expiry and high hit rate.

### Eviction Policy
- **LRU (Least Recently Used)**: Evict item not accessed for longest time. Approximated with clock algorithm. Redis: `maxmemory-policy allkeys-lru`. Best for: general-purpose web caching, session data, social feeds. Avoid when: bursty access patterns (a single scan evicts all recent items).
- **LFU (Least Frequently Used)**: Evict item with lowest access frequency. Counter decays over time in Redis. Redis: `maxmemory-policy allkeys-lfu`. Best for: media caching where popular items stay popular (skewed distribution). Avoid when: new items (they start with frequency=0 and get evicted immediately).
- **TTL (Time To Live)**: Evict items after fixed expiration regardless of access pattern. Redis: `SET key value EX seconds`. Best for: API responses, auth tokens, search results, rate limiting. Avoid when: freshness doesn't matter (TTL overhead with no benefit).
- **FIFO (First In First Out)**: Evict oldest inserted item regardless of access pattern. Not native in Redis. Best for: simple queue-like caches, rotating logs. Avoid when: most caching scenarios (ignores access frequency entirely).
- **Random**: Evict a random item. Redis: `maxmemory-policy allkeys-random`. Best for: truly uniform access patterns (rare). Avoid when: almost all production caches.
- **noeviction**: Return error when memory is full instead of evicting. Redis: `maxmemory-policy noeviction`. Best for: when data loss is unacceptable, persistent Redis queues. Avoid when: high write-rate caches (will OOM immediately).

### Redis Data Structures
- **Strings**: GET/SET/INCR in O(1). Use for: session tokens, feature flags, simple counts, cached HTML, serialized JSON objects. INCR is atomic -- safe for distributed counters without locks.
- **Hashes**: HGET/HSET O(1), HGETALL O(n fields). Use for: user profiles (HSET user:123 name Alice age 30), session objects. Better than serialized JSON when you need to update individual fields frequently.
- **Lists**: LPUSH/RPUSH/LPOP/RPOP O(1). Use for: message queues, recent activity feeds (store last N tweet IDs per user), notification queues. LRANGE for pagination: O(S + N). Warning: LINDEX is O(n) -- avoid for mid-list access.
- **Sets**: SADD/SREMOVE/SISMEMBER all O(1), SMEMBERS O(n). Use for: unique visitors, tag systems, friend/follower relationships. SINTERSTORE for set intersection (mutual friends). For large cardinalities, use HyperLogLog instead.
- **Sorted Sets (ZSETs)**: ZADD O(log n), ZRANK O(log n), ZRANGE O(log n + k). Use for: leaderboards (score = rating), priority queues, timeline feeds (score = timestamp), rate limiting windows. Workhorse of real-time ranking systems.
- **HyperLogLog**: PFADD O(1), PFCOUNT O(1). Use for: approximate unique counts with O(1) space (12KB regardless of cardinality), ~0.81% standard error. Perfect for daily active users, unique page visitors.
- **Streams**: XADD O(1), XREAD O(n). Persistent append-only log with consumer groups. Use for: event streaming (alternative to Kafka for moderate throughput), activity feeds, audit logs.
- **Bitmaps**: SETBIT/GETBIT O(1), BITCOUNT O(n/8). Use for: daily active user tracking (1 bit per user per day = 125MB for 1B users), feature flags per user, bloom filter-like structures.

### Redis Data Structure Decision Guide
| Use Case | Redis Structure | Key Pattern | Key Operation |
|----------|----------------|-------------|---------------|
| Session data | Hash | session:{session_id} | HSET / HGET / HGETALL + TTL |
| Rate limiting | Sorted Set | ratelimit:{user_id}:{window} | ZADD timestamp, ZCOUNT in window, ZREMRANGEBYSCORE |
| Leaderboard (Top-K) | Sorted Set | leaderboard:global | ZADD {score} {user_id}, ZREVRANGE 0 9 |
| Recent activity feed | List | feed:{user_id} | LPUSH + LTRIM to 500, LRANGE for pagination |
| Unique visitor count (approx) | HyperLogLog | hll:visitors:{date} | PFADD {user_id}, PFCOUNT |
| Pub/Sub messaging | Pub/Sub or Streams | channel:{topic} | PUBLISH / SUBSCRIBE or XADD / XREAD |
| Distributed lock | String + NX | lock:{resource} | SET lock:res uuid NX EX 30 |
| Geospatial index | Geo | drivers:active | GEOADD lat lng driver_id, GEORADIUS pickup 2km |
| Bloom filter (membership) | Bitmap / RedisBloom | bloom:{resource} | SETBIT at hash positions |

## Cache Invalidation
Phil Karlton: "There are only two hard things in Computer Science: cache invalidation and naming things."

- **TTL-based expiry**: Set a TTL and let items expire. Simple, no coordination needed. Con: may serve stale data for up to TTL seconds. Appropriate when: data freshness lag is acceptable (social profile, product catalog).
- **Event-driven invalidation**: When DB row changes, publish an invalidation event (via Kafka, CDC, or DB triggers). Cache consumers listen and delete/update the key. Con: complex distributed coordination. Risk: if the invalidation message is lost, cache is permanently stale. Appropriate when: data must be fresh within seconds (inventory levels, pricing).
- **Write-through invalidation**: On write, update BOTH DB and cache atomically (or invalidate cache on DB write). Con: write latency doubles. Appropriate when: strong consistency is required.
- **Versioned cache keys**: Instead of `user:123`, use `user:123:v7` where v7 is the current version. On update, increment version. Old keys naturally become orphaned and expire via TTL. Con: need to store and serve the current version number. Appropriate when: cache data is expensive to compute (ML features, aggregates).

The dirty secret: there is no perfect strategy. Every approach trades latency, consistency, and complexity.

## Cache Stampede (Thundering Herd) Solutions
- **Mutex Lock (Distributed Lock)**: On cache miss, acquire a distributed lock (Redis SETNX). Only the lock holder queries the DB and populates the cache. All other waiters retry and get the cache hit. Pros: exactly one DB query per cache miss. Cons: adds latency for all waiters (lock contention), single point of failure if lock holder crashes. Best for: expensive DB queries, ML inference results, aggregate computations.
- **Probabilistic Early Expiration (PER)**: When a cached item is close to expiry, each request independently and probabilistically refreshes it before it expires. Probability = exp(-beta x time_remaining). Pros: no lock, no coordination, scales horizontally. Cons: may perform extra refreshes. Best for: moderate-traffic caches where eventual refresh is acceptable. Twitter uses this for timeline caches.
- **Background Refresh**: A background async job refreshes cache keys before they expire. At item insertion, also schedule a refresh at (TTL - buffer) in a queue. Pros: zero extra latency for reads, no lock needed. Cons: requires a separate refresh worker, stale data possible in the buffer window. Best for: large objects that are expensive to compute.

## Multi-Level Caching Architecture
- **L1 -- Process-level in-memory cache** (Guava Cache, Caffeine): ~1ms lookup, stores hundreds of hot objects per service instance. Zero network cost. Invalidation is local only. Use for: configuration values, static reference data.
- **L2 -- Distributed cache** (Redis, Memcached): ~1ms network RTT, stores millions of objects across the cluster. Shared across all service instances. Use for: session data, user profiles, cached API responses, ML model outputs.
- **L3 -- CDN edge cache** (CloudFront, Cloudflare): ~5-50ms depending on PoP proximity, serves billions of objects globally. Can't cache dynamic/user-specific content. Use for: static assets, cacheable API responses, video chunks.
- **L4 -- Browser cache**: 0ms (no network), stores hundreds of MB per user. Controlled by Cache-Control headers. Use for: static assets with long max-age, API responses that can be stale-while-revalidate.

Key design principle: each layer absorbs what the previous missed. Sizing the L2 cache correctly (targeting 95%+ hit rate) means the DB only handles 5% of read traffic -- often a 20x reduction in DB load.

## Memcached vs Redis
| Aspect | Redis | Memcached | Winner |
|--------|-------|-----------|--------|
| Data structures | 8 types: String, Hash, List, Set, ZSet, HLL, Stream, Bitmap | String only | Redis |
| Persistence | RDB snapshots + AOF write-ahead log | None (pure in-memory) | Redis |
| Replication | Master-replica + Redis Sentinel + Redis Cluster | No native replication | Redis |
| Memory efficiency | Higher overhead per key (~64-100 bytes) | Lower overhead per key (~40 bytes) | Memcached |
| Multi-threading | Single-threaded for commands (6.0+ I/O multi-thread) | Natively multi-threaded | Memcached |
| Cluster scaling | Redis Cluster (hash slots, automatic resharding) | Client-side consistent hashing | Redis Cluster |
| Pub/Sub | Native PUBLISH/SUBSCRIBE + Streams | None | Redis |
| Lua scripting | EVAL -- atomic multi-command scripts | None | Redis |

Use Redis when you need: persistence, complex data structures, pub/sub, atomic ops, Lua scripting.
Use Memcached when you need: maximum throughput, simplest key-value, already deployed.

## Deep Dive Topics
- Distributed cache with consistent hashing: modulo hashing (key % N) remaps ~N/2 keys on node change; consistent hashing remaps only K/N keys; virtual nodes ensure even load distribution
- Cache warming strategies: fan-out service populates cache at write time for active users
- Celebrity problem: users with >10K followers are NOT fan-out-on-write cached; their tweet IDs stored only in hot cache and fetched at read time
- Sizing: 200M active users x 500 tweet_ids x 8 bytes = 800GB per region; 3 Redis nodes x 256GB each

## Interview Scenario: Design Caching for Twitter Timeline
- Setup: 200M DAU, 700K reads/sec, each timeline is a list of 500 tweet IDs
- L1 -- Redis Feed Cache: per-user feed as Redis List (LPUSH + LTRIM to 500 entries), 7-day TTL, fan-out service populates cache at tweet write time, 90%+ hit rate for active users
- L2 -- Hot Tweet Cache: separate Redis Hash per tweet storing metadata (like count, retweet count, author info). Updated by counter service via HINCRBY. Hot tweets get dedicated Redis nodes with higher replication.
- Cache miss handling: on Redis feed miss, Feed Service falls back to Cassandra -- fetches recent tweets from followed accounts, sorts by tweet_id (Snowflake), materializes cache. ~150ms vs ~5ms for cache hit.
- Celebrity problem: celebrities (>10K followers) are NOT fan-out-on-write cached. Their tweet IDs are stored only in the hot tweet cache and fetched at read time. Prevents 100M Redis writes per celebrity tweet.
- Sizing: 200M active users x 500 tweet_ids x 8 bytes = 800GB per region. 3 Redis nodes x 256GB each = 768GB. Redis Cluster with 3 shards. Cost ~$15K/month vs $1.2B/year in Cassandra read costs.

## Follow-Up Variations
- Walk me through cache-aside vs write-through. Design a caching strategy for a user profile service with 100M users.
- What is the thundering herd problem? Implement a production-safe solution.
- How does consistent hashing solve the remapping problem, and why do virtual nodes matter?
- Design the caching layer for a flash sale: 10K QPS normally, 500K QPS for 5 minutes during a sale. Product inventory can't go negative.
