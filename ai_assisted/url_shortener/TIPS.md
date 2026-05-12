# Tips: URL Shortener

## Key Concepts to Know

- **Base62 encoding** — Convert a unique integer ID to a string using `[a-zA-Z0-9]`. This is the standard approach for generating short aliases.
- **Hashing vs. encoding** — MD5/SHA hashes are longer and require truncation (collision risk). Counter-based Base62 encoding is deterministic and collision-free.
- **Idempotency** — Store a `hash(long_url) → alias` mapping to return the same alias for repeated submissions.

## Common Mistakes

| Mistake | Why It's Wrong |
|---------|---------------|
| Using UUIDs for aliases | Too long, not URL-friendly |
| Truncating MD5 to 7 chars without collision handling | Birthday problem: ~5% collision at 1B URLs |
| Storing only `alias → long_url` | Can't enforce idempotency without a reverse lookup |
| Ignoring custom alias collisions | Must check if a user-provided alias already exists |
| Doing analytics writes synchronously on redirect | Adds latency to the critical read path |

## How to Prompt the AI Effectively

1. **Start with data models:** "Define the database schema for a URL shortener with fields for alias, long_url, created_at, and click_count."
2. **Ask for the encoding algorithm separately:** "Implement Base62 encoding that converts an integer to a 7-character string using [a-zA-Z0-9]."
3. **Don't ask for everything at once:** "Now add a caching layer using an in-memory LRU cache with 10K capacity."
4. **Verify output:** Check that the AI's Base62 implementation handles `id=0` correctly and produces exactly 7 characters.

## Architecture Patterns

```
Client → CDN (optional) → Load Balancer → API Server
                                          ├── Cache (Redis/Memcached)
                                          └── Database (PostgreSQL/DynamoDB)
```

- **Read path:** Check cache → cache miss → query DB → update cache → return URL.
- **Write path:** Check idempotency → generate alias → write to DB → invalidate cache if needed.

## What Interviewers Look For

- Understanding of Base62 encoding and why it's preferred over hashing.
- Awareness of the read-heavy access pattern and how it shapes design decisions.
- Ability to reason about collision probability (birthday problem).
- Practical caching strategy with eviction and invalidation.
- Clean separation between the redirect path (fast) and analytics (async).
