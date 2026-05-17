# Design an Extensible Rate Limiter (LLD) — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] What is the key granularity (API key, user ID, IP address)?
  - [ ] Is burst traffic expected and acceptable, or should output be strictly smooth?
  - [ ] Single-process or distributed (multi-server) deployment?
  - [ ] What happens on storage failure (fail-open or fail-closed)?
- [ ] List functional requirements (3-5 items):
  - [ ] Limit requests per key to N requests per time window
  - [ ] Thread-safe under concurrent requests
  - [ ] Algorithm swappable without changing callers
  - [ ] Storage swappable (in-memory to Redis) without changing algorithm
  - [ ] Return remaining quota and retry-after information
- [ ] List non-functional requirements:
  - [ ] Atomic read-modify-write for correctness under concurrency
  - [ ] Per-key locking to avoid serializing all keys
  - [ ] Deterministic tests via injected clock and store
  - [ ] Low latency (rate limit check should not add measurable overhead)
- [ ] State your assumptions:
  - [ ] Per-key rate limiting (not global)
  - [ ] Configurable limit and window per key/tenant
  - [ ] May need to scale from single-process to distributed

## Phase 2: High-Level Design (3-5 min)
- [ ] Identify the core entities using SEDIE or similar:
  - [ ] `RateLimiter` — public API: `allow(key) -> Decision`
  - [ ] `Algorithm` — strategy interface: `allow(key, policy, clock) -> Decision`
  - [ ] `Store` — storage abstraction: `get`, `set`, atomic operations
  - [ ] `Clock` — injectable time: `now_ms() -> int`
  - [ ] `Decision` — value object: `(allowed, remaining, retry_after_ms)`
  - [ ] `PolicyResolver` — maps key to `(limit, window_ms)`
- [ ] Draw the class diagram showing Strategy + Dependency Injection:
  - [ ] RateLimiter owns Algorithm, Store, Clock, PolicyResolver
  - [ ] Algorithm implementations: TokenBucket, SlidingWindowLog, FixedWindow
  - [ ] Store implementations: InMemoryStore, RedisStore
  - [ ] Clock implementations: SystemClock, FakeClock
- [ ] Walk through the main flow:
  - [ ] Caller invokes `RateLimiter.allow(key)`
  - [ ] PolicyResolver resolves `(limit, window_ms)` for this key
  - [ ] Algorithm.allow reads state from Store, computes decision, writes updated state
  - [ ] Return Decision to caller
- [ ] Present the design and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Present the algorithm comparison and justify your choice:
  - [ ] Fixed Window: O(1) memory, but 2x burst at boundaries
  - [ ] Sliding Window Log: exact, but O(limit) memory per key
  - [ ] Sliding Window Counter: O(1) memory, ~0.1% error (Cloudflare)
  - [ ] Token Bucket: O(1) memory, configurable burst (Stripe, AWS)
  - [ ] Leaky Bucket: smooths output, protects downstream services
  - [ ] State your choice and the use case it fits
- [ ] Implement the core Algorithm.allow() method:
  - [ ] Token Bucket: refill based on elapsed time, cap at capacity, consume 1 token
  - [ ] Sliding Window Log: evict expired timestamps, check count, append if allowed
- [ ] Explain the concurrency model:
  - [ ] The read-modify-write must be atomic (read state, decide, write state)
  - [ ] Per-key `threading.Lock` for in-process concurrency
  - [ ] Redis Lua script for distributed concurrency
  - [ ] Why not a global lock: serializes all keys, becomes throughput bottleneck
- [ ] Show the RateLimiter orchestrator:
  - [ ] Resolves policy per key
  - [ ] Delegates to algorithm
  - [ ] Catches exceptions and applies failure policy (fail-open/fail-closed)
- [ ] Demonstrate testability:
  - [ ] Inject `FakeClock` to advance time deterministically
  - [ ] Inject `InMemoryStore` to inspect state after operations
  - [ ] No `time.sleep()` calls in tests

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss distributed rate limiting:
  - [ ] In-process locks do not span servers
  - [ ] Redis Lua script for atomic read-modify-write across nodes
  - [ ] Use Redis `TIME` command as reference clock to handle clock skew
  - [ ] Store interface unchanged, only implementation swaps to RedisStore
- [ ] Address failure modes:
  - [ ] Redis unavailable: fail-open (allow, for non-critical APIs) or fail-closed (deny, for billing/abuse)
  - [ ] Retry double-counting: network timeout + retry consumes two tokens
  - [ ] Idempotency: pass `request_id`, check idempotency cache before consuming token
- [ ] Handle the boundary burst problem:
  - [ ] Fixed window allows 2x limit across window boundaries
  - [ ] Attacker can exploit by timing requests at boundary
  - [ ] Token bucket or sliding window required for security-sensitive endpoints
- [ ] Discuss extensibility:
  - [ ] New algorithm: implement Algorithm interface only, no other changes
  - [ ] New storage backend: implement Store interface only
  - [ ] Per-tenant limits: PolicyResolver with tenant override map
  - [ ] All extensions leave RateLimiter, Decision, and existing classes unchanged
- [ ] Discuss production concerns:
  - [ ] Striped locking (N=256 buckets) for very high cardinality keys
  - [ ] Memory limits for sliding window log at scale
  - [ ] Monitoring: track deny rate, p99 latency of rate limit check, store health

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made and why (algorithm choice, failure policy)
- [ ] Mention what you would improve with more time
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
