# Design a Distributed Cache

## One-Liner
In-memory data store distributed across multiple nodes for sub-millisecond data access with high availability.

## Functional Requirements
- Get and set key-value pairs with TTL support
- Automatic data partitioning across nodes
- Handle node failures without data loss (replication)
- Cache eviction when memory is full
- Support cache invalidation and updates

## Non-Functional Requirements
- Sub-millisecond read latency
- Millions of operations per second
- Horizontal scalability (add/remove nodes dynamically)
- High availability (survive node failures)

## Key Scale Questions
- Terabytes of cached data across hundreds of nodes
- Millions of ops/sec (90% reads)
- Hot keys: 1% of keys get 80% of traffic
- Replication factor: 3 (for durability)
- Node memory: 64-256GB per node

## Core Components
- **Client Library**: consistent hashing, request routing, failure handling
- **Cache Nodes**: in-memory key-value store (Redis or Memcached instances)
- **Cluster Manager**: membership management, rebalancing, failure detection
- **Replication Manager**: sync/async replication between nodes
- **Eviction Engine**: LRU/LFU policy enforcement per node
- **Monitoring**: hit rate, latency, memory usage, eviction rate metrics

## Key Design Decisions

### Data Partitioning
- **Option A: Consistent hashing with virtual nodes**: Balanced distribution, minimal data movement on node changes, industry standard
- **Option B: Hash-based modulo**: Simple, but N/3 data movement when adding/removing nodes
- **Option C: Range-based partitioning**: Good for range queries, risk of hot spots with sequential keys

### Replication Strategy
- **Option A: Synchronous replication**: Strong consistency, higher write latency (wait for all replicas)
- **Option B: Asynchronous replication**: Low write latency, risk of data loss on primary failure
- **Option C: Quorum-based (R + W > N)**: Tunable consistency, balanced approach

### Cache Invalidation
- **Option A: TTL-based**: Simple, eventual consistency, stale data within TTL window
- **Option B: Write-through**: Update cache on every DB write. Always fresh, slower writes
- **Option C: Write-around**: Write to DB only, invalidate cache. Avoids cache pollution, read misses after write
- **Option D: Write-back**: Write to cache first, async flush to DB. Fastest writes, risk of data loss

## API Endpoints
| Method | Path | Description |
|--------|------|-------------|
| GET | /api/cache/{key} | Get value by key |
| PUT | /api/cache/{key} | Set value with optional TTL |
| DELETE | /api/cache/{key} | Invalidate a key |

## Database Schema
N/A (in-memory key-value store)

| Data Field | Description |
|------------|-------------|
| key | String, up to 250 bytes |
| value | Binary blob, up to 1MB |
| ttl | Optional expiration in seconds |
| version | Optional, for optimistic concurrency |

## Deep Dive Topics
- Consistent hashing ring: virtual nodes to handle uneven node capacities
- LRU vs LFU eviction: LRU is simple, LFU better for stable hot keys; W-TinyLFU as hybrid
- Gossip protocol for cluster membership: failure detection, anti-entropy, converging view
- Hot key problem: detection (monitoring), mitigation (local caching, key splitting)

## Follow-Up Variations
- How would you handle cache stampede (thundering herd) when a hot key expires?
- How do you handle cache warming when adding new nodes?
- What about multi-datacenter cache replication?
- How would you implement a cache with strong consistency guarantees?
