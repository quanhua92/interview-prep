# Experiment Design End-to-End

Source: [Experiment Design End-to-End: MDE, Randomization, CUPED, SRM, Switchback, Ramps (CalibreOS)](https://www.calibreos.com/learn/analytics-experiment-design)

## One-Liner
Design and run a valid A/B experiment from hypothesis through ramp-to-100%, covering randomization unit selection, power/MDE calculation, variance reduction (CUPED), SRM diagnostics, multi-metric correction, and specialized designs (switchback, interleaving, synthetic control).

## Requirements

### Functional
- Formulate a directional, falsifiable, quantified hypothesis with MDE and guardrails
- Choose the correct randomization unit (user, session, request, cluster, switchback)
- Define a pre-registered metric stack: primary (one), guardrails (3-5), counter-metrics, secondary (3-5)
- Compute sample size and experiment duration from baseline, MDE, alpha, and power
- Apply variance reduction (CUPED, stratification) to shorten experiment duration
- Pre-commit analysis plan: test choice, multiple-testing correction, peeking policy
- Set up SRM (Sample Ratio Mismatch) diagnostics and halt conditions
- Plan the ramp: 1% -> 5% -> 25% -> 50% -> 100% with holdback
- Diagnose novelty/primacy effects and segment heterogeneity at readout

### Non-Functional
- Statistical validity: unbiased treatment effect estimate, controlled false-positive rate
- Duration constraint: experiment must complete within the business decision window
- Scalability: concurrent experiments via layered hashing without interaction
- Blast-radius control: catch P0 issues at low exposure before wide ramp

## Key Concepts

### The 9-Step Framework
1. **Hypothesis**: directional, falsifiable, quantified (treatment T moves metric M by delta on unit U without regressing guardrails G1..Gk)
2. **Randomization unit**: user, session, request, cluster, or switchback depending on contamination risk
3. **Metric stack**: primary (exactly one, pre-registered), guardrails, counter-metrics, secondary
4. **Sample size / MDE**: n_per_arm ~ 15.7 * sigma^2 / delta^2; set MDE to the minimum effect that moves the business decision
5. **Variance reduction**: CUPED (Y_adj = Y - theta*(X - E[X])), stratification; both unbiased and free when pre-period data exists
6. **Pre-committed analysis plan**: test choice, Bonferroni for primary+guardrails, BH-FDR for secondary, peeking policy
7. **SRM diagnostics**: chi-square goodness-of-fit daily; halt at p < 0.001; never "rebalance"
8. **Specialized designs**: switchback (marketplace pricing), interleaving (ranking), synthetic control (geo holdout)
9. **Ramp plan**: 1% canary -> 5% guardrail -> 25% pre-experiment -> 50/50 decision -> 100% + holdback

### Randomization Unit Decision Matrix

| Unit | Use When | Variance | Risks |
|------|----------|----------|-------|
| Request ID | Pure-infra (cache, latency) | Highest | Cannot measure user metrics |
| Session ID | Per-session stateless (search, ads) | High | Carry-over learning |
| User ID | UI, personalization, ranker, retention | Medium-low | Long-term carry-over |
| Cluster | Social, marketplace, two-sided platforms | Lower (n_eff = n/(1+(m-1)*ICC)) | Cluster picking bias |
| Switchback | Platform-equilibrium (pricing, matching) | Variable, needs ~30 toggles | Day-of-week confounds, hangover |

### CUPED Variance Reduction
- Formula: Y_adj = Y - theta * (X - E[X]), where theta = Cov(Y,X)/Var(X)
- Variance shrinks by (1 - rho^2): rho=0.8 -> 64% reduction (~3x faster), rho=0.6 -> 36%, rho=0.4 -> 16%
- Breaks down: new users with no pre-period, brand-new metrics, treatment-changing user composition

## Decisions

### Sample Size: MDE Framing
- Wrong: "what is the smallest effect we can detect?"
- Right: "what is the smallest effect we would care about?"
- Powering to detect 0.05pp when 0.5pp is the ship bar wastes time on a meaningless effect
- Worked example: DoorDash 8% baseline conversion, +0.5pp MDE -> ~46,200/arm -> round up to 1 week for seasonality

### Multiple Testing Strategy
- **Bonferroni (alpha/k)**: for primary + guardrails (1 primary + 4 guardrails -> alpha/5 = 0.01 each)
- **Benjamini-Hochberg FDR <= 0.10**: for secondary metric panel and segment cuts
- Running k=20 tests at alpha=0.05 without correction -> expect 1 false positive by construction

### Peeking Policy
- Fixed-horizon: analyze only at planned end date (cleanest)
- Sequential: mSPRT or always-valid p-values if peeking is required
- Peeking daily at alpha=0.05 for 30 days inflates Type I error to ~25%

### Ramp Halt Conditions
- Crash rate increase > 10% relative
- p99 latency increase > 50ms or > 25% relative
- Any guardrail regression beyond pre-set threshold
- SRM at p < 0.001
- Strong negative DAU signal (> 2 sigma from baseline)

## Deep Dives

### SRM (Sample Ratio Mismatch) - The Silent Killer
- Observed ratio differs from intended at statistically improbable level
- Root causes: bot filter on one variant, latency-induced exposure dropout, salt collision, crash on first load, ad-blocker on tracking pixel
- When SRM fires: halt, do not rebalance, trace logging chain, restart after bug fix
- Diagnostic: chi-square on assignment counts daily, threshold p < 0.001

### Switchback Design (Marketplace Experiments)
- Toggle treatment on/off at fixed intervals (30 min to 4 hours) over entire population
- Used by Lyft, Uber, DoorDash for pricing/matching experiments
- Must balance day-of-week and hour-of-day across variants
- Hangover effect: treatment actions carry over to control window -> use buffer windows or accept ITT interpretation

### Interleaving (Ranking Experiments)
- Interleave two rankings within a single result list for same user
- Attribute clicks to the ranker that surfaced the item
- Massive variance reduction (user-level variation removed)
- Only works for ranked-list outputs with unambiguous per-item attribution
- Used by Bing, Yahoo, Netflix

### Novelty and Primacy Effects
- **Novelty**: treatment looks great in week 1, converges by week 3-4
- **Primacy**: treatment looks worse early (users confused), recovers later
- Fix: run >= 4 weeks; analyze week-2-onwards; require effect to persist into holdback

### Common Failure Modes (by Frequency)
1. Novelty effect masquerading as real lift
2. Primacy effect killing good ideas via fast rollback
3. Network effects bias (user-level randomization underestimates in social products)
4. Carry-over from earlier experiments
5. Survivorship bias (analyzing only users who completed the funnel)
6. Simpson's Paradox (aggregate improved, every segment worsened)
7. Multiple-comparison fishing ("it moved on metric 14 out of 20")
8. Assignment/exposure mismatch (logged assignment but not actual exposure)

## Follow-Ups
- How would you design an experiment for a two-sided marketplace where treatment affects both supply and demand?
- Your experiment is underpowered at the current MDE. Do you lower power, raise alpha, apply CUPED, or change the question?
- How do you handle concurrent experiments that might interact? What is layered hashing?
- The experiment shows a positive primary metric but a guardrail regression. What is your recommendation?
- How do you measure long-term retention effects when the decision experiment only runs 2-4 weeks?
- When would you use synthetic control vs difference-in-differences vs RDD?
- Your SRM check fires at p=0.0001. The product team wants to keep running. What do you say?
