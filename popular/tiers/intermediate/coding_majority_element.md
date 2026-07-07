# Majority Element

- **Category**: Coding
- **Difficulty**: Easy
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 169, Glassdoor

---

## Question Description

Given an array `nums` of size `n`, return the majority element.

The majority element is the element that appears more than $\lfloor n / 2 \rfloor$ times. You may assume that the majority element always exists in the array.

### Examples
*   **Input**: `nums = [3,2,3]`
    *   **Output**: `3`
*   **Input**: `nums = [2,2,1,1,1,2,2]`
    *   **Output**: `2`

---

## Detailed Solution (C++)

While this problem can be solved using **Divide and Conquer** in $\mathcal{O}(n \log n)$ time, the optimal approach is the **Boyer-Moore Voting Algorithm**, which runs in $\mathcal{O}(n)$ time and $\mathcal{O}(1)$ space. 

### Boyer-Moore Voting Algorithm Logic
1. Maintain a `candidate` and a `count` initialized to `0` or the first element.
2. For each element in the array:
   - If `count` is `0`, assign the current element to `candidate` and set `count` to `1`.
   - If the current element equals `candidate`, increment `count`.
   - Otherwise, decrement `count`.
3. Because the majority element appears more than $\lfloor n / 2 \rfloor$ times, its votes will always dominate and remain at the end.

We also show the **Divide and Conquer** implementation to demonstrate pattern flexibility:
- Split the array into two halves.
- Find the majority candidate in the left half and right half recursively.
- If the candidates are the same, that candidate is the majority element of the combined segment.
- If they differ, count the frequency of both candidates in the combined segment and return the one with the higher count.

### Standard C++ Production Code

#### Optimal Approach: Boyer-Moore Voting ($\mathcal{O}(n)$ Time, $\mathcal{O}(1)$ Space)
```cpp
#include <vector>

class Solution {
public:
    int majorityElement(const std::vector<int>& nums) noexcept {
        int candidate = nums[0];
        int count = 1;
        
        for (size_t i = 1; i < nums.size(); ++i) {
            if (count == 0) {
                candidate = nums[i];
                count = 1;
            } else if (nums[i] == candidate) {
                ++count;
            } else {
                --count;
            }
        }
        
        return candidate;
    }
};
```

#### Divide and Conquer Approach ($\mathcal{O}(n \log n)$ Time, $\mathcal{O}(\log n)$ Space)
```cpp
#include <vector>
#include <algorithm>

class SolutionDivideConquer {
public:
    int majorityElement(const std::vector<int>& nums) {
        return findMajority(nums, 0, static_cast<int>(nums.size()) - 1);
    }

private:
    int findMajority(const std::vector<int>& nums, int left, int right) {
        if (left == right) {
            return nums[left];
        }
        
        int mid = left + (right - left) / 2;
        int leftMajority = findMajority(nums, left, mid);
        int rightMajority = findMajority(nums, mid + 1, right);
        
        if (leftMajority == rightMajority) {
            return leftMajority;
        }
        
        // Count occurrences of each candidate in [left, right]
        int leftCount = countInRange(nums, leftMajority, left, right);
        int rightCount = countInRange(nums, rightMajority, left, right);
        
        return leftCount > rightCount ? leftMajority : rightMajority;
    }

    int countInRange(const std::vector<int>& nums, int target, int left, int right) {
        int count = 0;
        for (int i = left; i <= right; ++i) {
            if (nums[i] == target) {
                ++count;
            }
        }
        return count;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

#### Optimal Approach: Boyer-Moore Voting
```python
from typing import List

class Solution:
    def majorityElement(self, nums: List[int]) -> int:
        """
        Finds the majority element using the Boyer-Moore Voting Algorithm.
        
        Time Complexity: O(n)
        Space Complexity: O(1)
        """
        candidate = nums[0]
        count = 1
        
        for num in nums[1:]:
            if count == 0:
                candidate = num
                count = 1
            elif num == candidate:
                count += 1
            else:
                count -= 1
                
        return candidate
```

#### Divide and Conquer Approach
```python
from typing import List

class SolutionDivideConquer:
    def majorityElement(self, nums: List[int]) -> int:
        """
        Finds the majority element using Divide and Conquer.
        
        Time Complexity: O(n log n)
        Space Complexity: O(log n)
        """
        def get_majority(left: int, right: int) -> int:
            if left == right:
                return nums[left]
            
            mid = left + (right - left) // 2
            left_maj = get_majority(left, mid)
            right_maj = get_majority(mid + 1, right)
            
            if left_maj == right_maj:
                return left_maj
            
            # Count frequencies in range
            left_count = sum(1 for i in range(left, right + 1) if nums[i] == left_maj)
            right_count = sum(1 for i in range(left, right + 1) if nums[i] == right_maj)
            
            return left_maj if left_count > right_count else right_maj

        return get_majority(0, len(nums) - 1)
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Built-in `collections.Counter`
*   In Python, you can find the majority element via `Counter(nums).most_common(1)[0][0]`. While this is extremely concise, it uses $\mathcal{O}(n)$ auxiliary space to store the hash map, which is suboptimal compared to Boyer-Moore's $\mathcal{O}(1)$ space.

### 2. Slicing in Recursion
*   In the Divide and Conquer approach, passing array slices (e.g., `nums[:mid]`) creates copies of lists. To achieve the $\mathcal{O}(n \log n)$ time limit and avoid extra memory allocations, pass indices `left` and `right` rather than slicing the list.

---

## Complexity Analysis

### Boyer-Moore Voting Algorithm:
| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | Single pass over the array of size $n$. |
| **Space Complexity** | $\mathcal{O}(1)$ | Uses a constant number of integer variables. |

### Divide and Conquer:
| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n \log n)$ | Defined by $T(n) = 2T(n/2) + \mathcal{O}(n)$ where counting the frequencies takes $\mathcal{O}(n)$ at each step. |
| **Space Complexity** | $\mathcal{O}(\log n)$ | Depth of the recursion call stack is $\log n$. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if the majority element is not guaranteed to exist?
*   **Answer**: The Boyer-Moore algorithm will still return a candidate. To verify if it is indeed the majority element, perform a second linear pass over the array to count the actual occurrences of that candidate. If the count is $> \lfloor n / 2 \rfloor$, it is the majority element; otherwise, no majority element exists.

### Q2: How can we find all elements that appear more than $\lfloor n / 3 \rfloor$ times? (LeetCode 229)
*   **Answer**: Generalize Boyer-Moore to maintain up to **two candidates** and their respective counts (since at most two elements can appear more than $\lfloor n / 3 \rfloor$ times). In a second pass, verify both candidates.

---

## Pro-Tip: How to Impress the Interviewer

*   **Parallelizability (MapReduce)**: Point out that Boyer-Moore is inherently sequential. However, the **Divide and Conquer** approach is highly parallelizable. In distributed systems (like MapReduce or Spark), we can find majority candidates in chunks of a massive file on different servers, and then merge the candidates by counting their occurrences in a final reduction step.
*   **Bitwise Voting**: Discuss another $\mathcal{O}(32 \cdot n) = \mathcal{O}(n)$ solution: count the number of set bits at each of the 32 bit positions. If a bit is set in more than half of the elements, that bit will be set in the majority element. This highlights a deep understanding of low-level data representation.
