# Data Pipelines — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Problem Framing (2-3 min)
- [ ] State the core tension: data pipelines are the backbone of every AI/ML system — garbage in, garbage out
- [ ] Cite key facts to establish scope:
  - [ ] Modern data stack: ingestion → raw tables → dbt transformations → curated tables → downstream
  - [ ] ETL → ELT shift: transform inside warehouse, not in separate layer
  - [ ] Lambda → Kappa: single codebase for batch and stream
  - [ ] Lakehouse formats (Delta/Iceberg) bring ACID to data lakes
- [ ] Frame for AI engineering: pipelines feed training data, embeddings, features, and RAG indexes

## Phase 2: Pipeline Fundamentals (3-4 min)
- [ ] Explain ETL vs ELT:
  - [ ] ETL: extract → transform on separate server → load
  - [ ] ELT: extract → load raw into warehouse → transform with warehouse compute (dbt)
  - [ ] ELT is default in 2026; ETL only for compliance/PII sanitization
- [ ] Compare batch vs streaming:
  - [ ] Batch: minutes to hours latency, very high throughput, simple reasoning
  - [ ] Streaming: milliseconds to seconds, continuous processing, state management complexity
- [ ] Explain Lambda vs Kappa architecture:
  - [ ] Lambda: batch layer + speed layer + serving layer (dual codebase problem)
  - [ ] Kappa: everything is a stream, batch = log replay (single codebase)
  - [ ] Kappa winning in 2026; lambda persists for regulatory audit
- [ ] Describe data contracts:
  - [ ] Schema (columns, types, constraints)
  - [ ] Quality guarantees (freshness SLA, completeness)
  - [ ] Semantic definitions, ownership, change management
  - [ ] Enforced by dbt contracts, Schema Registry, Great Expectations

## Phase 3: Batch Processing (3-4 min)
- [ ] Walk through Apache Airflow core concepts:
  - [ ] DAG, Task, Operator, Sensor, XCom, Executor, Connection, Pool, Variable
  - [ ] Airflow 3.x uses `data_interval_start` instead of `execution_date`
- [ ] Describe 5 DAG design anti-patterns:
  - [ ] Top-level heavy imports (scheduler pressure)
  - [ ] No task retries
  - [ ] Monolithic DAGs (split by domain/SLA)
  - [ ] Hardcoded dates (use Jinja templates)
  - [ ] XCom for large data (use S3/Object Storage XCom backend)
- [ ] Walk through dbt core concepts:
  - [ ] Model (SQL SELECT, materialized as view/table/incremental)
  - [ ] Source, Ref, Test, Macro, Seed, Snapshot, Contract, Exposure, Metric
  - [ ] Materialization types: view (no storage), table (full rebuild), incremental (append/merge)
- [ ] Describe dbt testing strategy:
  - [ ] Generic tests: not_null, unique, accepted_values, relationships
  - [ ] Custom SQL tests: business logic assertions
  - [ ] dbt-expectations: distribution, KLD, regex
  - [ ] Contracts: enforce column names + types
- [ ] Mention Spark basics:
  - [ ] DataFrame (structured, Catalyst optimizer, Tungsten engine)
  - [ ] Lazy evaluation: transformations build DAG, actions trigger execution
  - [ ] Broadcast join for small tables, partitioning, shuffle considerations

## Phase 4: Stream Processing (3-4 min)
- [ ] Walk through Kafka fundamentals:
  - [ ] Topic (append-only log), Partition (parallelism unit)
  - [ ] Producer (writes to partitions), Consumer (reads from partitions, tracks offset)
  - [ ] Consumer Group (each partition consumed by exactly one consumer)
  - [ ] Broker (server node), KRaft (Zookeeper-free metadata)
- [ ] Explain consumer group rebalancing:
  - [ ] Triggered when consumer joins/leaves
  - [ ] Eager rebalancing: all partitions revoked, full pause
  - [ ] Cooperative/incremental rebalancing (2.4+): only moved partitions pause
  - [ ] Sticky assignment minimizes partition movement
- [ ] Explain exactly-once semantics:
  - [ ] Idempotent producers: sequence numbers per partition, dedup on broker
  - [ ] Transactional producers: two-phase commit across multiple partitions
  - [ ] Consumers: `isolation.level=read_committed` to skip uncommitted messages
- [ ] Describe Schema Registry:
  - [ ] Stores Avro/Protobuf/JSON Schema definitions
  - [ ] Enforces backward/forward/full compatibility
  - [ ] Prevents consumers from breaking on schema evolution
- [ ] Mention event-driven patterns:
  - [ ] Event sourcing: state as immutable event sequence
  - [ ] CQRS: separate read/write models via Kafka
  - [ ] Changelog-based state: compacted topics for state rebuilding

## Phase 5: Data Quality (3-4 min)
- [ ] Walk through Great Expectations:
  - [ ] Expectation types: table-level (row count, column count), column-level (not null, unique, range, regex), multi-column, cross-table
  - [ ] Suites as contracts, data docs for visualization
