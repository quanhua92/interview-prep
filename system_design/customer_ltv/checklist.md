# Design a Customer LTV System — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] Is the business model subscription (contractual), e-commerce (non-contractual), or hybrid?
  - [ ] How is churn defined -- explicit cancel event or inactivity threshold (e.g., 90 days)?
  - [ ] What is the CLV horizon -- 12-month, 5-year, or lifetime?
  - [ ] What is the primary use case -- acquisition bidding, CRM targeting, credit decisions, or all three?
  - [ ] How do we handle new users with minimal history (cold-start)?
- [ ] List functional requirements (3-5 items):
  - [ ] Estimate per-customer CLV with calibrated dollars and uncertainty intervals (p10/p50/p90)
  - [ ] Compute churn scores (ranking) and retention predictions (calibrated probabilities)
  - [ ] Estimate uplift / incremental value from treatments (CATE) for CRM campaigns
  - [ ] Feed downstream systems: ads bidding, CRM send frequency, credit limits
  - [ ] Handle cold-start for new users with limited behavioral data
- [ ] List non-functional requirements (latency, availability, scale):
  - [ ] Sub-200ms real-time scoring for in-session interventions (cancel-flow offers)
  - [ ] Nightly batch scoring for CRM campaigns and capacity planning
  - [ ] Calibrated dollar output for bid optimization (not just rank ordering)
  - [ ] Monthly retrain with drift monitoring; quarterly recalibration
- [ ] State your scale estimates (users, requests, storage):
  - [ ] 50M+ customers (e.g., Shopify-scale marketplace)
  - [ ] Millions of daily score refreshes for CRM and ads platforms
  - [ ] Sparse purchase histories for non-contractual; rich event logs for subscription
  - [ ] Cold-start: new users need scores from day one with hierarchical pooling

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw a simple box diagram: Client -> LB -> [CLV Service / Churn Service / Uplift Service] -> [Feature Store + Model Store] -> [Cache + DB]
- [ ] Identify the main operations and their access patterns:
  - [ ] `GET /api/customers/{id}/clv` -- get CLV estimate (read, batch-precomputed + real-time)
  - [ ] `GET /api/customers/{id}/churn-score` -- get churn rank (read, nightly batch)
  - [ ] `POST /api/customers/{id}/treatment-uplift` -- get CATE for a treatment (read, model inference)
  - [ ] `POST /api/campaigns/allocate` -- optimize budget allocation (write, daily batch)
  - [ ] `POST /api/conversions/value` -- fire CLV value to ads platform (write, real-time)
- [ ] Note the read:write ratio and where caching helps:
  - [ ] Scoring reads dominate (millions of lookups from CRM/ads)
  - [ ] Cache precomputed CLV and churn scores in Redis for active users
  - [ ] Feature store (Tecton/Feast) with streaming Kafka updates for real-time features
- [ ] Present the diagram and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain model family choice and justify by business type:
  - [ ] Non-contractual: BG/NBD + Gamma-Gamma (generative assumptions beat RFM on sparse data)
  - [ ] Contractual: Cox PH for subscription tenure (handles right-censoring via partial likelihood)
  - [ ] Production path: probabilistic baseline + DNN residual on top
- [ ] Explain label construction and why leakage matters:
  - [ ] Label is future spend from t0 forward, NOT historical revenue to date
  - [ ] Point-in-time feature snapshots are mandatory
  - [ ] Right-censored customers contribute to likelihood but not response variable
- [ ] Define API endpoints with method, path, request/response:
  - [ ] `GET /api/customers/{id}/clv` -> `{"estimate": 450.0, "p10": 200, "p50": 450, "p90": 800, "model_version": "v3"}`
  - [ ] `GET /api/customers/{id}/churn-score` -> `{"score": 72, "updated_at": "..."}`
  - [ ] `POST /api/customers/{id}/treatment-uplift` -> `{"cate": 15.0, "treatment": "10%_discount"}`
  - [ ] `POST /api/campaigns/allocate` -> `{"treated_ids": [...], "total_uplift": 50000, "budget_used": 5000}`
- [ ] Sketch the database schema:
  - [ ] Table `customer_scores`: `customer_id` (PK), `clv_estimate`, `clv_p10/p50/p90`, `churn_score`, `retention_prob`, `model_version`, `score_timestamp`
  - [ ] Table `uplift_cache`: `customer_id`, `treatment_id`, `cate`, `model_version`
  - [ ] Table `treatment_log`: `customer_id`, `treatment_id`, `outcome`, `timestamp` (for RCT data collection)
- [ ] Discuss batch vs real-time scoring trade-off:
  - [ ] Batch (nightly): rank-stable use cases like CRM campaigns, capacity planning. LightGBM on full feature set.
  - [ ] Real-time (<200ms): in-session interventions. GBDT on CPU (LightGBM ONNX) with feature store lookup.
  - [ ] Calibration monitoring: PSI on features, isotonic recalibration quarterly
- [ ] Walk through the main flow end-to-end:
  - [ ] CLV computation: nightly batch trains BG/NBD + Gamma-Gamma -> scores all customers -> writes to Redis + DB -> fires conversion values to ads platforms for stable customers
  - [ ] Cancel-flow intervention: user hits cancel -> real-time churn score from feature store + GBDT -> if uplift > threshold, surface personalized discount offer -> log treatment/outcome for future uplift model retraining

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss calibration strategy:
  - [ ] PIT histograms and calibration error by decile (not just aggregate RMSE)
  - [ ] Fat-tailed CLV errors hide catastrophic miscalibration in high-value segment
  - [ ] Isotonic recalibration on rolling holdout cohort quarterly
  - [ ] Pin model version generating values; ramp new models over 2-week windows to avoid bid algorithm shock
- [ ] Explain uplift modeling approach:
  - [ ] T-learner: separate models per treatment arm, simple to audit
  - [ ] X-learner: cross-fit counterfactuals for imbalanced treatment sizes
  - [ ] Causal forest: honest splitting with confidence intervals for complex interactions (N > 500K)
  - [ ] Training requires randomized experiments (A/B tests); observational data needs propensity score adjustment
- [ ] Address budget allocation under constraints:
  - [ ] Greedy (sort by uplift/cost): quick baseline but ignores diminishing returns
  - [ ] Integer programming (Gurobi/OR-Tools): optimal with budget, fairness, per-user cap constraints
  - [ ] Thompson sampling: online learning with posterior uncertainty for real-time allocation
- [ ] Handle cold-start problem:
  - [ ] Hierarchical Bayesian partial pooling across channel, geography, product tier as shrinkage prior
  - [ ] Default to global mean only as last resort (over-bids on low-value channels)
- [ ] Discuss privacy-first integration (2024-2026 era):
  - [ ] Apple ATT / SKAdNetwork: CLV discretized into 6-bit log-scaled buckets; rank ordering matters more than exact dollars
  - [ ] Google Privacy Sandbox: lose per-user conversion values; shift to audience targeting with high-CLV lookalike seeds
  - [ ] Only upload calibrated values (post isotonic, MAE <= 15%) to ads platforms
- [ ] Address multi-objective optimization:
  - [ ] LTV vs engagement tradeoffs via weighted scalarization or constrained optimization
  - [ ] Short-term CLV optimization can harm long-term value; use proxy metrics (NPS, engagement) as regularizers

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made and why
- [ ] Mention what you would improve with more time
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
