# Tier 4: Expert — Coding Interview Preparation Roadmap

Welcome to the **Expert (Tier 4) Coding Roadmap**. This directory serves as your structured study guide and indexed reference repository for advanced/expert-level algorithmic design. These patterns cover complex multi-dimensional traversals, graph connectivity and dependency modeling, greedy heuristics, and monotonic limits.

---

## 🗺️ Progression Roadmap

To build expert problem-solving intuition, start with spatial 2D matrix indexes, progress to network graphs and connectivity structures, then explore greedy choice intervals and monotonic boundary limits.

```text
┌────────────────────────────────────────┐
│  Step 1: Spatial Indices               │
│  (Matrix Traversal)                    │
└────────────────────┬───────────────────┘
                     │
                     ▼
┌────────────────────────────────────────┐
│  Step 2: Dependency & Connectivity     │
│  (Graph & Union Find)                  │
└────────────────────┬───────────────────┘
                     │
                     ▼
┌────────────────────────────────────────┐
│  Step 3: Interval Choice & Scheduling  │
│  (Greedy Algorithms)                   │
└────────────────────┬───────────────────┘
                     │
                     ▼
┌────────────────────────────────────────┐
│  Step 4: Boundary Limits               │
│  (Monotonic Stack)                     │
└────────────────────────────────────────┘
```

---

## 📈 Detailed Learning Modules & File Index

Here is the complete catalog of the 24 Expert problems, categorized by pattern, and arranged in recommended learning order.

### Module 1: Matrix Traversal
*Goal: Manipulate 2D coordinate spaces, perform in-place spatial rotations, and resolve multi-source BFS grid maps.*

