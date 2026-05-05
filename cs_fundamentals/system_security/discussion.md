# System Security

OWASP top 10, authentication, encryption, HTTPS, common web vulnerabilities, and secure password hashing for SWE interviews.

## Key Concepts

- **OAuth 2.0 vs JWT vs SSO**: OAuth 2.0 is an authorization framework that lets a user grant a third-party application limited access to their resources without sharing credentials. JWT (JSON Web Token) is a compact, self-contained token format used to transmit claims between parties (often used in OAuth flows). SSO (Single Sign-On) allows a user to authenticate once and access multiple applications, typically implemented via protocols like SAML or OpenID Connect.
- **Symmetric vs Asymmetric Encryption**: Symmetric encryption (AES, ChaCha20) uses the same key for both encryption and decryption, making it fast but requiring a secure key exchange mechanism. Asymmetric encryption (RSA, ECC) uses a public-private key pair; the public key encrypts and the private key decrypts, solving the key distribution problem but at significantly higher computational cost.
- **HTTPS / TLS**: HTTPS is HTTP over TLS (Transport Layer Security). TLS provides encryption (data cannot be read by intermediaries), authentication (server identity verified via certificate), and integrity (data cannot be tampered with). The server presents an X.509 certificate signed by a trusted Certificate Authority (CA) to prove its identity.
- **SQL Injection**: An attack where untrusted input is concatenated directly into SQL queries, allowing an attacker to execute arbitrary SQL commands. Prevention requires parameterized queries (prepared statements), input validation, and using an ORM that escapes inputs by default.
- **CSRF (Cross-Site Request Forgery)**: An attack that tricks a user's browser into making authenticated requests to a different site without their knowledge. Defense strategies include anti-CSRF tokens embedded in forms, SameSite cookie attributes, and checking the Origin/Referer headers.

## Common Questions with Brief Answer Outlines

**Q: How does OAuth 2.0 work?**
- The client application redirects the user to the authorization server with a client ID, redirect URI, and requested scopes.
- The user authenticates with the authorization server and grants permission.
- The authorization server redirects back with an authorization code.
- The client exchanges the authorization code for an access token (and optionally a refresh token) by authenticating itself with the authorization server.
- The client uses the access token to call the resource server's API on behalf of the user.

**Q: Explain the OWASP Top 10 and how to mitigate common vulnerabilities.**
- Broken Access Control: enforce server-side authorization checks, use principle of least privilege.
- Cryptographic Failures: use strong, up-to-date algorithms (AES-256, TLS 1.3), never store plaintext passwords.
- Injection (SQL, XSS): use parameterized queries, output encoding, and Content Security Policy (CSP) headers.
- Insecure Design: adopt threat modeling during design, implement security by design principles.
- Security Misconfiguration: disable unnecessary features, use secure defaults, keep dependencies updated.
- Vulnerable Components: maintain an inventory of third-party libraries, use automated scanning tools.
- Authentication Failures: implement multi-factor authentication, enforce strong password policies, use rate limiting.
- Software and Data Integrity Failures: verify digital signatures, use integrity checks for CI/CD pipelines.
- Logging and Monitoring Failures: implement centralized logging, set up alerts for suspicious activity.
- Server-Side Request Forgery (SSRF): validate and sanitize all URLs, restrict outbound network access.

**Q: What is XSS and how do you prevent it?**
- Stored XSS: attacker injects malicious script that is persisted in the database and served to other users (e.g., in comments).
- Reflected XSS: malicious script is included in the URL or form input and immediately reflected back in the response.
- DOM-based XSS: script manipulates the DOM directly without server interaction (e.g., document.write with user input).
- Prevention: always escape/encode user input before rendering, use Content Security Policy (CSP) to restrict script sources, and use frameworks that auto-escape (React, Angular).

**Q: How should passwords be stored securely?**
- Never store plaintext passwords; use a slow, salted hash function designed for passwords.
- Use algorithms like bcrypt, scrypt, or Argon2, which incorporate a salt and a work factor (cost) to resist brute force and rainbow table attacks.
- bcrypt uses Blowfish with a configurable cost factor; scrypt adds memory hardness to resist GPU attacks; Argon2 (winner of the Password Hashing Competition) provides both memory and time hardness.
- Use a unique random salt per password (bcrypt handles this internally) so identical passwords produce different hashes.
- Adjust the cost factor over time as hardware improves to maintain adequate resistance.

**Q: What is the difference between HTTPS and HTTP, and how does the TLS handshake establish a secure connection?**
- HTTP sends data in plaintext; HTTPS encrypts all data using TLS, preventing eavesdropping and tampering.
- The client sends a ClientHello with supported cipher suites and a random number.
- The server responds with its certificate, chosen cipher suite, and its own random number.
- The client validates the server's certificate chain against trusted root CAs.
- The client generates a pre-master secret, encrypts it with the server's public key, and sends it.
- Both parties derive session keys from the pre-master secret and both random numbers.
- TLS 1.3 simplifies this to one round trip and supports 0-RTT for resumed sessions.

**Q: What is CORS and how does the same-origin policy protect users?**
- The same-origin policy (SOP) is a browser security mechanism that restricts web pages from making requests to a different domain, protocol, or port than the one that served the page. It prevents malicious sites from reading data from authenticated sessions on other sites.
- Cross-Origin Resource Sharing (CORS) is a relaxation of SOP, controlled by the server via HTTP headers. The server specifies which origins are allowed (Access-Control-Allow-Origin), which methods are permitted (Access-Control-Allow-Methods), and which headers can be sent (Access-Control-Allow-Headers).
- For non-simple requests (e.g., PUT, DELETE, or requests with custom headers), the browser sends a preflight OPTIONS request first to verify permissions.
- Common misconfigurations: using Access-Control-Allow-Origin: * with credentials enabled, or reflecting the Origin header without validation, which effectively disables SOP.

**Q: How does session-based authentication differ from token-based authentication?**
- Session-based auth: the server creates a session (stored in memory, database, or Redis) after the user logs in, and sends a session ID via a cookie. On each request, the server looks up the session to identify the user.
  - Pros: sessions can be revoked server-side; the token (cookie) is just an opaque identifier.
  - Cons: requires server-side storage; does not scale well across multiple servers without a shared session store; vulnerable to CSRF.
- Token-based auth (JWT): the server issues a signed JWT containing claims (user ID, roles, expiration). The client stores the token (typically in localStorage) and sends it in the Authorization header.
  - Pros: stateless (no server-side session storage); easier to scale across services; suitable for SPAs and mobile apps.
  - Cons: tokens cannot be easily revoked before expiration; JWT payload is base64-encoded (not encrypted), so do not store sensitive data; vulnerable to XSS if stored in localStorage.
- Hybrid approaches: use a short-lived access token (JWT) with a long-lived refresh token stored in an httpOnly cookie.

## Quick Reference Table

| Attack | Description | Primary Mitigation |
|---|---|---|
| SQL Injection | Untrusted input in SQL queries | Parameterized queries, ORM |
| XSS | Injecting scripts into web pages | Output encoding, CSP headers |
| CSRF | Forged requests from authenticated users | Anti-CSRF tokens, SameSite cookies |
| DDoS | Overwhelming a service with traffic | Rate limiting, CDN, WAF |
| Man-in-the-Middle | Intercepting communication | TLS/HTTPS, certificate pinning |
| Brute Force | Repeatedly guessing passwords | Rate limiting, account lockout, bcrypt |
| Clickjacking | Tricking user into clicking hidden elements | X-Frame-Options header, CSP |
