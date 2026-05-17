# Experiment Design End-to-End — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the experiment goal back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] What is the treatment? What surface does it affect (UI, ranking, infra, marketplace)?
  - [ ] Is there a business deadline for the decision (e.g., ship in 2 weeks)?
  - [ ] Are there spillover or network effects (social, two-sided marketplace)?
- [ ] Formulate a directional, falsifiable, quantified hypothesis:
  - [ ] "Treatment T will move primary metric M by at least delta (MDE) on unit U without regressing guardrails G1..Gk beyond threshold tau"
- [ ] List the metric stack:
  - [ ] Primary metric (exactly one, pre-registered): sensitive, aligned, resistant to gaming
  - [ ] Guardrails (3-5): latency p99, crash rate, DAU, revenue — each with regression threshold
  - [ ] Counter-metrics: should move if the mechanism is real (e.g., recall improvement -> lower zero-result rate)
  - [ ] Secondary (3-5): supporting evidence for the readout, FDR-corrected
- [ ] State your scale estimates (baseline rate, daily traffic, available duration)

## Phase 2: Randomization and Power (3-5 min)
- [ ] Choose the randomization unit and justify:
  - [ ] User ID: personalization, UI, ranker (no spillover)
  - [ ] Session ID: per-session stateless features (search, ads)
  - [ ] Request ID: infra-level (cache, latency, retry)
  - [ ] Cluster: social features, marketplace, two-sided platforms (unbiased under spillover)
  - [ ] Switchback: platform-equilibrium changes (pricing, matching, dispatch)
- [ ] Compute sample size: n_per_arm ~ 15.7 * sigma^2 / delta^2
  - [ ] Plug in baseline rate, target MDE, alpha=0.05, power=0.80
  - [ ] If cluster randomization: n_eff = n / (1 + (m-1)*ICC), typical ICC=0.05-0.15
- [ ] Convert n to days at expected daily exposure x allocation percentage
- [ ] If duration exceeds business window, reach for variance reduction before lowering power:
  - [ ] CUPED: variance shrinks by (1 - rho^2), typical rho=0.6-0.8 -> 35-65% reduction
  - [ ] Stratification on platform / country / tenure for high-variance segments
  - [ ] Combine both for maximum gain
- [ ] Present the power/duration tradeoff and your recommendation

## Phase 3: Pre-Committed Analysis Plan (3-5 min)
- [ ] Choose the statistical test:
  - [ ] Two-proportion z-test for binary metrics (conversion, CTR)
  - [ ] Welch's t-test for continuous metrics (revenue, time spent)
  - [ ] Mann-Whitney U or bootstrap for skewed metrics (revenue with whale tail)
  - [ ] Cluster-robust SE for cluster randomization
- [ ] Specify multiple-testing correction:
  - [ ] Bonferroni (alpha/k) for primary + guardrails (family-wise error control)
  - [ ] Benjamini-Hochberg FDR <= 0.10 for secondary metric panel
- [ ] Declare peeking policy:
  - [ ] Fixed-horizon (analyze only at planned end date) — cleanest
  - [ ] Sequential testing (mSPRT, always-valid p-values) if peeking is required
- [ ] Pre-commit halt conditions:
  - [ ] SRM at p < 0.001
  - [ ] Guardrail regression beyond threshold
  - [ ] Crash rate increase > 10% relative
- [ ] State that all analysis decisions are pre-registered before enrollment

## Phase 4: Infrastructure and Ramp (5-8 min, interviewer-directed)
- [ ] Describe randomization implementation:
  - [ ] Hash(user_id + experiment_id) for orthogonality across experiments
  - [ ] Layered hashing: independent layers for UI, ranker, infra experiments
  - [ ] Exposure logging at the moment user sees the variant (not assignment)
- [ ] Set up SRM diagnostics:
  - [ ] Chi-square goodness-of-fit on assignment counts daily
  - [ ] If SRM fires: halt, trace logging chain, restart after fix — do not rebalance
- [ ] Plan the ramp schedule:
  - [ ] 1% canary (1-3 days): smoke test only — crash, latency, errors
  - [ ] 5% guardrail check (2-3 days): guardrail dashboards must clear
  - [ ] 25% pre-experiment (3-5 days): SRM check, variance estimation, segment sanity
  - [ ] 50/50 decision experiment (1-4 weeks): powered to MDE, pre-registered analysis
  - [ ] 100% + optional 5% holdback (6-12 weeks): long-term retention, novelty wear-off
- [ ] Address concurrent experiment orthogonality via layered hashing
- [ ] Discuss specialized designs if the interviewer probes:
  - [ ] Switchback: for marketplace pricing/matching (toggle at fixed time windows)
  - [ ] Interleaving: for ranking (interleave two rankings for same user, attribute clicks)
  - [ ] Synthetic control: for geo holdouts and regulatory/all-or-nothing rollouts
- [ ] Plan readout diagnostics:
  - [ ] Novelty effect: drop first 7 days or run >= 4 weeks
  - [ ] Primacy effect: same wait-for-stabilization approach
  - [ ] Segment heterogeneity: pre-register 2-3 segment cuts with FDR control
  - [ ] ITT analysis on all assigned users (no survivorship bias)

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the experiment design in 2-3 sentences (hypothesis -> unit -> power -> ramp)
- [ ] State the trade-offs you made (power vs duration, Bonferroni vs FDR, user vs cluster)
- [ ] Mention what you would improve with more time (longer holdback, interleaving, CUPAC for sparse metrics)
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
