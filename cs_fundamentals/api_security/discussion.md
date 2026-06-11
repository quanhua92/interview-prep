# API Security

Sources:
- [OWASP API Security Top 10 (2023)](https://owasp.org/API-Security/editions/2023/en/0x11-t10/)
- [OWASP Top 10 Web Application Security Risks (2025)](https://owasp.org/www-project-top-10/)
- [API Security Risks: The 10 Most Exploited in 2026 (CybelAngel)](https://cybelangel.com/blog/api-security-risks/)
- [LiteLLM Proxy - LLM Gateway](https://docs.litellm.ai/docs/proxy/quick_start)
- [CVE-2026-42208: LiteLLM SQL Injection and the AI Gateway Credential Problem (Penligent)](https://www.penligent.ai/hackinglabs/cve-2026-42208-litellm-sql-injection-and-the-ai-gateway-credential-problem/)
- [OWASP Top 10 LLM Security Risks (2025)](https://genai.owasp.org/llm-top-10/)
- [Best LLM Gateways in 2025 (Pomerium)](https://www.pomerium.com/blog/best-llm-gateways-in-2025)
- [OWASP API Security: Top 10 Security Risks & Remedies for 2026 (Axway)](https://blog.axway.com/learning-center/digital-security/risk-management/owasps-api-security)

## One-Liner
Securing APIs requires defense-in-depth across authentication, authorization, input validation, rate limiting, transport security, and secrets management -- with special considerations for LLM API backends where API key exposure, prompt injection via API abuse, and unbounded token consumption are first-class threats.

## Core Competencies Table

| Area | Description | Proficiency Expectation |
|------|-------------|------------------------|
| API Authentication | API keys (static, rotating), OAuth2 flows (authorization code, client credentials, PKCE), JWT structure/validation/rotation, session cookies, mTLS | Walk through any OAuth2 flow end-to-end; explain JWT validation steps and common attacks (alg confusion, missing aud); compare auth mechanisms for different client types |
| API Authorization | RBAC vs ABAC, scopes/permissions, principle of least privilege, service-to-service auth, BOLA prevention | Design authorization for a multi-tenant API; explain why BOLA is the #1 API risk and how to prevent it; compare RBAC/ABAC for different architectures |
| LLM-Specific API Security | API key management for OpenAI/Anthropic/Gemini, credential rotation without deployment, proxy patterns (LiteLLM, Portkey), gateway security | Design a secure LLM API proxy architecture; explain CVE-2026-42208 and why LLM gateways are high-value targets; implement key rotation without redeployment |
| Rate Limiting | Token bucket, sliding window, fixed window, per-user/per-key/per-IP, distributed rate limiting (Redis), 429 handling | Choose the right algorithm for a given scenario; implement distributed rate limiting with Redis; explain how rate limiting mitigates LLM10 (unbounded consumption) |
| Input Validation & Sanitization | Schema validation (Pydantic, JSON Schema), input size limits, content-type enforcement, SQL/NoSQL injection prevention | Design validation middleware for a REST API; explain why schema validation prevents mass assignment; compare Pydantic vs JSON Schema approaches |
| Transport Security | TLS/HTTPS, certificate management, HSTS, certificate pinning, TLS version requirements | Explain TLS 1.3 handshake; design certificate rotation strategy; explain why certificate pinning matters for mobile APIs |
| OWASP API Security Top 10 | All 10 API-specific risks with mitigations relevant to AI/LLM backends | Walk through all 10 risks; identify the 3 most critical for a given system; explain how each maps to LLM-specific threats |
| CORS & CSRF | Cross-origin policies, preflight requests, same-site cookies, CSRF tokens | Configure CORS for a SPA + API backend; explain why CORS is not a security feature; design CSRF defense for cookie-based auth |
| Security Headers | Content-Security-Policy, X-Frame-Options, X-Content-Type-Options, Strict-Transport-Security | Design security header strategy for a production API; explain what each header prevents |
| Secrets Management | Environment variables, secret managers (AWS Secrets Manager, Vault), secret rotation, CI/CD secrets | Design a secrets management architecture; explain why env vars are not sufficient for production; implement secret rotation with zero downtime |

## 1. API Authentication

### API Keys

| Type | Use Case | Security Profile |
|------|----------|-----------------|
| **Static API key** | Simple internal services, low-risk integrations | Weak: single shared secret, no expiry, leaked = full access until manual rotation. Adequate for read-only public data APIs only |
| **Rotating API key** | Production services, third-party integrations | Better: periodic rotation (weekly/monthly). Requires coordination with consumers. Still no granular permissions or user association |
| **Scoped API key** | Multi-tenant SaaS, per-customer access | Good: key encodes permissions/scope. Can be revoked individually. OpenAI uses this pattern (project-scoped keys) |

**Storage**: API keys MUST NOT be in source code, git history, or client-side JavaScript. Store in secret managers (AWS Secrets Manager, HashiCorp Vault, GCP Secret Manager) or environment variables injected at runtime (not in `.env` files committed to VCS).

### OAuth 2.0 Flows

| Flow | Client Type | Use Case | Security |
|------|------------|----------|----------|
| **Authorization Code + PKCE** | Web app, SPA, mobile | User-facing apps that need delegated access | Strongest: code exchange via backend, PKCE binds code to client, no token in URL fragment |
| **Client Credentials** | Server-to-server | Cron jobs, backend services, no user involved | Service authenticates directly with client_id + client_secret. Secret lives in Vault/KMS |
| **Device Code** | TV, CLI, IoT | Limited input devices | User approves on second device while first device polls. No secret on the device |
| **Implicit** | -- | DEPRECATED. Token in URL fragment, vulnerable to token leakage | Never propose this |
| **ROPC** | -- | DEPRECATED by OAuth 2.1. Password sent directly to client | Only for legacy migration |

**Authorization Code + PKCE Flow (step by step)**:
1. Client generates `code_verifier` (random 43-128 char string) and `code_challenge` (SHA256 of verifier, base64url encoded)
2. Client redirects user to authorization server with `client_id`, `redirect_uri`, `scope`, `code_challenge`, `code_challenge_method=S256`
3. User authenticates and grants consent
4. Authorization server redirects back with `authorization_code`
5. Client exchanges code for tokens (POST to token endpoint), sending `code_verifier` to prove it initiated the flow
6. Server verifies `code_challenge == SHA256(code_verifier)`, returns `access_token` + `refresh_token`

### JWT (JSON Web Token)

**Structure**: `header.payload.signature` (three base64url-encoded segments)

```
Header:  {"alg": "RS256", "typ": "JWT", "kid": "key-2026-01"}
Payload: {"sub": "user:123", "iss": "auth.myapp.com", "aud": "api.myapp.com",
           "exp": 1749686400, "iat": 1749685500, "scope": "read:documents write:documents",
           "roles": ["editor"]}
Signature: RSASHA256(base64url(header) + "." + base64url(payload), private_key)
```

**Required validation steps** (on EVERY request):
1. Verify signature using public key (from JWK set, matched by `kid`)
2. Check `exp` -- token is expired
3. Check `iss` -- token was not issued by a trusted issuer
4. Check `aud` -- token is not intended for a different service (confused deputy attack)
5. Check `nbf` (not before) -- token is not being used prematurely
6. Hardcode accepted algorithms: `algorithms=["RS256"]` -- never trust the `alg` header (algorithm confusion attack, CVE-2016-10555)

**Common attacks**:
- **Algorithm confusion**: Attacker sets `alg: HS256` and uses the RSA public key as the HMAC shared secret. The verifier, using the public key for HMAC, produces a valid signature. Mitigation: hardcode accepted algorithms
- **Missing `aud` validation**: Token issued for service A is replayed at service B. Mitigation: always validate `aud` against expected audience
- **`jti` replay**: Token replay within TTL window. Mitigation: short TTL + `jti` seen-set for high-value operations
- **Token in URL**: Leaked via browser history, logs, Referer headers. Never put JWTs in URLs

**Key rotation strategy**:
- Store signing keys in HSM/KMS
- Publish multiple keys in JWK set at `/.well-known/jwks.json`
- New tokens signed with new key (identified by `kid`)
- Old key remains valid for verification until `max_token_lifetime + grace_period` (typically 24h)
- Remove old key from JWK set after grace period
- Verifiers cache JWK set with 15-min TTL; refetch on unknown `kid` before rejecting

### mTLS (Mutual TLS)

Both client and server present X.509 certificates. The server verifies the client certificate before accepting any request.

- **Use case**: Service-to-service communication in zero-trust architectures, financial APIs (Open Banking), internal microservice mesh
- **Flow**: TLS handshake + client certificate verification. Server checks client cert against a CA or allows list
- **Advantage**: No API keys or tokens to leak. Cryptographic identity bound to the service
- **Disadvantage**: Certificate management complexity (issuance, rotation, revocation via CRL/OCSP). Not suitable for public-facing APIs (no browser/most mobile clients support mTLS)
- **Production pattern**: Service mesh (Istio, Linkerd) handles mTLS transparently. Envoy sidecars terminate and re-establish TLS with client certs

### Session Cookies vs JWTs for APIs

| Aspect | Session Cookie | JWT Bearer Token |
|--------|---------------|-----------------|
| State | Server-side (Redis, DB) | Stateless (self-contained) |
| Revocation | Instant (delete session) | Hard (short TTL + blocklist) |
| Scaling | Needs shared store | No coordination needed |
| CSRF risk | Yes (cookie sent automatically) | No (sent in Authorization header) |
| XSS risk | Lower (httpOnly cookie) | Higher (localStorage accessible to JS) |
| Best for | Monoliths, traditional web apps | Microservices, SPAs, mobile |

### Service-to-Service Authentication

| Method | Description | Use Case |
|--------|-------------|----------|
| **mTLS** | Mutual certificate authentication | Zero-trust microservice mesh |
| **JWT (service tokens)** | Short-lived JWT with `sub: service:payments` | Microservices behind API gateway |
| **Client Credentials (OAuth2)** | Service authenticates with client_id/secret, gets access token | Backend services calling external APIs |
| **API keys** | Static or rotating keys | Simple internal integrations |
| **gRPC metadata** | Auth token in gRPC metadata headers | gRPC-based microservices |

## 2. API Authorization

### RBAC (Role-Based Access Control)

User → Role → Permissions. Three tables: `(user, role)`, `(role, permission)`.

```
users: user_id, email, ...
user_roles: user_id, role_id
roles: role_id, role_name
role_permissions: role_id, permission_id
permissions: permission_id, action, resource
```

- **O(1) lookup**: Join user → role → permission
- **Simple, auditable**: Easy to reason about who can do what
- **Breaks when**: Permissions depend on resource ownership or sharing. "Alice can edit her own documents but only view Bob's" requires per-resource checks beyond RBAC

### ABAC (Attribute-Based Access Control)

Policy engine evaluates rules over user, resource, and environment attributes.

```python
# Example OPA policy
allow {
    input.user.role == "editor"
    input.resource.owner == input.user.id
    input.action == "write"
    not input.environment.maintenance_mode
}
```

- **Flexible**: Rules based on any combination of attributes
- **Compliance-driven**: Time-of-day, IP range, device posture
- **Implementation**: Open Policy Agent (OPA), AWS IAM policies, Cedar (Amazon), Casbin
- **Cost**: Rule evaluation overhead per request

### BOLA Prevention (Broken Object-Level Authorization)

**API1:2023 -- the #1 API security risk.** An attacker modifies an object ID in the API request to access another user's resources.

```
GET /api/documents/1234  → attacker changes to /api/documents/5678
→ accesses another user's document if server doesn't check ownership
```

**Prevention**:
1. ALWAYS check `resource.owner == current_user` on every data access operation
2. Never rely on sequential or guessable IDs alone (use UUIDs, but still check ownership)
3. Centralize authorization in middleware, not scattered in endpoint handlers
4. Write automated tests: "User A cannot access User B's resource via ID manipulation"
5. Log and alert on authorization failures (repeated attempts = likely probing)

### Principle of Least Privilege

Every API client, service, and token should have the minimum permissions necessary for its function.

- **Scopes**: OAuth2 scopes grant granular permissions (`read:documents`, `write:documents`, `admin:users`)
- **Per-endpoint permissions**: Not all authenticated users should access all endpoints
- **Service accounts**: A cron job should not have admin permissions
- **API key scoping**: LLM API keys should be scoped to specific models and rate limits

## 3. LLM-Specific API Security

### The LLM API Key Problem

AI Engineer backends call multiple LLM providers (OpenAI, Anthropic, Gemini, Mistral). Each provider issues API keys that:
- Have no user-scoping (anyone with the key can use the full quota)
- Can incur unlimited financial cost if leaked
- Cannot be revoked without redeployment (if hardcoded)
- Are often found in git history, CI logs, client-side code

**Real-world breaches**:
- OpenAI customer data breach via Mixpanel vendor hack (November 2025) -- analytics dataset exported
- CVE-2026-42208: Pre-auth SQL injection in LiteLLM Proxy exposed AI gateway credentials
- Stripe API hijacking for card skimming (ongoing since August 2024)

### API Key Management Patterns

| Pattern | Description | Pros | Cons |
|---------|-------------|------|------|
| **Environment variable** | `OPENAI_API_KEY` injected at runtime | Simple, standard | Leaked in process listings, error logs, requires deployment to rotate |
| **Secret manager** | AWS Secrets Manager, Vault, GCP Secret Manager | Rotation without deployment, access logging, audit trail | Latency on first fetch, requires IAM setup |
| **LLM Gateway/Proxy** | LiteLLM, Portkey, Helicone, Kong AI Gateway | Single point of key management, usage tracking, per-request routing, cost controls | Single point of failure, gateway itself is high-value target (CVE-2026-42208), added latency |

### LLM Gateway Architecture

```
Application → LLM Gateway (LiteLLM / Portkey / self-built)
  → OpenAI (key stored in gateway vault)
  → Anthropic (key stored in gateway vault)
  → Gemini (key stored in gateway vault)

Benefits:
- Application never touches provider keys
- Gateway handles key rotation, failover, rate limiting
- Per-team/per-model quotas and cost controls
- Request logging and observability
- Model routing (A/B testing, fallback)

Risks:
- Gateway is a critical dependency (availability)
- Gateway is a high-value target (stores all keys)
- Must be secured with same rigor as the secrets it protects
```

**Securing the LLM gateway itself**:
1. mTLS between application and gateway
2. Service account authentication (not API keys for gateway access)
3. Gateway deployed in private VPC, no public ingress
4. Input validation at gateway level (reject oversized prompts, suspicious content)
5. Rate limiting per consumer (mitigates LLM10: Unbounded Consumption)
6. Regular security audits of the gateway itself (CVE-2026-42208 showed gateways can be SQL-injected)

### Credential Rotation Without Deployment

```
1. Key stored in AWS Secrets Manager with auto-rotation (30-day schedule)
2. Application reads key via SDK on startup and caches in memory
3. Secrets Manager triggers rotation: creates new key version
4. Application polls or subscribes to rotation event
5. Application fetches new key, replaces in memory cache
6. Old key remains valid for provider-defined grace period
7. No deployment, no restart, no downtime
```

For LLM providers that support multiple active keys: issue new key, update secret manager, wait for propagation, revoke old key.

## 4. Rate Limiting

### Algorithms

| Algorithm | Behavior | Burst Support | Memory | Best For |
|-----------|----------|---------------|--------|----------|
| **Fixed Window** | N requests per time window | 2x burst at boundaries | O(1) per key | Simple APIs, low accuracy acceptable |
| **Sliding Window Log** | N requests in last T seconds | Natural burst | O(N) per key | High-accuracy, low-volume APIs |
| **Sliding Window Counter** | Weighted average of current + previous window | Near-natural burst | O(1) per key | Production default for most APIs |
| **Token Bucket** | Tokens refill at constant rate, burst up to bucket capacity | Controlled burst | O(1) per key | Payment APIs, AWS-style APIs |
| **Leaky Bucket** | Constant outflow rate | No burst (smoothed) | O(1) per key | Traffic shaping, consistent throughput |

### Fixed Window Burst Problem

With 100 req/min limit:
- Requests 0-59: allowed up to 100
- Requests 60-119: allowed up to 100
- Requests 58-62 (across boundary): 100 from window 1 + 100 from window 2 = 200 in 4 seconds

**Sliding window counter** solves this: `estimated_count = count_current_window * weight + count_previous_window * (1 - weight)` where `weight` = elapsed time in current window / window size.

### Distributed Rate Limiting

Single-process rate limiting fails in distributed systems: 50 pods each allow 100 req/min = 5000 req/min total (100x intended).

**Redis-based distributed rate limiting**:
```
# Fixed window counter in Redis (atomic Lua script)
local key = KEYS[1]
local limit = tonumber(ARGV[1])
local window = tonumber(ARGV[2])

local current = tonumber(redis.call('GET', key) or '0')
if current >= limit then
    return 0  # rejected
end
redis.call('INCR', key)
redis.call('EXPIRE', key, window)
return 1  # allowed
```

**Tools**: Redis + Lua scripts, Redis Cell module, rate limiting libraries in API gateways (Kong, Envoy, AWS API Gateway).

### 429 Response Handling

When a client receives `429 Too Many Requests`:
- Response MUST include `Retry-After` header (seconds until limit resets)
- Response SHOULD include `X-RateLimit-Limit`, `X-RateLimit-Remaining`, `X-RateLimit-Reset` headers
- Client MUST implement exponential backoff: wait `Retry-After`, then 2x, 4x, 8x, cap at 60s
- Client MUST NOT spam retry immediately after 429

### Per-Dimension Rate Limiting

| Dimension | Key Format | Use Case |
|-----------|-----------|----------|
| Per-IP | `rl:ip:{ip}:{endpoint}` | Public API, anonymous access |
| Per-user | `rl:user:{user_id}:{endpoint}` | Authenticated API, fair usage |
| Per-API-key | `rl:key:{api_key_id}:{endpoint}` | Third-party integrations |
| Per-tenant | `rl:tenant:{tenant_id}:{endpoint}` | Multi-tenant SaaS |
| Global | `rl:global:{endpoint}` | Hard ceiling for the service |

## 5. Input Validation & Sanitization

### Schema Validation

**Pydantic** (Python):
```python
from pydantic import BaseModel, Field, constr

class CreateDocument(BaseModel):
    title: constr(min_length=1, max_length=200)
    content: str = Field(..., max_length=50000)
    tags: list[str] = Field(default_factory=list, max_length=20)
    visibility: Literal["private", "team", "public"]
```

**JSON Schema** (language-agnostic):
```json
{
  "type": "object",
  "required": ["title", "content"],
  "properties": {
    "title": {"type": "string", "minLength": 1, "maxLength": 200},
    "content": {"type": "string", "maxLength": 50000},
    "visibility": {"type": "string", "enum": ["private", "team", "public"]}
  },
  "additionalProperties": false
}
```

- `additionalProperties: false` prevents mass assignment (user sends `{"is_admin": true}`)
- Field-level length constraints prevent oversized payloads
- Enum/type validation prevents injection of unexpected types

### Input Size Limits

| Layer | Limit | Purpose |
|-------|-------|---------|
| Web server / reverse proxy | `client_max_body_size` (Nginx), `LimitRequestBody` (Apache) | Prevent oversized request bodies before application |
| API framework | Body size limit (FastAPI: `app.add_middleware(RequestSizeLimitMiddleware, max_body_size=1_000_000)`) | Application-level enforcement |
| LLM proxy | Prompt token count limit (e.g., 128K tokens max) | Prevent unbounded consumption (OWASP LLM10, API4) |
| Database | Column length constraints, JSON field size limits | Defense in depth |

### Content-Type Enforcement

- Reject requests where `Content-Type` header doesn't match expected type
- Prevent content-type confusion attacks (sending JSON with `text/xml` to bypass JSON-specific validation)
- FastAPI automatically enforces this when using `Body(...)` with typed parameters
- Explicit check: `if request.headers.get("Content-Type") != "application/json": return 415`

### SQL/NoSQL Injection Prevention

| Attack | Mechanism | Prevention |
|--------|-----------|------------|
| **SQL injection** | Untrusted input concatenated into SQL query | Parameterized queries / prepared statements (always), ORM (SQLAlchemy, Django ORM) |
| **NoSQL injection** | Object-based query manipulation (MongoDB: `{"password": {"$ne": ""}}`) | Input type validation, field whitelist, sanitized query builders |
| **ORM injection** | Raw SQL through ORM's `.raw()` or `.execute()` with unsanitized input | Never pass user input to raw queries. Use ORM's parameterized methods |
| **Command injection** | User input in `os.system()`, `subprocess.call()` with `shell=True` | Never use `shell=True` with user input. Use `subprocess.run([...], shell=False)` |

**Mass assignment prevention**:
- Use explicit field whitelists (not `request.json` directly mapped to model)
- `additionalProperties: false` in JSON Schema
- Pydantic model with only expected fields
- Django: use `ModelForm` with `fields` whitelist, not `Model(request.POST)`

## 6. Transport Security

### TLS/HTTPS

All API traffic MUST use TLS. No exceptions.

**TLS 1.3 handshake (simplified)**:
1. Client sends `ClientHello` with supported cipher suites, TLS version, key share
2. Server responds with `ServerHello`, chosen cipher suite, its key share, certificate
3. Client verifies server certificate chain against trusted root CAs
4. Both parties derive shared secret from key exchange (Diffie-Hellman)
5. Session keys derived from shared secret
6. Application data encrypted with session keys

**TLS 1.3 advantages over 1.2**:
- 1-RTT handshake (was 2-RTT in TLS 1.2)
- 0-RTT for resumed sessions (replay risk, use with caution)
- Removed obsolete algorithms (RC4, DES, 3DES, SHA-1, MD5)
- Forced forward secrecy (no static RSA key exchange)
- Encrypted Server Hello (SNI not visible to network observers with ECH)

### Certificate Management

| Aspect | Requirement |
|--------|-------------|
| **CA** | Use trusted CA (Let's Encrypt for public, internal CA for private) |
| **Automation** | ACME protocol (certbot, cert-manager) for automatic renewal |
| **Rotation** | Rotate certificates before expiry (30-day renewal, 7-day overlap) |
| **OCSP/CRL** | Enable OCSP stapling for revocation checking |
| **TLS version** | Minimum TLS 1.2, prefer TLS 1.3. Disable TLS 1.0/1.1 and SSLv3 |
| **Cipher suites** | Disable weak ciphers. Require ECDHE + AES-GCM or ChaCha20-Poly1305 |

### HSTS (HTTP Strict Transport Security)

```
Strict-Transport-Security: max-age=63072000; includeSubDomains; preload
```

- Tells browser: only use HTTPS for this domain for `max-age` seconds (2 years)
- `includeSubDomains`: apply to all subdomains
- `preload`: eligible for HSTS preload list (Chrome, Firefox, Safari ship with hardcoded list)
- MUST have valid HTTPS before enabling HSTS (irreversible for preload)

### Certificate Pinning

- **Public key pinning**: Hardcode expected server public key hash in client
- **Prevents**: MITM with fraudulent CA-issued certificates
- **Mobile APIs**: Common pattern in banking, healthcare apps
- **Risk**: Pin rotation breaks all clients if not handled carefully (use backup pins, two-pin rotation)
- **HTTP Public Key Pinning (HPKP)**: Deprecated (removed from Chrome 2018). Alternatives: native pinning in mobile SDKs (iOS `URLSessionDelegate`, Android `NetworkSecurityConfig`), DANE (TLSA DNS records), or Certificate Transparency log monitoring

## 7. OWASP API Security Top 10 (2023)

The OWASP API Security Top 10 is the definitive list of API-specific security risks. The 2023 edition is the current standard (no 2025/2026 API-specific update -- the general OWASP Top 10 updated to 2025, but the API-specific list remains the 2023 edition).

| # | Risk | Description | Mitigation | AI/LLM Relevance |
|---|------|-------------|------------|-------------------|
| **API1** | Broken Object Level Authorization | Attacker modifies object ID to access another user's resources | Always check resource ownership per request; centralize authorization; use UUIDs | LLM API: user accessing another user's chat history, prompts, or generated content via ID manipulation |
| **API2** | Broken Authentication | Weak auth implementation allows identity compromise | Enforce strong auth (MFA, PKCE); short token TTL; refresh rotation; brute-force protection | LLM proxy: weak authentication on gateway allows attacker to use any provider key |
| **API3** | Broken Object Property Level Authorization | Excessive data exposure or mass assignment | Whitelist response fields; `additionalProperties: false`; never expose internal fields | LLM API: response includes full system prompt, internal model metadata, or other user's API key |
| **API4** | Unrestricted Resource Consumption | No limits on network, CPU, memory, or paid API calls | Rate limiting, input size limits, timeout enforcement, cost caps per user | **Critical for LLM APIs**: unlimited prompt sizes → unbounded token consumption → massive cost (OWASP LLM10) |
| **API5** | Broken Function Level Authorization | Regular users access admin endpoints | Role checks on every endpoint; separate admin paths; deny by default | LLM API: regular user calls admin endpoints to modify system prompts or access all users' data |
| **API6** | Unrestricted Access to Sensitive Business Flows | Business logic abused without auth/bot protection | Bot detection, CAPTCHA, transaction signing, business-level rate limits | LLM API: automated mass generation of content, spam via chat API, abuse of free tier |
| **API7** | Server Side Request Forgery (SSRF) | API fetches attacker-controlled URL | URL validation/whitelist; block internal IPs; restrict outbound network | LLM API: LLM tool-use / function calling fetching attacker-supplied URLs (agent SSRF) |
| **API8** | Security Misconfiguration | Default credentials, open CORS, verbose errors, unnecessary features | Secure defaults; disable debug mode; proper CORS; disable directory listing | LLM gateway: default credentials, exposed admin panel, verbose error messages leaking model configs |
| **API9** | Improper Inventory Management | Undocumented APIs, shadow APIs, old versions | API inventory; disable deprecated endpoints; API discovery tools | LLM backend: forgotten test endpoints, debug routes, old model versions still accessible |
| **API10** | Unsafe Consumption of APIs | Trusting third-party API data without validation | Validate all third-party data; don't trust SDK defaults; monitor dependencies | **Critical**: LLM gateway trusting provider responses; third-party model APIs returning malicious content |

### API Security vs General Web Security

| OWASP Web Top 10 (2025) | OWASP API Top 10 (2023) | Key Difference |
|------------------------|------------------------|----------------|
| A01: Broken Access Control | API1: BOLA, API3: BOPLA, API5: BFLA | APIs expose granular object/property/function access control that web apps don't (SSRF now rolled into A01) |
| A05: Injection | API8 (misconfiguration enables injection) | Injection is less about SQL and more about SSRF, mass assignment in APIs |
| A06: Insecure Design | API6 (unrestricted business flows) | API business logic abuse is a distinct threat category |
| A02: Security Misconfiguration | API8: Security Misconfiguration | Same category, rose from #5 to #2 — more critical in APIs (default configs expose data) |

## 8. CORS & CSRF

### CORS (Cross-Origin Resource Sharing)

CORS is a relaxation of the same-origin policy (SOP), controlled by the server. It is NOT a security feature -- it is a mechanism to allow controlled cross-origin access.

**Same-origin policy**: A page from `https://app.mycompany.com` cannot read responses from `https://api.othercompany.com` via `fetch()`/`XMLHttpRequest`.

**CORS headers**:
```
Access-Control-Allow-Origin: https://app.mycompany.com  (NOT *)
Access-Control-Allow-Methods: GET, POST, PUT, DELETE
Access-Control-Allow-Headers: Authorization, Content-Type
Access-Control-Allow-Credentials: true
Access-Control-Max-Age: 86400
```

**Preflight (OPTIONS) request**: Browser sends `OPTIONS` before non-simple requests (PUT, DELETE, custom headers, content-type != form-urlencoded/multipart/text-plain). Server responds with allowed origins/methods/headers. Browser then sends the actual request only if preflight passes.

**Common misconfigurations**:
- `Access-Control-Allow-Origin: *` with `Access-Control-Allow-Credentials: true` (browser blocks this, but if implemented in reverse proxy that strips it...)
- Reflecting `Origin` header: `Access-Control-Allow-Origin: ${request.headers.origin}` (allows any origin)
- Wildcard methods: `Access-Control-Allow-Methods: *` (should enumerate only needed methods)

**For APIs**: If the API is only consumed by server-side code or mobile apps (not browsers), CORS headers are irrelevant -- browsers enforce CORS, not mobile apps or `curl`. But always set restrictive CORS anyway in case a browser-based client is added later.

### CSRF (Cross-Site Request Forgery)

Attack: User visits `evil.com`, which contains `<img src="https://api.myapp.com/transfer?to=attacker&amount=10000">`. Browser sends cookies with the request. If `api.myapp.com` trusts cookies, the transfer succeeds.

**Defense strategies**:
| Strategy | Mechanism | Effectiveness |
|---------|-----------|---------------|
| **SameSite cookies** | `Set-Cookie: session=abc; SameSite=Strict` (or `Lax`) | Strong. `Strict` = no cross-origin cookie sending. `Lax` = allows top-level navigations (GET) |
| **CSRF tokens** | Server generates random token, embedded in form/headers, validated on submit | Strong. Token must be present in request body or custom header (not sent by cross-origin img/script) |
| **Bearer tokens** | Token in `Authorization` header, not in cookie | CSRF-proof. Cross-origin requests cannot set custom headers without CORS preflight |
| **Double submit cookie** | Token in both cookie and request body, compare server-side | Good but weaker than CSRF tokens (cookie still sent cross-origin for `SameSite=None`) |

**For API-only backends**: Using `Authorization: Bearer <token>` instead of cookies makes the API inherently CSRF-proof. This is the primary reason JWT Bearer tokens are preferred for SPAs and API backends.

## 9. Security Headers

| Header | Value | Prevents |
|--------|-------|----------|
| `Content-Security-Policy` | `default-src 'self'; script-src 'self'; style-src 'self' 'unsafe-inline'; img-src 'self' data:; connect-src 'self' https://api.myapp.com` | XSS (restricts where scripts/styles can load from) |
| `X-Content-Type-Options` | `nosniff` | MIME-type sniffing (browser won't guess content type, e.g., JSON displayed as HTML) |
| `X-Frame-Options` | `DENY` (or `SAMEORIGIN`) | Clickjacking (page cannot be embedded in iframe) |
| `Strict-Transport-Security` | `max-age=63072000; includeSubDomains; preload` | Downgrade attacks (forces HTTPS for all future requests) |
| `Referrer-Policy` | `strict-origin-when-cross-origin` | Leaking sensitive URLs in Referer header |
| `Permissions-Policy` | `camera=(), microphone=(), geolocation=()` | Unauthorized use of browser features |
| `Cache-Control` | `no-store, no-cache, must-revalidate` | Caching sensitive responses (especially for authenticated endpoints) |

**For API responses** (non-HTML):
```
X-Content-Type-Options: nosniff
Strict-Transport-Security: max-age=63072000; includeSubDomains
Cache-Control: no-store
Referrer-Policy: strict-origin-when-cross-origin
```

CSP and X-Frame-Options are primarily for HTML responses, not raw JSON API responses. But apply them universally at the API gateway for defense in depth.

### CSP for LLM Chat Interfaces

If your API serves an HTML chat interface:
```
Content-Security-Policy:
  default-src 'self';
  script-src 'self' https://cdn.myapp.com;
  connect-src 'self' https://api.myapp.com wss://ws.myapp.com;
  style-src 'self' 'unsafe-inline';
  frame-ancestors 'none';
  base-uri 'self';
  form-action 'self'
```

- `frame-ancestors 'none'` prevents clickjacking (replaces X-Frame-Options)
- `connect-src` restricts where the chat UI can send API requests
- `script-src` restricts script sources (prevents injection of malicious scripts via LLM output)

## 10. Secrets Management

### Why Environment Variables Are Not Sufficient

| Risk | Example |
|------|---------|
| **Process listing** | `ps aux` can show environment variables on some systems |
| **Error logs** | Unhandled exceptions may dump env vars into log files |
| **CI/CD exposure** | `.env` files accidentally committed, exposed in CI logs |
| **No rotation** | Env var changes require deployment restart |
| **No audit** | No access logging, no revocation trail |
| **Broad access** | All processes on the machine see all env vars |

### Secret Managers

| Tool | Type | Key Features |
|------|------|-------------|
| **HashiCorp Vault** | Self-hosted or HCP | Dynamic secrets (DB credentials auto-generated), PKI engine, transit encryption, policies, audit log. Industry standard |
| **AWS Secrets Manager** | Managed | Auto-rotation (30-day schedule), integration with IAM/RDS/Lambda, encryption with KMS |
| **AWS SSM Parameter Store** | Managed | Hierarchy (paths), cheaper than Secrets Manager, no auto-rotation for all types |
| **GCP Secret Manager** | Managed | Auto-rotation, IAM integration, versioning |
| **Azure Key Vault** | Managed | HSM-backed, certificate management, access policies |
| **1Password CLI / Doppler / Infisical** | Developer-focused | Easy onboarding, team sharing, CI/CD integration |

### Secret Rotation Pattern

```
1. Secret stored in secret manager with rotation schedule
2. Application fetches secret at startup, caches in memory
3. Rotation event triggers:
   a. Secret manager generates new version
   b. Application notified (polling or webhook)
   c. Application fetches new version, updates memory cache
   d. Old version invalidated after grace period
4. No deployment, no restart
```

For LLM API keys: issue new key from provider dashboard, update secret manager, verify new key works, revoke old key.

### CI/CD Secrets

- NEVER commit secrets to git (even in `docker-compose.local.yml` or `.env`)
- Use CI/CD secret variables (GitHub Secrets, GitLab CI Variables, Bitbucket Pipelines)
- GitHub Actions: `${{ secrets.OPENAI_API_KEY }}` -- never logged or visible in UI
- Pre-commit hooks (like this repo's `.githooks/pre-commit`) to catch accidental commits
- GitHub Secret Scanning: automatically detects committed secrets and alerts

### Defense in Depth for Secrets

1. **Storage**: Secret manager, not env vars or config files
2. **Access**: IAM roles with least privilege. Only the service that needs the secret can read it
3. **Rotation**: Automated rotation on schedule and on compromise detection
4. **Transmission**: TLS everywhere. Secrets in transit are encrypted
5. **Usage**: Secrets used in memory only, never logged or serialized
6. **Revocation**: Immediate revocation capability without deployment
7. **Detection**: Secret scanning in git history, CI logs, error reports

## Interview Questions

### Q1: Walk through how you would secure a REST API for an AI backend that calls OpenAI/Anthropic APIs.

**Model Answer**:

1. **Authentication**: JWT Bearer tokens for user auth. Short-lived access tokens (15 min TTL) + refresh token rotation. RS256 signing with JWK set for key distribution. Validate `exp`, `iss`, `aud`, and hardcode `algorithms=["RS256"]`

2. **LLM API key management**: Store OpenAI/Anthropic keys in AWS Secrets Manager with auto-rotation. Application fetches on startup, caches in memory, subscribes to rotation events. Optionally use LiteLLM proxy as LLM gateway -- application sends request to gateway, gateway holds provider keys

3. **Authorization**: RBAC for role-based access. Every endpoint checks user role. For resource access (chat history, documents), enforce object-level authorization: `resource.owner == current_user`

4. **Rate limiting**: Token bucket algorithm at API gateway. Per-user limits (100 requests/min) and global limits. Redis-based distributed rate limiting across gateway pods. For LLM endpoints, enforce token count limits and cost caps per user per month

5. **Input validation**: Pydantic models for request/response schemas. `additionalProperties: false` prevents mass assignment. Max prompt size of 128K tokens. Content-Type enforcement. No raw SQL -- parameterized queries via SQLAlchemy

6. **Transport**: TLS 1.3 everywhere. mTLS for service-to-service. HSTS with preload. Certificate management via cert-manager

7. **Secrets**: All secrets in Vault/Secrets Manager. CI/CD secrets via GitHub Secrets. Secret scanning in pre-commit hooks. No secrets in environment files committed to VCS

### Q2: What is BOLA and why is it the #1 API security risk? How do you prevent it?

**Model Answer**:

BOLA (Broken Object Level Authorization, OWASP API1:2023) occurs when an API endpoint handles object identifiers but doesn't verify that the requesting user is authorized to access that specific object. An attacker simply changes the ID in the request to access another user's resources.

Example: `GET /api/users/me/documents/1234` -- attacker changes to `/api/users/me/documents/5678` to access another user's document. If the server only checks authentication (user is logged in) but not authorization (user owns document 5678), the attack succeeds.

**Prevention**:
1. Check `resource.owner == current_user` on every data access, in every endpoint
2. Centralize authorization logic in middleware, not scattered in handlers
3. Use UUIDs instead of sequential IDs (harder to guess but does NOT replace authorization checks)
4. Write automated tests that attempt cross-user access
5. Log and alert on authorization failures -- repeated failures likely indicate probing

For LLM APIs: this applies to chat histories, generated content, fine-tuning jobs, embeddings -- any resource identified by an ID.

### Q3: How does JWT authentication work end-to-end? What are the common vulnerabilities?

**Model Answer**:

**Flow**: Client authenticates (login) → Auth service verifies credentials → Issues RS256 JWT with claims (sub, iss, aud, exp, scope, roles) → Client sends JWT in `Authorization: Bearer <token>` → Resource service validates locally (signature, exp, iss, aud) → Processes request

**Required validation steps**: Verify signature with cached public key (from JWK set matched by `kid`), check `exp`, `iss`, `aud`, `nbf`. Hardcode `algorithms=["RS256"]`.

**Common vulnerabilities**:
1. Algorithm confusion (CVE-2016-10555): Attacker sets `alg: HS256`, uses RSA public key as HMAC secret. Fix: hardcode accepted algorithms
2. Missing `aud` validation: Token for service A replayed at service B (confused deputy). Fix: always validate `aud`
3. Long TTL: Extended exposure window. Fix: 5-15 min access tokens
4. Token in URL: Leaked via browser history, logs, Referer. Fix: never put JWTs in URLs
5. JWT payload not encrypted: Base64 encoded, not encrypted. Fix: never put secrets in JWT payload

### Q4: You're building an LLM proxy gateway. How do you secure the provider API keys?

**Model Answer**:

1. **Architecture**: Application → LLM Gateway (in private VPC) → Provider APIs. Application never touches provider keys
2. **Key storage**: Gateway stores keys in HashiCorp Vault or AWS Secrets Manager with auto-rotation
3. **Gateway authentication**: mTLS between application and gateway. Service account auth, not API keys for gateway access
4. **Gateway hardening**: No public ingress. Input validation (reject oversized prompts). Rate limiting per consumer. No default credentials. Security patches applied promptly (CVE-2026-42208 showed gateways are targets)
5. **Key rotation**: New provider key issued → update Vault → gateway fetches new key → verify it works → revoke old key. Zero downtime
6. **Observability**: Log all requests (sans sensitive data). Alert on unusual patterns (spike in errors, cost anomalies)
7. **Fallback**: Multiple provider keys per provider for failover. Dead letter queue for failed requests

### Q5: Explain the difference between token bucket and sliding window rate limiting. When would you use each?

**Model Answer**:

**Token bucket**: Tokens accumulate at a fixed rate up to a maximum (bucket capacity). Each request consumes a token. If bucket is empty, request is rejected. Allows burst up to bucket capacity, then settles to steady rate. Standard for payment APIs (AWS, Stripe) where controlled burst is desirable.

**Sliding window counter**: Maintains weighted count of requests: `count = current_window * weight + previous_window * (1 - weight)` where weight is elapsed time / window size. O(1) memory, near-exact accuracy. Production default for most REST APIs.

Use token bucket when you need to allow controlled bursts (payment processing, LLM API calls where users may legitimately need to send multiple requests quickly). Use sliding window counter for general-purpose rate limiting where smooth distribution is preferred (user-facing APIs, social features).

### Q6: What is CORS? Is it a security feature? How do you configure it for a SPA + API backend?

**Model Answer**:

CORS is NOT a security feature. It is a relaxation of the same-origin policy, controlled by the server via response headers. The same-origin policy prevents a page from `https://evil.com` from reading responses from `https://api.myapp.com`. CORS allows the API server to explicitly permit cross-origin access.

**Configuration for SPA + API**:
```
Access-Control-Allow-Origin: https://app.myapp.com  (exact origin, not *)
Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS
Access-Control-Allow-Headers: Authorization, Content-Type
Access-Control-Allow-Credentials: true  (if using cookies)
Access-Control-Max-Age: 86400  (preflight cache for 24h)
```

**Critical rules**:
- Never use `Access-Control-Allow-Origin: *` with `Access-Control-Allow-Credentials: true`
- Never reflect the `Origin` header without validation
- If using JWT Bearer tokens (not cookies), `Allow-Credentials` is not needed
- Preflight (OPTIONS) is automatic for non-simple requests; handle it at the API gateway or framework level

### Q7: How do you prevent SQL injection in a Python/FastAPI API? What about NoSQL injection?

**Model Answer**:

**SQL injection prevention**: Always use parameterized queries (prepared statements). SQLAlchemy ORM handles this by default -- `session.query(User).filter(User.email == email)` generates a parameterized query. Never use f-strings or string concatenation for SQL: `db.execute(f"SELECT * FROM users WHERE email = '{email}'")` is vulnerable.

For raw SQL in SQLAlchemy: `db.execute(text("SELECT * FROM users WHERE email = :email"), {"email": email})`.

**NoSQL injection prevention**: MongoDB queries can be manipulated via object injection. `{"password": {"$ne": ""}}` in a login query bypasses authentication. Prevention:
1. Type validation: ensure password is a string, not a dict
2. Field whitelist: only allow known fields in queries
3. Use MongoDB's query builders that enforce schema, not raw dict queries
4. Pydantic validation before passing to query layer

### Q8: Your LLM API is being abused -- someone discovered the endpoint and is sending unlimited requests. How do you respond?

**Model Answer**:

**Immediate (0-5 min)**:
1. Rate limit: Apply emergency per-IP rate limit at the API gateway/waf
2. Identify: Check logs for the source (IP, user agent, patterns)
3. Block: Add IP to blocklist if clearly malicious
4. Cost cap: Enable per-user cost limits if the LLM provider supports it

**Short-term (hours)**:
1. Implement proper rate limiting: token bucket with Redis, per-user/per-API-key
2. Add request size limits: max prompt tokens, max response tokens
3. Authentication: Ensure all endpoints require auth (no unauthenticated LLM access)
4. Monitoring: Alert on unusual usage patterns (spikes in token consumption, errors)

**Long-term (days)**:
1. Implement tiered rate limits: per-plan (free tier: 10 RPM, paid: 100 RPM, enterprise: custom)
2. Budget alerts: alert when user approaches their token budget
3. Circuit breaker: auto-disable users who exceed limits for a cooldown period
4. OWASP API4 compliance: Document and test resource consumption limits
5. Consider LLM gateway (LiteLLM, Portkey) for centralized cost control and routing

### Q9: What security headers should every API response include? Explain what each prevents.

**Model Answer**:

Every API response should include:
1. `X-Content-Type-Options: nosniff` -- Prevents MIME-type sniffing. If the API returns JSON but the browser (or proxy) tries to interpret it as HTML, this header forces correct interpretation. Prevents XSS via content-type confusion
2. `Strict-Transport-Security: max-age=63072000; includeSubDomains` -- Forces HTTPS for all future requests. Prevents downgrade attacks (attacker forcing HTTP to intercept traffic)
3. `Cache-Control: no-store` -- Prevents caching of authenticated API responses. Prevents sensitive data being stored in browser cache, CDN cache, or proxy cache
4. `Referrer-Policy: strict-origin-when-cross-origin` -- Limits what URL information is sent in the Referer header. Prevents leaking sensitive path/query parameters to third-party sites
5. `X-Frame-Options: DENY` -- Prevents the API response being embedded in an iframe. Prevents clickjacking (primarily for HTML endpoints)
6. `Content-Security-Policy` -- Primarily for HTML endpoints served by the API. Restricts script/style/image sources to prevent XSS

For pure JSON API responses, the minimum is: `X-Content-Type-Options: nosniff`, `Strict-Transport-Security`, `Cache-Control: no-store`, `Referrer-Policy`.

### Q10: Walk through the OWASP API Security Top 10. Which 3 are most critical for an LLM API backend?

**Model Answer**:

1. **API1: Broken Object Level Authorization** -- BOLA. Most critical. LLM backends expose chat histories, generated content, fine-tuning jobs by ID. Must enforce ownership checks on every resource access
2. **API2: Broken Authentication** -- Weak auth on the LLM proxy/gateway allows unauthorized access. Combined with API3 (excessive data exposure), could leak system prompts or other users' conversations
3. **API3: Broken Object Property Level Authorization** -- Mass assignment or excessive data exposure. LLM API responses must not include internal fields (system prompts, model parameters, other users' API keys)
4. **API4: Unrestricted Resource Consumption** -- Critical for LLM. No prompt size limit + no rate limit = unbounded token consumption = unlimited cost. Must enforce input size, token count, and cost limits
5. **API5: Broken Function Level Authorization** -- Regular user accessing admin endpoints (modify system prompts, access all users' data)
6. **API6: Unrestricted Access to Sensitive Business Flows** -- Automated abuse of free tier, mass content generation
7. **API7: Server Side Request Forgery** -- LLM agent/function calling fetching attacker-controlled URLs
8. **API8: Security Misconfiguration** -- Default credentials on LLM gateway, verbose errors, CORS misconfiguration
9. **API9: Improper Inventory Management** -- Forgotten test endpoints, debug routes, old model versions
10. **API10: Unsafe Consumption of APIs** -- Trusting third-party model provider responses without validation

**Most critical for LLM backend**: API4 (cost/critical), API1 (data breach), API2 (gateway compromise). These three cover the unique risk profile of LLM API backends.

### Q11: Explain how mTLS works and when you would use it for API security.

**Model Answer**:

mTLS (Mutual TLS) requires both client and server to present X.509 certificates during the TLS handshake. In regular TLS (one-way), only the server proves its identity. In mTLS, the server also verifies the client certificate.

**Handshake**: Client sends `ClientHello` + client certificate → Server verifies client cert against trusted CA or allows list → Server sends `ServerHello` + server certificate → Client verifies server cert → Key exchange → Encrypted communication.

**When to use**:
1. **Service mesh** (Istio, Linkerd): mTLS between all microservices. Envoy sidecars handle it transparently
2. **Financial APIs**: Open Banking (PSD2) requires mTLS for TPP access
3. **Internal microservices**: Zero-trust architecture where every service authenticates to every other service
4. **LLM gateway**: mTLS between application and LLM gateway ensures only authorized services can call the gateway

**When not to use**:
- Public-facing APIs (most browsers don't support client certs)
- Mobile apps (client cert management is complex)
- Simple internal APIs where JWT/OAuth2 is sufficient

**Management**: Certificate issuance via internal CA (Vault PKI engine, cert-manager), rotation (30-day lifetime, auto-renewal), revocation via OCSP/CRL.

### Q12: How do you design a secrets management architecture for a multi-service backend that calls multiple LLM providers?

**Model Answer**:

**Architecture**:
1. **HashiCorp Vault** as central secrets manager. Stores all LLM provider keys, database credentials, internal service tokens
2. **Vault Agent** or Vault CSI driver for Kubernetes: injects secrets as files or environment variables into pods at startup. No secrets in k8s Secrets (which are base64, not encrypted at rest by default)
3. **Dynamic secrets** for database credentials: Vault generates short-lived DB credentials per service, auto-rotates
4. **Static secrets** for LLM API keys: stored in Vault KV engine with 30-day rotation schedule
5. **Access policies**: Each service has its own Vault role with least privilege -- payment service can read DB creds but not LLM keys; LLM service can read provider keys but not payment gateway secrets
6. **Audit**: Vault audit log (append-only) records every secret access. SIEM integration
7. **Rotation automation**: Vault's auto-rotation for static secrets, cron for provider-specific key rotation (issue new key from OpenAI dashboard, update Vault, verify, revoke old)

**For CI/CD**: GitHub Secrets for deploy keys and tokens. GitHub Secret Scanning to detect committed secrets. Pre-commit hooks (like this repo's) to prevent accidental commits.

**Verification**: Regular secret scanning in git history (gitleaks, truffleHog). Automated rotation verification (test that new key works before revoking old).

## Key Terminology

**BOLA (Broken Object Level Authorization)** -- OWASP API1:2023, the #1 API security risk. Occurs when an API endpoint accesses a resource by ID without verifying the requesting user owns that resource. Attacker modifies the ID parameter to access other users' data. Prevention: always check resource ownership, centralize authorization, use UUIDs (but never rely on unguessable IDs alone).

**OWASP API Security Top 10** -- The definitive list of API-specific security risks, last updated in 2023. Covers BOLA (API1), broken authentication (API2), broken object property level authorization (API3), unrestricted resource consumption (API4), broken function level authorization (API5), unrestricted business flows (API6), SSRF (API7), security misconfiguration (API8), improper inventory management (API9), and unsafe consumption of APIs (API10).

**Token Bucket** -- Rate limiting algorithm where tokens accumulate at a constant rate up to a maximum capacity. Each request consumes a token; if empty, the request is rejected. Allows controlled bursts up to capacity, then settles to steady rate. Standard for payment APIs and cloud provider APIs (AWS, Stripe).

**mTLS (Mutual TLS)** -- TLS extension where both client and server present X.509 certificates during the handshake. Used for zero-trust service-to-service communication (service mesh, financial APIs). Provides cryptographic identity without API keys or tokens. Management overhead via certificate lifecycle (issuance, rotation, revocation).

**PKCE (Proof Key for Code Exchange)** -- Extension to OAuth 2.0 Authorization Code flow that prevents authorization code interception. Client generates a random `code_verifier`, sends `code_challenge` (SHA256 hash) to the authorization server, and proves possession of the verifier when exchanging the code for tokens. Required for SPAs and mobile apps where the client secret cannot be stored securely.

**CORS (Cross-Origin Resource Sharing)** -- HTTP header-based mechanism that allows a server to indicate which origins are permitted to access its resources from a browser. Controlled by the server via `Access-Control-Allow-Origin` and related headers. Preflight (OPTIONS) requests sent by browsers for non-simple requests. NOT a security feature -- it relaxes the same-origin policy.

**HSTS (HTTP Strict Transport Security)** -- Response header (`Strict-Transport-Security`) that instructs browsers to only use HTTPS for all future requests to the domain. With `includeSubDomains; preload`, the domain is included in browser-shippped HSTS preload lists. Prevents downgrade attacks but is irreversible for preload.

**LLM Gateway** -- A proxy layer between applications and LLM providers (e.g., LiteLLM, Portkey, Helicone) that provides a unified API interface, centralized key management, per-team rate limiting, cost controls, model routing, and observability. The gateway stores all provider API keys, making it a high-value security target.

**Mass Assignment** -- Attack where an attacker sends unexpected fields in a request body that get bound to internal model properties. For example, sending `{"is_admin": true}` in a profile update. Prevention: explicit field whitelists, `additionalProperties: false` in JSON Schema, Pydantic models with only expected fields.

**SSRF (Server-Side Request Forgery)** -- OWASP API7:2023. Attack where an API fetches a remote resource using an attacker-controlled URL without validation. The attacker can make the server access internal services (metadata APIs, databases) that are not directly exposed. Critical for LLM APIs with tool-use/function-calling capabilities where the LLM can initiate HTTP requests.

## Cross-References

- **cs_fundamentals/auth_systems** -- OAuth 2.0 flows, JWT structure/validation, RBAC/ABAC/ReBAC, session vs token auth, key rotation (deeper dive on auth system design)
- **cs_fundamentals/system_security** -- OWASP Top 10 (web), HTTPS/TLS, SQL injection, XSS, CSRF, password hashing, CORS fundamentals
- **cs_fundamentals/api_gateway** -- API gateway architecture, distributed rate limiting, JWT validation at gateway, header stripping, circuit breakers
- **production_engineering/ai_safety_compliance** -- OWASP Top 10 LLM vulnerabilities (LLM01-LLM10), prompt injection, jailbreak defense, PII detection, guardrails (maps to API4 unbounded consumption)
- **production_engineering/security** -- General security patterns, supply chain security (maps to API10)
- **role_specific/senior_ai_engineer** -- Security ownership, LLM gateway deployment, production security architecture
