# IPO

- **Category**: Coding
- **Difficulty**: Hard
- **Target Role**: Software Engineer / AI Systems Architect
- **Source**: LeetCode 502, Glassdoor

---

## Question Description

Suppose LeetCode will start its IPO soon. In order to sell a good price of its shares to Venture Capital, LeetCode would like to work on some projects to increase its capital before the IPO. Since it has limited resources, it can only finish at most $k$ distinct projects before the IPO. Help LeetCode design the best way to maximize its total capital after finishing at most $k$ distinct projects.

You are given $n$ projects where the $i$-th project has a pure profit `profits[i]` and a minimum capital of `capital[i]` is needed to start it.

Initially, you have $w$ capital. When you finish a project, you will obtain its pure profit and the profit will be added to your total capital.

Pick a list of at most $k$ distinct projects from given projects to maximize your final capital, and return the final maximized capital.

The answer is guaranteed to fit in a 32-bit signed integer.

### Examples
*   **Input**: `k = 2`, `w = 0`, `profits = [1,2,3]`, `capital = [0,1,1]`
    *   **Output**: `4`
    *   **Explanation**:
        *   Since your initial capital is 0, you can only start the project indexed 0.
        *   After finishing it, you obtain profit 1, and your capital becomes 1.
        *   With capital 1, you can either start the project indexed 1 or 2.
        *   Since you can choose at most 2 projects, you should choose project 2 to get the maximum capital.
        *   Total capital is 0 + 1 + 3 = 4.
*   **Input**: `k = 3`, `w = 0`, `profits = [1,2,3]`, `capital = [0,1,2]`
    *   **Output**: `6`

---

## Detailed Solution (C++)

The problem can be solved greedily using a **Min-Heap (or Sorting) + Max-Heap** combination:
1. **Sort Projects**: Combine `capital[i]` and `profits[i]` into pairs and sort them in ascending order of their required capital. This allows us to easily find which projects can be started given our current capital $w$.
2. **Track Available Projects**: Maintain a `max_heap` of profits. As our capital $w$ increases, we scan through the sorted projects and push the profits of all newly affordable projects (i.e., where `capital[i] <= w`) into the `max_heap`.
3. **Greedy Choice**: Out of all affordable projects in the `max_heap`, we greedily choose the one with the maximum profit. We pop it, add its profit to our capital $w$, and repeat this step up to $k$ times.
4. **Early Exit**: If at any step before $k$ projects the `max_heap` becomes empty (meaning we cannot afford any new projects and have no projects left in our pool), we terminate early and return $w$.

### Standard C++ Production Code

```cpp
#include <vector>
#include <queue>
#include <algorithm>

class Solution {
public:
    int findMaximizedCapital(int k, int w, std::vector<int>& profits, std::vector<int>& capital) {
        const int n = static_cast<int>(profits.size());
        
        // Pair projects as (capital, profit)
        std::vector<std::pair<int, int>> projects(n);
        for (int i = 0; i < n; ++i) {
            projects[i] = {capital[i], profits[i]};
        }

        // Sort projects by capital required (ascending)
        std::sort(projects.begin(), projects.end());

        // Max-heap to store profits of all currently affordable projects
        std::priority_queue<int> max_profit_heap;
        int idx = 0;

        for (int step = 0; step < k; ++step) {
            // Push all affordable projects into the max-heap
            while (idx < n && projects[idx].first <= w) {
                max_profit_heap.push(projects[idx].second);
                idx++;
            }

            // If we have no affordable projects, we cannot proceed further
            if (max_profit_heap.empty()) {
                break;
            }

            // Greedily pick the project with the highest profit
            w += max_profit_heap.top();
            max_profit_heap.pop();
        }

        return w;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the type-hinted Python implementation using `heapq` and negating profits to simulate a max-heap.

```python
from typing import List
import heapq

class Solution:
    def findMaximizedCapital(self, k: int, w: int, profits: List[int], capital: List[int]) -> int:
        """
        Maximizes the total capital after selecting at most k projects.
        
        Time Complexity: O(N log N + k log N)
        Space Complexity: O(N) to store projects pair list
        """
        # Zip and sort by capital
        projects = sorted(zip(capital, profits))
        
        # Min-heap simulated as max-heap by negating profits
        max_heap: List[int] = []
        idx = 0
        n = len(projects)

        for _ in range(k):
            # Push profits of all affordable projects (capital <= w)
            while idx < n and projects[idx][0] <= w:
                # Store negated profit to turn python's min-heap into a max-heap
                heapq.heappush(max_heap, -projects[idx][1])
                idx += 1
            
            # If no projects can be undertaken, exit early
            if not max_heap:
                break
            
            # Retrieve the project with the maximum profit
            w += -heapq.heappop(max_heap)

        return w
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Simulating Max-Heaps via Negation
*   Python's built-in `heapq` module only supports **Min-Heaps**. To simulate a **Max-Heap**, we negate the values before pushing them (`heapq.heappush(heap, -value)`) and negate them again when popping (`-heapq.heappop(heap)`).
*   Care must be taken with the sign conversion when working with objects or multiple fields (e.g. tuples). For example, a tuple `(-profit, capital)` will prioritize profit first (descending) and capital second (ascending).

### 2. Space Optimization using `zip`
*   In Python, `zip(capital, profits)` creates a generator. Passing it to `sorted()` creates a new list of tuples, which is highly efficient because the underlying sorting routine runs in C. 
*   However, this does copy the arrays into a new structure, consuming $\mathcal{O}(N)$ space. If memory is extremely tight, we can index a list of indices and sort it instead.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n \log n + k \log n)$ | Sorting the $n$ projects takes $\mathcal{O}(n \log n)$. In the worst case, we push and pop $n$ projects from the heap, taking $\mathcal{O}((n + k) \log n)$ time. |
| **Space Complexity** | $\mathcal{O}(n)$ | To store the combined capital-profit pairings and the heap elements. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if projects can be done multiple times?
*   **Answer**: If a project can be repeated infinitely, we don't need to track multiple projects in a heap. At any step, we just want to perform the single most profitable project that we can afford. In this case, we can use a Segment Tree or Binary Indexed Tree (BIT) to find the maximum profit element with `capital[i] <= w`, query/update it, or use dynamic programming if the state space is small.

### Q2: What if capital is deducted (i.e. starting a project has a transaction cost that is not refunded)?
*   **Answer**: In the current problem, capital $w$ is non-decreasing since we only need `capital[i] <= w` as a threshold, and then we get `profits[i]` back. If capital is actually *spent* (i.e. $w$ is decremented by `capital[i]` and incremented by `profits[i]`), our capital can fluctuate up and down. This variation makes the problem equivalent to the Knapsack problem with ordering dependencies, which is **NP-hard** and requires Dynamic Programming or Backtracking with pruning.

---

## Pro-Tip: How to Impress the Interviewer

*   **Explain the Monotonicity of Capital**: Explain that the greedy choice is optimal *because* our capital $w$ is monotonically non-decreasing. Since $w$ never decreases, any project that becomes affordable in step $t$ remains affordable in all future steps $t+1, t+2, \ldots$. This allows us to keep a single pointer `idx` moving forward through the sorted projects list, guaranteeing a total runtime of $\mathcal{O}(n \log n + k \log n)$ rather than $\mathcal{O}(n \cdot k)$.
*   **Prevent Double Heap Pushes**: Highlight that each project is pushed into the `max_profit_heap` at most once by keeping the `idx` pointer state persistent across iterations of the main $k$-loop. This is a critical optimization that prevents the algorithm from degrading to $\mathcal{O}(n \cdot k)$.
