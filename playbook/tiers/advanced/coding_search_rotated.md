# Search in Rotated Sorted Array

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 33, Glassdoor
- **Flashcards**: [Modified Binary Search deck](../../flash_cards/coding/modified_binary_search.md)

---

## Question Description

There is an integer array `nums` sorted in ascending order (with **distinct** values).

Prior to being passed to your function, `nums` is possibly rotated at an unknown pivot index `k` ($1 \le k < \text{nums.length}$) such that the resulting array is `[nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]` (**0-indexed**). For example, `[0,1,2,4,5,6,7]` might be rotated at pivot index `3` and become `[4,5,6,7,0,1,2]`.

Given the array `nums` **after** the possible rotation and an integer `target`, return the index of `target` if it is in `nums`, or `-1` if it is not in `nums`.

You must write an algorithm with $\mathcal{O}(\log n)$ runtime complexity.

### Examples
*   **Input**: `nums = [4,5,6,7,0,1,2]`, `target = 0`
    *   **Output**: `4`
*   **Input**: `nums = [4,5,6,7,0,1,2]`, `target = 3`
    *   **Output**: `-1`
*   **Input**: `nums = [1]`, `target = 0`
    *   **Output**: `-1`

---

## Detailed Solution (C++)

The core algorithm is a modified **Binary Search**. In a rotated sorted array, splitting the array in half guarantees that at least one of the halves is normally sorted. We can identify which half is sorted by comparing the boundary values:
1. If `nums[left] <= nums[mid]`, the left half is sorted.
   * If the target lies within $[ \text{nums}[left], \text{nums}[mid] )$, we narrow our search to the left half.
   * Otherwise, we search the right half.
2. If `nums[mid] < nums[left]`, the right half must be sorted.
   * If the target lies within $( \text{nums}[mid], \text{nums}[right] ]$, we search the right half.
   * Otherwise, we search the left half.

### Standard C++ Production Code

```cpp
#include <vector>
#include <cstddef>

class Solution {
public:
    int search(const std::vector<int>& nums, int target) noexcept {
        // Edge Case: Handle empty collection explicitly to prevent unsigned underflow
        if (nums.empty()) {
            return -1;
        }

        int left = 0;
        int right = static_cast<int>(nums.size()) - 1; // Safely cast size to int

        while (left <= right) {
            int mid = left + (right - left) / 2; // Prevent integer overflow (left + right) / 2

            if (nums[mid] == target) {
                return mid;
            }

            // Determine which half is normally sorted
            if (nums[left] <= nums[mid]) {
                // Left side is sorted
                if (target >= nums[left] && target < nums[mid]) {
                    right = mid - 1; // Target is in the left sorted portion
                } else {
                    left = mid + 1;  // Target is in the right portion
                }
            } else {
                // Right side is sorted
                if (target > nums[mid] && target <= nums[right]) {
                    left = mid + 1;  // Target is in the right sorted portion
                } else {
                    right = mid - 1; // Target is in the left portion
                }
            }
        }

        return -1; // Target not found
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the iterative, type-hinted Python implementation. It avoids recursive call overhead and ensures true constant space.

```python
from typing import List

class Solution:
    def search(self, nums: List[int], target: int) -> int:
        """
        Searches for a target in a rotated sorted array using binary search.
        
        Time Complexity: O(log N)
        Space Complexity: O(1)
        """
        # Edge Case: Handle empty collection explicitly
        if not nums:
            return -1

        left, right = 0, len(nums) - 1

        while left <= right:
            # Floor division operator '//' is required in Python to get integer index.
            # 'left + (right - left) // 2' is used to demonstrate system-level safety,
            # preventing overflow in languages with fixed-width integers.
            mid = left + (right - left) // 2

            if nums[mid] == target:
                return mid

            # Determine which half is normally sorted
            if nums[left] <= nums[mid]:
                # Left side is sorted
                if nums[left] <= target < nums[mid]:
                    right = mid - 1  # Target is within the sorted left portion
                else:
                    left = mid + 1   # Search the right portion
            else:
                # Right side is sorted
                if nums[mid] < target <= nums[right]:
                    left = mid + 1   # Target is within the sorted right portion
                else:
                    right = mid - 1  # Search the left portion

        return -1
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Integer Division: `/` vs `//`
*   In Python 3, the single slash division operator `/` returns a floating-point number (e.g., `5 / 2 = 2.5`). Python list indexes must be integers; using a float results in a `TypeError`. 
*   Always use the floor division operator `//` (e.g., `5 // 2 = 2`) to ensure index variables remain integers.

### 2. Arbitrary-Precision Integers vs System Limits
*   Python handles arbitrary-precision integers natively (it automatically transitions to "large integers" when values exceed $2^{63} - 1$). Thus, `(left + right) // 2` cannot overflow in Python.
*   However, writing `left + (right - left) // 2` is still recommended in system programming interviews. It signals that you write portable, compiler-agnostic code that translates safely to low-level environments (C/C++, Rust, CUDA).

