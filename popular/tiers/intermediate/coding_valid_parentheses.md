# Valid Parentheses

- **Category**: Coding
- **Difficulty**: Easy
- **Target Role**: Software Engineer / QA & Test Engineer
- **Source**: LeetCode 20, Glassdoor
- **Flashcards**: [Stack deck](../../flash_cards/coding/stack.md)

---

## Question Description

Given a string `s` containing just the characters `'('`, `')'`, `'{'`, `'}'`, `'['` and `']'`, determine if the input string is valid.

An input string is valid if:
1.  Open brackets must be closed by the same type of brackets.
2.  Open brackets must be closed in the correct order.
3.  Every close bracket has a corresponding open bracket of the same type.

### Examples
*   **Input**: `s = "()"`
    *   **Output**: `true`
*   **Input**: `s = "()[]{}"`
    *   **Output**: `true`
*   **Input**: `s = "(]"`
    *   **Output**: `false`
*   **Input**: `s = "([])"`
    *   **Output**: `true`
*   **Input**: `s = "([)]"`
    *   **Output**: `false`

---

## Detailed Solution (C++)

A standard linear scan with a **Stack** data structure is optimal.
To simplify the character mapping and comparison code in interviews, we can use an elegant pattern: **when encountering an opening bracket, push its expected closing bracket onto the stack**.
When we encounter a closing bracket, we simply compare it directly to `st.top()`. This eliminates the need to map closing brackets to opening brackets during pop comparison.

### Standard C++ Production Code

```cpp
#include <string>
#include <stack>

class Solution {
public:
    bool isValid(const std::string& s) noexcept {
        std::stack<char> st;

        for (const char ch : s) {
            if (ch == '(') {
                st.push(')');
            } else if (ch == '[') {
                st.push(']');
            } else if (ch == '{') {
                st.push('}');
            } else {
                // If stack is empty (no matching open bracket) or 
                // top character doesn't match the closing bracket
                if (st.empty() || st.top() != ch) {
                    return false;
                }
                st.pop();
            }
        }

        return st.empty();
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the Python implementation using the same expected closing bracket matching pattern.

```python
class Solution:
    def isValid(self, s: str) -> bool:
        """
        Validates if parenthesized string s is well-formed.
        
        Time Complexity: O(N)
        Space Complexity: O(N)
        """
        stack = []

        for char in s:
            if char == '(':
                stack.append(')')
            elif char == '[':
                stack.append(']')
            elif char == '{':
                stack.append('}')
            else:
                # If stack is empty or current closing char doesn't match top
                if not stack or stack.pop() != char:
                    return False

        return len(stack) == 0
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. `list` as a Stack
*   In Python, standard lists `[]` are used as stacks. Adding elements using `.append()` and removing elements using `.pop()` run in $\mathcal{O}(1)$ amortized time.
*   Unlike C++ `std::stack`, Python lists are dynamic arrays, so resizing events will copy references to a larger array. However, this amortizes to constant time.

### 2. Early Termination Performance
*   If the string length is odd, it is impossible for all brackets to be paired. We can check `len(s) % 2 != 0` at the very beginning to return `False` immediately, saving execution time.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | We scan the string of length $n$ exactly once. Each character is pushed or popped at most once. |
| **Space Complexity** | $\mathcal{O}(n)$ | In the worst case (e.g. `"((((((("`), the stack stores all characters of the string. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if the string contains non-bracket characters (e.g. `"a + (b * c)"`)?
*   **Answer**: We can simply ignore any non-bracket characters and only run the push/pop logic when encountering bracket characters (`(`, `)`, `[`, `]`, `{`, `}`).

### Q2: What if we only have one type of bracket (e.g. only `(` and `)`)? Can we optimize space?
*   **Answer**: Yes. If only one type of bracket exists, we don't need a stack. We can just use an integer counter initialized to `0`.
    *   Increment the counter when seeing `(`.
    *   Decrement the counter when seeing `)`.
    *   If the counter ever drops below `0`, return `false` (unbalanced).
    *   At the end, return `true` if the counter is exactly `0`. This reduces space complexity to $\mathcal{O}(1)$.

---

## Pro-Tip: How to Impress the Interviewer

*   **Expected Closing Bracket Strategy**: Highlight the design choice of pushing the closing bracket (`')'`, `']'`, `'}'`) instead of the opening bracket (`'('`, `'['`, `'{'`). This eliminates the lookup mapping step during popping and leads to cleaner, less bug-prone code.
*   **Explain the Chomsky Hierarchy**: Mention that matching arbitrary nested parentheses is a classic **Context-Free Language (CFL)** problem (specifically, the Dyck language). It cannot be parsed by a regular expression (Finite Automaton) because it requires memory of arbitrary depth. This shows strong computer science theory background.
