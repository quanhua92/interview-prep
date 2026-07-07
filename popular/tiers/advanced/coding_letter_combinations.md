# Letter Combinations of a Phone Number

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / AI Systems Architect / QA & Test Engineer
- **Source**: LeetCode 17, Glassdoor

---

## Question Description

Given a string containing digits from `2-9` inclusive, return all possible letter combinations that the number could represent. Return the answer in any order.

A mapping of digits to letters (just like on the telephone buttons) is given below. Note that `1` and `0` do not map to any letters.

*   `2` -> `"abc"`
*   `3` -> `"def"`
*   `4` -> `"ghi"`
*   `5` -> `"jkl"`
*   `6` -> `"mno"`
*   `7` -> `"pqrs"`
*   `8` -> `"tuv"`
*   `9` -> `"wxyz"`

### Examples

*   **Input**: `digits = "23"`
    *   **Output**: `["ad","ae","af","bd","be","bf","cd","ce","cf"]`
*   **Input**: `digits = ""`
    *   **Output**: `[]`
*   **Input**: `digits = "2"`
    *   **Output**: `["a","b","c"]`

---

## Detailed Solution (C++)

The backtracking approach builds combinations index-by-index. For each digit in the input string, we look up its mapped characters, place one character into our current working path, and recursively move to the next digit.

To optimize performance in C++:
1.  **Pre-allocated String**: Instead of building the path by repeatedly appending and popping characters (which might trigger reallocations), we pre-allocate a string `path` of size `digits.size()` and overwrite characters by index.
2.  **Pass by Reference**: Avoid copying strings and vectors by passing them as references to the helper function.

### Standard C++ Production Code

```cpp
#include <vector>
#include <string>
#include <algorithm>

class Solution {
private:
    const std::vector<std::string> phone_map = {
        "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
    };

    void backtrack(const std::string& digits, int index, std::string& path, std::vector<std::string>& result) {
        if (index == digits.size()) {
            result.push_back(path);
            return;
        }
        
        // Convert character digit to index (e.g. '2' - '0' = 2)
        const std::string& letters = phone_map[digits[index] - '0'];
        for (char c : letters) {
            path[index] = c;
            backtrack(digits, index + 1, path, result);
        }
    }

public:
    std::vector<std::string> letterCombinations(const std::string& digits) {
        if (digits.empty()) {
            return {};
        }
        
        std::vector<std::string> result;
        std::string path(digits.size(), '\0');
        
        backtrack(digits, 0, path, result);
        return result;
    }
};
```

---

## Detailed Solution (Python)

In Python, we implement backtracking using a helper function and a list representation for the mutable path. When we reach a leaf node in the recursion tree (where `index == len(digits)`), we join the list of characters to construct a string and add it to our output.

### Standard Python Production Code

```python
from typing import List

class Solution:
    def letterCombinations(self, digits: str) -> List[str]:
        """
        Generates all possible letter combinations that the number digits could represent.
        
        Time Complexity: O(4^N * N)
        Space Complexity: O(N)
        """
        if not digits:
            return []

        phone_map = {
            "2": "abc",
            "3": "def",
            "4": "ghi",
            "5": "jkl",
            "6": "mno",
            "7": "pqrs",
            "8": "tuv",
            "9": "wxyz",
        }
        
        result: List[str] = []

        def backtrack(index: int, path: List[str]):
            if index == len(digits):
                result.append("".join(path))
                return
            
            for letter in phone_map[digits[index]]:
                path.append(letter)
                backtrack(index + 1, path)
                path.pop()  # Revert choice for backtracking step

        backtrack(0, [])
        return result
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. `join` Overhead
*   Using `"".join(path)` takes $\mathcal{O}(N)$ time where $N$ is the length of the list. Since this operation is done at the leaves of the recursion tree, the overall time matches the total output characters generated.
*   Avoid using string concatenation (e.g. `path + letter`) in backtracking parameters, as strings are immutable in Python and constructing new strings at each level incurs $\mathcal{O}(N)$ copy cost on every edge of the recursion tree.

### 2. Space Cost of dynamic lists vs pre-allocation
*   Python lists are dynamically resized arrays. Calling `append()` and `pop()` is highly optimized but still has some minor dynamic check overhead.
*   For longer strings, pre-allocating a list of fixed size `[None] * len(digits)` and assigning indices directly `path[index] = letter` avoids resize overhead and is slightly faster.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(4^N \cdot N)$ | Where $N$ is the number of digits. At most, a digit maps to 4 letters (e.g. '7', '9'). The number of leaves is at most $4^N$, and joining/sorting strings takes $\mathcal{O}(N)$ per result. |
| **Space Complexity** | $\mathcal{O}(N)$ | The depth of the recursion tree is $N$ levels, requiring $\mathcal{O}(N)$ stack space. |

---

## Common Follow-Up Questions & How to Answer

### Q1: How can we implement this iteratively instead of using recursion?
*   **The Answer**: We can generate combinations iteratively by building them layer by layer. Starting with a list containing an empty string, we iterate over each digit and build new combinations using a list comprehension, which avoids the overhead of `pop(0)` in a standard queue.
*   **Python Code**:
```python
    def letterCombinationsIterative(digits: str) -> List[str]:
        if not digits:
            return []
        phone_map = {
            "2": "abc", "3": "def", "4": "ghi", "5": "jkl",
            "6": "mno", "7": "pqrs", "8": "tuv", "9": "wxyz"
        }
        res = [""]
        for digit in digits:
            res = [prev + letter for prev in res for letter in phone_map[digit]]
        return res
```

### Q2: What if we want to return a generator/iterator instead of generating all combinations in memory at once?
*   **The Answer**: If the digit string is very long, materializing all combinations in memory consumes a massive amount of memory. Using Python's `yield` keywords allows returning a generator that yields combinations lazily.
*   **Python Code**:
    ```python
    def letterCombinationsLazy(self, digits: str):
        if not digits:
            return
        phone_map = {"2": "abc", "3": "def", "4": "ghi", "5": "jkl", "6": "mno", "7": "pqrs", "8": "tuv", "9": "wxyz"}
        
        def backtrack(index, path):
            if index == len(digits):
                yield "".join(path)
                return
            for letter in phone_map[digits[index]]:
                path.append(letter)
                yield from backtrack(index + 1, path)
                path.pop()
        yield from backtrack(0, [])
    ```

---

## Pro-Tip: How to Impress the Interviewer

*   **Mention Pre-allocation Benefits**: Point out that pre-allocating the string buffer (in C++) or a list (in Python) and mutating elements in-place is highly cache-friendly. It completely eliminates memory allocation and deallocation operations along the recursion path, which is critical for low-latency systems.
*   **Discuss Generator Pattern**: Bringing up generators and lazy evaluation shows that you care about memory consumption when handling large-scale datasets, which is highly appreciated in production software design.
*   **Address Cache Localization**: Explain that looking up values in a static dictionary/hash map or array is fast, but storing the phone mapping as a contiguous static array or `std::array` instead of a heap-allocated `std::map` avoids pointer indirection and cache misses.
