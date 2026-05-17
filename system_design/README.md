# System Design

Topic-based practice for system design interviews. Each topic has:

- **discussion.md** — Concise reference (key concepts, trade-offs, vocabulary). Read once, then rely on the checklist.
- **checklist.md** — Step-by-step working checklist. Use this every time you practice.

## Topics

| Topic | Core Concepts |
|-------|--------------|
| [URL Shortener](url_shortener/) | ID generation, caching, base62, sharding |
| [Chat System](chat_system/) | WebSockets, message queues, presence |
| [Rate Limiter](rate_limiter/) | Token bucket, sliding window, Redis |
| [News Feed](news_feed/) | Fan-out on write/read, graph, ranking |
| [Notification Service](notification_service/) | Push/pull, reliability, dedup, priority |
| [Search Autocomplete](search_autocomplete/) | Trie, ranking, prefix search at scale |
| [Distributed Cache](distributed_cache/) | Consistent hashing, replication, eviction |
| [Key-Value Store](key_value_store/) | SSTables, LSM trees, Bloom filters |
| [Web Crawler](web_crawler/) | URL frontier, politeness, dedup, BFS |
| [Ticket Booking](ticket_booking/) | Concurrency, locks, idempotency, oversell |
| [Recommender System](recommender_system/) | Two-tower retrieval, multi-stage ranking, ANN, re-ranking |

## How to Practice

1. Read the **discussion.md** once to learn the vocabulary and key decisions
2. Pick a topic and open its **checklist.md**
3. Walk through each phase verbally, checking items as you cover them
4. Aim to cover all items without referring to discussion.md
5. Use the practice notes at the bottom to track improvement
