# Design a Key-Value Store

## One-Liner
Distributed, durable key-value database optimized for high write throughput and horizontal scalability (like Dynamo/Cassandra).

## Functional Requirements
- CRUD operations on key-value pairs
- Configurable consistency level per operation
- Automatic data partitioning and rebalancing
- Replication for fault tolerance
- Support range queries on keys (optional)

## Non-Functional Requirements
- High write throughput (millions of writes/sec)
- Low read latency (<10ms p99)
- Horizontal scalability to petabyte-scale data
- Durability (no data loss on node failure)

## Key Scale Questions
- Petabyte-scale data across thousands of nodes
- Read:write ratio of roughly 1:1
- Key size: average 100 bytes, value size: average 1KB-10MB
- Replication factor: 3
- Consistency: eventual by default, strong on demand

## Core Components
- **Client Library**: request routing, retry logic, consistency level configuration
- **Partitioning Layer**: hash-based key partitioning across nodes
- **Storage Engine**: MemTable (in-memory) + SSTable (on-disk) with WAL
- **Compaction Manager**: background SSTable compaction (size-tiered or leveled)
- **Replication Manager**: synchronous/asynchronous replication to replica nodes
- **Membership/Gossip**: node discovery, failure detection, cluster state propagation
- **Hinted Handoff**: temporary storage for writes to unavailable replicas

## Key Design Decisions

### Storage Engine
- **Option A: LSM tree (MemTable + SSTable)**: Write-optimized, sequential writes only, reads may check multiple SSTables (mitigated by Bloom filters). Used by Cassandra, RocksDB, LevelDB
- **Option B: B-tree**: Read-optimized, random writes on update, good for read-heavy workloads. Used by MySQL, PostgreSQL
- **Option C: Fractal tree**: Hybrid, amortized writes, complex implementation

### Compaction Strategy
- **Option A: Size-tiered compaction**: Groups SSTables of similar size, good for write-heavy, more temporary disk space usage
- **Option B: Leveled compaction**: SSTables organized in levels, each level 10x larger, more predictable read performance, more write amplification
- **Option C: Date-tiered compaction**: Groups by timestamp, ideal for time-series data with TTL

### Replication Model
- **Option A: Leader-based (single leader)**: Strong consistency, leader is bottleneck
- **Option B: Leaderless (Dynamo-style)**: No single bottleneck, any node can coordinate writes, eventual consistency
- **Option C: Multi-leader**: Multiple acceptors for writes, conflict resolution needed (vector clocks, CRDTs)

## API Endpoints
| Method | Path | Description |
|--------|------|-------------|
| GET | /api/kv/{key} | Get value by key |
| PUT | /api/kv/{key} | Create/update key-value pair |
| DELETE | /api/kv/{key} | Delete a key |
| SCAN | /api/kv?start={key}&limit=N | Range scan from start key |

## Database Schema
| Component | Description |
|-----------|-------------|
| Key | Binary string, primary identifier |
| Value | Binary blob |
| Version/Vector Clock | For conflict detection and resolution |
| Timestamp | Last write timestamp |
| Tombstone | Deletion marker (not immediately removed) |

## Deep Dive Topics
- LSM tree write path: WAL -> MemTable -> flush to SSTable -> compaction
- Bloom filters: probabilistic data structure to avoid unnecessary SSTable reads
- Hinted handoff: when a replica is down, coordinator stores write hints and replays when replica recovers
- Anti-entropy repair: Merkle tree-based comparison between replicas to detect inconsistencies

## Follow-Up Variations
- How would you support transactions across multiple keys?
- What happens during a network partition (split brain)?
- How would you implement strong consistency as an option (quorum reads/writes)?
- How do you handle schema evolution and secondary indexes?
