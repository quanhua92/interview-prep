# Data Pipelines

Sources:
- [Apache Airflow Documentation — Core Concepts](https://airflow.apache.org/docs/apache-airflow/stable/core-concepts/)
- [dbt Documentation — What is dbt?](https://docs.getdbt.com/docs/introduction)
- [Apache Kafka Documentation](https://kafka.apache.org/documentation/)
- [Feast Feature Store Documentation](https://docs.feast.dev/)
- [Delta Lake — Build Lakehouses](https://delta.io/)
- [Apache Iceberg Documentation](https://iceberg.apache.org/docs/latest/)
- [Great Expectations Documentation](https://docs.greatexpectations.io/)
- [Soda Core Documentation](https://docs.soda.io/)
- [Prefect Documentation](https://docs.prefect.io/)
- [Dagster Documentation](https://docs.dagster.io/)
- [Temporal Documentation](https://docs.temporal.io/)
- [DVC — Data Version Control](https://dvc.org/)
- [Databricks — Unified Batch/Streaming](https://docs.databricks.com/)
- [Modern Data Stack — getdbt.com](https://www.getdbt.com/)
- [Kappa Architecture — LinkedIn Engineering](https://milinda.pathirage.org/kappa-architecture/)
- [Streaming vs Batch Processing — Confluent](https://developer.confluent.io/)

## One-Liner
Data pipelines move, transform, validate, and serve data from source to consumer — for an AI engineer in 2026 this means mastering batch orchestration (Airflow/dbt), stream processing (Kafka), feature stores (Feast), lakehouse formats (Delta/Iceberg), and AI-specific pipelines (RAG ingestion, embedding generation, vector index building).

## Core Competencies Table

| Area | Description | Proficiency Expectation |
|------|-------------|------------------------|
| Pipeline Fundamentals | ETL vs ELT, batch vs streaming, lambda/kappa architecture, data contracts, ingestion patterns | Explain the tradeoffs between lambda and kappa; design ingestion for a real-time ML feature pipeline |
| Batch Processing | Airflow DAGs/operators/sensors/XComs, dbt transformations/tests, Spark basics, scheduling | Design a multi-step Airflow DAG with conditional branching; write a dbt model with tests and documentation |
| Stream Processing | Kafka topics/partitions/consumer groups/offsets, event-driven architecture, exactly-once semantics, schema registry | Explain Kafka consumer group rebalancing; design an exactly-once streaming pipeline with schema evolution |
| Data Quality | Great Expectations/Soda, data validation contracts, schema enforcement, anomaly detection, data lineage | Design a data quality framework with row-level and aggregate checks; integrate into a CI/CD pipeline |
| Feature Stores | Feast/Tecton, offline vs online features, point-in-time correctness, feature freshness, serving latency | Explain point-in-time correctness and why it prevents data leakage; design a feature serving pipeline for real-time inference |
| Orchestration | Airflow alternatives (Prefect, Dagster, Temporal), DAG design patterns, dependency management, backfills | Compare Airflow vs Dagster vs Temporal; design a backfill strategy for a broken pipeline |
| Data Formats & Storage | Parquet vs Delta Lake vs Iceberg, columnar storage, time-travel queries, ACID on data lakes | Compare Delta vs Iceberg vs Hudi; explain how ACID transactions work on object storage |
| Pipeline Testing | Unit testing transforms, integration testing data flows, data snapshot testing, pipeline CI/CD | Design a testing strategy covering unit, integration, and snapshot tests for a dbt + Airflow pipeline |
| Data Pipeline for AI/ML | Training data pipelines, embedding pipelines, RAG ingestion, data versioning (DVC) | Design an end-to-end RAG ingestion pipeline from document ingestion to vector index serving |
| Production Operations | Monitoring, data freshness alerts, SLAs, backfill strategies, idempotency, failure recovery | Design monitoring for a 50-pipeline DAG; define SLAs and alerting for data freshness violations |

## 1. Pipeline Fundamentals

### ETL vs ELT

| Aspect | ETL (Extract-Transform-Load) | ELT (Extract-Load-Transform) |
|--------|------------------------------|-------------------------------|
| Transform location | Separate transformation server before loading | Transform inside the target data warehouse |
| Best for | On-premises, legacy systems, small-medium data | Cloud data warehouses (Snowflake, BigQuery, Redshift) |
| Tooling | Informatica, Talend, SSIS | dbt, Spark, SQL in warehouse |
| Flexibility | Transform before storage constraint | Leverage warehouse compute power |
| Modern stack trend | Legacy — being replaced by ELT | Default approach in modern data stack |

**Interview answer**: "In 2026, ELT is the default. You extract raw data into a data lake or warehouse, then transform using the warehouse's compute — typically with dbt. This leverages the warehouse's parallelism and avoids maintaining a separate transform layer. ETL still exists where compliance requires sanitizing data before storage or where the target cannot handle raw data."

### Batch vs Streaming

| Aspect | Batch | Streaming |
|--------|-------|-----------|
| Latency | Minutes to hours | Milliseconds to seconds |
| Throughput | Very high (process massive datasets) | Lower per-node (continuous) |
| Ordering | Global sort possible | Approximate ordering (timestamps, watermarks) |
| Fault tolerance | Retry the whole job | Checkpoint and resume from offset |
| Complexity | Simple to reason about | State management, exactly-once semantics |
| Tools | Airflow + Spark + dbt | Kafka + Flink + Spark Streaming |

### Lambda vs Kappa Architecture

**Lambda Architecture** (Nathan Marz):
- Two parallel paths: **batch layer** (recomputes full dataset, high accuracy) + **speed layer** (processes real-time, approximate results)
- **serving layer** merges both views
- Pros: accurate batch + real-time responsiveness
- Cons: maintaining two codebases for the same logic (dual implementation problem)

**Kappa Architecture** (Jay Kreps):
- Single path: everything is a stream. Batch is just a special case of stream replay
- Replay from Kafka log for reprocessing
- Pros: single codebase, simpler architecture
- Cons: stream framework must handle massive historical replay; schema evolution is harder

**Interview answer**: "In 2026, kappa is winning. Stream processing frameworks (Flink, Spark Streaming) can handle batch-scale reprocessing via log compaction and replay. Companies avoid the dual-maintenance cost of lambda. However, lambda persists where regulatory audit requires immutable batch reproducibility."

### Data Contracts

A data contract is a formal agreement between data producers and consumers specifying:
- **Schema**: column names, types, constraints, nullability
- **Semantic meaning**: business definition of each field
- **Quality guarantees**: freshness SLA, completeness thresholds, accuracy bounds
- **Ownership**: who produces, who consumes, escalation contacts
- **Change management**: how breaking changes are communicated (versioned schemas)

Tools: dbt contracts (column types enforcement), Confluent Schema Registry (Avro/Protobuf schemas), Great Expectations (expectation suites as contracts), Soda (contracts as checks).

### Ingestion Patterns

| Pattern | Description | Use Case |
|---------|-------------|----------|
| **Full Load** | Replace entire table on each run | Dimension tables, reference data |
| **Incremental Append** | Only new records since last run | Event logs, transaction records |
| **Change Data Capture (CDC)** | Capture row-level inserts/updates/deletes | Real-time sync between databases (Debezium + Kafka) |
| **Log-based** | Parse application logs as source | Behavioral event ingestion |
| **API-based** | Poll or webhook from source API | Third-party data (Stripe, Salesforce) |

## 2. Batch Processing

### Apache Airflow

Airflow is a platform to programmatically author, schedule, and monitor workflows as **DAGs** (Directed Acyclic Graphs).

**Core Concepts:**

| Concept | Description |
|---------|-------------|
| **DAG** | Directed Acyclic Graph defining task dependencies and execution order |
| **Task** | Single unit of work within a DAG |
| **Operator** | Template for a task (BashOperator, PythonOperator, KubernetesPodOperator, etc.) |
| **Sensor** | Waits for an external event (file landing, API response, time) before proceeding |
| **XCom** | Cross-task communication mechanism — tasks push/pull small data between themselves |
| **DAG Run** | Single execution instance of a DAG (triggered by schedule or manual) |
| **Executor** | Runs tasks (SequentialExecutor for dev, KubernetesExecutor for production, CeleryExecutor for distributed) |
| **Connection** | Configured hook to external systems (database, API, S3) |
| **Pool** | Limits parallel task execution to prevent resource exhaustion |
| **Variable** | Key-value store for configuration (vs Param for runtime input) |

**DAG Design Anti-Patterns to Mention:**

1. **Top-level code** — importing heavy libraries at DAG module level slows parser and causes scheduler pressure. Use `with DAG()` context manager or `@dag` decorator.
2. **No task retries** — always set `retries=3` with exponential backoff.
3. **Monolithic DAGs** — one DAG doing 100 tasks. Split by business domain or data freshness SLA.
4. **Hardcoded dates** — use `{{ ds }}`, `{{ data_interval_start }}` (Airflow 3.x) Jinja templates.
5. **XCom for large data** — XCom stores in metadata DB. For large payloads, use S3/Redis or Object Storage XCom backend.

**Typical Interview Answer — "How would you design a daily ETL DAG?"**

```python
with DAG(
    dag_id="daily_sales_etl",
    schedule="0 6 * * *",
    start_date=datetime(2025, 1, 1),
    catchup=False,
    retries=3,
) as dag:
    check_source_ready = S3KeySensor(
        task_id="check_source_ready",
        bucket="raw-data",
        key="sales/{{ ds }}/sales.parquet",
        timeout=60 * 30,
    )

    extract = PythonOperator(task_id="extract", python_callable=extract_sales)
    validate = PythonOperator(task_id="validate", python_callable=validate_schema)
    load = PythonOperator(task_id="load", python_callable=load_to_warehouse)
    notify = EmailOperator(task_id="notify", to="data-team@example.com", subject="ETL complete")

    check_source_ready >> extract >> validate >> load >> notify
```

### dbt (data build tool)

dbt transforms raw warehouse data into trusted data products. You write SQL `SELECT` statements; dbt handles materialization, dependency resolution, and testing.

**Core Concepts:**

| Concept | Description |
|---------|-------------|
| **Model** | A SQL SELECT statement that materializes as a view, table, or incremental materialization |
| **Source** | Declares raw data location; base tables upstream of models |
| **Ref** | `{{ ref('model_name') }}` — dependency reference, dbt resolves the DAG |
| **Test** | Assertions on data quality (not_null, unique, accepted_values, relationships, custom SQL) |
| **Macro** | Reusable Jinja template for common SQL patterns |
| **Seed** | CSV file loaded as a static table (reference data, mappings) |
| **Snapshot** | Type-2 slowly changing dimension (SCD2) — tracks changes over time |
| **Contract** | Enforces column names and types on materialized models (dbt 1.3+) |
| **Exposure** | Declares downstream BI dashboards or ML models that depend on models |
| **Metric** | Centralized metric definition (replaces duplicated logic in BI tools) |

**Materialization Types:**

| Type | Behavior | Use Case |
|------|----------|----------|
| `view` | No storage, query re-executes | Staging, intermediate models |
| `table` | Full rebuild each run | Small dimension tables, final outputs |
| `incremental` | Append/merge only new data | Large fact tables (>10M rows) |
| `materialized view` | DB-managed refresh | Where warehouse supports it |

**dbt Testing:**

```sql
-- models/staging/stg_orders.sql
{{ config(materialized='table') }}

SELECT
    order_id,
    customer_id,
    order_total,
    order_date
FROM {{ source('raw', 'orders') }}

-- tests/generic/stg_orders_not_null.yml
version: 2
models:
  - name: stg_orders
    columns:
      - name: order_id
        tests:
          - not_null
          - unique
      - name: order_total
        tests:
          - not_null
          - dbt_expectations.expect_column_values_to_be_between:
              min_value: 0
```

**Interview answer — "How do you prevent data quality issues in dbt?":**
"We use a layered approach: (1) dbt built-in tests (not_null, unique, relationships) on every column, (2) custom SQL tests for business logic (e.g., order_total should equal sum of line items), (3) dbt contracts to enforce column types at materialization time, (4) Great Expectations or Soda for runtime checks on production tables, (5) dbt docs auto-generated from model definitions so consumers understand what they're querying."

### Apache Spark Basics

- **Resilient Distributed Dataset (RDD)**: fault-tolerant distributed collection, lowest-level API
- **DataFrame**: structured data with named columns ( Catalyst optimizer + Tungsten execution engine)
- **Partitioning**: data split across cluster nodes; `repartition()` vs `coalesce()` (coalesce avoids shuffle)
- **Lazy evaluation**: transformations (map, filter, join) build a DAG; actions (count, collect, write) trigger execution
- **Shuffle**: cross-partition data movement (expensive); triggered by groupBy, join, distinct, repartition
- **Broadcast join**: small table sent to every executor; avoids shuffle. Threshold: `spark.sql.autoBroadcastJoinThreshold` (default 10MB)
- **Spark in 2026**: dominant for large-scale batch ETL; being supplemented by warehouse-native transforms (dbt) for most use cases. Spark Structured Streaming handles micro-batch and continuous processing.

## 3. Stream Processing

### Apache Kafka Fundamentals

| Concept | Description |
|---------|-------------|
| **Topic** | Log-structured, append-only feed of records. Categories of events (e.g., `orders`, `clicks`) |
| **Partition** | Topics divided into ordered partitions. Parallelism unit — each partition consumed by one consumer in a group |
| **Producer** | Writes records to topic partitions. Controls partitioning via key-based hashing or round-robin |
| **Consumer** | Reads records from partitions. Tracks its position via **offset** |
| **Consumer Group** | Set of consumers sharing topic consumption. Each partition consumed by exactly one consumer in the group |
| **Offset** | Sequential ID for each record within a partition. Consumers commit offsets to track progress |
| **Broker** | Kafka server node. Multiple brokers form a cluster |
| **Zookeeper / KRaft** | Cluster metadata management. Modern Kafka (3.3+) uses KRaft (Zookeeper-free) |
| **Retention** | Time-based or size-based. Old segments deleted or compacted |
| **Log Compaction** | Retains latest value per key. Used for changelog topics and state rebuilding |

**Consumer Group Rebalancing:**
When a consumer joins or leaves a group, Kafka triggers a rebalance — partitions are reassigned. During rebalance, consumption pauses (stop-the-world). **Sticky assignment** strategy minimizes partition movement. **Cooperative rebalancing** (Kafka 2.4+) allows incremental rebalancing without full stop.

**Exactly-Once Semantics:**

| Level | Description |
|-------|-------------|
| At-most-once | Fire and forget. Messages may be lost. Simplest |
| At-least-once | Acknowledge after processing. Messages may be duplicated on failure |
| Exactly-once | Idempotent processing + transactional writes. No duplicates, no losses |

Kafka exactly-once uses **transactional producers** (writes to multiple topics atomically) + **idempotent producers** (deduplication via sequence numbers per partition). Consumers use **read_committed** isolation level to read only transactionally committed messages.

**Interview answer — "How does Kafka guarantee ordering?":**
"Ordering is guaranteed within a single partition only. If you need global ordering, use a single partition (limits parallelism to one consumer). For topic-wide ordering, partition by key so all events for the same entity land on the same partition. Consumer groups provide parallelism — each partition is consumed by exactly one consumer in the group, preserving per-partition order."

### Schema Registry

Confluent Schema Registry stores Avro/Protobuf/JSON Schema definitions and enforces schema compatibility:
- **Backward compatibility**: new schema can read old data (add optional fields)
- **Forward compatibility**: old schema can read new data (add fields with defaults)
- **Full compatibility**: both directions
- Prevents consumers from breaking when producers evolve schemas

### Event-Driven Architecture

```
Producer → Kafka Topic → Consumer Group A (real-time ML features)
                            → Consumer Group B (analytics sink)
                            → Consumer Group C (audit log)
```

**Key patterns:**
- **Event sourcing**: state as a sequence of immutable events, rebuild state by replaying log
- **CQRS**: separate read and write models; writes go to Kafka, reads served from materialized view
- **Changelog-based state**: Kafka as source of truth, consumers build local state via compacted topics

## 4. Data Quality

### Great Expectations

```python
import great_expectations as gx

context = gx.get_context()

validator = context.get_validator(
    batch_request=MyBatchRequest(...),
    expectation_suite_name="orders_expectations"
)

validator.expect_column_values_to_not_be_null("order_id")
validator.expect_column_values_to_be_unique("order_id")
validator.expect_column_values_to_be_between("order_total", min_value=0)
validator.expect_table_row_count_to_be_between(min_value=1000, max_value=5000000)
validator.expect_column_values_to_match_regex("email", r"^[\w-]+@[\w-]+\.[\w-]+$")

validator.save_expectation_suite()
results = validator.validate()
```

**Expectation Types:**
| Category | Examples |
|----------|----------|
| **Table-level** | row count, column count, columns present |
| **Column-level** | not null, unique, type, range, set membership, regex |
| **Multi-column** | column pair A > column pair B, correlation |
| **Cross-table** | referential integrity (foreign key match) |

### Soda

Soda (Soda Core + Soda Cloud) provides data quality checks defined in YAML, integrated into CI/CD:

```yaml
checks for my_dataset:
  - row_count > 0
  - freshness(order_date) < 24h
  - invalid_count(email) < 5%  # regex check
  - missing_count(customer_id) = 0
  - duplicate_count(order_id) = 0
  - values in country must be in ['US', 'GB', 'DE', 'FR']
```

Run `soda scan` in CI/CD pipeline — fail the build if critical checks fail.

### Data Quality Framework Design

**Interview answer — "How would you design a data quality framework?"**
1. **Schema enforcement** at ingestion: validate column types, nullability, constraints before loading
2. **Row-level checks**: not_null, unique, range, regex via dbt tests or Great Expectations
3. **Aggregate checks**: row counts, distribution drift, freshness via Soda or custom monitors
4. **Cross-table checks**: referential integrity between fact and dimension tables
5. **Anomaly detection**: statistical monitoring of metric distributions over time (e.g., `expect_column_kl_divergence_to_be_less_than`)
6. **Lineage tracking**: data lineage from source to downstream consumers (dbt docs, OpenLineage, DataHub)
7. **Alerting**: PagerDuty/Slack alerts on failed checks; data freshness SLA violation

### Data Lineage

Track data flow from source to consumption:
- **dbt docs**: auto-generated lineage graph from `ref()` and `source()` dependencies
- **OpenLineage**: open standard for lineage metadata, integrated with Airflow, Spark, dbt
- **DataHub**: LinkedIn's metadata platform; centralized catalog with lineage, ownership, schema history
- **Apache Atlas**: Hadoop ecosystem metadata management

**Why it matters for AI engineers**: if a feature drifts or a RAG retrieval drops quality, lineage tells you which upstream data source changed.

## 5. Feature Stores

### Why Feature Stores?

**The consistency problem**: Training features computed in batch (offline) may differ from serving features computed at request time (online). This train-serve skew degrades model performance. Feature stores solve this by providing a single source of truth for feature definitions and values.

### Feast (Open Source)

| Component | Description |
|-----------|-------------|
| **Feature Definition** | Python SDK declares features with entities, value types, and data sources |
| **Offline Store** | Historical feature values for training (BigQuery, Snowflake, Redshift, PostgreSQL, file-based) |
| **Online Store** | Low-latency serving for inference (Redis, DynamoDB, Bigtable) |
| **Feature Server** | REST/gRPC endpoint for online retrieval (optional, for non-Python consumers) |
| **Registry** | Metadata store (feature definitions, entity relationships) in SQLite or PostgreSQL |

**Point-in-Time Correctness**:

The #1 reason to use a feature store. When building a training dataset, you must use feature values as they were at the time of the event — not future values that leaked through.

```
Example: Predicting churn on day 15.
Without PIT correctness: training data includes features computed on day 20 (future leak).
With PIT correctness: features for day 15's prediction use only data available <= day 15.
```

Feast handles this by joining entity timestamps against feature event timestamps.

**Feature Freshness**:
- **Batch features**: updated on a schedule (hourly, daily). Stale between updates
- **Streaming features**: pushed to online store via Flink/Kafka consumer. Seconds-level freshness
- **On-demand features**: computed at request time from raw data (e.g., "items purchased in last 24 hours")

### Tecton (Commercial)

Managed feature store with built-in stream processing. Provides:
- **Feature pipelines**: declarative transformations from raw data sources
- **Real-time serving**: sub-10ms p99 latency
- **Enterprise features**: RBAC, governance, audit logs, data lineage

### Feature Store for AI Engineers

**RAG-relevant patterns:**
- Store pre-computed document embeddings as features in the feature store
- Compute user-document interaction features (clicks, dwell time) for re-ranking
- Maintain freshness of embedding features when documents are updated

**Interview answer — "What is point-in-time correctness and why does it matter?":**
"When building ML training datasets, you must use feature values as they existed at the time of the event you're predicting — not as they are today. Without this, future information leaks into training, causing inflated offline metrics but degraded production performance. A feature store like Feast joins features by entity + timestamp, ensuring each training example only sees data available at that point in time."

## 6. Orchestration

### Airflow vs Alternatives

| Tool | Language | Strengths | Weaknesses | Best For |
|------|----------|-----------|------------|----------|
| **Apache Airflow** | Python (DAG files) | Massive ecosystem, battle-tested, huge community | DAG parser scalability, scheduler bottleneck, complex UX | Data engineering teams, mature orgs |
| **Prefect** | Python (functions + decorators) | Simple API, dynamic DAGs, native Kubernetes, excellent DX | Smaller community than Airflow | Teams wanting simpler setup, dynamic workflows |
| **Dagster** | Python (assets + ops) | Asset-centric model, built-in software-defined assets, type system | Smaller ecosystem, learning curve | Data platform teams, asset governance |
| **Temporal** | Go/Java/Python/TS | Durably executed workflows, code-first, fault-tolerant, supports long-running | Not data-native, general-purpose workflow engine | Application workflows, microservice orchestration |

### Dagster — Asset-Centric Model

Dagster models data pipelines as **software-defined assets** (SDAs) rather than tasks:

```python
from dagster import asset, DailyPartitionsDefinition

daily_partitions = DailyPartitionsDefinition(start_date="2025-01-01")

@asset(partitions_def=daily_partitions)
def raw_orders(context):
    return read_from_s3(context.partition_key)

@asset(partitions_def=daily_partitions,
       deps=[raw_orders])
def cleaned_orders(raw_orders):
    return raw_orders.dropna(subset=["customer_id"])
```

Key difference from Airflow: you define *what data exists* (assets) rather than *what tasks run*. Dagster computes the execution plan from asset dependencies.

### DAG Design Patterns

1. **Fan-out/Fan-in**: One task produces multiple downstream tasks, which converge before the next stage
2. **Conditional branching**: Use `BranchOperator` (Airflow) to route to different paths based on runtime value
3. **Dynamic task generation**: Generate tasks at runtime from configuration (e.g., one task per table)
4. **Sensor-based triggering**: Wait for upstream data availability before starting downstream
5. **Task groups**: Logical grouping of related tasks in Airflow UI (Airflow 2.3+)

### Backfill Strategies

| Scenario | Strategy |
|----------|----------|
| Small time range (< 1 week) | Airflow `backfill` command with `catchup=True` |
| Large time range (months/years) | Batched backfill — Airflow DAG with manual `execution_date` triggers |
| Idempotent backfill | Redo the entire period — since operations are idempotent, duplicates are harmless |
| Partition-based backfill | Process each partition independently; parallelize across partitions |
| Delta backfill | Only process dates where upstream data changed (Airflow data-aware scheduling) |

**Interview answer — "How do you handle a backfill for 2 years of data?"**
"First, verify the pipeline is idempotent — rerunning should produce the same result. Then process in weekly or monthly batches with Airflow, using `pool` to limit parallelism and avoid overloading the warehouse. Monitor warehouse queue times and adjust concurrency. For incremental models, ensure the merge key handles deduplication correctly."

## 7. Data Formats & Storage

### Columnar vs Row-Based Storage

| Format | Storage Layout | Best For | Read Speed |
|--------|---------------|----------|------------|
| CSV / JSON | Row-based | Logging, small files, human-readable | Full row scan needed |
| **Parquet** | Columnar | Analytics, large datasets | Read only needed columns (10-100x faster) |
| **ORC** | Columnar | Hive ecosystem | Similar to Parquet, Hive-optimized |
| **Avro** | Row-based with schema | Streaming, Kafka serialization | Fast writes, schema evolution |

**Columnar benefits**: (1) Read only needed columns — Parquet query on 3 of 200 columns reads 1.5% of data, (2) Compression — similar types in same block compress better (10:1 vs 3:1 for row-based), (3) Predicate pushdown — skip entire row groups based on column statistics (min/max values stored in footer).

### Lakehouse Formats: Delta Lake vs Apache Iceberg vs Apache Hudi

| Feature | Delta Lake | Apache Iceberg | Apache Hudi |
|---------|-----------|----------------|-------------|
| **ACID Transactions** | Yes (transaction log) | Yes (snapshot isolation) | Yes (MVCC) |
| **Time Travel** | VERSION AS OF, TIMESTAMP AS OF | AS OF TIMESTAMP, VERSION | Point-in-time queries |
| **Schema Evolution** | Add/drop columns, change types | Full schema evolution (add, drop, rename, reorder, widen) | Schema evolution |
| **Partition Evolution** | Manual (requires rewrite) | Hidden partitioning — evolve without rewrite | Yes |
| **Multi-engine** | Spark, Flink, Trino, Presto, Hive | Spark, Flink, Trino, Presto, Hive, Snowflake, BigQuery, Dremio | Spark, Flink, Trino |
| **UniForm compatibility** | Delta UniForm (read by Iceberg/Hudi) | Native open table format | Hudi MOR can be read as Iceberg |
| **Delete support** | MERGE, UPDATE, DELETE (row-level) | Row-level deletes (position or equality) | Write-side: insert, upsert, delete |
| **Catalog support** | Unity Catalog, Hive Metastore, AWS Glue | Nessie, Hive, AWS Glue, Polaris | Hive Metastore |
| **Community** | Databricks, LF Projects | Open source, broad community | Uber, Apache |

**Interview answer — "Delta vs Iceberg?"**
"Both provide ACID transactions on data lakes. Delta has the strongest Databricks ecosystem integration and Unity Catalog. Iceberg leads on multi-engine support and hidden partitioning (which lets you change partition scheme without rewriting data — a huge advantage at petabyte scale). In 2026, Iceberg is gaining broader adoption because it's engine-agnostic, but Delta's UniForm bridges the gap. For a new project on Snowflake or BigQuery, Iceberg is the natural choice. For Databricks shops, Delta is seamless."

### ACID on Object Storage

How do you get ACID on immutable S3 objects? **Transaction logs**.

Delta Lake: each write creates a new JSON commit file in the `_delta_log` directory. Readers read the latest version; old versions remain for time travel. Writes are optimistic — if two writers conflict, one retries. The commit protocol: (1) stage data files, (2) compute new log entry, (3) atomically rename (if path exists, someone else committed first — retry).

Iceberg: metadata tree (metadata file → manifest list → manifest → data files). Snapshots point to a specific manifest list. W3C-style optimistic concurrency.

### Time Travel

```sql
-- Delta Lake
SELECT * FROM orders VERSION AS OF 5;
SELECT * FROM orders TIMESTAMP AS OF '2025-12-01 00:00:00';

-- Iceberg
SELECT * FROM orders VERSION AS OF 5;
SELECT * FROM orders FOR SYSTEM_VERSION AS OF 5;

-- RESTORE to a previous version
RESTORE TABLE orders VERSION AS OF 5;
```

Use cases: audit compliance, debugging data corruption, reproducing model training datasets, rolling back bad deployments.

## 8. Pipeline Testing

### Testing Pyramid for Data Pipelines

| Level | Scope | Tool | Example |
|-------|-------|------|---------|
| **Unit tests** | Single transform function | pytest + df/pandas | Test SQL logic in dbt with `dbt test --select my_model` |
| **Integration tests** | End-to-end pipeline on sample data | dbt test, Airflow test DAG | Run DAG against dev database with fixture data |
| **Snapshot tests** | Output stability over time | Great Expectations, Soda | Compare today's row count/distribution against baseline |
| **Contract tests** | Schema compatibility | dbt contracts, Schema Registry | Producer/consumer schema compatibility check |
| **End-to-end tests** | Full pipeline on production mirror | Airflow + dbt on staging | Weekly full pipeline run on production data clone |

### dbt Testing Strategy

1. **Generic tests** (built-in): `not_null`, `unique`, `accepted_values`, `relationships`
2. **Custom SQL tests**: `SELECT COUNT(*) FROM model WHERE condition > threshold`
3. **dbt-expectations**: Great Expectations port for dbt (distribution, KLD, regex)
4. **Contract tests**: enforce column names + types at materialization time
5. **Schema tests**: `dbt test --schema` runs all generic tests
6. **CI/CD integration**: `dbt compile && dbt test` in GitHub Actions pre-merge

### Airflow Pipeline Testing

```bash
# Test DAG structure (no execution)
airflow dags test my_dag 2025-01-01

# Test individual task in isolation
airflow tasks test my_dag task_id 2025-01-01

# Validate DAG file parses correctly
python -c "from my_dag import dag; print(dag.tasks)"
```

### Data Snapshot Testing

Compare data characteristics against a known-good baseline:
```python
# Great Expectations — snapshot comparison
expectation_suite_name = "orders_snapshot"
validator.expect_table_row_count_to_match_other_table("orders_baseline")
validator.expect_column_values_to_match_json_hash("fingerprint_column")
```

**Interview answer — "How do you test a data pipeline?"**
"I use four levels: (1) unit tests on individual SQL transformations with sample data fixtures, (2) dbt's built-in tests (not_null, unique, relationships) on every model column, (3) Great Expectations suites for distribution checks and cross-table integrity, (4) end-to-end integration test running the full DAG on a staging environment with production-like data. Everything runs in CI — dbt test and Great Expectations fail the build on contract violations."

## 9. Data Pipeline for AI/ML

### Training Data Pipelines

```
Raw data sources (APIs, DBs, logs, S3)
  → Ingestion (Airflow DAG, Kafka consumers)
  → Validation (Great Expectations, dbt tests)
  → Transformation (dbt models, Spark jobs)
  → Feature computation (Feast offline store, batch scoring)
  → Dataset creation (Feast materialize, DVC tracked)
  → Model training (MLflow tracked)
  → Evaluation
  → Deployment
```

### Embedding Pipelines (Batch Vectorization)

For RAG systems and embedding-based retrieval, a batch embedding pipeline:

```
Documents (S3 / DB / crawled)
  → Chunking (split into 200-512 token chunks)
  → Text cleaning (remove HTML, normalize whitespace)
  → Embedding generation (OpenAI API / local model / Spark + sentence-transformers)
  → Vector store ingestion (Pinecone, Weaviate, pgvector, Qdrant, ChromaDB)
  → Index building (HNSW, IVF)
  → Metadata indexing (source URL, chunk ID, timestamp)
```

**Scale considerations:**
- For 1M+ documents, batch embed in parallel with Spark (sentence-transformers on GPU nodes) or with API-based embedding providers (batched requests)
- Embedding models: OpenAI `text-embedding-3-large` (3072 dims), Cohere, or local `bge-m3`
- Cost: 1M documents x 500 tokens avg = 500M tokens ~$750 with text-embedding-3-small

### RAG Ingestion Pipeline Design

```
Source documents (web pages, PDFs, knowledge base articles)
  → Fetch & parse (BeautifulSoup, LiteParse, Unstructured.io)
  → Chunk (recursive character splitting with overlap)
  → Deduplicate (MinHash / SimHash for near-duplicate detection)
  → Embed (batch via API or local model)
  → Upsert to vector store (with metadata: source, last_updated, chunk_id)
  → Schedule: Airflow DAG running daily or on webhook trigger (new document alert)
  → Monitoring: embedding drift detection, index health, retrieval relevance metrics
```

### Data Versioning (DVC)

**DVC (Data Version Control)** tracks datasets and models alongside code in Git:
- Stores data pointers in Git (`.dvc` files), actual data in cloud storage (S3, GCS, Azure Blob)
- `dvc push/pull` syncs data between local and remote
- Connects datasets to model experiments: reproduce any training run exactly
- Works with `dvc.yaml` pipelines (define stages and dependencies declaratively)

**DVC pipeline for ML:**
```yaml
# dvc.yaml
stages:
  prepare:
    cmd: python prepare.py
    deps:
      - data/raw/
    outs:
      - data/prepared/
  train:
    cmd: python train.py
    deps:
      - data/prepared/
    params:
      - model.lr
      - model.epochs
    outs:
      - model.pkl
  evaluate:
    cmd: python evaluate.py
    deps:
      - model.pkl
      - data/test/
    metrics:
      - metrics.json
```

## 10. Production Operations

### Pipeline Monitoring

| Metric | What to Monitor | Tool |
|--------|-----------------|------|
| **Data freshness** | Time since last successful write per table | Great Expectations freshness, Soda freshness, custom Airflow sensor |
| **Pipeline health** | Task success/failure rates, duration trends | Airflow UI, Grafana, Datadog |
| **Data volume** | Row counts, file sizes per partition | dbt test + Great Expectations `expect_table_row_count_to_be_between` |
| **Schema changes** | New/dropped/renamed columns | dbt contracts, Schema Registry, Soda schema checks |
| **Data quality scores** | Pass rate of expectations | Great Expectations data docs, Soda Cloud |
| **Downstream impact** | Which dashboards/models depend on this data | dbt exposures + lineage, DataHub |

### SLAs

Define freshness SLAs per dataset:

| Dataset | Freshness SLA | Alerting | Escalation |
|---------|---------------|----------|-------------|
| `users` | < 1 hour | Slack #data-alerts after 30 min | On-call engineer after 1 hour |
| `transactions` | < 15 minutes | PagerDuty after 15 min | Data lead after 30 min |
| `embeddings` | < 24 hours | Slack #rag-team after 18 hours | ML lead after 24 hours |

Airflow `sla` parameter on tasks: `sla_miss_callback` triggers when a task exceeds its time threshold.

### Idempotency

**Critical property**: running the same pipeline twice produces the same result. Achieved by:
- **Upsert/merge**: `MERGE INTO target USING source ON key WHEN MATCHED UPDATE WHEN NOT MATCHED INSERT`
- **Idempotent writes**: overwrite partition rather than append
- **Deduplication**: `ROW_NUMBER() OVER (PARTITION BY key ORDER BY timestamp DESC) WHERE rn = 1`
- **Atomic swaps**: write to temp table → `DROP TABLE old; ALTER TABLE new RENAME TO old;`

### Failure Recovery

| Failure | Recovery Strategy |
|---------|-------------------|
| Single task failure | Automatic retry (Airflow retries with exponential backoff) |
| Upstream data delay | Sensor with timeout + SLA alert |
| Bad data in source | Quarantine bad records, process valid ones, alert data engineering |
| Warehouse outage | Airflow task fails, retry after warehouse recovery |
| Schema evolution mismatch | Schema Registry rejects incompatible writes; producer fixes schema |
| Pipeline code bug | Fix code, deploy, backfill affected date range |

## Interview Questions

### Q1: Explain ETL vs ELT. When would you choose one over the other?

**Model answer**: "ETL transforms data before loading into the target; ELT loads raw data first and transforms inside the warehouse. In 2026, ELT is the default — you extract raw data into a data lake or warehouse, then transform using dbt or SQL in the warehouse. This leverages the warehouse's parallelism and avoids maintaining a separate transform layer. I'd choose ETL only when compliance requires sanitizing PII before storage, or when the target system cannot handle raw data. The modern data stack is ingestion (Fivetran, Airbyte) → raw tables → dbt transformations → curated tables → downstream consumption."

### Q2: How does Kafka ensure exactly-once delivery?

**Model answer**: "Kafka provides exactly-once semantics through three mechanisms: (1) Idempotent producers assign a sequence number per message per partition. If the broker sees a duplicate sequence number, it discards the duplicate, (2) Transactional producers use a two-phase commit protocol to atomically write to multiple partitions — either all commits or none, (3) Consumers use `isolation.level=read_committed` to read only transactionally committed messages. This prevents duplicates on producer retries and ensures consumers never see partially committed transactions. The tradeoff is higher latency and complexity — you need to manage transactional IDs and handle broker failover correctly."

### Q3: What is point-in-time correctness and why does it matter for ML?

**Model answer**: "Point-in-time correctness means using feature values as they existed at the time of the event being predicted, not future values. Without it, future information leaks into training data — a model trained on leaked data shows inflated offline metrics but degrades in production because those future features won't be available at inference time. Feature stores like Feast enforce this by joining entity timestamps against feature event timestamps when building training datasets. For example, if I'm predicting churn on day 15, the training row for that user uses features from day 15 or earlier, never day 20. This is the primary value proposition of feature stores."

### Q4: Design a data pipeline for a RAG system that ingests new documents and keeps embeddings fresh.

**Model answer**: "I'd build this as an Airflow DAG with three stages. First, an ingestion stage: fetch new documents from source (web crawler, S3 uploads, or DB change events), parse and chunk them with overlap for context preservation. Second, an embedding stage: batch the chunks and call an embedding API (OpenAI text-embedding-3-small or a local model like bge-m3), parallelizing with Spark if processing 100K+ chunks. Third, an upsert stage: write embeddings + metadata (source URL, chunk ID, timestamp, last_updated) to the vector store (pgvector for Postgres-native, Pinecone/Weaviate for managed). For freshness, the DAG runs daily and on webhook trigger for urgent updates. I'd also track which documents were last updated — only re-embed changed documents (delta sync) rather than full reindex. Monitoring includes embedding drift detection and retrieval relevance metrics (MRR, recall@k)."

### Q5: Compare Delta Lake and Apache Iceberg. Which would you recommend?

**Model answer**: "Both provide ACID transactions, time travel, and schema evolution on data lakes. Delta Lake uses a transaction log (`_delta_log`) with optimistic concurrency — each write creates a new JSON commit. Iceberg uses a metadata tree (metadata file → manifest list → manifest → data files). The key differentiator in 2026 is partition evolution: Iceberg has hidden partitioning, so you can change your partition scheme without rewriting petabytes of data — Delta requires a full rewrite. Iceberg also has broader multi-engine support (Spark, Flink, Trino, Snowflake, BigQuery). Delta has stronger Databricks ecosystem integration and Unity Catalog. Delta's UniForm (Universal Format) lets Iceberg clients read Delta tables. For a new project on a multi-engine stack, I'd recommend Iceberg. For Databricks shops, Delta is seamless."

### Q6: How do you test a dbt + Airflow pipeline end to end?

**Model answer**: "Four levels. First, unit tests: each dbt model has generic tests (not_null, unique, relationships) and custom SQL tests for business logic — run with `dbt test`. Second, snapshot tests: Great Expectations suites that compare row counts, distributions, and column checksums against a known-good baseline. Third, integration tests: Airflow DAG test runs against a staging environment with fixture data — `airflow tasks test my_dag task_id 2025-01-01`. Fourth, end-to-end: full pipeline run on a production data clone weekly. All of this runs in CI — `dbt compile && dbt test` on every pull request, Airflow DAG validation on commit, and Great Expectations in the staging environment before promoting to production."

### Q7: What happens when a Kafka consumer group rebalances?

**Model answer**: "When a consumer joins or leaves a group, Kafka triggers a rebalance — partitions are reassigned to consumers. During the rebalance, consumption pauses, which is called a stop-the-world event. There are two strategies: eager rebalancing (all consumers revoke all partitions and reassign from scratch — simple but causes a full pause) and cooperative/incremental rebalancing (Kafka 2.4+, consumers only revoke the partitions being moved — other partitions continue consuming). To minimize rebalance frequency, use sticky assignment (keeps existing assignments where possible) and stable consumer group membership (avoid dynamic scaling). For processing large state, use Kafka Streams' standby tasks to reduce recovery time after rebalance."

### Q8: You need to backfill 6 months of data for a dbt incremental model. How do you approach this?

**Model answer**: "First, verify the incremental model's merge/upsert logic handles idempotency — reprocessing the same date should produce the same result. Then run `dbt run --select my_model --vars '{"start_date': "2025-01-01", "end_date": "2025-06-01"}'` in weekly batches. Monitor warehouse queue times and concurrency — if the warehouse is overloaded, use Airflow to trigger weekly batches with `pool` to limit parallelism. After the backfill, validate with dbt tests and Great Expectations to confirm row counts and distributions match expectations. Finally, update the model's `incremental_strategy` to resume normal incremental processing from the current date."

### Q9: What is a data contract and how would you enforce one?

**Model answer**: "A data contract is a formal agreement between data producers and consumers specifying schema (columns, types, constraints), quality guarantees (freshness SLA, completeness thresholds), semantic definitions (what each field means), ownership, and change management. To enforce: (1) dbt contracts enforce column names and types at materialization time — if a producer changes a column type, the downstream model fails, (2) Schema Registry enforces Avro/Protobuf schema compatibility for streaming data, (3) Great Expectations suites define the quality contract — run in CI/CD to block deployments that violate quality thresholds, (4) dbt docs auto-generate documentation from model definitions, making the contract self-documenting. The key is shifting quality left — catch violations at the producer, not at the consumer."

### Q10: How do you monitor data freshness in production?

**Model answer**: "I use a layered approach. First, Airflow SLAs: set `sla` on tasks with `sla_miss_callback` to trigger Slack alerts when tasks exceed their time threshold. Second, data-level freshness checks: Great Expectations `expect_column_max_to_be_between` on a timestamp column, or Soda `freshness(col) < 1h`. Run these as periodic checks (every 15 minutes) on the actual data table. Third, downstream impact tracking: dbt exposures connect datasets to dashboards and models — if freshness violates SLA, alert the specific downstream consumers. Fourth, dashboard: Grafana or Datadog visualizing freshness per dataset with escalation tiers — Slack after first threshold, PagerDuty after critical threshold."

### Q11: Design a feature serving pipeline for a real-time fraud detection model.

**Model answer**: "Two paths. Batch path: nightly Spark job computes aggregate features (transaction frequency, average amount, geographic patterns) over 30-day windows, writes to Feast offline store, then materializes to Feast online store (Redis/DynamoDB) for serving. Streaming path: Kafka consumer processes individual transactions in real-time, computes rolling-window features (transactions in last 5 minutes, distance from last transaction), pushes to Feast online store. At inference time, the fraud model calls the feature server to fetch both batch features (historical aggregates) and streaming features (last 5 minutes) with a single entity key lookup. Point-in-time correctness is maintained by Feast when building training data from the offline store — each training example uses features as of the event timestamp, preventing future leakage. Feature freshness: batch features updated daily, streaming features updated within seconds."

### Q12: Explain how data versioning with DVC fits into an ML pipeline.

**Model answer**: "DVC tracks datasets and models alongside code in Git. It stores lightweight pointer files (`.dvc`) in Git while the actual data lives in cloud storage (S3, GCS). The key benefit: any training run is fully reproducible — `dvc checkout` restores the exact dataset version, `git checkout` restores the exact code, and the combination reproduces the exact model. DVC pipelines (`dvc.yaml`) define stages with dependencies — data preparation, training, evaluation — with each stage's inputs, outputs, and parameters tracked. When a dataset changes, DVC detects the change, reruns only affected downstream stages, and tracks the new model artifact. This integrates with CI/CD: on merge, DVC runs the pipeline, tracks metrics, and auto-evaluates against thresholds."

## Key Terminology

**ETL (Extract-Transform-Load)** -- Traditional pipeline pattern where data is extracted from sources, transformed on a separate processing layer, then loaded into a target. Being replaced by ELT in modern stacks where transformation happens inside the target data warehouse.

**ELT (Extract-Load-Transform)** -- Modern pipeline pattern: extract raw data and load directly into a data warehouse, then transform using the warehouse's compute (typically dbt SQL models). Default approach in the modern data stack.

**DAG (Directed Acyclic Graph)** -- Core abstraction in Airflow and orchestration tools. Defines task dependencies as a directed graph with no cycles — tasks execute in topological order based on upstream completion.

**Lambda Architecture** -- Dual-path architecture with a batch layer (full recompute for accuracy) and a speed layer (real-time approximate processing), merged at a serving layer. Largely replaced by kappa architecture.

**Kappa Architecture** -- Single-path architecture where everything is a stream. Batch is a special case of replaying the log. Eliminates dual-maintenance of batch and stream codebases.

**CDC (Change Data Capture)** -- Pattern for capturing row-level inserts, updates, and deletes from a source database in real-time. Debezium reads database transaction logs and publishes changes to Kafka topics.

**Schema Registry** -- Centralized service storing and enforcing data schemas (Avro, Protobuf, JSON Schema) for streaming pipelines. Enables schema evolution with backward/forward/full compatibility checks.

**Exactly-Once Semantics** -- Message delivery guarantee where each message is processed exactly once — no duplicates and no losses. Achieved via idempotent producers, transactional writes, and read_committed consumer isolation.

**Feature Store** -- Centralized system for managing ML features across training (offline) and serving (online). Feast and Tecton provide point-in-time correct feature retrieval, preventing data leakage.

**Point-in-Time Correctness** -- Using feature values as they existed at the time of the predicted event, not future values. Prevents data leakage where future information inflates offline model metrics.

**Lakehouse** -- Architecture combining data lake storage (S3, ADLS, GCS) with data warehouse features (ACID transactions, schema enforcement, time travel) via table formats like Delta Lake, Iceberg, or Hudi.

**Time Travel** -- Ability to query a table at a specific version or timestamp. All three lakehouse formats support this for audit, debugging, and reproduction.

**Columnar Storage** -- Data stored by column rather than row. Formats like Parquet enable reading only needed columns (10-100x faster for analytics) and achieve higher compression ratios.

**Data Contract** -- Formal agreement between data producers and consumers specifying schema, quality SLAs, semantic definitions, ownership, and change management. Enforced via dbt contracts, Schema Registry, Great Expectations.

**Data Lineage** -- Tracking data flow from source through transformations to downstream consumers. Tools: dbt docs, OpenLineage, DataHub. Critical for debugging data quality issues and impact analysis.

**Idempotency** -- Property where running the same operation multiple times produces the same result. Essential for pipeline reliability: retries, backfills, and reprocessing must not create duplicates.

**DVC (Data Version Control)** -- Git-like version control for datasets and ML models. Stores pointer files in Git, actual data in cloud storage. Enables reproducible ML experiments by tracking exact dataset + code + parameter combinations.

**UniForm (Delta Universal Format)** -- Delta Lake feature that enables Iceberg and Hudi clients to read Delta tables. Bridges the lakehouse format interoperability gap.

**Hidden Partitioning (Iceberg)** -- Iceberg's partition scheme is defined in table metadata, not exposed in queries. Partition columns can be changed without rewriting data, unlike Delta Lake where partition changes require full rewrites.

## Cross-References

- **cs_fundamentals/databases** -- SQL queries, ACID transactions, indexing, storage engines (B-Tree vs LSM-Tree) underpin all data pipeline storage and transformation
- **cs_fundamentals/distributed_systems** -- CAP theorem, consensus, replication patterns relevant to Kafka clusters and distributed pipeline execution
- **cs_fundamentals/system_design_framework** -- Pipeline design patterns, scalability considerations for data infrastructure
- **production_engineering/ai_safety_compliance** -- Data quality as safety for LLM systems, audit trails for data lineage
- **system_design/rag_system** -- Vector store ingestion, embedding pipelines, RAG data flow (directly builds on pipeline fundamentals)
- **data_analytics/sql_foundations** -- SQL patterns used throughout dbt transformations and pipeline queries
- **cs_fundamentals/databases** -- Star/snowflake schemas, fact/dimension tables, normalization — the warehouse models that pipeline transformations produce
- **role_specific/senior_ai_engineer** -- Feature platform ownership, ML data pipeline architecture, production ML infrastructure
