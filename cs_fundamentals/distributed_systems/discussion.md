# Distributed Systems

CAP theorem, consistency models, consensus algorithms, replication, sharding, fault tolerance, and eventual consistency for SWE interviews.

## Key Concepts

- **CAP Theorem**: In a distributed system, you can guarantee at most two of three properties: Consistency (every read returns the most recent write), Availability (every request receives a non-error response), and Partition Tolerance (the system continues operating despite network partitions). Since network partitions are inevitable in distributed systems, the real trade-off is between consistency and availability.
- **Consistency Models**: Range from strong consistency (linearizability: reads see the latest write) to weak consistency. Eventual consistency guarantees that, given no new writes, all replicas will converge to the same value eventually. Stronger models like causal consistency ensure operations that are causally related are seen by all nodes in the same order.
- **Consensus (Paxos/Raft)**: Protocols that allow distributed nodes to agree on a value despite failures. Paxos is theoretically foundational but notoriously hard to implement. Raft was designed for understandability, using a leader-based approach with log replication and leader election, and is used in systems like etcd and Consul.
- **Replication Strategies**: Single-leader replication routes all writes through a primary node, which then replicates to followers (provides strong consistency but single point of failure). Multi-leader replication allows writes at any node, using conflict resolution (provides higher availability but weaker consistency). Leaderless (quorum-based) systems like Dynamo allow any node to accept writes and reads.
- **Sharding (Partitioning)**: Distributing data across multiple nodes to scale horizontally. Key-based sharding uses a hash of a key to determine the data's node. Range-based sharding assigns contiguous ranges of keys to nodes. Consistent hashing minimizes data movement when nodes are added or removed.

## Common Questions with Brief Answer Outlines

**Q: Explain the CAP theorem and how it applies to real systems.**
- Consistency means every read returns the most recent write; availability means every request gets a response.
- Partition tolerance is unavoidable in distributed systems (networks can always fail).
- During a partition, you must choose to remain available (returning possibly stale data) or consistent (rejecting requests until the partition resolves).
- CP example: ZooKeeper prioritizes consistency, rejecting requests if a quorum is not available.
- AP example: Cassandra prioritizes availability, serving reads from any reachable replica even if data is stale.

**Q: How does the Raft consensus algorithm work?**
- Nodes are either leaders, followers, or candidates. Only the leader handles client requests.
- The leader sends AppendEntries messages to followers to replicate log entries.
- Followers acknowledge entries; once a majority acknowledges, the entry is committed.
- If followers do not receive heartbeats from the leader, they start an election by becoming candidates and requesting votes.
- The first candidate to receive a majority of votes becomes the new leader.
- Raft guarantees safety: only entries from leaders can be committed, and at most one leader per term.

**Q: What is eventual consistency and what are its challenges?**
- Eventually consistent systems allow replicas to diverge temporarily but guarantee convergence when writes stop.
- Challenges include read-after-write inconsistency (a user may read stale data after writing), read-after-read inconsistency (repeated reads may return different values), and write-write conflicts (concurrent writes to the same key).
- Mitigation strategies include read repair, hinted handoff, anti-entropy (Merkle trees), and vector clocks for conflict detection.
- Dynamo-style systems let clients tune consistency per operation (e.g., quorum reads and writes).

**Q: Compare vertical and horizontal scaling.**
- Vertical scaling adds more resources (CPU, RAM) to a single machine; it has a hard limit and creates a single point of failure.
- Horizontal scaling adds more machines, distributing load across them; it provides virtually unlimited capacity and better fault tolerance.
- Horizontal scaling requires handling data distribution (sharding), consistency, and failover, which adds complexity.
- Stateless services scale horizontally easily; stateful systems require careful data partitioning and replication.
- Most large-scale systems use a combination: vertical scaling for individual nodes and horizontal scaling across clusters.

**Q: How does consistent hashing work in distributed systems?**
- Both nodes and keys are mapped onto a ring (hash space, typically 0 to 2^32 - 1) using a hash function.
- Each key is assigned to the first node encountered clockwise on the ring.
- When a node is added or removed, only keys in its immediate range need to be remapped (minimizing data movement).
- Virtual nodes (replicas on the ring) ensure more uniform data distribution across nodes of varying capacity.
- Used in systems like DynamoDB, Cassandra, and Memcached for distributed caching.

**Q: What are vector clocks and how do they detect causality?**
- A vector clock is a data structure used to track causal relationships between events in a distributed system. Each node maintains a vector of logical timestamps, one entry per node.
- When a node performs an event, it increments its own entry in the vector. When sending a message, it includes its current vector clock. The receiving node updates its vector by taking the element-wise maximum and incrementing its own entry.
- Comparing vector clocks: event A happened-before event B if every entry in A's vector is <= B's vector and at least one is strictly less. If neither vector dominates the other, the events are concurrent (no causal relationship).
- Vector clocks are used for conflict detection in eventually consistent systems (e.g., DynamoDB, Riak) and for debugging distributed systems by reconstructing the order of events.

**Q: How are distributed transactions handled across multiple services?**
- Two-Phase Commit (2PC): a coordinator asks all participants to vote on whether they can commit (prepare phase); if all vote yes, the coordinator tells them to commit (commit phase). If any participant votes no or times out, all are told to abort. 2PC provides strong consistency but is a blocking protocol (participants hold locks while waiting for the coordinator) and is not fault-tolerant if the coordinator crashes.
- Saga pattern: a sequence of local transactions, each with a compensating action. If one step fails, previously completed steps are undone by running their compensating transactions in reverse order. Sagas do not hold locks and work well across different services and databases, but provide only eventual consistency and require careful design of compensating actions.
- Eventual consistency alternatives: choreography-based sagas (services emit events, no central coordinator) vs orchestration-based sagas (a central coordinator directs each step). Orchestration is easier to reason about for complex flows; choreography reduces coupling.

**Q: What is the Byzantine Generals Problem?**
- The Byzantine Generals Problem addresses how distributed nodes can reach consensus when some nodes may behave arbitrarily (including maliciously), not just by crashing. It is the hardest class of failure in distributed systems.
- The classic formulation: several generals must agree on a common plan (attack or retreat) using messengers, but some generals may be traitors sending conflicting messages.
- Byzantine failures include sending incorrect data, sending different data to different nodes, or colluding with other faulty nodes to disrupt consensus.
- The problem can be solved if fewer than one-third of nodes are Byzantine (f < n/3), using algorithms like PBFT (Practical Byzantine Fault Tolerance).
- Relevant in practice for blockchain networks, multi-party computation, and any system where nodes may be controlled by different adversarial entities.

## Quick Reference Table

| Strategy | Consistency | Availability | Complexity | Example Systems |
|---|---|---|---|---|
| Single-leader replication | Strong (sequential reads from leader) | Leader is a bottleneck; failover needed | Medium | PostgreSQL streaming replication, MySQL |
| Multi-leader replication | Eventual (conflict resolution needed) | High (writes at any node) | High (conflict detection) | Cassandra, CouchDB |
| Leaderless / Quorum | Tunable (W + R > N for strong) | High (any node serves) | Medium | DynamoDB, Riak |
| Raft consensus | Strong (linearizable) | Requires majority quorum | Medium | etcd, Consul, CockroachDB |
| Gossip protocol | Eventual | High | Low | Cassandra membership |
