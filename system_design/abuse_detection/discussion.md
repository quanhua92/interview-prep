# Design an Abuse Detection System

Source: [Abuse Detection (CalibreOS)](https://www.calibreos.com/learn/mlsd-abuse-detection)

## One-Liner
Build a cross-platform abuse detection system that scores user actions in real time to detect credential stuffing, account takeover, bot traffic, synthetic accounts, and fraud rings using velocity features, device fingerprints, and graph analysis.

## Functional Requirements
- Detect credential stuffing and account takeover (ATO) on the login path
- Identify bot traffic including headless browsers, scrapers, and automated scripts
- Enforce velocity limits per entity (IP, device, user, ASN) across rolling time windows
- Discover fraud rings and collusion clusters via shared infrastructure (device, phone, IP)
- Apply tiered mitigations: silent logging, invisible CAPTCHA, step-up auth, hard block
- Provide per-account risk scores that incorporate behavioral, device, and graph signals

## Non-Functional Requirements
- Sync (pre-auth) path latency under 20ms p99 to stay inside login SLO
- Async graph path can take minutes to hours for deep traversal
- Handle 100K+ requests/sec with sub-5ms velocity lookups
- False positive budget: even 0.5% challenge rate on 100M daily logins = 500K users interrupted
- Labels are sparse and delayed (chargebacks arrive 30-90 days later)
- Adversarial environment: attackers A/B test against defenses, static rules decay in days

## Key Scale Questions
- 100M+ daily logins across global user base
- 100K+ requests/sec at peak for velocity checks
- Redis velocity keys: one sorted set per entity per action type, TTL-bucketed across 1m/10m/1h/24h windows
- Graph queries: millions of nodes (accounts, devices, IPs), billions of edges (shared device, shared IP, referral)
- Device fingerprint entropy ~10^6 unique signatures per session
- Async GNN embedding jobs output 128-dim vectors cached in Redis with 24h TTL

## Core Components
- **Edge Filter**: TLS/JA3 fingerprint + ASN blocklist, blocks datacenter bots in ~1ms
- **Velocity Engine**: Redis sorted sets for rolling-window action counts per IP/device/user/ASN
- **Device Intelligence Service**: Canvas, WebGL, font fingerprints; emulator flags; JA3/JA4 TLS hash; HTTP header order; headless browser signals (`navigator.webdriver`, CDP artifacts)
- **Risk Scorer**: LightGBM or similar GBM on 50-100 features producing a calibrated 0-1 risk score
- **Graph Engine**: Neo4j or Neptune for ring detection; GNN (GraphSAGE/GCN) for 128-dim account embeddings; union-find for connected components
- **Behavioral Analysis**: Mouse telemetry, typing cadence, scroll patterns, session duration, dwell time
- **Mitigation Router**: Maps (risk_score, user_segment, account_value) to action: allow, invisible CAPTCHA, visible CAPTCHA, step-up auth, hard block
- **Feedback Loop**: Shadow-mode scoring, honeypot credentials, breach intel as weak labels for model retraining

## Key Design Decisions

### Sync Gate vs Async Graph
- **Sync path (sub-20ms)**: Redis velocity pipelined checks (5-10 lookups in ~2-3ms) + device fingerprint cache lookup (~2ms) + GBM scoring (~5-8ms). Must fit inside auth latency SLO.
- **Async path (minutes to hours)**: GNN embedding computation, deep graph traversal for ring detection, fraud ring clustering. Results cached as per-account risk vectors in Redis with 24h TTL, consumed by sync path on next request.

### Velocity Storage in Redis
- **Option A: Sorted sets with timestamp scores**: `ZADD` to insert, `ZCOUNT` for window range. TTL per key = max window. Pipelining batches multiple checks into one roundtrip.
- **Option B: HyperLogLog for cardinality**: `PFADD`/`PFCOUNT` for distinct-entity counts (e.g., distinct usernames tried per IP) using ~12KB regardless of cardinality.
- **Key patterns**: Hash IPs before key names to prevent enumeration; separate keyspaces per action type (`login`, `signup`, `password_reset`, `api_call`).

### Mitigation Hierarchy (Low to High Friction)
- **Silent**: Rate-limit IP/device, return cached fail-open responses, log for offline analysis (risk < 0.4)
- **Invisible challenge**: reCAPTCHA v3 / Cloudflare Turnstile score fused as a feature, not a hard gate (risk 0.3-0.6)
- **Visible CAPTCHA**: User solves puzzle; ~5% legitimate user abandonment; reserve for medium-high risk (risk 0.6-0.85)
- **SMS OTP step-up**: Deprecated by NIST SP 800-63B Rev 4 (2024) for high assurance; SS7/SIM-swap attacks bypass routinely
- **TOTP / Authenticator app**: Better than SMS, free, but recovery flows are a fraud vector
- **FIDO2/WebAuthn passkeys**: Phishing-resistant, cryptographic device-bound credentials. Fundamentally changes abuse economics: credential stuffing becomes impossible. Recovery flow becomes the new attack surface.
- **Hard block + manual review**: Account suspension with support ticket; reserved for confirmed abuse (risk > 0.95)

### Handling Delayed Labels
- Blocking stops the negative label stream; models starve on hard positives. Solutions: shadow scoring (score but don't enforce), honeypot accounts as clean positive labels, external breach intel (HaveIBeenPwned hashed comparison) as weak labels.
- Use temporal holdouts that respect label propagation lag (30-90 days for chargebacks).

## API Endpoints
| Method | Path | Description |
|--------|------|-------------|
| POST | /api/auth/login | Login with inline risk check (sync velocity + device + GBM) |
| GET | /api/risk/{account_id} | Get cached risk score and embedding for an account |
| POST | /api/risk/challenge | Submit CAPTCHA/step-up result, update risk state |
| GET | /api/velocity/{entity_type}/{entity_id} | Query velocity counts for an entity across windows |
| POST | /api/report/abuse | User-reported abuse event (async label ingestion) |
| GET | /api/graph/ring/{cluster_id} | Get accounts in a detected fraud ring (admin) |

## Database Schema
| Column | Type | Notes |
|--------|------|-------|
| account_id | BIGINT | PK, user account ID |
| risk_score | FLOAT | Cached 0-1 risk score |
| risk_embedding | BLOB(512) | 128-dim float vector from GNN |
| device_fingerprint_hash | VARCHAR(64) | SHA-256 of device signals |
| first_seen | TIMESTAMP | Account creation time |
| last_updated | TIMESTAMP | Risk score refresh time |

| Column | Type | Notes |
|--------|------|-------|
| entity_type | ENUM | ip, device, user, asn |
| entity_id | VARCHAR(128) | Hashed identifier |
| action_type | ENUM | login, signup, password_reset, api_call |
| window | ENUM | 1m, 10m, 1h, 24h |
| count | INT | Rolling window action count |
| distinct_count | INT | HyperLogLog cardinality estimate |

| Column | Type | Notes |
|--------|------|-------|
| source_account | BIGINT | FK to accounts |
| target_account | BIGINT | FK to accounts |
| edge_type | ENUM | shares_device, shares_ip, shares_phone, referral |
| weight | FLOAT | Connection strength |
| detected_at | TIMESTAMP | Edge creation time |

## Deep Dive Topics
- **Credential stuffing signals**: Failed login ratio per IP/device, ASN datacenter flags (Hetzner, OVH, AWS), JA3 TLS fingerprint mismatch with User-Agent, geo-velocity impossibility, breach dataset membership, HTTP header anomalies
- **Session hijacking detection**: Token replay from new device/IP, cookie theft patterns, sudden User-Agent change mid-session, geographic jump without VPN flag, activity spike inconsistent with baseline
- **Headless browser detection (2026)**: `navigator.webdriver` (trivially patched by puppeteer-stealth), CDP artifacts (Runtime.enable handlers), WebGL SwiftShader vs real GPU, JA4 TLS mismatch (Node.js OpenSSL vs Chrome BoringSSL), missing browser properties, DOM injection signatures from extensions
- **Behavioral biometrics**: Non-linear mouse trajectories with overshoot-correct vs straight-line bot paths; variable inter-key latency 100-300ms vs uniform 50ms bot typing; uneven scroll with backtracking vs linear constant-velocity; session dwell time 2-10s for humans vs sub-100ms for bots
- **Fraud ring detection**: Neo4j traversal for shared-device clusters among new accounts; union-find for connected components where accounts share >=2 edges; bulk-disable clusters with >=70% confirmed abuse; GNN embeddings propagate fraud/legit labels through edges
- **Adversarial robustness**: Withhold signals from challenge responses that help attackers calibrate; shadow-mode scoring to measure detection before enforcement; ring-level enforcement (suspend cluster, not just account) prevents whack-a-mole recovery
- **Fairness constraints**: Velocity and device signals have disparate impact on shared-device households and VPN users; audit false positive rate parity by user segment
- **Privacy**: Mouse/keyboard telemetry must be disclosed per GDPR/CCPA; store aggregate statistics or hashed representations, not raw XY coordinates (PII in some jurisdictions)

## Follow-Up Variations
- How would you handle a sudden spike in credential stuffing from a newly leaked breach dataset?
- What if attackers start using real browsers with human-like behavioral patterns (mouse movement, typing cadence)?
- How would you adapt the system for a marketplace where collusion rings coordinate review bombing?
- How do you balance fraud detection with user experience when false positives directly cause churn?
- What happens when an attacker compromises the device fingerprinting library itself?
- How would you migrate from rule-based velocity checks to ML-based scoring without disrupting existing protections?
