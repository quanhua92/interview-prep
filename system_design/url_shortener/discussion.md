# Design a URL Shortener

## One-Liner
Map long URLs to short, unique keys for easy sharing and analytics tracking.

## Functional Requirements
- Shorten a given long URL to a compact alias
- Redirect short URL to the original long URL
- Support custom aliases (optional)
- Track click analytics (referrer, timestamp, location)
- Expiration and deletion of short URLs

## Non-Functional Requirements
- High availability for redirect path (users click links constantly)
- Low-latency redirects (<50ms p99)
- Read-heavy workload optimization (10:1 read:write ratio)
- Horizontally scalable to handle viral link spikes

## Key Scale Questions
- 100M new URLs/day, ~1B reads/day
- Read:write ratio of 10:1
- Storage: ~100 bytes/URL metadata x 36.5B URLs/year = ~500GB/year
- Peak redirect traffic during viral events (10x normal)

## Core Components
- **API Gateway**: rate limiting, authentication for shorten endpoint
- **Shortening Service**: generates unique keys, validates URLs
- **ID Generator**: distributed unique ID (Snowflake or DB auto-increment)
- **Key-to-URL DB**: primary storage (Cassandra or sharded MySQL)
- **Redis Cache**: caches hot short URLs for fast redirects
- **Redirect Service**: lookup and 301/302 redirect
- **Analytics Pipeline**: async click event ingestion (Kafka -> analytics DB)

## Key Design Decisions

### Key Generation Strategy
- **Option A: Auto-increment ID + Base62 encode**: Simple, ordered, but exposes URL count and requires central coordination
- **Option B: Distributed ID (Snowflake) + Base62**: No single point of failure, slightly longer keys, good for distributed systems
- **Option C: Hash (MD5/SHA256) truncated + collision check**: No coordination needed, collision handling adds complexity

### Cache Strategy for Redirects
- **Option A: Cache nothing, read from DB**: Simple, but high DB load at scale
- **Option B: Write-through cache on shorten**: Hot URLs cached immediately, slight write latency increase
- **Option C: Lazy cache on first read**: Only popular URLs get cached, first redirect for any URL hits DB

### Redirect: 301 vs 302
- **301 (Permanent)**: Browser caches redirect, reduces server load, but breaks analytics for popular links
- **302 (Temporary)**: Every click hits server, full analytics, higher server load

## API Endpoints
| Method | Path | Description |
|--------|------|-------------|
| POST | /api/shorten | Create short URL from long URL |
| GET | /{short_key} | Redirect to original URL |
| DELETE | /api/shorten/{short_key} | Delete a short URL |
| GET | /api/shorten/{short_key}/stats | Get click analytics |

## Database Schema
| Column | Type | Notes |
|--------|------|-------|
| short_key | VARCHAR(10) | PK, base62 encoded ID |
| long_url | TEXT | Original URL |
| created_at | TIMESTAMP | Creation time |
| user_id | BIGINT | Creator (nullable) |
| expires_at | TIMESTAMP | Nullable, TTL |
| click_count | BIGINT | Counter (async updated) |

## Deep Dive Topics
- Base62 vs Base64 encoding trade-offs (URL-safe characters, no padding)
- Distributed ID generation: Snowflake implementation details, clock drift handling
- Consistent hashing for sharding by short_key prefix
- Handling collisions in hash-based approaches (double hash, rehash)

## Follow-Up Variations
- How would you handle custom aliases with uniqueness validation?
- What happens if the URL shortener service itself goes down during a viral event?
- How would you implement URL preview/malware detection before shortening?
- How do you handle rate limiting on the shorten endpoint to prevent abuse?
