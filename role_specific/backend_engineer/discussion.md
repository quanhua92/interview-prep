# Backend Engineer

Designing, building, and maintaining server-side systems that are scalable, reliable, and performant.

## Core Competencies

| Area | Description | Proficiency Expectation |
|------|-------------|------------------------|
| REST API Design | Resource modeling, HTTP methods, status codes, versioning, pagination, HATEOAS | Design clean APIs from scratch; justify design decisions |
| Databases (SQL/NoSQL) | Relational modeling, indexing, query optimization, CAP theorem, sharding, replication | Read query plans; choose the right DB for a given workload |
| Caching | Cache-aside, write-through/write-back, TTL strategies, cache invalidation, distributed caching | Design multi-layer caching; reason about consistency trade-offs |
| Message Queues | Point-to-point vs pub/sub, at-least-once vs exactly-once, backpressure, dead-letter queues | Pick the right messaging pattern; handle failure scenarios |
| Microservices | Service boundaries, inter-service communication, saga pattern, API gateways, service mesh | Decompose a monolith; handle distributed transactions |
| Authentication & Authorization | JWT, OAuth 2.0, RBAC, session management, OWASP Top 10, token rotation | Design secure auth flows; identify common vulnerabilities |
| Performance Optimization | Profiling, connection pooling, N+1 queries, load testing, latency analysis | Diagnose bottlenecks; propose data-driven optimizations |
| Monitoring & Observability | Metrics, structured logging, distributed tracing, alerting, SLOs | Instrument a service; debug production issues with traces |

## Common Interview Topics

- Design a REST API for a specific domain (e.g., e-commerce, social media)
- Explain the difference between SQL and NoSQL and when to use each
- How would you handle database migrations with zero downtime?
- Describe strategies for handling API versioning
- How do you ensure exactly-once message processing?
- Walk through how you would debug a slow API endpoint
- Design a rate limiter for your API
- How do you handle cascading failures in a microservices architecture?
- Explain connection pooling and why it matters
- Describe how you would implement a background job processing system

## Key Terminology

- **Idempotency** -- Making an operation safe to retry without side effects
- **Connection pooling** -- Reusing database connections to reduce overhead
- **N+1 query problem** -- Anti-pattern where N additional queries are issued per parent record
- **Backpressure** -- Flow control mechanism to prevent overwhelming downstream services
- **Circuit breaker** -- Failure detection pattern that stops cascading failures
- **Eventual consistency** -- Guarantee that all replicas converge to the same state over time
- **Sharding** -- Distributing data across multiple database instances by a partition key
- **Schema evolution** -- Managing changes to database or API schemas without breaking consumers

## Cross-References

- **System Design**: [Distributed Cache](../../system_design/distributed_cache/), [Rate Limiter](../../system_design/rate_limiter/), [Key-Value Store](../../system_design/key_value_store/), [News Feed](../../system_design/news_feed/), [Notification Service](../../system_design/notification_service/)
- **CS Fundamentals**: Networking (TCP/HTTP), Operating Systems (processes, threads, concurrency), Databases (ACID, isolation levels, indexing)
