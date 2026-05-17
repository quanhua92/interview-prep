# Design Cohort & Retention Analysis

Source: [Cohort & Retention Analysis: D1/D7/D30 Curves, Churn Interpretation, and Retention SQL (CalibreOS)](https://www.calibreos.com/learn/analytics-cohort-retention)

## One-Liner
Measure what fraction of a signup cohort returns on day N, build the SQL to compute it correctly, and diagnose whether a drop signals a product problem, acquisition shift, or measurement artifact.

## Requirements

### Functional Requirements
- Define an anchor event (signup, first purchase, activation milestone) and return event (login, meaningful action, revenue event)
- Compute N-day retention (D1, D7, D30) per cohort using user-level binary logic
- Build triangular cohort tables (rows = signup cohort, columns = time since signup, cells = retention %)
- Segment retention by acquisition channel, platform (iOS vs Android), and behavioral cohort
- Handle right-censoring for cohorts that have not had enough elapsed time

### Non-Functional Requirements
- SQL queries must avoid quadratic joins (use window functions for multi-horizon analysis in a single pass)
- Timezone handling must be consistent (calendar day vs rolling 24-hour, pick one and document)
- Censor incomplete cohorts or display with confidence ribbons
- Separate user-grain from event-grain to prevent power users from inflating retention

### Key Scale Questions
- Events table can be billions of rows; retention queries must be incremental, not full-table scans
- Cohort sizes vary wildly (10K organic vs 100K paid); noisy small cohorts need separate treatment
- Right-censoring grows with each new cohort; D30 analysis must exclude the last 30 days of signups

## Key Concepts

### Retention Definitions
| Definition | Numerator | Best For |
|---|---|---|
| Strict N-day | Active exactly on day N | Investor comparables |
| N-day window (bracketed) | Active any day 1 through N | Growth marketing |
| Weekly rolling | WAU of cohort / cohort size | B2B SaaS monitoring |
| Revenue-weighted | Spend on day N | Marketplaces |
| Recommended default | Binary user on day N + censoring rules | Interview + production |

### D1 / D7 / D30 Interpretation
- **D1** captures activation quality and first-impression value. Strongest predictor of long-term retention in consumer apps.
- **D7** measures habit formation, the transition from novelty to routine. Gold standard for investor comparison; most onboarding A/B tests are powered for D7.
- **D30** signals long-term product value. Tightly correlated with LTV in subscription products; below 15-20% in a paid app means the cohort likely will not recover CAC.

### Curve Shape Diagnostics
- **Steep D1-to-D7 drop, flat D7-D30 tail**: onboarding problem, not core product problem
- **Gradual linear decay**: low engagement frequency, not catastrophic churn
- **Power-law retention**: normal for utility apps (many churn fast, small core stays)
- **S-curve retention**: common in free-trial SaaS where paid conversion gates access

### Survival Analysis Framing
- Survival function S(t): probability user is still active beyond time t (the retention curve)
- Hazard function h(t): instantaneous churn rate at time t, conditional on surviving to t
- Hazard is more diagnostic than survival alone: two products with identical D30 can have radically different failure modes
- Early-peak hazard (D2-D3): novelty wore off, activation problem
- Trial-end spike (D14-D30): conversion gate or paywall
- Renewal spike (D365): annual subscription renewal risk

## Decisions

### Calendar Day vs Rolling 24-Hour Windows
- Calendar day (midnight-to-midnight): common in investor decks, easy cross-company comparison
- Rolling (168 hours post-anchor): more precise but harder to explain to stakeholders
- Pick one consistently; mixing produces off-by-one errors at timezone boundaries

### Partial Cohort Policy
- Exclude cohorts without enough elapsed time from the denominator for each horizon
- Alternative: display with confidence ribbons or mark as censored
- Including young cohorts in D30 denominator creates artificial drops (math artifact, not product truth)

### User-Grain vs Event-Grain
- Always count distinct users, not sessions. A single power user can inflate session counts and mask broad churn.
- This is the single most common mistake in retention SQL.

## Deep Dives

### Multi-Horizon Retention SQL (D1, D7, D30 in One Query)
Core technique: compute `days_since_anchor` for every event, then use `MAX(CASE WHEN days_since_anchor = N THEN 1 ELSE 0 END)` to mark retention at each horizon. This transforms a quadratic self-join into a linear scan with a group-by.

Key details:
- Use `DATE_TRUNC` or `DATEDIFF` consistently; never mix `INTERVAL '7 day'` with calendar-day logic
- `WHERE cohort_date <= CURRENT_DATE - INTERVAL '30 day'` to censor incomplete cohorts
- `LEFT JOIN` retention flags to anchor so users with zero return events appear with retention = 0

### Triangular Cohort Table (Retention Triangle)
Rows = signup cohort (week or month), columns = time since signup, cells = retention %. The table is right-censored (recent cohorts have not matured to later offsets), forming a triangle.

Interpretation patterns:
| Pattern | Visual Signal | Common Cause |
|---|---|---|
| Diagonal red streak | Recent cohorts worse at all horizons | Product regression or acquisition quality drop |
| Vertical red column | All cohorts weak at same time offset | Measurement bug or seasonal event |
| Top-right green corner | Recent cohorts strong early | Onboarding improvement |
| Jagged sawtooth | Alternating strong/weak cohorts | Weekly seasonality or batch acquisition |

Vertical analysis (down a column): compares different cohorts at the same lifecycle stage. Tests whether product or acquisition quality is improving.
Horizontal analysis (across a row): shows a single cohort's decay curve. Tests product-market fit and long-term stickiness.

### False Churn and Definition Drift
Three silent killers of retention metrics:
1. **Silent push opt-out**: DAU drops because fewer notifications reach users, not because engagement fell
2. **SDK version change**: New release stops firing an event (e.g., `screen_view`), retention collapses while true engagement is unchanged
3. **Acquisition mix shift**: Paid installs replace organic, headline D7 drops without any product regression

### Churn Interpretation
- Dormancy is not permanent exit; a user who misses D30 may return on D45 or D90
- Subscription products distinguish voluntary churn (cancellation), involuntary churn (payment failure), and dormancy
- Cohort-based churn is cleaner than blended monthly churn (fast growth artificially suppresses blended churn by inflating the denominator)
- Resurrecting churned users can be 3-5x cheaper than acquiring new ones for digital products

### Platform Delta (iOS vs Android)
- iOS retention runs ~3pp higher than Android across categories
- Reflects demographic mix (higher income, older, more willing to pay) and app quality selection
- Always segment by platform; never propose a blended target without acknowledging the split

### Retention Benchmarks by Product Type (2026 Medians)
| Product Type | D1 | D7 | D30 | Key Driver |
|---|---|---|---|---|
| Consumer Social (organic) | 40-50% | 25-35% | 15-25% | Network density |
| B2B SaaS (SMB) | 50-65% | 35-50% | 25-40% | Workflow integration |
| B2B SaaS (Enterprise) | 65% | 55% | 45% | Deep integrations |
| Mobile Gaming (midcore) | 35-45% | 18-28% | 10-18% | Progression pacing |
| Marketplace (two-sided) | 30-40% | 20-30% | 12-20% | Liquidity |
| Productivity Tools | 45-60% | 30-45% | 20-35% | Daily habit |
| Streaming Media | 55-70% | 40-55% | 30-45% | Content catalog |

2026 structural shifts: SMB SaaS NRR dropped below 100%; consumer mobile D30 compressed 10-15%; streaming monthly churn rose to ~5.5%. Never cite pre-2024 benchmarks without acknowledging compression.

## Follow-Ups
- D7 retention dropped 5pp after a launch. Walk through your investigation. (Check: acquisition mix shift, event schema change, platform mix, feature exposure)
- Should you invest in improving D1 from 40% to 45%, or D30 from 20% to 22%? (D1 is a multiplier on all downstream retention; D30 improvements have higher absolute LTV impact per user. Answer depends on funnel shape and marginal cost.)
- How would you design a retention dashboard for a freemium SaaS product? (Dimensions: cohort week, plan type, activation status, acquisition channel, platform)
- How would you use cohort segmentation to diagnose product vs acquisition quality problems? (Segment by channel within a cohort; if organic holds but paid drops, it is acquisition; if all segments drop simultaneously, it is product)
