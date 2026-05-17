# Design a Gaming Leaderboard System — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] Single global leaderboard or segmented (region, game mode, skill tier, season)?
  - [ ] Score model: higher-is-better (points) or lower-is-better (lap time)? All-time or time-windowed?
  - [ ] Read patterns: top-K, my-rank, players-around-me, percentile, or score range?
  - [ ] Update frequency: per-game-end (1 per match) or per-event (many per minute)?
  - [ ] Real-time visibility: sub-second (live esports) or minutes OK (mobile daily)?
  - [ ] Tournament/event leaderboards needed (time-bounded windows)?
  - [ ] Anti-cheat tolerance: casual (tolerant) or competitive (esports-grade)?
- [ ] List functional requirements (3-5 items):
  - [ ] Submit/update player score (idempotent)
  - [ ] Get top-K players (top 100)
  - [ ] Get a player's rank
  - [ ] Get players around a player (nearby ranks)
  - [ ] Get player's score percentile
- [ ] List non-functional requirements (latency, availability, scale):
  - [ ] Score submission: p99 < 50ms
  - [ ] Read queries: p99 < 20ms
  - [ ] Throughput: 100K-1M updates/sec peak
  - [ ] Sub-second update visibility
  - [ ] 99.95% availability
- [ ] State your scale estimates (users, requests, storage):
  - [ ] ~10M MAU, ~1M concurrent
  - [ ] ~50M score updates/day (~580/sec avg, 100K peak)
  - [ ] ~100M leaderboard views/day (~1K reads/sec avg, 100K peak)
  - [ ] ~100 bytes per sorted set entry
  - [ ] ~1 GB RAM per 10M-player leaderboard

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw a simple box diagram: Client -> LB -> [Score Submission Service + Anti-Cheat] -> [Redis Cluster (Sorted Sets)] -> [Postgres (persistence)] + [Kafka (event stream)]
- [ ] Identify the main operations and their access patterns:
  - [ ] `POST /api/scores` — submit score (write, high QPS)
  - [ ] `GET /api/leaderboard/top?k=100` — top-K (read, very high QPS)
  - [ ] `GET /api/leaderboard/rank/{player_id}` — player rank (read, high QPS)
  - [ ] `GET /api/leaderboard/around/{player_id}` — nearby players (read, moderate QPS)
- [ ] Note the read:write ratio and where caching helps:
  - [ ] Reads dominate (100:1 ratio during tournaments)
  - [ ] Top-K cached with 1s TTL absorbs most read load
  - [ ] Redis ZSET is itself an in-memory cache; Postgres is the persistent source of truth
- [ ] Present the diagram and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain Redis Sorted Set as the core primitive and justify:
  - [ ] Skip list (sorted by score) + hash table (member lookup) = dual structure
  - [ ] ZADD: O(log N) insert/update; ZREVRANGE: O(log N + K) top-K; ZREVRANK: O(log N) rank
  - [ ] GT modifier on ZADD enforces monotone-best (only updates if score increases)
  - [ ] Memory: ~100 bytes per entry, 10M players = 1 GB
- [ ] Define API endpoints with method, path, request/response:
  - [ ] `POST /api/scores` -> `{"submission_id": "...", "status": "accepted"}`
  - [ ] `GET /api/leaderboard/top?k=100` -> `[{"player_id": "...", "score": 9500, "rank": 1}]`
  - [ ] `GET /api/leaderboard/rank/{player_id}` -> `{"rank": 42, "score": 8700, "percentile": 0.5}`
  - [ ] `GET /api/leaderboard/around/{player_id}?neighbors=5` -> `[{"player_id": "...", "score": ..., "rank": ...}]`
- [ ] Sketch the database schema:
  - [ ] Redis ZSET key: `leaderboard:{region}:{mode}`, member: player_id, score: score
  - [ ] Table `scores`: `score_id` (PK), `player_id`, `score`, `game_id`, `submitted_at`, `status`, `submission_id`
  - [ ] Table `players`: `id`, `username`, `region`, `skill_tier`, `created_at`
- [ ] Discuss Redis vs Postgres trade-off:
  - [ ] Redis: hot leaderboard data, sub-ms reads, in-memory, rebuilt from Postgres on cold-start
  - [ ] Postgres: authoritative score history, audit trail, anti-cheat records, seasonal archive
  - [ ] S3 Parquet: archived seasons for analytics
- [ ] Walk through the main flow end-to-end:
  - [ ] Score submission: player finishes game -> game server computes score -> anti-cheat validates -> ZADD to Redis ZSET -> persist to Postgres
  - [ ] Top-K query: check top-K cache (1s TTL) -> cache miss: ZREVRANGE on Redis -> update cache -> return
  - [ ] Rank query: ZREVRANK on player's regional ZSET -> compute percentile -> return

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss sharding strategy:
  - [ ] Segmented leaderboards: separate ZSETs per region/mode/season (most common pattern)
  - [ ] Hash-sharded within a segment for very large segments
  - [ ] Cross-shard top-K: query each shard for top-K, merge sort (O(N log K))
  - [ ] Hierarchical: global top-1000 ZSET recomputed from segments
- [ ] Explain tournament/sliding window design:
  - [ ] Event stream (Kafka) stores individual game results
  - [ ] Recompaction job computes windowed scores into snapshot ZSET
  - [ ] Frequency: per-minute (1h window), per-10min (1d window), nightly (7d window)
  - [ ] Hybrid: incremental update on new event + periodic recompaction to fix drift
- [ ] Address anti-cheat as a first-class system:
  - [ ] Server-authoritative scoring (foundational -- client cannot submit scores)
  - [ ] Plausibility checks: max score per game, score increase rate, kill ratio bounds
  - [ ] Behavioral detection: input cadence, aim accuracy, IP/device fingerprinting, ML
  - [ ] Quarantine-and-review flow (do not publish suspicious scores immediately)
  - [ ] Removal: ZREM on confirmed cheaters, cascade by shared signals
- [ ] Handle consistency and real-time concerns:
  - [ ] Single-shard: instant (ZADD acknowledged, next read reflects it)
  - [ ] Cross-region: eventual consistency, recompaction job for global view
  - [ ] Read-after-write: local Redis returns updated state; client caches optimistically
  - [ ] Top-K cache: 1s TTL, stale-while-revalidate, bypass for live esports
  - [ ] WebSocket push for live leaderboard displays
- [ ] Discuss failure modes:
  - [ ] Cheater at #1: server-authoritative + plausibility + ML detection
  - [ ] Score regression bug: GT modifier on ZADD, alert on score-decrease patterns
  - [ ] Top-K cache stampede: probabilistic early refresh (XFetch), stale-while-revalidate
  - [ ] Hot shard (popular region): monitor per-shard load, sub-shard, accept asymmetric provisioning
  - [ ] Tournament cutoff race: clear boundary semantics, explicit reconciliation

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made and why
- [ ] Mention what you would improve with more time
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