| Pattern | Problem Name | Source | Difficulty | Core Concepts |
| :--- | :--- | :--- | :--- | :--- |
| **Matrix Traversal** | [Rotate Image](file:///Users/quan/workspace/interview-prep/popular/tiers/expert/coding_rotate_image.md) | [LeetCode 48](https://leetcode.com/problems/rotate-image/) | Medium | Matrix transpose and horizontal reflection, in-place swaps |
| **Matrix Traversal** | [Spiral Matrix](file:///Users/quan/workspace/interview-prep/popular/tiers/expert/coding_spiral_matrix.md) | [LeetCode 54](https://leetcode.com/problems/spiral-matrix/) | Medium | Index-boundary shrinking (top/bottom/left/right) |
| **Matrix Traversal** | [Diagonal Traverse](file:///Users/quan/workspace/interview-prep/popular/tiers/expert/coding_diagonal_traverse.md) | [LeetCode 498](https://leetcode.com/problems/diagonal-traverse/) | Medium | Index sum grouping ($r + c = \text{const}$), direction flips |
| **Matrix Traversal** | [01 Matrix](file:///Users/quan/workspace/interview-prep/popular/tiers/expert/coding_01_matrix.md) | [LeetCode 542](https://leetcode.com/problems/01-matrix/) | Medium | Multi-source BFS, 2D dynamic programming distance |

### Module 2: Dependency (Graph) & Connectivity (Union Find)
*Goal: Model dependency relationships, sort topological constraints, check cycles, and evaluate partition groups.*

| Pattern | Problem Name | Source | Difficulty | Core Concepts |
| :--- | :--- | :--- | :--- | :--- |
| **Graph** | [Course Schedule](file:///Users/quan/workspace/interview-prep/popular/tiers/expert/coding_course_schedule.md) | [LeetCode 207](https://leetcode.com/problems/course-schedule/) | Medium | Cycle detection in directed graphs, Kahn's BFS, DFS colors |
| **Graph** | [Course Schedule II](file:///Users/quan/workspace/interview-prep/popular/tiers/expert/coding_course_schedule_ii.md) | [LeetCode 210](https://leetcode.com/problems/course-schedule-ii/) | Medium | Topological sort order, in-degree arrays, DFS stack |
| **Graph** | [Find the Town Judge](file:///Users/quan/workspace/interview-prep/popular/tiers/expert/coding_town_judge.md) | [LeetCode 997](https://leetcode.com/problems/find-the-town-judge/) | Easy | Vertex in-degree/out-degree balance, array index mapping |
| **Union Find** | [Number of Connected Components](file:///Users/quan/workspace/interview-prep/popular/tiers/expert/coding_connected_components.md) | [LeetCode 323](https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/) | Medium | Disjoint Set Union (DSU) parent pointers, component count |
| **Union Find** | [Redundant Connection](file:///Users/quan/workspace/interview-prep/popular/tiers/expert/coding_redundant_connection.md) | [LeetCode 684](https://leetcode.com/problems/redundant-connection/) | Medium | DSU cycle detection, path compression |
| **Union Find** | [Satisfiability of Equality Equations](file:///Users/quan/workspace/interview-prep/popular/tiers/expert/coding_satisfiability_equations.md) | [LeetCode 990](https://leetcode.com/problems/satisfiability-of-equality-equations/) | Medium | DSU partition equivalence, inequality validation check |

### Module 3: Greedy Choice & Scheduling
*Goal: Make locally optimal choices (sorting, heaps, activity selections) to resolve globally optimal schedules and allocations.*

| Pattern | Problem Name | Source | Difficulty | Core Concepts |
| :--- | :--- | :--- | :--- | :--- |
| **Greedy** | [Jump Game](file:///Users/quan/workspace/interview-prep/popular/tiers/expert/coding_jump_game.md) | [LeetCode 55](https://leetcode.com/problems/jump-game/) | Medium | Maximum reachable index tracking, linear scan |
| **Greedy** | [Gas Station](file:///Users/quan/workspace/interview-prep/popular/tiers/expert/coding_gas_station.md) | [LeetCode 134](https://leetcode.com/problems/gas-station/) | Medium | Continuous index sum, starting point tracking, total balance |
| **Greedy** | [Candy](file:///Users/quan/workspace/interview-prep/popular/tiers/expert/coding_candy.md) | [LeetCode 135](https://leetcode.com/problems/candy/) | Hard | Dual-pass rating differentials (left-to-right, right-to-left) |
| **Greedy** | [Min Arrows to Burst Balloons](file:///Users/quan/workspace/interview-prep/popular/tiers/expert/coding_minimum_number_of_arrows_to_burst_balloons.md) | [LeetCode 452](https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/) | Medium | Interval sorting by end point, coordinate overlap greedy choice |
| **Greedy** | [Assign Cookies](file:///Users/quan/workspace/interview-prep/popular/tiers/expert/coding_assign_cookies.md) | [LeetCode 455](https://leetcode.com/problems/assign-cookies/) | Easy | Dual sorting, two-pointer greedy allocation match |
| **Greedy** | [IPO](file:///Users/quan/workspace/interview-prep/popular/tiers/expert/coding_ipo.md) | [LeetCode 502](https://leetcode.com/problems/ipo/) | Hard | Capital min-heap sort, project profit max-heap stream |
| **Greedy** | [Task Scheduler](file:///Users/quan/workspace/interview-prep/popular/tiers/expert/coding_task_scheduler.md) | [LeetCode 621](https://leetcode.com/problems/task-scheduler/) | Medium | Max-frequency mapping math, idle slot counting |
| **Greedy** | [Task Scheduler Multi-Machine](file:///Users/quan/workspace/interview-prep/popular/tiers/expert/coding_task_scheduler_multi_machine.md) | Custom | Hard | Multi-processor task sorting, earliest-available machine heaps |

### Module 4: Monotonic Stack (Boundary Limits)
*Goal: Manage non-increasing/non-decreasing value/index arrays to find the nearest smaller/larger elements in $\mathcal{O}(n)$ time.*

| Pattern | Problem Name | Source | Difficulty | Core Concepts |
| :--- | :--- | :--- | :--- | :--- |
| **Monotonic Stack** | [Largest Rectangle in Histogram](file:///Users/quan/workspace/interview-prep/popular/tiers/expert/coding_largest_rectangle.md) | [LeetCode 84](https://leetcode.com/problems/largest-rectangle-in-histogram/) | Hard | Non-decreasing height indices stack, width calculation |
| **Monotonic Stack** | [132 Pattern](file:///Users/quan/workspace/interview-prep/popular/tiers/expert/coding_132_pattern.md) | [LeetCode 456](https://leetcode.com/problems/132-pattern/) | Medium | Decreasing stack value, third element candidates search |
| **Monotonic Stack** | [Next Greater Element II](file:///Users/quan/workspace/interview-prep/popular/tiers/expert/coding_next_greater_element_ii.md) | [LeetCode 503](https://leetcode.com/problems/next-greater-element-ii/) | Medium | Circular array indexing (modulo $2n$), value stack |
| **Monotonic Stack** | [Daily Temperatures](file:///Users/quan/workspace/interview-prep/popular/tiers/expert/coding_daily_temperatures.md) | [LeetCode 739](https://leetcode.com/problems/daily-temperatures/) | Medium | Decreasing value indices stack, index offset calculations |
| **Monotonic Stack** | [Car Fleet](file:///Users/quan/workspace/interview-prep/popular/tiers/expert/coding_car_fleet.md) | [LeetCode 853](https://leetcode.com/problems/car-fleet/) | Medium | Sorting by position, monotonic decrease of target times |
| **Monotonic Stack** | [Sum of Subarray Minimums](file:///Users/quan/workspace/interview-prep/popular/tiers/expert/coding_sum_of_subarray_minimums.md) | [LeetCode 907](https://leetcode.com/problems/sum-of-subarray-minimums/) | Medium | Ple/Nle (previous/next lesser element) bounds, count products |

---

## 💡 Expert Tier Interview Strategy

### 1. Topological Sorting: Kahn's BFS vs. DFS
*   **Kahn's BFS**: Preferred when you need to detect cycles explicitly and process items in exactly the order of their dependency satisfaction level (e.g. printing topological sequence). Utilizes an in-degree array.
*   **DFS Color States**: Use color states (0=unvisited, 1=visiting, 2=visited) to identify back-edges (cycles) in directed graphs. DFS uses less memory in sparse trees but can overflow recursion limits.

### 2. Disjoint Set Union (DSU) Optimizations
*   **Path Compression**: In the `find()` helper, recursively point child nodes directly to the root:
    ```cpp
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]); // Path compression
    }
    ```
*   **Union by Rank/Size**: Merge the smaller tree under the larger tree to keep tree heights bounded by $\mathcal{O}(\alpha(n))$ (Inverse Ackermann complexity, practically $\le 4$).

### 3. Monotonic Stack index mappings
*   **Store Indices, Not Values**: Always store the *indices* of the array elements on the monotonic stack rather than the raw values. Storing indices allows you to compute distances/widths (as in Daily Temperatures or Largest Rectangle) and fetch raw values directly (`nums[stack.top()]`).
*   **Sentinel Elements**: To avoid checking for empty stacks during cleanup loops, append a sentinel element (e.g., `-1` or `0` for values) at the end of the input array. This forces the stack to flush and process all remaining items automatically.
