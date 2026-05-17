# Caching Strategies — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] What is the read:write ratio? (determines whether caching is worthwhile)
  - [ ] What consistency level is required? (strong vs eventual)
  - [ ] What is the acceptable staleness window? (seconds, minutes, hours)
  - [ ] Are there bursty traffic patterns? (flash sales, viral content)
- [ ] List functional requirements (3-5 items):
  - [ ] Serve cached reads at low latency (~1ms for Redis)
  - [ ] Handle cache misses gracefully with fallback to DB
  - [ ] Invalidate or update cached data when source changes
  - [ ] Support distributed cache across multiple nodes
  - [ ] Survive cache node failures without overwhelming DB
- [ ] List non-functional requirements (latency, availability, scale):
  - [ ] Cache reads in ~1ms (Redis) vs ~5-50ms (DB)
  - [ ] Handle 100,000+ QPS from a single Redis node
  - [ ] Target 95%+ cache hit rate for L2 distributed cache
  - [ ] Graceful degradation when cache is unavailable
- [ ] State your scale estimates (users, requests, storage):
  - [ ] DB handles 1,000-5,000 QPS per node
  - [ ] Redis handles 100,000+ QPS per node (10-100x throughput multiplier)
  - [ ] L2 cache at 95%+ hit rate = 20x reduction in DB load
  - [ ] Storage sizing: e.g. 200M users x 500 entries x 8 bytes = 800GB

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw a simple box diagram: Client -> LB -> [App Server] -> [L1 Cache] -> [L2 Redis Cluster] -> [DB]
- [ ] Identify the main operations and their access patterns:
  - [ ] Cache read: check L1 -> check L2 -> fallback to DB -> populate cache
  - [ ] Cache write: depends on strategy (cache-aside, write-through, write-behind)
  - [ ] Cache invalidation: TTL, event-driven, or versioned keys
  - [ ] Cache warmup: pre-populate on write or background job
- [ ] Note the read:write ratio and where caching helps:
  - [ ] Read-heavy workloads (>80% reads) benefit most from caching
  - [ ] Caching is a 10-100x read throughput multiplier at 1-5% of DB hardware cost
  - [ ] Each cache layer absorbs what the previous missed
- [ ] Present the diagram and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain cache write strategy choice and justify:
  - [ ] Cache-Aside: read-heavy workloads, eventual consistency acceptable. Most common pattern.
  - [ ] Write-Through: strong consistency required (payments, inventory). Write latency doubles.
  - [ ] Write-Behind: lowest write latency, eventual persistence OK (counters, leaderboards). Never for financial data.
  - [ ] Read-Through: simplified app code, managed cache tier (ElastiCache).
  - [ ] Refresh-Ahead: proactive refresh before TTL expiry, predictable access patterns.
  - [ ] State your choice and justify based on consistency requirements
- [ ] Define the eviction policy:
  - [ ] LRU: general-purpose, web caching, session data, social feeds
  - [ ] LFU: skewed access patterns, media caching where popular items stay popular
  - [ ] TTL: API responses, auth tokens, search results, rate limiting
  - [ ] noeviction: data loss unacceptable, persistent queues
- [ ] Select Redis data structures for each use case:
  - [ ] Hash for session data and user profiles (HSET/HGET O(1))
  - [ ] Sorted Set for leaderboards and rate limiting (ZADD O(log n))
  - [ ] List for activity feeds (LPUSH + LTRIM, LRANGE for pagination)
  - [ ] HyperLogLog for approximate unique counts (12KB regardless of cardinality)
  - [ ] String + NX for distributed locks (SET lock:res uuid NX EX 30)
  - [ ] Bitmaps for daily active user tracking (1 bit per user per day)
- [ ] Walk through the main flow end-to-end:
  - [ ] Cache hit: L1 check -> L2 check -> return (total ~1ms)
  - [ ] Cache miss: L1 miss -> L2 miss -> DB read -> populate L2 -> populate L1 -> return (~150ms)
  - [ ] Cache write: app writes to DB -> invalidate or update cache per strategy
  - [ ] Cache invalidation: TTL expiry or event-driven invalidation on data change

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss cache invalidation strategy:
  - [ ] TTL-based: simple, no coordination, may serve stale data up to TTL seconds
  - [ ] Event-driven: Kafka/CDC/DB triggers, complex but near-real-time freshness
  - [ ] Write-through: update both DB and cache atomically, doubles write latency
  - [ ] Versioned cache keys: `user:123:v7`, old keys orphaned and expire via TTL
- [ ] Explain how to handle cache stampede (thundering herd):
  - [ ] Mutex lock: distributed lock via SETNX, exactly one DB query per miss, lock contention overhead
  - [ ] Probabilistic Early Expiration (PER): no lock, no coordination, Twitter uses for timeline caches
  - [ ] Background refresh: async job refreshes before expiry, zero read latency impact
- [ ] Address multi-level caching architecture:
  - [ ] L1: process-level in-memory (Caffeine, Guava), ~1ms, local only
  - [ ] L2: distributed (Redis/Memcached), ~1ms network RTT, shared across instances
  - [ ] L3: CDN edge (CloudFront, Cloudflare), ~5-50ms, global, static/cacheable content
  - [ ] L4: browser cache, 0ms, controlled by Cache-Control headers
- [ ] Discuss distributed cache topology:
  - [ ] Consistent hashing: only K/N keys remapped on node change (vs ~N/2 with modulo)
  - [ ] Virtual nodes: ensure even load distribution across physical nodes
  - [ ] Redis Cluster: hash slots (16384), automatic resharding
- [ ] Compare Redis vs Memcached:
  - [ ] Redis: 8 data structures, persistence, replication, pub/sub, Lua scripting
  - [ ] Memcached: simpler, lower per-key overhead, natively multi-threaded, higher raw throughput
- [ ] Handle edge cases:
  - [ ] Cold start: pre-warm cache with known hot keys or background jobs
  - [ ] Cache failure: circuit breaker, graceful degradation to DB, rate limit DB queries
  - [ ] Celebrity/viral problem: avoid fan-out-on-write for high-follower accounts

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made and why (consistency vs latency vs complexity)
- [ ] Mention what you would improve with more time
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
