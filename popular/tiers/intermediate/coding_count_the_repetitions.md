# Count The Repetitions

- **Category**: Coding
- **Difficulty**: Hard
- **Target Role**: Software Engineer / AI Systems Architect
- **Source**: LeetCode 466, Glassdoor

---

## Question Description

We define $str = [s, n]$ as the string $str$ which consists of the string $s$ concatenated $n$ times.
*   For example, `["abc", 3]` ="abcabcabc".

We define that string $s_1$ can be obtained from string $s_2$ if we can remove some characters from $s_2$ such that it becomes $s_1$.
*   For example, `"abc"` can be obtained from `"abdbec"` because of the underlined characters `"a_b_d_b_e_c_"`, but it cannot be obtained from `"acbbe"`.

You are given two strings $s_1$ and $s_2$ and two integers $n_1$ and $n_2$. You have the two strings $str_1 = [s_1, n_1]$ and $str_2 = [s_2, n_2]$.

Return the maximum integer $m$ such that $str = [str_2, m]$ can be obtained from $str_1$.

### Examples
*   **Input**: `s1 = "acb"`, `n1 = 4`, `s2 = "ab"`, `n2 = 2`
    *   **Output**: `2`
    *   **Explanation**:
        $str_1 = \text{"acbacbacbacb"}$
        $str_2 = \text{"abab"}$
        We can obtain $str = [\text{"abab"}, 2] = \text{"abababab"}$ from $str_1$.
*   **Input**: `s1 = "acb"`, `n1 = 1`, `s2 = "acb"`, `n2 = 1`
    *   **Output**: `1`

**Constraints**:
*   $1 \le s_1.\text{length}, s_2.\text{length} \le 100$
*   $s_1$ and $s_2$ consist of lowercase English letters.
*   $1 \le n_1, n_2 \le 10^6$

---

## Detailed Solution (C++)

For a brute-force approach, we could iterate through all copies of $s_1$ and match character-by-character with $s_2$. However, since $n_1 \le 10^6$ and the lengths of the strings are $100$, simulating the entire match can require up to $10^8$ operations, which is too slow in a high-concurrency setting.

### Cycle Detection (Pigeonhole Principle)
We can optimize this to run in $\mathcal{O}(|s_1| \cdot |s_2|)$ time by detecting cycles. 
*   We match $s_2$ against repetitions of $s_1$ one block at a time.
*   At the end of processing the $i$-th copy of $s_1$, we record the state `s2_index` (the position in $s_2$ we are currently trying to match).
*   Since $|s_2| \le 100$, there are only $|s_2|$ possible values for `s2_index`. By the Pigeonhole Principle, within at most $|s_2| + 1$ iterations of $s_1$, we will encounter a `s2_index` that we have seen before.
*   When we find that we have seen the same `s2_index` after processing $s_1$ copy `i` as we did after copy `prev_i`, we have found a cycle!
*   The length of the cycle in terms of $s_1$ blocks is `cycle_len = i - prev_i`.
*   The number of times we matched $s_2$ completely within one cycle is `cycle_count = count - prev_count`.
*   We can skip matching for the remaining copies of $s_1$ mathematically:
    $$\text{full\_cycles} = \frac{n_1 - 1 - i}{\text{cycle\_len}}$$
    $$\text{count} \leftarrow \text{count} + \text{full\_cycles} \times \text{cycle\_count}$$
*   Finally, we simulate the remaining fractional cycle of $s_1$ copies.

### Standard C++ Production Code

