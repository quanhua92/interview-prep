# Design a Gaming Leaderboard

Source: [Gaming Leaderboard (CalibreOS)](https://www.calibreos.com/learn/hld-gaming-leaderboard)

## One-Liner
Design a real-time sorted ranking system for players using Redis Sorted Sets, with segmented leaderboards, anti-cheat validation, and tournament sliding windows at scale.

## Functional Requirements
- Submit/update a player's score (idempotent, p99 < 50ms)
- Get top-K players (e.g., top 100, p99 < 20ms)
- Get a player's rank (p99 < 20ms)
- Get players around a player (5 above, 5 below)
- Get score percentile ("you're top 10%")
- Tournament leaderboards with sliding windows (e.g., last 7 days)
- Anti-cheat validation on score submission (inline reject impossible scores)

## Non-Functional Requirements
- 100K-1M score updates/sec at peak
- 1M-10M reads/sec at peak
- 10M-1B players per leaderboard
- Sub-second update visibility
- 99.95% availability

## Key Scale Questions
- 10M MAU x 5 matches/day = 50M score updates/day (~580/sec avg)
- Peak (tournament weekend): ~100K updates/sec
- Reads: ~100M leaderboard views/day (~1K reads/sec avg, 100K peak)
- Sorted set memory: ~100 bytes per entry (member + score + skip list overhead)
- 10M players = 1 GB RAM per leaderboard
- 100 regional shards: ~100K players each = ~10 MB per shard

## Core Components
- **Score Submission Service**: receives scores, runs anti-cheat validation, writes to Redis
- **Redis Sorted Sets (ZSET)**: core ranking data structure (skip list + hash table)
- **Leaderboard Segmentation**: separate ZSETs per region, game mode, skill tier, season
- **Anti-Cheat Service**: server-authoritative scoring, plausibility checks, ML-based behavioral detection
- **Tournament/Window Engine**: event stream (Kafka) + periodic recompaction jobs for sliding windows
- **Top-K Cache**: cached top-100 with 1s TTL to absorb massive read load
- **WebSocket Push**: live leaderboard updates for esports broadcasts
- **Persistence Layer (Postgres/S3)**: authoritative score history, archive old seasons to S3 Parquet

## Key Design Decisions

### Why Redis Sorted Sets
- Skip list (sorted by score, O(log N) ops) + hash table (O(1) member lookup) = dual structure purpose-built for leaderboards
- Core ops: ZADD (insert/update), ZREVRANGE (top-K), ZREVRANK (rank by member), ZRANGEBYSCORE (score range)
- GT/LT modifiers (Redis 6.2+): only update if new score is greater -- enforces monotone-best without read-modify-write

### Sharding Strategy
- Single global ZSET breaks at 100M+ players: 10 GB+ memory on one node, single-threaded write bottleneck, slow failover
- **Segmented leaderboards** (default): separate ZSETs per region/mode/season. Most queries are within a segment
- **Hash-sharded within a segment**: for very large segments. Top-K requires merge from N shards (O(N log K))
- **Hierarchical**: global top-1000 ZSET recomputed from segmented leaderboards. Global top-K is cached; below 1000 needs segment query

### Tournament vs All-Time Leaderboards
- All-time: stable ZSET, straightforward
- Tournament (sliding window): store events in Kafka/Redis Stream, recompaction job periodically computes windowed scores into a snapshot ZSET
- Recompaction frequency: every minute (last hour), every 10 min (last day), nightly (last week)
- Hybrid: incremental update on new event + periodic recompaction to fix drift

### Anti-Cheat Layers
1. **Server-authoritative** (foundational): game server computes score, client cannot submit directly
2. **Plausibility checks**: max score per game, max score increase per minute, kill ratio bounds -- quarantine if violated
3. **Behavioral signals**: input cadence (perfect intervals = bot), aim accuracy beyond human limits, IP/device fingerprinting, ML detection
4. **Replay validation**: re-simulate replay file for high-stake competitive submissions
5. **Periodic audit**: manual review of top-N players, cascade removal via shared signals (IP, device)

## API Endpoints
| Method | Path | Description |
|--------|------|-------------|
| POST | /api/scores | Submit/update a player's score |
| GET | /api/leaderboard/top?k=100 | Get top-K players |
| GET | /api/leaderboard/rank/{player_id} | Get player's rank |
| GET | /api/leaderboard/around/{player_id}?neighbors=5 | Get players around a player |
| GET | /api/leaderboard/percentile/{player_id} | Get player's percentile |
| GET | /api/leaderboard/tournament?window=7d | Get tournament leaderboard |

## Database Schema
### Redis ZSET (hot path)
| Key | Member | Score |
|-----|--------|-------|
| leaderboard:{region}:{mode} | player_id | score |

### Postgres (persistent store)
| Column | Type | Notes |
|--------|------|-------|
| score_id | BIGINT | PK, Snowflake ID |
| player_id | BIGINT | FK to players |
| score | INT | Submitted score |
| game_id | BIGINT | FK to game session |
| submitted_at | TIMESTAMP | Time of submission |
| status | ENUM | pending, verified, rejected, quarantined |
| submission_id | UUID | Idempotency key |

## Deep Dive Topics
- Redis Sorted Set internals: skip list with O(log N) for all ops, hash table for member lookup, ~100 bytes per entry
- Cross-shard top-K merge: query each shard for top-K, merge sort -- O(N log K) for N shards, K items
- Rank percentile calculation: ZREVRANK gives 0-indexed rank; percentile = (rank + 1) / total * 100
- Season-based leaderboards: new ZSET per season (leaderboard:season:2024Q4), archive to S3 Parquet, drop Redis key
- Write amplification: one score update propagates to N leaderboards (global, regional, friend, skill-tier, seasonal) -- use Redis pipelining and batch updates per key
- Nearby-rank feature: ZREVRANGE leaderboard rank-5 rank+5 is O(log N + K)
- Top-K cache stampede mitigation: probabilistic early refresh (XFetch), stale-while-revalidate

## Follow-Up Variations
- How would you handle multi-dimensional rankings (by score AND skill tier AND region simultaneously)?
- What happens when a score regression bug submits 0 for all players?
- How do you handle tournament cutoff boundary races (scores arriving at midnight)?
- How would you implement a "friends-only" leaderboard on top of this?
- What if the leaderboard must support lower-is-better (lap times) alongside higher-is-better (points)?
