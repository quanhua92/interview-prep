# Design a CDN

Source: [CDN (CalibreOS)](https://www.calibreos.com/learn/hld-cdn)

## One-Liner
A globally-distributed read-through cache with DNS-based routing that cuts latency to tens of milliseconds, offloads 80-99% of origin bandwidth, and shields origins from bursty traffic.

## Functional Requirements
- Serve static assets (JS, CSS, images, video) from edge POPs closest to users
- Cache dynamic but cacheable content (product pages, search results) with short TTLs
- Invalidate cached content via TTL expiry, explicit purge, or versioned URLs
- Handle both push (pre-staged) and pull (on-demand) content distribution
- Support edge compute for auth, A/B routing, and request transformation at the edge

## Non-Functional Requirements
- Sub-50ms TTFB from edge POPs (vs 200-300ms from a distant origin)
- Cache hit rate >90% for static assets, >75% for HTML, >50% for API responses
- Origin offload ratio >95% (origin serves <5% of total traffic)
- Purge propagation <5s to 99% of POPs
- Survive POP outages via automatic traffic rerouting

## Key Scale Questions
- 300+ edge POPs globally, each serving millions of requests/sec
- At 1M QPS with 99% cumulative hit rate, origin sees ~10K QPS
- A viral URL without origin shield: 300 simultaneous misses from 300 POPs = thundering herd
- 10 PB/month video delivery: ~$500K/month savings on egress alone ($0.09/GB origin vs $0.02-0.04/GB CDN)
- Cache key cardinality: including cookies fragments cache from 95% hit rate to near 0%

## Core Components
- **Edge POP**: closest cache to user (~10ms), handles ~80% of requests, RAM + SSD
- **Regional Cache**: one per continent (~30ms), aggregates edge misses, brings cumulative hit rate to ~95%
- **Origin Shield**: single-region last defense (~80ms), request coalescing ensures origin sees 1 request per unique URL during bursts
- **Origin**: actual server/database, sees ~1% of user traffic in a well-tuned hierarchy
- **GeoDNS / Anycast Router**: routes user to nearest POP (Anycast preferred for automatic failover)
- **Edge Compute (Workers/Lambda@Edge)**: runs custom logic at POP for auth, ESI, A/B testing

## Key Design Decisions

### Push vs Pull CDN
- **Pull CDN**: caches lazily on first request. Default for web assets, images, API responses. Zero pre-provisioning, but first user per POP pays origin latency
- **Push CDN**: content explicitly uploaded and replicated to edges before demand. Best for large predictable files (video, game patches). No origin fetch ever, but higher storage cost
- **Hybrid**: push top 1% hot objects, pull the long tail. Netflix uses push (20GB 4K movies); Instagram uses pull (billions of images)

### Cache Invalidation Strategy
- **TTL expiry**: simple, free, but content stale for up to TTL. Use for staleness-tolerant content
- **Explicit purge**: CDN API call broadcasts invalidation to all POPs (~200ms on Fastly, ~30-60s on CloudFront). Use for low-frequency, high-urgency updates
- **Versioned URLs**: content hash in filename (/app.a3f7c9.js), 1-year immutable TTL. Invalidation is free because new URL has no cached copies. Production default for build-pipeline assets

### Cache Key Design
- Default key is (method, host, path). Adding cookies, query strings, or Vary headers fragments the cache
- Strip cookies on /static/* paths. Normalize query strings (whitelist only params that change response). Vary only on Accept-Encoding (2 variants), never User-Agent
- Include in cache key only what determines the response content

## API Endpoints
| Method | Path | Description |
|--------|------|-------------|
| GET | /static/* | Cached at edge with 1-year TTL (versioned URLs) |
| GET | /api/public/* | Cached at CDN for 5 min (s-maxage), browser 30s |
| GET | /api/me/* | Private, no-cache, must-revalidate |
| GET | /api/auth/* | No-store, never cached anywhere |
| PURGE | /path/to/resource | Explicit invalidation of cached content |

## Database Schema
| Column | Type | Notes |
|--------|------|-------|
| cache_key | STRING | Composite of (method, host, path), optionally normalized query params |
| content_hash | STRING | ETag / content hash for conditional requests (If-None-Match) |
| ttl | INT | Remaining seconds before eviction |
| vary_headers | STRING | Normalized variants (e.g., Accept-Encoding: gzip, br) |
| origin_url | STRING | Origin fetch URL for cache misses |
| last_fetched | TIMESTAMP | When content was last pulled from origin |
| hit_count | BIGINT | Request count since last population (for eviction priority) |

## Deep Dive Topics
- **Origin Shield and request coalescing**: when 1000 edge POPs all miss on the same URL simultaneously, shield sends exactly 1 request to origin and fans out the response. Cumulative hit rate reaches ~99%
- **Edge Side Includes (ESI)**: cache the HTML shell, inject personalized fragments at edge. Used for mixed cacheable + personalized pages
- **Edge compute trade-offs**: Cloudflare Workers (<1ms cold start, V8 isolates), Lambda@Edge (100-500ms cold start, AWS ecosystem), Fastly Compute (~50us cold start, WASM). Avoid for DB-heavy or heavy compute workloads
- **Failure modes**: cache stampede on TTL expiry (defend with request coalescing + probabilistic early refresh), cache poisoning via Host header injection, cookie leak into cached responses, origin meltdown from mass invalidation
- **Cache-Control recipes**: `max-age=31536000, immutable` for versioned assets; `max-age=60, stale-while-revalidate=600` for HTML; `s-maxage=300` for CDN-layer-only caching

## Follow-Up Variations
- How would you CDN a personalized dashboard where each user sees different data?
- Your CDN hit rate dropped from 95% to 70% after a deploy. What is your debug process?
- How do you handle video streaming at petabyte scale without bankrupting on egress?
- What happens when a POP goes down? How does traffic reroute?
- How would you implement geographic content restrictions (geo-fencing) at the edge?
