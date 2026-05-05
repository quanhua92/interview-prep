# Design Search Autocomplete

## One-Liner
Provide fast, relevant query suggestions as users type, ranked by popularity and personalization.

## Functional Requirements
- Return top-K suggestions for a given prefix
- Support ranking by query frequency and recency
- Personalize suggestions based on user history
- Handle typo tolerance (fuzzy matching)
- Support multiple languages

## Non-Functional Requirements
- Latency under 50ms for top-5 results
- Handle millions of queries per day
- Update suggestions in near-real-time (minutes, not hours)
- Low memory footprint per prefix

## Key Scale Questions
- Millions of queries/day, 10M unique query strings
- Top-5 results per keystroke
- Average query length: 3-5 characters
- Update frequency: trending queries shift hourly

## Core Components
- **Suggestion Service**: processes prefix queries, returns ranked suggestions
- **Trie Store**: in-memory trie for prefix search (per data center)
- **Aggregation Pipeline**: offline job to build/update trie from query logs
- **Personalization Service**: merges global + user-specific suggestions
- **Cache Layer**: Redis for top-K results per popular prefix
- **Analytics Pipeline**: real-time query log ingestion for trend detection

## Key Design Decisions

### Data Structure for Prefix Search
- **Option A: Trie**: Natural prefix matching, memory-heavy for large datasets, O(L) lookup where L = prefix length
- **Option B: Inverted index with prefix matching**: Use existing search infra (Elasticsearch), flexible ranking, slightly higher latency
- **Option C: Finite State Transducer (FST)**: Compressed trie, shared suffixes save memory, used by Lucene, harder to update dynamically

### Ranking Strategy
- **Option A: Frequency only**: Simple, but misses trending and recency signals
- **Option B: Frequency x Recency decay**: Weight recent queries higher, good for trending detection
- **Option C: Personalized ranking**: Combine global popularity with user's search history, best UX, more complex

### Update Strategy
- **Option A: Offline rebuild (batch)**: Daily/hourly batch job rebuilds trie. Simple, stale data between updates
- **Option B: Online update (real-time)**: Incremental trie updates on each query. Fresh data, complex concurrency control
- **Option C: Hybrid**: Batch for base trie + real-time cache overlay for trending queries. Good balance

## API Endpoints
| Method | Path | Description |
|--------|------|-------------|
| GET | /api/suggest?q={prefix}&limit=5 | Get autocomplete suggestions |
| GET | /api/suggest/trending | Get globally trending queries |

## Database Schema
| Column | Type | Notes |
|--------|------|-------|
| query_text | VARCHAR | The search query string |
| frequency | BIGINT | Global occurrence count |
| last_seen_at | TIMESTAMP | Most recent query time |
| category | VARCHAR | Optional category tag |

## Deep Dive Topics
- Trie node structure: each node stores children map + top-K suggestions at that prefix
- FST (Finite State Transducer) compression: how Lucene implements memory-efficient autocomplete
- Handling typo tolerance: edit distance (Levenshtein) at query time vs pre-computed phonetic index
- Edge n-gram approach in Elasticsearch for prefix search

## Follow-Up Variations
- How would you add real-time trending suggestions (e.g., sudden spike in "World Cup")?
- How would you handle autocomplete for a commerce site (products, not queries)?
- What if you need to support multi-word phrase suggestions, not just prefixes?
- How would you implement "did you mean" functionality alongside autocomplete?
