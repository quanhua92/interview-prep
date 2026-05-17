# Design a Thread-Safe LRU Cache — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] Is thread safety required, or is single-threaded acceptable?
  - [ ] Do entries need TTL (time-to-live) eviction, or only capacity-based LRU eviction?
  - [ ] Is there a loader function (cache-aside pattern), or is this a plain key-value cache?
  - [ ] What types are the keys and values (generics vs specific types)?
- [ ] List functional requirements (3-5 items):
  - [ ] `get(key)` returns value in O(1) or indicates miss
  - [ ] `put(key, value)` inserts/updates, evicts LRU when at capacity
  - [ ] `delete(key)` removes a key
  - [ ] Cache is capacity-bounded (fixed max entries)
  - [ ] Optional: TTL per entry, loader function for cache misses
- [ ] List non-functional requirements:
  - [ ] All operations O(1) time complexity
  - [ ] Thread-safe under concurrent access
  - [ ] No memory leaks (map and list always consistent)
  - [ ] Extensible interface (TTL, loader, distributed) without rewriting core
- [ ] State complexity targets:
  - [ ] `get()`: O(1) via HashMap lookup + O(1) move-to-head via doubly linked list
  - [ ] `put()`: O(1) via HashMap insert + O(1) insertion/removal via doubly linked list
  - [ ] Eviction: O(1) via tail pointer (no scanning)

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw the data structure composition:
  - [ ] HashMap: key -> Node pointer (enables O(1) lookup)
  - [ ] Doubly Linked List: sentinel head (MRU side) <-> ... <-> sentinel tail (LRU side)
  - [ ] Sentinel nodes eliminate all null-check edge cases
- [ ] Explain why each component is required from first principles:
  - [ ] "O(1) get requires O(1) lookup by key, so we need a HashMap"
  - [ ] "O(1) eviction requires knowing the LRU node without scanning, so we need a tail pointer"
  - [ ] "O(1) move-to-head requires O(1) pointer surgery on both neighbors, so we need a doubly linked list, not singly linked"
- [ ] Identify the main operations and their access patterns:
  - [ ] `get(key)`: read + possible write (move-to-head), hot path
  - [ ] `put(key, value)`: write + possible eviction, moderate frequency
  - [ ] `delete(key)`: write, infrequent
- [ ] Note: the HashMap stores **node pointers**, not just values, so move-to-head requires no search
- [ ] Present the design and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] State all five invariants explicitly before coding:
  - [ ] Size: `len(map) == count of non-sentinel nodes in list`
  - [ ] Recency: `head.next` is MRU; `tail.prev` is LRU
  - [ ] Capacity: `len(map) <= capacity` after every `put()`
  - [ ] Bidirectionality: `N.prev.next == N` and `N.next.prev == N` for all nodes
  - [ ] Thread safety: invariants 1-4 hold as observed by any thread
- [ ] Define the Node class:
  - [ ] Fields: `key`, `value`, `prev`, `next`, optional `expires_at`
  - [ ] `is_expired()` method for TTL check
  - [ ] Use `__slots__` (Python) for memory efficiency
- [ ] Define the LRUCache class:
  - [ ] Fields: `capacity`, `map`, sentinel `head`, sentinel `tail`, `lock`
  - [ ] Optional: `loader` callable, `ttl_seconds`, `in_flight` dict for singleflight
- [ ] Implement private helpers (must always be called with lock held):
  - [ ] `_insert_at_head(node)`: link node between sentinel head and current head.next
  - [ ] `_remove_node(node)`: unlink by rewiring prev.next and next.prev
  - [ ] `_move_to_head(node)`: compose remove + insert
  - [ ] `_evict_tail()`: remove and return `tail.prev`
- [ ] Implement public methods:
  - [ ] `get(key)`: acquire lock -> map lookup -> if expired, evict + load -> if hit, move-to-head -> return value
  - [ ] `put(key, value)`: acquire lock -> if exists, update + move-to-head -> else insert at head -> if over capacity, evict tail
  - [ ] `delete(key)`: acquire lock -> pop from map -> remove from list
- [ ] Walk through edge cases:
  - [ ] Capacity = 1 (every put evicts)
  - [ ] `put()` on existing key (update value + move-to-head, no eviction)
  - [ ] `get()` on expired key (lazy eviction + reload)

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss concurrency strategy:
  - [ ] Global lock: correct but serializes everything (throughput bottleneck)
  - [ ] ReadWriteLock: multiple readers, exclusive writer (better for read-heavy)
  - [ ] Segmented locking: partition keys across N segments via `hash(key) % N`, each with own lock; ~Nx throughput
  - [ ] State your choice and justify (segmented for production, global for simplicity)
- [ ] Explain thundering herd and singleflight:
  - [ ] Problem: N concurrent misses for same key fire N backend requests
  - [ ] Solution: track in-flight Futures per key; first miss loads, others wait on same Future
  - [ ] Critical: release cache lock before calling external loader (avoid deadlock)
- [ ] Discuss TTL eviction approaches:
  - [ ] Lazy: check `is_expired()` on every `get()` (simple, correct)
  - [ ] Eager: background thread with min-heap on expiry timestamps (proactive memory reclaim)
  - [ ] Hybrid: lazy on access + optional background sweep
- [ ] Explain scaling from local to distributed:
  - [ ] L1: Sticky routing (hash key to one server; cold slice on node loss)
  - [ ] L2: Shared Memcached/Redis (shared view, extra RTT ~0.5-1ms)
  - [ ] L3: Two-tier (local hot set + shared cache + DB; invalidation via pub/sub or short TTL)
  - [ ] Interface stays the same: abstract storage behind a `Store` interface
- [ ] Address failure modes:
  - [ ] Double-booking: non-atomic check-then-set outside lock -> fix: single lock scope
  - [ ] Memory leak: map/list out of sync -> fix: always update both atomically
  - [ ] Stale TTL: expiry not checked on get -> fix: lazy check inside get()
  - [ ] O(n) eviction: singly linked list -> fix: use doubly linked list

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made and why (e.g., segmented locking adds complexity but scales throughput)
- [ ] Mention what you would improve with more time (e.g., metrics/export, LFU policy swap, async loader)
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
