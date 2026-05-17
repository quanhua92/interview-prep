# Design an API Gateway

Source: [API Gateway (CalibreOS)](https://www.calibreos.com/learn/hld-api-gateway)

## One-Liner
Centralize cross-cutting concerns (auth, rate limiting, routing, TLS termination) at a single entry point for microservices, while keeping business logic out of the gateway layer.

## Functional Requirements
- Route incoming requests to the correct backend service by path, host, or header
- Terminate TLS and manage certificates centrally
- Authenticate clients: validate JWTs, OAuth2 tokens, API keys, or mTLS client certs
- Enforce rate limits per-IP, per-user, per-API-key, per-tenant, or per-endpoint
- Log access, emit metrics (latency histograms, 5xx rates), and propagate distributed tracing headers
- Transform requests/responses: rewrite paths, inject/strip headers, convert REST to gRPC
- Aggregate responses from multiple backend services (BFF pattern)
- Support API versioning and developer portal for external consumers

## Non-Functional Requirements
- Sub-millisecond routing overhead on hot paths (10K+ QPS)
- High availability: multi-AZ deployment, active-active across regions
- No single point of failure: stateless gateway pods, rate limit state in external HA store
- Graceful degradation: circuit breakers, bulkheads, decreasing timeouts inward
- Latency budget: gateway adds <5ms to p99 for non-aggregation paths

## Key Scale Questions
- 50 microservices behind the gateway, varying QPS per endpoint
- 100K QPS peak at the gateway layer
- Distributed rate limiting across 50+ gateway pods needs shared state (Redis)
- Authentication: RS256 signature verification costs ~100us-1ms per request
- Read:write ratio dominated by reads; gateway must not bottleneck on auth or rate-limit checks
- Multi-protocol backends: REST, gRPC, GraphQL, WebSocket

## Core Components
- **Routing Engine**: declarative path/host/header-to-service mapping, versioned and testable
- **TLS Terminator**: central certificate management, re-encrypt to backends or use mTLS mesh
- **Auth Filter**: validate JWT/OAuth2/API-key/mTLS once, propagate verified claims as internal headers
- **Rate Limiter**: distributed counters (Redis), sliding window counter algorithm, per-dimension quotas
- **Observability Pipeline**: structured access logs, per-route latency histograms, trace header propagation
- **Circuit Breaker**: per-backend error rate thresholds, cooldown windows, bulkhead isolation
- **Request Transformer**: path rewrite, header inject/strip, protocol translation (REST-gRPC)
- **BFF / Aggregation Layer**: client-specific gateways owned by client teams, parallel fan-out to backends

## Key Design Decisions

### Where to Validate JWTs
- **Option A: Every service validates independently.** Redundant CPU cost (~1ms per hop), inconsistent key rotation, duplicated logic across services
- **Option B: Gateway validates once, propagates claims as headers.** Gateway strips client-provided headers, injects verified X-User-Id/X-User-Roles/X-Tenant-Id. Downstream trusts gateway via mTLS mesh or private VPC. Production standard for most systems
- **Option C: Gateway validates + mints short-lived internal tokens.** Zero-trust between services, each hop verifies internal JWT. Used in cross-region or high-security deployments

### Rate Limiting Algorithm
- **Fixed window**: simple but 2x burst at boundaries
- **Sliding window log**: accurate, O(N) memory per user
- **Sliding window counter**: near-exact, O(1) memory, production default
- **Token bucket**: permits controlled bursts, standard for payment/AWS APIs
- **Leaky bucket**: constant outflow, good for traffic shaping

### Request Aggregation Strategy
- **Option A: Client makes parallel calls.** Simple backend, complex client, isolated failures
- **Option B: Shared gateway aggregates.** Gateway becomes distributed monolith with business logic
- **Option C: BFF per client type.** Each BFF owned by its client team, deploys independently, scales organizationally. Preferred approach

### Deployment Topology
- **Single shared gateway**: simple, works up to ~100 services and a few teams, becomes political bottleneck
- **Gateway per team/domain**: decentralized, faster teams, duplicated cross-cutting config
- **Layered (edge + domain gateways)**: thin edge for TLS/DDoS/coarse auth, domain gateways for business-specific concerns. Netflix/Amazon pattern, industry default at scale
- **BFF variant**: edge gateway + per-client BFFs calling shared backends. Standard for consumer-facing systems

## API Endpoints
| Method | Path | Description |
|--------|------|-------------|
| ANY | /api/{service}/* | Route to backend service by path prefix |
| GET | /health | Gateway health check |
| GET | /api/public/* | Public endpoints that skip auth |
| GET | /api/rate-limit-status | Return X-RateLimit-Remaining and X-RateLimit-Limit headers |

## Database Schema
| Column | Type | Notes |
|--------|------|-------|
| route_id | VARCHAR | PK, route identifier |
| path_pattern | VARCHAR | e.g. /api/products/* |
| service_host | VARCHAR | Backend service host:port |
| auth_required | BOOLEAN | Skip auth for public routes |
| rate_limit_rpm | INT | Per-route rate limit |
| enabled | BOOLEAN | Toggle route without deletion |

Rate limit counters stored in Redis: key = `rl:{user_id}:{endpoint}:{window}`, value = count, TTL = window duration.

## Deep Dive Topics
- Gateway vs Load Balancer vs Service Mesh: LB does traffic distribution, gateway adds application-aware features (auth, rate limiting, transformation), mesh handles east-west service-to-service (mTLS, retries, observability). Envoy deploys as all three with different configs
- Distributed rate limiting: local counters leak quota across pods (50 pods = 50x over-quota). Redis atomic INCR+EXPIRE solves this; at extreme scale, approximate counting with periodic sync reduces central store load
- The distributed monolith trap: teams start adding business logic to the gateway config. Guardrail: only infrastructure concerns belong in the gateway. Anything product-specific goes in a BFF or downstream service
- Cascading timeout prevention: set decreasing timeouts inward (client 10s, gateway 8s, service 5s, DB 2s) so inner layers fail fast
- JWT key rotation: gateway must refetch JWKS on unknown `kid` before rejecting; overlap rotation windows so old keys stay valid during grace period
- Header stripping: gateway must strip any client-provided internal headers (X-User-Id etc.) before injecting verified versions. Forgetting this is the most common gateway security bug
- Handling slow backends: timeouts + circuit breakers + bulkheads + hedged requests (send second request at P95, return whichever wins)

## Follow-Up Variations
- How would you handle WebSocket long-lived connections through the gateway?
- What happens when Redis (rate limit store) goes down — fail open or fail closed?
- How do you version APIs at the gateway without breaking existing clients?
- A team wants to bypass the gateway for internal service calls. What do you say?
- How would you implement a developer portal with self-service API key provisioning?
- What changes when you need to support GraphQL federation across multiple backend teams?
