# Design Pastebin

Source: [Pastebin (CalibreOS)](https://www.calibreos.com/learn/hld-pastebin)

## One-Liner
A text-snippet sharing service where users paste content, get a short URL, and share it — the canonical back-of-envelope estimation question that tests every fundamental system design skill.

## Functional Requirements
- Create paste with content, optional title, and TTL (10 min / 1 hour / 1 day / 1 week / 1 month / never)
- View paste via short URL (6-char base62 ID like `pastebin.com/Xy3Kp9`)
- Set expiration per paste; expired pastes return 404
- Optional syntax highlighting (client-side via JS library)
- Optional auth and delete-by-owner
- Abuse detection: flag malware, phishing, illegal content

## Non-Functional Requirements
- Read latency: p99 < 50ms (with CDN)
- Write latency: p99 < 100ms
- Reads: 1K/sec avg, 10K/sec peak
- Writes: 10/sec avg, 100/sec peak
- Availability: 99.9%
- Durability: 11 nines (object storage backed)
- 5-year storage: ~2TB total

## Key Scale Questions
- 100K pastes/day (~1.2 writes/sec avg, 100 writes/sec peak)
- 100M reads/day (~1K reads/sec avg, 10K peak)
- Read:write ratio of 1000:1
- Average paste size: ~10KB
- Storage: 100K x 10KB = 1 GB/day, ~2TB over 5 years
- Peak bandwidth: 10K reads/sec x 10KB = 100 MB/sec egress (served by CDN)
- Keyspace: 62^6 = ~56.8B possible IDs, only ~183M used in 5 years (~0.3%)

## Core Components
- **Paste Service**: handle create/read/delete operations
- **ID Generator**: produce short, unique, URL-safe paste IDs
- **Object Storage (S3)**: store paste body content
- **Metadata DB (Postgres)**: store paste metadata (ID, TTL, tier, owner)
- **Cache (Redis)**: hot-tier storage for recent pastes
- **CDN**: edge caching for immutable paste content
- **Cleanup Pipeline**: async job for TTL expiration and physical deletion
- **Abuse Detection Pipeline**: inline scanning + async ML classification

## Key Design Decisions

### ID Generation
- **Random + collision check**: generate random 6-char base62 string, check DB, retry on collision. Simplest; at 0.3% keyspace usage collisions are virtually impossible.
- **Counter-based (base62-encoded)**: global counter via Redis INCR, encode to base62. No collisions but predictable IDs.
- **Snowflake encoded to base62**: distributed, unique, but IDs are ~10-11 chars (longer URLs).
- Recommendation: random + collision check is simplest and adequate. Use base58 to drop ambiguous characters (0/O, 1/l/I).

### Hot/Cold Storage Tiering
- Pastes follow a clear access pattern: created -> viewed heavily for hours/days -> cold forever.
- Hot tier (recent ~7 days): Redis or SSD-backed store. Fast reads (<1ms).
- Cold tier (older): S3 Standard or S3 IA. Reads ~50-200ms but acceptable for low-traffic pastes.
- Cost: hot (200GB) ~$40/month + cold (1.8TB) ~$7/month = $47 total vs all-in-Redis $400/month.
- Tier migration via async lifecycle job; metadata DB tracks `storage_tier` per paste.
- Right-size it: at 100K pastes/day (~2TB total), even all-SSD Postgres is cheap. Tiering matters more at 10-100x scale.

### Expiration (TTL) and Cleanup
- Metadata DB stores `expires_at` per paste. Read path checks: if expired, return 404 (soft delete).
- Async cleanup pipeline runs nightly: physically delete expired pastes from storage after grace period (~24h).
- S3 lifecycle policies can handle cold-tier cleanup natively.
- "Never expire" pastes accumulate at ~50K/day = ~180GB/year. Manageable for years; eventually tier to cheapest storage.

### Read-Heavy Optimization (4 layers)
1. **CDN edge**: Pastes are immutable (write-once), so long TTL (24h+) is safe. Cache hit ratio 95-98% for active pastes.
2. **Application cache (Redis)**: holds frequently-accessed pastes behind CDN misses.
3. **DB read replicas**: Postgres replicas handle cache-miss load; async replication lag is invisible for reads.
4. **Hot storage tier**: recent pastes (7-day window) served from Redis directly. Only older pastes fall back to S3.

### Abuse Detection
- **Inline scan**: YARA rules, regex for CC numbers, hash matching. ~50ms, blocks obvious bad pastes at create time.
- **Async ML scan**: content classifier for phishing, base64 payloads (entropy analysis), credential dumps. Flags for review in minutes.
- **Reputation scoring**: IPs and accounts with abuse history auto-quarantine new pastes.
- **User reports**: "Report this paste" button queues for human review. Takedown sets `taken_down` flag, returns 410 Gone.
- Separate service from main read/write path; signals flow async.

## API Endpoints
| Method | Path | Description |
|--------|------|-------------|
| POST | /api/pastes | Create a new paste (content, TTL, title) |
| GET | /api/pastes/{id} | View paste by short ID |
| DELETE | /api/pastes/{id} | Delete paste (owner only, auth required) |
| POST | /api/pastes/{id}/report | Report paste for abuse |

## Database Schema
### Metadata Table (Postgres)
| Column | Type | Notes |
|--------|------|-------|
| paste_id | VARCHAR(6) | PK, base62 short ID |
| content_key | VARCHAR | S3 object key for paste body |
| title | VARCHAR | Optional title |
| owner_id | BIGINT | Nullable; auth-gated users |
| expires_at | TIMESTAMP | NULL = never expires |
| storage_tier | ENUM | hot, warm, cold, archive |
| created_at | TIMESTAMP | Creation time |
| taken_down | BOOLEAN | Abuse takedown flag |

## Deep Dive Topics
- Back-of-envelope estimation as the core interview skill: do the math on keyspace, storage, bandwidth
- ID collision probability via birthday paradox: 56B keyspace, 183M IDs = negligible collision risk
- Over-engineering trap: a single Postgres + S3 + Redis + CloudFront handles 1M pastes/day; resist adding Kafka, Cassandra, and microservices
- CDN cache invalidation on delete: short TTL + explicit purge, or signed URLs that expire
- Cache stampede on viral paste: probabilistic early refresh / lock-on-miss; CDN is primary defense
- Cold-tier latency spike: monitor per-tier read rates; alert on cold reads exceeding threshold
- Storage fill from never-expire pastes: lifecycle policies even on "never expire" (e.g., expire if not accessed in 3 years)

## Follow-Up Variations
- How would you support paste editing (version history)?
- What if pastes needed real-time collaborative editing (like Google Docs)?
- How would you add syntax highlighting for 200+ programming languages efficiently?
- How do you handle a paste that goes viral (Reddit hug-of-death at 10K reads/sec)?
- What if users could create "private" pastes requiring authentication to view?
- How would you build a search feature over all public pastes?
