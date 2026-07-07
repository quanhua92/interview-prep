# Insert Delete GetRandom O(1)

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 380, Glassdoor

---

## Question Description

Implement the `RandomizedSet` class:

*   `RandomizedSet()` Initializes the `RandomizedSet` object.
*   `bool insert(int val)` Inserts an item `val` into the set if not present. Returns `true` if the item was not already present, `false` otherwise.
*   `bool remove(int val)` Removes an item `val` from the set if present. Returns `true` if the item was present, `false` otherwise.
*   `int getRandom()` Returns a random element from the current set of elements (it's guaranteed that at least one element exists when this method is called). Each element must have the **same probability** of being returned.

You must implement the functions of the class such that each function works in **average** $\mathcal{O}(1)$ time complexity.

### Examples
*   **Input**:
    ```
    ["RandomizedSet", "insert", "remove", "insert", "getRandom", "remove", "insert", "getRandom"]
    [[], [1], [2], [2], [], [1], [2], []]
    ```
*   **Output**:
    ```
    [null, true, false, true, 2, true, false, 2]
    ```
*   **Explanation**:
    ```cpp
    RandomizedSet randomizedSet;
    randomizedSet.insert(1);   // Inserts 1 to the set. Returns true (1 inserted successfully).
    randomizedSet.remove(2);   // Returns false as 2 does not exist in the set.
    randomizedSet.insert(2);   // Inserts 2 to the set, returns true. Set now contains [1,2].
    randomizedSet.getRandom(); // getRandom() should return either 1 or 2 randomly with equal probability.
    randomizedSet.remove(1);   // Removes 1 from the set, returns true. Set now contains [2].
    randomizedSet.insert(2);   // 2 was already in the set, so return false.
    randomizedSet.getRandom(); // Since 2 is the only number in the set, getRandom() always returns 2.
    ```

---

## Detailed Solution (C++)

To implement all three operations in average $\mathcal{O}(1)$ time:
1.  **getRandom() in $\mathcal{O}(1)$**: We must be able to choose a random index in $[0, N-1]$ and look up the element at that index in $\mathcal{O}(1)$ time. This requires a **dynamic array** (`std::vector` in C++).
2.  **insert(val) in $\mathcal{O}(1)$**: We append `val` to the end of our dynamic array, and record its index in a **hash map** (`std::unordered_map` in C++) mapping `val -> index`.
3.  **remove(val) in $\mathcal{O}(1)$**: We look up the index of `val` in the hash map. To avoid shifting elements (which would cost $\mathcal{O}(N)$), we swap the target element with the **last** element in our array. Then, we update the last element's index in the hash map, pop the last element from the array, and delete the target key from the hash map.

### Standard C++ Production Code

```cpp
#include <vector>
#include <unordered_map>
#include <random>
#include <stdexcept>

class RandomizedSet {
private:
    std::vector<int> vals;
    std::unordered_map<int, int> idx_map;
    
    // Modern C++ Random Engine
    mutable std::mt19937 rng;

public:
    /** Initialize your data structure here. */
    RandomizedSet() : rng(std::random_device{}()) {}

    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if (idx_map.find(val) != idx_map.end()) {
            return false;
        }
        // Save the index where val will be placed in the vector
        idx_map[val] = static_cast<int>(vals.size());
        vals.push_back(val);
        return true;
    }

    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        auto it = idx_map.find(val);
        if (it == idx_map.end()) {
            return false;
        }
        
        int target_idx = it->second;
        int last_val = vals.back();
        
        // Swap target element with the last element
        vals[target_idx] = last_val;
        idx_map[last_val] = target_idx; // Update last element's index
        
        // Remove the last element
        vals.pop_back();
        idx_map.erase(it);
        
        return true;
    }

    /** Get a random element from the set. */
    int getRandom() const {
        if (vals.empty()) {
            throw std::runtime_error("Set is empty");
        }
        std::uniform_int_distribution<size_t> dist(0, vals.size() - 1);
        return vals[dist(rng)];
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

```python
import random

class RandomizedSet:
    def __init__(self):
        """
        Initializes the RandomizedSet data structure.
        """
        self.vals: list[int] = []
        self.idx_map: dict[int, int] = {}

    def insert(self, val: int) -> bool:
        """
        Inserts a value to the set. Returns True if the set did not already contain the specified element.
        """
        if val in self.idx_map:
            return False
        
        self.idx_map[val] = len(self.vals)
        self.vals.append(val)
        return True

    def remove(self, val: int) -> bool:
        """
        Removes a value from the set. Returns True if the set contained the specified element.
        """
        if val not in self.idx_map:
            return False
        
        # Get target index and value of the last element
        target_idx = self.idx_map[val]
        last_val = self.vals[-1]
        
        # Swap target element with the last element
        self.vals[target_idx] = last_val
        self.idx_map[last_val] = target_idx
        
        # Pop the last element and remove from map
        self.vals.pop()
        del self.idx_map[val]
        return True

    def getRandom(self) -> int:
        """
        Get a random element from the set.
        """
        # random.choice uses constant time list index retrieval under the hood
        return random.choice(self.vals)
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. The Swap-and-Pop Performance Optimization
*   Using `list.remove(val)` or `list.pop(idx)` in Python is a common pitfall. Both shift elements to fill the gap, incurring $\mathcal{O}(N)$ time complexity.
*   By copying the last element into the target index (`self.vals[target_idx] = last_val`) and running `self.vals.pop()`, we achieve a true $\mathcal{O}(1)$ operation because popping the last element of a Python list does not require element shifting.

### 2. Time Complexity of `in` Operator on List vs Dict
*   Checking `val in self.vals` takes $\mathcal{O}(N)$ time.
*   Checking `val in self.idx_map` utilizes the dictionary's underlying hash table, taking average $\mathcal{O}(1)$ time. Always check existence using the dictionary.

### 3. Memory Allocation Overhead of Dicts
*   Python dictionaries have significant memory overhead due to hash table allocation, collision resolution structures, and object wrapping.
*   If memory footprint is critical, pre-sizing or utilizing a custom hash map could be considered, though standard python `dict` is highly optimized in CPython 3.6+.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(1)$ average | Hash map lookups/deletions and dynamic array appends/pops execute in average constant time. |
| **Space Complexity** | $\mathcal{O}(n)$ | We store $n$ elements in both the dynamic array and the hash map. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if duplicates are allowed? (LeetCode 381)
*   **Answer**: When duplicates are allowed, a value can map to multiple indices. 
    1.  Change the map schema to `std::unordered_map<int, std::unordered_set<int>>` mapping each value to a set of indices.
    2.  For `remove(val)`, retrieve the set of indices for `val`, grab any index from it (e.g. the first one), swap it with the last element in the array, and update the index set of the swapped element.

### Q2: How does the load factor of the hash map affect the average-case $\mathcal{O}(1)$ time complexity?
*   **Answer**: As elements are added, if the load factor (ratio of elements to buckets) exceeds a threshold, the hash map reallocates and rehashes all keys, costing $\mathcal{O}(N)$ in the worst case.
*   To achieve stable performance in latency-sensitive systems, we can call `reserve()` or `rehash()` in C++ beforehand if the maximum size is known, avoiding runtime rehashing.

---

## Pro-Tip: How to Impress the Interviewer

*   **Mention Iterator Invalidation**: In C++, pushing elements into `std::vector` can cause reallocation, which invalidates all iterators, pointers, and references to elements. Although we only store raw integers (where invalidation is less dangerous than object references), pointing this out shows strong systems-level C++ hygiene.
*   **Randomness Determinism**: Highlight that in testing and production systems, it is vital to seed the random engine properly (using `std::random_device` for non-deterministic behavior in production, and deterministic seeds for reproducible test cases).
