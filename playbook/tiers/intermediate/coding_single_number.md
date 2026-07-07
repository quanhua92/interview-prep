# Single Number

- **Category**: Coding
- **Difficulty**: Easy
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 136, Glassdoor
- **Flashcards**: [Bit Manipulation deck](../../flash_cards/coding/bit_manipulation.md)

---

## Question Description

Given a **non-empty** array of integers `nums`, every element appears twice except for one. Find that single one.

You must implement a solution with a linear runtime complexity and use only constant extra space.

### Examples

*   **Input**: `nums = [2,2,1]`
    *   **Output**: `1`
*   **Input**: `nums = [4,1,2,1,2]`
    *   **Output**: `4`
*   **Input**: `nums = [1]`
    *   **Output**: `1`

### Constraints
*   $1 \le \text{nums.length} \le 3 \times 10^4$
*   $-3 \times 10^4 \le \text{nums}[i] \le 3 \times 10^4$
*   Each element in the array appears twice except for one element which appears only once.

---

## Detailed Solution (C++)

To solve this in $\mathcal{O}(n)$ time and $\mathcal{O}(1)$ space, we use the properties of the **bitwise XOR (`^`) operator**:
1.  **Identity Property**: $A \oplus 0 = A$ (XORing any number with 0 remains unchanged)
2.  **Self-Inverse Property**: $A \oplus A = 0$ (XORing a number with itself cancels out and results in 0)
3.  **Commutative and Associative Properties**: The order in which we XOR the elements does not matter.

If we XOR all the elements in the array:
$$\text{result} = nums[0] \oplus nums[1] \oplus \dots \oplus nums[n-1]$$
Since every number except one appears exactly twice, all pairs will cancel each other out to $0$. We are left with:
$$\text{result} = 0 \oplus \text{single\_number} = \text{single\_number}$$

### Standard C++ Production Code

```cpp
#include <vector>

class Solution {
public:
    int singleNumber(const std::vector<int>& nums) noexcept {
        int result = 0;
        for (int num : nums) {
            result ^= num;
        }
        return result;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the type-hinted Python implementation. It uses `functools.reduce` for a highly Pythonic, single-line alternative, alongside the standard iterative loop.

```python
from typing import List
from functools import reduce
import operator

class Solution:
    def singleNumber(self, nums: List[int]) -> int:
        """
        Finds the unique number in a list where all other elements appear twice.
        
        Time Complexity: O(N)
        Space Complexity: O(1)
        """
        result = 0
        for num in nums:
            result ^= num
        return result

    def singleNumberPythonic(self, nums: List[int]) -> int:
        """
        Highly optimized Pythonic alternative using reduce.
        """
        return reduce(operator.xor, nums)
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. The `reduce` and `operator` Shorthand
* Using `reduce(operator.xor, nums)` avoids the interpreter loop overhead by delegating the iteration and XOR operations to C code inside the Python runtime. This is generally faster than a standard Python `for` loop.

### 2. Large Integer Bit Lengths
* Since Python integers are arbitrary-precision, XOR operations do not overflow. However, in low-level languages, if numbers exceed standard 32-bit limits, proper type declaration (e.g. `long long` in C++) is necessary.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | We iterate through the array of $n$ numbers exactly once. |
| **Space Complexity** | $\mathcal{O}(1)$ | Only a single accumulator variable is stored. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if all other numbers appear three times instead of twice? (LeetCode 137)
* **Answer**: If numbers appear three times, XORing them will not cancel them out. 
  * **Solution**: We can count the number of set bits at each of the 32 bit positions. If the sum of set bits at a position is not divisible by 3, the single number must have a 1 at that position.
  * **Code (C++)**:
    ```cpp
    int singleNumberThree(vector<int>& nums) {
        int ans = 0;
        for (int i = 0; i < 32; ++i) {
            int sum = 0;
            for (int num : nums) {
                if ((num >> i) & 1) sum++;
            }
            if (sum % 3 != 0) {
                ans |= (1 << i);
            }
        }
        return ans;
    }
    ```

### Q2: What if there are two single numbers instead of one? (LeetCode 260)
* **Answer**: If there are two single numbers $x$ and $y$, XORing all elements yields $xor\_val = x \oplus y$. Since $x \ne y$, $xor\_val$ must have at least one set bit.
  * **Solution**:
    1. Find the rightmost set bit of $xor\_val$ using `diff = xor_val & -xor_val`.
    2. Divide all numbers in the array into two groups: those that have this bit set and those that don't.
    3. XORing all numbers in each group independently will cancel out the duplicates, leaving $x$ in one group and $y$ in the other.

---

## Pro-Tip: How to Impress the Interviewer

* **Discuss Hardware-Level Execution**: Explain that XOR is a single-cycle bitwise operation executed directly in the CPU's ALU. Because it does not use branch pointers, it has no risk of branch misprediction stalls, making it extremely fast.
* **Mention Loop Unrolling**: For high-performance graphics or AI system code, mentioning that compilers can unroll the loop to execute multiple XORs concurrently (exploiting ILP - Instruction-Level Parallelism) shows top-tier optimization skills.
