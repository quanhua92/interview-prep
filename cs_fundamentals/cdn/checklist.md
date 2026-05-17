# Design a CDN — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] What is the content mix: static assets, dynamic but cacheable, or personalized?
  - [ ] What is the invalidation latency requirement: seconds, minutes, or never-stale acceptable?
  - [ ] What is the traffic pattern: predictable large files or long-tail small objects?
  - [ ] What are the geographic hotspots: global uniform, regional concentration, or ISP-level?
  - [ ] What is the budget for cache misses (origin egress + compute cost)?
- [ ] List functional requirements (3-5 items):
  - [ ] Serve static assets from edge POPs closest to users
  - [ ] Cache dynamic content with short TTLs
  - [ ] Invalidate content via TTL, purge, or versioned URLs
  - [ ] Support push and pull distribution models
  - [ ] Support edge compute for auth and request transformation
- [ ] List non-functional requirements (latency, availability, scale):
  - [ ] Sub-50ms TTFB from edge
  - [ ] Cache hit rate >90% for static, >75% for HTML
  - [ ] Origin offload ratio >95%
  - [ ] Purge propagation <5s to 99% of POPs
  - [ ] Automatic failover on POP outage
- [ ] State your scale estimates:
  - [ ] 300+ edge POPs globally
  - [ ] 1M QPS total, origin sees ~10K QPS at 99% hit rate
  - [ ] 10 PB/month delivery = ~$500K/month egress savings
  - [ ] Without origin shield: 300 simultaneous misses per viral URL

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw the cache hierarchy: Client -> DNS -> Edge POP -> Regional Cache -> Origin Shield -> Origin
- [ ] Identify the main data flows:
  - [ ] Cache hit: Client -> DNS -> Edge POP (served from cache, ~10ms)
  - [ ] Cache miss: Edge POP -> Regional Cache -> Origin Shield -> Origin (request coalescing at each tier)
  - [ ] Push flow: Origin/Upload -> CDN Storage -> Edge POPs (pre-staged before demand)
- [ ] Note the push vs pull trade-off:
  - [ ] Pull CDN: default for web assets, caches on first request, zero pre-provisioning
  - [ ] Push CDN: best for large predictable files, no origin fetch, higher storage cost
  - [ ] Hybrid: push top 1% hot objects, pull the long tail
- [ ] Present the diagram and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain the three-tier cache hierarchy:
  - [ ] Edge POP (~10ms): small fast cache, ~80% hit rate
  - [ ] Regional cache (~30ms): aggregates edge misses, ~95% cumulative hit rate
  - [ ] Origin shield (~80ms): request coalescing, ~99% cumulative hit rate, single request to origin per unique URL
- [ ] Define cache invalidation strategy per content type:
  - [ ] Static assets (JS/CSS/images): versioned URLs with 1-year TTL, zero-cost invalidation
  - [ ] HTML pages: short TTL (60s) + stale-while-revalidate, or explicit purge on publish
  - [ ] API responses: s-maxage for CDN-layer caching, no-store for user-specific data
- [ ] Explain cache key design and what breaks hit rate:
  - [ ] Default key: (method, host, path)
  - [ ] Strip cookies on static paths, normalize query strings, avoid Vary: User-Agent
  - [ ] Including session cookies in cache key fragments hit rate to near 0%
- [ ] Walk through the main flows end-to-end:
  - [ ] Pull request flow: DNS resolution -> route to nearest POP -> cache hit/miss -> fetch from next tier or origin -> cache and serve
  - [ ] Push distribution: upload to CDN storage -> replicate to edge POPs -> serve without origin
  - [ ] Invalidation flow: purge API -> broadcast to all POPs -> replace with versioned URL pattern for zero-cost invalidation

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss edge compute options and trade-offs:
  - [ ] Cloudflare Workers: <1ms cold start, V8 isolates, 300+ POPs
  - [ ] Lambda@Edge: 100-500ms cold start, AWS ecosystem integration
  - [ ] Fastly Compute: ~50us cold start, WASM-based, highest raw perf
  - [ ] Use cases: auth at edge, A/B routing, ESI, geographic compliance
- [ ] Explain personalization behind a CDN:
  - [ ] Pattern 1: split page (cacheable shell + private API calls from browser)
  - [ ] Pattern 2: Edge Side Includes (ESI) for server-side fragment assembly
  - [ ] Pattern 3: edge compute for custom assembly logic
- [ ] Address failure modes and defenses:
  - [ ] Cache stampede: request coalescing + probabilistic early refresh
  - [ ] Cache poisoning: validate Host header at edge, never reflect into response
  - [ ] Cookie leak into cache: strict rule that Set-Cookie responses are private
  - [ ] Origin meltdown from mass invalidation: origin shield + gradual rollout + rate limiting
  - [ ] POP outage: Anycast auto-reroutes in seconds, GeoDNS fallback
- [ ] Discuss CDN provider selection:
  - [ ] Cloudflare: 300+ POPs, Anycast, best DDoS mitigation, generous free tier
  - [ ] Fastly: ~80 POPs, fastest purge (~150ms), VCL config, Reddit/Shopify/NYT
  - [ ] CloudFront: AWS integration, large footprint, historically slower purges
  - [ ] Netflix Open Connect: custom hardware at ISPs, push model, 95%+ served from inside ISP
  - [ ] Akamai: original CDN, enterprise-heavy, expensive

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made and why
- [ ] Mention what you would improve with more time
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
