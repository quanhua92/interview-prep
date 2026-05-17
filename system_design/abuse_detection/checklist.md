# Design an Abuse Detection System — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] Which abuse types are in scope: credential stuffing, ATO, bot scraping, fake accounts, fraud rings, or all?
  - [ ] What is the latency band: login-path (sub-20ms sync) vs async post-login (seconds to hours)?
  - [ ] What is the user friction budget: max step-up auth rate the product team will tolerate?
  - [ ] Are there regulatory constraints: SMS OTP legality, data localization, GDPR/CCPA for behavioral telemetry?
  - [ ] What are the label sources: support tickets, chargebacks, honeypots, breach intel?
- [ ] List functional requirements (3-5 items):
  - [ ] Detect credential stuffing and ATO on the login path in real time
  - [ ] Identify bot traffic including headless browsers and automated scripts
  - [ ] Enforce velocity limits per entity (IP, device, user, ASN) across rolling windows
  - [ ] Discover fraud rings via shared infrastructure (device graph, phone, IP)
  - [ ] Apply tiered mitigations calibrated to risk score and user segment
- [ ] List non-functional requirements (latency, availability, scale):
  - [ ] Sync path: sub-20ms p99 for pre-auth checks
  - [ ] Velocity lookups: sub-5ms p99, 100K+ req/sec
  - [ ] False positive budget: <0.5% challenge rate on legitimate users
  - [ ] Adversarial robustness: defenses must evolve as attackers A/B test
- [ ] State your scale estimates (users, requests, storage):
  - [ ] ~100M+ daily logins
  - [ ] ~100K+ requests/sec at peak for velocity checks
  - [ ] ~millions of accounts/devices, billions of graph edges
  - [ ] ~Redis: sorted sets per entity per action, TTL-bucketed across 4 window sizes
  - [ ] ~Graph embeddings: 128-dim vectors per account, cached 24h in Redis

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw a simple box diagram: Client -> Edge Filter -> [Velocity Engine + Device Intel] -> Risk Scorer -> Mitigation Router -> (async) Graph Engine -> Feedback Loop
- [ ] Identify the main operations and their access patterns:
  - [ ] Login/auth path: sync velocity + device check + GBM scoring (sub-20ms, highest QPS)
  - [ ] Post-login async: graph traversal, ring detection, embedding updates (minutes to hours)
  - [ ] Abuse reporting: async label ingestion for model retraining
  - [ ] Admin queries: ring investigation, risk score inspection
- [ ] Note the sync vs async boundary and where caching helps:
  - [ ] Sync path: Redis velocity + cached device fingerprint + GBM score (stateless model inference)
  - [ ] Async path: Neo4j/Neptune graph queries + GNN embeddings cached back to Redis
  - [ ] Edge filter: TLS/JA3 + ASN blocklist blocks datacenter bots in ~1ms before expensive checks
- [ ] Present the diagram and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain the sync/async split and justify:
  - [ ] Sync (sub-20ms): Redis velocity pipelined checks (~2-3ms) + device cache (~2ms) + GBM scoring (~5-8ms)
  - [ ] Async (minutes to hours): GNN embedding, deep graph traversal, ring clustering
  - [ ] Cached results from async jobs feed back into sync path on next request
- [ ] Define API endpoints with method, path, request/response:
  - [ ] `POST /api/auth/login` -> inline risk check, returns allow/challenge/block
  - [ ] `GET /api/risk/{account_id}` -> cached risk score + embedding
  - [ ] `POST /api/risk/challenge` -> submit CAPTCHA/step-up result
  - [ ] `GET /api/velocity/{entity_type}/{entity_id}` -> rolling window counts
  - [ ] `POST /api/report/abuse` -> user-reported abuse event
- [ ] Sketch the database schema:
  - [ ] Table `account_risk`: account_id, risk_score, risk_embedding (128-dim), device_fingerprint_hash, last_updated
  - [ ] Table `velocity_windows` (Redis): entity_type, entity_id, action_type, window, count, distinct_count
  - [ ] Table `graph_edges`: source_account, target_account, edge_type (shares_device, shares_ip, shares_phone, referral), weight, detected_at
