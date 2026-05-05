# Design a Key-Value Store — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] What is the value size range? Are values small (<1KB, like session data) or large (>1MB, like files)?
  - [ ] What is the expected read:write ratio? Is this read-heavy, write-heavy, or balanced?
  - [ ] What consistency model do we need: strong consistency (linearizable) or eventual consistency?
  - [ ] What are the durability requirements? Can we tolerate some data loss on failure (e.g., last few seconds)?
- [ ] List functional requirements (3-5 items):
  - [ ] PUT(key, value) — store a key-value pair
  - [ ] GET(key) — retrieve a value by key
  - [ ] DELETE(key) — remove a key-value pair
  - [ ] Support large value sizes efficiently
  - [ ] Support range queries (optional: scan keys in a range)
- [ ] List non-functional requirements (latency, availability, scale):
  - [ ] Low latency: reads in <10ms, writes in <50ms
  - [ ] High availability: 99.99% uptime, tolerate node failures
  - [ ] Scalability: scale to petabytes of data across hundreds of nodes
  - [ ] Durability: data survives node failures and process crashes (write-ahead log)
  - [ ] Consistency: tunable (strong for some use cases, eventual for others)
- [ ] State your scale estimates (users, requests, storage):
  - [ ] ~10B keys, ~10TB total data
  - [ ] ~1M reads/sec, ~500K writes/sec
  - [ ] Key size: ~100 bytes average
  - [ ] Value size: ~1KB average (but up to 10MB)
  - [ ] ~100 nodes in the cluster

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw a simple box diagram: Client -> [Coordinator Node] -> [Storage Nodes] -> [SSTables + WAL]
- [ ] Identify the main operations and their access patterns:
  - [ ] `PUT(key, value)` — write a key-value pair (high QPS)
  - [ ] `GET(key)` — read a value by key (high QPS)
  - [ ] `DELETE(key)` — delete a key (low QPS)
  - [ ] `SCAN(start_key, end_key)` — range scan (moderate QPS)
  - [ ] Background: compaction, rebalancing, anti-entropy repair
- [ ] Note the read:write ratio and where caching helps:
  - [ ] Read:Write ratio ~2:1 (balanced with slight read skew)
  - [ ] Block cache: cache frequently accessed SSTable blocks in memory
  - [ ] Bloom filter: avoid disk reads for non-existent keys
- [ ] Present the diagram and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain LSM tree write path and justify:
  - [ ] Write goes to in-memory MemTable (sorted, e.g., skip list or red-black tree)
  - [ ] Simultaneously appended to Write-Ahead Log (WAL) for durability
  - [ ] When MemTable is full, flush to disk as an immutable SSTable (Sorted String Table)
  - [ ] SSTables are sorted by key and stored in levels (Level 0, 1, 2, ...)
  - [ ] Advantage: writes are always fast (append-only), no in-place updates
- [ ] Define API endpoints with method, path, request/response:
  - [ ] `PUT /v1/keys/{key}` with body `{"value": "..."}` -> `201 Created`
  - [ ] `GET /v1/keys/{key}` -> `{"key": "...", "value": "..."}` or `404 Not Found`
  - [ ] `DELETE /v1/keys/{key}` -> `204 No Content`
  - [ ] `POST /v1/keys/scan` with body `{"start": "...", "end": "...", "limit": 100}` -> `[key-value pairs]`
- [ ] Sketch the data model:
  - [ ] Key: variable-length byte string
  - [ ] Value: variable-length byte string (up to 10MB)
  - [ ] Internal key format: `{user_key, sequence_number, tombstone_flag}` for MVCC
  - [ ] SSTable file: sequence of `{key, value}` sorted by user_key + sequence_number, with index block
- [ ] Discuss compaction strategy:
  - [ ] Size-tiered compaction: merge SSTables of similar size (good for write-heavy workloads)
  - [ ] Leveled compaction: merge into fixed-size levels (good for read-heavy, limits read amplification)
  - [ ] FIFO compaction: drop oldest data with TTL (good for time-series / cache use cases)
  - [ ] State your choice and trade-off
- [ ] Walk through Bloom filter optimization:
  - [ ] Bloom filter per SSTable: probabilistic data structure to test if a key MIGHT exist
  - [ ] Avoids disk I/O for keys that do not exist in the SSTable
  - [ ] False positives are OK (we just check disk), false negatives are NOT OK
  - [ ] Tuning: size Bloom filter for ~1% false positive rate

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss caching strategy:
  - [ ] Block cache: cache SSTable data blocks (LRU), serves most reads from memory
  - [ ] Index/cache: cache SSTable index blocks for fast key-to-block lookup
  - [ ] Row cache (optional): cache entire key-value pairs (higher memory cost)
  - [ ] Bloom filters reduce disk I/O even when cache misses
- [ ] Explain scaling/partitioning approach:
  - [ ] Hash partitioning: partition keys by hash(key) % N across nodes
  - [ ] Range partitioning: partition by key ranges (supports efficient range scans)
  - [ ] Consistent hashing for dynamic node addition/removal
  - [ ] Each partition is a replica set (primary + replicas)
- [ ] Address snapshot isolation and MVCC:
  - [ ] Each write gets a monotonically increasing sequence number (or timestamp)
  - [ ] SSTables store multiple versions of the same key with different sequence numbers
  - [ ] Read at a specific snapshot: find the latest version <= read timestamp
  - [ ] Old versions cleaned up during compaction after all snapshots have passed
- [ ] Handle range queries efficiently:
  - [ ] SSTables are sorted, so range scans are sequential reads (efficient)
  - [ ] Use SSTable index to find the starting block, then scan forward
  - [ ] Merge results from multiple SSTables using a merge iterator
- [ ] Discuss anti-entropy repair and fault tolerance:
  - [ ] Merkle tree per partition range: hash-based summary of key ranges
  - [ ] Compare Merkle trees between replicas to find inconsistent ranges
  - [ ] Repair: stream differing data between replicas
  - [ ] Hinted handoff: temporarily buffer writes for down replicas, replay on recovery
- [ ] Discuss monitoring and observability:
  - [ ] Write amplification (bytes written to disk / bytes written by client)
  - [ ] Read amplification (SSTables checked per read)
  - [ ] Space amplification (total disk usage / live data size)
  - [ ] Compaction stall rate and pending compaction bytes
  - [ ] WAL sync latency and flush frequency

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made and why
- [ ] Mention what you would improve with more time
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
