# Find the Town Judge

- **Category**: Coding
- **Difficulty**: Easy
- **Target Role**: Software Engineer / QA & Test Engineer
- **Source**: LeetCode 997, Glassdoor

---

## Question Description

In a town, there are `n` people labeled from `1` to `n`. There is a rumor that one of these people is secretly the town judge.

If the town judge exists, then:
1.  The town judge trusts nobody.
2.  Everybody (except for the town judge) trusts the town judge.
3.  There is exactly one person that satisfies properties 1 and 2.

You are given an array `trust` where `trust[i] = [ai, bi]` representing that the person labeled `ai` trusts the person labeled `bi`.

Return the label of the town judge if the town judge exists and can be identified, or return `-1` otherwise.

### Examples
*   **Input**: `n = 2`, `trust = [[1,2]]`
    *   **Output**: `2`
*   **Input**: `n = 3`, `trust = [[1,3],[2,3]]`
    *   **Output**: `3`
*   **Input**: `n = 3`, `trust = [[1,3],[2,3],[3,1]]`
    *   **Output**: `-1`

---

## Detailed Solution (C++)

The town judge problem can be modeled as finding a node in a directed graph with an **in-degree** of $n - 1$ and an **out-degree** of $0$.
*   If person $A$ trusts person $B$, there is a directed edge from $A \to B$.
*   This edge increases the out-degree of $A$ and increases the in-degree of $B$.

Rather than tracking in-degree and out-degree separately, we can compute a single **trust score** for each person:
$$\text{trust\_score}[i] = \text{in\_degree}[i] - \text{out\_degree}[i]$$

*   If person $i$ trusts someone, we decrement their score: `scores[a]--`.
*   If person $i$ is trusted by someone, we increment their score: `scores[b]++`.
*   The town judge must have a score of exactly $n - 1$ because they are trusted by all other $n - 1$ people (in-degree = $n - 1$) and trust no one (out-degree = $0$).

### Standard C++ Production Code

```cpp
#include <vector>

class Solution {
public:
    int findJudge(int n, std::vector<std::vector<int>>& trust) {
        // trust scores vector size n + 1 (1-indexed matching people labels)
        std::vector<int> scores(n + 1, 0);

        for (const auto& relation : trust) {
            int a = relation[0];
            int b = relation[1];
            scores[a]--; // Out-degree contribution
            scores[b]++; // In-degree contribution
        }

        for (int i = 1; i <= n; ++i) {
            if (scores[i] == n - 1) {
                return i;
            }
        }

        return -1;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

```python
from typing import List

class Solution:
    def findJudge(self, n: int, trust: List[List[int]]) -> int:
        """
        Finds the town judge using a single trust score array.
        
        Time Complexity: O(T + N) where T is length of trust and N is number of people.
        Space Complexity: O(N) for the score table.
        """
        scores = [0] * (n + 1)
        
        for a, b in trust:
            scores[a] -= 1
            scores[b] += 1
            
        for i in range(1, n + 1):
            if scores[i] == n - 1:
                return i
                
        return -1
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. 1-Based Indexing vs 0-Based Indexing
*   The problem uses 1-based indexing for people ($1$ to $n$). In Python, it is cleaner to allocate an array of size $n+1$ rather than performing index shifts (e.g. `i - 1`), which can introduce off-by-one errors.
*   The minor space overhead of $1$ extra element is negligible compared to code readability and safety benefits.

### 2. Hash Map vs List for Low Space Overhead
*   If $n$ is very large (e.g. $10^9$) but the trust array is small, allocating an array of size $n+1$ would consume too much memory.
*   In such a case, using a `collections.defaultdict(int)` to track trust scores is highly space-efficient, reducing auxiliary space to $\mathcal{O}(U)$ where $U$ is the number of unique participants in the trust list.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(N + T)$ | We iterate through the trust array of size $T$ once, then perform a linear scan of size $N$ to find the judge. |
| **Space Complexity** | $\mathcal{O}(N)$ | We store a trust score array of size $N + 1$. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What is the relationship between this and the "Celebrity Problem"?
*   **Answer**: This problem is a variant of the **Celebrity Problem**. A celebrity is someone who is known by everyone but knows no one.
*   While we are given a static trust array here, in the Celebrity Problem we are given a helper function `knows(A, B)`.
*   We can find the celebrity in $\mathcal{O}(N)$ time and $\mathcal{O}(1)$ space using a **Two-Pointer elimination** strategy:
    1.  Initialize candidate `c = 1`.
    2.  For `i` from `2` to `n`: if `knows(c, i)`, then `c` knows someone and cannot be the celebrity. So update candidate `c = i`. If `knows(c, i)` is false, `i` is not known by `c`, so `i` cannot be the celebrity (celebrity is known by everyone). Thus, keep `c`.
    3.  Verify the final candidate `c` by checking if `knows(c, i)` is false and `knows(i, c)` is true for all $i \neq c$.

### Q2: What if we have a streaming flow of trust events?
*   **Answer**: If trust relationships are added dynamically:
    1.  Maintain the in-degree and out-degree using a hash map or direct-address table.
    2.  Keep a pointer to the current candidate judge.
    3.  If the candidate judge trusts someone (out-degree > 0), they are disqualified.
    4.  If a new edge is added, update degrees. Check if the updated destination node meets the conditions (out-degree == 0 and in-degree == $N-1$).

---

## Pro-Tip: How to Impress the Interviewer

*   **Avoid Double Allocations**: Many candidates allocate two separate arrays for `inDegree` and `outDegree`. Proactively explain that a single array tracking the difference `inDegree - outDegree` is sufficient because the only valid configuration for a judge is to have out-degree $0$ and in-degree $n-1$, which unique maps to a score of $n-1$.
*   **Mention Cache Line Locality**: Using a flat `std::vector` of size $n+1$ in C++ ensures all elements are contiguous in memory. This allows the CPU to fetch multiple scores into a single L1 cache line, making the second lookup pass extremely fast.
