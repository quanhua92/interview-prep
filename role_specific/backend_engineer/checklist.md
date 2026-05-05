# Backend Engineer -- Prep Checklist

Use this checklist to track your preparation progress across core backend engineering competencies. Aim to complete every item before your interview window opens.

## Topic Prep Checklist per Competency

- [ ] **API Design**: Practice designing RESTful and gRPC APIs, including endpoint naming, versioning, pagination, and error response schemas.
- [ ] **Database Fundamentals**: Review SQL joins, indexing strategies, query optimization, ACID vs BASE, and differences between relational and NoSQL databases.
- [ ] **System Architecture**: Study microservices vs monoliths, service communication patterns (sync/async), and decomposition strategies.
- [ ] **Caching**: Understand cache-aside, write-through, write-back strategies, cache invalidation, and when to use Redis vs Memcached.
- [ ] **Message Queues**: Review use cases for Kafka, RabbitMQ, and SQS; understand topics, partitions, consumer groups, and exactly-once semantics.
- [ ] **Authentication and Authorization**: Be ready to discuss OAuth 2.0 flows, JWT tokens, session management, and RBAC vs ABAC.
- [ ] **Concurrency and Scaling**: Review horizontal vs vertical scaling, load balancing algorithms, connection pooling, and thread-safe patterns.
- [ ] **Observability**: Prepare to discuss logging, distributed tracing, health checks, and metrics collection (Prometheus, Grafana).
- [ ] **API Versioning**: Be ready to discuss URI vs header versioning, backward compatibility, and deprecation strategies.
- [ ] **Exactly-Once Processing**: Review idempotent producers, transactional messaging (Kafka), and deduplication strategies.
- [ ] **Background Jobs**: Understand job queues, delayed processing, dead-letter handling, and worker scaling patterns.
- [ ] **Cascading Failures**: Study circuit breakers, bulkheads, retries with exponential backoff, and timeout budgets in microservices.
- [ ] **Connection Pooling**: Be prepared to explain pool sizing, connection lifecycle, leak detection, and pool exhaustion recovery.

## Practice Questions

1. How would you design a URL shortener service from scratch?
2. Explain the difference between SQL and NoSQL databases and when you would choose one over the other.
3. How do you handle database migrations in a zero-downtime deployment?
4. What strategies do you use to handle API versioning without breaking existing clients?
5. Describe how you would debug a slow API endpoint that sometimes times out.
6. What is eventual consistency and where is it acceptable in a production system?
7. How do you ensure exactly-once message processing in a distributed system?
8. How do you handle cascading failures in a microservices architecture?
9. Explain connection pooling and why it matters for backend performance.
10. Describe how you would implement a background job processing system.
11. How do you ensure data integrity across distributed microservices?
12. Explain the CAP theorem and give a real-world example of a trade-off you have made.
13. What strategies do you use to handle database deadlocks?
14. Describe how you would implement idempotency in a payment processing API.

## System Design Bridge Items

- [ ] Review [Distributed Cache](../../system_design/distributed_cache/) for caching strategies relevant to backend services (cache-aside, write-through, invalidation).
- [ ] Study [Rate Limiter](../../system_design/rate_limiter/) for API protection patterns (token bucket, sliding window, distributed rate limiting).
- [ ] Connect database knowledge to [Key-Value Store](../../system_design/key_value_store/) for understanding storage engine design and consistency trade-offs.
- [ ] Study [News Feed](../../system_design/news_feed/) for fan-out strategies, ranking, and handling high write throughput.
- [ ] Map your API design and microservices knowledge to [Notification Service](../../system_design/notification_service/) (event-driven architecture, delivery guarantees).

## Practice Log

- [ ] 2026-05-__: Completed API design and database fundamentals review
- [ ] 2026-05-__: Walked through system architecture and caching practice problems
- [ ] 2026-05-__: Mock interview session covering all backend competency areas
