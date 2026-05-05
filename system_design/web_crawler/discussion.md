# Design a Web Crawler

## One-Liner
Scalable system to discover, fetch, and store web pages while respecting politeness policies and handling duplicates.

## Functional Requirements
- Discover and fetch web pages from seed URLs
- Respect robots.txt and crawl rate limits (politeness)
- Deduplicate URLs and content
- Parse and extract links for further crawling
- Store raw content and metadata for indexing

## Non-Functional Requirements
- Scale to billions of pages
- Polite crawling (respect per-domain rate limits)
- Fault tolerant (handle bad URLs, slow servers, network errors)
- Distributed execution across multiple machines

## Key Scale Questions
- Billions of pages, average 50KB per page = ~50TB of content
- Crawl rate: millions of pages/day
- URL frontier: billions of URLs to process
- Link graph: average 50 outbound links per page
- Freshness: re-crawl popular pages frequently (news sites daily, static pages monthly)

## Core Components
- **URL Frontier**: prioritized queue of URLs to crawl (Kafka + custom priority queue)
- **Crawler Workers**: fetch pages, parse HTML, extract links
- **URL Deduplication Service**: Bloom filter + checksum for seen URLs
- **Politeness Manager**: per-domain rate limiting, robots.txt parsing and caching
- **Content Store**: distributed storage for raw HTML (S3 or HDFS)
- **Link Extractor & Canonicalizer**: parse HTML, normalize URLs, handle relative paths
- **Indexing Pipeline**: downstream consumers that build search index from crawled content

## Key Design Decisions

### URL Frontier Design
- **Option A: Single priority queue**: Simple, but bottleneck at scale, no domain awareness
- **Option B: Per-domain queues with a scheduler**: Polite per-domain, priority across domains, more complex
- **Option C: Distributed priority queue (Kafka with partitions)**: Scalable, partition by domain hash for politeness

### URL Deduplication
- **Option A: Full URL set in database**: Exact dedup, but billions of URLs = massive storage
- **Option B: Bloom filter**: Memory-efficient, probabilistic (small false positive rate acceptable), needs periodic rebuild
- **Option C: SHA-256 checksum + Bloom filter**: Dedup by URL hash, also handle canonical URLs to avoid www/non-www duplicates

### Traversal Strategy
- **Option A: BFS (breadth-first)**: Good for breadth of coverage, needs large URL frontier, tends to crawl shallow
- **Option B: DFS (depth-first)**: Good for deep site crawling, risks getting stuck in deep sites, needs depth limit
- **Option C: Priority-based**: Combine PageRank estimation, freshness, and user-defined priority

## API Endpoints
| Method | Path | Description |
|--------|------|-------------|
| POST | /api/crawl/seed | Add seed URLs to frontier |
| GET | /api/crawl/status | Check crawl progress and stats |
| POST | /api/crawl/pause | Pause/resume crawling for a domain |
| GET | /api/crawl/page/{url_hash} | Retrieve stored page content |

## Database Schema
| Column | Type | Notes |
|--------|------|-------|
| url_hash | VARCHAR | SHA-256 of canonical URL, PK |
| raw_url | TEXT | Original URL |
| status | VARCHAR | pending, fetched, failed |
| fetch_time | TIMESTAMP | When page was fetched |
| content_hash | VARCHAR | SHA-256 of page content |
| crawl_depth | INT | BFS depth from seed |

## Deep Dive Topics
- Robots.txt parsing: per-domain caching, wildcard rule matching, crawl-delay directive
- URL canonicalization: handling scheme (http/https), www prefix, trailing slashes, query parameter sorting
- MapReduce-based crawling: worker fetches pages, emits (url, content), reducer stores and extracts links
- Handling JavaScript-rendered pages: headless browser crawling vs static HTML

## Follow-Up Variations
- How would you handle incremental crawling (re-crawling updated pages)?
- How do you detect and handle crawler traps (infinite URL spaces)?
- What about crawling sites that require authentication?
- How would you prioritize which pages to re-crawl for freshness?
