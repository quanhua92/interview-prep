# Bloom Filters: Probabilistic Set Membership

Source: [Bloom Filters (CalibreOS)](https://www.calibreos.com/learn/hld-bloom-filters)

## One-Liner
A space-efficient probabilistic data structure that tests set membership with zero false negatives and a bounded false positive rate, used to eliminate expensive lookups for absent elements.

## Functional Requirements
- Answer "is element X in set S?" in sub-microsecond time
- Guarantee zero false negatives (if the filter says no, the element is definitely absent)
- Accept a configurable false positive rate (filter may say yes when the element is absent)
- Support insert-only workloads (standard) or insert+delete workloads (variants)
- Fit large sets (millions to billions of elements) in a small fraction of the RAM needed for exact structures

## Non-Functional Requirements
- Sub-microsecond lookups (~100 ns for in-process RAM)
- Space efficiency: ~10 bits per element at 1% FPR (vs 64+ bits for exact structures)
- No false negatives under any condition (mathematical guarantee)
- Graceful degradation: as the filter fills past capacity, FPR rises but never produces false negatives

## Key Scale Questions
- 1M elements at 1% FPR = ~1.2 MB (vs 8 MB for 1M 64-bit integers)
- 500M elements at 0.1% FPR = ~900 MB (vs 4 GB for a hash set of 64-bit keys)
- Bits-per-element anchors: 7 bits -> 2% FPR, 10 bits -> 1% FPR, 14 bits -> 0.1% FPR, 20 bits -> 0.01% FPR
- Each additional 3.3 bits/element reduces FPR by 10x; doubling bits/element reduces FPR by ~100x
- Practical ceiling: beyond ~40 bits/element, a 64-bit fingerprint hash set becomes competitive

## Core Components
- **Bit array (m bits)**: all initialized to 0; shared across all inserted elements
- **k hash functions**: each maps an element to a position in [0, m-1]; typically MurmurHash3 or xxHash
- **Insert operation**: hash element with all k functions, set k bit positions to 1
- **Query operation**: hash element with all k functions; if any bit is 0 -> "definitely absent"; if all bits are 1 -> "possibly present"
- **Hash derivation optimization (Kirsch-Mitzenmacher)**: derive k hashes from 2 base hashes: `h_i(x) = h1(x) + i * h2(x) mod m`

## Key Design Decisions

### Standard vs. Counting vs. Cuckoo Filter
- **Standard Bloom Filter**: ~10 bits/element, no deletion support, zero false negatives. Best for static/append-only sets (SSTable membership, URL shortener)
- **Counting Bloom Filter**: ~40 bits/element (4-bit counters), supports deletion via increment/decrement, overflow risk at high load. Use when deletions are occasional and 4x memory is acceptable
- **Cuckoo Filter**: ~8 bits/element, supports true deletion via fingerprint removal, no overflow. Preferred over Counting BF for new systems requiring deletions. Weakness: hard failure at ~95% capacity (vs graceful FPR increase)

### Persistence Strategy
- **In-process RAM**: ~100 ns lookup, lost on restart. Acceptable when filter can be rebuilt from source data (Cassandra rebuilds per-SSTable filters on startup)
- **Redis-backed (RedisBloom)**: ~1 ms network RTT, survives restarts via AOF/RDB, shared across instances. Required when filter state must survive crashes or be shared across replicas
- **Periodic checkpoint**: persist bit array to disk every N minutes. Accept data loss for elements added after last checkpoint

### When NOT to Use a Bloom Filter
- False positives are security-critical (access control, rate limiting, fraud detection) -- use exact structures
- Element count under ~10,000 -- a hash set is smaller, simpler, and exact
- Need to enumerate or retrieve elements -- Bloom filters are membership-only
- Heavy deletion workload with a standard Bloom filter -- silently breaks correctness

## API Endpoints
| Operation | Description |
|-----------|-------------|
| `add(element)` | Hash element with k functions, set k bits to 1. O(k) time. |
| `contains(element)` | Hash element, check k bits. Return "possibly present" or "definitely absent". O(k) time. |
| `BF.RESERVE key error_rate capacity` | RedisBloom: create a filter sized for given capacity and target FPR |
| `BF.ADD key item` | RedisBloom: add element |
| `BF.EXISTS key item` | RedisBloom: check membership |

## Database Schema
| Parameter | Type | Notes |
|-----------|------|-------|
| m | int | Bit array size. `m = -1.44 * n * log2(p)` |
| k | int | Number of hash functions. `k = (m/n) * ln(2)` |
| n | int | Expected element count (must size at creation) |
| p | float | Target false positive rate (e.g., 0.001 for 0.1%) |
| bit_array | bits | m bits, all initialized to 0 |

## Deep Dive Topics
- **Three key formulas**: (1) FPR = `(1 - e^(-kn/m))^k`, (2) optimal k = `(m/n) * ln(2)`, (3) bits needed = `m = -n * ln(p) / (ln2)^2`
- **LSM-tree read path**: per-SSTable Bloom filter in RAM eliminates disk I/O for absent keys; Cassandra default is 0.1% FPR at ~10 bits/key; a guaranteed-miss goes from 50 ms (10 disk reads) to 1 us (10 RAM lookups) = 50,000x improvement
- **Production examples**: Cassandra/HBase/BigTable (SSTable membership), Chrome Safe Browsing (~1.5-2 MB for 650K-2M malicious URLs), Akamai CDN one-hit-wonder filtering (75% of cached objects only accessed once), Medium (seen-article dedup per user), Redis (RedisBloom module for stream dedup)
- **HyperLogLog vs Bloom filter**: HyperLogLog estimates cardinality ("how many distinct elements?") using ~1.5 KB for up to 10^18 elements; Bloom filter tests membership ("is this element in the set?"). Complementary primitives -- do not confuse them in interviews
- **Persistence gotcha**: in-RAM Bloom filter is lost on process restart; for crawlers or stateful dedup, must use Redis persistence, periodic checkpointing, or a durable key-value store instead
- **Sharding for per-user filters**: 100M users x 500 seen articles = 50B elements; shard by user_id, each user gets a ~875-byte filter; total ~87.5 GB, stored in partitioned Redis

## Follow-Up Variations
- How would you size a Bloom filter for a URL shortener with 500M keys? (Worked: 900 MB at 0.1% FPR, 10 hash functions, 4.4x savings vs 4 GB hash set)
- What happens when the filter fills beyond its designed capacity? (FPR degrades gracefully, never produces false negatives)
- How do you handle Bloom filter persistence in a distributed web crawler? (Redis-backed with AOF, or periodic disk checkpoint)
- When would you choose a Cuckoo Filter over a Counting Bloom Filter? (Any new system needing deletions: better space, true deletion, no overflow)
- How would you implement per-user content dedup for a recommendation system at 100M users? (Shard Bloom filters by user_id in Redis; ~875 bytes/user at 0.1% FPR for 500 items)
- How does Cassandra's `bloom_filter_fp_chance` config affect the space/accuracy tradeoff? (Lower value = more RAM per key but fewer false-positive disk reads; tunable per table)
