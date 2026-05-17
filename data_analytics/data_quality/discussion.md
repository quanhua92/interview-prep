# Analytics Data Quality

Source: [Data Quality Monitoring: Schema Drift, Null Rates, Freshness SLAs, and Anomaly Detection for Analytics (CalibreOS)](https://www.calibreos.com/learn/analytics-data-quality)

## One-Liner
Design a defense-in-depth data quality system that catches schema drift, null spikes, freshness breaches, and volume anomalies before they corrupt dashboards and decisions.

## Requirements

### Functional
- Detect schema drift (column renames, type changes, field removal) silently corrupting metrics
- Monitor null rates on key columns (user_id, transaction_id) with adaptive baselines
- Enforce freshness SLAs tiered by table business criticality
- Catch volume anomalies (row-count drops/spikes) with seasonality-aware detection
- Validate referential integrity (broken joins, orphan keys)
- Provide lineage-based triage from broken source to stale dashboard

### Non-Functional
- Alert latency under minutes for Tier 0 tables
- Scale to thousands of tables without alert fatigue
- Minimize compute overhead (metadata-only where possible)
- Each alert must have: owner, severity, runbook URL

### Scale Estimates
- 1000+ tables per organization
- Row counts vary 10x between weekday and weekend
- Late-arriving events (stream processing watermarks)
- Hundreds of Kafka topics with schema evolution

## Key Concepts

### Data Quality Layers (Defense-in-Depth)
1. **Contract tests at ingest**: Schema registry (Avro/Protobuf/JSON Schema) with compatibility modes
2. **Transformation assertions**: dbt tests, GX expectation suites
3. **Freshness/volume monitors**: SLA sensors on Airflow/Dagster, statistical anomaly detection
4. **BI-layer validation**: Dashboard sanity checks, metric definition drift detection

### Check Types and Severity
| Signal | P0? | Detector | Owner |
|--------|-----|----------|-------|
| Freshness breach | Yes | Airflow SLA sensor | DE oncall |
| Row count drop 50% | Yes | Anomaly on daily inserts | DE |
| Null spike on key column | Yes | Column stats monitor | Mobile + DE |
| Slow drift in mean | Maybe | Bayesian change point | DS + DE |
| Schema add column | No | Registry diff | Platform |

### Table Tiering for SLAs
- **Tier 0** (revenue, experimentation, fraud): SLA of minutes; breach triggers page
- **Tier 1** (daily operational dashboards): SLA of 1-4 hours; breach triggers Slack alert
- **Tier 2** (weekly reporting, ad-hoc): SLA of 12-24 hours; breach logged only

## Key Design Decisions

### Schema Drift Detection
- **Schema registry contracts**: Confluent Schema Registry enforces BACKWARD/FORWARD/FULL compatibility; incompatible schemas fail CI/CD
- **Column-level fingerprinting**: Hash schema (names + types + order) hourly; diff against baseline
- **SELECT * ban**: Explicit column lists prevent silent NULL reads from upstream renames
- **Deployment order**: BACKWARD = consumers first; FORWARD = producers first; FULL = either

### Null Rate Monitoring
- **EWMA baselines** over static thresholds: `baseline_t = alpha * nullrate_t + (1-alpha) * baseline_{t-1}`; alert if deviation exceeds N standard deviations
- **Seasonality-aware**: Separate baselines per day-of-week; handles weekend/weekday variance
- **Dimensional breakdowns**: Null rate by OS version, country, app version accelerates root cause

### Freshness SLA Measurement
- **Event-time lag**: `NOW() - MAX(event_timestamp)` -- data arrival delay from source
- **Processing-time lag**: `NOW() - MAX(partition_write_timestamp)` -- pipeline execution delay
- **Watermarks**: Define "how late is too late" for stream processing; SLA accounts for watermark tolerance

### Anomaly Detection Method Choice
- **EWMA + stddev bands**: Low complexity, 2-4 weeks training, no auto-seasonality; best for thousands of tables
- **Prophet**: Auto trend + seasonality, 6+ weeks training; best for high-value tables
- **STL decomposition**: Explainable, manual period config; best when interpretability matters
- **PCA bundling (Uber DQM)**: Correlates metrics into table-level quality scores; reduces alerts 5-10x

## Deep Dives

### Schema Registry and Compatibility Modes
- **BACKWARD**: New schema reads old data; add optional/remove fields; upgrade consumers first
- **FORWARD**: Old schema reads new data; upgrade producers first
- **FULL_TRANSITIVE**: Compatibility enforced across all historical versions
- **Migration rules (JSONata/CEL)**: Transform old-to-new at deserialization; enables controlled breaking changes without reprocessing

### Great Expectations in Production
- **Expectations**: Assertions (not_null, unique, between); 50+ built-in, custom via Python
- **Expectation Suites**: One per table, versioned in Git, part of CI/CD
- **Checkpoints**: Execute suite against date-scoped partitions (not full table); integrate with Airflow/dbt/Databricks
- **Anti-patterns**: Row-level validations on billion-row tables (cost spike); static + runtime validation merge bugs; no grace period for new tables

### Monte Carlo Data Observability
- **Metadata-only approach**: Reads `information_schema`, not `COUNT(*)` on data; zero compute cost increase
- **ML-based auto-baselining**: Learns patterns over 6-week window; auto freshness/volume/schema alerts
- **Dependency suppression**: Upstream freshness failure suppresses downstream alerts; avoids alert storms
- **Complements GX**: Monte Carlo for unknown-unknowns (broad ML coverage); GX for known-knowns (strict contracts on Tier 0)

### Uber D3/DQM Production Patterns
- **D3 (Dataset Drift Detector)**: Monitors 300+ Tier 0/1 tables; reduced time-to-detect from 45 days to 2 days
- **DQM**: PCA bundles correlated metrics into table-level quality scores; one alert instead of 20 per table
- **Sustain period**: 4-hour window; alert only if anomaly persists, prevents transient blips
- **Dependency suppression**: Freshness is dependency for volume/null checks; one root cause = one alert

### Alert Fatigue Prevention
- Page only on consumer-facing SLA breaks
- Route noisy checks to Slack with auto-ticket if persists N runs
- Use seasonality-aware thresholds (not static)
- Sustain period: wait N consecutive failures before alerting
- Grace periods for new tables (1-2 weeks)

### Data Contract Anti-Patterns
- Auto-cast everything to string (defeats type safety)
- Skip compatibility checks in production but enforce in dev (defeats left-shift)
- No ownership metadata in contracts (unforceable without responsible team)

## Follow-Ups
- How would you design freshness SLAs for a real-time streaming pipeline with late-arriving events?
- Row counts dropped 30% day-over-day -- what is your triage order?
- How would you build a data quality platform for 1000+ tables without alert fatigue?
- How do you handle a column rename that silently corrupts downstream dashboards?
- How would you implement data contracts across federated Kafka clusters (PayPal pattern)?
- What happens when a mobile SDK bug causes null rate to spike from 2% to 60% on a Friday night?
- How do you distinguish metric definition drift (PM changed funnel) from actual data corruption?
