# Data Engineer -- Prep Checklist

Use this checklist to track your preparation progress across core data engineering competencies. Aim to complete every item before your interview window opens.

## Topic Prep Checklist per Competency

- [ ] **ETL/ELT Pipelines**: Practice designing batch and streaming pipelines, understand the extract-transform-load workflow, and be able to compare ETL vs ELT trade-offs.
- [ ] **Data Modeling**: Review star schema, snowflake schema, slowly changing dimensions (SCD Type 1/2/3), and normalization for analytical workloads.
- [ ] **SQL Proficiency**: Master window functions, CTEs, aggregate functions, subqueries, and be comfortable writing complex analytical queries.
- [ ] **Big Data Technologies**: Understand the architecture of Spark, Hadoop (HDFS, MapReduce), and distributed data processing concepts.
- [ ] **Data Warehousing**: Be familiar with columnar vs row-based storage, data partitioning, and platforms like Snowflake, BigQuery, or Redshift.
- [ ] **Streaming and Real-Time Processing**: Review Kafka, Flink, and Spark Streaming; understand event time vs processing time and watermarks.
- [ ] **Data Quality and Governance**: Prepare to discuss data validation, schema evolution, data lineage, and tools like Great Expectations or dbt.
- [ ] **Orchestration**: Understand scheduling and dependency management with Airflow, Dagster, or Prefect; know DAG patterns, idempotent tasks, and backfill strategies for production pipelines.

## Practice Questions

1. How would you design a data pipeline to ingest and process clickstream data in near real-time?
2. Explain the difference between a star schema and a snowflake schema. When would you use each?
3. How do you handle late-arriving data in a streaming pipeline?
4. Describe how you would migrate a legacy ETL pipeline to a modern ELT approach.
5. What is the difference between row-based and columnar storage, and how does it affect query performance?
6. How would you design an idempotent data pipeline that can safely reprocess failed batches?
7. Explain how Airflow DAGs work and how you would handle dependencies between tasks.
8. What strategies do you use to optimize slow SQL queries on large datasets?
9. How do you ensure data quality across multiple upstream sources?
10. Describe how you would implement slowly changing dimensions in a data warehouse.
11. What is schema evolution and how do you handle it in production pipelines?
12. How would you design a data lake architecture that supports both batch and streaming workloads?
13. Explain the concept of data partitioning and how you would choose partition keys.
14. How do you monitor data pipelines and alert on failures or data anomalies?
15. How do you manage backfills for a production pipeline without impacting ongoing operations?

## System Design Bridge Items

- [ ] Review [Notification Service](../../system_design/notification_service/) for understanding event-driven pipelines, fan-out patterns, and delivery guarantees.
- [ ] Connect data extraction knowledge to [Web Crawler](../../system_design/web_crawler/) for data pipeline design, URL deduplication, and large-scale data ingestion.
- [ ] Study [News Feed](../../system_design/news_feed/) for event aggregation patterns, ranking, and handling high write throughput.
- [ ] Review distributed storage systems and data replication for understanding how data platforms scale horizontally.

## Practice Log

- [ ] 2026-05-__: Completed SQL proficiency and data modeling review
- [ ] 2026-05-__: Walked through ETL/ELT pipeline and streaming design problems
- [ ] 2026-05-__: Mock interview session covering all data engineering competency areas
