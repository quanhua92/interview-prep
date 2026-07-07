# Task Scheduler with Multiple Machines

- **Category**: Coding
- **Difficulty**: Hard
- **Target Role**: Software Engineer / AI Systems Architect
- **Source**: LeetCode 621 (Extension), Glassdoor

---

## Question Description

You are given an array of CPU tasks, each labeled with a letter from A to Z, a cooldown period $n$, and $m$ identical parallel machines.

Each machine can execute at most one task per time interval. Tasks can be completed in any order across the machines. Cooldown is tracked **per-machine**: if machine $M$ runs task $A$ at time $t$, that machine $M$ cannot run task $A$ again until time $t + n + 1$. Other machines are unaffected and may run task $A$ at any time (including simultaneously with $M$).

Return the *minimum number of time intervals* required to complete all tasks across all $m$ machines.

### Examples
*   **Input**: `tasks = ["A","A","A","B","B","B"]`, `n = 2`, `m = 1`
    *   **Output**: `8`
    *   **Explanation**: This is the original LeetCode 621 problem.
        *   `A -> B -> idle -> A -> B -> idle -> A -> B`
*   **Input**: `tasks = ["A","A","A","B","B","B"]`, `n = 2`, `m = 2`
    *   **Output**: `4`
    *   **Explanation**: Cooldown is per-machine, so machines can swap tasks.
        *   `t=0`: M1=A, M2=B
        *   `t=1`: M1=B, M2=A (M1 never ran B, and M2 never ran A)
        *   `t=2`: idle (both machines must wait cooldown)
        *   `t=3`: M1=A, M2=B
*   **Input**: `tasks = ["A","C","A","B","D","B"]`, `n = 1`, `m = 2`
    *   **Output**: `3`
    *   **Explanation**:
        *   `t=0`: M1=A, M2=B
        *   `t=1`: M1=C, M2=D
        *   `t=2`: M1=A, M2=B

---

## Detailed Solution (C++)

With multiple machines and per-machine cooldown constraints, we cannot use a simple single-variable mathematical formula. Instead, we must simulate the scheduling process using a **Greedy Simulation with Discrete-Event Time Skipping**:

1. **Greedy Strategy**: At each time interval $t$, we attempt to assign tasks to each of the $m$ machines. For each machine $i$ (from $0$ to $m-1$), we look for the highest-frequency remaining task that is not on cooldown on that specific machine $i$.
2. **State Tracking**:
   * We keep an array `freq` of size 26 representing the remaining count of each task.
   * We maintain a 2D matrix `cooldown[m][26]` where `cooldown[mi][t]` stores the next time step machine `mi` is allowed to execute task `t`.
3. **Time Skip (Discrete-Event Optimization)**: If in a time interval $t$ we are unable to assign *any* task to *any* machine (meaning all remaining tasks are on cooldown on all machines), incrementing time by $1$ repeatedly leads to wasteful "busy-waiting" loops. Instead, we jump `time` directly to the next earliest cooldown expiry time among all active cooldowns.

### Standard C++ Production Code

```cpp
#include <vector>
#include <algorithm>
#include <climits>

class Solution {
public:
    int leastInterval(std::vector<char>& tasks, int n, int m) {
        int freq[26] = {0};
        for (char c : tasks) {
            freq[c - 'A']++;
        }

        // cooldown[mi][task] stores the next time machine mi can run task
        // Initialize to INT_MIN (meaning immediately runnable)
        std::vector<std::vector<int>> cooldown(m, std::vector<int>(26, INT_MIN));

        int time = 0;
        int remaining = static_cast<int>(tasks.size());

        while (remaining > 0) {
            bool assigned = false;

            // Greedily assign tasks to each machine at the current time step
            for (int mi = 0; mi < m; ++mi) {
                int best_task = -1;
                int best_count = 0;

                for (int t = 0; t < 26; ++t) {
                    if (freq[t] > best_count && cooldown[mi][t] <= time) {
                        best_task = t;
                        best_count = freq[t];
                    }
                }

                if (best_task >= 0) {
                    freq[best_task]--;
                    cooldown[mi][best_task] = time + n + 1;
                    remaining--;
                    assigned = true;
                }
            }

            if (assigned) {
                time++;
            } else {
                // Time Jump: Find the next earliest time a cooldown expires
                int next_time = INT_MAX;
                for (int mi = 0; mi < m; ++mi) {
                    for (int t = 0; t < 26; ++t) {
                        if (cooldown[mi][t] > time && cooldown[mi][t] < next_time) {
                            next_time = cooldown[mi][t];
                        }
                    }
                }
                time = next_time;
            }
        }

        return time;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the type-hinted Python implementation using a dense list of lists for optimal cooldown lookups.

```python
from typing import List
from collections import Counter

