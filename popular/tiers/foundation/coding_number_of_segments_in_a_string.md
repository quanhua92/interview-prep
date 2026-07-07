# Number of Segments in a String

- **Category**: Coding
- **Difficulty**: Easy
- **Target Role**: Software Engineer / Low-Level Developer
- **Source**: LeetCode 434, Glassdoor
- **Flashcards**: [String deck](../../flash_cards/coding/string.md)

---

## Question Description

Given a string `s`, return the number of segments in the string.

A **segment** is defined to be a contiguous sequence of non-space characters.

### Examples

*   **Input**: `s = "Hello, my name is John"`
    *   **Output**: `5`
    *   **Explanation**: The five segments are `["Hello,", "my", "name", "is", "John"]`.
*   **Input**: `s = "Hello"`
    *   **Output**: `1`

---

## Detailed Solution (C++)

To solve this in **one pass** with $\mathcal{O}(1)$ auxiliary space, we can model this as a simple two-state machine:
*   State 1: We are outside a segment (encountering spaces).
*   State 2: We are inside a segment (encountering non-space characters).

When we iterate through the string:
*   If we find a non-space character while currently *not* in a segment, it indicates the start of a new segment. We increment our counter and set `in_segment` to `true`.
*   If we find a space character, we set `in_segment` to `false`.

Alternatively, we can count the number of characters that are not spaces and are either at index `0` or preceded by a space.

### Standard C++ Production Code

```cpp
#include <string>

class Solution {
public:
    int countSegments(const std::string& s) noexcept {
        int count = 0;
        bool in_segment = false;

        for (const char c : s) {
            if (c != ' ') {
                if (!in_segment) {
                    count++;
                    in_segment = true;
                }
            } else {
                in_segment = false;
            }
        }

        return count;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the optimized single-pass state-machine approach in Python, followed by a discussion on Python's built-in split approach.

```python
class Solution:
    def countSegments(self, s: str) -> int:
        """
        Counts segments in a string without creating temporary string objects.
        
        Time Complexity: O(N)
        Space Complexity: O(1)
        """
        count = 0
        in_segment = False
        
        for ch in s:
            if ch != " ":
                if not in_segment:
                    count += 1
                    in_segment = True
            else:
                in_segment = False
                
        return count
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Built-in `split()` vs State Machine
*   A naive Python solution is `len(s.split())`. By default, `s.split()` splits by any whitespace run.
*   **Performance Tradeoff**: While `len(s.split())` is very concise and written in highly optimized C under the hood, it creates a list containing the split substrings. If the input string is very large (e.g. several megabytes), this creates an auxiliary array of strings, leading to $\mathcal{O}(n)$ memory allocation and high garbage collection overhead.
*   Our state machine approach maintains $\mathcal{O}(1)$ auxiliary space and avoids creating any new string objects, which is critical for low-level performance.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | We scan the string of length $n$ exactly once. |
| **Space Complexity** | $\mathcal{O}(1)$ | Only a few primitive variables (`count`, `in_segment`) are allocated. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if segments are separated by arbitrary whitespace (tabs, newlines, carriage returns)?
*   **Answer**: In C++, we should replace the check `c != ' '` with `!std::isspace(static_cast<unsigned char>(c))`. In Python, we can check `not ch.isspace()`.

### Q2: How can we implement this if the input string is a stream (e.g., reading from a network socket or file) that doesn't fit in memory?
*   **Answer**: Because the algorithm only looks at the current character and a single boolean state flag, it is perfectly suited for streaming. We can read the stream character-by-character (or in chunks) and update the state.
*   **C++ Stream Example**:
    ```cpp
    int countSegments(std::istream& stream) {
        int count = 0;
        bool in_segment = false;
        char c;
        while (stream.get(c)) {
            if (!std::isspace(static_cast<unsigned char>(c))) {
                if (!in_segment) {
                    count++;
                    in_segment = true;
                }
            } else {
                in_segment = false;
            }
        }
        return count;
    }
    ```

---

## Pro-Tip: How to Impress the Interviewer

*   **Critique Built-in Split Libraries**: Proactively mention that while using library functions like `std::stringstream` or Python's `split()` is easy to write, they copy parts of the string and allocate memory. Highlighting the memory allocation downside shows you prioritize efficiency.
*   **Character Classification Safety**: In C++, when using `std::isspace`, always mention that you must cast the character to `unsigned char` first. Standard C library functions like `isspace` exhibit undefined behavior if passed a negative value, which can happen with signed characters representing non-ASCII or extended characters (e.g., ISO-8859-1). Showing this level of safety is a massive differentiator.