### 3. List Slicing Performance Penalty
*   A common Python mistake is to slice arrays during search (e.g., `search(nums[:mid])`). Slicing a list in Python creates a **shallow copy** of that slice, taking $\mathcal{O}(k)$ time and space (where $k$ is the slice length).
*   Doing this degrades the algorithm's time complexity from $\mathcal{O}(\log n)$ to $\mathcal{O}(n)$, and space from $\mathcal{O}(1)$ to $\mathcal{O}(n)$. Always use pointer boundaries (`left`, `right`) to partition the search space in-place.

### 4. Recursion Limit and Frame Allocations
*   If binary search is implemented recursively, each call allocates a new stack frame in Python. Because Python's default call stack limit is low (typically $1000$), deep recursive searches can cause a `RecursionError` on large datasets.
*   Additionally, frame allocation in Python has higher CPU overhead compared to C++ because of dynamic object bindings. The iterative implementation is always preferred for optimal performance.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(\log n)$ | The search space is halved in each step of the binary search loop. |
| **Space Complexity** | $\mathcal{O}(1)$ | Only a few integer variables are maintained, requiring constant auxiliary memory. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if duplicates are allowed in the array? (LeetCode 81)
*   **The Problem**: If the array has duplicate values (e.g., `nums = [1, 1, 1, 1, 0, 1, 1]`), we cannot determine if the left or right side is sorted when `nums[left] == nums[mid] == nums[right]`.
*   **The Solution**: When this edge case is hit, we must shrink both boundaries (`left++` and `right--`) until they differ.
*   **Code Addition**:
    ```cpp
    if (nums[left] == nums[mid] && nums[mid] == nums[right]) {
        left++;
        right--;
        continue;
    }
    ```
*   **Complexity Impact**: The worst-case time complexity degrades to $\mathcal{O}(n)$ (when all elements are duplicates and we must scan linearly), though average-case remains $\mathcal{O}(\log n)$.

### Q2: How can we implement this logic "branchlessly" to prevent CPU branch mispredictions?
*   **The Problem**: Binary search is notoriously slow on CPUs due to **branch mispredictions** (the search direction has a $50\%$ probability, which confuses the hardware branch predictor and flushes the execution pipeline).
*   **The Solution**: We can eliminate branching by using data dependencies (ternary selectors or arithmetic) to compute the next boundaries instead of using `if/else` statements. Modern compilers translate ternary operators like `cond ? val1 : val2` into conditional move instructions (`CMOV` on x86, `SEL` on ARM/GPU), which execute without branch prediction.
*   **Example (Conceptual Branchless Update)**:
    ```cpp
    // Instead of if-else:
    int left_sorted = (nums[left] <= nums[mid]);
    int target_in_left = (target >= nums[left]) & (target < nums[mid]);
    int target_in_right = (target > nums[mid]) & (target <= nums[right]);

    int choose_left = left_sorted ? target_in_left : !target_in_right;
    
    // Update indices conditionally
    right = choose_left ? (mid - 1) : right;
    left = choose_left ? left : (mid + 1);
    ```

### Q3: How would you parallelize this search on a GPU (CUDA) for multiple targets?
*   **The Problem**: If 32 threads in a single **warp** search for different targets in parallel, their paths will diverge (some branch left, some right), causing **warp divergence** which serializes execution.
*   **Optimizations**:
    1.  **Shared Memory**: Store the array in GPU shared memory (`__shared__`) if it is accessed repeatedly by all threads. Shared memory has low latency and high bandwidth.
    2.  **Memory Coalescing**: Ensure that targets queried by adjacent threads are stored contiguously in memory so the GPU can load them in a single memory transaction.
    3.  **Bank Conflicts**: Ensure the array accesses do not fall into the same shared memory bank (modulo 32 addressing).

---

## Pro-Tip: How to Impress the Interviewer

*   **Catch the Underflow Bug Proactively**: Point out that doing `nums.size() - 1` without checking if `nums` is empty is a classic security and stability bug. Since `size()` returns `size_t` (unsigned), an empty vector yields `0 - 1 = 18446744073709551615` (on 64-bit platforms), causing an immediate out-of-bounds crash in the loop condition `left <= right`. Casting to `int` or explicitly handling empty checks proves real-world C++ systems hygiene.
*   **Mention Cache Prefetching**: Mention that while binary search has $\mathcal{O}(\log n)$ complexity, for small arrays ($n \le 64$), a simple linear scan (`std::find`) is often faster in practice due to contiguous hardware prefetching and the lack of branch mispredictions.
*   **Highlight CPU Pipeline Stalls**: Discussing CPU pipelining and branch misprediction costs shows you think about how code interacts with the physical silicon, which is critical for low-level development at companies like NVIDIA.
