# API Design Principles -- Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] What resources does the system expose? (orders, users, payments, etc.)
  - [ ] What operations do clients need? (CRUD, complex workflows like cancel/refund)
  - [ ] Are there reliability requirements? (idempotent payments, safe retries on mobile)
  - [ ] Who are the API consumers? (internal microservices, mobile clients, third-party)
- [ ] List functional requirements (3-5 items):
  - [ ] Clients can create, read, update, and delete resources
  - [ ] Mutating operations must be safely retryable (idempotency)
  - [ ] Collections must support pagination (cursor-based)
  - [ ] Errors must return machine-readable codes with request IDs
  - [ ] API must be versioned to support backward-compatible evolution
- [ ] List non-functional requirements:
  - [ ] Backward compatibility: never break existing clients
  - [ ] Idempotency: every write operation safe to retry
  - [ ] Observability: request IDs for distributed tracing
  - [ ] Rate limiting: protect the API from abuse
- [ ] State the guiding laws:
  - [ ] Hyrum's Law: all observable behaviors will be depended on
  - [ ] Postel's Law: conservative in what you send, liberal in what you accept
  - [ ] Principle of Least Astonishment: no surprises in API behavior

## Phase 2: High-Level Design (3-5 min)
- [ ] Model resources as nouns (not verbs): `/orders`, `/users`, `/payments`
- [ ] Identify the main operations and their access patterns:
  - [ ] `POST /orders` -- create an order (write, needs idempotency key)
  - [ ] `GET /orders/{id}` -- get a single order (read, idempotent)
  - [ ] `GET /orders?cursor=xxx&limit=20` -- list orders (read, paginated)
  - [ ] `PUT /orders/{id}` -- replace entire order (write, idempotent)
  - [ ] `PATCH /orders/{id}` -- partial update (write, not guaranteed idempotent)
  - [ ] `DELETE /orders/{id}` -- remove order (write, idempotent)
  - [ ] `POST /orders/{id}/cancellations` -- cancel order (complex action as sub-resource)
- [ ] Note HTTP method properties:
  - [ ] GET, PUT, DELETE are idempotent
  - [ ] POST is not idempotent (needs idempotency key)
  - [ ] PATCH is not guaranteed idempotent
- [ ] Present the resource model and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Define idempotency key strategy for POST endpoints:
  - [ ] Client sends `Idempotency-Key: <uuid>` header
  - [ ] Server stores `(key, response)` on first call (Redis, 24h TTL)
  - [ ] On duplicate: return stored response, skip processing
  - [ ] On key collision with different body: return 409 Conflict
  - [ ] Enables safe retries on unreliable networks (mobile, microservices)
- [ ] Define API versioning strategy:
  - [ ] URI versioning: `/v1/orders` (most practical, easiest to route)
  - [ ] Header versioning: `Accept: application/vnd.api+json;version=2` (cleaner URIs)
  - [ ] Query param: `/orders?version=2` (simplest but easily omitted)
  - [ ] Rule: v1 is forever, maintain in parallel until deprecation window passes
- [ ] Define error contract (RFC 7807 Problem Details):
  - [ ] `error_code`: machine-readable (clients switch on it)
  - [ ] `message`: human-readable (for logs and debugging)
  - [ ] `request_id`: links to distributed traces
  - [ ] `timestamp`: when the error occurred
  - [ ] `details`: additional context (validation errors, etc.)
  - [ ] HTTP status code aligns: 404, 422, 429, 503, etc.
- [ ] Define pagination strategy:
  - [ ] Cursor-based: encode last seen sort key as Base64 cursor
  - [ ] Stable under concurrent inserts (no duplicates/skips)
  - [ ] O(1) per page vs O(offset) for offset pagination
  - [ ] Always add tiebreaker: `ORDER BY created_at DESC, id DESC`
- [ ] Walk through the main flow end-to-end:
  - [ ] Create order: client sends POST with Idempotency-Key -> server checks store -> processes or returns cached result
  - [ ] List orders: client sends GET with cursor -> server reads from DB using cursor -> returns page with next_cursor
  - [ ] Cancel order: client sends POST to /orders/{id}/cancellations -> server validates business rules -> returns cancellation resource

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss backward compatibility rules:
  - [ ] Safe changes: add optional fields, add endpoints, add enum values, relax validation
  - [ ] Breaking changes: remove/rename fields, change types, change error codes, make optional required
  - [ ] Strategy: deprecate first, run both versions 6+ months, then remove
- [ ] Explain PUT vs PATCH semantics:
  - [ ] PUT replaces the full resource (client must send all fields)
  - [ ] PATCH updates only supplied fields
  - [ ] JSON Patch (RFC 6902) for explicit operation semantics
- [ ] Address rate limiting:
  - [ ] Return `X-RateLimit-Limit`, `X-RateLimit-Remaining`, `X-RateLimit-Reset` headers
  - [ ] Return `Retry-After` header on 429
  - [ ] Include machine-readable `error_code: RATE_LIMIT_EXCEEDED`
- [ ] Handle common mistakes:
  - [ ] Use UUIDs not auto-increment IDs (prevent enumeration, enable DB migration)
  - [ ] Never return 200 for errors (breaks monitoring, retries, client control flow)
  - [ ] Never make optional fields required in existing versions (breaking change)
  - [ ] Avoid chatty APIs (composite endpoints or GraphQL)
- [ ] Discuss ownership modeling:
  - [ ] `POST /orders/{id}/cancel` hides business rules
  - [ ] `POST /orders/{id}/cancellations` gives the action its own resource and state
  - [ ] States: requested, accepted, rejected, completed

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the API design in 2-3 sentences
- [ ] State the trade-offs you made and why (e.g., URI versioning vs header versioning)
- [ ] Mention Hyrum's Law: minimal API surface is better than exposing everything
- [ ] Mention what you would improve with more time (OpenAPI spec, consumer-driven contract tests)
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
