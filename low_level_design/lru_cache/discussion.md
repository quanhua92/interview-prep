# Design a Thread-Safe LRU Cache

Source: [LLD Case Study: Thread-Safe LRU Cache (CalibreOS)](https://www.calibreos.com/learn/lld-lru-cache)

## One-Liner
Design an O(1) LRU cache using HashMap + doubly linked list, with thread safety, TTL eviction, and a path to distributed scaling.

## Requirements

### Functional
- `get(key)` returns cached value or triggers a miss in O(1)
- `put(key, value)` inserts or updates a key, evicting the least-recently-used entry when at capacity
- `delete(key)` removes a key from cache
- Capacity-bounded: oldest entry evicted when full
- Optional: TTL per entry, loader function for cache-aside, singleflight for duplicate miss deduplication

### Non-Functional
- All operations must be O(1) time complexity
- Thread-safe under concurrent read/write without serializing all access
- No memory leaks: map and list must stay consistent after every operation
- Extensible to distributed deployment without changing the public interface

## Key Concepts

### Why This Problem Matters
LRU cache is the canonical LLD interview problem because it simultaneously tests data structure composition (why doubly linked list + hash map?), invariant reasoning (what must always be true?), concurrency design (how to avoid serializing all access?), and extensibility (how to add TTL or a loader without rewriting the core?).

### Data Structure Composition
Each constraint forces the next design decision:
- O(1) `get()` requires O(1) lookup by key --> **HashMap**
- O(1) eviction requires knowing the LRU node without scanning --> **tail pointer**
- O(1) move-to-head requires O(1) pointer surgery on both neighbors --> **doubly linked list** (not singly linked)
- The HashMap stores **node pointers** directly, so move-to-head needs no search

### Sentinel Nodes
Use dummy `head` and `tail` sentinel nodes to eliminate all null-check edge cases. `head.next` is MRU; `tail.prev` is LRU. This means you never null-check during pointer surgery.

### Five Invariants (state before coding)
1. **Size invariant:** `len(map) == count of non-sentinel nodes in list`
2. **Recency invariant:** `head.next` is MRU; `tail.prev` is LRU
3. **Capacity invariant:** After every `put()`, `len(map) <= capacity`
4. **Bidirectionality invariant:** For every node N: `N.prev.next == N` and `N.next.prev == N`
5. **Thread safety invariant:** Invariants 1-4 hold as observed by any thread

### SEDIE Framework
1. **Scope:** O(1) get/put, thread-safe, capacity-bounded, optional TTL/loader/singleflight
2. **Extract Entities:** LRUCache (orchestrator), Node (DLL node with key/value/prev/next/expiry), EvictionPolicy, Loader, Singleflight
3. **Design Classes:** LRUCache owns capacity, HashMap, sentinel head/tail, locks. Node owns key, value, prev, next, expires_at
4. **Implement Critical Methods:** `get()` does map lookup + move-to-head; `put()` handles update or insert + eviction
5. **Extensibility:** TTL via lazy expiry check, singleflight via in-flight Futures, segmented locking via key-hash partitioning

## Decisions

### Locking Strategy
- **Global lock (E4):** Correct but serializes all reads and writes. Throughput bottleneck under load.
- **ReadWriteLock (E5):** Multiple concurrent readers, exclusive writer. Better for read-heavy workloads.
- **Segmented locking (E6+):** Partition keys across N independent `(HashMap, DLL, Lock)` segments via `hash(key) % N`. Concurrent access on different segments never blocks. Effectively N times throughput. This is the production-grade answer.

### TTL Eviction
- **Lazy eviction:** Check `node.is_expired()` on every `get()`. Simple, correct, no background thread needed. Expired entries consume memory until accessed.
- **Eager eviction:** Background `ScheduledExecutorService` scans a min-heap ordered by expiry timestamp. More complex but reclaims memory proactively.
- **Hybrid (recommended):** Lazy check on `get()` plus optional background sweep for long-idle entries.

### Singleflight (Thundering Herd Prevention)
When N threads miss for the same key simultaneously, without singleflight all N call the loader. With singleflight, the first miss registers an in-flight `Future` per key; subsequent threads wait on that same Future. The backend sees exactly 1 request instead of N.
- Critical detail: **release the cache lock before calling the external loader** to avoid deadlock.
- Local: `concurrent.futures` or `threading.Event` per key. Distributed: Redis SETNX with TTL.

### Scaling from Local to Distributed
| Level | Strategy | Trade-off |
|-------|----------|-----------|
| L1 | Sticky routing: hash key to one server | Each host authoritative for its slice; node loss = cold slice |
| L2 | Shared Memcached/Redis | Shared view, extra RTT (~0.5-1ms), shared failure domain |
| L3 | Two-tier: L1 local hot set + L2 shared + L3 DB | Best hit rates; invalidation via pub/sub or short TTL |

The `get(key)` and `put(key, value)` interface stays the same from local to distributed. Abstract the storage layer behind a `Store` interface from day one.

## Deep Dives

### Core Operations Walkthrough
- **`get(key)`:** Acquire lock -> map lookup -> if miss, call loader -> if expired, evict + load -> if hit, move-to-head -> release lock -> return value
- **`put(key, value)`:** Acquire lock -> if key exists, update value + move-to-head -> else create node, insert at head, add to map -> if over capacity, evict `tail.prev` from both list and map -> release lock
- **Private helpers** (`_insert_at_head`, `_remove_node`, `_move_to_head`, `_evict_tail`): Must never be called without the lock held

### Failure Modes
| Failure | Cause | Fix |
|---------|-------|-----|
| Double-booking (two threads in same node) | Non-atomic check-then-set outside lock | All check-and-set inside single lock acquisition |
| Memory leak (detached nodes) | Node removed from list but not map (or vice versa) | Always update map and list together atomically |
| Thundering herd on cold cache | N concurrent misses all call loader | Singleflight: deduplicate in-flight loads per key |
| Stale TTL entries served | Expiry not checked on `get()` | Lazy check `node.is_expired()` inside `get()` |
| Global lock bottleneck | Single lock on entire cache | Segmented LRU: N segments each with own lock |
| O(n) eviction with singly-linked list | No back-pointer for predecessor removal | Use doubly linked list for O(1) `remove_node` |

### Interview Level Expectations
- **E4/Mid-level:** Working LRU with OrderedDict or hand-rolled HashMap + singly linked list. Bugs on edge cases (capacity=1, existing key update). Cannot articulate why doubly linked list is required.
- **E5/Senior:** Derives data structure from constraints. Uses sentinel nodes. States invariants explicitly. Proposes ReadWriteLock for concurrent reads.
- **E6+/Staff:** Segmented locking, TTL with lazy + eager eviction, singleflight for thundering herd, maps distributed extension path.

## Follow-Ups
- How do you keep O(1) guarantees under concurrency without a global bottleneck?
- Walk through exactly what happens when `put()` is called on a key that already exists.
- How would you add TTL eviction without breaking the O(1) guarantee for `get()` and `put()`?
- How would you scale this LRU cache to work across 10 application servers?
- How would you swap LRU for LFU eviction without rewriting the cache class?
- What happens when the loader function is slow and 1,000 threads all miss for the same key?
- How do you prevent stale reads when a cache invalidation message is lost in a distributed setup?
