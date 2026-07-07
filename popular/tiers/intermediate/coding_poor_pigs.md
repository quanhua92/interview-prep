# Poor Pigs

- **Category**: Coding
- **Difficulty**: Hard
- **Target Role**: Software Engineer / AI Systems Architect
- **Source**: LeetCode 458, Glassdoor

---

## Question Description

There are `buckets` buckets of liquid, where exactly one of the buckets is poisonous. To figure out which one is poisonous, you feed some number of pigs the liquid to see whether they will die or not. Unfortunately, you only have `minutesToTest` minutes to determine which bucket is poisonous.

You can feed the pigs according to these steps:
1. Choose some number of pigs to feed.
2. For each pig, choose which buckets to feed it. The pig will consume all chosen buckets simultaneously and instantly. Each bucket can be fed to any number of pigs, and each pig can consume any number of buckets.
3. Wait for `minutesToDie` minutes. During this time, any pig that consumed the poison will die, and all other pigs survive.
4. If you still have time left, you can repeat this process with the surviving pigs (using new buckets).
5. You can test at most $\lfloor \frac{\text{minutesToTest}}{\text{minutesToDie}} \rfloor$ times.

Given `buckets`, `minutesToDie`, and `minutesToTest`, return the *minimum* number of pigs needed to figure out which bucket is poisonous within the allotted time.

### Examples
*   **Input**: `buckets = 4`, `minutesToDie = 15`, `minutesToTest = 15`
    *   **Output**: `2`
    *   **Explanation**: 
        *   At time 0, feed the first pig buckets 1 and 2, and feed the second pig buckets 2 and 3.
        *   At time 15, there are 4 possible outcomes:
            *   If only the first pig dies, bucket 1 is poisonous.
            *   If only the second pig dies, bucket 3 is poisonous.
            *   If both pigs die, bucket 2 is poisonous.
            *   If neither pig dies, bucket 4 is poisonous.
*   **Input**: `buckets = 4`, `minutesToDie = 15`, `minutesToTest = 30`
    *   **Output**: `2`
    *   **Explanation**: We have 2 test rounds ($30 / 15 = 2$). With 2 pigs, we can test up to 9 buckets, so 2 pigs are sufficient for 4 buckets.

---

## Detailed Solution (C++)

This is fundamentally an **information theory** and **base-$k$ representation** problem:
1. Let $T = \lfloor \frac{\text{minutesToTest}}{\text{minutesToDie}} \rfloor$ be the number of test rounds available.
2. For each pig, there are exactly $T + 1$ possible outcomes (states) at the end of the entire test process:
   * It dies in round 1.
   * It dies in round 2.
   * ...
   * It dies in round $T$.
   * It survives all rounds.
3. If we have $P$ pigs, each pig behaves independently. Therefore, the total number of distinct joint states we can distinguish is:
   $$\text{States} = (T + 1)^P$$
4. To uniquely identify which of the $N$ buckets is poisonous, the number of distinct joint states must be greater than or equal to $N$:
   $$(T + 1)^P \ge N$$
5. We need to find the smallest integer $P$ satisfying this inequality. We can find this by iteratively multiplying $(T+1)$ until the value meets or exceeds `buckets`. This avoids any floating-point precision issues that might arise from using `std::log` or `std::pow`.

### Standard C++ Production Code

```cpp
#include <limits>

class Solution {
public:
    int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
        if (buckets <= 1) {
            return 0;
        }

        int tests = minutesToTest / minutesToDie;
        int pigs = 0;
        long long base = tests + 1;
        long long max_buckets_distinguished = 1;

        while (max_buckets_distinguished < buckets) {
            // Prevent integer overflow during multiplication
            if (max_buckets_distinguished > (std::numeric_limits<long long>::max() / base)) {
                break;
            }
            max_buckets_distinguished *= base;
            pigs++;
        }

        return pigs;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the Python implementation.

```python
import math

class Solution:
    def poorPigs(self, buckets: int, minutesToDie: int, minutesToTest: int) -> int:
        """
        Determines the minimum number of pigs needed to find the poisonous bucket.
        
        Time Complexity: O(log_(T+1) N)
        Space Complexity: O(1)
        """
        if buckets <= 1:
            return 0

        # Number of rounds we can perform
        rounds = minutesToTest // minutesToDie
        base = rounds + 1
        
        # We need to find smallest P such that base^P >= buckets
        # This is equivalent to P = ceil(log(buckets) / log(base))
        # To avoid floating point inaccuracy, we can use a loop or integer power comparison.
        pigs = 0
        current_limit = 1
        while current_limit < buckets:
            current_limit *= base
            pigs += 1
            
        return pigs
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Floating-Point Precision Risk with `math.log`
*   A naive mathematical solution is:
    ```python
    return math.ceil(math.log(buckets) / math.log(rounds + 1))
    ```
*   **Warning**: Floating-point division and logarithmic approximations can lead to precision errors for boundary numbers. For example, `math.log(125) / math.log(5)` might return `2.9999999999999996` due to IEEE-754 precision limits, and applying `math.ceil` would mistakenly round it up to `3` instead of `3` directly (or round `3.0000000000000004` up to `4`).
*   Using integer multiplication `current_limit *= base` in a loop guarantees exact integer evaluation and is completely free of floating-point precision issues.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(\log_{T+1} n)$ | The loop runs at most $\approx 15$ times since the base is at least $2$ and $N \le 1000$ (with $2^{10} = 1024$). |
| **Space Complexity** | $\mathcal{O}(1)$ | Only a few scalar variables are maintained. |

---

## Common Follow-Up Questions & How to Answer

### Q1: How do we actually schedule the feedings (the experiment design)?
*   **Answer**: 
    1. Represent each bucket's ID (from $0$ to $N-1$) in base-$(T+1)$ notation. Each bucket will have a coordinates representation $(d_0, d_1, \dots, d_{P-1})$, where each digit $d_i \in [0, T]$.
    2. Pig $i$ is responsible for the $i$-th dimension (or digit position).
    3. In round $r$ (for $r \in [1, T]$), pig $i$ drinks from all buckets where the $i$-th digit $d_i$ is equal to $r-1$.
    4. If pig $i$ dies in round $r$, we know the poisonous bucket's $i$-th digit is $r-1$.
    5. If pig $i$ survives all $T$ rounds, the poisonous bucket's $i$-th digit must be $T$.
    6. By combining the survival/death round of all $P$ pigs, we get the exact base-$(T+1)$ digits of the poisonous bucket.

### Q2: What if pigs can recover after a round?
*   **Answer**: The problem explicitly states that once a pig consumes the poison, it dies and cannot be reused. If recovery were possible, it would increase the number of states per pig and dramatically decrease the number of pigs needed.

---

## Pro-Tip: How to Impress the Interviewer

*   **Explain the Multidimensional Grid (Hypercube)**: Explain the problem using a spatial coordinate analogy. For $P$ pigs and $T$ rounds, think of the state space as a $P$-dimensional hypercube of side length $T+1$. Each cell in this hypercube corresponds to a bucket. Each pig controls one axis. In each round $r$, a pig drinks the "slice" perpendicular to its axis at coordinate $r-1$. The point of intersection of the "dead slices" (or survival on that axis) uniquely identifies the single poisonous cell. This geometric interpretation shows a profound intuition for multi-dimensional coding theory.
*   **Proactively Address IEEE-754 Precision**: Point out the risk of using `log` or `pow` with float math and explain how the integer loop completely avoids this vulnerability. Interviewers love engineers who write defensively against float precision bugs.
