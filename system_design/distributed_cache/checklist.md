# Design a Distributed Cache — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] What is the total cache size (GB/TB)? How many cache nodes do we expect to run?
  - [ ] What eviction policy is preferred: LRU, LFU, FIFO, or configurable per use case?
  - [ ] What are the consistency requirements: strict consistency, eventual consistency, or read-after-write?
  - [ ] Do we need TTL (time-to-live) support for cache entries?
- [ ] List functional requirements (3-5 items):
  - [ ] Support GET and PUT operations on key-value pairs
  - [ ] Distribute data across multiple nodes
  - [ ] Support configurable eviction policies when cache is full
  - [ ] Support TTL expiration for individual keys
  - [ ] Handle node additions and removals with minimal data reshuffling
- [ ] List non-functional requirements (latency, availability, scale):
  - [ ] Ultra-low latency: reads and writes in <1ms
  - [ ] High availability: tolerate node failures without data loss
  - [ ] Scalability: horizontal scaling to hundreds of nodes
  - [ ] Consistency: configurable (strong or eventual depending on use case)
  - [ ] Memory efficiency: minimize overhead per cached item
- [ ] State your scale estimates (users, requests, storage):
  - [ ] ~100 cache nodes, ~1TB total cache memory
  - [ ] ~1M reads/sec, ~100K writes/sec at peak
  - [ ] ~100M keys in the cache
  - [ ] Average value size: ~1KB

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw a simple box diagram: Client -> [Cache Client Library] -> [Cache Nodes] -> [Gossip Protocol / Config Service]
- [ ] Identify the main operations and their access patterns:
  - [ ] `GET(key)` — read from cache (extremely high QPS)
  - [ ] `PUT(key, value, ttl)` — write to cache (moderate QPS)
  - [ ] `DELETE(key)` — invalidate a cache entry (low QPS)
  - [ ] Node join/leave — rehash and redistribute data (infrequent)
- [ ] Note the read:write ratio and where caching helps:
  - [ ] Read:Write ratio ~10:1 (typical caching workload)
  - [ ] The cache itself IS the caching layer — focus on hit ratio optimization
  - [ ] Local L1 cache on client side can reduce network calls further
- [ ] Present the diagram and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain consistent hashing and justify your choice:
  - [ ] Consistent hashing: maps keys to nodes using a hash ring
  - [ ] Virtual nodes: each physical node has multiple virtual nodes on the ring for balanced distribution
  - [ ] On node removal: only keys from that node are remapped (minimal disruption)
  - [ ] Alternative: Rendezvous hashing (highest random weight), simpler and better balance
  - [ ] State your choice and trade-offs
- [ ] Define API with method, path, request/response:
  - [ ] `GET /cache/{key}` -> value or 404
  - [ ] `PUT /cache/{key}` with body `{value, ttl}` -> 200 OK
  - [ ] `DELETE /cache/{key}` -> 200 OK
  - [ ] Internal: node discovery and membership protocol
- [ ] Sketch the data model:
  - [ ] In-memory hash table per node: `{key -> (value, ttl, version, last_accessed)}`
  - [ ] Hash ring metadata: `{virtual_node_id -> physical_node_address}`
  - [ ] Replication metadata: `{key -> [primary_node, replica_nodes]}`
- [ ] Discuss replication strategy:
  - [ ] Replication factor N (e.g., N=3): each key is stored on N nodes
  - [ ] Write: write to primary, then replicate to replicas (synchronous or asynchronous)
  - [ ] Read: read from primary or nearest replica
  - [ ] Trade-off: synchronous replication = strong consistency but higher latency; async = eventual consistency but faster
- [ ] Walk through write policy choices:
  - [ ] Write-through: write to cache and DB simultaneously
  - [ ] Write-back (write-behind): write to cache, async write to DB
  - [ ] Write-around: write to DB, invalidate or update cache
  - [ ] State your choice and trade-off

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss eviction strategy in detail:
  - [ ] LRU (Least Recently Used): simple, good for general workloads, O(1) with doubly-linked list + hashmap
  - [ ] LFU (Least Frequently Used): better for hot keys, O(1) with counter per entry
  - [ ] Approximate LRU (like Redis): sampled random keys, evict least recently accessed
  - [ ] Explain implementation: each node maintains its own local eviction policy
- [ ] Explain scaling/partitioning approach:
  - [ ] Add node: place virtual nodes on ring, only affected keys migrate
  - [ ] Remove node: virtual nodes removed, affected keys redistributed
  - [ ] Rebalancing: background migration process, serve reads from old + new node during transition
- [ ] Address node failure handling:
  - [ ] Failure detection: gossip protocol or heartbeat (SWIM-style)
  - [ ] On primary failure: promote a replica to primary
  - [ ] On replica failure: create new replica from surviving copies
  - [ ] Hinted handoff: temporarily buffer writes for a down node, replay when it recovers
- [ ] Handle cache warming and cold start:
  - [ ] On new node: gradually take traffic, replicate hot keys from existing nodes
  - [ ] On cluster restart: pre-load critical data from backing store
  - [ ] On failover: replicas serve reads immediately, no warming needed
- [ ] Discuss monitoring and observability:
  - [ ] Cache hit/miss ratio per node and globally
  - [ ] Memory usage per node, eviction rate
  - [ ] Latency (p50, p95, p99) for GET and PUT
  - [ ] Replication lag between primary and replicas
  - [ ] Node health and membership changes

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made and why
- [ ] Mention what you would improve with more time
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
