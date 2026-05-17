# Back-of-Envelope Estimation -- Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] Confirm DAU (or derive from MAU x 0.3-0.5 if not given)
- [ ] Identify major user actions and estimate per-user action rates:
  - [ ] How many reads per user per day? (e.g., feed loads, page views)
  - [ ] How many writes per user per day? (e.g., posts, messages, uploads)
  - [ ] State the read:write ratio explicitly
- [ ] List data object sizes for the domain:
  - [ ] What is the size of each record/row/object being stored?
  - [ ] Are there media attachments? (photos, videos -- these dominate storage)
- [ ] State assumptions clearly to the interviewer before computing

## Phase 2: Traffic Estimation (2-3 min)
- [ ] Compute average QPS for each action: DAU x actions/user/day / 86,400
- [ ] Compute peak QPS: average QPS x 3 (consumer apps) or x 5-10 (B2B)
- [ ] Separate read QPS from write QPS
- [ ] Identify which is the bottleneck (usually reads for consumer apps)
- [ ] State: "Peak QPS is X, which is Yx beyond a single [DB/Redis/app server]"
- [ ] Make the architecture implication explicit:
  - [ ] <1K QPS: single server, no caching
  - [ ] 1K-10K: LB + read replicas, light caching
  - [ ] 10K-100K: Redis mandatory, ~93%+ hit rate
  - [ ] 100K-1M: CDN + multi-tier caching + sharding
  - [ ] >1M: distributed everything, multi-region

## Phase 3: Capacity Estimation (2-3 min)
- [ ] Estimate server count: peak QPS / single-server throughput
  - [ ] App servers: peak QPS / 10K-30K RPS per node
  - [ ] DB capacity: check against single-instance limits (~5K complex QPS for Postgres)
- [ ] If using cache, compute required hit rate: (peak QPS - DB capacity) / peak QPS
- [ ] For connection-heavy systems (chat, real-time):
  - [ ] Estimate concurrent connections: DAU x connection-model (persistent vs polling)
  - [ ] Connection servers = concurrent connections / 65K per server
- [ ] For message-queue systems: check Kafka/broker throughput (~500K msgs/sec per broker)
- [ ] Present the numbers and get alignment before moving on

## Phase 4: Storage Estimation (2-3 min)
- [ ] Compute daily raw storage: writes/sec x bytes/record x 86,400
- [ ] Apply three multipliers:
  - [ ] Replication factor: x3 (HDFS, Kafka, S3, Postgres with replicas)
  - [ ] Index overhead: x1.5-2x for relational DBs (skip for object storage)
  - [ ] Encoding variants: x4x for video (5 resolution tiers); skip for text
- [ ] Compute 5-year total: daily (with multipliers) x 1,825 days
- [ ] Identify the storage tier:
  - [ ] <1 TB: single DB
  - [ ] 1-100 TB: S3 for blobs + DB for structured
  - [ ] 100 TB - 1 PB: tiered retention (hot/warm/cold)
  - [ ] >1 PB: distributed file system (HDFS/Colossus), multi-DC
- [ ] Sanity-check from a second direction (total corpus or known benchmarks)
- [ ] State: "This is [GB/TB/PB/EB] territory, which implies [storage choice]"

## Phase 5: Connect to Design (2-3 min)
- [ ] Summarize: "Peak [X] read QPS, [Y] write QPS, [Z] storage over 5 years"
- [ ] State the binding constraint: is it CPU, memory, network, I/O, or connections?
- [ ] Connect each number to a design decision:
  - [ ] High read QPS -> caching layer required, here's the hit rate
  - [ ] High storage -> sharding or object storage, here's the tier
  - [ ] High connections -> connection-tier fleet, here's the server count
  - [ ] High write QPS -> Kafka/message queue, partition count
- [ ] Mention trade-offs and what would change with different assumptions
- [ ] Move on to the actual system design -- estimation is the input, not the output

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
