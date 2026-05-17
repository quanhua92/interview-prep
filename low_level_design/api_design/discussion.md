# API Design Principles

Source: [API Design Principles (CalibreOS)](https://www.calibreos.com/learn/lld-api-design-principles)

## One-Liner
Design APIs as stable service contracts using REST resource modeling, idempotency keys, versioning strategies, and error contracts that let independent teams evolve without breaking each other.

## Why API Design Is an LLD Topic
- API design lives at the intersection of LLD and systems thinking
- It is not just "write REST endpoints" -- it is modeling your domain as a service contract that multiple teams or systems will depend on for years
- A poorly designed API is harder to change than poorly structured internal code, because clients depend on it
- The three laws of API design define why this is hard: once an API is published, you effectively promise never to break clients even in ways you did not document

### The Three Laws
- **Hyrum's Law:** "With a sufficient number of users of an API, it does not matter what you promise in the contract: all observable behaviors of your system will be depended on by somebody." This is why you cannot remove fields, change error codes, or alter response structure without breaking someone.
- **Postel's Law:** Be conservative in what you send, liberal in what you accept.
- **Principle of Least Astonishment:** Every naming choice, every field, every error code is a permanent commitment.

## What Earns Each Level

### 6/10
- Knows HTTP methods and status codes
- Designs basic CRUD endpoints
- Knows GET is idempotent

### 8/10
- Designs idempotent PUT and DELETE
- Implements idempotency keys for non-idempotent POST (payment, order)
- Versions APIs correctly (URI versioning vs header)
- Designs a complete error response schema with error codes, messages, and request IDs

### 10/10
- Applies Hyrum's Law when designing (build only what you commit to)
- Designs for backward compatibility from day one (required fields must have defaults, never remove fields)
- Explains consumer-driven contract testing
- Designs the full API surface: pagination (cursor vs offset), rate limiting headers, partial update (PATCH vs PUT), and idempotency key mechanics with deduplication window

## The API Design Checklist

### 01: REST Resource Modeling -- Nouns, Not Verbs
- Resources should be nouns: `/orders`, `/users`, `/products`
- Actions are expressed via HTTP methods: GET (read), POST (create), PUT (replace), PATCH (partial update), DELETE (remove)
- Anti-pattern: `/createOrder`, `/getUser`, `/deleteProduct` (verbs in URLs)
- Exception: complex operations that do not map to CRUD (e.g., `/orders/{id}/cancel`), use POST to a sub-resource action noun

### 02: Idempotency -- Design for Safe Retries
- GET, PUT, DELETE are inherently idempotent (calling them N times has the same effect as calling once)
- POST creates a new resource, not inherently idempotent (two POSTs create two orders)
- For idempotency on POST: require clients to supply an `Idempotency-Key` header (UUID)
- Store `(idempotency_key, response)` on first call
- On duplicate request: return stored response without processing
- Deduplication window: 24 hours typical
- This enables clients to safely retry on network failure

### 03: Versioning -- Plan Before You Ship v1
Three strategies:
- **URI versioning:** `/v1/users`, `/v2/users` -- most visible, easiest to route, cached independently
- **Header versioning:** `Accept: application/vnd.api+json;version=2` -- cleaner URIs, harder to curl/debug
- **Query param:** `/users?version=2` -- simplest but easily omitted
- URI versioning is the most practical
- Rule: v1 is forever. Do not break v1 when shipping v2, maintain in parallel until v1 deprecation window (6-24 months) passes

### 04: Error Contracts -- Every Error Has a Contract
- Standard error response:
  ```json
  {
    "error_code": "ORDER_NOT_FOUND",
    "message": "Order abc123 does not exist.",
    "request_id": "req_xyz789",
    "timestamp": "2024-01-15T10:23:45Z",
    "details": {}
  }
  ```
- `error_code` is machine-readable (clients can switch on it)
- `message` is human-readable (developers can read it in logs)
- `request_id` links to distributed traces
- HTTP status code aligns: 404 for `ORDER_NOT_FOUND`, 422 for validation errors, 429 for rate limit exceeded, 503 for dependency unavailable

### 05: Backward Compatibility -- Never Break Clients
- **Safe changes (backward compatible):** add new optional fields, add new endpoints, add new enum values (clients must handle unknown values), relax validation
- **Breaking changes:** remove or rename fields, change field types, change error codes, remove enum values, make optional fields required
- **Strategy:** deprecate first (add `Deprecation` header), run deprecated version for 6+ months, remove only after all clients have migrated
- Additive-only changes to the data contract

## Key Design Decisions

### Idempotency Key Flow: Safe Payment Retry
1. Client sends `POST /payments` with `Idempotency-Key: <uuid>` header
2. Server checks idempotency store (e.g., Redis)
3. If key exists: return stored response, skip processing
4. If key is new: execute operation, store `(key, response)` with 24h TTL
5. Client can safely retry on network failure -- same key always returns same result

### Pagination: Cursor vs Offset
- Cursor-based pagination should be preferred over offset pagination for mutable datasets
- Cursor encodes the last seen row's sort key (Base64-encoded `{"id": 123}`)
- Stable under concurrent inserts; offset pagination shows duplicates/skips when rows are inserted between pages
- Cursor pagination is O(1) per page; offset is O(offset) per page
- Always add a tiebreaker: `ORDER BY created_at DESC, id DESC`

**Cursor Pagination Response Template:**
```
GET /orders?cursor=eyJpZCI6MTIzfQ==&limit=20

{
  "orders": [...],
  "pagination": {
    "next_cursor": "eyJpZCI6MTQzfQ==",
    "has_more": true,
    "total_count": null
  }
}
```

### Rate Limit Error Contract (HTTP 429)
```
HTTP/1.1 429 Too Many Requests
X-RateLimit-Limit: 1000
X-RateLimit-Remaining: 0
X-RateLimit-Reset: 1705334625
Retry-After: 60
Content-Type: application/json

{
  "error_code": "RATE_LIMIT_EXCEEDED",
  "message": "Rate limit of 1000 requests per minute exceeded.",
  "request_id": "req_abc123"
}
```

### PUT vs PATCH
- PUT replaces the full resource representation
- PATCH updates only supplied fields
- For explicit operation semantics, use JSON Patch (RFC 6902)

```
// PUT replaces the full resource
PUT /users/123
{"name": "Alice", "email": "alice@example.com", "role": "admin"}

// PATCH updates only supplied fields
PATCH /users/123
{"email": "alice@newdomain.com"}

// JSON Patch (RFC 6902)
PATCH /users/123
[{"op": "replace", "path": "/email", "value": "alice@newdomain.com"}]
```

## HTTP Method Semantics and Properties

| Method | Idempotent? | Safe? | Typical use | Response code |
|--------|-------------|-------|-------------|---------------|
| GET | Yes | Yes (no side effects) | Read resource or collection | 200 OK, 404 Not Found |
| POST | No | No | Create resource, trigger action | 201 Created, 202 Accepted (async) |
| PUT | Yes | No | Replace entire resource | 200 OK, 204 No Content |
| PATCH | Not guaranteed | No | Partial update of resource | 200 OK, 204 No Content |
| DELETE | Yes | No | Remove resource (2nd DELETE = 404, same outcome) | 204 No Content, 404 if already deleted |
| HEAD | Yes | Yes | Same as GET but no body (check existence, headers) | 200 or 404 |
| OPTIONS | Yes | Yes | Discover allowed methods, CORS preflight | 200 with Allow header |

## Idempotency Key Implementation and RFC 7807 Error Contract

```python
import json
from enum import Enum
from typing import Any, Callable

# Idempotency: safe payment retry, server stores result keyed on client token
class IdempotencyStore:
    """Redis-backed store. Key TTL: 24h (per Stripe's convention)."""
    def __init__(self, redis_client):
        self._redis = redis_client

    def get_or_execute(self, key: str, operation: Callable, ttl: int = 86400) -> Any:
        cached = self._redis.get(f"idem:{key}")
        if cached:
            return json.loads(cached)  # return stored result, skip side effect
        result = operation()
        self._redis.setex(f"idem:{key}", ttl, json.dumps(result))
        return result

# RFC 7807 Problem Details, machine-readable error codes, not string messages
class ErrorCode(Enum):
    VALIDATION_FAILED = "VALIDATION_FAILED"
    RESOURCE_NOT_FOUND = "RESOURCE_NOT_FOUND"
    PAYMENT_DECLINED = "PAYMENT_DECLINED"
    RATE_LIMIT_EXCEEDED = "RATE_LIMIT_EXCEEDED"

_HTTP_STATUS = {
    ErrorCode.VALIDATION_FAILED: 400,
    ErrorCode.RESOURCE_NOT_FOUND: 404,
    ErrorCode.PAYMENT_DECLINED: 422,
    ErrorCode.RATE_LIMIT_EXCEEDED: 429,
}

def make_error(code: ErrorCode, detail: str, instance: str) -> dict:
    """Clients key on `type` URI, not `message` string, survives translation."""
    return {
        "type": f"https://api.example.com/errors/{code.value.lower()}",
        "title": code.value.replace("_", " ").title(),
        "status": _HTTP_STATUS[code],
        "detail": detail,
        "instance": instance,
    }

# Usage: POST /v1/payments with Idempotency-Key header
# idem_store.get_or_execute(request.headers["Idempotency-Key"], lambda: charge(...))
```

## Common API Design Mistakes

1. **Chatty APIs.** Client makes 10 API calls to render one screen. Fix: composite endpoints that return all data needed for a screen in one request. Or GraphQL for flexible client-driven queries.

2. **Returning internal IDs directly.** Exposing auto-increment database IDs (`/users/42`) reveals row count and enables enumeration attacks. Prefer UUIDs (`/users/usr_f47ac10b-58cc-4372-a567`). UUIDs also enable database migration without changing external IDs.

3. **Missing idempotency on writes.** A mobile app retries a failed payment results in double charge. Any mutating operation that is exposed to unreliable networks (mobile, microservices) needs idempotency.

4. **Unstable sort order in paginated results.** Paginating by `ORDER BY created_at` fails when multiple records have the same timestamp (ties are broken non-deterministically). Always add a tiebreaker: `ORDER BY created_at DESC, id DESC`. Cursor-based pagination requires a stable, unique sort key.

5. **Returning 200 for errors.** `{"status": "error", "code": 404}` with HTTP 200. Clients cannot use standard HTTP error handling, monitoring tools miss errors, and retry logic breaks. Use proper HTTP status codes.

6. **Adding required fields to existing endpoints.** Making a previously optional field required in PUT is a breaking change. Existing clients without that field will suddenly fail. Deprecate the old shape, add the new required field as optional first, then make it required only in v2.

## API Principles as Violation-Fix Pairs

- **Resource modeling violation:** `/createOrder`, `/cancelOrder`, and `/getOrdersForUser` expose verbs and implementation thinking. Fix: model nouns and sub-resources: `POST /orders`, `POST /orders/{id}/cancellations`, `GET /users/{id}/orders`.

- **Idempotency violation:** a mobile client retries `POST /payments` after a timeout and the server charges twice. Fix: require `Idempotency-Key`, persist the first response by key and request fingerprint, and return the stored response for duplicate retries. If the same key arrives with a different body, return `409 Conflict` or `422 Unprocessable Entity`; do not silently treat it as the same operation.

- **Compatibility violation:** adding a required request field to v1 breaks old clients overnight. Fix: additive-only evolution in a published version: new response fields are optional, new request fields have defaults, enum consumers must handle unknown values, and breaking changes ship under `/v2`.

- **Error-contract violation:** returning HTTP 200 with `{status: "error"}` destroys retries, monitoring, and client control flow. Fix: use status codes plus a stable machine-readable `error_code`, human message, `request_id`, and details object. The principle is simple: clients should never parse prose to decide what to do next.

## Design APIs Around Retries, Drift, and Ownership

- APIs fail in production because clients retry, schemas drift, and teams assume ownership boundaries differently. A strong LLD API answer designs for those realities from the first endpoint.
- For every mutating call, ask: "Can the client safely retry if the socket dies after the server commits?" If not, add idempotency or make the operation naturally idempotent with `PUT` to a client-chosen resource ID.
- For every response field, ask: "Am I willing to support this observable behavior for years?" Hyrum's Law means clients will depend on sort order, nullability, field presence, error codes, and pagination shape even if the docs are vague. That is why minimal responses are often better than dumping ORM objects.
- For every endpoint, define ownership. `POST /orders/{id}/cancel` sounds convenient but can hide business rules: paid orders may require refund workflow, shipped orders may require return workflow. Modeling `POST /orders/{id}/cancellations` gives the action its own resource and state: requested, accepted, rejected, completed.
- The interview signal is to connect API shape to evolvability: stable IDs, cursor pagination, idempotency keys, explicit errors, and versioning are not REST trivia; they are tools that let independent teams deploy without breaking each other.

## Interview Delivery Summary

- When asked to "design the API" for a system: first model the resources (nouns), then define the methods per resource (CRUD + action sub-resources for complex operations).
- Address idempotency on POST endpoints explicitly: "For the payment endpoint, I would require an `Idempotency-Key` header, the server stores the result keyed on this, so retries are safe."
- Version from day one: "I would version the API as `/v1/` from the start, even if there is no v2 yet, it costs nothing now and saves a painful migration later."
- Staff signal: bring up Hyrum's Law: "Once we expose a field, clients will depend on it. We should only include what we are committing to maintain. I would start with a minimal surface and expand rather than expose everything and try to remove later."

## Follow-Up Variations
- How do you handle a payment API call that fails and the client does not know if the payment was processed?
- Design the REST API for an order management system (place order, get order, cancel order, list user's orders).
- How would you version an API that serves both mobile and web clients with different release cycles?
- What happens when you need to remove a field that clients depend on?
- How do you design pagination for a feed that receives new items in real-time?
