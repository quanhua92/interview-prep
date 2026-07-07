# Permutation in String

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 567, Glassdoor

---

## Question Description

Given two strings `s1` and `s2`, return `true` if `s2` contains a permutation of `s1`, or `false` otherwise.

In other words, return `true` if one of `s1`'s permutations is the substring of `s2`.

### Examples

*   **Input**: `s1 = "ab"`, `s2 = "eidbaooo"`
    *   **Output**: `true`
    *   **Explanation**: `s2` contains one permutation of `s1` (`"ba"`).
*   **Input**: `s1 = "ab"`, `s2 = "eidboaoo"`
    *   **Output**: `false`

---

## Detailed Solution (C++)

This problem is isomorphic to **Find All Anagrams in a String**, except we return a boolean value immediately upon finding the first match instead of accumulating indices.

We use a **Sliding Window of Fixed Size** matching the length of `s1`.
1. We populate a frequency map `target` of size 26 for string `s1`.
2. As we iterate through `s2` using a sliding window pointer `right`, we add `s2[right]` to our `current` frequency map.
3. If the window length exceeds `s1.length()`, we remove the leftmost character `s2[right - s1.length()]` from `current`.
4. If `target` is equal to `current`, we return `true` immediately.
5. If the loop finishes without a match, we return `false`.

### Standard C++ Production Code

```cpp
#include <string>
#include <array>

class Solution {
public:
    bool checkInclusion(const std::string& s1, const std::string& s2) noexcept {
        const int n1 = static_cast<int>(s1.size());
        const int n2 = static_cast<int>(s2.size());

        // Edge Case: If s1 is longer than s2, s2 cannot contain a permutation of s1
        if (n1 > n2) {
            return false;
        }

        std::array<int, 26> target{};
        std::array<int, 26> current{};

        // Populate the frequency table for s1
        for (int i = 0; i < n1; ++i) {
            target[s1[i] - 'a']++;
        }

        // Slide the window across s2
        for (int right = 0; right < n2; ++right) {
            current[s2[right] - 'a']++;

            // Shrink/slide window by removing the element that is out of bounds
            if (right >= n1) {
                current[s2[right - n1] - 'a']--;
            }

            // Direct O(26) comparison of arrays
            if (target == current) {
                return true;
            }
        }

        return false;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the Python implementation. We use a simple integer list of size 26 for frequencies to avoid the overhead of dictionary operations, matching the logic of the C++ implementation.

```python
class Solution:
    def checkInclusion(self, s1: str, s2: str) -> bool:
        """
        Determines if s2 contains a permutation of s1.
        
        Time Complexity: O(N) where N is the length of s2.
        Space Complexity: O(1) as the list uses a fixed size of 26.
        """
        n1, n2 = len(s1), len(s2)
        if n1 > n2:
            return False

        target = [0] * 26
        current = [0] * 26

        # Populate target frequency table for s1
        for ch in s1:
            target[ord(ch) - 97] += 1  # 97 is ord('a')

        # Slide the window across s2
        for right in range(n2):
            current[ord(s2[right]) - 97] += 1
            
            # Remove character that fell outside of window
            if right >= n1:
                current[ord(s2[right - n1]) - 97] -= 1
                
            # Compare the frequency lists
            if current == target:
                return True

        return False
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Choice of List vs Dictionary
*   In Python, comparing lists (`list1 == list2`) checks elements by index in C and is extremely fast.
*   Using dictionaries (`Counter`) would require deleting elements that reach `0` to keep the key counts aligned. List comparison avoids this logic and is much cleaner and faster in practice.

### 2. Micro-optimization: Avoiding `ord()` in Inner Loop
*   In Python, calling `ord()` inside the loop introduces function call overhead.
*   We can convert both strings into lists of integers using `[ord(c) - 97 for c in string]` beforehand. This pre-processing moves the function call overhead outside of the main loop, speeding up execution for very long strings.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n_2)$ | We scan string `s2` of length $n_2$ once. At each step, comparing two lists of size 26 is $\mathcal{O}(26) = \mathcal{O}(1)$. |
| **Space Complexity** | $\mathcal{O}(1)$ | The alphabet is lowercase English letters, so the memory footprint is bounded at $26$ integers. |

---

## Common Follow-Up Questions & How to Answer

### Q1: Can we optimize the array comparison from $\mathcal{O}(26)$ to true $\mathcal{O}(1)$?
*   **Answer**: Yes, by maintaining a `matches` counter initialized to the number of matches between the first window and target.
*   **Explanation**: We count how many characters have the exact same frequency in both `target` and `current`. As the window slides, we only modify the frequencies of two characters (entering and leaving). We adjust the `matches` count accordingly:
    *   If the new frequency of the character matches `target`, we increment `matches`.
    *   If it used to match but now does not, we decrement `matches`.
    *   If `matches == 26`, we return `true`.

### Q2: What if we want to find the start index of the first occurrence of the permutation?
*   **Answer**: We simply return `right - n1 + 1` instead of returning `true`. If the loop completes without a match, we return `-1`.

---

## Pro-Tip: How to Impress the Interviewer

*   **Mention SIMD and Array Layout**: Explain that in C++, `std::array<int, 26>` is stored as a contiguous stack block. Compilers are highly capable of auto-vectorizing array comparisons (using AVX/SIMD instructions) so that checking `target == current` executes in only a couple of CPU clock cycles.
*   **Space-Time Tradeoff awareness**: Mention that pre-indexing the string into a numeric array (such as converting ASCII to integers `0-25`) reduces the runtime overhead of string parsing and character arithmetic inside the sliding window loop.
