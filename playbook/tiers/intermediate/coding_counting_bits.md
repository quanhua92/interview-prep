# Counting Bits

- **Category**: Coding
- **Difficulty**: Easy
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 338, Glassdoor
- **Flashcards**: [Bit Manipulation deck](../../flash_cards/coding/bit_manipulation.md)

---

## Question Description

Given an integer `n`, return an array `ans` of length `n + 1` such that for each `i` ($0 \le i \le n$), `ans[i]` is the **number of 1's** in the binary representation of `i`.

You must implement a solution with linear $\mathcal{O}(n)$ runtime complexity and perform it in a single pass without using any built-in functions.

### Examples

*   **Input**: `n = 2`
    *   **Output**: `[0,1,1]`
    *   **Explanation**:
        *   `0` $\rightarrow$ `0` (0 set bits)
        *   `1` $\rightarrow$ `1` (1 set bit)
        *   `2` $\rightarrow$ `10` (1 set bit)
*   **Input**: `n = 5`
    *   **Output**: `[0,1,1,2,1,2]`
    *   **Explanation**:
        *   `0` $\rightarrow$ `000` (0 set bits)
        *   `1` $\rightarrow$ `001` (1 set bit)
        *   `2` $\rightarrow$ `010` (1 set bit)
        *   `3` $\rightarrow$ `011` (2 set bits)
        *   `4` $\rightarrow$ `100` (1 set bit)
        *   `5` $\rightarrow$ `101` (2 set bits)

### Constraints
*   $0 \le n \le 10^5$

---

## Detailed Solution (C++)

A naive approach counts the bits for each number independently, which takes $\mathcal{O}(n \log n)$ time. 
To achieve $\mathcal{O}(n)$ time, we use **Dynamic Programming** combined with **Bit Manipulation**. We can derive the count of $1$s for `i` using previously computed subproblems:

### Approach 1: Most Significant Bit (MSB) / Shift Property
The binary representation of `i` is identical to `i >> 1` (which is `i / 2`) shifted right by 1 bit, plus the value of the least significant bit (`i & 1`).
$$\text{ans}[i] = \text{ans}[i \gg 1] + (i \ \& \ 1)$$
Since $i \gg 1 < i$, the value for $\text{ans}[i \gg 1]$ is guaranteed to have already been computed.

### Approach 2: Least Significant Bit (LSB) / Brian Kernighan clearing
We know that `i & (i - 1)` clears the lowest set bit of `i`. Thus, the number of set bits in `i` is exactly $1$ more than the number of set bits in the resulting value:
$$\text{ans}[i] = \text{ans}[i \ \& \ (i - 1)] + 1$$
Both approaches yield a highly optimized, single-pass $\mathcal{O}(n)$ runtime.

### Standard C++ Production Code

```cpp
#include <vector>

class Solution {
public:
    std::vector<int> countBits(int n) {
        // Initialize the output array with zeros
        std::vector<int> ans(n + 1, 0);

        for (int i = 1; i <= n; ++i) {
            // ans[i] = count of (i shifted right by 1) + 1 if i is odd (least significant bit is 1)
            ans[i] = ans[i >> 1] + (i & 1);
        }

        return ans;
    }

    // Alternative DP Transition using Brian Kernighan's bit clearing
    std::vector<int> countBitsAlternative(int n) {
        std::vector<int> ans(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            ans[i] = ans[i & (i - 1)] + 1;
        }
        return ans;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the iterative, type-hinted Python implementation using the shift property.

```python
from typing import List

class Solution:
    def countBits(self, n: int) -> List[int]:
        """
        Generates bit count array for numbers 0 to n in O(N) time.
        
        Time Complexity: O(N)
        Space Complexity: O(1) auxiliary space (excluding result array).
        """
        ans = [0] * (n + 1)
        for i in range(1, n + 1):
            ans[i] = ans[i >> 1] + (i & 1)
        return ans
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Integer Bitwise Shift
* Python handles bitwise operations natively in C. The operator `i >> 1` is significantly faster than division `i // 2` because bit-shifting is processed directly by the CPU ALU, avoiding floating-point division conversion.

### 2. Pre-allocation of List Memory
* In Python, constructing the list using `ans = [0] * (n + 1)` allocates a contiguous array block at the start. Doing `ans.append(...)` inside the loop causes dynamic list resizing, which triggers heap reallocation and copying of elements, slowing down runtime performance.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | Every integer from $1$ to $n$ is processed exactly once in constant $\mathcal{O}(1)$ time. |
| **Space Complexity** | $\mathcal{O}(1)$ | Auxiliary space is constant (the $\mathcal{O}(n)$ space is only for the returned answer array). |

---

## Common Follow-Up Questions & How to Answer

### Q1: Can you solve this using a divide and conquer technique?
* **Answer**: Yes, the numbers of set bits follow a recursive pattern. For any power of $2$ (let's say $2^k$), the sequence of set bits for $[2^k, 2^{k+1} - 1]$ is identical to the sequence of $[0, 2^k - 1]$ with each element incremented by 1 (representing the leading $2^k$ bit).
* We can build the array by copying the previously computed half and adding $1$ to each element.

### Q2: How would you parallelize this for extremely large $N$ (e.g. $N = 10^9$)?
* **Answer**: Since the DP state `ans[i]` depends on `ans[i >> 1]`, there is a data dependency. However, since the dependency only goes from lower indices to higher indices, we can chunk the computation.
  * Alternatively, we can eliminate the DP dependency entirely: each thread can compute its number's popcount independently using the hardware `POPCNT` instruction (via `std::experimental::simd` or OpenMP parallel loops). This is highly parallelizable and executes in parallel $\mathcal{O}(N / P)$ time where $P$ is the number of cores.

---

## Pro-Tip: How to Impress the Interviewer

* **Contrast DP Relations**: Discuss the difference between `ans[i >> 1] + (i & 1)` and `ans[i & (i - 1)] + 1`. Point out that `ans[i & (i - 1)] + 1` is slightly more intuitive as it directly counts the number of operations required by Brian Kernighan's algorithm.
* **Explain Compiler Optimizations**: Explain that compilers can optimize bit shifts (`i >> 1`) and bitwise ANDs (`i & 1`) into single-cycle CPU instructions (`SHR` and `AND`). Pointing this out shows you write code with compiler optimization pathways in mind.
