# Decode String

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / QA & Test Engineer
- **Source**: LeetCode 394, Glassdoor

---

## Question Description

Given an encoded string, return its decoded string.

The encoding rule is: `k[encoded_string]`, where the `encoded_string` inside the square brackets is being repeated exactly `k` times. Note that `k` is guaranteed to be a positive integer.

You may assume that the input string is always valid; there are no extra white spaces, square brackets are well-formed, etc. Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, `k`. For example, there will not be input like `3a` or `2[4]`.

The test cases are generated so that the length of the output will never exceed $10^5$.

### Examples
*   **Input**: `s = "3[a]2[bc]"`
    *   **Output**: `"aaabcbc"`
*   **Input**: `s = "3[a2[c]]"`
    *   **Output**: `"accaccacc"`
*   **Input**: `s = "2[abc]3[cd]ef"`
    *   **Output**: `"abcabccdcdcdef"`

---

## Detailed Solution (C++)

A standard stack solution parses the string character-by-character.
We can implement an optimized C++ solution by storing indices instead of raw sub-strings on the stack.
*   We use a single `std::string result` to build the output.
*   Our stack only needs to store pairs of `std::pair<int, int>` which represent `{repeat_multiplier, start_index_in_result}`.
*   When encountering `'['`, we push the multiplier and the current length of `result` onto the stack.
*   When encountering `']'`, we retrieve the start index, extract the segment `result.substr(start)`, and append it `repeat - 1` times.
*   This approach avoids allocating separate strings on the stack, which dramatically reduces heap allocations.

### Standard C++ Production Code

```cpp
#include <string>
#include <vector>
#include <utility>

class Solution {
public:
    std::string decodeString(const std::string& s) noexcept {
        // stack stores: {repeat_count, start_index_in_result}
        std::vector<std::pair<int, int>> stk;
        std::string result;
        int curr_num = 0;

        for (const char ch : s) {
            if (ch >= '0' && ch <= '9') {
                curr_num = curr_num * 10 + (ch - '0');
            } else if (ch == '[') {
                stk.push_back({curr_num, static_cast<int>(result.size())});
                curr_num = 0; // Reset for next potential nested multiplier
            } else if (ch == ']') {
                auto [repeat, start] = stk.back();
                stk.pop_back();
                
                std::string seg = result.substr(start);
                // Append segment (repeat - 1) times since it is already in result once
                for (int j = 1; j < repeat; ++j) {
                    result += seg;
                }
            } else {
                result += ch;
            }
        }
        return result;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the Python implementation. In Python, list concatenations are highly optimized, so pushing strings and counts onto a stack is clean and simple.

```python
class Solution:
    def decodeString(self, s: str) -> str:
        """
        Decodes a nested repeat pattern string.
        
        Time Complexity: O(L) where L is the length of the decoded string.
        Space Complexity: O(D) where D is the maximum nesting depth of brackets.
        """
        stack = []
        curr_num = 0
        curr_str = ""

        for char in s:
            if char.isdigit():
                curr_num = curr_num * 10 + int(char)
            elif char == "[":
                # Push the current state (multiplier and the prefix string built so far)
                stack.append((curr_num, curr_str))
                curr_num = 0
                curr_str = ""
            elif char == "]":
                # Pop multiplier and prefix, build the new current string
                repeat, prefix = stack.pop()
                curr_str = prefix + curr_str * repeat
            else:
                curr_str += char

        return curr_str
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Large String Concatenations
*   In Python, string modification (`curr_str += char`) creates a new string on the heap because Python strings are immutable.
*   For very long strings, this can degrade performance due to quadratic copy operations.
*   **Alternative**: Store characters in a list (e.g. `curr_list.append(char)`) and use `''.join(curr_list)` to build the final string. In LeetCode, since the output size is capped at $10^5$, string additions are fast enough, but list joins are safer for massive strings.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(l)$ | Where $l$ is the length of the decoded string. We write each character to the output at least once. |
| **Space Complexity** | $\mathcal{O}(d + l)$ | Where $d$ is the maximum nesting depth (stack space) and $l$ is the output string buffer size. |

---

## Common Follow-Up Questions & How to Answer

### Q1: How can we implement this recursively?
*   **Answer**: We can write a recursive helper function that takes the current read index `idx`. It parses digits and letters, and recurses when encountering `[`. It returns the parsed string and the updated index.
*   **Recursive C++ Example**:
    ```cpp
    class Solution {
    private:
        std::string decode(const std::string& s, int& i) {
            std::string res;
            while (i < s.length() && s[i] != ']') {
                if (!std::isdigit(s[i])) {
                    res += s[i++];
                } else {
                    int k = 0;
                    while (i < s.length() && std::isdigit(s[i])) {
                        k = k * 10 + (s[i++] - '0');
                    }
                    i++; // skip '['
                    std::string decoded = decode(s, i);
                    i++; // skip ']'
                    while (k-- > 0) res += decoded;
                }
            }
            return res;
        }
    public:
        std::string decodeString(std::string s) {
            int i = 0;
            return decode(s, i);
        }
    };
    ```

### Q2: What if we push nested expressions like `100[100[100[a]]]`? How to prevent Out-Of-Memory (OOM)?
*   **Answer**: This is a potential **Denial of Service (DoS)** exploit. Deep nesting with large multipliers can generate gigabytes of data from a tiny input string, blowing up memory.
    *   **Mitigation**: In a production environment, track the length of the output string during parsing. If the cumulative output size exceeds a safety threshold (e.g., 5MB), abort execution and throw an exception.

---

## Pro-Tip: How to Impress the Interviewer

*   **Avoid Sub-string Heap Allocations**: Show off by highlighting the index-tracking optimization in C++. Standard stack solutions push substrings onto the stack, e.g., `std::stack<std::string>`. This invokes `std::string` constructors and triggers heap allocations for every bracket depth. Storing `{repeat_multiplier, start_index}` inside a simple `vector` keeps memory flat and avoids heap thrashing.
*   **Discuss AST / Parsing Context**: Mention that this problem is a simple parsing task of a context-free grammar ($S \to \text{term} \mid S S$, $\text{term} \to \text{chars} \mid \text{num}[S]$). Framing it as a grammar parser shows you understand formal compiler theory.
