# URL Shortener — FastAPI Implementation

A full URL shortener service built with FastAPI, implementing the core requirements and all five follow-ups from the interview problem.

## Quick Start

```bash
cd ai_assisted/url_shortener/solutions/python
uv sync
uv run pytest tests/ -v
```

To run the server:

```bash
uv run uvicorn app.main:app --reload
```

## Project Structure

```
app/
├── main.py        # FastAPI routes and app setup
├── models.py      # Pydantic request/response schemas
├── base62.py      # Base62 encoding/decoding
├── storage.py     # In-memory URL storage (auto-increment)
├── storage_hash.py # In-memory URL storage (hash-based, Follow-up 6)
├── cache.py       # LRU cache with TTL
├── analytics.py   # Click tracking with buffered writes
└── service.py     # Business logic orchestrator
tests/
├── conftest.py    # Shared async client fixture
├── test_api.py    # HTTP integration tests
├── test_base62.py # Encoding unit tests
├── test_cache.py  # LRU cache unit tests
├── test_analytics.py  # Analytics unit tests
└── test_service.py    # Service layer unit tests
├── test_storage_hash.py # Hash-based storage tests (Follow-up 6)
```

## API Endpoints

| Method | Path | Description |
|--------|------|-------------|
| `POST` | `/shorten` | Create a short alias for a URL |
| `GET` | `/{alias}` | Redirect to the original URL (302) |
| `GET` | `/info/{alias}` | Resolve alias to URL (JSON) |
| `GET` | `/analytics/{alias}` | Get click count for an alias |
| `GET` | `/analytics/top` | Get top URLs ranked by clicks |

## How the Interview Requirements Are Addressed

### Core Requirements

1. **7-character alias generation** — `base62.py` encodes auto-incrementing IDs using the 62-character set `[a-zA-Z0-9]`, zero-padded to exactly 7 characters. This gives ~3.5 trillion unique aliases.

2. **Redirect** — `GET /{alias}` returns a 302 redirect to the original URL.

3. **Idempotency** — `storage.py` maintains a `url_to_alias` reverse mapping. Submitting the same URL always returns the same alias, enforced at the storage layer.

4. **Custom aliases** — `POST /shorten` accepts an optional `custom_alias` field. Collision detection returns a 409 error.

### Follow-Up 1: Caching Hot URLs

Implemented in `cache.py` as an `LRUCache` using `collections.OrderedDict`:

- **LRU eviction**: When the cache reaches capacity (default 10,000 entries), the least recently used entry is evicted.
- **TTL support**: Entries expire after a configurable number of seconds (default 300s). Expired entries are evicted lazily on access.
- **Integration**: `service.py` checks the cache before storage on every resolve. Cache misses populate the cache. Cache hits skip storage entirely.
- **Thundering herd mitigation**: The cache is populated immediately after URL creation (cache warming). In production, you'd add request coalescing or a bloom filter.

### Follow-Up 2: Database Selection

This implementation uses in-memory dicts (see `storage.py`), which map to the following production considerations:

- **PostgreSQL** would suit this workload well: strong consistency for the `url_to_alias` idempotency check, B-tree indexes on both `alias` and `long_url`, and straightforward vertical scaling. Read replicas handle the 10:1 read-to-write ratio.
- **DynamoDB** would also work: the alias as partition key gives O(1) lookups, and eventual consistency on the reverse mapping (`url_to_alias`) is acceptable since idempotency is a convenience, not a correctness requirement. DynamoDB auto-scales for the read-heavy pattern.
- **Sharding**: With 3.5 trillion possible aliases, a hash-based sharding strategy on the alias itself distributes load evenly. Range-based sharding on the auto-increment ID avoids hotspots during creation.

### Follow-Up 3: Analytics / Click Tracking

Implemented in `analytics.py` with a fire-and-forget buffered write pattern:

- **Buffered writes**: Clicks are appended to a `deque` buffer (fire-and-forget). The buffer is flushed to a `Counter` periodically, simulating an async write-behind pattern that keeps the redirect path fast.
- **No blocking on redirect**: `record_click()` only appends to a buffer — it never blocks the resolve path. This avoids slowing down the redirect with analytics writes.
- **Top URLs**: `get_top(n)` uses `Counter.most_common()` for efficient ranking.
- **Production extension**: In production, clicks would be written to a message queue (Kafka/Kinesis), consumed by a stream processor, and stored in an OLAP database (ClickHouse/Redshift) for dashboard queries.

### Follow-Up 4: Collision Handling

