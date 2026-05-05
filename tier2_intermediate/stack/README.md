# Stack

## Core Idea
A stack is a LIFO (Last In, First Out) data structure. Push elements onto the top, pop from the top. Stacks are ideal for problems involving nested structures, matching pairs, and "undo" operations.

## When to Recognize
- "Valid parentheses" / "matching brackets"
- "Decode string" / "nested patterns"
- "Min stack" / "max stack"
- "Next greater element" (also see Monotonic Stack)
- "Basic calculator" / "evaluate expression"
- "Daily temperatures" (also see Monotonic Stack)

## Complexity
- **Time:** O(n) — each element pushed/popped at most once
- **Space:** O(n) — worst case all elements on stack

## Key Variants
1. **Matching brackets** — push opening, pop and match on closing
2. **Nested structure decoding** — stack stores (count, prefix) pairs
3. **Min/Max stack** — auxiliary stack tracks running minimum/maximum

## Practice Problems

| # | Problem | Difficulty |
|---|---------|------------|
| 20 | [Valid Parentheses](./problems/p020_valid_parentheses.py) | Easy |
| 394 | [Decode String](./problems/p394_decode_string.py) | Medium |
| 155 | [Min Stack](./problems/p155_min_stack.py) | Medium |

## Common Pitfalls
- Forgetting to check that the stack is empty before accessing `stack[-1]`.
- Not handling the case where input ends with unmatched opening brackets.
- Using `stack.pop()` without checking if the stack is empty first.
