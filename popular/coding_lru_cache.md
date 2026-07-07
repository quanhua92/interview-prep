# LRU Cache Implementation

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer / AI System Engineer
- **Source**: LeetCode 146, Glassdoor, Taro
- **Flashcards**: [Coding Playbook deck](flash_cards/behavioral_qa/coding_playbook.md)

---

## Question Description

Design a data structure that follows the constraints of a **Least Recently Used (LRU) cache**.

Implement the `LRUCache` class:
*   `LRUCache(int capacity)` Initialize the LRU cache with positive size `capacity`.
*   `int get(int key)` Return the value of the `key` if the key exists, otherwise return `-1`.
*   `void put(int key, int value)` Update the value of the `key` if the key exists. Otherwise, add the `key-value` pair to the cache. If the number of keys exceeds the `capacity` from this operation, **evict** the least recently used key.

### Constraints
*   $1 \le \text{capacity} \le 3000$
*   $0 \le \text{key} \le 10^4$
*   $0 \le \text{value} \le 10^5$
*   At most $2 \times 10^5$ calls will be made to `get` and `put`.
*   **Requirement**: Both `get` and `put` must run in $\mathcal{O}(1)$ average time complexity.

---

## Detailed Solution (C++)

In high-bar low-level systems interviews (especially at NVIDIA), standard containers like `std::list` paired with `std::unordered_map` are discouraged. The standard library allocator introduces dynamic memory overhead and pointer chasing. Interviewers expect you to **implement the doubly linked list from scratch**, showing a solid grasp of manual pointer manipulation, memory management, and cache-conscious designs.

Below is a production-grade, memory-safe, and modern C++ implementation.

```cpp
#include <unordered_map>
#include <stdexcept>
#include <utility>

class LRUCache {
private:
    // Doubly Linked List Node Definition
    struct Node {
        int key;
        int value;
        Node* prev{nullptr};
        Node* next{nullptr};
        
        Node(int k, int v) noexcept : key(k), value(v) {}
    };

    int capacity;
    int size;
    Node* head; // Dummy head sentinel
    Node* tail; // Dummy tail sentinel
    
    // Hash map mapping key to Node pointer for O(1) lookups
    std::unordered_map<int, Node*> cacheMap;

    // Helper: Remove a node from the doubly linked list
    void removeNode(Node* node) noexcept {
        Node* prevNode = node->prev;
        Node* nextNode = node->next;
        if (prevNode) prevNode->next = nextNode;
        if (nextNode) nextNode->prev = prevNode;
    }

    // Helper: Insert a node right after the dummy head (most recently used position)
    void insertAtHead(Node* node) noexcept {
        Node* nextNode = head->next;
        
        head->next = node;
        node->prev = head;
        
        node->next = nextNode;
        if (nextNode) nextNode->prev = node;
    }

    // Helper: Move an existing node to the head (marks it as recently used)
    void moveToHead(Node* node) noexcept {
        removeNode(node);
        insertAtHead(node);
    }

    // Helper: Evict the tail node (least recently used, just before dummy tail)
    Node* popTail() noexcept {
        Node* res = tail->prev;
        if (res != head) {
            removeNode(res);
            return res;
        }
        return nullptr;
    }

public:
    // Explicit constructor to prevent implicit conversions
    explicit LRUCache(int capacity) : capacity(capacity), size(0) {
        if (capacity <= 0) {
            throw std::invalid_argument("Capacity must be positive.");
        }
        // Create dummy head and tail to avoid edge cases and null pointer checks
        head = new Node(-1, -1);
        tail = new Node(-1, -1);
        head->next = tail;
        tail->prev = head;
    }

    // Rule of 5: Prevent resource leaks and double deletions via copying/moving
    ~LRUCache() noexcept {
        Node* curr = head;
        while (curr != nullptr) {
            Node* temp = curr->next;
            delete curr;
            curr = temp;
        }
    }

    LRUCache(const LRUCache&) = delete;
    LRUCache& operator=(const LRUCache&) = delete;
    LRUCache(LRUCache&&) noexcept = delete;
    LRUCache& operator=(LRUCache&&) noexcept = delete;

    int get(int key) noexcept {
        auto it = cacheMap.find(key);
        if (it == cacheMap.end()) {
            return -1;
        }
        
        Node* node = it->second;
        moveToHead(node); // Accessing the node makes it most recently used
        return node->value;
    }

    void put(int key, int value) noexcept {
        auto it = cacheMap.find(key);
        
        if (it != cacheMap.end()) {
            // Key exists: update value and move node to head
            Node* node = it->second;
            node->value = value;
            moveToHead(node);
        } else {
            // Key does not exist: create a new node
            Node* newNode = new Node(key, value);
            cacheMap[key] = newNode;
            insertAtHead(newNode);
            size++;
            
            if (size > capacity) {
                // Capacity exceeded: evict least recently used (tail->prev)
                Node* tailNode = popTail();
                if (tailNode) {
                    cacheMap.erase(tailNode->key);
                    delete tailNode; // Deallocate node memory
                    size--;
                }
            }
        }
    }
};
```

