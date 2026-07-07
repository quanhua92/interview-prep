# LFU Cache

- **Category**: Coding
- **Difficulty**: Hard
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 460, Glassdoor

---

## Question Description

Design and implement a data structure for a **Least Frequently Used (LFU)** cache.

Implement the `LFUCache` class:

*   `LFUCache(int capacity)` Initializes the object with the `capacity` of the data structure.
*   `int get(int key)` Gets the value of the `key` if the `key` exists in the cache. Otherwise, returns `-1`.
*   `void put(int key, int value)` Updates the value of the `key` if present, or inserts the `key` if not already present. When the cache reaches its `capacity`, it should invalidate and remove the **least frequently used** key before inserting a new item. For this problem, when there is a **tie** (i.e., two or more keys with the same frequency), the key that has been **least recently used** should be invalidated.

To determine the least frequently used key, a **use counter** is maintained for each key in the cache. The key with the smallest use counter is the least frequently used key.

When a key is first inserted into the cache, its use counter is set to `1` (due to the `put` operation). The use counter for a key in the cache is incremented on either a `get` or `put` operation.

The functions `get` and `put` must each run in $\mathcal{O}(1)$ average time complexity.

### Examples

*   **Input**:
    `["LFUCache", "put", "put", "get", "put", "get", "get", "put", "get", "get", "get"]`
    `[[2], [1, 1], [2, 2], [1], [3, 3], [2], [3], [4, 4], [1], [3], [4]]`
*   **Output**:
    `[null, null, null, 1, null, -1, 3, null, -1, 3, 4]`
*   **Explanation**:
    ```python
    # cnt(x) = use counter for key x
    # cache=[] displays LFU/LRU ordering (leftmost is least recently used)
    lfu = LFUCache(2)
    lfu.put(1, 1)   # cache=[1], cnt(1)=1
    lfu.put(2, 2)   # cache=[2, 1], cnt(2)=1, cnt(1)=1
    lfu.get(1)      # returns 1; cache=[1, 2], cnt(1)=2, cnt(2)=1
    lfu.put(3, 3)   # 2 is evicted (cnt(2)=1 is lowest); cache=[3, 1], cnt(3)=1, cnt(1)=2
    lfu.get(2)      # returns -1 (not found)
    lfu.get(3)      # returns 3; cache=[3, 1], cnt(3)=2, cnt(1)=2
    lfu.put(4, 4)   # 1 is evicted (tie break: cnt(1)=cnt(3)=2, but 1 is LRU); cache=[4, 3], cnt(4)=1, cnt(3)=2
    lfu.get(1)      # returns -1 (not found)
    lfu.get(3)      # returns 3; cache=[3, 4], cnt(3)=3, cnt(4)=1
    lfu.get(4)      # returns 4; cache=[4, 3], cnt(4)=2, cnt(3)=3
    ```

### Constraints
*   $1 \le \text{capacity} \le 10^4$
*   $0 \le \text{key} \le 10^5$
*   $0 \le \text{value} \le 10^9$
*   At most $2 \times 10^5$ calls will be made to `get` and `put`.

---

## Detailed Solution (C++)

To implement LFU Cache in $\mathcal{O}(1)$ average time complexity:
1.  **Cache Map**: `std::unordered_map<int, Node>` maps `key` to its details: `val`, current frequency `freq`, and an iterator to its position in the frequency lists to allow $\mathcal{O}(1)$ deletion.
2.  **Frequency Lists**: `std::unordered_map<int, std::list<int>> freqMap` maps each frequency count to a doubly-linked list of keys sharing that frequency. The most recently accessed key is pushed to the `front` of the list, so the LRU key for a frequency is always at the `back` of the list.
3.  **Global Minimum Frequency**: `minFreq` tracks the lowest active frequency across the cache. When eviction is required, we remove the key from the back of `freqMap[minFreq]`.

### Update State (`touch` helper):
When a key is accessed:
1.  Remove the key from its current frequency list in `freqMap[oldFreq]` in $\mathcal{O}(1)$ using the saved iterator.
2.  Increment the key's frequency: `freq++`.
3.  Push the key to the front of the new frequency list `freqMap[newFreq]`, and update the saved list iterator in the node.
4.  If the old frequency list is now empty and `oldFreq == minFreq`, increment `minFreq`.

### Standard C++ Production Code

```cpp
#include <unordered_map>
#include <list>
#include <iterator>

class LFUCache {
private:
    struct Node {
        int key;
        int val;
        int freq;
        std::list<int>::iterator it; // Iterator pointing to its location in the frequency list
    };

    int cap;
    int minFreq;
    std::unordered_map<int, Node> cache;
    std::unordered_map<int, std::list<int>> freqMap; // Maps frequency -> list of keys (front is MRU, back is LRU)

    void touch(int key) {
        auto& node = cache[key];
        int oldFreq = node.freq;
        node.freq++;

        // Remove from the old frequency list
        freqMap[oldFreq].erase(node.it);

        // Add to the new frequency list
        freqMap[node.freq].push_front(key);
        node.it = freqMap[node.freq].begin();

        // If the old frequency list is empty and was the minFreq, increment minFreq
        if (freqMap[oldFreq].empty() && oldFreq == minFreq) {
            minFreq++;
        }
    }

public:
    LFUCache(int capacity) : cap(capacity), minFreq(0) {}

    int get(int key) {
        if (cap == 0 || !cache.count(key)) {
            return -1;
        }
        touch(key);
        return cache[key].val;
    }

    void put(int key, int value) {
        if (cap == 0) {
            return;
        }

        // If key already exists, update value and touch frequency
        if (cache.count(key)) {
            cache[key].val = value;
            touch(key);
            return;
        }

        // Evict if cache is at capacity
        if (cache.size() >= static_cast<size_t>(cap)) {
            // Retrieve the LRU key with the minimum frequency
            int evict_key = freqMap[minFreq].back();
            freqMap[minFreq].pop_back();
            cache.erase(evict_key);
        }

        // Insert new element with frequency 1
        minFreq = 1;
        freqMap[1].push_front(key);
        cache[key] = Node{key, value, 1, freqMap[1].begin()};
    }
};
```