The auto-increment ID approach in `storage.py` makes collisions impossible by design:

- Each URL gets a unique monotonically increasing integer ID, which is then Base62-encoded. No two URLs can produce the same alias.
- For custom aliases, collision detection is explicit: `store_custom()` checks for existing aliases and raises `ValueError` on conflict.
- **Birthday problem**: With 7-character Base62 aliases (62^7 ≈ 3.5 trillion), even at 1 billion URLs the collision probability with random generation would be ~14%. The auto-increment approach eliminates this risk entirely.
- **Pre-generation vs. on-the-fly**: This implementation generates on-the-fly. Pre-generating a pool of aliases (e.g., via a key-derivation service) would reduce write latency in a distributed setup but adds operational complexity.

### Follow-Up 5: TOCTOU Race Conditions

The original implementation had a classic Time-of-Check-to-Time-of-Use vulnerability: `store_custom()` checked `if alias in alias_to_url` and then inserted in two separate steps. Under concurrent requests, two threads could both pass the check and one would silently overwrite the other. The same gap existed in `store()` for the idempotency check, and in `_next_id()` for the counter increment.

**Fix**: No locks needed. FastAPI runs `async def` handlers on a single-threaded event loop. Dict operations complete synchronously without any `await` yield point, so the event loop cannot interleave two request handlers mid-check-and-insert. The entire check-then-insert sequence is effectively atomic. This is different from Rust's Tokio, where multiple OS threads share memory and `Arc<Mutex<T>>` is required — Python's asyncio has no such parallelism within a single process.

**When you would need locks**:
- **Sync handlers** (`def` instead of `async def`): FastAPI offloads these to a thread pool, where multiple threads share state and `threading.Lock` is necessary.
- **Multi-worker** (`uvicorn --workers N`): Separate processes don't share memory at all. Use database-level atomicity (`INSERT ... ON CONFLICT` with a `UNIQUE` constraint) or distributed locking (Redis `SETNX`).
- **Await inside critical section**: If you `await` a database call between check and insert, the event loop can switch to another coroutine. Use `asyncio.Lock` in that case.

### Follow-Up 6: Auto-Increment vs. Hash-Based Aliases

Implemented in `storage_hash.py` as an alternative `HashURLStorage` backend. The service is storage-agnostic — swap backends via `URLShortenerService(storage=HashURLStorage())`.

**How it works**: `SHA-256(long_url)` → take first 8 bytes as integer → mod 62^7 → Base62 encode. If two different URLs produce the same hash, retry with a deterministic salt (`SHA-256(long_url + "1")`, etc.).

**Comparison**:

| | Auto-Increment (`storage.py`) | Hash-Based (`storage_hash.py`) |
|---|---|---|
| Idempotency | Requires `url_to_alias` dict + lock | **Free** — same URL always hashes to same alias |
| Dicts needed | 2 (`alias_to_url` + `url_to_alias`) | **1** (`alias_to_url` only) |
| Collisions | Impossible by design | Possible (birthday problem) — handled by salt-based retry |
| TOCTOU complexity | No lock needed (single-threaded event loop) | No lock needed — idempotency is implicit |
| Predictability | Sequential (`0000001`, `0000002`...) | Unpredictable |
| Distributed | Needs centralized counter or Snowflake ID | **Stateless** — any node can generate aliases independently |

**When hash is better**: Distributed systems where nodes can't coordinate a counter. Hash-based aliases are generated purely from the URL — no shared state required. The `url_to_alias` dict and its TOCTOU concerns vanish entirely.

**When auto-increment is better**: Single-instance systems where zero collisions matter more than the extra dict. Simpler mental model — no collision retry logic, no hashing, just a counter.

**The key insight**: The hash approach eliminates the entire class of TOCTOU bugs around idempotency because there's no reverse mapping to protect. The insert path is equally safe on a single-threaded event loop — no interleaving is possible without an `await` yield point.

## Test Coverage

51 tests covering:

- **Base62**: encode/decode roundtrip, zero-padding, 7-char invariant
- **LRU Cache**: get/put, eviction, TTL expiration, update existing keys
- **Analytics**: click recording, buffer flush, top-N ranking
- **Service**: full shorten→resolve flow, cache hit/miss, idempotency, custom aliases
- **TOCTOU**: documented as a real concern in multi-threaded languages (Rust, Go, Java); not applicable here due to Python's single-threaded event loop
- **Hash-based storage**: idempotency, collision handling, custom aliases, concurrency, service integration
- **API**: all HTTP endpoints, status codes (200/302/404/409/422), redirect behavior
