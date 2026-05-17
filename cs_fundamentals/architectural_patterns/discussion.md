# Architectural Patterns for Distributed Systems

Source: [Architectural Patterns (CalibreOS)](https://www.calibreos.com/learn/hld-architectural-patterns)

## One-Liner
Recognize which of 10 recurring patterns a system design problem requires, then apply the proven solution template -- pattern-first thinking beats memorizing case studies.

## Functional Requirements
- Identify the dominant architectural pattern(s) in any system design problem within 60 seconds
- Apply the correct solution template for each of the 10 patterns: Read Scaling, Write Scaling, Real-Time Delivery, Async Work Offloading, Contention Management, Large Object Storage, Distributed Consistency, Service Communication, Data Partitioning, and Fault Isolation
- Compose multiple patterns together (most real systems need 2-3)
- Articulate the forcing function (the number or constraint that makes the pattern necessary) before proposing the solution

## Non-Functional Requirements
- Pattern recognition should be instantaneous -- this is about decomposition, not invention
- Each pattern has a clear trigger condition (e.g., read QPS > 10K/sec, operation > 500ms, business op spans services)
- Solutions must include the trade-off, not just the upside
- Staff-level expectation: derive the number first, then the pattern follows

## Key Scale Questions
- 10 patterns cover the hard parts of virtually every distributed system design question
- "Design Twitter" = Write Scaling (fan-out) + Real-Time Delivery (feed push)
- "Design Uber" = Contention Management (atomic driver assignment) + Real-Time Delivery (location updates)
- "Design Stripe" = Distributed Consistency (payment across services) + Contention Management (idempotent retries)
- Each pattern has a threshold: reads > 5-10K/sec, writes > 2-5K/sec, operation > 500ms, concurrent writers on same resource, dataset exceeds one node, etc.

## Core Components

### Pattern 1: Read Scaling
- **L1 In-process cache**: HashMap in app memory, sub-microsecond, ~100MB cap, not shared across pods
- **L2 Distributed cache**: Redis Cluster at ~0.5ms, 100K+ ops/sec, cache-aside with TTL
- **L3 CDN**: CloudFront/Fastly at <50ms globally, for publicly cacheable content only
- **L4 Read replicas**: 1-3 PostgreSQL replicas, 2-5ms latency, async replication lag 0-100ms
- Key insight: Redis at $500/mo absorbs 100K read QPS; a 4th read replica at $5K/mo adds only 5K QPS -- cache first, replicate second
- Cache write strategies: cache-aside (default), write-through (strong consistency), write-behind (write-heavy), read-through (managed)
- Three invalidation failure modes: TTL too long (stale reads), cache stampede on cold start, inconsistent invalidation across replicas

### Pattern 2: Write Scaling
- **Vertical sharding**: different tables on different DB servers by service boundary
- **Horizontal sharding**: one table split across N nodes by hash(key) % N
- **CQRS**: separate write model (normalized, PostgreSQL) from read model (denormalized, Elasticsearch/Redis) synced via Kafka
- **Event sourcing**: append-only immutable events, no UPDATE/DELETE contention, state derived by replay
- Production insight: CQRS + Kafka solves 10K-100K writes/sec without sharding. Sharding is the last resort, not the first choice

### Pattern 3: Real-Time Delivery
- **Long polling**: server holds request up to 30s, ~1 HTTP handshake per 30s, for low-frequency updates
- **SSE**: unidirectional HTTP/2 stream, browser-native auto-reconnect, for dashboards/notifications
- **WebSockets**: bidirectional full-duplex TCP, ~2KB RAM per connection, for chat/gaming/collaboration
- Routing architecture: every WS gateway subscribes to Redis Pub/Sub channel per user; backend publishes to `user:{id}:events`; at 1M users = ~100 WS servers at 10K connections each

### Pattern 4: Async Work Offloading
- **Fire-and-forget**: write to Kafka/SQS, return 202 Accepted, worker processes asynchronously (emails, audit logs)
- **Fan-out**: one event triggers N downstream writes (300K feed insertions via Kafka workers)
- **Long-running jobs**: job record in DB with status, publish job_id to Kafka, client polls or gets webhook
- **Distributed workflows (Saga)**: choreography (<4 steps, simple) vs orchestration via Temporal (complex, durable execution)
- Dead letter queues after 3-5 retries with exponential backoff -- never discard silently

### Pattern 5: Contention Management
- **Pessimistic locking (SELECT FOR UPDATE)**: row-level lock, for low-concurrency high-value ops (payments, seat reservation)
- **Optimistic concurrency (OCC)**: version counter + conditional UPDATE, no lock held, retries under contention (O(concurrency^2))
- **Queue-based serialization**: route writes for same entity to single Kafka partition, serialize at infrastructure level
- **Idempotency keys**: client-generated UUID, server stores result with unique constraint, check + execute + store in one transaction

### Pattern 6: Large Object Storage
- **Pre-signed URL upload**: client gets S3 URL from API, uploads directly -- bytes never touch app servers
- **Chunked multipart upload**: files >100MB split into 5-100MB parts, upload in parallel, up to 5TB per object
- **CDN delivery**: CloudFront edge PoPs cache at ~200 global locations, <50ms delivery
- **Content-addressed storage**: store by SHA-256 hash, deduplicate identical files (Dropbox reported 40% storage reduction)
- Metadata in PostgreSQL/DynamoDB, never binary data in DB

### Pattern 7: Distributed Consistency
- **2PC**: atomic but blocking -- coordinator crash after PREPARE locks participants indefinitely. Only use within single DB cluster
- **Outbox pattern**: write domain record + outbox event in one local transaction; poller/CDC publishes to Kafka. Production standard for "write + publish event"
- **Saga (choreography)**: each service emits events, reacts to others. Simple but hard to debug beyond 4 steps
- **Saga (orchestration via Temporal)**: durable workflow function, survives crashes, explicit compensation logic. Used at Uber, Airbnb, Stripe

### Pattern 8: Service Communication
- **gRPC for internal**: Protobuf 5-10x smaller/faster than JSON, HTTP/2 multiplexing, type-safe .proto stubs, ~1ms vs ~5-10ms REST
- **REST for external**: universal client support, human-readable JSON, full browser compatibility
- **Kafka for async internal**: durable event log, multiple consumer groups, millions of messages/sec
- **SQS for simple task queues**: managed, one producer to one consumer, <10K msg/sec
- Rule: gRPC is strictly better than REST internally on every technical axis; the only reason not to is developer familiarity

### Pattern 9: Data Partitioning
- **Hash sharding (hash(key) % N)**: uniform distribution, no range queries, resharding moves ~50% of keys
- **Consistent hashing**: virtual ring 0 to 2^32, adding node moves only ~1/N keys. Virtual nodes (150-300 per server) for uniform load
- **Range sharding**: supports range queries but sequential keys create hot shards (all writes to last shard)
- Shard key must match dominant query pattern; query without shard key = O(N) scatter-gather across all shards
- Cross-shard queries: maintain separate Elasticsearch/ClickHouse for analytics, never OLAP on sharded OLTP

### Pattern 10: Fault Isolation
- **Circuit breaker**: monitors failure rate, opens at threshold (50% failures in 10s), fail-fast in ~1ms, half-open probe after 30-60s cooldown
- **Bulkhead**: separate thread pools per downstream dependency; slow Payments won't starve DB or Cache pools
- **Retry + exponential backoff + jitter**: 3-5 retries, doubling delay, +/-25% jitter to prevent thundering herd
- **Timeout + deadline propagation**: gRPC deadline propagation so abandoned requests cancel downstream work
- **Load shedding**: return 503 for non-critical requests when capacity is exhausted, preserve critical paths

## Key Design Decisions

### Pattern Selection
- **Option A: Derive first, then propose**: calculate QPS/latency from requirements, identify which thresholds are crossed, name the pattern explicitly. Staff-level signal.
- **Option B: Propose technology first**: "I'd add Redis here" -- 6/10 answer, no forcing function articulated.
- **Option C: Memorize case studies**: brittle, fails on novel systems like auction engines or sensor pipelines.

### CQRS vs Direct Sharding
- **Option A: CQRS + Kafka**: handles 10K-100K writes/sec without sharding. Two schemas to maintain, eventual consistency on reads (~50-500ms lag).
- **Option B: Horizontal sharding**: linear write scale with N shards but high operational cost (resharding, cross-shard queries). Last resort.
- **Option C: Connection pooling (PgBouncer)**: pushes to 20-30K writes/sec as first optimization before structural change.

### Saga: Choreography vs Orchestration
- **Option A: Choreography**: services emit events, no coordinator. Simple start, hard to debug, use for <4 steps.
- **Option B: Orchestration (Temporal)**: durable workflow, queryable state, explicit compensation. Use for >4 steps, complex compensation, audit requirements.

## API Endpoints
| Method | Path | Pattern | Description |
|--------|------|---------|-------------|
| POST | /api/uploads/initiate | Large Objects | Get pre-signed S3 URL for direct upload |
| GET | /api/feed | Read Scaling | Fetch cached feed (L2 cache hit) |
| POST | /api/posts | Async Work | Create post, fan-out async via Kafka |
| POST | /api/payments/{id}/charge | Contention | Charge with Idempotency-Key header |
| POST | /api/orders | Distributed Consistency | Create order via outbox + saga |
| WS | /ws/events | Real-Time | WebSocket with Redis Pub/Sub routing |
| GET | /api/jobs/{id} | Async Work | Poll long-running job status |

## Database Schema
| Table | Column | Type | Notes |
|-------|--------|------|-------|
| idempotency_keys | key | UUID | PK, client-generated |
| idempotency_keys | response | JSON | Stored result for dedup |
| idempotency_keys | created_at | TIMESTAMP | TTL cleanup after 24h |
| outbox_events | id | BIGINT | PK, auto-increment |
| outbox_events | aggregate_id | BIGINT | Domain entity ID |
| outbox_events | event_type | VARCHAR | e.g., "order.created" |
| outbox_events | payload | JSONB | Event data |
| outbox_events | published | BOOLEAN | Default false |
| objects | object_id | UUID | PK, random (avoid S3 hotspotting) |
| objects | user_id | BIGINT | FK to users |
| objects | s3_key | VARCHAR | Path in S3 bucket |
| objects | content_type | VARCHAR | MIME type |
| objects | size_bytes | BIGINT | File size |
| objects | sha256 | CHAR(64) | Content hash for dedup |

## Deep Dive Topics
- Cache stampede prevention: probabilistic early expiration or request coalescing
- WebSocket scaling from 10K to 10M: Redis Pub/Sub at 1M, Kafka partitions at 10M
- Idempotency key implementation: check + execute + store must be one atomic DB transaction
- Outbox pattern internals: Debezium CDC vs polling relay, at-least-once delivery implications
- Consistent hashing virtual nodes: 150-300 vnodes per physical server for proportional load redistribution
- Circuit breaker state machine: CLOSED -> OPEN (threshold) -> HALF-OPEN (probe) -> CLOSED (success)
- Hot shard problem in hash sharding: uniform key distribution does not mean uniform QPS distribution
- CQRS read lag: 50-500ms between write commit and read model update, unacceptable for financial balances

## Follow-Up Variations
- How would you handle a system that needs both strong consistency for payments and eventual consistency for feeds?
- What happens when a Kafka consumer crashes after processing but before committing the offset?
- How do you reshard a 50-billion-row table with zero downtime?
- How would you design a rate limiter that uses contention management patterns?
- What is the anti-pattern that fails staff-level interviews and how do you avoid it?
- How do you prevent double-charging when an HTTP retry hits a payment service?
