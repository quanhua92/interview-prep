# Design an Extensible Rate Limiter (LLD)

Source: [LLD Case Study: Extensible Rate Limiter (CalibreOS)](https://www.calibreos.com/learn/lld-rate-limiter)

## One-Liner
Build a thread-safe, algorithm-swappable rate limiter with clean interfaces, deterministic testability, and a migration path from single-process to distributed Redis-backed enforcement.

## Requirements

### Functional
- Limit requests per key (API key, user ID, IP) to at most N requests per time window
- Thread-safe under concurrent requests
- Algorithm swappable without changing the caller
- Storage swappable (in-memory to Redis) without changing the algorithm

### Non-Functional
- Atomic read-modify-write for correctness under concurrency
- Per-key locking (not global) to avoid throughput bottleneck
- Deterministic tests via injected clock and store
- Fail-open or fail-closed policy on storage failure

## Key Concepts
- **RateLimiter**: public API (`allow(key) -> Decision`)
- **Algorithm interface**: strategy pattern (`allow(key, policy, clock) -> Decision`)
- **Store interface**: abstraction over storage (`get`, `set`, `atomic_increment`)
- **Clock interface**: injectable time source (`now_ms() -> int`) for deterministic tests
- **Decision value object**: `(allowed, remaining, retry_after_ms)`
- **PolicyResolver**: maps key to `(limit, window_ms)` with per-tenant overrides
- **Strategy + Dependency Injection**: algorithm and storage are injected, swappable without caller changes

## Decisions

### Algorithm Choice
- **Fixed Window**: O(1) memory, simple counter per `(key, window_id)`. Allows 2x burst at window boundaries. Use only for low-stakes internal metrics.
- **Sliding Window Log**: Exact enforcement, deque of timestamps per key. O(limit) memory per key. Rarely used in production due to memory cost.
- **Sliding Window Counter**: Interpolates between two adjacent fixed windows. O(1) memory, ~0.1% error. Cloudflare uses this for edge rate limiting.
- **Token Bucket**: Configurable burst via `capacity`, sustained rate via `rate`. O(1) memory. Stripe and AWS API Gateway use this. Best default for API rate limiting.
- **Leaky Bucket**: Smooths bursty input into constant output rate. Use for protecting downstream services, not for client-facing limits.

### Concurrency Model
- **Problem**: Read-modify-write race. Two threads both read `tokens=1`, both decrement, both pass. Limit bypassed.
- **In-process fix**: Per-key `threading.Lock`. Only threads for the same key serialize; different keys run in parallel. A global lock serializes all checks and becomes the throughput bottleneck at scale.
- **Distributed fix**: Redis Lua script for atomic read-modify-write. Redis executes Lua atomically with no interleaving. Same correctness as per-key lock across servers.

### Clock Skew in Distributed Systems
- Application server clocks can diverge by 50ms+, causing token bucket refill calculations to differ across nodes.
- Mitigation: use Redis `TIME` command as the reference clock instead of app server `time.time()`.

### Failure Policy
- **Fail-open**: allow requests when storage errors. Appropriate for non-critical APIs where availability > rate correctness.
- **Fail-closed**: deny requests on storage errors. Required for billing-critical or abuse-prevention APIs.
- Not deciding is a decision: unhandled exceptions produce unpredictable default behavior.

## Deep Dives

### Class Architecture (Strategy + DI)
- `RateLimiter` owns: Algorithm, Store, Clock, PolicyResolver, fail_open flag
- Algorithm implementations: `TokenBucketAlgorithm`, `SlidingWindowLogAlgorithm`, `FixedWindowAlgorithm`
- Store implementations: `InMemoryStore` (test/local), `RedisStore` (production)
- Clock implementations: `SystemClock`, `FakeClock` (deterministic tests)
- Adding a new algorithm, new store backend, or per-tenant limits requires zero changes to `RateLimiter` or existing classes

### Token Bucket Implementation
- State per key: `(tokens: float, last_refill_ms: int)`
- On each request: refill tokens based on elapsed time (`tokens += elapsed * refill_rate`), cap at capacity, then check `tokens >= 1`
- If allowed: consume 1 token, return `(allowed=True, remaining=int(tokens))`
- If denied: compute `retry_after_ms = (1.0 - tokens) / refill_rate`, return `(allowed=False, retry_after_ms=wait)`

### Sliding Window Log Implementation
- State per key: `deque` of request timestamps
- On each request: evict timestamps older than `now - window_ms`, check `len(log) < limit`, append if allowed
- `retry_after_ms` = time until the oldest timestamp exits the window
- Exact correctness, but O(limit) memory per key

### Extensibility Matrix
| Extension | Classes Changed | Classes Added | Interface Change? |
|-----------|----------------|---------------|-------------------|
| Add leaky bucket | None | LeakyBucketAlgorithm | No |
| Swap local to Redis | None | RedisStore | No |
| Per-tenant limits | None | PolicyResolver with tenant map | No |
| Fail-open vs fail-closed | RateLimiter (add flag) | None | No |
| Retry-after header | Decision (add field) | None | No |
| Request idempotency | None | IdempotencyFilter (wraps RateLimiter) | No |

### Production Pitfalls
1. **Hardcoding `time.time()`**: Makes tests flaky and time-dependent. Inject a `FakeClock` for deterministic testing.
2. **No failure policy**: Undefined behavior on Redis outage. Explicitly choose fail-open or fail-closed.
3. **Clock skew**: Divergent server clocks cause incorrect refill calculations. Use Redis `TIME` as reference.
4. **Retry double-counting**: Network timeout + retry consumes two tokens. Use `request_id` idempotency cache to return the same Decision without re-consuming.
5. **Fixed window on security paths**: 2x boundary burst is exploitable. Use token bucket or sliding window for sensitive endpoints.

## Follow-Ups
- How would you handle weighted requests (e.g., a write costs 5 tokens but a read costs 1)?
- What happens when a tenant's limits need to change at runtime without restarting?
- How would you add request idempotency to prevent retry double-counting?
- Design a monitoring/alerting system that detects when a key is approaching its limit.
- How would you implement hierarchical rate limiting (per-endpoint + per-user global)?
