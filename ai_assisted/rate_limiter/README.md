# Problem 03: Distributed Rate Limiter

**Role:** Backend / Infrastructure Engineer
**Duration:** 45-60 minutes
**Difficulty:** Hard
**Format:** System Design Prototyping → Feature Build-Out

---

## Background

Our API platform serves millions of requests per day across multiple endpoints. We need a rate limiting service that throttles requests based on user tiers:

- **Free tier:** 100 requests/hour
- **Pro tier:** 1,000 requests/hour
- **Enterprise tier:** 10,000 requests/hour

When a user exceeds their limit, the API should return `429 Too Many Requests` with a `Retry-After` header.

You'll start by implementing a single-server rate limiter, then we'll discuss distribution.

## Functional Requirements

1. Given a `user_id` and `tier`, determine whether a request is allowed or throttled.
2. Return remaining quota and time until quota resets.
3. Support three user tiers with configurable limits.
4. Return proper HTTP response headers (`X-RateLimit-Remaining`, `X-RateLimit-Reset`, `Retry-After`).

## Non-Functional Requirements

- Decision must be made in < 5ms at the application layer.
- The system should be accurate — no false positives (throttling valid requests) and minimal false negatives (allowing over-limit requests).
- Rate limit state should persist across server restarts.

## Constraints

- Start with a single server, in-memory implementation.
- Use a fixed time window (1 hour) for the initial implementation.
- You may assume user IDs are valid and tiers are one of: `free`, `pro`, `enterprise`.

## Starter Interface

```python
class RateLimiter:
    def check(self, user_id: str, tier: str) -> RateLimitResult:
        """Check if a request is allowed. Returns allow/deny + metadata."""
        ...

class RateLimitResult:
    allowed: bool
    remaining: int
    reset_at: int       # Unix timestamp
    retry_after: int    # Seconds until next window (0 if allowed)
```

---

## Follow-Up Questions

### Follow-Up 1: Token Bucket Algorithm
> "Fixed windows have a problem: a user can send 100 requests at 11:59 and another 100 at 12:01 — 200 requests in 2 minutes. How would you fix this?"

- Implement a **token bucket** or **sliding window log** algorithm instead.
- Explain the trade-off between accuracy and memory usage.
- How does each algorithm behave under burst traffic?

### Follow-Up 2: Distributed State
> "We're scaling to 10 servers behind a load balancer. How do you maintain an accurate request count across all of them?"

- Centralized store (Redis) vs. gossip protocol vs. eventual consistency.
- What's the latency impact of calling Redis on every request?
- Can you use a **write-behind** pattern (local counter + periodic sync)?

### Follow-Up 3: Redis Failure Resilience
> "Redis goes down. What happens to the rate limiter?"

- **Fail-open** (allow all requests) vs. **fail-closed** (block all requests) — when is each appropriate?
- Implement a fallback strategy (e.g., local in-memory counters with looser limits).
- How do you alert and recover?

### Follow-Up 4: Per-Endpoint Limits
> "Different API endpoints have different cost profiles. A `/search` call is 10x more expensive than a `/health` check. How do you model this?"

- Introduce a **cost-based** rate limiter where each endpoint has a weight.
- How does this change the token bucket implementation?
- Discuss weighted vs. hierarchical rate limiting.
