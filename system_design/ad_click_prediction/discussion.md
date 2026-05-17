# Design an Ad Click Prediction System

Source: [Ad Click Prediction (CalibreOS)](https://www.calibreos.com/learn/mlsd-ad-click-prediction)

## One-Liner
Build a production CTR prediction system that estimates ad click probability under strict latency budgets, feeds calibrated scores into an auction, and maximizes long-term ad revenue while protecting user experience.

## Functional Requirements
- Predict click probability (pCTR) for each ad impression in real time
- Serve scores within ~50ms for tens of thousands of candidate ads per request
- Calibrate raw model outputs so predicted probabilities match realized click rates
- Support multi-stage ranking: retrieval, light ranking, full ranking, calibration, auction
- Handle delayed conversion labels (hours to days after impression)
- Support multiple ad surfaces: feed, search, stories

## Non-Functional Requirements
- Inference latency: ~50ms end-to-end (p99)
- Scale: billions of impressions per day (Meta/Google scale)
- Calibration accuracy: per-segment COEC close to 1.0
- Model freshness: online learning with hourly or streaming updates
- Robustness to distribution shift, feedback loops, and privacy regime changes

## Key Scale Questions
- Billions of impressions/day, each requiring a pCTR score
- 20-50 categorical features with millions of unique values each (user_id, ad_id, etc.)
- 10-30 dense features (bid amount, historical CTR, time-of-day)
- Embedding tables totaling hundreds of GB to several TB
- Read-heavy serving path with strict latency SLO
- Conversion labels arrive hours to days after the impression (delayed feedback)

## Core Components
- **Feature Service**: delivers session-level features (recency signals, last ad category clicked) at sub-10ms
- **Candidate Generator (Retrieval)**: narrows tens of thousands of ads to a manageable set via lightweight filtering
- **Ranking Model (GBDT or DLRM)**: scores each candidate ad with pCTR
- **Calibration Layer**: isotonic regression or Platt scaling per segment to correct systematic over/underconfidence
- **Auction Engine**: GSP or VCG-style auction that computes final ad ranking and pricing using `score = bid x calibrated_pCTR x quality_factor`
- **Training Pipeline**: offline batch training on impression logs + online incremental updates every 1-6 hours
- **Logging and Attribution**: impression and click event logging with configurable attribution windows (7d, 30d)

## Key Design Decisions

### Model Architecture: GBDT vs DLRM
- **GBDT (LightGBM)**: simpler to deploy, faster iteration, good baseline. Works well with handcrafted features. The go-to for v1 systems.
- **DLRM**: learns second-order feature interactions via dot-product layer, replacing manual cross-feature engineering. Better AUC at Meta/Google scale but 10-100x more expensive to serve. Memory-bandwidth bound, not compute bound.

### Calibration Strategy
- **Global calibration**: single isotonic regression over all predictions. Simpler but hides tail-segment drift.
- **Per-segment calibration**: separate isotonic regression per advertiser vertical, placement, and user cohort. Cuts calibration RMSE by 30-50% but adds routing latency.
- **Bias constraints in training loss**: add penalty term `lambda x sum_k(mean(pred_k) - mean(label_k))^2` to anchor model during training rather than relying solely on post-hoc correction.

### Handling Delayed Feedback
- Conversion labels arrive hours to days after the impression. Naive training overfits to recent clicks and misses conversions.
- Use configurable attribution windows (7d, 30d) and windowed labels with delayed loss weighting.
- Lag-aware backtests to catch offline/online metric divergence.

### Auction Design
- **GSP with quality adjustment**: `score = bid x pCTR x quality`. Winner pays minimum to maintain rank: `price = score_next / (pCTR x quality) + epsilon`.
- Quality factor penalizes low-quality ads (poor landing page, low relevance, policy violations).
- Reserve price based on opportunity cost of showing an ad vs organic content.
- Pacing (PID loop or token bucket) throttles spend to match daily budgets; depends on accurate pCTR.

### Privacy-Preserving Design (2024+)
- Dual-regime architecture: identity-rich path (first-party data) and identity-poor path (contextual features, cohort IDs).
- On-device inference for privacy-sensitive scoring: models must quantize to <100MB (INT8) for Core ML / NNAPI.
- Aggregated attribution via SKAdNetwork / Privacy Sandbox: noisy, delayed, batched conversion signals require noise-aware loss functions.

## API Endpoints
| Method | Path | Description |
|--------|------|-------------|
| POST | /api/predict | Score a batch of candidate ads with pCTR |
| GET | /api/auction | Run auction over scored candidates, return winners and prices |
| POST | /api/impressions | Log an impression event |
| POST | /api/clicks | Log a click event |
| POST | /api/conversions | Log a conversion event (delayed) |
| GET | /api/calibration/status | Check per-segment calibration health (COEC) |

## Database Schema
| Table | Column | Type | Notes |
|-------|--------|------|-------|
| impressions | impression_id | BIGINT | PK, Snowflake ID |
| impressions | user_id | BIGINT | User who saw the ad |
| impressions | ad_id | BIGINT | Ad shown |
| impressions | placement | VARCHAR | feed, search, stories |
| impressions | predicted_pctr | FLOAT | Model output at serve time |
| impressions | shown_at | TIMESTAMP | Impression time |
| clicks | click_id | BIGINT | PK |
| clicks | impression_id | BIGINT | FK to impressions |
| clicks | clicked_at | TIMESTAMP | Click time |
| conversions | conversion_id | BIGINT | PK |
| conversions | click_id | BIGINT | FK to clicks |
| conversions | value | DECIMAL | Conversion value |
| conversions | converted_at | TIMESTAMP | Conversion time |
| calibration_buckets | segment_key | VARCHAR | vertical x placement x cohort |
| calibration_buckets | isotonic_mapping | BLOB | Serialized lookup table |
| calibration_buckets | updated_at | TIMESTAMP | Last recalibration time |

## Deep Dive Topics
- **DLRM architecture details**: embedding layers for sparse categoricals, bottom MLP for dense features, dot-product interaction layer for second-order feature interactions, top MLP for final logit. Embedding tables sharded across GPUs/parameter servers.
- **Feature hashing (hash trick)**: map unbounded categorical IDs (100M+ user IDs) to fixed-size tables (10M slots) using MurmurHash3. Collision impact on AUC is typically <0.1%. Multi-hash embeddings reduce collision impact at Kx memory cost.
- **ESMM / CTCVR**: model click-through-conversion-rate as `pCTCVR = pCTR x pCVR` with shared embeddings and dual towers. Eliminates sample selection bias because every impression contributes gradient signal. Auction score becomes `bid x pCTCVR x quality`.
- **Feedback loop problem**: serving ads based on CTR predictions changes which ads get impressions, which changes future CTR estimates. The training distribution is endogenous to the model. Mitigate with exploration budget (1-3% traffic) and propensity-weighted training.
- **Position bias**: ads in slot 1 get inflated CTR. Correct via inverse propensity weighting or a position feature ablated at inference time.
- **Negative downsampling with probability correction**: train on a subsample of negatives, then correct predicted probabilities back at serving time.
- **System evolution v1 to v3**: batch GBDT baseline -> online features + staged serving -> multi-objective with exploration control. Each upgrade triggered by specific metric degradation.

## Follow-Up Variations
- How would you design the system to optimize for conversions (CPA) instead of clicks (CPC)?
- What changes when you add a new ad surface (e.g., stories) with very different engagement patterns?
- How do you handle a new advertiser with zero historical data (cold start)?
- How would you detect and mitigate calibration drift in real time?
- What happens to the system when Apple further restricts cross-app tracking?
- How do you design a multi-task model that jointly predicts click, conversion, and long-term user engagement?
- How would you A/B test a new ranking model without destabilizing the auction?
