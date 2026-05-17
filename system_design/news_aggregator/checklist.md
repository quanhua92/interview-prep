# Design a News Aggregator System — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] Authenticated only or anonymous browsing? (Reddit allows both — affects caching)
  - [ ] Which feed types: subreddit feed, home feed, front page?
  - [ ] Which ranking algorithms: Hot, New, Rising, Top, Controversial?
  - [ ] Upvotes AND downvotes, or upvote-only (like Hacker News)?
  - [ ] Comment threading depth: unlimited or capped?
- [ ] List functional requirements (3-5 items):
  - [ ] Users submit posts (link or text) to subreddits
  - [ ] Users upvote/downvote posts and comments
  - [ ] Subreddit feeds with multiple sort modes (Hot, New, Rising, Top)
  - [ ] Home feed for logged-in users (merged from subscribed subreddits)
  - [ ] Nested comment threads with efficient subtree retrieval
- [ ] List non-functional requirements (latency, availability, scale):
  - [ ] Feed load < 100ms p99
  - [ ] Vote score updates within ~30 seconds (eventual consistency)
  - [ ] 99.9% availability
  - [ ] Strong consistency for vote deduplication (no double-voting)
- [ ] State your scale estimates (users, requests, storage):
  - [ ] ~400M MAU, ~50M DAU
  - [ ] ~2M posts/day, ~30M comments/day, ~200M votes/day
  - [ ] ~18K feed reads/sec peak
  - [ ] Read:write ratio ~200:1

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw a simple box diagram: Client -> LB -> [Feed Service / Vote Service / Post Service] -> [Redis Sorted Sets + Kafka + Postgres]
- [ ] Identify the main operations and their access patterns:
  - [ ] `GET /api/subreddits/{id}/feed?sort=hot` — read subreddit feed (highest QPS)
  - [ ] `POST /api/vote` — cast vote (high QPS write, async to Kafka)
  - [ ] `POST /api/posts` — submit post (moderate QPS)
  - [ ] `GET /api/feed/home` — home feed (read-time merge of K subreddits)
- [ ] Note the read:write ratio and where caching helps:
  - [ ] Read:Write ratio ~200:1 (feed reads massively dominate)
  - [ ] Pre-compute subreddit feeds as Redis sorted sets
  - [ ] Serve displayed scores from Redis, not Postgres
- [ ] Present the diagram and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain feed pre-computation strategy and justify:
  - [ ] Subreddit feeds: one Redis sorted set per subreddit per sort type
  - [ ] Home feed: read-time merge (pipeline K ZREVRANGE calls, merge in memory) — works for K <= 200
  - [ ] Front page: single global sorted set, recomputed every ~60s
  - [ ] Why NOT per-user materialized feeds: subreddit feeds are already pre-computed, read-time merge is cheap
- [ ] Define API endpoints with method, path, request/response:
  - [ ] `POST /api/posts` -> `{post_id, created_at}`
  - [ ] `GET /api/subreddits/{id}/feed?sort=hot&cursor=xxx` -> `[post list]`
  - [ ] `POST /api/vote` -> `200 OK` (writes to votes table + Kafka)
  - [ ] `GET /api/posts/{id}/comments` -> `[comment tree]`
- [ ] Sketch the database schema:
  - [ ] Table `posts`: `post_id` (Snowflake), `subreddit_id`, `author_id`, `title`, `url`, `selftext`, `score`, `upvote_count`, `downvote_count`, `created_at`
  - [ ] Table `comments`: `comment_id`, `post_id`, `parent_comment_id`, `author_id`, `body`, `score`, `path` (materialized path), `depth`
  - [ ] Table `votes`: `(user_id, target_id, target_type)` composite PK, `direction` (+1/-1)
  - [ ] Table `subreddits`: `subreddit_id`, `name` (unique slug), `subscriber_count`, `settings`
  - [ ] Table `subscriptions`: `(user_id, subreddit_id)` composite PK
- [ ] Discuss SQL vs NoSQL trade-off:
  - [ ] Posts/comments/votes: Postgres with hash partitioning (by subreddit_id or target_id)
  - [ ] Feed ranking: Redis sorted sets (not a DB — a cache layer for ranked feeds)
  - [ ] Vote stream: Kafka for async delta aggregation
- [ ] Walk through the main flow end-to-end:
  - [ ] Post creation: user posts -> Post Service stores in Postgres -> ZADD to subreddit's "new" sorted set
  - [ ] Vote: user votes -> INSERT/UPDATE votes table (dedup) + publish to Kafka topic -> Flink batches deltas -> bulk update Postgres -> ranking service updates Redis sorted sets
  - [ ] Feed read: ZREVRANGE from Redis sorted set -> hydrate post metadata from Postgres/read replica -> return

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Explain the ranking algorithms:
  - [ ] Hot (Reddit): `sign(score) * log10(max(|score|, 1)) + epoch_seconds / 45000` — logarithmic compression + time decay
  - [ ] Hot (HN): `(points - 1) / (age_hours + 2)^1.8` — aggressive decay
  - [ ] Wilson Score for comments: 95% CI lower bound on upvote proportion
  - [ ] Rising: vote velocity ratio (recent votes / total votes)
  - [ ] Controversial: low |upvotes - downvotes| / max(upvotes, downvotes) with minimum vote threshold
- [ ] Discuss vote aggregation at scale:
  - [ ] Hot-row problem: naive UPDATE deadlocks on viral posts (10K+ votes/sec on one row)
  - [ ] Delta aggregation: Kafka + Flink 1-min tumbling windows -> bulk UPDATE
  - [ ] Redis INCR for live display score (atomic, ~100K ops/sec per core)
  - [ ] Vote fuzzing: perturb displayed scores ~10% to break bot targeting
- [ ] Explain comment threading:
  - [ ] Materialized path: `WHERE path LIKE 'prefix%'` — single B-tree scan, one query for full subtree
  - [ ] Why NOT adjacency list (N+1 queries or slow recursive CTEs) or closure table (O(d*n) storage)
  - [ ] Thread hydration: load top 3 comments by Wilson Score for feed preview; full tree on click
- [ ] Address scalability concerns:
  - [ ] Redis sorted set sizing: ~200-2,000 entries per set, ~9GB total across all subreddits and sorts
  - [ ] Posts table partitioning: by subreddit_id or created_at (monthly)
  - [ ] Votes table partitioning: hash by target_id to distribute viral post load
  - [ ] Home feed merge limit: works up to ~200 subscriptions; cap or paginate beyond that
- [ ] Handle failure modes:
  - [ ] Feed staleness: Hot sorted sets refresh every 5 min — acceptable tradeoff
  - [ ] Cache miss fallback: rebuild subreddit sorted set from Postgres
  - [ ] Vote spike on viral post: Redis handles display; Kafka/Flink handle DB writes
  - [ ] Cross-region: async Redis replication (~100ms lag acceptable for feeds)

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made and why
- [ ] Mention what you would improve with more time
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
