# Fast & Slow Pointers

## Core Idea

Use two pointers that move at different speeds through a data structure.
The slow pointer advances one step at a time while the fast pointer advances
two steps. If there is a cycle, the fast pointer will eventually "lap" the
slow pointer (i.e., they will meet).

## When to Recognize

Look for these keywords in the problem statement:

- Linked list cycle detection, "detect cycle"
- "Middle of linked list", "find the middle node"
- "Happy number", "number theory cycle"
- "Circular array", "find duplicate number"
- Problems involving repeated transformations or loops in sequences

## Complexity

| Variant | Time | Space |
|---------|------|-------|
| Cycle detection in linked list | O(n) | O(1) |
| Find middle of linked list | O(n) | O(1) |
| Happy number (number theory) | O(log n) | O(1) |

## Key Insight

If there is no cycle, the fast pointer reaches the end (None) before the slow
pointer. If there is a cycle, both pointers are trapped inside it, and the
distance between them decreases by 1 on each step (since fast gains 1 step per
iteration). They are guaranteed to meet within O(cycle_length) steps.

## Problems in This Pattern

| Problem | Difficulty | Variant |
|---------|-----------|---------|
| P141 Linked List Cycle | Easy | Cycle detection in linked list |
| P202 Happy Number | Easy | Happy number (number theory cycle) |
| P876 Middle of the Linked List | Easy | Find middle node (non-cycle variant) |

## Template Variants

1. **Cycle detection** -- detect whether a linked list has a cycle
2. **Find middle** -- find the middle node of a linked list
3. **Happy number** -- detect cycles in a number transformation sequence

See `template.py` for annotated skeleton code for each variant.
