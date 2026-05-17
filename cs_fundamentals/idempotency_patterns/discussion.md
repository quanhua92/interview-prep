# Idempotency Patterns: Safe Retries, Exactly-Once Semantics, and Fencing Tokens

Source: [Idempotency Patterns (CalibreOS)](https://www.calibreos.com/learn/hld-idempotency-patterns)

## One-Liner
Ensure that retrying an operation produces the same result as executing it once, using idempotency keys, fencing tokens, saga compensation, and exactly-once processing patterns.

## Functional Requirements
- Prevent duplicate side effects when clients retry failed requests (double charges, double bookings)
- Support idempotent POST endpoints via client-generated idempotency keys
- Handle concurrent requests with the same key (race conditions)
- Provide exactly-once processing semantics on top of at-least-once delivery
- Support distributed transaction compensation across multiple services (saga pattern)

## Non-Functional Requirements
- Idempotency key lookup under 5ms (Redis SETNX or SQL UNIQUE constraint)
- TTL of 24 hours for idempotency records (aligned with retry window)
- Tolerance for network partitions, GC pauses, and server crashes mid-execution
- Correctness over performance on critical paths (payments): prefer SQL over Redis for idempotency state

## Key Scale Questions
- At 1M requests/day, 0.1% failure rate = 1,000 retries daily that must not produce duplicates
- Payment PSP latency: 200-500ms per charge (long window for network drops)
- Kafka consumers processing millions of messages/day must deduplicate by event ID
- Saga workflows spanning 3-5 services with compensation latency 100-300ms per step

## Core Components
- **Idempotency Key Store**: Redis (SETNX with TTL) or SQL (UNIQUE constraint + INSERT ON CONFLICT) for storing key -> {state, response} mappings
- **Request Hash Validator**: SHA-256 hash of request body stored alongside key to detect key reuse with different payloads
- **PENDING/DONE State Machine**: Atomic reserve (PENDING) before execution, update to DONE after; background job reconciles stale PENDING keys
- **Distributed Lock + Fencing Token**: Monotonically increasing integer token issued by lock server; storage system rejects writes with lower tokens
- **Saga Orchestrator**: Temporal or custom orchestrator driving multi-step distributed transactions with compensating actions

## Key Design Decisions

### Idempotency Key Storage
- **Option A: Redis SETNX**: Fast (~1ms), TTL built-in, but splits state across two stores (Redis + DB). Risk: crash after Redis write but before DB write leaves inconsistent state
- **Option B: SQL UNIQUE constraint**: Slower (~5ms) but idempotency record and business write in same ACID transaction. Correct by default
- **Option C: Dual (Redis for speed + SQL for durability)**: Best of both, more operational complexity. Stripe uses this pattern

### Exactly-Once Processing
- **Option A: At-most-once + idempotent retries**: Do not retry failed requests, but design each request to be idempotent so a retry is safe if it occurs
- **Option B: At-least-once + idempotent consumer (dominant pattern)**: Retry aggressively; consumer deduplicates based on message ID. This is what Kafka, SQS, and virtually every production queue uses

### Saga Implementation
- **Option A: Choreography**: Each service subscribes to events and knows its role. Simple, no single point of failure. Hard to debug at 6+ steps
- **Option B: Orchestration (Temporal/Step Functions)**: Central orchestrator drives each step, handles failures, invokes compensations. Easier to debug, adds a coordination service dependency

## API Endpoints
| Method | Path | Description |
|--------|------|-------------|
| POST | /api/charges | Create a charge (requires `Idempotency-Key` header) |
| GET | /api/charges/{id} | Get charge status |
| POST | /api/bookings | Create a booking saga (requires `Idempotency-Key` header) |

## Database Schema
| Column | Type | Notes |
|--------|------|-------|
| scoped_key | TEXT | PK, `{tenant_id}:{idem_key}` |
| request_hash | TEXT | SHA-256 of request body |
| state | TEXT | `PENDING` or `DONE` |
| response_body | JSONB | Stored only when DONE |
| response_status | INT | HTTP status code |
| created_at | TIMESTAMPTZ | Creation time |
| expires_at | TIMESTAMPTZ | `created_at + 24h` |

## Deep Dive Topics
- **The race condition**: Two concurrent requests with the same key. Fix: SETNX (only one worker gets True) or SQL UNIQUE constraint (loser gets 0 rows inserted). Return 409 Conflict while state=PENDING
- **Fencing tokens**: Distributed lock expiry during GC pause causes two processes to believe they hold the lock. Fix: monotonically increasing token; storage rejects writes with older tokens. Mechanisms: ZooKeeper zxid, Redis Lua compare-and-write, etcd revision
- **Kafka EOS boundary**: Exactly-once applies only within Kafka-to-Kafka pipelines. External side effects (Postgres writes, HTTP calls) require separate idempotency at the consumer level
- **Temporal workflow determinism**: Workflow functions must be deterministic (no random, no `datetime.now()`, no direct API calls). All I/O wrapped in Activity functions whose results are recorded in the event log

## Follow-Up Variations
- How would you handle idempotency when the PSP itself retries a webhook callback?
- What happens if two different users generate the same UUID as an idempotency key?
- How would you design idempotency for a batch processing system (1000 records per batch)?
- How do you reconcile PENDING idempotency keys after a server crash mid-execution?
