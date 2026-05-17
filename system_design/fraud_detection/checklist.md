# Design a Fraud Detection System — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] What type of fraud? (card-present, card-not-present, account takeover, first-party)
  - [ ] What is the latency budget? (100ms? 50ms?)
  - [ ] What are the approximate costs of FN vs FP? (drives the threshold formula)
  - [ ] What scale? (TPS, peak TPS)
  - [ ] What regulatory requirements apply? (explainability, PCI-DSS, data retention)
- [ ] List functional requirements (3-5 items):
  - [ ] Score every transaction for fraud probability in real-time
  - [ ] Block, allow, or flag for review based on score
  - [ ] Provide explainability for declined transactions
  - [ ] Continuously learn from confirmed fraud labels
  - [ ] Detect coordinated fraud rings
- [ ] List non-functional requirements (latency, availability, scale):
  - [ ] Low latency: p99 < 100ms end-to-end
  - [ ] Scale: handle 1K-5K TPS (up to 24K at Visa scale)
  - [ ] Handle extreme class imbalance (~0.1% fraud rate)
  - [ ] Resist adversarial drift
  - [ ] Satisfy regulatory constraints (SHAP explanations, PCI-DSS)
- [ ] State your scale estimates:
  - [ ] ~0.1% base fraud rate (1 in 1,000)
  - [ ] C_FN ~$535 (avg fraud + chargeback), C_FP ~$100 (CLV x churn)
  - [ ] ~1K TPS average, ~5K TPS peak
  - [ ] Label delay: 7-30 days for confirmed fraud

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw a box diagram: Payment Gateway -> Rules Engine -> [Feature Store + GBDT Scorer] -> [Deep Model (borderline)] -> Decision
- [ ] Identify the main operations and their access patterns:
  - [ ] `POST /transactions/score` — score a transaction (real-time, latency-critical)
  - [ ] `GET /transactions/{id}/explain` — get decline explanation (async, low QPS)
  - [ ] `POST /labels` — submit confirmed fraud label (async, moderate QPS)
  - [ ] `POST /rules` — update fraud rules (admin, low QPS)
- [ ] Note the multi-stage cascade and latency budget:
  - [ ] Stage 1: Rules (~3ms, 100% traffic)
  - [ ] Stage 2: Feature fetch + GBDT (~25ms, ~30% traffic)
  - [ ] Stage 3: Entity embedding + deep model (~40ms, ~2% traffic)
  - [ ] Total p99: ~100ms
- [ ] Present the diagram and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain the multi-stage cascade and justify each stage:
  - [ ] Stage 1 — Rules engine: in-memory hash lookups, blacklists, velocity limits (<5ms)
  - [ ] Stage 2 — GBDT (LightGBM): primary ML scorer on tabular + velocity features (~10ms)
  - [ ] Stage 3 — Deep model: shallow MLP on GNN entity embeddings for borderline cases (~35ms)
  - [ ] Only ~2% of traffic reaches Stage 3 (borderline scores between two thresholds)
- [ ] Define the decision threshold formula:
  - [ ] Optimal threshold: tau = C_FP / (C_FN + C_FP)
  - [ ] Typical result: ~0.157 (block if P(fraud) > 15.7%)
  - [ ] Requires calibrated probabilities (Platt scaling or isotonic regression)
- [ ] Explain why GBDTs over deep learning for the primary scorer:
  - [ ] Faster inference (~10ms vs ~30ms), naturally calibrated, handles missing values, SHAP interpretability, faster training
- [ ] Sketch the feature families and their serving latencies:
  - [ ] Transactional: amount, merchant_category, is_international (~0ms, from request)
  - [ ] Velocity: tx_count_1h, amount_sum_1h via Flink -> Redis (~3ms)
  - [ ] Behavioral: avg_amount_30d, typical_hours from Feast online store (~5ms)
  - [ ] Device/network: device_age, ip_risk_score, geo_velocity (~8ms)
  - [ ] Graph: fraud ring embeddings from pre-computed GNN (~5ms lookup)
- [ ] Walk through the main flow end-to-end:
  - [ ] Transaction arrives -> Rules check -> if passes, fetch features from Redis (pipelined) -> GBDT scores -> if borderline, fetch GNN embedding + run deep model -> apply threshold -> decision

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss class imbalance handling:
  - [ ] scale_pos_weight = n_negative / n_positive in LightGBM (e.g., 999)
  - [ ] If downsampling: apply Bayes' theorem odds-ratio correction to recalibrate
  - [ ] Use PR-AUC as primary offline metric (not ROC-AUC, which is distorted at 0.1% base rate)
- [ ] Explain suppression bias and mitigation:
  - [ ] Model blocks suppress ground truth labels -> compounding selection bias
  - [ ] Mitigation: exploration budget (approve ~0.1% of borderline declines), counterfactual logging with IPS
- [ ] Discuss graph neural networks for fraud rings:
  - [ ] Nodes: cards, accounts, devices, IPs, merchants
  - [ ] GraphSAGE: aggregate 1-hop and 2-hop neighborhood info into entity embeddings
  - [ ] Embeddings pre-computed hourly, stored in Redis for fast lookup
  - [ ] Catches coordinated fraud invisible to transaction-level features
- [ ] Address label delay:
  - [ ] Three label sources: chargebacks (14-30 day delay, high confidence), analyst reviews (same-day, expensive), rule triggers (immediate, noisy)
  - [ ] Never evaluate on transactions from the last 30 days (incomplete labels)
  - [ ] Dollar-weighted training samples (high-value fraud matters more)
- [ ] Explain adversarial drift and model monitoring:
  - [ ] Champion/challenger deployment with automated canary on precision degradation
  - [ ] Feature distribution PSI alerts, fraud rate monitoring by merchant category
  - [ ] Calibration drift: monthly reliability diagrams, Platt scaling recalibration
- [ ] Address failure modes:
  - [ ] Adversarial drift: faster retraining, adversarial eval set
  - [ ] Suppression bias: exploration holdout, counterfactual logging
  - [ ] Training-serving skew: shared feature registry (Feast), shadow mode
  - [ ] Model monoculture: diverse model families, independent training pipelines

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made and why (GBDT over DL for latency/calibration, cascade over single model for cost)
- [ ] Mention what you would improve with more time (GNN real-time inference, active learning loop, multi-region deployment)
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
