# Consistency Models

Source: [Consistency Models (CalibreOS)](https://www.calibreos.com/learn/hld-consistency-models)

## One-Liner
Choose the weakest consistency model that satisfies each data type's product promise, mapping linearizable, causal, read-your-writes, and eventual guarantees to the right database and coordination strategy.

## Functional Requirements
- After a write completes, define what value a subsequent read returns
- Prevent anomalies: stale reads, lost updates, write skew, read inversion
- Allow concurrent writes from multiple replicas without silent data loss
- Support different consistency levels for different data types within the same system
- Provide conflict resolution strategies beyond last-write-wins

## Non-Functional Requirements
- Minimize latency overhead from coordination (quorum, consensus)
- Maintain availability under network partitions
- Scale reads without requiring global ordering for every operation
- Keep convergence time bounded for eventually consistent data
- Support multi-region replication with predictable staleness

## Key Scale Questions
- What staleness window is acceptable per data type? (1ms for inventory vs minutes for like counts)
- How many replicas must acknowledge a write before it is considered committed?
- What is the cost of strong consistency in terms of latency and availability?
- Does the system need to handle concurrent multi-device edits (shopping carts, collaborative docs)?
- Which operations are causally related and must be ordered vs independent and can be reordered?

## Core Components
- **Consensus Module**: Raft/Paxos for linearizable operations (leader election, locking, inventory)
- **Replication Layer**: Multi-region replica sync with configurable quorum (ONE, QUORUM, ALL)
- **Vector Clock / HLC Service**: Tracks causal ordering between related operations
- **CRDT Engine**: Merge-conflict-free data structures for counters, sets, and registers
- **Session Manager**: Ensures read-your-writes and monotonic reads via sticky routing or write-through cache
- **Reconciliation Jobs**: Background repair path for eventual consistency convergence
- **Idempotency Layer**: Prevents duplicate processing during retries (idempotency keys in Redis backed by durable storage)

## Key Design Decisions

### Consistency Model per Data Type
- **Bank balances / inventory / leader election**: Linearizable (strong). Over-selling or split-brain is catastrophic. Use single-node RDBMS, Spanner, or etcd.
- **Like / view / follower counts**: Eventual. Temporary undercount is acceptable, availability is critical. Use Cassandra, DynamoDB, or Redis INCR.
- **User's own posts / comments**: Read-your-writes. User must see their own actions immediately. Use sticky session routing or write-through cache.
- **DM message ordering**: Causal. Replies must appear after the parent message. Use vector clocks or hybrid logical clocks.
- **Distributed shopping cart**: Eventual + CRDT. Concurrent additions on multiple devices must merge, not overwrite. Use OR-Set or add-wins merge.
- **User profile (name, email)**: Eventual with LWW. Conflicts are rare, last-write-wins is acceptable. Use DynamoDB or Cassandra with timestamps.

### CAP vs PACELC
- **CAP**: During a network partition, choose between Consistency (return error) or Availability (return stale data). Partition tolerance is not optional -- partitions happen in every real system.
- **PACELC extends CAP**: Even without a partition, there is a latency-consistency tradeoff. Cassandra with QUORUM reads is slower but more consistent; with ONE reads it is faster but potentially stale.
- CP systems: ZooKeeper, etcd, Spanner. AP systems: Cassandra, DynamoDB, CouchDB.
- Most systems are not purely CP or AP -- they adjust the tradeoff per operation.

### Conflict Resolution Strategy
- **Last-Write-Wins (LWW)**: Simple but silently drops concurrent updates. Acceptable for profile changes, disastrous for shopping carts or financial data.
- **CRDTs**: Merge without conflict by design (associative, commutative, idempotent). G-Counter, PN-Counter, G-Set, OR-Set.
- **Application-level resolution**: Use version vectors, detect conflicts, and resolve based on business logic.

## API Endpoints
| Method | Path | Description |
|--------|------|-------------|
| POST | /api/data/{key} | Write a value (consistency level specified in header) |
| GET | /api/data/{key} | Read a value (consistency level specified in header) |
| POST | /api/cart/{user_id}/items | Add item to distributed shopping cart (CRDT merge) |
| GET | /api/cart/{user_id} | Get cart contents (eventual, may need reconciliation) |
| POST | /api/lock/{resource} | Acquire distributed lock (linearizable, consensus-backed) |

## Database Schema
| Column | Type | Notes |
|--------|------|-------|
| key | STRING | Partition key |
| value | BLOB | Data payload |
| version | BYTES | Vector clock or HLC for causal ordering |
| timestamp | TIMESTAMP | Last-write timestamp for LWW resolution |
| tombstone | BOOLEAN | Soft-delete marker for 2P-Set CRDTs |
| node_id | INT | Replica that authored this version (for G-Counter) |

## Deep Dive Topics
- **Linearizability cost**: Every operation requires multi-node consensus (Raft/Paxos). Adds 1-2 network round trips per read. Use only where the cost of ambiguity exceeds the cost of coordination.
- **Vector clocks**: Track causal dependencies between operations. Each write appends the node ID and sequence number. Detect concurrent writes when vectors are incomparable. Used by Dynamo, Riak.
- **CRDT internals**: G-Counter (per-node increments, merge = max per node), PN-Counter (two G-counters for inc/dec), OR-Set (unique tags per add, add wins over concurrent remove). Used by Redis, Riak, Cassandra counters.
- **Consistency anomalies**: Stale read (read returns old value), lost update (concurrent write overwritten), write skew (two transactions read overlapping data and commit conflicting updates), read inversion (read sees a value that never globally existed). Each model prevents a subset.
- **Reconciliation paths**: Weaker consistency always needs a repair path. Background anti-entropy, read-repair on access, or manual reconciliation for conflicts that cannot be auto-merged.

## Follow-Up Variations
- How would you design consistency for a collaborative document editor (like Google Docs)?
- What happens when a network partition heals and two replicas have conflicting writes to the same bank account?
- How would you implement read-your-writes in a system with 10 read replicas and 1 write leader?
- Can you use eventual consistency for inventory if you over-provision by 5%?
- How do CRDTs handle a remove-then-re-add scenario for a shopping cart item?
- What consistency model does a distributed lock service require, and what happens if the lock holder crashes?
