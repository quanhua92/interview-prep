# Task Scheduler

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / AI Systems Architect
- **Source**: LeetCode 621, Glassdoor

---

## Question Description

You are given an array of CPU tasks, each labeled with a letter from A to Z, and a cooldown interval $n$. Each CPU interval can be idle or allow the completion of one task. Tasks can be completed in any order, but there's a constraint: there has to be a gap of at least $n$ intervals between two tasks with the same label.

Return the *minimum number of CPU intervals* required to complete all tasks.

### Examples
*   **Input**: `tasks = ["A","A","A","B","B","B"]`, `n = 2`
    *   **Output**: `8`
    *   **Explanation**: A possible optimal sequence is: `A -> B -> idle -> A -> B -> idle -> A -> B`. After completing task A, you must wait 2 intervals before doing A again. The same applies to task B.
*   **Input**: `tasks = ["A","C","A","B","D","B"]`, `n = 1`
    *   **Output**: `6`
    *   **Explanation**: A possible sequence is: `A -> B -> C -> D -> A -> B`. No idle intervals are required.
*   **Input**: `tasks = ["A","A","A","B","B","B"]`, `n = 3`
    *   **Output**: `10`
    *   **Explanation**: A possible sequence is: `A -> B -> idle -> idle -> A -> B -> idle -> idle -> A -> B`.

---

## Detailed Solution (C++)

The problem can be solved mathematically by focusing on the most frequent tasks.

### Mathematical Formula Intuition
1. Let the highest frequency of any task be `max_freq`. Let $A$ be one of these tasks.
2. To schedule $A$ with a gap of at least $n$ intervals, we create `max_freq - 1` partitions. Each partition must have a size of `n + 1` (containing $A$ itself followed by $n$ slots for other tasks or idle periods).
3. The last partition only needs to accommodate the final occurrences of the tasks that share the maximum frequency (`max_count`).
4. Thus, the minimum length of the layout is:
   $$\text{Formula} = (\text{max\_freq} - 1) \times (n + 1) + \text{max\_count}$$
5. If we have more tasks than can fit in these empty slots, we can insert them into the slots without increasing the required length beyond `tasks.size()`. Since there are enough distinct tasks, the scheduling will always be possible without any idle slots.
6. Therefore, the minimum intervals required is:
   $$\max(\text{tasks.size()}, (\text{max\_freq} - 1) \times (n + 1) + \text{max\_count})$$

### Standard C++ Production Code

```cpp
#include <vector>
#include <string>
#include <algorithm>

class Solution {
public:
    int leastInterval(std::vector<char>& tasks, int n) {
        // Frequency array for uppercase English letters A-Z
        int freq[26] = {0};
        for (char c : tasks) {
            freq[c - 'A']++;
        }

        // Find the maximum frequency
        int max_freq = 0;
        for (int i = 0; i < 26; ++i) {
            if (freq[i] > max_freq) {
                max_freq = freq[i];
            }
        }

        // Count how many tasks have this maximum frequency
        int max_count = 0;
        for (int i = 0; i < 26; ++i) {
            if (freq[i] == max_freq) {
                max_count++;
            }
        }

        // Apply the mathematical formula
        int part_count = max_freq - 1;
        int part_length = n + 1;
        int min_intervals = part_count * part_length + max_count;

        // The answer is the maximum of the formula and the total number of tasks
        return std::max(static_cast<int>(tasks.size()), min_intervals);
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the type-hinted Python implementation using `collections.Counter`.

```python
from typing import List
from collections import Counter

class Solution:
    def leastInterval(self, tasks: List[str], n: int) -> int:
        """
        Calculates the minimum intervals required to complete all tasks with cooldown n.
        
        Time Complexity: O(N) where N is the number of tasks
        Space Complexity: O(1) auxiliary (at most 26 unique task keys)
        """
        if not tasks:
            return 0

        freq = Counter(tasks)
        max_freq = max(freq.values())
        
        # Count how many tasks share the maximum frequency
        max_count = sum(1 for v in freq.values() if v == max_freq)
        
        formula = (max_freq - 1) * (n + 1) + max_count
        return max(len(tasks), formula)
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Python Character Arithmetic
*   Unlike C++ where we can map characters directly to indices via `c - 'A'`, Python does not support character subtraction. 
*   We must use `ord(c) - ord('A')` to convert characters to integer indices. Using `collections.Counter` avoids this character conversion overhead altogether by hashing the task string values directly.

### 2. Generator Expression Overhead vs List Comprehension
*   `sum(1 for v in freq.values() if v == max_freq)` uses a generator expression to calculate the count. 
*   For small dataset sizes (e.g., at most 26 unique characters), a list comprehension like `sum([1 for v in freq.values() if v == max_freq])` can be slightly faster in Python due to lower overhead in creating the generator object, although a generator is more memory-friendly for massive datasets.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | Where $n$ is the total number of tasks. We perform a single pass to count task frequencies. |
| **Space Complexity** | $\mathcal{O}(1)$ | The alphabet size is fixed to 26 letters, requiring constant storage. |

---

## Common Follow-Up Questions & How to Answer

### Q1: How would you construct and return the actual scheduled sequence of tasks?
*   **Answer**: To construct the actual task sequence, we use a **Max-Heap** and a **Queue**:
    1. Count frequencies and push all task counts and characters into a max-heap as `(frequency, task_char)`.
    2. Maintain a queue to store tasks that are on cooldown, keeping track of the time they become available again: `(remaining_frequency, task_char, next_available_time)`.
    3. At each time step `t`:
       * Check if any task at the front of the cooldown queue is ready (`next_available_time <= t`). If so, pop it and push it back onto the max-heap.
       * If the max-heap is not empty, pop the most frequent task, append it to our result, decrement its frequency, and if its frequency is still $>0$, push it to the cooldown queue with `next_available_time = t + n + 1`.
       * If the max-heap is empty, append `"idle"`.
       * Increment `t`.

### Q2: What if tasks have precedence dependencies (e.g. Task B can only start after Task A finishes)?
*   **Answer**: This is a DAG Scheduling problem with communication/cooldown delays. We would combine **Topological Sort (Kahn's Algorithm)** with the greedy scheduling approach. A task can only be pushed into the max-heap when all its incoming dependency tasks are completed and its cooldown constraint is satisfied.

---

## Pro-Tip: How to Impress the Interviewer

*   **Explain the Math-Greedy Duality**: Explain to the interviewer that while a simulation using a max-heap and queue is intuitive and necessary if we need to output the schedule itself, the math formula method runs in $\mathcal{O}(N)$ time and $\mathcal{O}(1)$ auxiliary space, compared to the simulation's $\mathcal{O}(TotalTime \cdot \log 26)$. Since $TotalTime$ can be much larger than $N$ (due to $n$ and idles), the math solution is infinitely faster for large cooldown values.
*   **Discuss Alphabet Size Generality**: Mention that the solution generalizes to any alphabet size $|\Sigma|$ (not just 26). The time complexity remains $\mathcal{O}(N + |\Sigma|)$ and space complexity $\mathcal{O}(|\Sigma|)$.
*   **SIMD Vectorization potential in C++**: Point out that the C++ loop to count frequencies can easily be vectorized by modern compilers since it operates on a contiguous block of data.
