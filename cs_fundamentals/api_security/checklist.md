# API Security -- Self-Assessment Checklist

Use this checklist to gauge your readiness for API security interview questions. Check off items as you can confidently explain them without notes.

## Concept Self-Assessment

- [ ] Can you explain the difference between API keys, OAuth2 tokens, JWTs, session cookies, and mTLS -- and when to use each?
- [ ] Can you walk through the Authorization Code + PKCE flow step by step, including code_verifier/code_challenge?
- [ ] Can you list all JWT validation steps and explain the algorithm confusion attack and missing `aud` validation?
- [ ] Can you explain BOLA (OWASP API1), why it's the #1 API risk, and how to prevent it?
- [ ] Can you compare token bucket vs sliding window rate limiting and choose the right one for a given scenario?
- [ ] Can you explain how to manage LLM API keys securely, including gateway proxy patterns and rotation without deployment?
- [ ] Can you walk through the OWASP API Security Top 10 (all 10 risks) and identify the most critical for LLM backends?
- [ ] Can you explain CORS configuration for a SPA + API backend, and why CORS is not a security feature?
- [ ] Can you list the security headers every API response should include and explain what each prevents?
- [ ] Can you design a secrets management architecture using Vault or AWS Secrets Manager with rotation?

## Explain-Out-Loud Prompts

- [ ] Walk through how you would secure a REST API for an AI backend that calls OpenAI/Anthropic APIs end-to-end.
- [ ] Explain how BOLA works with a concrete example and describe the full prevention strategy.
- [ ] Walk through JWT authentication end-to-end: issuance, validation, rotation, revocation.
- [ ] Design a rate limiting system for a distributed LLM API with per-user and per-tenant limits.
- [ ] Explain how an LLM gateway proxy (LiteLLM/Portkey) works and how you would secure the gateway itself.
- [ ] Compare RBAC vs ABAC for a multi-tenant AI platform API authorization system.
- [ ] Explain mTLS handshake and when you would (and would not) use it for API security.

## Common Questions Practice

- [ ] What is BOLA and why is it the #1 API security risk? Give a concrete attack example and prevention steps.
- [ ] How does JWT authentication work end-to-end? What are the common vulnerabilities (alg confusion, missing aud, long TTL)?
- [ ] You're building an LLM proxy gateway. How do you secure the provider API keys? (storage, rotation, gateway hardening)
- [ ] Explain token bucket vs sliding window rate limiting. When would you use each?
- [ ] What is CORS? Is it a security feature? How do you configure it for a SPA + API backend?
- [ ] How do you prevent SQL injection and NoSQL injection in a Python/FastAPI API?
- [ ] Your LLM API is being abused with unlimited requests. Walk through immediate, short-term, and long-term responses.
- [ ] What security headers should every API response include? Explain what each prevents.
- [ ] Walk through the OWASP API Security Top 10. Which 3 are most critical for an LLM API backend and why?
- [ ] How does mTLS work? When would you use it for API security?
- [ ] Design a secrets management architecture for a multi-service backend calling multiple LLM providers.
- [ ] How does OAuth 2.0 PKCE prevent authorization code interception? Walk through the flow.
- [ ] What is mass assignment? How do JSON Schema `additionalProperties: false` and Pydantic prevent it?
- [ ] How do you implement distributed rate limiting with Redis? What happens if Redis goes down?
- [ ] Explain CVE-2026-42208 (LiteLLM SQL injection). What does it teach us about LLM gateway security?
- [ ] What is SSRF in the context of LLM APIs with function calling? How do you prevent it?
- [ ] How does the same-origin policy work? What is a preflight request and when does the browser send one?
- [ ] Compare session cookies vs JWT Bearer tokens for API authentication. When would you use each?

## Deep-Dive Topics

- [ ] JWT key rotation strategy: JWK set with multiple keys, `kid` matching, overlap windows, verifier caching
- [ ] Refresh token rotation and reuse detection (family-based revocation)
- [ ] LLM API cost control architecture: per-user budgets, token counting, tiered limits, circuit breakers
- [ ] Certificate pinning for mobile APIs: pros, cons, rotation strategy
- [ ] TLS 1.3 vs 1.2: handshake differences, cipher suite differences, 0-RTT risks
- [ ] CSRF defense comparison: SameSite cookies, CSRF tokens, Bearer tokens, double submit cookie
- [ ] API versioning security implications: deprecation, breaking changes, shadow endpoints
- [ ] Shadow API detection: API discovery tools, log analysis, CI/CD pipeline review
- [ ] CSP for LLM chat interfaces: restricting connect-src, script-src, preventing injection via LLM output

## Practice Log

- [ ] ______________ -- ________________________________________________________________
- [ ] ______________ -- ________________________________________________________________
- [ ] ______________ -- ________________________________________________________________
