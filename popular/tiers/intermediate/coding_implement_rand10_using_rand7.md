# Implement Rand10() Using Rand7()

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 470, Glassdoor
- **Flashcards**: [Randomized deck](../../flash_cards/coding/randomized.md)

---

## Question Description

Given the API `rand7()` that generates a uniform random integer in the range $[1, 7]$, write a function `rand10()` that generates a uniform random integer in the range $[1, 10]$. You can only call the API `rand7()`, and you shouldn't call any other API. Please do not use a language's built-in random API.

Each test case will have one internal argument `n`, the number of times that your implemented function `rand10()` will be called while testing. Note that this is not an argument passed to `rand10()`.

### Follow up:
*   What is the expected value for the number of calls to `rand7()`?
*   Can you minimize the number of calls to `rand7()`?

### Examples
*   **Input**: `n = 1`
    *   **Output**: `[2]`
*   **Input**: `n = 2`
    *   **Output**: `[8, 2]`

---

## Detailed Solution (C++)

To generate a range larger than $7$, we can call `rand7()` twice. This can be conceptualized as creating a 2D coordinate grid of size $7 \times 7$:
$$\text{idx} = (\text{row} - 1) \times 7 + \text{col}$$
where $\text{row} = \text{rand7}()$ and $\text{col} = \text{rand7}()$.

This yields a uniform distribution of integers in the range $[1, 49]$.
Since we need a range of $10$, we can take the largest multiple of $10$ that is less than or equal to $49$, which is $40$.
*   If $\text{idx} \le 40$, we map it uniformly to $[1, 10]$ by returning `(idx - 1) % 10 + 1`.
*   If $\text{idx} > 40$, we reject the sample and try again. This technique is called **Rejection Sampling**.

### Standard C++ Production Code

```cpp
// The rand7() API is pre-defined. 
// int rand7();

class Solution {
public:
    int rand10() {
        int row, col, idx;
        do {
            row = rand7();
            col = rand7();
            idx = (row - 1) * 7 + col; // Range [1, 49]
        } while (idx > 40); // Reject [41, 49]
        
        return (idx - 1) % 10 + 1;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

```python
# The rand7() API is already defined for you.
# def rand7():
#     @return a random integer in the range 1 to 7

class Solution:
    def rand10(self) -> int:
        """
        Generates a random integer in range [1, 10] using rand7().
        
        Time Complexity: O(1) average (rejection sampling)
        Space Complexity: O(1)
        """
        while True:
            row = rand7()
            col = rand7()
            idx = (row - 1) * 7 + col  # Generates uniform [1, 49]
            
            if idx <= 40:
                return (idx - 1) % 10 + 1
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Loop Termination & Infinite Loops
*   Since rejection sampling can theoretically run forever (though the probability of infinite looping is $0$), Python has no recursion limit issues here because we use an iterative `while True` loop rather than recursive calls. Always prefer iterative loops for rejection sampling.

### 2. Random Number Generator Seeding
*   In Python, random testing is often mocked by setting seeds. When testing your solution locally, do not import the `random` module or write custom randomizers inside the production class, as LeetCode relies on a predefined `rand7()` implementation.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(1)$ average | The probability of acceptance is $40/49 \approx 0.816$. The expected number of loops is $1 / 0.816 \approx 1.225$. In the worst-case, it is $\mathcal{O}(\infty)$ but practically constant. |
| **Space Complexity** | $\mathcal{O}(1)$ | Constant auxiliary variables are maintained. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What is the expected number of calls to `rand7()` in the basic implementation?
*   **Answer**: Each loop iteration makes exactly 2 calls to `rand7()`. The success rate of each iteration is $40/49$. Using the geometric distribution, the expected number of iterations is $\frac{1}{p} = \frac{49}{40} = 1.225$. 
    *   Thus, the expected number of calls to `rand7()` is $2 \times 1.225 = 2.45$ calls.

### Q2: How can we optimize this to minimize the expected number of calls?
*   **Answer**: Instead of discarding the values from $41$ to $49$, we can reuse them!
    1. If we get $\text{idx} > 40$, we have a number in $[41, 49]$. Subtract 40 to get a number in $[1, 9]$ (call this $val_1$).
    2. Generate a new $\text{col} = \text{rand7}()$. Combine them: $\text{idx}_2 = (val_1 - 1) \times 7 + \text{col}$. This gives a range $[1, 63]$.
    3. Accept $[1, 60]$ (returning `(idx_2 - 1) % 10 + 1`). If $\text{idx}_2 > 60$, we have a number in $[61, 63]$.
    4. Subtract 60 to get a number in $[1, 3]$ (call this $val_2$).
    5. Generate a new $\text{col} = \text{rand7}()$. Combine: $\text{idx}_3 = (val_2 - 1) \times 7 + \text{col}$. This gives a range $[1, 21]$.
    6. Accept $[1, 20]$. If $\text{idx}_3 = 21$, we have 1 left. Since we cannot combine a range of 1 with $\text{rand7}()$ to get $\ge 10$, we start over.
    *   This reduces the expected number of calls to **$2.193$**!

---

## Pro-Tip: How to Impress the Interviewer

*   **Explain Shannon Entropy**: Mention that generating a number in $[1, 10]$ requires at least $\log_2(10) \approx 3.32$ bits of entropy. Each call to `rand7()` provides $\log_2(7) \approx 2.8$ bits of entropy. Therefore, we need at least $3.32 / 2.8 \approx 1.18$ calls to `rand7()`. Our optimized rejection sampling method ($2.19$ calls) is extremely close to the theoretical thermodynamic limit.
*   **Mention Hardware RNG Stalls**: Discuss that in systems programming, random number APIs (like `/dev/urandom` or hardware `RDRAND` instructions) can block or stall the CPU pipeline if the entropy pool is depleted. Rejection sampling strategies must balance mathematical accuracy with execution latency.