- [ ] Describe Soda:
  - [ ] YAML-based checks: row_count, freshness, missing_count, duplicate_count, values in
  - [ ] `soda scan` in CI/CD — fail build on violations
- [ ] Design a data quality framework:
  - [ ] Schema enforcement at ingestion
  - [ ] Row-level checks (dbt tests / Great Expectations)
  - [ ] Aggregate checks (row counts, distribution drift, freshness)
  - [ ] Cross-table checks (referential integrity)
  - [ ] Anomaly detection (statistical monitoring over time)
  - [ ] Lineage tracking (dbt docs, OpenLineage, DataHub)
  - [ ] Alerting (PagerDuty/Slack on failed checks, freshness SLA violations)
- [ ] Explain data lineage importance:
  - [ ] If a feature drifts, lineage tells you which upstream source changed
  - [ ] Tools: dbt docs, OpenLineage, DataHub

## Phase 6: Feature Stores (3-4 min)
- [ ] Explain the consistency problem:
  - [ ] Training features (batch) may differ from serving features (online) → train-serve skew
  - [ ] Feature store provides single source of truth
- [ ] Walk through Feast components:
  - [ ] Feature Definition (Python SDK)
  - [ ] Offline Store (historical, for training: BigQuery, Snowflake, Redshift, PostgreSQL)
  - [ ] Online Store (low-latency serving: Redis, DynamoDB, Bigtable)
  - [ ] Feature Server (REST/gRPC endpoint)
  - [ ] Registry (metadata in SQLite/PostgreSQL)
- [ ] Explain point-in-time correctness:
  - [ ] Use feature values as they existed at the event timestamp, not future values
  - [ ] Without PIT: future information leaks into training → inflated metrics
  - [ ] Feast joins entity timestamps against feature event timestamps
- [ ] Describe feature freshness:
  - [ ] Batch features: scheduled (hourly/daily), stale between updates
  - [ ] Streaming features: pushed via Flink/Kafka consumer, seconds-level freshness
  - [ ] On-demand features: computed at request time
- [ ] Mention Tecton: managed feature store with stream processing, sub-10ms p99

## Phase 7: Orchestration (3-4 min)
- [ ] Compare Airflow vs alternatives:
  - [ ] Airflow: Python DAGs, massive ecosystem, scheduler bottleneck
  - [ ] Prefect: Python decorators, dynamic DAGs, excellent DX
  - [ ] Dagster: asset-centric model (software-defined assets), type system
  - [ ] Temporal: durable workflows, general-purpose (not data-native)
- [ ] Explain Dagster's asset model:
  - [ ] Define what data exists (assets) rather than what tasks run
  - [ ] Dagster computes execution plan from asset dependencies
  - [ ] Software-defined assets with partitioning
- [ ] List DAG design patterns:
  - [ ] Fan-out/Fan-in
  - [ ] Conditional branching (BranchOperator)
  - [ ] Dynamic task generation
  - [ ] Sensor-based triggering
  - [ ] Task groups for logical grouping
- [ ] Describe backfill strategies:
  - [ ] Small range: Airflow backfill with catchup=True
  - [ ] Large range: batched backfill (weekly/monthly), pool for concurrency
  - [ ] Idempotent backfill: redo entire period safely
  - [ ] Partition-based: process partitions independently
  - [ ] Delta backfill: only process dates with changed upstream data

## Phase 8: Data Formats & Storage (3-4 min)
- [ ] Compare columnar vs row-based:
  - [ ] Columnar (Parquet): read only needed columns, better compression (10:1 vs 3:1)
  - [ ] Predicate pushdown: skip row groups based on min/max in footer
- [ ] Compare lakehouse formats:
  - [ ] Delta Lake: transaction log (_delta_log), Unity Catalog, Databricks ecosystem
  - [ ] Apache Iceberg: metadata tree, hidden partitioning (no rewrite), multi-engine
  - [ ] Apache Hudi: write-side (insert, upsert, delete), Uber origin
  - [ ] UniForm: Delta tables readable by Iceberg/Hudi clients
- [ ] Explain ACID on object storage:
  - [ ] Transaction logs (Delta) or metadata trees (Iceberg) on immutable S3
  - [ ] Optimistic concurrency: stage files, compute log entry, atomic rename
  - [ ] If rename fails (path exists), someone else committed — retry
- [ ] Describe time travel:
  - [ ] Query table at specific version or timestamp
  - [ ] Use cases: audit, debugging corruption, reproducing training data, rollbacks

## Phase 9: Pipeline Testing & AI/ML Pipelines (3-4 min)
- [ ] Walk through the testing pyramid:
  - [ ] Unit tests: single transform function, sample data fixtures, pytest + dbt test
  - [ ] Integration tests: full DAG on sample data, staging environment
  - [ ] Snapshot tests: compare row counts/distributions against baseline
  - [ ] Contract tests: schema compatibility, dbt contracts, Schema Registry
  - [ ] End-to-end tests: full pipeline on production mirror, weekly
