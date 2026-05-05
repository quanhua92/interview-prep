# Data Engineer

Building reliable data infrastructure that moves, transforms, and makes data accessible for analytics and ML.

## Core Competencies

| Area | Description | Proficiency Expectation |
|------|-------------|------------------------|
| ETL/ELT Pipelines | Extract, transform, load patterns; batch vs streaming; pipeline orchestration | Design end-to-end pipelines; handle schema evolution |
| Data Warehousing | Star/snowflake schemas, slowly changing dimensions, columnar storage, partitioning | Model a warehouse schema; optimize query performance |
| Streaming Systems | Kafka, Spark Streaming, Flink, windowing, watermarking, exactly-once semantics | Design a real-time pipeline; reason about latency vs correctness |
| SQL Proficiency | Window functions, CTEs, query optimization, execution plans, complex aggregations | Write and optimize complex analytical queries |
| Data Modeling | Entity-relationship modeling, normalization, denormalization, data contracts | Choose the right model for the use case |
| Orchestration | Airflow DAGs, task dependencies, idempotency, retry strategies, backfills | Build reliable DAGs; handle failure recovery |
| Data Quality | Validation rules, anomaly detection, data lineage, Great Expectations, data contracts | Design a data quality framework; catch issues before downstream |
| Big Data Tools | Spark, Hadoop, Parquet, Delta Lake, data lakehouse architecture | Process large datasets efficiently; choose file formats |

## Common Interview Topics

- Design a data pipeline for processing user event data
- Explain the difference between batch and stream processing
- How do you handle late-arriving data in a streaming pipeline?
- Design a schema for a data warehouse for an e-commerce platform
- How would you ensure data quality across your pipelines?
- Explain windowing strategies in stream processing (tumbling, sliding, session)
- How do you handle schema evolution without breaking downstream consumers?
- Describe how you would optimize a slow SQL query on a large table
- Design an idempotent ETL pipeline
- How do you manage backfills for a production pipeline?

## Key Terminology

- **Lambda architecture** -- Combining batch and stream processing layers for low-latency and accuracy
- **Slowly Changing Dimensions (SCD)** -- Techniques for tracking historical changes in dimension tables
- **Watermarking** -- Mechanism to track progress in event time within a streaming system
- **Data lakehouse** -- Architecture combining data lake storage with warehouse-style management
- **Idempotency** -- Ensuring a pipeline produces the same result when run multiple times
- **Schema registry** -- Centralized service for storing and enforcing data schemas (e.g., Confluent Schema Registry)
- **Change Data Capture (CDC)** -- Tracking row-level changes in a database for incremental processing
- **Data contract** -- Formal agreement between data producers and consumers on schema and quality

## Cross-References

- **System Design**: [Notification Service](../../system_design/notification_service/) (event-driven pipelines), [Web Crawler](../../system_design/web_crawler/) (data extraction pipelines), [News Feed](../../system_design/news_feed/) (event aggregation)
- **CS Fundamentals**: Databases (ACID, indexing, query optimization), Distributed Systems (consistency, replication), Algorithms (sorting, hashing, graph traversal)
