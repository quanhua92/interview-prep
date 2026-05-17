# Cohort & Retention Analysis — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem: measure what fraction of a signup cohort returns over time and diagnose why it changes
- [ ] Ask clarifying questions:
  - [ ] What is the anchor event? (signup, first purchase, activation milestone)
  - [ ] What counts as a "return"? (any login, meaningful action, or revenue event)
  - [ ] Calendar day or rolling 24-hour windows?
  - [ ] What is the partial cohort policy? (exclude incomplete horizons or mark censored)
- [ ] List functional requirements (3-5 items):
  - [ ] Compute N-day retention (D1, D7, D30) per cohort
  - [ ] Build triangular cohort table (rows = cohort, cols = time since signup)
  - [ ] Segment by acquisition channel, platform, behavioral cohort
  - [ ] Handle right-censoring for recent cohorts
  - [ ] Distinguish user-grain from event-grain (count distinct users, not sessions)
- [ ] List non-functional requirements:
  - [ ] SQL must scale to billions of events (use window functions, avoid quadratic joins)
  - [ ] Consistent timezone handling (pick one convention, document it)
  - [ ] Incremental computation for production pipelines
- [ ] State your retention definition choice:
  - [ ] Strict N-day (binary: did user return on exactly day N?)
  - [ ] Bracketed window (active any day 1 through N)
  - [ ] Rolling weekly (WAU of cohort / cohort size)
  - [ ] Recommended: binary user-level + censoring rules

## Phase 2: High-Level Design (3-5 min)
- [ ] Sketch the data flow: events table -> anchor CTE (first signup per user) -> activity flags (days_since_anchor) -> retention flags (MAX CASE per horizon) -> cohort aggregation
- [ ] Identify the key SQL components:
  - [ ] Anchor CTE: `user_id`, `MIN(ts)` as `cohort_date`
  - [ ] Activity CTE: `user_id`, `DATE_TRUNC('day', ts)` as event date, `DATEDIFF` as `days_since_anchor`
  - [ ] Retention flags: `MAX(CASE WHEN days_since_anchor = N THEN 1 ELSE 0 END)` per horizon
  - [ ] Final aggregation: `AVG(retained_dN)` across cohort, with censoring filter
- [ ] Note the read pattern: retention queries are analytical (batch), not real-time OLTP
- [ ] Discuss where caching or materialized views help (retention curves for active dashboards)

## Phase 3: Core Component Design (5-8 min)
- [ ] Write the multi-horizon retention SQL (D1, D7, D30 in one query):
  - [ ] Anchor CTE with `MIN(ts)` grouped by user
  - [ ] Activity flags CTE joining events to anchor, computing `days_since_anchor`
  - [ ] Retention flags CTE with `MAX(CASE ...)` for each horizon
  - [ ] Final SELECT with `AVG(COALESCE(flag, 0))` and `WHERE cohort_date <= CURRENT_DATE - INTERVAL '30 day'`
- [ ] Explain the triangular cohort table:
  - [ ] Rows = signup cohort (week/month), columns = weeks since signup, cells = retention %
  - [ ] Right-censored by nature (recent cohorts lack data for later offsets)
  - [ ] Read vertically: compare cohorts at same lifecycle stage
  - [ ] Read horizontally: see single cohort's decay curve
- [ ] Discuss interpretation patterns:
  - [ ] Diagonal red streak = product regression or acquisition quality drop
  - [ ] Vertical red column = measurement bug or seasonality
  - [ ] Top-right green = onboarding improvement
  - [ ] Jagged sawtooth = weekly seasonality
- [ ] Walk through D1/D7/D30 curve interpretation:
  - [ ] D1: activation quality, first-impression value, strongest predictor of long-term retention
  - [ ] D7: habit formation, gold standard for investor comparison, powers onboarding A/B tests
  - [ ] D30: long-term product value, correlates with LTV in subscription products
- [ ] Address false churn and definition drift:
  - [ ] Silent push opt-out (notifications stop, not engagement)
  - [ ] SDK version change (event schema breaks, not user behavior)
  - [ ] Acquisition mix shift (paid replaces organic, not product regression)

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss retention benchmarks by product type:
  - [ ] Consumer social (organic): D1 40-50%, D7 25-35%, D30 15-25%
  - [ ] B2B SaaS (SMB): D1 50-65%, D7 35-50%, D30 25-40%
  - [ ] Mobile gaming (midcore): D1 35-45%, D7 18-28%, D30 10-18%
  - [ ] Marketplace (two-sided): D1 30-40%, D7 20-30%, D30 12-20%
  - [ ] Always cite benchmarks with context (definition, year, segment)
- [ ] Explain survival analysis for retention:
  - [ ] Survival function S(t): probability of being active beyond time t
  - [ ] Hazard function h(t): instantaneous churn rate at time t, conditional on surviving
  - [ ] Hazard is more diagnostic than survival alone (reveals when churn risk peaks)
  - [ ] Kaplan-Meier estimator for empirical survival curves
  - [ ] Cox Proportional Hazards for quantifying feature effects on churn
- [ ] Discuss advanced SQL techniques:
  - [ ] Rolling retention (weekly active cohort share) with LEFT JOIN
  - [ ] Kaplan-Meier SQL: cumulative product of survival probabilities using `EXP(SUM(LN(prob))) OVER (ORDER BY tenure)`
  - [ ] Handling censored users (still active at analysis cutoff)
- [ ] Address platform and segment differences:
  - [ ] iOS runs ~3pp higher than Android across categories
  - [ ] Segment by acquisition channel, platform, activation status
  - [ ] Small cohorts are noisy; always show cohort size alongside retention %
- [ ] Discuss 2026 benchmark shifts:
  - [ ] SMB SaaS NRR dropped below 100% (expansion compression)
  - [ ] Consumer mobile D30 compressed 10-15% (CAC saturation)
  - [ ] Streaming monthly churn rose to ~5.5% (subscription fatigue)

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize: lock anchor and return-event definitions, use user-grain strict N-day retention with censoring, validate SQL with manual cohort audit before trusting the curve
- [ ] State trade-offs: strict N-day vs bracketed windows, calendar vs rolling time, censoring vs including partial cohorts
- [ ] Mention improvements with more time: survival analysis with Cox regression, behavioral cohort segmentation, incremental pipeline automation
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
