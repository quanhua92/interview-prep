# Design a Rate Limiter

## One-Liner
Protect services from abuse by enforcing request rate quotas per client or endpoint.

## Functional Requirements
- Limit requests per user/IP/API key within a time window
- Return appropriate HTTP status (429 Too Many Requests)
- Support different rate limit rules per endpoint
- Allow configurable rate limit policies
- Provide rate limit metadata in response headers

## Non-Functional Requirements
- Low overhead per request (<5ms added latency)
- Distributed coordination across multiple server instances
- Highly available (fail-open or fail-closed strategy)
- Minimal memory footprint at scale

## Key Scale Questions
- Millions of requests/sec across distributed servers
- Rules: 100 req/min per user, 1000 req/min per IP
- Number of unique clients: millions of API keys + IPs
- Memory per client: varies by algorithm (fixed window: ~64 bytes, sliding log: much more)

## Core Components
- **Rate Limit Middleware**: intercepts requests, checks quota, enforces limits
- **Redis Cluster**: distributed counter/storage for rate limit state
- **Policy Store**: configuration of rate limit rules per endpoint/client tier
- **Rate Limit Service**: centralized evaluation (optional, can be embedded as middleware)
- **Admin Dashboard**: view and configure rate limit policies
- **Metrics Pipeline**: track rate-limited requests, breach events

## Key Design Decisions

### Rate Limiting Algorithm
- **Option A: Fixed Window Counter**: Simple, INCR + EXPIRE in Redis, burst at window boundaries (2x rate possible)
- **Option B: Sliding Window Log**: Precise, uses sorted set per client, high memory per client at high rates
- **Option C: Sliding Window Counter**: Hybrid of A and B, combines current window count + weighted previous window, good balance
- **Option D: Token Bucket**: Smooth rate, allows short bursts, requires atomic Lua script in Redis

### Distributed Coordination
- **Option A: Redis with atomic operations**: Low latency, single point of failure (mitigated by cluster), data loss on failover
- **Option B: Consistent local + periodic sync**: No network overhead per request, eventually consistent, risk of slight over-limiting
- **Option C: Actor model (per-key actor)**: Precise per-key, requires actor framework, harder to deploy

### Failure Strategy
- **Option A: Fail-open**: If Redis is down, allow all requests. Availability over correctness
- **Option B: Fail-closed**: If Redis is down, reject all requests. Correctness over availability
- **Option C: Local fallback**: Use in-memory local counter when Redis unavailable, approximate but available

## API Endpoints
| Method | Path | Description |
|--------|------|-------------|
| GET | /api/v1/check | Check current rate limit status |
| GET | /api/v1/policies | List rate limit policies |
| PUT | /api/v1/policies/{id} | Update a rate limit policy |
| * | * | Rate limit headers on all responses |

## Database Schema
| Column | Type | Notes |
|--------|------|-------|
| policy_id | VARCHAR | PK |
| name | VARCHAR | Policy name |
| limit | INT | Max requests in window |
| window_sec | INT | Time window in seconds |
| scope | VARCHAR | user, ip, api_key |
| endpoint_pattern | VARCHAR | Glob pattern for endpoints |

## Deep Dive Topics
- Redis Lua scripts for atomic rate limit checks (INCR + EXPIRE as atomic operation)
- Sliding window counter math: weighted_count = current_window + (elapsed/window_size * previous_window)
- Handling clock skew in distributed environments
- Rate limit headers: X-RateLimit-Limit, X-RateLimit-Remaining, X-RateLimit-Reset

## Follow-Up Variations
- How would you implement rate limiting without Redis (purely in-memory)?
- How do you handle rate limiting for WebSocket connections (persistent, not request-based)?
- What about adaptive rate limiting based on server load?
- How would you implement a token bucket in a distributed setting?
