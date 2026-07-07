# Product of Array Except Self

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer
- **Source**: LeetCode 238, Glassdoor

---

## Question Description

Given an integer array `nums`, return an array `answer` such that `answer[i]` is equal to the product of all the elements of `nums` except `nums[i]`.

You must write an algorithm that runs in $\mathcal{O}(n)$ time and **without using the division operation**.

The product of any prefix or suffix of `nums` is guaranteed to fit in a 32-bit signed integer.

### Examples
*   **Input**: `nums = [1, 2, 3, 4]`
    *   **Output**: `[24, 12, 8, 6]`
*   **Input**: `nums = [-1, 1, 0, -3, 3]`
    *   **Output**: `[0, 0, 9, 0, 0]`

---

## Detailed Solution (C++)

To solve this problem in $\mathcal{O}(n)$ time without division and in $\mathcal{O}(1)$ auxiliary space, we construct the prefix and suffix products directly within the output vector:
1. **Prefix Pass**: We iterate from left to right. We use the output array to store the prefix product. Specifically, `output[i]` will store the product of all elements to the left of index `i`.
2. **Suffix Pass**: We iterate from right to left. We maintain a running suffix product in a single variable (`right`). We multiply the current prefix product stored in `output[i]` by `right`, then update `right` by multiplying it by `nums[i]`.

This achieves the result in-place without allocating separate prefix and suffix arrays.

### Standard C++ Production Code

```cpp
#include <vector>

class Solution {
public:
    std::vector<int> productExceptSelf(const std::vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        if (n == 0) return {};

        std::vector<int> output(n, 1);

        // Step 1: Compute prefix products in output array
        // output[i] contains the product of all elements to the left of i.
        int left = 1;
        for (int i = 0; i < n; ++i) {
            output[i] = left;
            left *= nums[i];
        }

        // Step 2: Compute suffix products on the fly and multiply with prefix products
        int right = 1;
        for (int i = n - 1; i >= 0; --i) {
            output[i] *= right;
            right *= nums[i];
        }

        return output;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the type-hinted Python implementation using the single-array prefix/suffix technique.

```python
from typing import List

class Solution:
    def productExceptSelf(self, nums: List[int]) -> List[int]:
        """
        Computes the product of array except self without division in O(N) time and O(1) auxiliary space.
        """
        n = len(nums)
        if n == 0:
            return []

        output = [1] * n

        # Step 1: Left prefix products
        left_product = 1
        for i in range(n):
            output[i] = left_product
            left_product *= nums[i]

        # Step 2: Right suffix products accumulated on the fly
        right_product = 1
        for i in range(n - 1, -1, -1):
            output[i] *= right_product
            right_product *= nums[i]

        return output
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Division Operators and Zero Handling
*   If we were allowed to use division, we might try: `total_product // nums[i]`. However, division in Python 3 using `/` yields a float, which can introduce precision errors for large integers. 
*   Furthermore, if the array contains `0`, division by zero raises a `ZeroDivisionError`. The prefix/suffix product approach is structurally robust and naturally handles any number of zeros without any branchy check logic.

### 2. Avoiding Intermediate Lists for Memory Efficiency
*   A naive approach allocates two extra arrays: `left_products` and `right_products`, resulting in an auxiliary space complexity of $\mathcal{O}(n)$. 
*   By writing prefix products directly into the final `output` list and updating it using a scalar `right_product`, we satisfy the strict $\mathcal{O}(1)$ auxiliary space constraint.

### 3. Dynamic Arrays (Lists) vs Pre-allocated Lists
*   Using `output = [1] * n` is faster than repeatedly calling `output.append()` because it allocates the block of memory all at once. Repeatedly appending elements causes Python's underlying dynamic array to resize and copy elements, adding a minor but noticeable overhead.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | Two linear scans over the array of size $n$. |
| **Space Complexity** | $\mathcal{O}(1)$ | No extra memory is allocated besides the output array (which does not count towards auxiliary complexity). |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if division is allowed?
*   **Answer**: If division is allowed, we can first count the number of zeros in `nums`:
    *   If zero count $\ge 2$: The output array is entirely zeros.
    *   If zero count $= 1$: Only the index containing the zero will have a non-zero product (which equals the product of all other elements). All other indices will be zero.
    *   If zero count $= 0$: We calculate the product of all elements and then set `output[i] = total_product / nums[i]`.
*   **Trade-off**: The prefix-suffix product algorithm is still superior because it is completely branch-free regarding zero detection, avoiding CPU pipeline stalls.

### Q2: What if we need prefix products for operations that do not have inverses?
*   **Answer**: The prefix-suffix strategy is highly general and applies to any **associative binary operation** $(S, \cdot)$. Examples include Matrix Multiplication, Greatest Common Divisor (GCD), Minimum/Maximum, and Boolean AND/OR. Since operations like GCD or Min/Max do not have inverse operations (analogous to division for multiplication), the prefix/suffix approach is the standard way to solve "except self" queries.

---

## Pro-Tip: How to Impress the Interviewer

*   **Mention Cache Locality**: Highlight that the left-to-right pass accesses `nums` sequentially, which perfectly aligns with modern CPU cache prefetching. The right-to-left pass accesses memory in reverse sequential order, which is also well-supported by hardware prefetchers, maintaining excellent cache efficiency compared to pointer-based or tree-based solutions.
*   **Discuss Compiler Vectorization (SIMD)**: Mention that while simple loops are easily vectorized by compilers, loop-carried dependencies (such as `left *= nums[i]`) limit automatic vectorization. Thus, this prefix-sum pattern operates as a sequential reduction and scan.