---

## Detailed Solution (Python)

In Python, we can implement the LRU Cache using two primary approaches:
1. **Custom Doubly Linked List + Dict**: Mirroring the C++ structure, which shows dynamic reference manipulation and algorithm design.
2. **`collections.OrderedDict`**: Utilizing Python's standard library, which is implemented in C under CPython and is highly optimized.

### Approach 1: Custom Doubly Linked List & Dict (Recommended for Interview Depth)

This approach implements the list pointers manually. To optimize memory footprint and execution speed, we utilize `__slots__` in the `Node` class.

```python
from typing import Dict, Optional

class Node:
    # __slots__ prevents the creation of __dict__ and __weakref__ for each instance,
    # reducing memory overhead and improving attribute access speed.
    __slots__ = ('key', 'value', 'prev', 'next')

    def __init__(self, key: int, value: int):
        self.key: int = key
        self.value: int = value
        self.prev: Optional[Node] = None
        self.next: Optional[Node] = None


class LRUCache:
    def __init__(self, capacity: int):
        if capacity <= 0:
            raise ValueError("Capacity must be positive.")
        self.capacity: int = capacity
        
        # Sentinel dummy head and tail nodes to eliminate edge cases (e.g. empty lists)
        self.head: Node = Node(-1, -1)
        self.tail: Node = Node(-1, -1)
        self.head.next = self.tail
        self.tail.prev = self.head
        
        # Hash map mapping key -> Node
        self.cache: Dict[int, Node] = {}

    def _remove(self, node: Node) -> None:
        """Remove an existing node from the doubly linked list."""
        prev_node = node.prev
        next_node = node.next
        if prev_node:
            prev_node.next = next_node
        if next_node:
            next_node.prev = prev_node

    def _add_to_head(self, node: Node) -> None:
        """Insert a node immediately after the dummy head."""
        first_node = self.head.next
        self.head.next = node
        node.prev = self.head
        node.next = first_node
        if first_node:
            first_node.prev = node

    def _move_to_head(self, node: Node) -> None:
        """Move a node to the front of the list (MRU)."""
        self._remove(node)
        self._add_to_head(node)

    def get(self, key: int) -> int:
        if key not in self.cache:
            return -1
        node = self.cache[key]
        self._move_to_head(node)
        return node.value

    def put(self, key: int, value: int) -> None:
        if key in self.cache:
            # Update existing key
            node = self.cache[key]
            node.value = value
            self._move_to_head(node)
        else:
            # Evict least recently used node if at capacity
            if len(self.cache) >= self.capacity:
                lru_node = self.tail.prev
                if lru_node and lru_node is not self.head:
                    self._remove(lru_node)
                    self.cache.pop(lru_node.key, None)
            
            # Insert new key
            new_node = Node(key, value)
            self.cache[key] = new_node
            self._add_to_head(new_node)
```

### Approach 2: Using `collections.OrderedDict` (Pythonic / Standard Library)

`OrderedDict` maintains keys in insertion order. By utilizing `move_to_end()` and `popitem(last=False)`, we can implement the LRU Cache in a few lines.