class Solution:
    def leastInterval(self, tasks: List[str], n: int, m: int) -> int:
        """
        Calculates the minimum CPU intervals to execute tasks on m parallel machines
        with a per-machine cooldown constraint of n.
        
        Time Complexity: O(T * m * 26) where T is the total active time steps.
        Space Complexity: O(m * 26) for tracking cooldown states.
        """
        freq = Counter(tasks)
        
        # cooldown[mi][task_index] stores the next available time for machine mi
        cooldown = [[0] * 26 for _ in range(m)]

        time = 0
        remaining = len(tasks)

        # Map character tasks to 0-25 index
        def task_to_idx(char: str) -> int:
            return ord(char) - ord('A')

        while remaining > 0:
            assigned = False

            for i in range(m):
                best_task = None
                best_count = 0
                
                for task, count in freq.items():
                    if count > best_count:
                        task_idx = task_to_idx(task)
                        if cooldown[i][task_idx] <= time:
                            best_task = task
                            best_count = count
                            
                if best_task:
                    freq[best_task] -= 1
                    if freq[best_task] == 0:
                        del freq[best_task]  # Clean up dictionary
                    
                    task_idx = task_to_idx(best_task)
                    cooldown[i][task_idx] = time + n + 1
                    remaining -= 1
                    assigned = True

            if assigned:
                time += 1
            else:
                # Fast forward to next cooldown expiry to prevent idle busy-loops
                next_time = min(
                    t for machine_cooldowns in cooldown 
                    for t in machine_cooldowns if t > time
                )
                time = next_time

        return time
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Dictionary Size Modification During Iteration
*   In Python, we cannot delete keys from a dictionary while iterating over it (doing so raises a `RuntimeError: dictionary changed size during iteration`). 
*   In our code, we iterate over `freq.items()`. When a task count reaches 0, we delete it using `del freq[best_task]`. However, this deletion occurs *outside* the inner loop that iterates over `freq.items()`, making it safe.

### 2. Dense Matrix `cooldown` vs List of Dictionaries
*   Using a dense 2D list `cooldown = [[0] * 26 for _ in range(m)]` is significantly faster than using a list of dicts `[{} for _ in range(m)]` because array indexing via integer offsets is much faster than hashing string keys inside nested loops.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(T \cdot m \cdot |\Sigma|)$ | Where $T$ is the number of time intervals, $m$ is the number of machines, and $|\Sigma| = 26$ is the task alphabet size. |
| **Space Complexity** | $\mathcal{O}(m \cdot |\Sigma|)$ | Required to maintain the per-machine cooldown matrix. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if the cooldown is global (shared across all machines) instead of per-machine?
*   **Answer**: If the cooldown is global (e.g. if machine 1 runs $A$, no machine can run $A$ for $n$ units), the problem becomes equivalent to the single-machine task scheduler but with a faster consumption rate. We can model this by running $m$ tasks per interval (if available and not on global cooldown) and scheduling them using a single global cooldown queue.

### Q2: How does this simulation scale if the number of unique task types is very large (e.g. $|\Sigma| \ge 10^5$)?
*   **Answer**: If $|\Sigma|$ is large, scanning all tasks linearly to find the `best_task` becomes too slow. We should replace the linear scan with a **Priority Queue (Max-Heap)** storing the remaining counts of tasks that are currently available. 
    *   We maintain a global max-heap of ready tasks.
    *   We maintain a cooldown list/queue per machine.
    *   At each step, we pop from the max-heap and assign it to the machine. If a machine cannot run the top task, we temporarily buffer the popped tasks until we find a task the machine is allowed to run, then push the buffer back into the heap.

---

## Pro-Tip: How to Impress the Interviewer

*   **Highlight the Discrete-Event Skipping Optimization**: In real-world systems engineering (e.g., job schedulers like Kubernetes, Mesos, or Yarn), time is not incremented unit-by-unit if all resources are blocked. Implementing the time-skip optimization (`time = next_time`) shows that you write production-ready, event-driven systems code rather than naive loops.
*   **Discuss Cache Alignment of the Cooldown Matrix**: In C++, since the matrix dimensions are small ($m \le 26$, $|\Sigma| = 26$), the entire `cooldown` matrix easily fits inside a single L1 cache line (which is typically 64 bytes for modern CPUs). Keeping the rows contiguous in memory ensures cache friendly access.