- [ ] Discuss storage trade-offs:
  - [ ] Velocity: Redis sorted sets with timestamp scores, TTL auto-expiration, pipelined batch lookups
  - [ ] Graph: Neo4j/Neptune for relationship traversal, GNN for embeddings, results cached in Redis
  - [ ] Device fingerprints: computed once per session (~3-5ms), cached in session store
  - [ ] HyperLogLog for distinct-entity cardinality (~12KB regardless of scale)
- [ ] Walk through the main flow end-to-end:
  - [ ] Login request arrives -> Edge filter checks TLS/JA3 + ASN blocklist (~1ms)
  - [ ] Velocity engine: pipelined Redis lookups for IP/device/ASN across windows (~2-3ms)
  - [ ] Device intelligence: fingerprint lookup + session cache (~2ms)
  - [ ] Risk scorer: GBM produces 0-1 score (~5-8ms)
  - [ ] Mitigation router: maps score to action (allow/invisible CAPTCHA/visible CAPTCHA/step-up/block)
  - [ ] Async: Kafka event triggers graph traversal, GNN embedding update, ring detection
  - [ ] Feedback loop: shadow-mode scoring, honeypot labels, breach intel feed model retraining

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss credential stuffing detection:
  - [ ] Failed login ratio per IP/device, ASN datacenter flags, JA3 TLS fingerprint mismatch
  - [ ] Geo-velocity impossibility (NYC to Singapore in 10 min)
  - [ ] Breach dataset membership (HaveIBeenPwned hashed comparison)
  - [ ] HTTP header anomalies (Python requests library defaults vs real browsers)
- [ ] Explain bot detection signals:
  - [ ] Headless browser: navigator.webdriver, CDP artifacts, WebGL SwiftShader, JA4 TLS mismatch
  - [ ] Behavioral: action timing precision (machine-regular intervals), dwell time (sub-100ms = bot), engagement ratio anomalies
  - [ ] Multi-layer pipeline: TLS filter -> device fingerprint -> behavioral ML, each layer progressively more expensive
- [ ] Detail Redis velocity architecture:
  - [ ] Sorted sets with timestamp scores, ZADD + ZCOUNT for windowed counts
  - [ ] Pipelining: batch 5-10 checks in single roundtrip (~2-3ms vs 10ms sequential)
  - [ ] Sharding: consistent hashing across Redis cluster
  - [ ] Hash entity IDs in key names to prevent enumeration attacks
  - [ ] Window trade-offs: 1m catches bursts, 24h catches slow-drip, combine with weighted scoring
- [ ] Discuss graph-based fraud ring detection:
  - [ ] Shared infrastructure edges: device, phone, IP, payment method
  - [ ] Union-find for connected components: accounts sharing >=2 edges grouped into cluster
  - [ ] Bulk-disable clusters with >=70% confirmed abuse (ring-level, not account-level)
  - [ ] Offline GNN (GraphSAGE/GCN) training, 128-dim embeddings cached in Redis 24h TTL
  - [ ] Online sync path: lightweight embedding lookup (~2ms) + GBM scoring (~5-8ms)
- [ ] Address the delayed label problem:
  - [ ] Blocking stops negative label stream, models starve on hard positives
  - [ ] Shadow scoring: score but don't enforce, preserve label diversity
  - [ ] Honeypot accounts: clean positive labels uncontaminated by reporting bias
  - [ ] Temporal holdouts respecting 30-90 day chargeback propagation lag
- [ ] Discuss mitigation hierarchy and product trade-offs:
  - [ ] Silent -> invisible CAPTCHA -> visible CAPTCHA -> step-up auth -> hard block
  - [ ] FIDO2/passkeys: fundamentally change economics (no password to stuff), recovery flow becomes new attack surface
  - [ ] Rate of step-up challenges is a product KPI: optimize friction curve, not just detection AUC
  - [ ] Fairness audit: FPR parity across user segments (shared-device households, VPN users)

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made and why (sync vs async boundary, friction vs security, label quality)
- [ ] Mention what you would improve with more time (streaming GNN via Flink, cross-platform device graph, adversarial robustness)
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
