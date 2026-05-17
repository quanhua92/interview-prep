# Bit Manipulation -- Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Recognize the Pattern (1 min)
- [ ] Identify signal words: "unique element," "missing number," "count 1 bits," "subsets," "power of 2," "swap without temp"
- [ ] Determine which core property applies:
  - [ ] XOR self-inverse (pairs cancel) -- for unique/missing element problems
  - [ ] `n & (n-1)` -- for counting set bits or power-of-two check
  - [ ] `n & (-n)` -- for isolating lowest set bit (used in Single Number III)
  - [ ] Bitmask enumeration -- for subset/combination problems
- [ ] State the time/space target: most bit manipulation solutions are O(n) time, O(1) space

## Phase 2: Verbalize the Intuition (1-2 min)
- [ ] For XOR problems: "XOR is its own inverse -- a^a=0 and a^0=a -- so pairs cancel and the unique element survives"
- [ ] For power of two: "A power of 2 has exactly one set bit; subtracting 1 flips all bits below it, so n & (n-1) = 0"
- [ ] For Brian Kernighan's: "Each iteration of n &= (n-1) clears one set bit, so the loop runs k times for k set bits"
- [ ] For bitmask subsets: "Each subset of n elements maps to an n-bit number; iterate 0 to 2^n - 1"

## Phase 3: Code the Solution (3-5 min)
- [ ] Write the core bit operation correctly:
  - [ ] XOR fold: `result = 0; for n in nums: result ^= n`
  - [ ] Brian Kernighan's: `while n: n &= n-1; count += 1`
  - [ ] Power of 2: `n > 0 and (n & (n-1)) == 0`
  - [ ] Subset enumeration: `for mask in range(1 << n): check (mask >> i) & 1`
  - [ ] Missing number: XOR all indices and values together
- [ ] Handle edge cases:
  - [ ] n = 0 for power-of-two check (0 is NOT a power of 2)
  - [ ] Empty array (return 0 for XOR)
  - [ ] Negative numbers (Python integers are arbitrary precision -- may need 32-bit mask)
- [ ] State time and space complexity

## Phase 4: Handle Follow-Ups (2-3 min)
- [ ] "What if elements appear 3 times instead of 2?" -- Count bits at each position modulo 3, O(32n) time, O(1) space
- [ ] "What if there are TWO unique numbers?" -- XOR all to get a^b, isolate a differing bit with `xor & (-xor)`, split into two groups, XOR each group
- [ ] "What about integer overflow?" -- XOR approach avoids overflow vs. sum formula `n(n+1)/2`
- [ ] "Can you do this without a loop?" -- SWAR popcount or hardware `bin(n).count('1')` / `Integer.bitCount(n)`
- [ ] "Real-world applications?" -- Redis bitmaps, bloom filters, chess engine move generation, permission flags, Huffman coding

## Phase 5: Quick Reference Check (1 min)
- [ ] Get bit i: `(n >> i) & 1`
- [ ] Set bit i: `n | (1 << i)`
- [ ] Clear bit i: `n & ~(1 << i)`
- [ ] Toggle bit i: `n ^ (1 << i)`
- [ ] Lowest set bit: `n & (-n)`
- [ ] Clear lowest set bit: `n & (n - 1)`
- [ ] Power of 2: `n > 0 and (n & (n-1)) == 0`
- [ ] XOR swap: `a ^= b; b ^= a; a ^= b` (only when a and b are guaranteed different variables)
- [ ] Enumerate submasks: `sub = mask; while sub: use sub; sub = (sub-1) & mask`

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:

Source: [Bit Manipulation: XOR Tricks, Bit Masking & Power-of-Two Patterns (CalibreOS)](https://www.calibreos.com/learn/dsa-bit-manipulation)