---

## Detailed Solution (Python)

To achieve true $\mathcal{O}(1)$ average operations in Python without writing a custom doubly linked list from scratch, we use `collections.OrderedDict`. 

In Python, an `OrderedDict` maintains insertion order. The oldest inserted item can be removed in $\mathcal{O}(1)$ using `popitem(last=False)`.

### Standard Python Production Code

```python
from collections import OrderedDict, defaultdict

class LFUCache:
    def __init__(self, capacity: int):
        self.cap = capacity
        self.min_freq = 0
        self.cache = {}  # maps key -> (val, freq)
        self.freq_map = defaultdict(OrderedDict) # maps freq -> OrderedDict of {key: True} (MRU is right, LRU is left)

    def _touch(self, key: int) -> None:
        val, freq = self.cache[key]
        
        # Remove from old frequency OrderedDict
        del self.freq_map[freq][key]
        if not self.freq_map[freq]:
            del self.freq_map[freq]
            if freq == self.min_freq:
                self.min_freq += 1
                
        # Update frequency and insert into new frequency OrderedDict
        new_freq = freq + 1
        self.cache[key] = (val, new_freq)
        self.freq_map[new_freq][key] = True

    def get(self, key: int) -> int:
        if self.cap == 0 or key not in self.cache:
            return -1
        self._touch(key)
        return self.cache[key][0]

    def put(self, key: int, value: int) -> None:
        if self.cap == 0:
            return

        if key in self.cache:
            _, freq = self.cache[key]
            self.cache[key] = (value, freq)
            self._touch(key)
            return

        # Evict LFU (LRU as tiebreaker) if cache is full
        if len(self.cache) >= self.cap:
            # popitem(last=False) pops the oldest/first inserted key (LRU) in O(1)
            evict_key, _ = self.freq_map[self.min_freq].popitem(last=False)
            del self.cache[evict_key]
            if not self.freq_map[self.min_freq]:
                del self.freq_map[self.min_freq]

        # Insert new key
        self.min_freq = 1
        self.cache[key] = (value, 1)
        self.freq_map[1][key] = True
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. OrderedDict vs Standard Set/Dict
* In older Python versions, standard dictionaries did not guarantee order, and standard `set` objects do not support $\mathcal{O}(1)$ popping of the *oldest* element.
* While Python 3.7+ dictionaries maintain insertion order, `collections.OrderedDict` provides explicit methods like `popitem(last=False)` (which pops the first-inserted key in $\mathcal{O}(1)$), making it the most readable and correct tool for simulating doubly-linked list nodes.

### 2. Guarding against Capacity 0
* Always check for `capacity == 0` during initialization and `put` operations. Failing to check this can lead to evicting elements on an empty cache or infinite loops if elements are inserted into a zero-capacity cache.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity (get)** | $\mathcal{O}(1)$ | Dictionary lookup and `OrderedDict`/`list` iterator deletion/insertion take constant average time. |
| **Time Complexity (put)** | $\mathcal{O}(1)$ | Insertion, eviction, and pointer manipulation run in constant average time. |
| **Space Complexity** | $\mathcal{O}(\text{capacity})$ | We store at most `capacity` number of nodes in the hash maps and lists. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What is the difference between LRU (Least Recently Used) and LFU (Least Frequently Used)?
* **Answer**: 
  * **LRU** only considers the *recency* of access. If a key was accessed long ago, it is evicted, even if it had been accessed 100 times before.
  * **LFU** considers *frequency* first, using recency only as a tiebreaker. If a key is accessed 100 times, it will not be evicted in favor of a key accessed once, even if the latter was accessed more recently. LFU is better for static popular content patterns, but LRU adapts better to shifting hot-spots.

### Q2: How can we prevent "frequency starvation" in LFU?
* **Answer**: In a basic LFU cache, items that get a huge burst of traffic early on will accumulate high frequency counts (e.g., $1000$ accesses) and will never be evicted, even if they are never accessed again (frequency starvation).
  * **Solution**: Introduce **frequency decay**. Periodically (e.g. after a certain number of operations or time interval), divide all use counters by 2, or subtract a constant, allowing older items' weights to decay over time.

---

## Pro-Tip: How to Impress the Interviewer

* **Use List Iterators Correctly**: In C++, point out that saving `std::list<int>::iterator` inside the `Node` avoids searching the list when deleting elements. Searching a linked list takes $\mathcal{O}(N)$ time; using the iterator directly reduces list deletion to a true $\mathcal{O}(1)$ pointer update.
* **Explain Memory Overhead**: Discuss the memory cost of LFU. Because we store list pointers, frequency tables, and cache values, LFU has a high memory overhead per cache item compared to a simple array or hashtable. Pointing this out highlights cost-conscious systems design thinking.
