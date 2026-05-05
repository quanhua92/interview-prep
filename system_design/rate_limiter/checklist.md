# Design a Rate Limiter — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] Is rate limiting per-user, per-IP, per-endpoint, or a combination of all three?
  - [ ] Should we allow burst traffic (e.g., allow a short spike up to N requests, then enforce a lower sustained rate)?
  - [ ] What happens when the limit is exceeded: return 429, queue the request, or throttle with delay?
- [ ] List functional requirements (3-5 items):
  - [ ] Track request counts per user/IP/endpoint within a time window
  - [ ] Return 429 Too Many Requests when limit is exceeded
  - [ ] Support configurable rate limits (different tiers for different users/APIs)
  - [ ] Allow burst requests up to a configurable ceiling
  - [ ] Distribute rate limit headers (`X-RateLimit-Limit`, `X-RateLimit-Remaining`, `X-RateLimit-Reset`)
- [ ] List non-functional requirements (latency, availability, scale):
  - [ ] Extremely low latency: rate limit check must add <5ms per request
  - [ ] High availability: rate limiter failure should not block all requests (fail-open vs fail-closed)
  - [ ] Scalability: handle millions of requests per second
  - [ ] Accuracy: minimize false positives (allowing over-limit) and false negatives (blocking valid requests)
- [ ] State your scale estimates (users, requests, storage):
  - [ ] ~10M active users, ~100K requests/sec at peak
  - [ ] Need to track counters for millions of keys simultaneously
  - [ ] Memory-bound: store counters for active time windows only

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw a simple box diagram: Client -> API Gateway -> [Rate Limiter Service] -> [Redis Cluster] -> [Backend Services]
- [ ] Identify the main operations and their access patterns:
  - [ ] `THROTTLE(key, limit, window)` — check if request is allowed, increment counter
  - [ ] Admin API to configure rate limits per user/tier/endpoint
  - [ ] Read-heavy in the hot path (check limit), write-heavy (increment counter)
- [ ] Note the read:write ratio and where caching helps:
  - [ ] Every request is a read+write (check + increment)
  - [ ] Cache rate limit configurations locally at each gateway to avoid Redis calls for config
- [ ] Present the diagram and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain algorithm choice and justify your decision:
  - [ ] Fixed Window Counter: simple, but has edge-burst problem at window boundaries
  - [ ] Sliding Window Log: accurate, but memory-intensive (stores every timestamp)
  - [ ] Sliding Window Counter: hybrid approach, good balance of accuracy and memory
  - [ ] Token Bucket: smooth rate, allows burst, well-suited for APIs
  - [ ] Leaky Bucket: smooth outburst, constant rate output
  - [ ] State your choice (e.g., Token Bucket via Redis + Lua script)
- [ ] Define API endpoints with method, path, request/response:
  - [ ] Rate limit check is a middleware/interceptor, not a user-facing endpoint
  - [ ] `GET /api/limits` -> `{"requests_limit": 100, "window": 60, "remaining": 42}`
  - [ ] `PUT /api/admin/limits/{user_id}` -> `{"endpoint": "...", "limit": 200, "window": 60}`
- [ ] Sketch the database schema (or in-memory data structures):
  - [ ] Redis key: `rate_limit:{user_id}:{endpoint}` -> counter + expiration TTL
  - [ ] Configuration store: SQL table `rate_limits` with `user_id`, `endpoint`, `limit`, `window`, `burst`
- [ ] Discuss SQL vs NoSQL trade-off:
  - [ ] Counter storage: Redis (NoSQL in-memory) — sub-ms latency, atomic INCR, TTL expiration
  - [ ] Configuration: SQL or config service — relational, low QPS, strong consistency
- [ ] Walk through the main flow end-to-end:
  - [ ] Request arrives at API Gateway -> extract rate limit key (user/IP) -> Lua script in Redis: check counter, increment if under limit, return remaining -> if over limit, return 429

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss caching strategy:
  - [ ] Rate limit configs cached at gateway nodes (periodic refresh or push-based updates)
  - [ ] Redis as the authoritative counter store (already in-memory cache)
- [ ] Explain scaling/partitioning approach:
  - [ ] Redis Cluster with consistent hashing for counter distribution
  - [ ] Local rate limiting as first line of defense (in-process token bucket)
  - [ ] Distributed rate limiting via Redis as second line (global accuracy)
- [ ] Address single points of failure:
  - [ ] Redis Cluster with replication for counter durability
  - [ ] Fail-open strategy: if Redis is down, allow requests (log and alert)
  - [ ] Local fallback counters if Redis is unreachable
- [ ] Handle distributed coordination and race conditions:
  - [ ] Use Redis Lua scripts for atomic check-and-increment
  - [ ] Discuss the trade-off of eventual consistency in distributed rate limiting (some overshoot possible)
  - [ ] Clock synchronization: use server time, not client time
  - [ ] Counter reset strategy: rely on Redis TTL for automatic window expiration
- [ ] Discuss monitoring and observability:
  - [ ] Track rate limit hit rate (how often 429 is returned)
  - [ ] Monitor Redis latency and availability
  - [ ] Per-user/per-endpoint rate limit utilization dashboards
  - [ ] Alert on abnormal spikes or rate limiter failures

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made and why
- [ ] Mention what you would improve with more time
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
