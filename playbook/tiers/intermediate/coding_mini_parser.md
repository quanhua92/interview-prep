# Mini Parser

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / QA & Test Engineer
- **Source**: LeetCode 385, Glassdoor
- **Flashcards**: [DFS deck](../../flash_cards/coding/dfs.md)

---

## Question Description

Given a string `s` representing the serialization of a nested list, implement a parser to deserialize it and return the deserialized `NestedInteger`.

Each element is either an integer or a list whose elements may also be integers or other lists.

> [!NOTE]
> The `NestedInteger` class is a predefined interface provided by the environment. It can represent either a single integer or a nested list.

### Examples
*   **Input**: `s = "324"`
    *   **Output**: `324`
    *   **Explanation**: You should return a `NestedInteger` object which contains a single integer `324`.
*   **Input**: `s = "[123,[456,[789]]]"`
    *   **Output**: `[123,[456,[789]]]`
    *   **Explanation**: Return a `NestedInteger` object containing a nested list with 2 elements:
        1. An integer containing value `123`.
        2. A nested list containing two elements:
            *   An integer containing value `456`.
            *   A nested list containing one element:
                *   An integer containing value `789`.

---

## Detailed Solution (C++)

We can parse the serialized string using two primary approaches:
1. **Recursive DFS / Parser Approach**: We pass an index by reference. If the character is `'['`, we parse a list recursively. Otherwise, we parse a single integer.
2. **Iterative Stack-based Approach**: We push empty `NestedInteger` objects onto a stack when encountering `'['`, add integers/sub-lists to the top of the stack, and pop them when encountering `']'`.

Here, the **recursive DFS approach** is highly intuitive and matches the recursive definition of the `NestedInteger` structure.

### Standard C++ Production Code

```cpp
#include <string>
#include <vector>
#include <cctype>

// Pre-defined NestedInteger class interface for reference
class NestedInteger {
  public:
    NestedInteger();
    NestedInteger(int value);
    bool isInteger() const;
    int getInteger() const;
    void setInteger(int value);
    void add(const NestedInteger &elem);
    const std::vector<NestedInteger> &getList() const;
};

class Solution {
private:
    NestedInteger parse(const std::string& s, int& idx) noexcept {
        // Case 1: Parsing a single integer
        if (s[idx] != '[') {
            int start = idx;
            while (idx < static_cast<int>(s.length()) && (s[idx] == '-' || std::isdigit(s[idx]))) {
                idx++;
            }
            return NestedInteger(std::stoi(s.substr(start, idx - start)));
        }

        // Case 2: Parsing a nested list
        NestedInteger ni; // Default constructor creates a list
        idx++; // skip '['
        
        while (idx < static_cast<int>(s.length()) && s[idx] != ']') {
            ni.add(parse(s, idx));
            if (idx < static_cast<int>(s.length()) && s[idx] == ',') {
                idx++; // skip ',' separating elements
            }
        }
        idx++; // skip ']'
        return ni;
    }

public:
    NestedInteger deserialize(const std::string& s) noexcept {
        if (s.empty()) {
            return NestedInteger();
        }
        int idx = 0;
        return parse(s, idx);
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the iterative stack-based solution in Python, which is robust against recursion depth limitations and parses the structure sequentially.

```python
# Pre-defined NestedInteger interface for reference
# class NestedInteger:
#     def __init__(self, value=None):
#         """If value is not specified, initializes an empty list. Otherwise with an integer."""
#     def isInteger(self) -> bool:
#     def add(self, elem: 'NestedInteger') -> None:
#     def setInteger(self, value: int) -> None:
#     def getInteger(self) -> int:
#     def getList(self) -> List['NestedInteger']:

class Solution:
    def deserialize(self, s: str) -> NestedInteger:
        """
        Deserializes a nested list serialization string into a NestedInteger.
        
        Time Complexity: O(N)
        Space Complexity: O(N) for stack usage
        """
        if not s:
            return NestedInteger()
            
        # If the string represents a single integer
        if s[0] != '[':
            return NestedInteger(int(s))
            
        stack = []
        current = None
        i = 0
        n = len(s)
        
        while i < n:
            char = s[i]
            if char == '[':
                # Start of a new NestedInteger list
                new_ni = NestedInteger()
                stack.append(new_ni)
                i += 1
            elif char == ']':
                # End of a list, pop it and attach to its parent if exists
                finished = stack.pop()
                current = finished
                if stack:
                    stack[-1].add(finished)
                i += 1
            elif char == ',':
                i += 1
            else:
                # Parse integer
                j = i
                while j < n and (s[j].isdigit() or s[j] == '-'):
                    j += 1
                val = int(s[i:j])
                num_ni = NestedInteger(val)
                if stack:
                    stack[-1].add(num_ni)
                else:
                    current = num_ni
                i = j
                
        return current
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Pointer Traversal in Python
*   In C++, passing an integer index `idx` by reference is extremely cheap. In Python, primitives are immutable, so passing `idx` by value will not update it in parent calls.
*   **Workarounds**:
    1. Pass `idx` in a single-element list (e.g., `idx = [0]`) and modify `idx[0]`.
    2. Maintain `idx` as an instance variable `self.idx`.
    3. Use an iterative approach (like the Python code above) to avoid index tracking issues altogether.

### 2. Lexical Substring and Garbage Collection
*   Python's slicing `s[i:j]` creates a new string copy. For large inputs (length up to $5 \times 10^4$), repeated slicing can generate significant garbage collection overhead.
*   The iterative implementation above avoids slicing until it finds the boundaries of an integer, converting it directly using `int(s[i:j])`.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | Every character is scanned at most a constant number of times. Integer parsing checks each digit once. |
| **Space Complexity** | $\mathcal{O}(d)$ | Where $d$ is the nesting depth of the list (at most $\mathcal{O}(n)$). This space is consumed by the call stack (recursive) or the explicit stack (iterative). |

---

## Common Follow-Up Questions & How to Answer

### Q1: How would you validate if the input serialization string is well-formed?
*   **Answer**: To validate the input format:
    1. Track bracket balance (number of `'['` must match `']'`).
    2. Ensure commas are only placed between items (not directly after `'['` or before `']'`).
    3. Ensure no trailing characters are present after the top-level list/integer closes.
    4. Integers must only contain optional negative sign and valid digits.

### Q2: Can you write a generator to yield flat integers from the NestedInteger?
*   **Answer**: In Python, we can write a clean recursive generator using `yield from`:
    ```python
    def flatten(ni: NestedInteger):
        if ni.isInteger():
            yield ni.getInteger()
        else:
            for sub_ni in ni.getList():
                yield from flatten(sub_ni)
    ```

---

## Pro-Tip: How to Impress the Interviewer

*   **Explain C++ std::stoi Limits**: Mention that `std::stoi` can throw an out-of-range exception if the input number exceeds the limits of standard integers. According to constraints, LeetCode limits numbers to $[-10^6, 10^6]$, which comfortably fits within a 32-bit signed integer. However, pointing this out shows robustness in production engineering.
*   **Use Stack/Recursion Equivalence**: Point out that the recursive approach naturally maps to a depth-first search of a rose tree structure, whereas the iterative stack solution behaves like a pushdown automaton parsing a context-free grammar ($S \to [L] \mid \text{num}$, $L \to S, L \mid S$).
