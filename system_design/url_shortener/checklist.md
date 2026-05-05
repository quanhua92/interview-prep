# Design a URL Shortener — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] Do users need custom aliases (e.g., `bit.ly/my-brand`) or only auto-generated short codes?
  - [ ] Should short URLs expire after a certain time, or are they permanent?
  - [ ] Do we need analytics (click count, referrer, geographic data, device type)?
- [ ] List functional requirements (3-5 items):
  - [ ] Shorten a long URL to a unique short code
  - [ ] Redirect short URL to the original long URL
  - [ ] Optionally support custom aliases
  - [ ] Return analytics for a shortened URL
  - [ ] Handle link expiration and deletion
- [ ] List non-functional requirements (latency, availability, scale):
  - [ ] High availability: redirect must not fail (users share links broadly)
  - [ ] Low latency: redirect in <50ms, shortening in <200ms
  - [ ] Scalability: handle millions of shortens and billions of redirects per day
  - [ ] Durability: short URLs must persist and not be lost
- [ ] State your scale estimates (users, requests, storage):
  - [ ] ~100M new short URLs per month (~40 new/sec, peak ~200/sec)
  - [ ] ~10B redirects per month (~4K redirects/sec, peak ~20K/sec)
  - [ ] 100M URLs stored, ~500 bytes average per record = ~50GB total storage

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw a simple box diagram: Client -> LB -> [API Service] -> [DB + Cache]
- [ ] Identify the main operations and their access patterns:
  - [ ] `POST /api/shorten` — write-heavy, relatively low volume
  - [ ] `GET /{short_code}` — read-heavy, extremely high volume (redirect)
  - [ ] `GET /api/stats/{short_code}` — read, moderate volume
- [ ] Note the read:write ratio and where caching helps:
  - [ ] Read:Write ratio is roughly 100:1 or higher (redirects vs shortens)
  - [ ] Cache the redirect mapping aggressively (hot keys in Redis/Memcached)
- [ ] Present the diagram and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain key generation strategy and justify your choice:
  - [ ] Option A: Counter + base62 encoding (simple, no collisions, sequential)
  - [ ] Option B: MD5/SHA-256 hash truncated to 7 chars (distributed, collision risk)
  - [ ] Option C: Pre-generated random IDs with uniqueness check
  - [ ] State your choice and trade-off (e.g., counter with base62 for simplicity, or hash for distributed generation)
- [ ] Define API endpoints with method, path, request/response:
  - [ ] `POST /api/shorten` -> `{"short_url": "short.ly/abc123", "short_code": "abc123"}`
  - [ ] `GET /{short_code}` -> `302 Redirect` to long URL
  - [ ] `GET /api/stats/{short_code}` -> `{"clicks": 1234, "created_at": "..."}`
  - [ ] `DELETE /api/shorten/{short_code}` -> `200 OK`
- [ ] Sketch the database schema:
  - [ ] Table `urls`: `id (BIGINT PK)`, `short_code (VARCHAR UNIQUE)`, `long_url (TEXT)`, `user_id`, `created_at`, `expires_at`, `custom_alias (BOOL)`
  - [ ] Table `analytics`: `id`, `short_code (FK)`, `timestamp`, `ip`, `country`, `device`, `referrer`
- [ ] Discuss SQL vs NoSQL trade-off:
  - [ ] SQL (MySQL/Postgres): good for relational analytics, strong consistency, easy joins
  - [ ] NoSQL (Cassandra/DynamoDB): easier horizontal scaling, high write throughput
  - [ ] Choose SQL for metadata + NoSQL (or time-series DB) for analytics
- [ ] Walk through the main flow end-to-end:
  - [ ] Shorten: client POSTs long URL -> service generates short code -> writes to DB -> returns short URL
  - [ ] Redirect: client GETs short code -> check cache first -> if miss, query DB -> update cache -> 302 redirect

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss caching strategy:
  - [ ] Cache the full mapping `{short_code -> long_url}` in Redis
  - [ ] Use write-through or write-behind on shorten
  - [ ] Set TTL (e.g., 24h) and evict on delete/expiration
  - [ ] Handle cache stampede for viral URLs (request coalescing or local cache)
- [ ] Explain scaling/partitioning approach:
  - [ ] Partition URLs table by `short_code` hash or range
  - [ ] Use read replicas for analytics queries
  - [ ] Shard analytics by time for time-series access patterns
- [ ] Address single points of failure:
  - [ ] Multi-AZ deployment for all services
  - [ ] Database failover with replicas
  - [ ] Redis cluster for cache redundancy
- [ ] Handle cache invalidation and collision handling:
  - [ ] On update/delete: invalidate cache entry, use versioning or TTL
  - [ ] For hash-based codes: check for collision and retry with different input
  - [ ] For counter-based: use a distributed counter service (Zookeeper, Redis INCR, or DB sequence)
- [ ] Discuss monitoring and observability:
  - [ ] Track redirect latency (p50, p95, p99)
  - [ ] Monitor cache hit ratio
  - [ ] Alert on high redirect error rate or cache miss spike

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made and why
- [ ] Mention what you would improve with more time
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
