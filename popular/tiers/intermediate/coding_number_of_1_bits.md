# Number of 1 Bits

- **Category**: Coding
- **Difficulty**: Easy
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 191, Glassdoor
- **Flashcards**: [Bit Manipulation deck](../../flash_cards/coding/bit_manipulation.md)

---

## Question Description

Given a positive integer `n`, write a function that returns the number of set bits (also known as the **Hamming weight** or **population count**) in its binary representation.

### Examples

*   **Input**: `n = 11` (Binary: `1011`)
    *   **Output**: `3`
    *   **Explanation**: The binary representation has three set bits.
*   **Input**: `n = 128` (Binary: `10000000`)
    *   **Output**: `1`
    *   **Explanation**: The binary representation has one set bit.
*   **Input**: `n = 2147483645` (Binary: `1111111111111111111111111111101`)
    *   **Output**: `30`

### Constraints
*   $1 \le n \le 2^{31} - 1$

---

## Detailed Solution (C++)

There are three main ways to compute the Hamming weight:
1.  **Bit-by-Bit Shift**: Check each of the 32 bits one by one. This takes $\mathcal{O}(32)$ iterations regardless of the number of set bits.
2.  **Brian Kernighan's Algorithm**: 
    The expression `n & (n - 1)` clears the lowest set bit (rightmost `1` bit) of `n`. For example:
    *   `n     = 12` (`1100`)
    *   `n - 1 = 11` (`1011`)
    *   `n & (n - 1) = 8` (`1000`)
    
    By looping and executing `n &= n - 1` until `n` becomes `0`, we only iterate as many times as there are `1` bits in the integer. This is highly efficient for sparse bit arrays.
3.  **Built-in POPCNT instruction**: Modern CPUs have a dedicated hardware instruction (`POPCNT`) to count bits in a single CPU cycle. We can access this in C++ via compilers intrinsics (`__builtin_popcount`).

### Standard C++ Production Code

```cpp
#include <cstdint>

class Solution {
public:
    int hammingWeight(uint32_t n) noexcept {
        int count = 0;
        
        // Brian Kernighan's Algorithm
        while (n != 0) {
            n &= (n - 1); // Clears the lowest set bit
            count++;
        }
        
        return count;
    }
    
    // Alternative: Hardware Accelerated Popcount
    int hammingWeightHardware(uint32_t n) noexcept {
        return __builtin_popcount(n);
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the type-hinted Python implementation using Brian Kernighan's algorithm.

```python
class Solution:
    def hammingWeight(self, n: int) -> int:
        """
        Counts the number of set bits in an integer.
        
        Time Complexity: O(k) where k is the number of set bits (at most 32).
        Space Complexity: O(1)
        """
        count = 0
        while n:
            n &= (n - 1)  # Clear the lowest set bit
            count += 1
        return count

    def hammingWeightBuiltin(self, n: int) -> int:
        """
        Alternative: Python 3.10+ native bit_count() method, which is implemented
        in C using hardware POPCNT if available.
        """
        return n.bit_count()
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Python 3.10+ `int.bit_count()`
* Starting in Python 3.10, the `int` class has a native `bit_count()` method that returns the number of set bits.
* For older versions of Python, a common shorthand is `bin(n).count('1')`. However, `bin(n)` produces an intermediate string representation of the binary digits (e.g. `'0b1011'`), which allocates heap memory and is much slower than bitwise operations.

### 2. Arbitrary Precision and Sign Bit
* In Python, integers have arbitrary precision. A negative integer in Python (like `-1`) is represented under-the-hood with infinite 2s complement sign-extension (infinite sequence of leading `1` bits). Thus, checking `hammingWeight` of a negative number in Python can lead to infinite loops unless masked (e.g., `n = n & 0xffffffff`).

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(k)$ | Loop runs exactly $k$ times, where $k$ is the number of set bits (Hamming weight). Worst case is $\mathcal{O}(32)$ for 32-bit integers. |
| **Space Complexity** | $\mathcal{O}(1)$ | Uses constant memory. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What is the complexity if you need to run this on a stream of 64-bit integers?
* **Answer**: If we need to process integers repeatedly, Brian Kernighan's algorithm can be replaced with a **lookup table (LUT)**. 
  * We can precompute the Hamming weight of all 8-bit integers ($256$ values) and store them in a static array.
  * For any 64-bit integer, we split it into eight 8-bit chunks and look up their values:
    $$\text{count} = \text{LUT}[n \ \& \ 0\text{xff}] + \text{LUT}[(n \gg 8) \ \& \ 0\text{xff}] + \dots$$
  * This runs in $\mathcal{O}(1)$ operations (exactly 8 lookups and shifts).

### Q2: How can we implement bit count using parallel bit summation (SWAR - SIMD Within A Register)?
* **Answer**: SWAR counts bits by performing divide-and-conquer additions on adjacent bit segments in parallel:
  ```cpp
  uint32_t countBits(uint32_t i) {
      i = i - ((i >> 1) & 0x55555555); // count pairs
      i = (i & 0x33333333) + ((i >> 2) & 0x33333333); // count nibbles
      i = (i + (i >> 4)) & 0x0F0F0F0F; // count bytes
      i = i + (i >> 8);
      i = i + (i >> 16);
      return i & 0x0000003F;
  }
  ```

---

## Pro-Tip: How to Impress the Interviewer

* **Demonstrate Low-Level/Hardware Knowledge**: Mention the `POPCNT` assembly instruction on x86/x64 and `LD` / `CNT` on ARM. Explain how compilers translate `__builtin_popcount` directly into a single hardware instruction when compiling with optimization flags like `-march=native`.
* **Mention Sign Extension Pitfalls**: Point out how negative numbers are handled differently in languages with fixed-width types (C++'s `uint32_t` handles this cleanly via unsigned wrap-around) versus Python's infinite-precision integers, showing full system-level awareness.
