# Bit Manipulation

## Core Idea
Directly manipulate individual bits of integers using bitwise operators: AND (`&`), OR (`|`), XOR (`^`), NOT (`~`), left shift (`<<`), right shift (`>>`). Common tricks include Brian Kernighan's algorithm, XOR cancellation, and DP on bits.

## When to Recognize
- "Number of 1 bits" / "count set bits" / "hamming weight"
- "Single number" (find element appearing once, others twice)
- "Power of two"
- "Counting bits" for all numbers 0..n
- Problems involving binary representations or parity

## Complexity
- **Time:** O(k) for Brian Kernighan's where k = set bits; O(n) for DP approach
- **Space:** O(1) for most operations; O(n) for counting bits DP array

## Key Variants
1. **Brian Kernighan's algorithm** — `n &= (n - 1)` clears lowest set bit
2. **XOR trick** — pairs cancel out, leaving the unique element
3. **DP + bit manipulation** — `ans[i] = ans[i >> 1] + (i & 1)` for counting bits

## Practice Problems

| # | Problem | Difficulty |
|---|---------|------------|
| 191 | [Number of 1 Bits](./problems/p0191_number_of_1_bits.py) | Easy |
| 136 | [Single Number](./problems/p136_single_number.py) | Easy |
| 338 | [Counting Bits](./problems/p338_counting_bits.py) | Medium |
| 470 | [Implement Rand10() Using Rand7()](./solutions/p470_implement_rand10_using_rand7.py) | Medium |
| 476 | [Number Complement](./solutions/p476_number_complement.py) | Easy |

## Common Pitfalls
- Not masking to 32 bits when working with negative numbers (Python integers are arbitrary precision).
- Confusing bitwise AND (`&`) with logical AND (`and`).
- Off-by-one errors in DP counting bits (remember `ans[0] = 0`).
