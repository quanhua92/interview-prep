# 10 Architectural Patterns -- Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Identify which of the 10 patterns the problem requires:
  - [ ] Read Scaling: read QPS exceeds single DB capacity (~5-10K/sec)
  - [ ] Write Scaling: write QPS exceeds single primary (~2-5K/sec)
  - [ ] Real-Time Delivery: clients need sub-second push updates
  - [ ] Async Work Offloading: operations take >500ms or need retry
  - [ ] Contention Management: multiple writers race for shared resource
  - [ ] Large Object Storage: binary blobs too large for DB rows
  - [ ] Distributed Consistency: business transaction crosses service boundaries
  - [ ] Service Communication: choosing sync vs async protocol
  - [ ] Data Partitioning: dataset exceeds one node's capacity
  - [ ] Fault Isolation: downstream failure must not cascade
- [ ] Name the pattern explicitly to the interviewer: "The core challenge here is a [pattern name] problem"
- [ ] List the forcing functions (derive the numbers):
  - [ ] Calculate read QPS from DAU x reads/session x sessions/day / 86400
  - [ ] Calculate write QPS similarly
  - [ ] Check if any operation exceeds 500ms
  - [ ] Check if any business operation spans multiple services
  - [ ] Check if dataset exceeds single-node storage

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw the read path (if Read Scaling applies):
  - [ ] Client -> L1 (in-process) -> L2 (Redis) -> L3 (CDN if public) -> L4 (read replicas) -> Primary DB
- [ ] Draw the write path (if Write Scaling applies):
  - [ ] Client -> API -> Write Store (PostgreSQL) -> Kafka event -> Read Store (Elasticsearch/Redis)
- [ ] Draw the real-time path (if Real-Time Delivery applies):
  - [ ] Client <-> WebSocket Gateway -> Redis Pub/Sub -> Backend Service
- [ ] Draw the async path (if Async Work applies):
  - [ ] Client -> API (return 202) -> Kafka -> Worker -> DLQ on failure
- [ ] Present the diagram and get alignment before going deeper

## Phase 3: Core Component Design (5-8 min)
- [ ] For Read Scaling, justify cache strategy choice:
  - [ ] Cache-aside (default, lazy load)
  - [ ] Write-through (strong consistency needed)
  - [ ] Write-behind (extreme write-heavy, non-critical data)
  - [ ] Explain invalidation: TTL + event-driven (DEL on Kafka event)
  - [ ] Address cold start / cache stampede prevention
- [ ] For Write Scaling, justify approach:
  - [ ] Connection pooling first (PgBouncer to 20-30K writes/sec)
  - [ ] CQRS + Kafka next (10K-100K writes/sec, two schemas)
  - [ ] Horizontal sharding last resort (resharding cost, cross-shard queries)
- [ ] For Contention Management, justify strategy:
  - [ ] SELECT FOR UPDATE (low concurrency, high value: payments, seats)
  - [ ] Optimistic concurrency (moderate contention: profile updates, cart)
  - [ ] Queue-based serialization (unlimited concurrency: Kafka partition per entity)
  - [ ] Always add idempotency keys for retry-able mutations
- [ ] For Distributed Consistency, justify approach:
  - [ ] Outbox pattern (default for "write + publish event")
  - [ ] Saga choreography (<4 steps, simple compensation)
  - [ ] Saga orchestration via Temporal (>4 steps, complex, audit trail)
  - [ ] Never use 2PC across service boundaries
- [ ] Sketch key API endpoints with method, path, request/response
- [ ] Sketch the database schema for critical tables (idempotency_keys, outbox_events, objects)

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss cache invalidation failure modes:
  - [ ] TTL too long -> stale reads -> event-driven invalidation
  - [ ] Cache stampede on cold start -> probabilistic early expiration
  - [ ] Inconsistent invalidation across regions -> Kafka event to all regions
- [ ] Explain WebSocket scaling across servers:
  - [ ] At 10K users: single server
  - [ ] At 1M users: 100 WS servers + Redis Pub/Sub routing
  - [ ] At 10M users: Kafka partitions replace Redis Pub/Sub
- [ ] Explain resharding and consistent hashing:
  - [ ] Hash % N moves 50% of keys on +1 node
  - [ ] Consistent hashing with vnodes moves only ~1/N keys
  - [ ] Virtual nodes (150-300 per server) for uniform redistribution
- [ ] Address the hot shard problem:
  - [ ] Hash sharding distributes keys uniformly but not QPS
  - [ ] Celebrity users on one shard create disproportionate traffic
  - [ ] Mitigate with caching or different fan-out strategy for hot entities
- [ ] Explain fault isolation patterns:
  - [ ] Circuit breaker: CLOSED -> OPEN (50% failures) -> HALF-OPEN (probe) -> CLOSED
  - [ ] Bulkhead: separate thread pools per downstream dependency
  - [ ] Retry + exponential backoff + jitter (AWS SDK full jitter: random(0, base_delay))
  - [ ] Deadline propagation via gRPC context
- [ ] Discuss the anti-pattern: proposing a pattern without deriving its forcing function
  - [ ] "I'd add Redis" = 6/10
  - [ ] "At 139K reads/sec derived from 200M DAU x 20 reads x 3 sessions / 86400, single PostgreSQL at 5K reads/sec is the bottleneck, forcing a distributed cache tier" = 9/10

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences, naming each pattern used
- [ ] State the trade-offs you made (e.g., eventual consistency vs strong, sharding cost vs single-node ceiling)
- [ ] Mention what you would improve with more time
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