```python
from collections import OrderedDict

class LRUCacheOrderedDict:
    def __init__(self, capacity: int):
        if capacity <= 0:
            raise ValueError("Capacity must be positive.")
        self.capacity: int = capacity
        self.cache: OrderedDict[int, int] = OrderedDict()

    def get(self, key: int) -> int:
        if key not in self.cache:
            return -1
        # Move the accessed key to the end to mark it as most recently used
        self.cache.move_to_end(key)
        return self.cache[key]

    def put(self, key: int, value: int) -> None:
        if key in self.cache:
            self.cache[key] = value
            self.cache.move_to_end(key)
        else:
            if len(self.cache) >= self.capacity:
                # popitem(last=False) pops the first (FIFO/LRU) item
                self.cache.popitem(last=False)
            self.cache[key] = value
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Memory Overhead and `__slots__`
*   **The Problem**: In Python, every class instance by default contains a dictionary `__dict__` to allow dynamic attribute assignment. This adds significant memory overhead (typically ~100–150 bytes per node).
*   **The Solution**: Declaring `__slots__ = ('key', 'value', 'prev', 'next')` tells Python not to create `__dict__`. This slashes the memory footprint of each `Node` by up to **$70\%$**, which is critical when storing millions of entries in a cache.

### 2. Standard Dict vs `OrderedDict`
*   In Python 3.7+, standard `dict` maintains insertion order. However, standard `dict` does not expose an efficient `move_to_end()` API. Doing `d[key] = d.pop(key)` to move a key to the end works, but it causes hash map re-evaluation, potential bucket re-allocation, and temporary object creation.
*   `collections.OrderedDict` internally maintains a doubly linked list of keys alongside the hash table. Its C-based implementation makes operations like `move_to_end()` highly efficient, but it consumes more memory than a standard dictionary.

### 3. Garbage Collection & Circular References
*   A custom doubly linked list creates circular references (`node.next.prev == node`). Python's reference counting alone cannot reclaim memory from cyclic structures; they must be cleared by the cyclic garbage collector (generational GC).
*   To prevent memory bloat, explicitly clearing links on eviction (e.g., `lru_node.prev = None; lru_node.next = None`) allows Python's reference counting to immediately reclaim the node without waiting for the next garbage collection cycle.

---

## Complexity Analysis

| Operation | Time Complexity | Space Complexity | Description |
| :--- | :--- | :--- | :--- |
| `get()` | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ | Hash map lookup takes $\mathcal{O}(1)$ average time, and list pointer adjustments take $\mathcal{O}(1)$ time. |
| `put()` | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ | Lookup/insertion in hash map takes $\mathcal{O}(1)$ average. Eviction and node insertion take $\mathcal{O}(1)$ time. |
| Total Space | - | $\mathcal{O}(C)$ | Where $C$ is the capacity. The hash map and the doubly linked list store at most $C + 2$ nodes. |

---

## Common Follow-Up Questions & How to Answer

### Q1: How would you make this LRU Cache thread-safe?
*   **Naive Approach**: Protect all operations with a single `std::mutex`. This causes high lock contention under multi-threaded workloads, defeating concurrency.
*   **Optimized Solution - Shared Mutex (Read-Write Lock)**:
    Since `get()` modifies the linked list structure (invoking `moveToHead`), it requires a write lock on the linked list. Thus, standard `std::shared_mutex` does not yield a performance boost on its own if every read results in a structural write.
*   **Production Workaround - Segmented Cache**:
    Partition the key space into $N$ independent cache segments (buckets) using a hash function (e.g., `key % N`). Each segment has its own lock and internal LRU cache. This scales concurrency linearly with the segment count and minimizes lock contention.
*   **Advanced Solution - Deferred Recency Updates**:
    To avoid structural linked-list modifications on every read, write lock acquisition can be deferred. 
    1. Read operations only query the hash map and push the accessed node's address into a thread-safe, lock-free ring buffer (e.g., Single-Producer Multi-Consumer or SPMC).
    2. A background thread (or the writer thread during a `put`) periodically drains the ring buffer and batches the updates to the doubly linked list. This maintains $\mathcal{O}(1)$ read latency with minimal lock overhead.

### Q2: How do you optimize for cache locality and avoid dynamic memory fragmentation?
*   **The Problem**: Frequent calls to `new` and `delete` cause heap fragmentation and trigger costly system calls. Scattered node allocations lead to pointer-chasing and CPU D-Cache misses.
*   **The Solution - Array-backed Memory Pool**:
    Pre-allocate a contiguous array/vector of nodes of size `capacity`.
    Instead of using raw 64-bit pointers (`Node*`), use 32-bit indices (`int32_t`) to point to the next/prev nodes in the array. This slashes the pointer memory footprint in half (from 16 bytes to 8 bytes per node), allowing more nodes to fit in a single CPU cache line (typically 64 bytes).
    
    ```cpp
    struct PoolNode {
        int key;
        int value;
        int32_t prev;
        int32_t next;
    };
    std::vector<PoolNode> pool;
    int32_t freeListHead;
    ```
    We manage a linked list of free indices inside this pre-allocated array. Allocating a node is now as simple as popping from `freeListHead`, and deallocating is pushing back to it—both are $\mathcal{O}(1)$ actions without OS heap involvement.

### Q3: What if the Cache capacity is extremely large (e.g., millions of items)?
*   **Memory Overhead of `std::unordered_map`**:
    `std::unordered_map` is highly memory-inefficient due to node bucket structures and chaining collision handling.
*   **Optimization**:
    1. Replace `std::unordered_map` with a flat, open-addressing hash map (e.g., Google's `absl::flat_hash_map` or Robin Hood hashing).
    2. Store nodes in a compact representation.
    3. Use a multi-tiered cache hierarchy if the size exceeds DRAM capacity: Keep the most hot items in an in-memory L1 cache and spill over to an SSD-backed L2 cache (using page-aligned block reads/writes).

---

## Pro-Tip: How to Impress the Interviewer

*   **Mention CPU Cache Line Alignment**: Node structs should ideally align to cache lines (64 bytes). In C++, you can use `alignas(64)` to ensure nodes are aligned at cache-line boundaries to prevent false sharing and improve memory controller efficiency.
*   **Avoid Pointer Chasing**: Mention that linked lists are inherently cache-unfriendly. Highlight that in high-performance engines (e.g., NVIDIA's driver pipelines or tensor streaming pipelines), we avoid linked lists entirely where possible, replacing them with circular ring buffers or flat array index chains.
*   **Always Call Out Resource Ownership**: When writing custom data structures, explicitly define the Rule of 5 (deleting copy/move constructors and assignment operators). This signals to the interviewer that you write production-quality, bulletproof code that prevents memory leaks and double deletions.
