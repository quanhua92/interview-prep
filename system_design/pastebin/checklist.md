# Design Pastebin — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] Max paste size? (Default: 1MB; real Pastebin: 512KB free, 10MB premium)
  - [ ] Expiration model? (TTL options: 10min, 1hour, 1day, 1week, 1month, never)
  - [ ] Privacy model? (Public, unlisted, or auth-required)
  - [ ] Auth and edit support? (Default: read-only public pastes; auth optional)
  - [ ] Syntax highlighting? (Client-side or server-side)
- [ ] List functional requirements (3-5 items):
  - [ ] Users can create pastes with content + TTL + optional title
  - [ ] Users can view pastes via short URL
  - [ ] Pastes expire based on TTL; expired pastes return 404
  - [ ] Optional: auth, delete-by-owner, syntax highlighting
  - [ ] Abuse detection for malware, phishing, illegal content
- [ ] List non-functional requirements (latency, availability, scale):
  - [ ] Read latency: p99 < 50ms (with CDN)
  - [ ] Write latency: p99 < 100ms
  - [ ] Availability: 99.9%
  - [ ] Durability: 11 nines (object storage)
- [ ] State your scale estimates (users, requests, storage):
  - [ ] ~100K pastes/day (~1.2 writes/sec avg, 100 peak)
  - [ ] ~100M reads/day (~1K reads/sec avg, 10K peak)
  - [ ] Read:write ratio ~1000:1
  - [ ] Average paste size ~10KB
  - [ ] Storage: ~1 GB/day, ~2TB over 5 years

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw a simple box diagram: Client -> CDN -> LB -> [Paste Service] -> [Cache (Redis) + Metadata DB (Postgres) + Object Storage (S3)]
- [ ] Identify the main operations and their access patterns:
  - [ ] `POST /api/pastes` — create paste (write, low QPS)
  - [ ] `GET /api/pastes/{id}` — view paste (read, high QPS, 1000:1 ratio)
  - [ ] `DELETE /api/pastes/{id}` — delete paste (write, very low QPS)
  - [ ] `POST /api/pastes/{id}/report` — report abuse (write, very low QPS)
- [ ] Note the read:write ratio and where caching helps:
  - [ ] Read:Write ratio ~1000:1 (read-heavy)
  - [ ] CDN caches immutable paste content at edge (95-98% hit ratio)
  - [ ] Redis caches hot/recent pastes behind CDN
- [ ] Present the diagram and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain ID generation strategy and justify:
  - [ ] Random 6-char base62 + collision check: simplest, 62^6 = 56.8B IDs, 0.3% keyspace usage
  - [ ] Counter-based (base62-encoded): no collisions but predictable URLs
  - [ ] Snowflake encoded as base62: distributed but IDs too long (~10-11 chars)
  - [ ] State your choice (recommend: random + collision check)
  - [ ] Mention base58 to avoid ambiguous characters (0/O, 1/l/I)
- [ ] Define API endpoints with method, path, request/response:
  - [ ] `POST /api/pastes` -> `{"id": "Xy3Kp9", "url": "pastebin.com/Xy3Kp9"}`
  - [ ] `GET /api/pastes/{id}` -> `{"content": "...", "title": "...", "created_at": "..."}`
  - [ ] `DELETE /api/pastes/{id}` -> `204 No Content`
  - [ ] `POST /api/pastes/{id}/report` -> `{"status": "queued"}`
- [ ] Sketch the database schema:
  - [ ] Table `pastes`: `paste_id (VARCHAR(6), PK)`, `content_key (VARCHAR, S3 key)`, `title`, `owner_id`, `expires_at (TIMESTAMP)`, `storage_tier (ENUM)`, `created_at`, `taken_down (BOOLEAN)`
  - [ ] Object storage (S3): paste body stored as objects keyed by content_key
- [ ] Discuss storage tiering:
  - [ ] Hot tier (Redis, recent ~7 days): sub-ms reads
  - [ ] Cold tier (S3 Standard/IA, older): 50-200ms reads, acceptable for low traffic
  - [ ] Cost: hot $40/mo + cold $7/mo = $47 vs all-Redis $400/mo
  - [ ] Right-size: at 2TB total, even all-SSD Postgres is cheap; don't over-engineer tiers
- [ ] Walk through the main flow end-to-end:
  - [ ] Create: user submits paste -> Paste Service generates ID -> store body in S3 -> store metadata in Postgres -> cache in Redis -> return short URL
  - [ ] Read: client requests paste -> CDN check -> cache miss to Redis (hot tier) -> miss to Postgres metadata -> fetch body from appropriate tier -> return content
  - [ ] Expire: read path checks `expires_at` (soft delete); async job physically reclaims storage nightly

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss caching strategy (4 read layers):
  - [ ] Layer 1: CDN edge — long TTL (24h+), pastes are immutable
  - [ ] Layer 2: Application cache (Redis) — behind CDN misses
  - [ ] Layer 3: DB read replicas — handle cache-miss load
  - [ ] Layer 4: Hot storage tier — recent pastes served from Redis directly
- [ ] Explain expiration and cleanup pipeline:
  - [ ] Soft delete: read path checks `expires_at`, returns 404 if expired
  - [ ] Physical cleanup: async nightly job deletes expired pastes after grace period
  - [ ] S3 lifecycle policies for cold-tier cleanup
  - [ ] "Never expire" pastes: tier to cheapest storage over time
- [ ] Address failure modes:
  - [ ] ID collision: collision check + retry; math says negligible risk
  - [ ] Cache stampede on viral paste: CDN absorbs; lock-on-miss or probabilistic early refresh
  - [ ] Cold-tier latency spike: monitor per-tier read rates; alert on anomalies
  - [ ] Storage fill from never-expire: lifecycle policies, tier down, monitor growth
  - [ ] Abuse incident: inline detection for known patterns, auto-takedown for high-confidence, human review queue
- [ ] Discuss abuse detection pipeline:
  - [ ] Inline: YARA rules, regex, hash matching (~50ms, blocks at create time)
  - [ ] Async ML: content classifier, entropy analysis (minutes lag, flags for review)
  - [ ] Reputation: IP/account scoring, auto-quarantine from bad-rep sources
  - [ ] User reports: queue for human review; takedown sets `taken_down` flag, returns 410 Gone
- [ ] Right-size the engineering:
  - [ ] Single Postgres + S3 + Redis + CloudFront is correct for 100K pastes/day
  - [ ] Resist adding Kafka, Cassandra, microservices to a small system

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made and why
- [ ] Mention what you would improve with more time
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
