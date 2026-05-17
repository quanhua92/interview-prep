# Design a News Aggregator

Source: [News Aggregator (CalibreOS)](https://www.calibreos.com/learn/hld-news-aggregator)

## One-Liner
Design a Reddit/Hacker News-style content aggregator with vote-based ranking algorithms, community feeds, and nested comment threading at scale (400M MAU).

## Functional Requirements
- Submit posts (link or text) to community subreddits
- Upvote and downvote posts and comments (+1/-1, one vote per user per item)
- Subreddit feeds with multiple sort modes: Hot, New, Rising, Top, Controversial
- Home feed for logged-in users (merged from subscribed subreddits)
- Front page for anonymous guests (global popular feed)
- Nested comment threads with unlimited depth
- User karma derived from votes on own posts/comments

## Non-Functional Requirements
- Feed load latency: ~100ms p99
- Vote score display updates within ~30 seconds (eventual consistency)
- Throughput: ~18K feed reads/sec peak, ~2,300 votes/sec, ~23 posts/sec
- Availability: 99.9%
- Strong consistency for vote deduplication (no double-voting); eventual consistency for scores

## Key Scale Questions
- 400M MAU, ~50M DAU
- ~2M posts/day, ~30M comments/day, ~200M votes/day
- Read:write ratio ~200:1 (feed serving dominates)
- ~57K active subreddits
- Post storage: ~7.3TB over 5 years; Vote table: ~18TB over 5 years
- Core challenge is NOT fan-out (unlike Twitter) — it is ranking + vote aggregation + community feed generation

## Core Components
- **Post Service**: create, store, and retrieve posts (link or self-text)
- **Vote Service**: accept votes, enforce uniqueness via DB constraint, publish to Kafka
- **Vote Aggregation Pipeline**: Kafka + Flink — batch vote deltas in 1-min windows, bulk-update Postgres
- **Feed Ranking Service**: recompute hot/rising/top scores on schedule, update Redis sorted sets
- **Feed Service**: serve subreddit/home/front-page feeds from Redis sorted sets
- **Comment Service**: store comments with materialized path, retrieve subtrees efficiently
- **Subscription Service**: manage user-to-subreddit subscriptions for home feed generation

## Key Design Decisions

### Vote Aggregation: Delta vs. Per-Vote Update
- **Naive**: `UPDATE posts SET score = score + 1` per vote — causes hot-row lock contention on viral posts (10K+ votes/sec serialized on one row)
- **Delta aggregation via Kafka**: Each vote writes to votes table (dedup) + Kafka topic. Flink batches deltas per post in 1-min windows, applies bulk update to Postgres. Display score served from Redis `INCR` (atomic, arbitrary throughput)

### Feed Pre-Computation Strategy
- **Subreddit feeds**: One Redis sorted set per subreddit per sort type (`subreddit:{id}:hot`, etc.). Ranking service recomputes on schedule (Hot: every 5 min, Top: every 15-60 min, New: real-time ZADD on post creation)
- **Home feed (logged-in)**: Read-time merge — pipeline K Redis ZREVRANGE calls for subscribed subreddits, merge in memory. Works well for K <= 200 subscriptions. Cheaper than maintaining 50M per-user materialized feeds
- **Front page (guest)**: Single global sorted set `global:front_page`, recomputed every ~60s from top subreddits

### Comment Threading: Materialized Path vs. Closure Table
- **Materialized path** (chosen): Store full ancestry path as string (`'0001.0003.0012'`). Subtree retrieval via `WHERE path LIKE 'prefix%'` — single B-tree index scan. One query returns full tree in order. Compact storage
- **Closure table** (alternative): Stores all ancestor-descendant pairs. More flexible for moves, but O(d x n) storage growth. Overkill for mostly-immutable comment trees

### Ranking Algorithm Selection
- **Hot (Reddit)**: `sign(score) * log10(max(|score|, 1)) + (epoch_seconds / 45000)` — logarithmic vote compression means early votes matter more; time factor continuously decays old posts
- **Hot (HN)**: `(points - 1) / (age_hours + 2)^1.8` — simpler, more aggressive time decay
- **Rising**: vote velocity ratio `votes_last_hour / max(votes_last_24h, 1)` — catches breakout posts
- **Comments (Wilson Score)**: lower bound of 95% CI on upvote proportion — handles low-vote items fairly (1/1 upvotes ranks below 500/510 upvotes correctly)

## API Endpoints
| Method | Path | Description |
|--------|------|-------------|
| POST | /api/posts | Submit a post to a subreddit |
| GET | /api/subreddits/{id}/feed?sort=hot&cursor=xxx | Get subreddit feed |
| GET | /api/feed/home?cursor=xxx | Get personalized home feed |
| GET | /api/feed/front | Get front page (guest) |
| POST | /api/vote | Cast upvote/downvote (post or comment) |
| POST | /api/comments | Add a comment (with parent_comment_id for replies) |
| GET | /api/posts/{id}/comments?cursor=xxx | Get comment tree for a post |
| POST | /api/subreddits | Create a subreddit |
| POST | /api/subscriptions | Subscribe to a subreddit |

## Database Schema
### posts
| Column | Type | Notes |
|--------|------|-------|
| post_id | BIGINT | PK, Snowflake ID |
| subreddit_id | BIGINT | FK to subreddits |
| author_id | BIGINT | FK to users |
| title | VARCHAR(300) | Post title |
| url | VARCHAR | Nullable, for link posts |
| selftext | TEXT | Nullable, for text posts |
| score | INT | Denormalized: upvotes - downvotes |
| upvote_count | INT | Denormalized counter |
| downvote_count | INT | Denormalized counter |
| created_at | TIMESTAMP | Used in ranking formulas |

### comments
| Column | Type | Notes |
|--------|------|-------|
| comment_id | BIGINT | PK |
| post_id | BIGINT | FK to posts |
| parent_comment_id | BIGINT | Nullable (null = top-level) |
| author_id | BIGINT | FK to users |
| body | TEXT | Comment content |
| score | INT | Denormalized counter |
| path | VARCHAR | Materialized path e.g. '0001.0003.0012' |
| depth | INT | Nesting level |

### votes
| Column | Type | Notes |
|--------|------|-------|
| user_id | BIGINT | Composite PK |
| target_id | BIGINT | Composite PK (post or comment) |
| target_type | ENUM | Composite PK ('post' or 'comment') |
| direction | SMALLINT | +1 or -1 |
| created_at | TIMESTAMP | |

### subreddits
| Column | Type | Notes |
|--------|------|-------|
| subreddit_id | BIGINT | PK |
| name | VARCHAR | Unique slug |
| subscriber_count | INT | Denormalized |
| moderator_ids | ARRAY | |
| settings | JSONB | NSFW flag, posting rules |

### subscriptions
| Column | Type | Notes |
|--------|------|-------|
| user_id | BIGINT | Composite PK |
| subreddit_id | BIGINT | Composite PK |
| subscribed_at | TIMESTAMP | |

## Deep Dive Topics
- Vote fuzzing: randomly perturb displayed scores by ~10% to prevent bot score-targeting (presentation-layer only, not stored)
- Hot-row problem: why naive per-vote UPDATE deadlocks on viral posts and how Kafka + Flink delta aggregation solves it
- Wilson Score for comment ranking: why simple score fails (1 upvote / 0 downvotes should not equal 10 upvotes / 9 downvotes)
- Redis sorted set sizing: ~200-2,000 entries per subreddit per sort, ~9GB total for all 57K subreddits x 5 sorts
- Home feed scaling limit: read-time merge works up to ~200 subscriptions; beyond ~500, merge overhead dominates
- Vote table partitioning: hash-partition by target_id to distribute viral post write load across shards
- Cross-datacenter: async Redis replication for sorted sets (~100ms lag acceptable); vote writes to primary region Postgres
- Feed staleness tradeoff: Hot sorted sets refresh every 5 min — viral posts may take up to 5 min to appear, which is acceptable

## Follow-Up Variations
- How would you add a "save post" and "saved posts feed" feature?
- What changes if subreddits have private membership (requires auth for feed reads)?
- How would you implement cross-posting (same post in multiple subreddits)?
- How do you handle moderation at scale (automated content filtering, report queues)?
- What if you needed real-time Hot feed updates (sub-5-min freshness) — what are the cost tradeoffs?
- How would you add a recommendation system that surfaces posts from non-subscribed subreddits?
