# Analytics Data Quality -- Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem: data quality is a defense-in-depth system, not a single check
- [ ] Ask clarifying questions:
  - [ ] What data sources are we monitoring (Kafka streams, batch ETL, warehouse tables)?
  - [ ] What is the table count and what tiering model is used?
  - [ ] Are we building in-house or using a platform (Monte Carlo, GX)?
- [ ] List functional requirements (3-5 items):
  - [ ] Detect schema drift (column renames, type changes, field removal)
  - [ ] Monitor null rates on key columns with adaptive baselines
  - [ ] Enforce tiered freshness SLAs (Tier 0: minutes, Tier 1: hours, Tier 2: best-effort)
  - [ ] Catch volume anomalies with seasonality-aware detection
  - [ ] Provide lineage-based triage from source to dashboard
- [ ] List non-functional requirements:
  - [ ] Alert latency under minutes for Tier 0
  - [ ] Scale to 1000+ tables without alert fatigue
  - [ ] Minimize compute (metadata-only where possible)
  - [ ] Every alert has owner, severity, runbook URL
- [ ] State your scale estimates:
  - [ ] 1000+ tables, hundreds of Kafka topics
  - [ ] Row counts vary 10x weekday vs weekend
  - [ ] Late-arriving events (watermark tolerance)

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw a layered architecture: [Source] -> [Schema Registry] -> [Ingest] -> [Transform (dbt)] -> [Warehouse] -> [BI]
- [ ] Show defense-in-depth: contract tests at ingest -> transformation assertions -> freshness/volume monitors -> BI validation
- [ ] Identify the main check categories:
  - [ ] **Freshness**: `NOW() - MAX(event_timestamp)` per table tier
  - [ ] **Volume**: row-count anomaly detection (EWMA/Prophet)
  - [ ] **Schema**: registry diff, column fingerprinting
  - [ ] **Distribution**: null rate EWMA, distinct count, value ranges
  - [ ] **Referential integrity**: broken join detection, orphan keys
- [ ] Define table tiering model:
  - [ ] Tier 0 (revenue, experimentation, fraud): SLA minutes, page oncall
  - [ ] Tier 1 (daily operational dashboards): SLA 1-4 hours, Slack alert
  - [ ] Tier 2 (weekly reporting): SLA 12-24 hours, log only
- [ ] Present the diagram and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain schema drift detection strategy:
  - [ ] Schema registry with compatibility modes (BACKWARD, FORWARD, FULL)
  - [ ] Deployment order: BACKWARD = consumers first, FORWARD = producers first
  - [ ] Migration rules (JSONata/CEL) for controlled breaking changes
  - [ ] SELECT * ban with explicit column lists in production SQL
- [ ] Explain null rate monitoring approach:
  - [ ] EWMA baseline: `baseline_t = alpha * nullrate_t + (1-alpha) * baseline_{t-1}`
  - [ ] Alert if deviation exceeds N stddev (N=3 low-noise, N=2 sensitive)
  - [ ] Seasonality-aware: separate baselines per day-of-week
  - [ ] Dimensional breakdowns by OS, country, app version
- [ ] Explain freshness SLA measurement:
  - [ ] Event-time lag vs processing-time lag
  - [ ] Watermarks for late data in streaming pipelines
  - [ ] Orchestration integration: Airflow SLA miss callbacks, Dagster freshness checks
  - [ ] Lineage-based triage: OpenLineage/Marquez for upstream/downstream deps
- [ ] Explain anomaly detection method choice:
  - [ ] EWMA + stddev: simple, thousands of tables, no auto-seasonality
  - [ ] Prophet: auto trend + seasonality, high-value tables
  - [ ] STL: explainable, manual period config
  - [ ] PCA bundling (Uber DQM): reduces alerts 5-10x via correlated metric scoring

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss Great Expectations integration:
  - [ ] Expectations (not_null, unique, between) grouped into suites per table
  - [ ] Checkpoints run date-scoped partitions, not full tables (avoid cost spike)
  - [ ] Suites versioned in Git as CI/CD deployment gate
  - [ ] Anti-pattern: row-level validation on billion-row tables
- [ ] Discuss Monte Carlo for broad observability:
  - [ ] Metadata-only approach reads information_schema, zero compute cost
  - [ ] ML auto-baselining over 6-week rolling window
  - [ ] Dependency suppression: upstream freshness failure suppresses downstream alerts
  - [ ] Complements GX (unknown-unknowns vs known-knowns)
- [ ] Discuss alert fatigue prevention:
  - [ ] Page only on consumer-facing SLA breaks
  - [ ] Sustain period: alert only if anomaly persists N consecutive runs
  - [ ] Grace period for new tables (1-2 weeks before alerts fire)
  - [ ] Dependency suppression: freshness failure suppresses volume/null alerts
- [ ] Discuss triage order when a metric looks wrong:
  - [ ] 1. Is the pipeline fresh? (max event timestamp lag)
  - [ ] 2. Did row counts move? (join keys dropped, silent fanout loss)
  - [ ] 3. Schema change? (renamed column reads NULL downstream)
  - [ ] 4. Definition drift? (PM changed funnel, data correct but semantics moved)
- [ ] Discuss data contract anti-patterns:
  - [ ] Auto-cast to string defeats type safety
  - [ ] Skip compatibility checks in prod but enforce in dev defeats left-shift
  - [ ] No ownership metadata makes contracts unforceable

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize: "I tier tables by business criticality, enforce schema contracts at ingest, run transformation assertions in dbt, track freshness with SLA thresholds, and use seasonality-aware anomaly detection. Every alert has an owner and runbook."
- [ ] State trade-offs: EWMA simplicity vs Prophet sophistication; metadata-only coverage vs full data scans; alert sensitivity vs fatigue
- [ ] Mention improvements with more time: automated lineage propagation, self-healing pipelines, ML-based root cause attribution

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
