# Consistency Models — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] What data types does the system handle (financial, counters, user-generated, messages)?
  - [ ] What staleness tolerance does each data type have?
  - [ ] Are there multi-device or multi-region concurrent write scenarios?
  - [ ] What anomalies would cause user harm, financial loss, or security exposure?
- [ ] List functional requirements (3-5 items):
  - [ ] Define read guarantees after a write completes
  - [ ] Prevent anomalies (stale reads, lost updates, write skew, read inversion)
  - [ ] Support concurrent writes from multiple replicas
  - [ ] Provide conflict resolution beyond last-write-wins
  - [ ] Allow different consistency levels per data type
- [ ] List non-functional requirements (latency, availability, scale):
  - [ ] Minimize coordination latency for strong consistency paths
  - [ ] Maintain availability under network partitions
  - [ ] Scale reads without global ordering for every operation
  - [ ] Bound convergence time for eventually consistent data
- [ ] State your scale estimates:
  - [ ] Number of data types and their consistency requirements
  - [ ] Read:write ratio per data type
  - [ ] Cross-region replication topology (how many regions, typical RTT)
  - [ ] Expected conflict rate for concurrent writes

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw a simple box diagram: Client -> LB -> [App Service] -> [Consensus Module + Replication Layer + Session Manager] -> [DB Cluster (multiple replicas)]
- [ ] Identify the main operations and their access patterns:
  - [ ] Write with strong consistency (consensus path, quorum write)
  - [ ] Write with eventual consistency (async replication, fire-and-forget)
  - [ ] Read with strong consistency (leader read or quorum read)
  - [ ] Read with eventual consistency (any replica, may be stale)
  - [ ] Read-your-writes (sticky session or write-through cache)
- [ ] Note the consistency spectrum and where each data type falls:
  - [ ] Eventual -> Monotonic Reads -> Read-Your-Writes -> Causal -> Linearizable
  - [ ] Map each data type to its position on the spectrum
- [ ] Present the diagram and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain the consistency hierarchy (weakest to strongest):
  - [ ] Eventual: converge eventually, no freshness guarantee (like counts, DNS)
  - [ ] Monotonic reads: never see older data after seeing newer (sticky sessions)
  - [ ] Read-your-writes: user sees own changes immediately (posts, comments)
  - [ ] Causal: related operations ordered, concurrent unordered (DMs, threads)
  - [ ] Linearizable: appears as single copy, instant visibility (locks, inventory)
- [ ] Map data types to models with justification:
  - [ ] Bank balance -> Linearizable (double spend is catastrophic)
  - [ ] Like/view count -> Eventual (slight lag acceptable, availability critical)
  - [ ] User's own content -> Read-your-writes (must see own actions)
  - [ ] Messages -> Causal (reply after parent)
  - [ ] Shopping cart -> Eventual + CRDT (merge concurrent additions)
  - [ ] Profile data -> Eventual + LWW (conflicts rare, acceptable)
- [ ] Discuss CAP theorem properly:
  - [ ] P is not optional (partitions happen in every real system)
  - [ ] Real choice: C vs A during a partition
  - [ ] CP: return error rather than stale data (ZooKeeper, etcd, Spanner)
  - [ ] AP: serve possibly stale data (Cassandra, DynamoDB, CouchDB)
  - [ ] PACELC: latency vs consistency tradeoff even without partition
- [ ] Define API endpoints with consistency level:
  - [ ] `POST /api/data/{key}` with `Consistency-Level: QUORUM` header
  - [ ] `GET /api/data/{key}` with `Consistency-Level: ONE` header
  - [ ] `POST /api/cart/{user_id}/items` (CRDT merge)
  - [ ] `POST /api/lock/{resource}` (linearizable, consensus-backed)
- [ ] Sketch the database schema:
  - [ ] Table: key, value, version (vector clock / HLC), timestamp, tombstone, node_id
  - [ ] Explain version vectors for causal tracking
  - [ ] Explain tombstones for soft-delete in CRDTs
- [ ] Walk through the main flow end-to-end:
  - [ ] Strong write: client writes -> consensus (Raft) -> quorum ack -> committed
  - [ ] Eventual write: client writes -> single replica ack -> async replication -> converge
  - [ ] Read-your-writes: client reads -> routed to write replica or write-through cache

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss CRDTs for conflict resolution:
  - [ ] G-Counter: per-node increments, merge = max per node (Cassandra counters)
  - [ ] PN-Counter: two G-counters for increment and decrement
  - [ ] G-Set: grow-only set, merge = union (presence tracking)
  - [ ] OR-Set: add-wins, unique tag per add (shopping carts, Amazon design)
  - [ ] When to mention: shopping carts, collaborative editing, presence, counters
- [ ] Explain vector clocks and causal ordering:
  - [ ] Each write appends (node_id, sequence_number)
  - [ ] Concurrent writes detected when vectors are incomparable
  - [ ] Used by Dynamo, Riak for conflict detection
- [ ] Address consistency anomalies:
  - [ ] Stale read: read returns old value (prevented by linearizable, mitigated by read-your-writes)
  - [ ] Lost update: concurrent write silently dropped (prevented by CRDTs or version checks)
  - [ ] Write skew: two transactions read overlapping data and commit conflicting updates
  - [ ] Read inversion: read sees a value that never globally existed
- [ ] Discuss reconciliation and repair paths:
  - [ ] Background anti-entropy (periodic full sync)
  - [ ] Read-repair on access (fix inconsistencies as reads happen)
  - [ ] Manual reconciliation for unresolvable conflicts
  - [ ] Weaker consistency always needs a repair path
- [ ] Explain linearizability cost:
  - [ ] Multi-node consensus (Raft/Paxos) required for every operation
  - [ ] 1-2 network round trips per read/write
  - [ ] Lower availability under partition (must reject rather than serve stale)
  - [ ] Use only where ambiguity cost exceeds coordination cost

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made and why (per data type, not blanket)
- [ ] Mention what you would improve with more time
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
