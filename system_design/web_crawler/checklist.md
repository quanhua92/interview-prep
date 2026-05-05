# Design a Web Crawler — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] What is the crawl scope: a single domain (site-specific) or the entire web (like Googlebot)?
  - [ ] How fresh does the data need to be? How often should already-crawled pages be re-crawled?
  - [ ] What content types should we handle: HTML only, or also PDFs, images, videos, APIs?
- [ ] List functional requirements (3-5 items):
  - [ ] Discover and fetch web pages starting from seed URLs
  - [ ] Parse pages and extract links for further crawling
  - [ ] Store page content and metadata (title, headers, timestamp)
  - [ ] Avoid re-crawling the same URL (deduplication)
  - [ ] Respect robots.txt and rate limit requests per domain (politeness)
- [ ] List non-functional requirements (latency, availability, scale):
  - [ ] Scalability: crawl billions of pages across millions of domains
  - [ ] Fault tolerance: tolerate worker failures, network errors, and malicious pages
  - [ ] Politeness: configurable crawl delay per domain, respect robots.txt
  - [ ] Freshness: re-crawl important pages frequently, less important pages less often
  - [ ] Extensibility: support custom parsers and extractors for different content types
- [ ] State your scale estimates (users, requests, storage):
  - [ ] ~10B pages to crawl, ~100M new/updated pages per day
  - [ ] ~50K fetches/sec at peak
  - [ ] ~1M domains to track politeness rules for
  - [ ] Storage: ~1PB for raw page content + metadata

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw a simple box diagram: Seed URLs -> [URL Frontier (Queue)] -> [Crawler Workers] -> [Downloader] -> [Parser] -> [Storage + Index] -> [New URLs -> URL Frontier]
- [ ] Identify the main operations and their access patterns:
  - [ ] URL scheduling: prioritize and assign URLs to workers
  - [ ] Page fetching: HTTP GET with proper headers, cookies, and error handling
  - [ ] Parsing: extract links, metadata, and structured content
  - [ ] Storage: save raw HTML, extracted content, and URL metadata
  - [ ] Deduplication: check if URL or page content has been seen before
- [ ] Note the read:write ratio and where caching helps:
  - [ ] Write-heavy: each crawl generates new content, metadata, and discovered URLs
  - [ ] Reads: occasional re-fetch of previously crawled pages
  - [ ] Cache DNS resolutions and robots.txt files to avoid redundant requests
- [ ] Present the diagram and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain URL frontier design:
  - [ ] Priority queues: URLs prioritized by importance (PageRank, crawl frequency, user priority)
  - [ ] Per-domain queues: maintain separate queues per domain to enforce politeness (crawl delay)
  - [ ] Backend storage: Kafka or distributed queue with priority support
  - [ ] Front-end: scheduler selects the next URL to crawl based on priority and politeness
- [ ] Define API/internal interfaces:
  - [ ] Internal: `Scheduler.next_url()` -> returns next URL to crawl
  - [ ] Internal: `Downloader.fetch(url)` -> returns `HTTP response (status, headers, body)`
  - [ ] Internal: `Parser.extract(html)` -> returns `{links: [...], metadata: {...}, content: "..."}`
  - [ ] Internal: `DedupChecker.is_seen(url, content_hash)` -> boolean
  - [ ] Internal: `Storage.save(url, content, metadata)` -> success/failure
- [ ] Sketch the data model:
  - [ ] Table `urls`: `url (PK)`, `status (pending/crawling/done/failed)`, `last_crawled_at`, `crawl_count`, `priority`, `domain`
  - [ ] Table `pages`: `url`, `raw_html`, `content_hash`, `title`, `headers`, `fetched_at`
  - [ ] Table `robots_rules`: `domain`, `rules (JSON)`, `fetched_at`
  - [ ] Table `domain_politeness`: `domain`, `crawl_delay_ms`, `last_access_time`, `concurrent_requests`
- [ ] Discuss SQL vs NoSQL trade-off:
  - [ ] URL metadata: NoSQL (Cassandra) partitioned by domain, high write throughput
  - [ ] Page content: object store (S3) or blob store (raw HTML can be large)
  - [ ] Robots.txt cache: Redis with TTL per domain
- [ ] Walk through the main crawl flow end-to-end:
  - [ ] Scheduler picks next URL from frontier -> Downloader fetches the page (check robots.txt first) -> Parser extracts links and content -> DedupChecker checks if URL/content is new -> if new, store content and add discovered links to frontier -> update URL status to done -> repeat

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss politeness implementation:
  - [ ] Per-domain crawl delay: enforce minimum time between requests to same domain
  - [ ] robots.txt parsing: fetch and cache, respect Disallow and Crawl-delay directives
  - [ ] Concurrent connection limit per domain (e.g., max 2 simultaneous connections)
  - [ ] DNS lookup caching to avoid hammering DNS servers
- [ ] Explain deduplication approach:
  - [ ] URL dedup: canonicalize URLs (lowercase, remove fragments, sort query params), check Bloom filter + database
  - [ ] Content dedup: compute SHA-256 hash of page content, check SimHash for near-duplicate detection
  - [ ] Bloom filter for fast negative checks: if Bloom filter says "not seen," definitely new; if "maybe seen," check database
- [ ] Explain scaling/partitioning approach:
  - [ ] Horizontal scaling: add more crawler workers
  - [ ] Partition URL frontier by domain (all URLs for a domain go to the same worker for politeness)
  - [ ] Partition storage by URL hash for even distribution
  - [ ] Use message queue (Kafka) for the URL frontier with topic partitioning
- [ ] Address fault tolerance:
  - [ ] Worker failure: URLs being processed return to the queue (at-least-once delivery)
  - [ ] Retry transient HTTP errors (429, 503) with exponential backoff
  - [ ] Mark permanently failed URLs (repeated 404, timeout) as failed after N retries
  - [ ] Checkpoint crawl progress periodically for recovery
- [ ] Handle priority management:
  - [ ] Priority signals: PageRank score, page change frequency, user-submitted priority, manual boost
  - [ ] Freshness priority: pages that change often get higher priority for re-crawl
  - [ ] Multi-level queues: high/medium/low priority queues, scheduler always picks from highest available
- [ ] Discuss monitoring and observability:
  - [ ] Crawl rate (pages/sec) and queue depth
  - [ ] HTTP error rate by status code and domain
  - [ ] Duplicate detection rate (new vs. already-seen)
  - [ ] Politeness compliance (actual delay vs. configured delay per domain)
  - [ ] Worker health and task completion rate

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made and why
- [ ] Mention what you would improve with more time
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
