# Design an Authentication & Authorization System

Source: [Auth Systems (CalibreOS)](https://www.calibreos.com/learn/hld-auth-systems)

## One-Liner
Design a system that verifies user identity (AuthN) and enforces permissions (AuthZ) using JWTs, OAuth 2.0/OIDC flows, and an appropriate authorization model (RBAC/ABAC/ReBAC).

## Functional Requirements
- User registration and login (email/password, SSO via OIDC providers)
- Issue and validate short-lived access tokens and long-lived refresh tokens
- Role-based or relationship-based permission checks on every API request
- MFA support (TOTP, WebAuthn/passkeys)
- Token revocation (logout, password reset, account compromise)
- Account recovery flows
- Audit logging of all auth events (for SOC 2/HIPAA compliance)

## Non-Functional Requirements
- AuthZ checks must complete under 10ms per request (p99)
- AuthN service must handle login spikes (Monday morning, product launches)
- Signing key rotation with zero downtime
- Stateless token verification at scale (100M+ users, 100+ microservices)
- Fail-closed: any validation error denies access

## Key Scale Questions
- 100M users, 10M DAU
- Every API call triggers an AuthZ check (billions/day)
- Read:write ratio heavily read-dominated (auth checks vs logins)
- JWT verification must be local (no central DB hit) -- p99 < 1ms via cached public key
- AuthZ service (e.g., Zanzibar) needs to handle ~2M permission checks/sec at <10ms p99

## Core Components
- **AuthN Service**: handles login, registration, MFA, issues tokens (JWT access + refresh)
- **Token Service**: signs JWTs with RS256, manages JWK set, handles refresh token rotation
- **AuthZ Service**: evaluates permissions (RBAC tables, ABAC policies, or ReBAC graph)
- **Key Management**: stores signing keys in HSM/KMS, publishes JWK set at `/.well-known/jwks.json`
- **Session Store** (hybrid only): Redis-backed session records for global logout support
- **User Store**: user profiles, password hashes (Argon2id), MFA factors
- **Audit Logger**: immutable log of all auth events for compliance

## Key Design Decisions

### Session vs JWT
- **Session-based**: server stores state, trivial revocation (delete row), small client payload (~32 bytes), but every request hits session store. Works to ~10M concurrent sessions with Redis.
- **JWT (stateless)**: client holds signed claims, no server lookup on verify, scales to any number of services. Revocation is hard -- short TTL (5-15 min) + refresh tokens + optional blocklist.
- **Hybrid**: JWT for cross-service identity propagation, central session record in AuthN service for global logout. Common in production.

### HS256 vs RS256 Signing
- **HS256**: symmetric shared secret. All verifiers hold the signing key. One compromise leaks token-minting ability. Only for single monolith.
- **RS256**: asymmetric. Auth service signs with private key; all services verify with public key via JWK set. The correct choice for microservices.

### OAuth 2.0 Flow Selection
- **Authorization Code + PKCE**: web apps, SPAs, mobile. The only correct answer for user-facing clients. PKCE binds code exchange to initiating client.
- **Client Credentials**: service-to-service (cron jobs, backend APIs). No user involved. Secret lives in Vault/KMS.
- **Device Code**: TVs, CLI tools (`gcloud auth login`). User approves on a second device while first device polls.
- **Implicit flow**: deprecated (token leaks via URL fragments). Proposing it is a strong negative signal.
- **ROPC (Password Credentials)**: deprecated by OAuth 2.1. Only for legacy migration.

### Authorization Model
- **RBAC**: (user, role) + (role, permission) tables. O(1) lookup. Simple, auditable. Breaks when permissions depend on resource ownership or sharing.
- **ABAC**: policies over user/resource/environment attributes. Rule evaluation cost. Good for compliance-driven rules (time-of-day, IP range). Implemented via OPA, AWS IAM, Cedar.
- **ReBAC (Zanzibar)**: graph of (user, relation, object) tuples. Graph traversal, cached ~5ms. For collaboration products (Docs, Drive, Dropbox). SpiceDB is the open-source implementation.
- **Hybrid**: RBAC for coarse roles, ReBAC for fine-grained resource sharing. Most production systems at scale.

### Revocation Strategy
- Short access-token TTL (5-15 min) limits exposure window
- Refresh token rotation on every use; detect reuse as theft indicator
- Optional blocklist (Redis set of revoked JWT IDs) for high-value revocations (password reset, device loss)
- Never put JWTs in URLs (leaks via browser history, logs, Referer headers)

## API Endpoints
| Method | Path | Description |
|--------|------|-------------|
| POST | /auth/register | Create account (email, password, name) |
| POST | /auth/login | Authenticate, return access + refresh tokens |
| POST | /auth/refresh | Exchange refresh token for new access token |
| POST | /auth/logout | Invalidate refresh token, optionally blocklist access token |
| POST | /auth/mfa/enroll | Register MFA factor (TOTP secret or WebAuthn credential) |
| POST | /auth/mfa/verify | Verify MFA challenge during login |
| GET | /auth/.well-known/jwks.json | Public signing keys for JWT verification |
| GET | /auth/.well-known/openid-configuration | OIDC discovery metadata |
| POST | /auth/check | AuthZ check: given principal, action, resource -> allow/deny |

## Database Schema

### users
| Column | Type | Notes |
|--------|------|-------|
| user_id | UUID | PK |
| email | VARCHAR(255) | Unique, used for login |
| password_hash | CHAR(97) | Argon2id hash, never plaintext |
| created_at | TIMESTAMP | Account creation time |
| mfa_enabled | BOOLEAN | Whether MFA is active |

### refresh_tokens
| Column | Type | Notes |
|--------|------|-------|
| token_id | UUID | PK, hashed token value |
| user_id | UUID | FK to users |
| family_id | UUID | Groups tokens for reuse detection |
| expires_at | TIMESTAMP | Long-lived (days to weeks) |
| rotated_at | TIMESTAMP | When this token was replaced |

### user_roles (RBAC)
| Column | Type | Notes |
|--------|------|-------|
| user_id | UUID | FK to users |
| role | VARCHAR(50) | e.g., admin, editor, viewer |
| resource_id | VARCHAR(255) | Optional scope to specific resource |

### relation_tuples (ReBAC / Zanzibar)
| Column | Type | Notes |
|--------|------|-------|
| user | STRING | e.g., `user:alice` or `group:engineering` |
| relation | STRING | e.g., `editor`, `viewer`, `owner` |
| object | STRING | e.g., `document:xyz`, `folder:abc` |

## Deep Dive Topics
- JWT algorithm confusion attack (CVE-2016-10555): hardcode `algorithms=["RS256"]` in verifier
- Missing `aud` validation = confused deputy attack (token from service A replayed at B)
- Refresh token reuse detection: if a previously-used refresh token appears, revoke the entire token family
- Key rotation: publish multiple keys in JWK set, sign with new key via `kid`, remove old key after max_token_lifetime + buffer
- OIDC vs OAuth: OIDC adds `id_token` (JWT with user claims) on top of OAuth's access token. "Sign in with Google" = OIDC. "Access my Google Calendar" = OAuth.
- WebAuthn/Passkeys: phishing-resistant by design (domain binding). Private key never leaves device. Preferred MFA for 2024+.
- Zanzibar internals: namespace-based relation tuples, LeetCode-style graph traversal with caching, ~2M checks/sec at <10ms p99
- Timing attacks on password comparison: use `hmac.compare_digest()` (constant-time)
- Session fixation: regenerate session ID on every privilege escalation

## Follow-Up Variations
- How would you design SSO across 10 microservices with key rotation?
- How do you handle "sign out everywhere" (global logout) with JWTs?
- Design auth for a multi-tenant SaaS with enterprise SAML/OIDC federation (Okta, Azure AD)
- How would you implement passwordless login with WebAuthn passkeys?
- What changes when you need to support 100K concurrent sessions on a monolith vs 100M across microservices?
- How do you prevent token theft in a browser SPA (XSS exfiltration)?