```cpp
#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    int getMaxRepetitions(std::string s1, int n1, std::string s2, int n2) {
        if (n1 == 0) {
            return 0;
        }

        int s1_len = static_cast<int>(s1.size());
        int s2_len = static_cast<int>(s2.size());

        // Quick check: If there is any character in s2 that is not present in s1,
        // we can never match s2.
        std::vector<bool> s1_chars(26, false);
        for (char c : s1) {
            s1_chars[c - 'a'] = true;
        }
        for (char c : s2) {
            if (!s1_chars[c - 'a']) {
                return 0;
            }
        }

        // prev_iter[s2_idx] stores the iteration index i of s1 where s2_idx was matched.
        std::vector<int> prev_iter(s2_len + 1, -1);
        // prev_count[s2_idx] stores the count of fully matched s2 at that point.
        std::vector<int> prev_count(s2_len + 1, 0);

        int count = 0;
        int s2_idx = 0;
        bool found_cycle = false;

        for (int i = 0; i < n1; ++i) {
            for (int j = 0; j < s1_len; ++j) {
                if (s1[j] == s2[s2_idx]) {
                    s2_idx++;
                    if (s2_idx == s2_len) {
                        count++;
                        s2_idx = 0;
                    }
                }
            }

            if (!found_cycle && prev_iter[s2_idx] >= 0) {
                found_cycle = true;
                int prev_i = prev_iter[s2_idx];
                int prev_cnt = prev_count[s2_idx];

                int cycle_len = i - prev_i;
                int cycle_count = count - prev_cnt;

                int remaining = n1 - 1 - i;
                int full_cycles = remaining / cycle_len;

                count += full_cycles * cycle_count;
                int processed = i + full_cycles * cycle_len + 1;

                // Simulate the remaining parts
                for (int ii = processed; ii < n1; ++ii) {
                    for (int jj = 0; jj < s1_len; ++jj) {
                        if (s1[jj] == s2[s2_idx]) {
                            s2_idx++;
                            if (s2_idx == s2_len) {
                                count++;
                                s2_idx = 0;
                            }
                        }
                    }
                }
                break;
            }

            if (!found_cycle) {
                prev_iter[s2_idx] = i;
                prev_count[s2_idx] = count;
            }
        }

        return count / n2;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the clean Python implementation with type annotations and early cycle breaking.

```python
class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        """
        Returns the maximum integer m such that [s2, m * n2] is a subsequence of [s1, n1].
        
        Time Complexity: O(|s1| * |s2|)
        Space Complexity: O(|s2|)
        """
        if n1 == 0:
            return 0
            
        s1_len, s2_len = len(s1), len(s2)
        
        # Verify characters
        if not set(s2).issubset(set(s1)):
            return 0

        # Mapping: s2_index -> (s1_index_i, total_matched_s2_count)
        index_map = {}
        count = 0
        s2_index = 0

        for i in range(n1):
            for j in range(s1_len):
                if s1[j] == s2[s2_index]:
                    s2_index += 1
                    if s2_index == s2_len:
                        count += 1
                        s2_index = 0
            
            # Check for cycle
            if s2_index in index_map:
                prev_i, prev_count = index_map[s2_index]
                
                cycle_len = i - prev_i
                cycle_count = count - prev_count
                
                remaining = n1 - 1 - i
                full_cycles = remaining // cycle_len
                
                count += full_cycles * cycle_count
                processed = i + full_cycles * cycle_len + 1
                
                # Simulate the remainder
                for ii in range(processed, n1):
                    for jj in range(s1_len):
                        if s1[jj] == s2[s2_index]:
                            s2_index += 1
                            if s2_index == s2_len:
                                count += 1
                                s2_index = 0
                break
            else:
                index_map[s2_index] = (i, count)
                
        return count // n2
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Fast Character Set Verification
*   We use Python's built-in set subset operation: `set(s2).issubset(set(s1))`.
*   This takes $\mathcal{O}(|s1| + |s2|)$ time and is implemented in highly-optimized C code internally, which allows us to exit early with `0` in a fraction of a millisecond if any character in $s_2$ cannot be matched.

### 2. Hash Map Performance
*   Using Python's dictionary `index_map` works seamlessly since integers are hashable. In C++, we used a fixed-size `std::vector` of size `s2_len + 1`, which avoids the overhead of hashing altogether. In Python, the small number of keys ($|s_2| \le 100$) means hash collisions are non-existent, keeping lookups at near constant time.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(|s_1| \cdot |s_2|)$ | We run the simulation until a cycle is found. The number of outer loop iterations is at most $|s_2| + 1$ (due to Pigeonhole Principle). In each iteration, we loop through $|s_1|$ characters. |
| **Space Complexity** | $\mathcal{O}(|s_2|)$ | The space to store the visited states (`index_map` or `prev_iter` array of size $|s_2|$). |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if $n_1$ is extremely large (e.g., up to $10^{12}$)?
*   **Answer**: The cycle-detection algorithm would still run in the same time complexity because the cycle is detected in at most $|s_2| + 1$ steps. The only modification required is to use a 64-bit integer (`long long` in C++ or Python's native arbitrary precision integers) to avoid integer overflow when multiplying `full_cycles * cycle_count`.

### Q2: Why is the outer loop index bound by $|s_2|$ rather than $|s_1|$?
*   **Answer**: Because the state transitions are defined by where we land in $s_2$ at the boundary of $s_1$ blocks. Since the pointer in $s_1$ resets to $0$ at the start of each block, the only state parameter that determines the future transitions is `s2_index`. The number of unique states for `s2_index` is exactly $|s_2|$.

---

## Pro-Tip: How to Impress the Interviewer

*   **Pigeonhole Principle Proof**: Walk the interviewer through the Pigeonhole Principle proof for why cycle detection works. Specifically, note that because we are evaluating `s2_index` at the end of each $s_1$ repetition, the number of distinct values of `s2_index` is bounded by $|s_2|$. This guarantees that we will see a duplicate state in at most $|s_2| + 1$ blocks.
*   **Pre-filtering with Set Algebra**: Highlighting the early character existence check demonstrates attention to realistic performance and edge cases. In production systems, checking constraints early saves CPU cycles.
