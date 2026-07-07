# Min Stack

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer
- **Source**: LeetCode 155, Glassdoor

---

## Question Description

Design a stack that supports `push`, `pop`, `top`, and retrieving the minimum element in constant time.

Implement the `MinStack` class:
*   `MinStack()` initializes the stack object.
*   `void push(int val)` pushes the element `val` onto the stack.
*   `void pop()` removes the element on the top of the stack.
*   `int top()` gets the top element of the stack.
*   `int getMin()` retrieves the minimum element in the stack.

You must implement a solution with $\mathcal{O}(1)$ time complexity for each function.

### Examples
*   **Input**:
    ```text
    ["MinStack","push","push","push","getMin","pop","top","getMin"]
    [[],[-2],[0],[-3],[],[],[],[]]
    ```
    *   **Output**:
        `[null,null,null,null,-3,null,0,-2]`
    *   **Explanation**:
        ```cpp
        MinStack minStack;
        minStack.push(-2);
        minStack.push(0);
        minStack.push(-3);
        minStack.getMin(); // return -3
        minStack.pop();
        minStack.top();    // return 0
        minStack.getMin(); // return -2
        ```

---

## Detailed Solution (C++)

A standard stack only provides access to its top element. To retrieve the minimum element in $\mathcal{O}(1)$ time, we must maintain auxiliary state. 
The cleanest production-grade solution uses **two parallel stacks**:
1.  `st`: A standard stack storing the elements.
2.  `mn`: An auxiliary stack where the top element always represents the minimum value in the stack at that height.

### Standard C++ Production Code

```cpp
#include <vector>
#include <algorithm>
#include <stdexcept>

class MinStack {
private:
    std::vector<int> st; // Main value stack
    std::vector<int> mn; // Running minimum stack

public:
    MinStack() noexcept {}

    void push(int val) noexcept {
        st.push_back(val);
        if (mn.empty()) {
            mn.push_back(val);
        } else {
            mn.push_back(std::min(val, mn.back()));
        }
    }

    void pop() noexcept {
        if (!st.empty()) {
            st.pop_back();
            mn.pop_back();
        }
    }

    int top() const {
        if (st.empty()) {
            throw std::underflow_error("Stack is empty");
        }
        return st.back();
    }

    int getMin() const {
        if (mn.empty()) {
            throw std::underflow_error("Stack is empty");
        }
        return mn.back();
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the Python implementation. Instead of two separate lists, we can store values as tuples `(val, current_min)` inside a single list to keep the structure unified.

```python
class MinStack:
    def __init__(self):
        """
        Initializes the stack. We store tuples of (value, min_so_far).
        """
        self.stack = []

    def push(self, val: int) -> None:
        """
        Pushes element val onto the stack.
        """
        if not self.stack:
            self.stack.append((val, val))
        else:
            current_min = self.stack[-1][1]
            self.stack.append((val, min(val, current_min)))

    def pop(self) -> None:
        """
        Removes the element on the top of the stack.
        """
        if self.stack:
            self.stack.pop()

    def top(self) -> int:
        """
        Gets the top element of the stack.
        """
        if not self.stack:
            raise IndexError("pop from empty stack")
        return self.stack[-1][0]

    def getMin(self) -> int:
        """
        Retrieves the minimum element in the stack.
        """
        if not self.stack:
            raise IndexError("getMin from empty stack")
        return self.stack[-1][1]
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Amortized dynamic array resizing
*   Python's lists are dynamic arrays. Resizing a list allocates extra capacity to support subsequent $\mathcal{O}(1)$ push operations. Under extreme heap constraints, storing tuples `(val, min_val)` creates small overhead since tuples require $48$ bytes of metadata in Python, while a flat integer list is smaller.

### 2. Exceptions handling
*   According to LeetCode constraints, `pop`, `top`, and `getMin` will always be called on non-empty stacks. However, in production-grade code, it is critical to raise standard exceptions (`IndexError` or custom exceptions) to handle invalid access attempts safely.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(1)$ | All operations (`push`, `pop`, `top`, `getMin`) only perform indexing or basic arithmetic, taking constant time. |
| **Space Complexity** | $\mathcal{O}(n)$ | For $n$ elements pushed, we store $n$ states of the minimum. |

---

## Common Follow-Up Questions & How to Answer

### Q1: How can we optimize space when there are many duplicate pushes?
*   **Answer**: Instead of pushing to the `min` stack every time, we only push a value to the `min` stack if it is **less than or equal to** the current minimum.
    *   During a `pop` operation, we only pop from the `min` stack if the popped value from the main stack is equal to the top of the `min` stack.
    *   This prevents storing redundant minimums when many large elements are pushed consecutively.

### Q2: Can we implement this with $\mathcal{O}(1)$ auxiliary space? (The Difference Trick)
*   **Answer**: Yes, we can store only the **differences** between the pushed values and the running minimum. This requires a single stack of integers and a single `min_val` variable.
    *   **Push `val`**:
        *   If stack is empty: `min_val = val`, push `0`.
        *   If `val >= min_val`: push `val - min_val`.
        *   If `val < min_val`: push `val - min_val` (which is negative!), and update `min_val = val`.
    *   **Pop**:
        *   Let top element be `diff`.
        *   If `diff < 0`: the previous minimum was `min_val - diff`. Update `min_val = min_val - diff`.
        *   Pop from stack.
    *   **Top**:
        *   Let top element be `diff`.
        *   If `diff >= 0`: return `diff + min_val`.
        *   If `diff < 0`: return `min_val`.
    *   **Trade-off**: In languages with fixed-width integers, subtracting values can result in integer overflow. Thus, you must use 64-bit integers (`long long` in C++) to prevent this.

---

## Pro-Tip: How to Impress the Interviewer

*   **Warn About Custom Memory Allocators**: Mention that in high-performance C++ systems, invoking `std::vector::push_back` repeatedly calls default heap allocators which can cause memory fragmentation. Using a pre-allocated stack (`std::vector::reserve`) or custom memory arena allocators guarantees predictable allocation time and locality.
*   **Evaluate Thread Safety**: Discuss how adding locking mechanisms (`std::mutex` or read-write locks) would make this data structure thread-safe for producer-consumer pipelines, which is a key consideration in real-world systems architecture.
