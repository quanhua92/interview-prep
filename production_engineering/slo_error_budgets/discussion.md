# SLO Design: Error Budgets, Burn Rate Alerts, and the Reliability Tradeoff

Source: [SLO Design: Error Budgets, Burn Rate Alerts, and the Reliability Tradeoff (CalibreOS)](https://www.calibreos.com/learn/prod-slo-error-budgets)

## One-Liner
Design Service Level Objectives that make reliability measurable and actionable through error budgets and burn rate alerting.

## Why SLOs Are the Most Misunderstood Tool in Reliability Engineering
Most teams think about reliability in terms of uptime: "we target 99.9% availability." This framing has two problems:
- **Nothing actionable for on-call**: 99.9% availability means ~8.7 hours of downtime per year, but that number alone does not tell you whether someone should be paged right now.
- **Binary framing**: either you are "up" or "down," when the real problem is usually *degradation*: some requests succeed, some time out, P99 latency rises while P50 looks fine.

SLOs solve this by making reliability *measurable* and *actionable*:
- **Measurable**: Instead of "we're up," you know "~3.2% of checkout requests failed in the past hour, which is 2.4x our 30-day error rate."
- **Actionable**: Instead of "we're burning error budget," you know "at current burn rate we will exhaust the month's error budget in 4 hours, which means we need to mitigate now."

The Google SRE team credits SLOs with making their reliability/velocity tradeoff explicit and data-driven. Before SLOs, the reliability team would veto any deploy that risked an outage. With SLOs, the question becomes: does the remaining error budget allow this deploy? If yes, ship it. If no, wait until the budget recovers.

## What Interviewers Are Testing
- **L4/Mid signal**: Knows the difference between SLI, SLO, and SLA. Can describe what an error budget is. Has set up basic availability alerts.
- **L5/Senior signal**: Can design a meaningful SLI for a specific service. Can calculate error budget consumption. Knows that 99.9% availability != 99.9% of requests succeed (the measurement window matters). Understands why simple threshold alerts on error rate produce alert fatigue.
- **Staff signal**: Designs multi-window burn rate alerts. Understands the reliability vs. velocity tradeoff explicitly. Can argue for a specific SLO tightness based on business risk. Knows when to set a looser SLO (and why that is sometimes the right answer). Understands the difference between customer-facing SLOs and internal service SLOs. Has opinions about SLO measurement methodology (request success rate vs. user journey success rate).

## The SLI -> SLO -> SLA Hierarchy

### SLI (Service Level Indicator): The Measurement
- A quantitative measurement of a specific aspect of service behavior
- The measurement must be:
  1. **Meaningful to the user**: does it capture an experience users actually care about?
  2. **Measurable in production**: not theoretical
  3. **Aggregatable**: you can compute a number from it over a time window
- The four canonical SLI categories from the SRE book:
  - **Availability**: what fraction of requests succeeded?
  - **Latency**: what fraction of requests completed in under X ms?
  - **Quality**: what fraction of responses were correct/valid?
  - **Throughput**: how many requests per second can the system sustain?
- Choose the SLI that most directly correlates with a user experiencing a degraded service

### SLO (Service Level Objective): The Target
- The target value for the SLI over a rolling time window
- Form: "X% of requests will have property Y over a rolling 28-day window"
- The rolling window matters: 28 days is standard because it avoids month-boundary effects and is long enough to smooth weekly seasonality
- The target percentage determines the error budget:
  - 99.9% availability over 28 days = 0.1% error budget = 40.3 minutes of downtime per 28 days
  - 99.5% = 0.5% budget = 3.36 hours
- The SLO should be: tight enough that violating it means users are actually impacted, and loose enough that you can ship features and take on-call sleep

### Error Budget: The Operational Currency
- Error budget = 100% - SLO
- A 99.9% SLO has a 0.1% error budget
- Concretely: if your service handles 1,000,000 requests per day, a 99.9% SLO means you can afford 1,000 failed requests per day, or 28,000 per 28-day window
- The error budget makes reliability concrete
- Instead of "we should not deploy on Fridays," the conversation becomes "we have 15,000 error budget units left this month; this deploy has a 5% chance of burning 10,000, is that risk acceptable given the feature value?"

### SLA (Service Level Agreement): The Contract
- The legal/commercial agreement with customers about what level of service is guaranteed and what penalties apply for non-compliance
- SLAs should be:
  1. **Looser than the SLO**: you need headroom between what you guarantee and what you target
  2. **Defined only for measurable metrics**: ones you can reliably measure and report
  3. **Set from business risk**: not purely technical aspiration
- Typical relationship: if your SLO is 99.9%, your SLA might be 99.5%, giving you a buffer of 3+ hours per month before you are in breach
- Never set an SLA tighter than your SLO

## SLO Architecture: From Raw Metrics to Alerting
The pipeline from raw telemetry to SLO alerts:
1. **Raw metrics** (e.g., HTTP response codes, request latency) collected from application instrumentation
2. **SLI computation** (e.g., success rate = successful requests / total requests, excluding health checks)
3. **SLO comparison** (e.g., is the 28-day rolling success rate >= 99.9%?)
4. **Error budget tracking** (how much of the 28-day budget remains?)
5. **Burn rate alerting** (is the current error rate consuming budget too fast?)

## Burn Rate Alerting: The System That Replaced Threshold Alerts
The naive approach to SLO alerting is to alert when the error rate exceeds the SLO threshold: fire an alert when the 5-minute error rate exceeds the 0.1% threshold. This produces alert fatigue: brief error rate spikes that would burn only 1% of the monthly error budget still trigger a page.

- **Burn rate** is the solution: `burn_rate = (error_rate_in_window) / (1 - SLO_target)`
- For a 99.9% SLO (0.1% error budget), a 1.0x burn rate means you are exactly on track to exhaust the budget in 28 days. A 14x burn rate means you will exhaust the budget in 28/14 = 2 days.

### The Two-Window Alert Approach (from Google's SRE Workbook)

| Alert | Short Window | Long Window | Burn Rate Threshold | Urgency | Page? |
|-------|-------------|-------------|-------------------|---------|-------|
| Fast burn | 1 hour | 5 minutes | > 14.4x | SLO exhausted in ~2 days at this rate | Yes, immediate |
| Slow burn | 6 hours | 30 minutes | > 6x | SLO exhausted in ~5 days | Yes, next business hour |
| Budget warning | 24h | 72h | > 1x sustained | SLO tracking below target | Slack, no page |

The two-window requirement prevents spurious alerts: both the short window AND the long window must show the elevated burn rate before an alert fires. A 30-second spike causes the 1-hour window to show a high rate, but if the 5-minute window has already recovered, no alert fires.

### Concrete Math for a 99.9% SLO with 1M Requests/Day
- 28-day error budget: 28,000 failed requests
- 14.4x burn rate: 14.4 x 0.1% = 1.44% error rate
- At 1.44% error rate with 1M req/day: 14,400 errors/day
- Budget exhaustion: 28,000 / 14,400 = 1.94 days
- Alert fires when 1h window shows > 14.4x burn AND 5m window also shows > 14.4x burn

## Designing the Right SLI: What to Measure and What Not To
Choosing the right SLI is harder than setting the right SLO target. The SLI must be meaningful (correlated with user experience), measurable (instrumented in production), and actionable (when it degrades, you know what to investigate).

### Four Common SLI Design Mistakes
1. **Measuring infrastructure health instead of user experience.** CPU utilization, memory usage, and disk I/O are not SLIs, they are symptoms. A service can have 90% CPU utilization and happy users, or 20% CPU and a broken database connection. Measure what users experience: request success rate and latency.
2. **Including health check requests in the SLI denominator.** Load balancers send health checks every few seconds. Including them inflates the "total requests" denominator without reflecting user traffic. Filter them: `WHERE path != '/health'`.
3. **Using arithmetic mean latency.** Mean latency hides the tail. P50 latency of 20ms means half of users see < 20ms. P99 of 4,000ms means roughly 1 in 100 users waits 4 seconds. SLI latency should be measured at P99 or P95, not the mean.
4. **Setting the same SLO for all endpoints.** The checkout endpoint and the static assets endpoint have very different user impact when degraded. Use different SLOs for different criticality tiers, or use a user journey SLO rather than an endpoint SLO.

### The User Journey SLO
The most accurate but hardest to implement: instead of measuring per-request success, measure whether a user was able to complete a complete business transaction (search -> product page -> add to cart -> checkout -> payment). A user journey SLO directly correlates with business impact but requires distributed tracing and a definition of what constitutes a successful journey.

## Burn Rate Alert Configuration: Prometheus and Alertmanager
Example Prometheus recording rules and alert rules for a 99.9% availability SLO:

```yaml
# SLO: 99.9% availability, 28-day rolling window
# Error budget: 0.1% = 40.3 minutes of downtime per 28 days

groups:
  - name: checkout-service-slo
    rules:
      # SLI: fraction of requests that returned 2xx/3xx in the window
      - record: job:request_success_rate:1h
        expr: |
          sum(rate(http_requests_total{job="checkout-service",
            code=~"2..|3.."}[1h]))
          /
          sum(rate(http_requests_total{job="checkout-service",
            path!="/health"}[1h]))

      - record: job:request_success_rate:5m
        expr: |
          sum(rate(http_requests_total{job="checkout-service",
            code=~"2..|3.."}[5m]))
          /
          sum(rate(http_requests_total{job="checkout-service",
            path!="/health"}[5m]))

      # Burn rate = (1 - success_rate) / (1 - SLO_target)
      # SLO target = 0.999, so (1 - 0.999) = 0.001
      - record: job:slo_burn_rate:1h
        expr: (1 - job:request_success_rate:1h) / 0.001

      - record: job:slo_burn_rate:5m
        expr: (1 - job:request_success_rate:5m) / 0.001

      # Fast burn alert: both 1h and 5m windows show > 14.4x burn
      - alert: CheckoutServiceFastBurn
        expr: |
          job:slo_burn_rate:1h > 14.4
          and
          job:slo_burn_rate:5m > 14.4
        for: 2m
        labels:
          severity: page
          slo: checkout-availability
        annotations:
          summary: "Checkout SLO fast burn: {{ $value | printf \"%.1f\" }}x burn rate"

      # Slow burn alert: both 6h and 30m windows show > 6x burn
      - alert: CheckoutServiceSlowBurn
        expr: |
          (1 - job:request_success_rate:6h) / 0.001 > 6
          and
          (1 - job:request_success_rate:30m) / 0.001 > 6
        for: 15m
        labels:
          severity: warning
          slo: checkout-availability
```

## Common SLO Design Mistakes That Hurt Teams
- **Setting SLOs without measurement data.** "We'll target 99.9%" is not a design, it is a guess. Set the SLO by measuring your current reliability over the past 90 days, then decide whether that level is acceptable. Starting from a measurement prevents an SLO that is simultaneously unachievable (causing constant alert fatigue) and meaningless (too loose to catch real issues).
- **A single SLO for all services.** Your internal admin dashboard does not need a 99.9% SLO. Your payment gateway does. Applying the same SLO everywhere means you either under-protect critical services or burn engineering time maintaining unnecessary reliability for non-critical ones.
- **Threshold alerts instead of burn rate alerts.** A 5-minute error rate spike to 2% that immediately recovers is not a reliability emergency; it burned ~0.02% of the monthly error budget. A sustained 0.5% error rate for 12 hours burned 25% of the monthly error budget and never triggered your threshold alert. Burn rate captures what matters; threshold alerts capture noise.
- **Not resetting error budget on SLO revision.** If you tighten the SLO from 99.5% to 99.9%, the error budget shrinks by 5x. If you do not reset the budget tracking, you will immediately appear to have exhausted your budget from historical incidents. Always reset error budget tracking when revising the SLO target.
- **Using SLO exhaustion as a deploy freeze without nuance.** "Budget is at 10%, no deploys until it recovers" ignores the risk profile of the deploy. A low-risk config-only change with a 3-minute rollback window has different risk than a database migration. SLO budget should inform deploy risk decisions, not replace them with a binary gate.

## SLO Target Selection: Business Risk x Achievability Matrix

| SLO Target | Error Budget (28 days) | Implied Downtime | Appropriate For | Required Engineering Investment |
|-----------|----------------------|-----------------|----------------|-------------------------------|
| 99.0% | 1.0% = 6.7 hours | 6.7 hours/month | Internal tools, admin dashboards, non-critical batch jobs | Basic health checks, single-region deployment, minimal on-call rotation |
| 99.5% | 0.5% = 3.4 hours | 3.4 hours/month | Internal developer platforms, secondary user-facing features | Monitoring, automated restarts, regular on-call rotation |
| 99.9% | 0.1% = 40 minutes | 40 min/month | Core user-facing product features, authenticated API endpoints | Full observability, burn rate alerting, runbooks, canary deploys |
| 99.95% | 0.05% = 20 minutes | 20 min/month | Payment processing, core auth, high-revenue features | Multi-region, automated failover, chaos engineering, quarterly game days |
| 99.99% | 0.01% = 4 minutes | 4 min/month | Financial transaction processing, healthcare data, real-time safety systems | Full multi-region active-active, shadow mode testing, near-zero-downtime deploys, dedicated SRE team |

## Level Differentiation: SLO Knowledge by Engineering Level

| Level | SLI Understanding | SLO Design | Alerting Approach | Error Budget Usage | What They Miss |
|-------|------------------|-----------|------------------|-------------------|---------------|
| L3/Junior | Knows uptime percentage; confuses SLA and SLO | Uses 99.9% because it sounds right | Error rate threshold alerts; alert fatigue is common | Does not use error budget as a decision tool | The hierarchy: why SLI -> SLO -> SLA matters; burn rate alerting; error budget as reliability currency |
| L4/Mid | Understands SLI vs SLO vs SLA distinction; knows error budget = 1 - SLO | Sets SLO from intuition; may measure current reliability first | Basic burn rate alerts; may not use two-window approach | Knows error budget conceptually; does not use it for deploy decisions | Multi-window alerting; user journey SLOs vs endpoint SLOs; SLO tightness calibrated to business risk |
| L5/Senior | Designs SLIs that correlate with user experience; filters health checks; uses P99 not mean | Sets SLO from measurement; uses different SLOs for different tiers; leaves headroom between SLO and SLA | Two-window burn rate alerts; different severity levels for fast vs slow burn | Uses error budget to make deploy and freeze decisions explicitly | SLO review cadence; measuring whether SLO is the right level over time; organizational dynamics of SLO ownership |
| Staff/SRE Lead | User journey SLOs; SLI methodology review; synthetic monitoring for critical paths | SLO tightness based on explicit business risk analysis; cost of each additional 9 in engineering effort | Alerting hierarchy with escalation paths; alert noise measurement and review | Error budget reports as input to quarterly planning; SLO exhaustion as a team-level signal, not just an on-call signal | This is the target: SLOs as a reliability system, not just a metric |
