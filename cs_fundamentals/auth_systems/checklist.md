# Design an Authentication & Authorization System -- Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] Is this AuthN (who are you), AuthZ (what can you do), or both?
  - [ ] What clients: web, mobile, CLI, service-to-service? (Each maps to a different OAuth flow)
  - [ ] Single-tenant or multi-tenant? Is SSO required (SAML/OIDC federation)?
  - [ ] What scale: 10K users or 100M?
  - [ ] What authorization complexity: roles, attributes, or relationships?
  - [ ] What MFA / account-recovery requirements?
  - [ ] Any compliance requirements (SOC 2, HIPAA, PCI-DSS)?
- [ ] List functional requirements (3-5 items):
  - [ ] User registration and login (email/password, SSO)
  - [ ] Issue short-lived access tokens + long-lived refresh tokens
  - [ ] Permission checks on every API request
  - [ ] MFA support (TOTP, WebAuthn/passkeys)
  - [ ] Token revocation (logout, password reset, compromise)
- [ ] List non-functional requirements (latency, availability, scale):
  - [ ] AuthZ checks under 10ms (p99)
  - [ ] Handle login spikes gracefully
  - [ ] Zero-downtime signing key rotation
  - [ ] Fail-closed on any validation error
- [ ] State your scale estimates (users, requests, storage):
  - [ ] ~100M total users, ~10M DAU
  - [ ] Billions of AuthZ checks/day (every API call)
  - [ ] ~1M logins/day (~12 logins/sec avg, spikes to 10x)
  - [ ] Token storage: ~1KB/token x sessions

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw a simple box diagram: Client -> LB -> [API Gateway] -> [AuthN Service + AuthZ Service] -> [Resource Services]
- [ ] Identify the main operations and their access patterns:
  - [ ] `POST /auth/login` -- authenticate user, issue tokens (write, moderate QPS)
  - [ ] `POST /auth/refresh` -- exchange refresh token for new access token (write, high QPS)
  - [ ] `POST /auth/check` -- AuthZ check: principal + action + resource -> allow/deny (read, very high QPS)
  - [ ] `GET /auth/.well-known/jwks.json` -- public signing keys (read, cached)
- [ ] Note the AuthN vs AuthZ split explicitly:
  - [ ] AuthN happens once per session (+ refresh); AuthZ happens on every request
  - [ ] Different failure modes: broken AuthN = impersonation; broken AuthZ = unauthorized actions
  - [ ] Different data stores: users/passwords vs role assignments/ACLs/relation graphs
- [ ] Present the diagram and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain session vs JWT decision and justify:
  - [ ] Session-based: trivial revocation, server stores state, needs shared Redis for horizontal scaling
  - [ ] JWT (stateless): no server lookup, scales to any number of services, revocation is hard
  - [ ] Hybrid: JWT for cross-service propagation + central session record for global logout
  - [ ] State your choice based on architecture (monolith = sessions; microservices = JWT)
- [ ] Explain HS256 vs RS256 signing:
  - [ ] HS256: symmetric, all verifiers share secret, single compromise leaks everything
  - [ ] RS256: asymmetric, private key signs, public key verifies via JWK set
  - [ ] Pick RS256 for any system with more than one verifying service
- [ ] Explain OAuth 2.0 flow selection:
  - [ ] Web/SPA/Mobile = Authorization Code + PKCE
  - [ ] Service-to-service = Client Credentials
  - [ ] TV/CLI = Device Code
  - [ ] Never use Implicit flow (deprecated)
- [ ] Define API endpoints with method, path, request/response:
  - [ ] `POST /auth/login` -> `{"access_token": "...", "refresh_token": "...", "expires_in": 900}`
  - [ ] `POST /auth/refresh` -> `{"access_token": "...", "refresh_token": "...", "expires_in": 900}`
  - [ ] `POST /auth/logout` -> `204 No Content`
  - [ ] `POST /auth/check` -> `{"allowed": true/false}`
  - [ ] `GET /auth/.well-known/jwks.json` -> JWK set with public keys and `kid` values
- [ ] Sketch the database schema:
  - [ ] Table `users`: `user_id` (PK), `email` (unique), `password_hash` (Argon2id), `mfa_enabled`, `created_at`
  - [ ] Table `refresh_tokens`: `token_id` (PK, hashed), `user_id` (FK), `family_id`, `expires_at`, `rotated_at`
  - [ ] Table `user_roles` (RBAC): `user_id`, `role`, optional `resource_id`
  - [ ] Table `relation_tuples` (ReBAC): `user`, `relation`, `object`
- [ ] Discuss authorization model choice:
  - [ ] RBAC: simple (user, role) + (role, permission), O(1), breaks on resource ownership/sharing
  - [ ] ABAC: attribute-based policies, compliance-driven, OPA/Cedar
  - [ ] ReBAC (Zanzibar): graph tuples, collaboration products, SpiceDB, ~2M checks/sec
  - [ ] Hybrid: RBAC for coarse, ReBAC for fine-grained resource sharing
- [ ] Walk through the main flow end-to-end:
  - [ ] Login: user submits credentials -> AuthN service verifies password (Argon2id) + MFA -> issues RS256 JWT (5-15 min TTL) + refresh token
  - [ ] API request: client sends Bearer token -> resource service validates JWT locally with cached public key (checks signature, exp, iss, aud) -> AuthZ check via policy engine -> allow/deny

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss JWT revocation strategy:
  - [ ] Short TTL (5-15 min) limits exposure
  - [ ] Refresh token rotation on every use; detect reuse as theft
  - [ ] Optional blocklist (Redis set) for high-value revocations
  - [ ] Never put JWTs in URLs
- [ ] Explain key management and rotation:
  - [ ] Store signing keys in HSM/KMS, never in config files
  - [ ] Publish JWK set with multiple active keys
  - [ ] Rotate quarterly: add new key, sign with `kid`, remove old key after max TTL + buffer
  - [ ] Verifiers cache JWK set (15 min - 1 hour TTL), pick up new keys automatically
- [ ] Address common attack vectors:
  - [ ] Algorithm confusion: hardcode `algorithms=["RS256"]` (never trust `alg` header)
  - [ ] Missing `aud` validation: confused deputy attack (token replay across services)
  - [ ] Token replay: short TTL + `jti` seen-set for high-value ops + TLS everywhere
  - [ ] Timing attacks: constant-time comparison for password hashes
  - [ ] Session fixation: regenerate session ID on privilege escalation
  - [ ] Refresh token theft: rotate on use + family-based revocation
- [ ] Discuss MFA approaches:
  - [ ] TOTP: strong against breaches, weak against phishing (real-time relay)
  - [ ] SMS: deprecated by NIST for primary factor (SIM swap, SS7)
  - [ ] WebAuthn/Passkeys: phishing-resistant (domain binding), preferred for 2024+
  - [ ] Magic links: low friction, but email security = auth security
- [ ] Explain OAuth vs OIDC:
  - [ ] OAuth 2.0: authorization (delegation), issues access tokens, no user identity
  - [ ] OIDC: authentication layer on top of OAuth, adds `id_token` (JWT with user claims)
  - [ ] "Sign in with Google" = OIDC; "Access my Google Calendar" = OAuth
  - [ ] OIDC Discovery: `/.well-known/openid-configuration` for dynamic endpoint resolution

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made and why:
  - [ ] JWT vs sessions (scale vs revocation simplicity)
  - [ ] RBAC vs ReBAC (simplicity vs expressiveness)
  - [ ] Short TTL + refresh rotation vs blocklist (latency vs immediate revocation)
- [ ] Mention what you would improve with more time
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
