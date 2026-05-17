# Bloom Filters — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the core problem: many queries ask for elements that don't exist, and each guaranteed-miss lookup wastes an expensive operation (disk I/O, network call, etc.)
- [ ] Ask clarifying questions:
  - [ ] Is the set static/append-only, or do elements need to be deleted?
  - [ ] What is the cost of a false positive? (wasted disk read vs. user-facing error)
  - [ ] Does the filter need to survive process restarts?
  - [ ] How many elements (n) and what target FPR (p)?
- [ ] State the two key properties:
  - [ ] Zero false negatives: if the filter says "absent", the element is guaranteed not in the set
  - [ ] Bounded false positives: filter may say "present" when the element is absent, but rate is controlled by sizing parameters
- [ ] Quantify space savings: ~10 bits/element at 1% FPR vs 64+ bits for exact structures (7-14x more memory-efficient)
- [ ] Know the rule-of-thumb anchors:
  - [ ] 7 bits/elem -> ~2% FPR (k~5)
  - [ ] 10 bits/elem -> ~1% FPR (k~7)
  - [ ] 14 bits/elem -> ~0.1% FPR (k~10)
  - [ ] 20 bits/elem -> ~0.01% FPR (k~14)

## Phase 2: High-Level Design (3-5 min)
- [ ] Describe the data structure: bit array of m bits (all 0s) + k independent hash functions
- [ ] Explain insert: hash element with k functions, set k bit positions to 1
- [ ] Explain query: hash element with k functions; any bit 0 -> "definitely absent"; all bits 1 -> "possibly present"
- [ ] Explain why false negatives are impossible: inserted bits stay at 1 forever; no code path unsets them
- [ ] Explain why false positives occur: bit positions are shared across elements; k positions can coincidentally all be 1 from other elements
- [ ] Explain why standard Bloom filters cannot support deletion: unsetting bits shared with other elements would introduce false negatives
- [ ] Mention hash function choice: MurmurHash3 or xxHash (fast, uniform distribution, not cryptographic); Kirsch-Mitzenmacher trick to derive k hashes from 2 base hashes

## Phase 3: Core Component Design (5-8 min)
- [ ] State the three sizing formulas:
  - [ ] FPR: `p = (1 - e^(-kn/m))^k`
  - [ ] Optimal k: `k = (m/n) * ln(2)` (balances discrimination vs. bit saturation)
  - [ ] Bits needed: `m = -1.44 * n * log2(p)` (the key interview formula)
- [ ] Walk through a worked sizing example:
  - [ ] 1M elements at 0.1% FPR: m ~ 14.4M bits (~1.8 MB), k ~ 10
  - [ ] 500M elements at 0.1% FPR: m ~ 7.2B bits (~900 MB), k ~ 10
- [ ] Choose the right variant for the use case:
  - [ ] Standard Bloom filter: append-only sets (SSTable membership, URL shortener)
  - [ ] Cuckoo filter: dynamic sets with deletions (~8 bits/elem, true deletion, preferred over Counting BF)
  - [ ] Counting Bloom filter: dynamic sets when 4x memory cost is acceptable (~40 bits/elem, deletion via 4-bit counters, overflow risk)
- [ ] Address persistence:
  - [ ] In-process RAM: fast but lost on restart (ok for rebuildable filters like Cassandra SSTables)
  - [ ] Redis-backed (RedisBloom): survives restarts, shared across instances, ~1 ms RTT
  - [ ] Periodic disk checkpoint: accept data loss after last checkpoint
- [ ] Walk through end-to-end flow for a real system:
  - [ ] Cassandra read: key lookup -> check per-SSTable Bloom filters in RAM -> skip SSTables that say "absent" -> read only SSTables that say "possibly present"
  - [ ] Web crawler: fetch URL -> check Redis Bloom filter -> if "absent", crawl and add to filter -> if "possibly present", skip (with small chance of false skip)

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss production examples and their sizing:
  - [ ] Cassandra: ~10 bits/key at 0.1% FPR, tunable via `bloom_filter_fp_chance`
  - [ ] Chrome Safe Browsing: ~1.5-2 MB for 650K-2M malicious URLs, eliminates ~99.9% of API calls
  - [ ] Akamai CDN: one-hit-wonder filter, only cache objects on second request, improves cache hit rate from ~25% to ~50%
  - [ ] Medium: per-user seen-article filter, periodically reset when FPR rises
- [ ] Explain the LSM-tree read path integration:
  - [ ] Each SSTable has a companion Bloom filter in RAM
  - [ ] Without filter: N disk reads for N SSTables (1-10 ms each)
  - [ ] With filter: N RAM lookups (~100 ns each), disk I/O only for "possibly present" SSTables
  - [ ] 50,000x latency improvement for guaranteed-miss queries
- [ ] Compare with HyperLogLog (common interview trap):
  - [ ] Bloom filter: set membership ("is X in the set?")
  - [ ] HyperLogLog: cardinality estimation ("how many distinct elements?") using ~1.5 KB for any cardinality up to 10^18
  - [ ] They solve different problems; confusing them signals shallow understanding
- [ ] Handle the persistence gotcha:
  - [ ] In-RAM filter lost on restart -> crawler re-crawls all URLs
  - [ ] Solutions: Redis with AOF, periodic checkpoint, or replace with durable key-value store
- [ ] Discuss scaling for per-user filters:
  - [ ] 100M users x 500 items each = 50B elements total
  - [ ] Shard by user_id: each user gets ~875 bytes (500 items x 14 bits)
  - [ ] Total: ~87.5 GB, stored in partitioned Redis or dedicated probabilistic store
- [ ] Know when NOT to propose a Bloom filter:
  - [ ] False positives are security-critical (access control, fraud detection)
  - [ ] Fewer than ~10K elements (use exact hash set)
  - [ ] Need to enumerate or retrieve elements
  - [ ] Heavy deletions with a standard Bloom filter

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize: Bloom filter trades bounded false positives for massive space savings and sub-microsecond lookups
- [ ] State the sizing for the interview problem: "n elements at p% FPR needs m bits with k hash functions"
- [ ] Mention what you would improve with more time (e.g., Cuckoo filter for deletions, Redis persistence, adaptive FPR tuning)
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
