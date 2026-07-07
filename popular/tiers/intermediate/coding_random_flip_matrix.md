# Random Flip Matrix

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 519, Glassdoor

---

## Question Description

There is an $m \times n$ binary grid matrix with all the values set to `0` initially. Design an algorithm to randomly pick an index `(i, j)` where `matrix[i][j] == 0` and flip it to `1`. All the indices `(i, j)` where `matrix[i][j] == 0` should be equally likely to be returned.

Optimize your algorithm to minimize the number of calls made to the built-in random function of your language and optimize the time and space complexity.

Implement the `Solution` class:
*   `Solution(int m, int n)` Initializes the object with the size of the binary matrix $m$ and $n$.
*   `int[] flip()` Returns a random index `[i, j]` of the matrix where `matrix[i][j] == 0` and flips it to `1`.
*   `void reset()` Resets all the values of the matrix to `0`.

### Constraints
*   $1 \le m, n \le 10^4$
*   There will be at least one free cell for each call to `flip`.
*   At most $1000$ calls will be made to `flip` and `reset`.

### Examples
*   **Input**:
    ```text
    ["Solution", "flip", "flip", "flip", "reset", "flip"]
    [[3, 1], [], [], [], [], []]
    ```
*   **Output**: `[null, [1, 0], [2, 0], [0, 0], null, [2, 0]]`
*   **Explanation**:
    ```cpp
    Solution solution(3, 1);
    solution.flip();  // returns [1, 0]
    solution.flip();  // returns [2, 0]
    solution.flip();  // returns [0, 0] (no other 0-cells left)
    solution.reset(); // all cells reset to 0
    solution.flip();  // returns [2, 0] (randomly chosen again)
    ```

---

## Detailed Solution (C++)

A naive approach would be to store all $m \times n$ elements in an array and run a standard **Fisher-Yates Shuffle**. However, the matrix size can be up to $10^4 \times 10^4 = 10^8$ cells, requiring $\approx 400$ MB of memory, which exceeds LeetCode's memory limit.

Since at most $1000$ calls will be made to `flip`, we can simulate the Fisher-Yates shuffle using a **Hash Map** to lazily track swapped elements.

### Lazy Fisher-Yates Logic
1. We represent the matrix cells as virtual indices in the range $[0, \text{total} - 1]$ where $\text{total} = m \times n$.
2. In each `flip()` call:
   - Pick a random virtual index `r` in the range $[0, \text{total} - 1]$.
   - Determine the actual value represented by `r`. If `r` is a key in `mapping`, we use `mapping[r]`; otherwise, the actual value is just `r`. Let's call this `x`.
   - We must swap the selected value with the value at the end of our active selection range (`total - 1`). 
   - Find the value at `total - 1`: if `total - 1` is in `mapping`, it is `mapping[total - 1]`; otherwise, it is `total - 1`. Let's call this `lastVal`.
   - Update `mapping[r] = lastVal`. This moves the last element to position `r`.
   - Delete the entry for `total - 1` from `mapping` if it exists (since that index is no longer accessible).
   - Decrement `total` by 1.
   - Return the coordinate `[x / n, x % n]`.
3. `reset()` simply clears the hash map and sets `total = m * n`.

### Standard C++ Production Code

```cpp
#include <vector>
#include <unordered_map>
#include <cstdlib>

class Solution {
private:
    int m;
    int n;
    int total;
    std::unordered_map<int, int> mapping;

public:
    Solution(int m, int n) : m(m), n(n), total(m * n) {}

    std::vector<int> flip() {
        // Choose a random index in the range [0, total - 1]
        int r = std::rand() % total;

        // If r has been mapped/swapped, get its mapped value; otherwise, it is r itself
        int x = mapping.count(r) ? mapping[r] : r;

        // Get the value representing the last position in the active range
        int lastIdx = total - 1;
        int lastVal = mapping.count(lastIdx) ? mapping[lastIdx] : lastIdx;

        // Swap: place the last value at index r
        mapping[r] = lastVal;

        // Clean up the map by erasing the last index to prevent memory bloat
        mapping.erase(lastIdx);
        
        // Decrement the active size of the selection pool
        total--;

        return {x / n, x % n};
    }

    void reset() {
        mapping.clear();
        total = m * n;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

```python
import random
from typing import List, Dict

