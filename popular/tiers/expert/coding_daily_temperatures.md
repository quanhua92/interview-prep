# Daily Temperatures

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 739, Glassdoor
- **Flashcards**: [Monotonic Stack deck](../../flash_cards/coding/monotonic_stack.md)

---

## Question Description

Given an array of integers `temperatures` representing the daily temperatures, return an array `answer` such that `answer[i]` is the number of days you have to wait after the $i$-th day to get a warmer temperature. If there is no future day for which this is possible, keep `answer[i] == 0` instead.

### Examples

*   **Input**: `temperatures = [73,74,75,71,69,72,76,73]`
    *   **Output**: `[1,1,4,2,1,1,0,0]`
*   **Input**: `temperatures = [30,40,50,60]`
    *   **Output**: `[1,1,1,0]`
*   **Input**: `temperatures = [30,60,90]`
    *   **Output**: `[1,1,0]`

---

## Detailed Solution (C++)

The standard solution uses a **Monotonic Decreasing Stack** storing indices of the temperatures.
1. We iterate through the array from left to right.
2. For each day `i` with temperature `temperatures[i]`, we compare it with the temperature at the index stored at the top of the stack.
3. While the stack is not empty and the current temperature `temperatures[i]` is strictly greater than the temperature at the index on top of the stack (`temperatures[stack.back()]`):
    * We pop the top index `j`.
    * The number of days we had to wait for index `j` is `i - j`.
    * We set `answer[j] = i - j`.
4. We push the current index `i` onto the stack.

By the end of the iteration, any indices remaining on the stack do not have a warmer day in the future, and their default value `0` remains in `answer`.

### Standard C++ Production Code

```cpp
#include <vector>
#include <cstddef>

class Solution {
public:
    std::vector<int> dailyTemperatures(std::vector<int>& temperatures) {
        if (temperatures.empty()) {
            return {};
        }

        const int n = static_cast<int>(temperatures.size());
        std::vector<int> answer(n, 0);
        std::vector<int> stack;
        stack.reserve(n); // Reserve memory to prevent dynamic reallocation overhead

        for (int i = 0; i < n; ++i) {
            // Keep popping elements from the stack while we find a warmer temperature
            while (!stack.empty() && temperatures[i] > temperatures[stack.back()]) {
                int prev_index = stack.back();
                stack.pop_back();
                answer[prev_index] = i - prev_index;
            }
            stack.push_back(i);
        }

        return answer;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the type-hinted Python implementation using the monotonic stack.

```python
from typing import List

class Solution:
    def dailyTemperatures(self, temperatures: List[int]) -> List[int]:
        """
        Calculates the number of days to wait for a warmer temperature.
        
        Time Complexity: O(N)
        Space Complexity: O(N)
        """
        if not temperatures:
            return []

        n = len(temperatures)
        answer = [0] * n
        stack: List[int] = []

        for i, temp in enumerate(temperatures):
            # While stack is not empty and current temperature is warmer than top of stack
            while stack and temp > temperatures[stack[-1]]:
                prev_index = stack.pop()
                answer[prev_index] = i - prev_index
            stack.append(i)

        return answer
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Dynamic Memory Overhead
* In Python, lists grow dynamically. The stack can hold up to $n$ indices, resulting in memory allocation and copying at the C-level under the hood. While Python handles this efficiently, using an in-place array pointer jumping method (detailed below) can avoid stack allocation entirely.

### 2. Fast Enumeration
* Using `enumerate(temperatures)` is faster and more Pythonic than looping over `range(len(temperatures))` and accessing elements by index, as it avoids index-lookup overhead inside the virtual machine interpreter loop.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | Each index is pushed and popped from the stack at most once. |
| **Space Complexity** | $\mathcal{O}(n)$ | The stack can store up to $n$ elements in the worst case (e.g., when temperatures are strictly decreasing). |

---

## Common Follow-Up Questions & How to Answer

### Q1: Can we solve this problem in $\mathcal{O}(1)$ auxiliary space (excluding the output array)?
* **Answer**: Yes! By iterating from **right to left** and using the information already stored in the `answer` array to jump over colder days, we can avoid allocating an external stack.
* For each index `i` from $n-2$ down to $0$, we set `curr = i + 1`. 
* If `temperatures[curr] <= temperatures[i]`, then if `answer[curr] == 0`, it means there is no warmer day to the right of `curr`, hence there is no warmer day for `i`. If `answer[curr] > 0`, we can jump `curr += answer[curr]` to the next warmer day and repeat the comparison.
* **Code Example (C++)**:
    ```cpp
    std::vector<int> dailyTemperatures(std::vector<int>& temperatures) {
        int n = temperatures.size();
        std::vector<int> answer(n, 0);
        for (int i = n - 2; i >= 0; --i) {
            int curr = i + 1;
            while (curr < n && temperatures[curr] <= temperatures[i]) {
                if (answer[curr] == 0) {
                    curr = n; // Break, no warmer day exists
                } else {
                    curr += answer[curr]; // Jump to next warmer day
                }
            }
            if (curr < n) {
                answer[i] = curr - i;
            }
        }
        return answer;
    }
    ```

### Q2: How can we leverage the temperature constraint $30 \le \text{temperatures}[i] \le 100$?
* **Answer**: Since the temperature range is extremely small (only $71$ unique values), we can keep an array `next_occurrence` of size $101$, initialized to $\infty$, which stores the earliest index where each temperature occurs. 
* Iterating from right to left, for each day `i`, we look up the values in `next_occurrence` for all temperatures from `temperatures[i] + 1` to `100`. The minimum index found tells us the closest warmer day. We then update `next_occurrence[temperatures[i]] = i`. This takes $\mathcal{O}(71 \cdot n)$ time and $\mathcal{O}(1)$ auxiliary space.

---

## Pro-Tip: How to Impress the Interviewer

* **Propose the Array-Jumping Optimization**: Point out that the space complexity can be reduced from $\mathcal{O}(n)$ to $\mathcal{O}(1)$ auxiliary space (excluding the output array) using the right-to-left array jumping technique. This shows exceptional problem-solving depth.
* **Discuss Cache Locality**: Note that the array-jumping algorithm exhibits superior cache locality compared to stack-based approaches because it reuses the output array and minimizes pointer jumps, which fits beautifully in low-level CPU caches.
