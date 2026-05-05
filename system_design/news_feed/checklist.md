# Design a News Feed System — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] Is the feed chronological (reverse-chronological) or ranked (algorithm-based)?
  - [ ] What post types do we support: text, image, video, links, or all of the above?
  - [ ] Is the social model friend-based (bidirectional, like Facebook) or follower-based (unidirectional, like Twitter)?
- [ ] List functional requirements (3-5 items):
  - [ ] Users can create posts (text, images, videos)
  - [ ] Users can follow other users
  - [ ] Users see a feed of posts from people they follow
  - [ ] Users can like, comment, and share posts
  - [ ] Feed should update in near real-time
- [ ] List non-functional requirements (latency, availability, scale):
  - [ ] Low latency: feed load in <200ms
  - [ ] High availability: 99.9% uptime
  - [ ] Scalability: handle millions of users and billions of posts
  - [ ] Freshness: new posts appear in follower feeds within seconds
- [ ] State your scale estimates (users, requests, storage):
  - [ ] ~1B total users, ~200M DAU
  - [ ] ~500M new posts/day (~6K posts/sec)
  - [ ] ~100M feed loads/day (~1.2K feed loads/sec)
  - [ ] ~10 new follows per user on average
  - [ ] Storage: ~50TB for posts + metadata per year

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw a simple box diagram: Client -> LB -> [Feed Service] -> [Social Graph Service + Post Service] -> [Cache + DB]
- [ ] Identify the main operations and their access patterns:
  - [ ] `POST /api/posts` — create a post (write, moderate QPS)
  - [ ] `GET /api/feed` — load user's feed (read, high QPS)
  - [ ] `POST /api/follow` — follow a user (write, low QPS)
  - [ ] `POST /api/posts/{id}/like` — like a post (write, high QPS)
- [ ] Note the read:write ratio and where caching helps:
  - [ ] Read:Write ratio ~100:1 (feed reads dominate)
  - [ ] Cache pre-computed feeds, post data, and user profiles
  - [ ] Pre-generate feeds for active users (fan-out on write)
- [ ] Present the diagram and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain fan-out strategy choice and justify:
  - [ ] Fan-out on Write (push model): pre-compute feeds when a post is created, fast reads
  - [ ] Fan-out on Read (pull model): compute feed on demand, slow reads but simple writes
  - [ ] Hybrid approach: push for users with <N followers, pull for celebrities with >N followers
  - [ ] State your choice and the threshold (e.g., hybrid with N = 1M followers)
- [ ] Define API endpoints with method, path, request/response:
  - [ ] `POST /api/posts` -> `{"post_id": "...", "created_at": "..."}`
  - [ ] `GET /api/feed?cursor=xxx&limit=20` -> `[{"post_id": "...", "content": "...", "author": "..."}]`
  - [ ] `POST /api/users/{id}/follow` -> `200 OK`
  - [ ] `POST /api/posts/{id}/like` -> `{"likes": 42}`
- [ ] Sketch the database schema:
  - [ ] Table `users`: `id`, `username`, `profile_pic`, `created_at`
  - [ ] Table `posts`: `id`, `user_id (FK)`, `content`, `media_urls`, `created_at`, `like_count`, `comment_count`, `share_count`
  - [ ] Table `follows`: `follower_id (FK)`, `followee_id (FK)`, `created_at` (composite PK)
  - [ ] Table `feed` (for fan-out on write): `user_id`, `post_id`, `created_at` (partitioned by user_id, ordered by created_at)
- [ ] Discuss SQL vs NoSQL trade-off:
  - [ ] Social graph (follows): graph DB or SQL with proper indexing
  - [ ] Posts: SQL for strong consistency on counts, or NoSQL (Cassandra) for write scalability
  - [ ] Feed table: NoSQL (Cassandra) partitioned by user_id for fast reads
- [ ] Walk through the main flow end-to-end:
  - [ ] Post creation: user creates post -> Post Service stores -> Fan-out Service pushes post_id to all followers' feed tables -> if celebrity (>1M followers), write to a special pull list
  - [ ] Feed load: user requests feed -> Feed Service reads from feed table (pull) + merges celebrity posts (pull) + ranks/sorts -> returns posts with pagination

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss caching strategy:
  - [ ] Cache pre-computed feed in Redis for active users (TTL ~5 min)
  - [ ] Cache post metadata (author, content, media URLs) separately
  - [ ] Invalidate feed cache when a new post from a followed user arrives
- [ ] Explain scaling/partitioning approach:
  - [ ] Partition feed table by `user_id` (each user's feed on one shard)
  - [ ] Partition posts by `post_id` for even distribution
  - [ ] Partition social graph by `follower_id` (each user's follow list on one shard)
- [ ] Address single points of failure:
  - [ ] Async fan-out via message queue (Kafka) to decouple post creation from fan-out
  - [ ] Multi-AZ database and cache deployment
  - [ ] Retry failed fan-out jobs from the queue
- [ ] Handle the celebrity problem (millions of followers):
  - [ ] Hybrid approach: push for normal users, pull for celebrities
  - [ ] Mark celebrity posts in a separate table/list
  - [ ] On feed load, merge pushed posts + pull celebrity posts + rank
  - [ ] Optionally pre-compute celebrity posts on a timer for top-N followers
- [ ] Discuss ranking algorithm:
  - [ ] Chronological: simple, predictable
  - [ ] Engagement-based: score = f(recency, likes, comments, shares, user relationship)
  - [ ] ML-based: personalization using user's past engagement patterns
  - [ ] Trade-off: ranking adds latency, can pre-compute scores periodically

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made and why
- [ ] Mention what you would improve with more time
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
