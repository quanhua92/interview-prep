# Design a News Feed

## One-Liner
Generate a personalized, ranked feed of posts from a user's social graph with efficient retrieval and ranking.

## Functional Requirements
- Display a chronological or ranked feed of posts from friends/followed pages
- Support posting text, images, and videos
- Like, comment, and share interactions
- Feed pagination (infinite scroll)
- Real-time feed updates when friends post

## Non-Functional Requirements
- Feed generation under 500ms
- Support 1B users with varying social graph sizes
- Read-heavy workload (feed fetch >> post creation)
- Handle viral posts efficiently (millions of likes)

## Key Scale Questions
- 1B users, 100M posts/day
- Average 500 friends per user (power users: 5,000+)
- Read:write ratio of 100:1 (feed reads dominate)
- Storage: ~1KB/post metadata x 36.5B posts/year = ~36TB/year
- Fan-out factor: 500 (average number of followers per post)

## Core Components
- **Post Service**: create, store, and retrieve posts
- **Social Graph Service**: manage friendships and follow relationships
- **Fan-out Service**: push new posts to followers' feeds
- **Feed Ranking Service**: score and rank posts for each user
- **Feed Cache**: pre-computed feed stored in Redis or memcached
- **Media Service**: image/video upload, resize, CDN delivery
- **Notification Service**: notify followers of new posts (async)

## Key Design Decisions

### Fan-out Strategy
- **Option A: Fan-out on write (push)**: Write post to all followers' feeds. Fast read, slow write for celebrities (millions of followers)
- **Option B: Fan-out on read (pull)**: Fetch latest posts from all friends at read time. Fast write, slow read, need to query N friends
- **Option C: Hybrid**: Push for normal users (followers < threshold), pull for celebrities. Best of both worlds, more complex

### Feed Ranking
- **Option A: Chronological**: Simple, no ML, predictable, but low engagement
- **Option B: Relevance score (EdgeRank-like)**: Affinity x Content weight x Time decay. Higher engagement, needs ML pipeline
- **Option C: ML-based personalization**: Neural ranking model, real-time features, highest engagement, most complex

### Pagination
- **Option A: Offset-based**: Simple, but inconsistent with new posts arriving during pagination
- **Option B: Cursor-based (keyset pagination)**: Uses post_id or timestamp as cursor. Consistent, efficient for infinite scroll

## API Endpoints
| Method | Path | Description |
|--------|------|-------------|
| POST | /api/posts | Create a new post |
| GET | /api/feed | Get user's news feed |
| GET | /api/posts/{id} | Get a single post |
| POST | /api/posts/{id}/like | Like a post |
| POST | /api/posts/{id}/comments | Add a comment |

## Database Schema
| Column | Type | Notes |
|--------|------|-------|
| post_id | BIGINT | PK, Snowflake ID |
| author_id | BIGINT | Poster user ID |
| content | TEXT | Post body |
| media_urls | JSON | Attached media |
| created_at | TIMESTAMP | Creation time |
| like_count | INT | Denormalized counter |
| comment_count | INT | Denormalized counter |

## Deep Dive Topics
- Social graph storage: adjacency list representation, edge-cut minimization for graph partitioning
- Handling celebrity accounts in hybrid fan-out (fan-out to a "special" queue, merged at read time)
- Feed pre-computation: background jobs that update feed caches periodically vs real-time push
- Denormalized counters vs exact counts (eventual consistency for like_count)

## Follow-Up Variations
- How would you handle a feed that mixes posts from friends and followed pages (different ranking)?
- What happens when a user follows 50,000 accounts?
- How would you implement "stories" (ephemeral content) on top of this?
- How do you handle post deletion propagation across all cached feeds?
