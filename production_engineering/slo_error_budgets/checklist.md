# SLO Design: Error Budgets, Burn Rate Alerts, and the Reliability Tradeoff — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] Is the SLO for a user-facing service or an internal service?
  - [ ] What is the current measured reliability (do we have baseline data)?
  - [ ] Are there existing SLAs that constrain the SLO target?
  - [ ] What is the business impact of downtime (revenue per minute, user churn)?
- [ ] Define the SLI hierarchy (3-4 items):
  - [ ] SLI: the quantitative measurement (e.g., request success rate, P99 latency)
  - [ ] SLO: the target value over a rolling window (e.g., 99.9% over 28 days)
  - [ ] Error budget: 100% - SLO (the operational currency for reliability decisions)
  - [ ] SLA: the contractual commitment (must be looser than the SLO)
- [ ] State your scale estimates:
  - [ ] ~1M requests/day (example)
  - [ ] ~28,000 error budget units per 28-day window at 99.9%
  - [ ] ~40.3 minutes of allowed downtime per 28-day window

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw the SLI-to-alerting pipeline: Raw Metrics -> SLI Computation -> SLO Comparison -> Error Budget Tracking -> Burn Rate Alerting
- [ ] Identify the four canonical SLI categories:
  - [ ] Availability (request success rate)
  - [ ] Latency (fraction of requests under threshold)
  - [ ] Quality (response correctness)
  - [ ] Throughput (requests per second)
- [ ] Choose the SLI that best correlates with user experience
- [ ] State why 28-day rolling window is standard (avoids month-boundary effects, smooths weekly seasonality)
- [ ] Present the design and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Design the SLI for the specific service:
  - [ ] Define "good" events vs "total" events (e.g., 2xx/3xx responses / total responses)
  - [ ] Filter health checks from the denominator (`path != '/health'`)
  - [ ] Use P99 or P95 for latency, never mean
- [ ] Set the SLO target based on measurement, not intuition:
  - [ ] Measure past 90 days of reliability
  - [ ] Choose a target that is achievable but tight enough to catch real issues
  - [ ] Leave headroom between SLO and SLA (e.g., SLO 99.9%, SLA 99.5%)
- [ ] Calculate error budget:
  - [ ] Error budget = 100% - SLO target
  - [ ] Convert to concrete units (minutes of downtime, number of failed requests)
  - [ ] Example: 99.9% SLO with 1M req/day = 1,000 failed req/day = 28,000 per 28 days
- [ ] Design burn rate alerts (not threshold alerts):
  - [ ] Explain why threshold alerts cause alert fatigue
  - [ ] Define burn rate: `burn_rate = (error_rate_in_window) / (1 - SLO_target)`
  - [ ] Fast burn: > 14.4x over 1h AND 5m windows -> immediate page
  - [ ] Slow burn: > 6x over 6h AND 30m windows -> next business hour
  - [ ] Budget warning: > 1x over 24h AND 72h -> Slack notification, no page
- [ ] Walk through the two-window approach:
  - [ ] Both short and long windows must show elevated burn rate
  - [ ] A 30-second spike does not trigger because the 5m window recovers
  - [ ] A sustained degradation triggers because both windows stay elevated

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss SLI design pitfalls:
  - [ ] Measuring infrastructure health (CPU, memory) instead of user experience
  - [ ] Including health check requests in the denominator
  - [ ] Using arithmetic mean latency instead of P99/P95
  - [ ] Setting the same SLO for all endpoints regardless of criticality
- [ ] Explain the user journey SLO concept:
  - [ ] Measures end-to-end transaction success (search -> product -> cart -> checkout -> payment)
  - [ ] Most accurate but hardest to implement (requires distributed tracing)
  - [ ] Directly correlates with business impact
- [ ] Discuss SLO target selection trade-offs:
  - [ ] 99.0% for internal tools (6.7 hours/month downtime)
  - [ ] 99.9% for core user-facing features (40 min/month)
  - [ ] 99.99% for financial/healthcare (4 min/month, requires dedicated SRE team)
  - [ ] Each additional 9 costs exponentially more engineering effort
- [ ] Address common mistakes:
  - [ ] Setting SLOs without measurement data (start from 90-day baseline)
  - [ ] Single SLO for all services (different criticality tiers need different SLOs)
  - [ ] Not resetting error budget on SLO revision
  - [ ] Binary deploy freeze on budget exhaustion instead of risk-informed decisions
- [ ] Walk through Prometheus/Alertmanager configuration:
  - [ ] Recording rules for success rate over different windows
  - [ ] Burn rate computation: `(1 - success_rate) / (1 - SLO_target)`
  - [ ] Alert rules with two-window conditions and severity labels

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made and why (reliability vs velocity)
- [ ] Mention what you would improve with more time (user journey SLOs, SLO review cadence, quarterly error budget reports)
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
