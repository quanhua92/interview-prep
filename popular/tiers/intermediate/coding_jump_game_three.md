# Jump Game III

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 1306, Glassdoor

---

## Question Description

Given an array of non-negative integers `arr` and a starting index `start`, you are initially positioned at `arr[start]`. When you are at index `i`, you can jump to `i + arr[i]` or `i - arr[i]`. 

Check if you can reach **any** index with value `0`.

Notice that you cannot jump outside of the array boundaries at any time.

### Examples
*   **Input**: `arr = [4,2,3,0,3,1,2]`, `start = 5`
    *   **Output**: `true`
    *   **Explanation**: 
        One possible path to reach index 3 (value 0) is:
        `index 5 -> index 4 -> index 1 -> index 3`
*   **Input**: `arr = [4,2,3,0,3,1,2]`, `start = 0`
    *   **Output**: `true`
    *   **Explanation**: 
        One possible path to reach index 3 (value 0) is:
        `index 0 -> index 4 -> index 1 -> index 3`
*   **Input**: `arr = [3,0,2,1,2]`, `start = 2`
    *   **Output**: `false`
    *   **Explanation**: 
        There is no way to reach any index with value 0 starting from index 2.

---

## Detailed Solution (C++)

The problem represents a graph traversal on a directed graph where each index $i$ has edges pointing to $i + \text{arr}[i]$ and $i - \text{arr}[i]$. We can use **Depth-First Search (DFS)** to traverse the graph starting from the node `start`. To prevent infinite loops caused by cycles, we maintain a `visited` array (using `std::vector<char>` or mutating the array) to record indices that have already been visited.

### Standard C++ Production Code

```cpp
#include <vector>

class Solution {
private:
    bool dfs(const std::vector<int>& arr, int i, std::vector<char>& visited) noexcept {
        // Base Case: check array boundaries and visited state
        if (i < 0 || i >= static_cast<int>(arr.size()) || visited[i]) {
            return false;
        }
        
        // Target found
        if (arr[i] == 0) {
            return true;
        }

        // Mark as visited
        visited[i] = 1;

        // Traverse left and right branches
        return dfs(arr, i + arr[i], visited) || dfs(arr, i - arr[i], visited);
    }

public:
    bool canReach(const std::vector<int>& arr, int start) noexcept {
        // Handle edge cases
        if (arr.empty() || start < 0 || start >= static_cast<int>(arr.size())) {
            return false;
        }
        
        // std::vector<char> is more space-efficient than std::vector<bool>
        // and avoids the non-standard reference proxy behavior of std::vector<bool>
        std::vector<char> visited(arr.size(), 0);
        return dfs(arr, start, visited);
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the recursive Python implementation using a set for visited track record.

```python
from typing import List

class Solution:
    def canReach(self, arr: List[int], start: int) -> bool:
        """
        Determines if we can reach an index with value 0 in the array starting from 'start'.
        
        Time Complexity: O(N) where N is the length of the array.
        Space Complexity: O(N) due to visited set and call stack.
        """
        # Edge Case: boundary checks
        if not arr or start < 0 or start >= len(arr):
            return False

        n = len(arr)
        visited = set()

        def dfs(i: int) -> bool:
            # Base Case: check bounds and visited
            if i < 0 or i >= n or i in visited:
                return False
            
            # Target reached
            if arr[i] == 0:
                return True
            
            visited.add(i)
            jump = arr[i]
            
            # Recurse on left and right options
            return dfs(i + jump) or dfs(i - jump)

        return dfs(start)
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Recursion Stack Limit
*   In the worst case (e.g., an array where each step is $1$ and elements are chained sequentially), the maximum depth of recursion is $N$ (up to $5 \times 10^4$ according to constraints).
*   Python's default recursion limit is $1000$. A deep DFS search will trigger a `RecursionError`.
*   **Workaround**: You can increase Python's recursion limit using `sys.setrecursionlimit(200000)`, or rewrite the traversal iteratively using an explicit stack (DFS) or queue (BFS) to avoid stack overflow.

### 2. Visited Collection Performance
*   Using a standard Python `set` has an average $\mathcal{O}(1)$ insertion and lookup time, but can suffer from hashing collisions and high memory overhead (each element in a set requires about $24-32$ bytes of metadata).
*   Alternatively, using a list of booleans like `visited = [False] * len(arr)` is faster, has no hash overhead, and requires significantly less memory ($1$ byte reference per element).

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | We visit each index at most once. For each index, we do $\mathcal{O}(1)$ checks and operations. |
| **Space Complexity** | $\mathcal{O}(n)$ | Due to the recursion call stack and the `visited` array/set, which scale linearly with the size of the input. |

---

## Common Follow-Up Questions & How to Answer

### Q1: How can we solve this problem in $\mathcal{O}(1)$ auxiliary space?
*   **Answer**: If we are allowed to mutate the input array `arr`, we can mark an index `i` as visited by changing `arr[i]` to its negative counterpart `arr[i] = -arr[i]`. Since all values are originally non-negative, any negative value indicates a visited state.
*   **Python Code Implementation**:
    ```python
    def canReach(self, arr: List[int], start: int) -> bool:
        if start < 0 or start >= len(arr) or arr[start] < 0:
            return False
        if arr[start] == 0:
            return True
        
        # Save value, negate it in-place to mark as visited
        val = arr[start]
        arr[start] = -arr[start]
        
        return self.canReach(arr, start + val) or self.canReach(arr, start - val)
    ```

### Q2: Write the Breadth-First Search (BFS) solution. How does BFS compare to DFS here?
*   **Answer**: BFS is also $\mathcal{O}(n)$ time and space but searches level-by-level, which will find the shortest path of jumps to reach the target index.
*   **C++ BFS Implementation**:
    ```cpp
    #include <vector>
    #include <queue>

    class Solution {
    public:
        bool canReach(const std::vector<int>& arr, int start) {
            int n = arr.size();
            std::queue<int> q;
            std::vector<char> visited(n, 0);

            q.push(start);
            visited[start] = 1;

            while (!q.empty()) {
                int curr = q.front();
                q.pop();

                if (arr[curr] == 0) return true;

                for (int next_idx : {curr + arr[curr], curr - arr[curr]}) {
                    if (next_idx >= 0 && next_idx < n && !visited[next_idx]) {
                        visited[next_idx] = 1;
                        q.push(next_idx);
                    }
                }
            }
            return false;
        }
    };
    ```

---

## Pro-Tip: How to Impress the Interviewer

*   **Avoid `std::vector<bool>`**: In C++, explain why you used `std::vector<char>` or `std::vector<uint8_t>` instead of `std::vector<bool>`. `std::vector<bool>` is space-optimized (packed as a bitmask) and returns proxy references rather than real pointers or references. This makes it incompatible with some standard library functions and can introduce thread-safety issues.
*   **Tail Recursion and Compiler Optimization**: Notice that the DFS implementation is NOT tail-recursive because it performs a logical OR operation after the recursive calls (`dfs(...) || dfs(...)`). Therefore, the compiler cannot perform tail-call optimization (TCO). Highlighting this shows deep knowledge of assembly and compiler architecture.
