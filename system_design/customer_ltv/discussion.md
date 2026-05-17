# Design a Customer LTV System

Source: [Customer LTV (CalibreOS)](https://www.calibreos.com/learn/mlsd-customer-ltv)

## One-Liner
Build a production system that estimates discounted future customer value using probabilistic models, survival analysis, and uplift modeling to power acquisition bidding, CRM targeting, and credit decisions.

## Functional Requirements
- Estimate per-customer CLV (expected discounted future spend) with calibrated dollar output and uncertainty intervals (p10/p50/p90)
- Support subscription (contractual) and e-commerce/app (non-contractual) business models
- Compute churn scores (ranking) and retention predictions (calibrated probabilities) as distinct outputs
- Estimate incremental value from treatments (uplift/CATE) for CRM campaigns
- Feed downstream systems: paid acquisition bidding (Google/Meta value-based bidding), CRM send frequency, credit line decisions
- Handle cold-start for new users with limited history

## Non-Functional Requirements
- Calibrated dollar output (not just rank ordering) for bid optimization -- systematic 30% overestimate causes systematic overbidding
- Nightly batch scoring for CRM/capacity planning; sub-200ms real-time scoring for in-session interventions (cancel-flow discount offers)
- Right-censoring awareness: young customers have unknown horizons, must not bias toward churned users
- Monthly retrain cadence with drift monitoring (PSI on feature distributions)
- Quarterly recalibration via isotonic regression on rolling windows without full retrain

## Key Scale Questions
- 50M+ customers (Shopify-scale), millions of daily score refreshes
- Non-contractual: sparse purchase histories (many single-purchase customers), unobserved churn events
- Contractual: observable cancel events, time-varying covariates (subscription tier, support tickets)
- Read-heavy scoring workload: millions of lookups from ads platforms and CRM tools
- Cold-start: new users with one session need hierarchical partial pooling across channel/geography/product tier
- Privacy constraints: Apple ATT, third-party cookie deprecation, GDPR limit attribution signals

## Core Components
- **CLV Model Service**: BG/NBD + Gamma-Gamma for non-contractual; Cox PH / survival models for contractual; DNN residual on top for production path
- **Churn Scoring Service**: batch (nightly) for CRM ranking; real-time (feature store + GBDT) for in-session interventions
- **Uplift Model Service**: meta-learners (T-learner, X-learner) or causal forests for treatment effect estimation
- **Feature Store**: Tecton/Feast with streaming Kafka updates; pre-aggregated features (30-day session counts, RFM aggregates) for real-time lookups
- **Calibration Service**: isotonic regression recalibration on rolling holdout cohorts; PIT histograms and calibration error by decile
- **Budget Allocation Service**: integer programming (Gurobi/OR-Tools) for campaign targeting under budget/fairness/cap constraints
- **Ads Integration Pipeline**: server-side conversion events with predicted CLV values to Google Enhanced Conversions and Meta CAPI

## Key Design Decisions

### Label Construction (Avoid Leakage)
- **Option A (WRONG): Regress historical revenue to date.** Leaks future information unless features are point-in-time snapshots at cohort start.
- **Option B (CORRECT): Use future spend from t0 forward as label.** All features must be available at t0. Point-in-time joins are mandatory. Right-censored customers contribute to likelihood but not response variable.

### Model Family by Business Type
- **Non-contractual (e-commerce, apps):** BG/NBD models repeat purchases with latent dropout; Gamma-Gamma models spend per transaction. Beats RFM regression on sparse data because it encodes generative assumptions.
- **Contractual (subscriptions):** Cox proportional hazards for tenure with observable cancel events. Parametric (Weibull, log-logistic) when extrapolation beyond observed data is needed.
- **Production path:** Probabilistic baseline (BG/NBD or Cox) + DNN residual on top. Best of both: interpretability from baseline, lift from DNN.

### Churn Scoring vs Retention Prediction
- **Churn scoring:** Relative ranking (top 10% risk gets save campaigns). Low calibration need. Daily batch. Evaluated by AUC/precision@k.
- **Retention prediction:** Calibrated P(active in T days) for aggregate revenue forecasting. High calibration need. Weekly batch. Evaluated by Brier score.
- **CLV estimation:** Calibrated E[discounted future spend] in dollars. Critical calibration for bidding. Nightly batch. Evaluated by MAE in dollars and policy simulation.

### Uplift Model Architecture
- **S-learner:** Single model with treatment as feature. Low variance, high bias for strong HTE.
- **T-learner:** Separate models per arm. Low bias, high variance for small subgroups. Easiest to audit.
- **X-learner:** Cross-fit counterfactuals. Balances bias-variance for imbalanced treatment sizes.
- **Causal forest:** Honest splitting with confidence intervals. Best for complex interactions when N > 500K.

### Budget Allocation Strategy
- **Greedy (sort by uplift/cost):** O(N log N), ignores diminishing returns and constraints. Quick baseline.
- **Integer programming (Gurobi/OR-Tools):** Optimal with budget, fairness, and per-user cap constraints. Used for daily batch campaigns.
- **Thompson sampling:** Online learning with posterior uncertainty. Used for real-time in-session allocation.

## API Endpoints
| Method | Path | Description |
|--------|------|-------------|
| GET | /api/customers/{id}/clv | Get predicted CLV with p10/p50/p90 |
| GET | /api/customers/{id}/churn-score | Get churn risk rank (0-100) |
| GET | /api/customers/{id}/retention | Get P(active in T days) calibrated |
| POST | /api/customers/{id}/treatment-uplift | Get CATE for a given treatment |
| POST | /api/campaigns/allocate | Allocate treatment budget under constraints |
| POST | /api/conversions/value | Fire server-side conversion with predicted CLV to ads platforms |

## Database Schema
| Column | Type | Notes |
|--------|------|-------|
| customer_id | BIGINT | PK |
| clv_estimate | DECIMAL | Predicted discounted future spend |
| clv_p10 / p50 / p90 | DECIMAL | Uncertainty quantiles |
| churn_score | FLOAT | Risk rank 0-100 |
| retention_prob | FLOAT | Calibrated P(active in T days) |
| model_version | VARCHAR | Pin model version for ads integration |
| score_timestamp | TIMESTAMP | When score was computed |
| segment_id | INT | Acquisition channel / product tier for partial pooling |

## Deep Dive Topics
- **Label leakage:** Regressing lifetime revenue to date leaks future information; point-in-time dataset construction is mandatory
- **Right-censoring:** Customers with partial tenure contribute to likelihood but not response; excluding them biases toward churned users, including them with partial labels biases low
- **Calibration validation:** PIT histograms and calibration error by decile, not aggregate RMSE -- fat-tailed CLV errors hide catastrophic miscalibration in high-value segment
- **Proportional hazards assumption:** Test with Schoenfeld residuals; if violated, stratify or use time-varying coefficients
- **Cold-start hierarchical pooling:** Shrinkage prior across channel/geography/product tier instead of global mean (which over-bids on low-value channels)
- **Privacy-first integration:** SKAdNetwork limits CLV to 6-bit log-scaled buckets on iOS; Google Aggregated Reporting loses per-user values entirely -- shift to audience targeting
- **Multi-objective optimization:** LTV vs engagement tradeoffs via weighted scalarization, constrained optimization, or Pareto frontier exploration
- **Feature drift:** PSI monitoring triggers auto-retrain; pandemic-scale behavioral shifts silently degrade churn models

## Follow-Up Variations
- How would you handle a marketplace where merchants have both subscription revenue and GMV-based revenue?
- What happens when your CLV model's mean shifts 20% after a retrain -- how do you prevent bid algorithm shock?
- How would you design uplift modeling when you only have observational (non-randomized) campaign data?
- How do you handle the cold-start problem for a brand-new acquisition channel with no historical CLV data?
- How would you build a system that optimizes for 5-year CLV instead of 12-month, given only 1 year of data?
- How do you ensure fair lending compliance when CLV scores affect credit pricing decisions?
