# Idempotency Patterns — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] What operations need idempotency? (payments, bookings, message processing, API calls)
  - [ ] What is the failure model? (network drops, server crashes, GC pauses, duplicate messages)
  - [ ] Are we protecting HTTP APIs, message consumers, or distributed transactions?
  - [ ] What is the scale of retries? (QPS, retry rate, concurrent request probability)
- [ ] List functional requirements (3-5 items):
  - [ ] Prevent duplicate side effects on retry (no double charges, no double bookings)
  - [ ] Support idempotency keys on POST endpoints
  - [ ] Handle concurrent requests with the same key (race conditions)
  - [ ] Support distributed transaction compensation across services
  - [ ] Provide exactly-once processing on top of at-least-once delivery
- [ ] List non-functional requirements (latency, correctness, scale):
  - [ ] Idempotency key lookup under 5ms
  - [ ] TTL of 24 hours (aligned with retry window)
  - [ ] Correctness over performance on critical paths
  - [ ] Tolerance for network partitions, GC pauses, server crashes
- [ ] State your scale estimates:
  - [ ] At 1M requests/day, 0.1% failure = 1,000 retries daily
  - [ ] PSP latency 200-500ms (long window for network drops)
  - [ ] Kafka consumers deduplicating millions of messages/day

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw a simple box diagram: Client -> LB -> [API Server] -> [Idempotency Store (Redis/SQL)] -> [Downstream Service (PSP, DB)]
- [ ] Identify the main operations and their access patterns:
  - [ ] `POST /api/charges` with `Idempotency-Key` header — create charge (must be idempotent)
  - [ ] `GET /api/charges/{id}` — read charge status (naturally idempotent)
  - [ ] Kafka consumer processing — read message, dedupe by event ID, write to DB
  - [ ] Distributed lock acquire -> write -> release (needs fencing tokens)
- [ ] Note the retry pattern and where idempotency is enforced:
  - [ ] Client generates UUID v4 before first attempt, reuses on all retries
  - [ ] Server atomically reserves key (SETNX or INSERT ON CONFLICT) with state=PENDING
  - [ ] If key exists and state=DONE: return cached response
  - [ ] If key exists and state=PENDING: return 409 Conflict (another worker processing)
  - [ ] Execute operation, then atomically update to state=DONE
- [ ] Present the diagram and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain idempotency key storage choice and justify:
  - [ ] Redis SETNX: fast (~1ms), built-in TTL, but split state risk
  - [ ] SQL UNIQUE constraint: slower (~5ms) but same ACID transaction as business write
  - [ ] Dual (Redis + SQL): best of both, more operational complexity
  - [ ] For payments: always prefer SQL for correctness
- [ ] Define the state machine for idempotency keys:
  - [ ] PENDING: key reserved, operation in progress
  - [ ] DONE: operation completed, response cached
  - [ ] Background job: reconcile stale PENDING keys older than execution timeout
- [ ] Sketch the database schema:
  - [ ] Table `idempotency_keys`: `scoped_key` (PK: `{tenant_id}:{idem_key}`), `request_hash` (SHA-256), `state` (PENDING/DONE), `response_body` (JSONB), `response_status` (INT), `created_at`, `expires_at`
  - [ ] Index on `(state, created_at) WHERE state = 'PENDING'` for cleanup job
- [ ] Discuss race condition handling:
  - [ ] TOCTOU race: two workers read "key not found" before either writes
  - [ ] Fix: SETNX (atomic set-if-not-exists) or SQL INSERT ON CONFLICT DO NOTHING
  - [ ] Second worker gets 409 Conflict while first worker executes
- [ ] Walk through the main flow end-to-end:
  - [ ] Client sends POST with Idempotency-Key header
  - [ ] Server SETNX with state=PENDING; if exists, return cached response or 409
  - [ ] Server executes operation (calls PSP, writes DB), forwards idempotency key downstream
  - [ ] Server updates key to state=DONE with full response
  - [ ] Client retry with same key gets cached response — no re-execution

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss exactly-once semantics:
  - [ ] Exactly-once delivery is provably impossible (Two Generals' Problem / FLP impossibility)
  - [ ] "Effectively-once" = at-least-once delivery + idempotent consumer
  - [ ] The consumer is responsible for idempotency, not the broker
- [ ] Explain Kafka EOS scope and limitations:
  - [ ] Kafka EOS applies only within Kafka-to-Kafka pipelines (producer -> broker -> consumer writing to another topic)
  - [ ] External side effects (Postgres, HTTP calls) are NOT covered by Kafka EOS
  - [ ] Producer idempotence: PID + sequence number deduplication at broker
  - [ ] Transactional producers: consume-transform-produce cycle is atomic
  - [ ] `isolation.level: read_committed` to avoid reading aborted transactions
- [ ] Address fencing tokens for distributed locks:
  - [ ] Problem: GC pause > lock TTL causes two processes to believe they hold the lock
  - [ ] Solution: monotonically increasing token; storage rejects writes with lower tokens
  - [ ] Mechanisms: ZooKeeper zxid, Redis Lua compare-and-write, etcd revision
  - [ ] Redlock without fencing is insufficient — always pair locks with fencing tokens
- [ ] Discuss saga pattern for distributed transactions:
  - [ ] 2PC: atomic but slow (100-300ms), holds locks across participants, blocks during partitions
  - [ ] Saga: sequence of local transactions with compensating actions on failure
  - [ ] Compensation is NOT rollback — it is a forward-moving correction (new business operation)
  - [ ] Compensations must be idempotent (safe to retry if they fail)
  - [ ] Choreography vs Orchestration tradeoffs (simplicity vs debuggability)
  - [ ] Temporal: event-sourced workflow execution, replays history on crash, guarantees compensation completion
- [ ] Handle the 5-step algorithm for any endpoint:
  - [ ] Step 1: Require client-generated idempotency key (UUID v4 in header)
  - [ ] Step 2: Scope key per tenant (`{tenant_id}:{idem_key}`)
  - [ ] Step 3: Atomic reserve before execution (PENDING state via SETNX or INSERT ON CONFLICT)
  - [ ] Step 4: Execute and atomically update to DONE
  - [ ] Step 5: Set TTL aligned with retry window (24h default)

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made and why (SQL vs Redis, choreography vs orchestration)
- [ ] Mention what you would improve with more time
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
