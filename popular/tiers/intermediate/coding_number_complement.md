# Number Complement

- **Category**: Coding
- **Difficulty**: Easy
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 476, LeetCode 1009, Glassdoor

---

## Question Description

The **complement** of an integer is the integer you get when you flip all the `0`'s to `1`'s and all the `1`'s to `0`'s in its binary representation.

For example, the integer `5` is `101` in binary (with no leading zero bits), and its complement is `010` which is `2` in decimal.

Given an integer `num`, return *its complement*.

### Examples

*   **Input**: `num = 5`
    *   **Output**: `2`
    *   **Explanation**: The binary representation of `5` is `101` (no leading zero bits), and its complement is `010`. So you need to output `2`.
*   **Input**: `num = 1`
    *   **Output**: `0`
    *   **Explanation**: The binary representation of `1` is `1` (no leading zero bits), and its complement is `0`. So you need to output `0`.

### Constraints
*   $1 \le \text{num} < 2^{31}$

---

## Detailed Solution (C++)

To find the complement of `num` (excluding leading zeros), we want to flip only the bits that are part of the active binary representation of `num`.
1.  **Determine Bit Length ($L$)**:
    We count how many bits are needed to represent `num`. For example, $5$ (`101`) needs $3$ bits.
2.  **Generate a Mask of $L$ Ones**:
    A mask of $L$ ones is created via:
    $$\text{mask} = (1 \ll L) - 1$$
    For $L=3$, $(1 \ll 3) - 1 = 8 - 1 = 7$ (`111` in binary).
3.  **XOR to Flip Bits**:
    XORing `num` with the mask flips all of its active bits:
    $$\text{complement} = \text{num} \oplus \text{mask}$$
    For $5$ (`101`) $\oplus$ $7$ (`111`) $= 2$ (`010`).

### C++ Integer Overflow Safety:
If `num` is $2^{31} - 1$ (the maximum signed 32-bit integer), $L = 31$.
Evaluating `1 << 31` using standard signed integers causes **undefined behavior (UB)** because shifting into the sign bit overflows a signed 32-bit integer.
To prevent this, we must perform the shift on an **unsigned integer** (using the `1u` literal) which is safe from signed overflow:
$$\text{mask} = (1u \ll L) - 1$$

### Standard C++ Production Code

```cpp
#include <cstdint>

class Solution {
public:
    int findComplement(int num) noexcept {
        // Calculate the number of bits needed to represent num
        int bits = 0;
        int temp = num;
        while (temp > 0) {
            bits++;
            temp >>= 1;
        }

        // Generate mask of 'bits' ones. Use 1u (unsigned) to prevent UB/overflow if bits == 31
        unsigned int mask = (1u << bits) - 1;

        // XORing with a mask of all ones flips the bits
        return num ^ static_cast<int>(mask);
    }

    // Alternative: Optimized using Count Leading Zeros intrinsic
    int findComplementOptimized(int num) noexcept {
        // __builtin_clz returns the number of leading 0-bits in a 32-bit int
        int leading_zeros = __builtin_clz(num);
        int active_bits = 32 - leading_zeros;
        
        unsigned int mask = (1u << active_bits) - 1;
        return num ^ static_cast<int>(mask);
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the type-hinted Python implementation. It uses Python's built-in `bit_length()` method to determine the number of active bits.

```python
class Solution:
    def findComplement(self, num: int) -> int:
        """
        Returns the complement of num by masking and XORing.
        
        Time Complexity: O(1) (bit_length is constant-time or near constant-time)
        Space Complexity: O(1)
        """
        # Determine the number of bits in the binary representation of num
        bits = num.bit_length()
        
        # Create a mask of 1s of the same length
        mask = (1 << bits) - 1
        
        # XOR num with the mask to flip all active bits
        return num ^ mask
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. The `bit_length()` Method
* Python's `int.bit_length()` returns the number of bits necessary to represent an integer in binary, excluding the sign and leading zeros. For example, `(5).bit_length()` returns `3`.
* This is a C-level operation, executing much faster than loop-based bit-shifting in Python.

### 2. Arbitrary Precision Negation
* A common mistake is using the bitwise NOT operator `~num`.
* In Python, integers have arbitrary precision. Applying `~num` flips all bits including the infinite leading sign bits (e.g. `~5` yields `-6`). We must use a mask to restrict the flip to only the active bits of `num`.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(1)$ | Counting bits and bitwise operations execute in constant time (at most 31 iterations, which is bounded). |
| **Space Complexity** | $\mathcal{O}(1)$ | Uses a constant amount of auxiliary memory. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if `num = 0`?
* **Answer**: If `num = 0`, its binary representation is `0`. The complement of `0` is `1`.
  * In the loop-based implementation, if `num = 0`, the loop `while (temp > 0)` does not execute, leaving `bits = 0`, and yielding `mask = 0`. XORing `0 ^ 0` would incorrectly return `0`.
  * However, the LeetCode constraint specifies $1 \le num < 2^{31}$, so `num` is never `0` in this problem. If it could be `0` (like in LeetCode 1009), we would add an explicit check: `if (num == 0) return 1;`.

### Q2: Can we solve this branchlessly without using loops or intrinsic CLZ?
* **Answer**: Yes, we can generate a mask of ones by propagating the highest set bit to the right using bitwise OR shifts:
  ```cpp
  int mask = num;
  mask |= mask >> 1;
  mask |= mask >> 2;
  mask |= mask >> 4;
  mask |= mask >> 8;
  mask |= mask >> 16;
  // Now mask contains all 1s from the MSB down to LSB
  return num ^ mask;
  ```
  This is branchless, loopless, does not use floats or intrinsics, and is extremely fast.

---

## Pro-Tip: How to Impress the Interviewer

* **Demonstrate UB Awareness**: Proactively discuss why doing `1 << 31` on a signed 32-bit integer is Undefined Behavior in C++. Explain how using `1u` (unsigned literal) avoids this constraint because unsigned arithmetic is guaranteed to wrap modulo $2^{32}$.
* **Propose the Bit-Propagation Hack**: Presenting the bit-propagation algorithm (under Q2) shows that you understand binary prefix operations and how to write high-performance, branchless CPU instruction blocks.