- [ ] Describe dbt testing in CI/CD:
  - [ ] `dbt compile && dbt test` on every pull request
  - [ ] Airflow DAG validation on commit
  - [ ] Great Expectations in staging before production promotion
- [ ] Design embedding pipeline for RAG:
  - [ ] Documents → chunking (200-512 tokens with overlap) → embed (API or local model)
  - [ ] Upsert to vector store (pgvector, Pinecone, Weaviate, Qdrant)
  - [ ] Index building (HNSW, IVF), metadata indexing
  - [ ] Scale: Spark + sentence-transformers for GPU parallelism, or batched API calls
- [ ] Describe RAG ingestion pipeline:
  - [ ] Fetch → parse → chunk → deduplicate (MinHash/SimHash) → embed → upsert
  - [ ] Airflow DAG daily + webhook trigger for urgent updates
  - [ ] Delta sync: only re-embed changed documents
  - [ ] Monitoring: embedding drift, index health, retrieval relevance (MRR, recall@k)
- [ ] Explain DVC for data versioning:
  - [ ] Pointer files in Git, actual data in cloud storage (S3, GCS)
  - [ ] dvc.yaml pipelines: stages with dependencies, params, metrics, outputs
  - [ ] Reproduce any training run: dvc checkout dataset + git checkout code
  - [ ] Integration with CI/CD: run pipeline on merge, track metrics

## Phase 10: Production Operations (3-4 min)
- [ ] Walk through pipeline monitoring:
  - [ ] Data freshness: time since last successful write
  - [ ] Pipeline health: task success/failure rates, duration trends
  - [ ] Data volume: row counts, file sizes per partition
  - [ ] Schema changes: new/dropped/renamed columns
  - [ ] Data quality scores: pass rate of expectations
  - [ ] Downstream impact: which dashboards/models depend on this data
- [ ] Design SLA framework:
  - [ ] Per-dataset freshness SLAs (users: < 1hr, transactions: < 15min, embeddings: < 24hr)
  - [ ] Escalation tiers: Slack → PagerDuty → data lead
  - [ ] Airflow SLA with sla_miss_callback
- [ ] Explain idempotency:
  - [ ] Upsert/merge, overwrite partitions, deduplication with ROW_NUMBER
  - [ ] Atomic swaps: write to temp → drop old → rename new
  - [ ] Same pipeline twice = same result
- [ ] Describe failure recovery strategies:
  - [ ] Single task: automatic retry with exponential backoff
  - [ ] Upstream delay: sensor with timeout + SLA alert
  - [ ] Bad data: quarantine bad records, process valid ones, alert
  - [ ] Warehouse outage: retry after recovery
  - [ ] Schema mismatch: Schema Registry rejects, producer fixes
  - [ ] Code bug: fix, deploy, backfill affected range

## Practice Questions

1. Explain ETL vs ELT. When would you choose one over the other?
2. How does Kafka ensure exactly-once delivery? Walk through the mechanism.
3. What is point-in-time correctness and why does it matter for ML training?
4. Design a data pipeline for a RAG system ingesting documents and keeping embeddings fresh.
5. Compare Delta Lake and Apache Iceberg. Which would you recommend and when?
6. How do you test a dbt + Airflow pipeline end to end?
7. What happens during a Kafka consumer group rebalance? How do you minimize disruption?
8. You need to backfill 6 months of data for a dbt incremental model. Walk through your approach.
9. What is a data contract? How would you design and enforce one?
10. How do you monitor data freshness in production?
11. Design a feature serving pipeline for real-time fraud detection.
12. How does DVC fit into an ML pipeline alongside Git?
13. A downstream dashboard shows stale data but the Airflow DAG shows green. How do you debug?
14. Your Kafka consumer starts falling behind on a high-volume topic. What do you do?
15. How would you migrate from a batch-only pipeline to a streaming-aware architecture?

## Phase 11: System Design Bridge (2-3 min)
- [ ] Connect data pipelines to the full AI engineer stack:
  - [ ] Databases (SQL, ACID) → data pipeline storage and transformation
  - [ ] Distributed systems (CAP, replication) → Kafka cluster design, pipeline fault tolerance
  - [ ] RAG system design → embedding pipelines, vector store ingestion, freshness
  - [ ] SQL foundations → dbt model SQL, pipeline query patterns
  - [ ] Senior AI engineer role → feature platform ownership, ML data pipeline architecture
- [ ] Emphasize the bridge: data pipelines are the infrastructure that makes all AI systems work
- [ ] Key tradeoff to articulate: batch simplicity vs streaming latency vs operational complexity

## Phase 12: Wrap-Up & Synthesis (2-3 min)
- [ ] Summarize the 10 topic areas covered
- [ ] Reiterate the core insight: ELT + dbt is the modern default; streaming for latency-critical paths; feature stores prevent train-serve skew; lakehouse formats bring ACID to object storage
- [ ] Highlight the AI engineer angle: embedding pipelines, RAG ingestion, feature stores, and DVC are what differentiate a data engineer from an AI pipeline engineer
- [ ] Connect to production reality: idempotency, monitoring, SLAs, and backfill strategies are what keep pipelines running
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
