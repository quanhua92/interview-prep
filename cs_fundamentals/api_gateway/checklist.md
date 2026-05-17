# Design an API Gateway — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] Who are the clients — web, mobile, partner APIs, internal services?
  - [ ] What auth models: session cookies, OAuth2, API keys, mTLS?
  - [ ] What QPS targets and latency SLOs per endpoint?
  - [ ] Which protocols: REST, gRPC, GraphQL, WebSocket?
  - [ ] What rate limiting dimensions: per-IP, per-user, per-API-key, per-tenant?
  - [ ] Do clients need request aggregation or make parallel calls?
  - [ ] What deployment topology: single gateway, per-team, or layered?
- [ ] List functional requirements (3-5 items):
  - [ ] Route requests to backend services by path/host/header
  - [ ] Terminate TLS centrally
  - [ ] Authenticate clients (JWT, OAuth2, API keys, mTLS)
  - [ ] Enforce rate limits per dimension
  - [ ] Emit logs, metrics, and distributed tracing headers
- [ ] List non-functional requirements (latency, availability, scale):
  - [ ] Sub-millisecond routing overhead on hot paths
  - [ ] Multi-AZ, active-active deployment
  - [ ] No SPOF: stateless pods, external HA store for rate limits
  - [ ] Circuit breakers and bulkheads for resilience
- [ ] State your scale estimates:
  - [ ] ~50 microservices behind the gateway
  - [ ] ~100K QPS peak at the gateway layer
  - [ ] ~50 gateway pods needing shared rate limit state
  - [ ] RS256 JWT verification: ~100us-1ms per request

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw a simple box diagram: Client -> CDN/WAF -> [API Gateway] -> [Backend Services] -> [DB/Cache]
- [ ] Identify the main request flows:
  - [ ] Public request: Client -> Gateway -> Route -> Backend (no auth)
  - [ ] Authenticated request: Client -> Gateway -> Validate JWT -> Inject Claims -> Route -> Backend
  - [ ] Rate-limited request: Gateway checks Redis counter -> 429 or pass-through
- [ ] Note where gateway fits vs other layers:
  - [ ] Load balancer: traffic distribution (L4/L7), no business-aware auth
  - [ ] API gateway: superset of L7 LB with auth, rate limiting, transformation
  - [ ] Service mesh: east-west service-to-service (mTLS, retries, observability)
  - [ ] Production: run all three (CDN/WAF -> gateway -> mesh)
- [ ] Present the diagram and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain JWT validation strategy and justify:
  - [ ] Option A: every service validates (redundant, inconsistent)
  - [ ] Option B: gateway validates, claims as headers (production standard)
  - [ ] Option C: gateway validates + mints internal tokens (zero-trust)
  - [ ] State your choice (B for most cases, C for zero-trust)
- [ ] Explain rate limiting algorithm:
  - [ ] Sliding window counter: near-exact, O(1) memory, production default
  - [ ] Distributed via Redis: atomic INCR + EXPIRE, sub-ms latency
  - [ ] At extreme scale: approximate counting with periodic sync
- [ ] Explain aggregation / BFF strategy:
  - [ ] Shared gateway aggregation leads to distributed monolith
  - [ ] BFF per client type: owned by client team, deploys independently
  - [ ] GraphQL as BFF: Apollo Gateway federates schemas across backends
- [ ] Define API contract:
  - [ ] `ANY /api/{service}/*` -> routed to backend service
  - [ ] `GET /api/public/*` -> skip auth
  - [ ] Rate limit headers: `X-RateLimit-Remaining`, `X-RateLimit-Limit`
  - [ ] On 429: `Retry-After: <seconds>` header + JSON body
- [ ] Sketch the route config schema:
  - [ ] Table `routes`: `route_id`, `path_pattern`, `service_host`, `auth_required`, `rate_limit_rpm`, `enabled`
  - [ ] Redis keys: `rl:{user_id}:{endpoint}:{window}` for rate limit counters
- [ ] Walk through the main flow end-to-end:
  - [ ] Request arrives -> TLS termination -> strip client internal headers -> auth validation -> rate limit check -> route to backend -> log/metrics/trace -> return response
  - [ ] On auth failure: 401/403 with clear error
  - [ ] On rate limit exceeded: 429 with Retry-After
  - [ ] On backend failure: circuit breaker opens, return 503

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss distributed rate limiting:
  - [ ] Local counters leak quota: 50 pods x 100 RPM = 5000 RPM actual
  - [ ] Redis atomic counters solve it; Lua scripts for sliding window
  - [ ] Fail-open vs fail-closed when Redis is down (per-endpoint decision)
- [ ] Explain timeout cascade prevention:
  - [ ] Decreasing timeouts inward: client 10s -> gateway 8s -> service 5s -> DB 2s
  - [ ] Connection pool limits per backend to avoid exhausting gateway
- [ ] Handle slow downstream service:
  - [ ] Circuit breaker: open after N failures or error rate threshold
  - [ ] Bulkheads: separate connection pools per backend
  - [ ] Retries: exponential backoff + jitter, only idempotent requests, max 2-3
  - [ ] Hedged requests: send second at P95, return whichever wins
- [ ] Discuss JWT key rotation:
  - [ ] JWKS URI with dynamic fetch and cache (5 min TTL)
  - [ ] On unknown `kid`: refetch before rejecting (with rate limit to prevent DoS)
  - [ ] Overlap rotation windows so old keys valid during grace period
- [ ] Address the distributed monolith trap:
  - [ ] No business logic in gateway config
  - [ ] If it cannot be routing/auth/rate-limit/header-transform, it belongs in a service
  - [ ] BFFs for client-specific aggregation, not the shared gateway
- [ ] Discuss deployment topology:
  - [ ] Single gateway: works up to ~100 services, becomes bottleneck
  - [ ] Layered: edge gateway (TLS, DDoS, coarse auth) + domain gateways
  - [ ] Conway's Law: topology mirrors org structure

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made and why
- [ ] Mention what you would improve with more time
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
