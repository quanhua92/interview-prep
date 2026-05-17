# Design an Ad Click Prediction System — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] Are we optimizing for clicks, conversions, or value?
  - [ ] Which ad surfaces (feed, search, stories) and what is the latency budget?
  - [ ] What are the label delays for click vs conversion?
  - [ ] What is the attribution window (7d, 30d)?
  - [ ] Are we in a privacy-constrained environment (post-ATT, cookieless)?
- [ ] List functional requirements (3-5 items):
  - [ ] Predict click probability (pCTR) for each ad impression in real time
  - [ ] Serve scores within ~50ms for thousands of candidate ads
  - [ ] Calibrate predictions so they match realized click rates
  - [ ] Feed scores into an auction to determine ad ranking and pricing
  - [ ] Handle delayed conversion labels with configurable attribution windows
- [ ] List non-functional requirements (latency, availability, scale):
  - [ ] Low latency: ~50ms p99 end-to-end inference
  - [ ] High throughput: billions of impressions per day
  - [ ] Calibration accuracy: per-segment COEC close to 1.0
  - [ ] Model freshness: hourly or streaming online updates
  - [ ] Robustness to distribution shift and feedback loops
- [ ] State your scale estimates (users, requests, storage):
  - [ ] Billions of impressions/day
  - [ ] Tens of thousands of candidate ads per request
  - [ ] 20-50 categorical features (millions of unique values each)
  - [ ] 10-30 dense features
  - [ ] Embedding tables: hundreds of GB to TB

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw a simple box diagram: Client -> Ad Server -> [Candidate Generator -> Ranker -> Calibrator -> Auction] -> Response
- [ ] Identify the main operations and their access patterns:
  - [ ] `POST /api/predict` — score a batch of candidate ads (compute-heavy, latency-critical)
  - [ ] `GET /api/auction` — run auction over scored candidates (read, latency-critical)
  - [ ] `POST /api/impressions` — log impression (write, async)
  - [ ] `POST /api/clicks` — log click (write, async)
  - [ ] `POST /api/conversions` — log conversion (write, delayed)
- [ ] Note the online/offline split:
  - [ ] Offline: batch training on impression logs, daily or hourly
  - [ ] Online: real-time feature serving and inference at request time
  - [ ] Calibration: recomputed daily on rolling window of production logs
- [ ] Present the diagram and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain model architecture choice and justify:
  - [ ] GBDT (LightGBM): simpler, faster iteration, good baseline, works with handcrafted features
  - [ ] DLRM: learns second-order feature interactions via dot-product layer, better AUC at scale, 10-100x more expensive to serve
  - [ ] Hybrid: GBDT for retrieval stage, DLRM for final ranking stage
- [ ] Explain multi-stage serving pipeline:
  - [ ] Stage 1: Candidate generation / retrieval (lightweight filters, thousands -> hundreds)
  - [ ] Stage 2: Light ranker (simple model, hundreds -> tens)
  - [ ] Stage 3: Full ranker (DLRM or GBDT, tens -> final scores)
  - [ ] Stage 4: Calibration (per-segment isotonic regression)
  - [ ] Stage 5: Auction (GSP with quality adjustment)
- [ ] Define API endpoints with method, path, request/response:
  - [ ] `POST /api/predict` -> `{"ad_scores": [{"ad_id": "...", "pctr": 0.03, "calibrated_pctr": 0.028}]}`
  - [ ] `GET /api/auction` -> `{"winners": [{"ad_id": "...", "price": 1.23, "rank": 1}]}`
  - [ ] `POST /api/impressions` -> `{"impression_id": "..."}`
  - [ ] `POST /api/clicks` -> `{"click_id": "..."}`
- [ ] Sketch the database schema:
  - [ ] Table `impressions`: `impression_id`, `user_id`, `ad_id`, `placement`, `predicted_pctr`, `shown_at`
  - [ ] Table `clicks`: `click_id`, `impression_id` (FK), `clicked_at`
  - [ ] Table `conversions`: `conversion_id`, `click_id` (FK), `value`, `converted_at`
  - [ ] Table `calibration_buckets`: `segment_key`, `isotonic_mapping`, `updated_at`