class Solution:
    def __init__(self, m: int, n: int):
        self.m = m
        self.n = n
        self.total = m * n
        self.mapping: Dict[int, int] = {}

    def flip(self) -> List[int]:
        """
        Flips a random 0 cell to 1.
        
        Time Complexity: O(1)
        Space Complexity: O(K) where K is the number of flips
        """
        # Pick a random virtual index
        r = random.randint(0, self.total - 1)
        
        # Resolve the actual value of the chosen cell
        x = self.mapping.get(r, r)
        
        # Resolve the value at the last active index
        last_idx = self.total - 1
        last_val = self.mapping.get(last_idx, last_idx)
        
        # Place the last element at the chosen position r
        self.mapping[r] = last_val
        
        # Erase the last index from mapping to conserve memory
        if last_idx in self.mapping:
            del self.mapping[last_idx]
            
        self.total -= 1
        
        return [x // self.n, x % self.n]

    def reset(self) -> None:
        """
        Resets the matrix. Time complexity: O(1)
        """
        self.mapping.clear()
        self.total = self.m * self.n
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Modulo and Division
*   In Python, you compute row and column using `x // self.n` (floor division) and `x % self.n` (modulo). Make sure to use integer floor division `//` so that coordinates are returned as integer types rather than floating-point values.

### 2. Random Integers using `randint`
*   In Python, `random.randint(a, b)` generates a random integer in the **inclusive** range $[a, b]$. Therefore, we pass `0` and `self.total - 1` as arguments. Passing `self.total` would result in an off-by-one index out-of-bounds error.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity (flip)** | $\mathcal{O}(1)$ | Hash map lookups, insertions, and deletions take constant time on average. |
| **Time Complexity (reset)** | $\mathcal{O}(1)$ | Clearing the map takes $\mathcal{O}(1)$ time. |
| **Space Complexity** | $\mathcal{O}(k)$ | Where $k$ is the number of calls to `flip()`. The map size never exceeds $k$, which is bounded by $1000$. |

---

## Common Follow-Up Questions & How to Answer

### Q1: Why is this better than using a set to track flipped indices?
*   **Answer**: If we use a set (e.g. `unordered_set`) to store flipped coordinates, we have to generate random numbers and retry if they are already in the set (Rejection Sampling). 
    *   As the matrix fills up (e.g., if we flip 99% of the cells), the collision rate spikes. The number of retries required to find an unflipped cell grows exponentially, leading to non-deterministic execution time. 
    *   The Fisher-Yates map-swap method guarantees that `flip()` completes in exactly $\mathcal{O}(1)$ time with zero retries.

### Q2: What happens if $m \times n$ is larger than standard integer limits (e.g. $10^{18}$)?
*   **Answer**: In Python, integers have arbitrary precision, so no overflow occurs. In C++, $10^{18}$ requires using `long long` for index calculations (`total` and `r`) to prevent overflow bugs. The hash map keys and values must also be declared as `long long`.

---

## Pro-Tip: How to Impress the Interviewer

*   **Highlight Memory Footprint Reduction**: Show that you explicitly clean up the map by erasing keys that fall outside the active selection boundary (`mapping.erase(lastIdx)`). Failing to do so keeps unused keys in memory, causing unnecessary heap overhead.
*   **Random Seed Reproducibility**: Discuss how setting a fixed random seed (reproducible testing) is essential when debugging randomized algorithms in production systems, and how to implement mocking for randomness in unit tests.
