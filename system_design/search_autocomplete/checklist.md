# Design a Search Autocomplete System — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] Should suggestions be real-time (as-you-type) or pre-computed and cached?
  - [ ] Are suggestions personalized (based on user history) or global (based on overall popularity)?
  - [ ] How many suggestions should we return per query, and what is the expected typing speed?
- [ ] List functional requirements (3-5 items):
  - [ ] Return top-K relevant suggestions as the user types each character
  - [ ] Support prefix matching (typing "ap" shows "apple", "application", "api")
  - [ ] Rank suggestions by popularity, relevance, or personal history
  - [ ] Update suggestion rankings as search trends change
  - [ ] Optionally support typo correction and fuzzy matching
- [ ] List non-functional requirements (latency, availability, scale):
  - [ ] Ultra-low latency: suggestions returned in <50ms per keystroke
  - [ ] High availability: 99.9% uptime
  - [ ] Scalability: handle millions of queries per second globally
  - [ ] Freshness: trending topics reflected within minutes
- [ ] State your scale estimates (users, requests, storage):
  - [ ] ~500M DAU, ~50K autocomplete queries/sec at peak
  - [ ] Query length: average 2-5 characters
  - [ ] Suggestion corpus: ~10M unique terms/phrases
  - [ ] Update frequency: ranking scores updated every few minutes

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw a simple box diagram: Client -> LB -> [Autocomplete Service] -> [Trie / Search Index] -> [Analytics Service]
- [ ] Identify the main operations and their access patterns:
  - [ ] `GET /api/suggest?q=ap&limit=5` — fetch suggestions (read, extremely high QPS)
  - [ ] Background job: update ranking scores from search analytics (write, continuous)
  - [ ] Admin API: add/remove terms from the corpus (write, low QPS)
- [ ] Note the read:write ratio and where caching helps:
  - [ ] Read:Write ratio ~10000:1 (suggestion fetches vs ranking updates)
  - [ ] Cache top suggestions for popular prefixes in Redis
  - [ ] Pre-compute top-K for all prefixes offline and serve from cache
- [ ] Present the diagram and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain data structure choice and justify:
  - [ ] Trie (prefix tree): O(L) lookup where L = prefix length, natural prefix matching
  - [ ] Each trie node stores top-K suggestions with scores
  - [ ] Alternative: Suffix array, n-gram index, or inverted index with Elasticsearch
  - [ ] State your choice: distributed trie with top-K cached at each node
- [ ] Define API endpoints with method, path, request/response:
  - [ ] `GET /api/suggest?q=ap&limit=5&locale=en` -> `{"suggestions": ["apple", "application", "api", "app store", "approach"]}`
  - [ ] `POST /api/suggest/popular` (internal) -> update rankings from analytics
  - [ ] `POST /api/admin/suggest/terms` -> add/update corpus terms
- [ ] Sketch the data structure:
  - [ ] Trie node: `{children: {char -> TrieNode}, suggestions: [{term, score}] (top-K sorted)}`
  - [ ] Term metadata table: `term`, `frequency`, `category`, `last_updated`
  - [ ] User personalization table: `user_id`, `term`, `weight`, `timestamp`
- [ ] Discuss SQL vs NoSQL trade-off:
  - [ ] Term corpus and rankings: NoSQL (Redis for serving, S3/offline store for persistence)
  - [ ] User search history: NoSQL (Cassandra) partitioned by user_id
  - [ ] Analytics data: data warehouse or time-series DB
- [ ] Walk through the main query flow end-to-end:
  - [ ] User types "ap" -> client debounces (e.g., 100ms) -> sends request -> Autocomplete Service checks local cache -> if miss, queries trie -> returns top-5 suggestions -> results cached for prefix "ap"
  - [ ] Background: Analytics service aggregates search logs -> updates term frequency scores -> rebuilds trie periodically

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss caching strategy:
  - [ ] L1: in-memory LRU cache on each service instance (top prefixes)
  - [ ] L2: Redis cluster (full prefix-to-suggestions mapping for hot prefixes)
  - [ ] L3: pre-computed offline data loaded into memory (full trie)
  - [ ] Cache invalidation: periodic refresh from offline-computed rankings
- [ ] Explain scaling/partitioning approach:
  - [ ] Partition trie by first character (26 partitions for English alphabet)
  - [ ] Or partition by prefix hash range
  - [ ] Each service instance holds a portion of the trie in memory
- [ ] Address single points of failure:
  - [ ] Multiple trie instances per partition (replication)
  - [ ] Fall back to Redis cache if trie service is unavailable
  - [ ] Graceful degradation: return cached/stale results during failures
- [ ] Handle data freshness:
  - [ ] Online: lightweight frequency updates via Kafka (real-time but approximate)
  - [ ] Offline: batch rebuild trie from full analytics data every N minutes
  - [ ] Trade-off: fresher data requires more compute; stale data is acceptable for autocomplete
- [ ] Handle typo correction and personalization:
  - [ ] Typo correction: Levenshtein distance on candidates, or BK-tree for fuzzy search
  - [ ] Personalization: blend global popularity score with user-specific weight (e.g., `score = alpha * global_freq + beta * user_freq`)
  - [ ] Country/language personalization: use locale parameter to rank region-specific terms higher
- [ ] Discuss monitoring and observability:
  - [ ] Query latency (p50, p95, p99)
  - [ ] Cache hit ratio
  - [ ] Suggestion click-through rate (quality metric)
  - [ ] Freshness lag (time from new trend to appearance in suggestions)

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made and why
- [ ] Mention what you would improve with more time
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
