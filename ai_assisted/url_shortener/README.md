# Problem 01: URL Shortener (Read-Heavy System)

**Role:** Backend Engineer
**Duration:** 45-60 minutes
**Difficulty:** Medium
**Format:** Feature Build-Out

---

## Background

Our company is building a URL shortening service similar to Bitly. Users submit long URLs and receive short, shareable aliases. The service is heavily read-dominated — URLs are clicked far more often than they are created.

You will be working on the core service. Focus on correctness first, then we'll iterate on scalability.

## Functional Requirements

1. Given a long URL, generate a unique **7-character** alias (e.g., `https://short.url/aB3x9Kp`).
2. Given a short alias, redirect to the original long URL.
3. The same long URL submitted multiple times should return the **same** alias (idempotency).
4. Support custom aliases if the user provides one (e.g., `https://short.url/my-custom-link`).

## Non-Functional Requirements

- Alias generation must be deterministic and collision-free.
- Redirects should be fast (target < 50ms at the application layer).
- The system should handle 100K URL creations/day and 10M reads/day.

## Constraints

- Alias character set: `[a-zA-Z0-9]` (62 characters).
- Alias length: exactly 7 characters (gives ~3.5 trillion unique aliases).
- You may assume a single database instance for the initial implementation.

## Starter Interface

```python
class URLShortener:
    def shorten(self, long_url: str) -> str:
        """Return the short alias for a long URL."""
        ...

    def resolve(self, short_alias: str) -> str | None:
        """Return the original long URL, or None if not found."""
        ...

    def custom_alias(self, long_url: str, alias: str) -> str:
        """Register a user-provided custom alias."""
        ...
```

---

## Follow-Up Questions

Your interviewer will progressively add these constraints during the session.

### Follow-Up 1: Caching Hot URLs
> "Our analytics show that 10% of URLs receive 90% of traffic. How would you implement caching for these 'hot' URLs?"

- Design a cache layer that sits in front of the database.
- Consider cache eviction policy (LRU, LFU, TTL-based).
- What happens on a cache miss? What's the thundering herd problem and how do you mitigate it?

### Follow-Up 2: Database Selection
> "We're deciding between PostgreSQL and DynamoDB for storage. Walk me through the trade-offs."

- Discuss consistency guarantees (strong vs. eventual).
- How does each handle the read-heavy access pattern?
- What about horizontal scaling and sharding the `alias → long_url` mapping?

### Follow-Up 3: Analytics
> "Now we want to track click counts per URL, with a dashboard showing top URLs by region. How does this change the design?"

- Where do you store click events? (OLTP vs. OLAP)
- How do you avoid slowing down the redirect path with analytics writes?
- Consider a fire-and-forget or sidecar pattern for event ingestion.

### Follow-Up 4: Collision Handling
> "What happens if two different long URLs generate the same alias? How do you handle this at scale?"

- Discuss retry strategies with different encodings.
- What's the probability of collision with 7 characters and 1 billion URLs? (Birthday problem)
- Would you pre-generate aliases or generate on-the-fly?

### Follow-Up 5: TOCTOU Race Conditions
> "The current implementation checks if a custom alias exists, then inserts it. What happens if two concurrent requests try to claim the same custom alias at the same time? Is there a TOCTOU vulnerability?"

- Identify the Time-of-Check-to-Time-of-Use gap in `store_custom()`.
- How would you make the check-and-insert atomic? (database unique constraints, `INSERT ... ON CONFLICT`, compare-and-swap)
- Does the same TOCTOU issue exist for the idempotency check in `url_to_alias`? What if two requests for the same long URL arrive simultaneously?
- How do these concerns change in a distributed, multi-instance deployment?

### Follow-Up 6: Auto-Increment vs. Hash-Based Aliases
> "The current design uses an auto-increment counter to generate aliases. What if we switched to a hash-based approach — compute `hash(long_url)[:7]` as the alias? Walk me through the trade-offs."

- Hash gives **free idempotency** — same URL always produces the same alias without a reverse lookup table. Is that worth the trade-off?
- With auto-increment, idempotency requires a separate `url_to_alias` mapping, which introduces TOCTOU concerns, locking complexity, and extra memory. Does hash eliminate that entire problem?
- What's the collision probability with 7-char Base62 hashes at 1 billion URLs? (~14% via the birthday problem — what's your retry/salting strategy?)
- Auto-increment produces **sequential, predictable** aliases. Is that a security concern? Does hash-based give better unpredictability?
- In a **distributed** system, auto-increment requires coordination (a centralized counter or ticket server). Hash-based is stateless — each node can generate aliases independently. How does that change the architecture?
- Are there hybrid approaches? (e.g., hash for idempotency detection, auto-increment for the actual alias)