- [ ] Discuss feature engineering for sparse, high-cardinality data:
  - [ ] Hash trick: map categorical IDs to fixed-size embedding tables (e.g., 10M slots)
  - [ ] Embedding dimension: 64-128 per feature
  - [ ] Dense features: normalization + bottom MLP
  - [ ] Target encoding for rare/low-frequency features
  - [ ] Cyclical encoding for temporal features (sin/cos for hour_of_day)
- [ ] Walk through the main flow end-to-end:
  - [ ] Serving: user visits page -> candidate ads retrieved -> ranked by model -> calibrated -> auction selects winners -> ads displayed
  - [ ] Training: impression and click logs collected -> labels joined with attribution window -> model retrained on fresh data -> calibration recomputed -> new model deployed with shadow evaluation

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss calibration in depth:
  - [ ] Why raw pCTR breaks auction economics (systematic over/underestimation by segment)
  - [ ] Isotonic regression: piecewise-constant monotonic mapping, arbitrary correction shapes, O(log N) lookup
  - [ ] Platt scaling: logistic on top of raw scores, faster but less flexible, fails on non-linear miscalibration
  - [ ] Per-segment calibration: separate mapping per vertical x placement x cohort, 30-50% RMSE reduction
  - [ ] COEC (Click-Over-Expected-Click): key metric, tracked per stratum as launch gate
- [ ] Explain the feedback loop problem:
  - [ ] Serving ads based on predictions changes which ads get impressions
  - [ ] Training distribution becomes endogenous to the model
  - [ ] Mitigation: exploration budget (1-3% traffic), propensity-weighted training
- [ ] Handle delayed feedback:
  - [ ] Conversion labels arrive hours to days after impression
  - [ ] Use windowed labels with configurable attribution window (7d, 30d)
  - [ ] Delayed loss weighting to prevent false negatives from early stopping
  - [ ] Lag-aware backtests to detect offline/online metric divergence
- [ ] Discuss auction design:
  - [ ] GSP with quality adjustment: `score = bid x pCTR x quality`
  - [ ] Pricing: `price = score_next / (pCTR x quality) + epsilon`
  - [ ] Reserve price based on opportunity cost of organic content
  - [ ] Pacing (PID loop or token bucket) depends on accurate pCTR
- [ ] Address ESMM / CTCVR for full-funnel modeling:
  - [ ] Pure CVR model suffers sample selection bias (trained only on clicks) and data sparsity
  - [ ] ESMM: model `pCTCVR = pCTR x pCVR` with shared embeddings, every impression contributes gradient
  - [ ] Auction score becomes `bid x pCTCVR x quality` for conversion-optimized advertisers
- [ ] Discuss privacy-preserving architecture (2024+):
  - [ ] Dual-regime: identity-rich path (first-party data) + identity-poor path (contextual features)
  - [ ] On-device inference: models quantized to <100MB for Core ML / NNAPI
  - [ ] Aggregated attribution: SKAdNetwork / Privacy Sandbox reporting is noisy and delayed
  - [ ] Both cookied and cookieless paths must coexist after Google's 2024 reversal
- [ ] Explain system evolution v1 to v3:
  - [ ] v1: batch GBDT, daily retraining, single global calibration bucket
  - [ ] v2: online feature service, per-segment calibration, multi-stage serving
  - [ ] v3: multi-objective DLRM with exploration control, propensity-weighted training
  - [ ] Each upgrade triggered by specific metric degradation (calibration RMSE > 0.02, exposure Gini rising, etc.)

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made and why (GBDT vs DLRM, global vs per-segment calibration, click vs conversion optimization)
- [ ] Mention what you would improve with more time (online learning, cold start handling, multi-task heads)
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
