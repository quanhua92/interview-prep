# Tips: Distributed Rate Limiter

## Key Concepts to Know

- **Fixed Window** — Count requests in a time window (e.g., 1 hour). Simple but allows double-burst at window boundaries.
- **Sliding Window Log** — Store timestamps of every request. Most accurate but memory-intensive (O(n) per user).
- **Token Bucket** — Tokens refill at a fixed rate; each request consumes one. Allows controlled bursts. Industry standard.
- **Leaky Bucket** — Requests are processed at a fixed rate (queue-based). Smooths traffic but adds latency.
- **Sliding Window Counter** — Hybrid: weighted count from current + previous window. Good accuracy with low memory.

## Common Mistakes

| Mistake | Why It's Wrong |
|---------|---------------|
| Using a simple counter without window reset | Counts accumulate forever — never resets |
| Ignoring the boundary problem in fixed windows | Allows 2x the limit in a short period |
| Storing every request timestamp in memory | O(n) memory per user — doesn't scale |
| Making a Redis call on every request without fallback | Single point of failure, adds latency |
| Not returning proper HTTP headers | Clients can't implement backoff correctly |

## Algorithm Comparison

| Algorithm | Memory | Accuracy | Burst Support | Complexity |
|-----------|--------|----------|---------------|------------|
| Fixed Window | O(1) | Low (boundary issue) | Yes | Simple |
| Sliding Window Log | O(n) | High | Yes | Medium |
| Token Bucket | O(1) | High | Controlled | Medium |
| Leaky Bucket | O(1) | High | No (queues) | Medium |
| Sliding Window Counter | O(1) | Medium-High | Partial | Medium |

## How to Prompt the AI Effectively

1. **Start simple:** "Implement a fixed-window rate limiter with configurable limits per user tier."
2. **Then upgrade:** "Now convert this to a token bucket algorithm. Each user has a bucket that refills at `limit/3600` tokens per second, with a max burst equal to the limit."
3. **Add distribution:** "Add a Redis backend so the rate limiter works across multiple servers. Use a Lua script for atomic check-and-decrement."
4. **Verify edge cases:** "What happens when the bucket is empty and a request arrives exactly when a token refills?"

## Architecture Patterns

```
Client → API Gateway → Rate Limiter Middleware
                        ├── Redis (centralized counter)
                        └── Local Cache (fallback)
```

- **Lua scripting in Redis** — Atomically checks and decrements the counter in a single round-trip.
- **Write-behind pattern** — Batch local increments to Redis every N seconds. Looser accuracy, lower latency.
- **Circuit breaker** — If Redis is unreachable, switch to local counters with reduced limits and alert.

## What Interviewers Look For

- Understanding of different rate limiting algorithms and their trade-offs.
- Awareness of the fixed window boundary problem and how to solve it.
- Practical distributed systems knowledge (Redis, atomicity, failure modes).
- Reasoning about fail-open vs. fail-closed and when each is appropriate.
- Ability to extend the model (weighted requests, per-endpoint limits).
