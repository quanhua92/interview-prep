# Fast & Slow Pointers (Linked List Patterns)

## One-Liner
Use two pointers moving at different speeds through a linked list to detect cycles, find the middle node, or locate specific positions -- all in O(1) space.

## What Interviewers Are Actually Testing
Linked list problems test **pointer discipline**, not algorithmic sophistication. Interviewers look for:
- Do you use a dummy/sentinel head node to handle edge cases cleanly?
- Do you save `next` before modifying pointers (order of operations)?
- Do you state loop termination conditions precisely (`while curr` vs `while curr.next` vs `while curr.next and curr.next.next`)?
- Do you handle empty list, single node, and two-node cases?
- Do you achieve O(1) space for in-place operations instead of collecting nodes in an array?

## The 6 Linked List Patterns (CalibreOS Taxonomy)

### Pattern 1: Fast/Slow Pointers (Floyd's Algorithm)
- Two pointers advance at different speeds. Fast moves 2 nodes per step, slow moves 1.
- Use for: cycle detection, finding the middle node, finding the start of a cycle, kth-from-end.
- Key invariant: when fast reaches the end in an acyclic list, slow is exactly at the middle.

### Pattern 2: In-Place Reversal
- Reverse a sublist or entire list by rewiring `.next` pointers left-to-right.
- Three-pointer technique: `prev`, `curr`, `next_node`.
- Use for: Reverse Linked List I/II, Reverse Nodes in K-Groups, Palindrome check.

### Pattern 3: Merge / Combine
- Merge two sorted lists with a dummy head. Extend to K lists via a min-heap.
- Use for: Merge Two Sorted Lists, Merge K Sorted Lists, Sort List (merge sort variant).
- Key: always attach `dummy.next` to avoid if-else for the result head.

### Pattern 4: Reorder / Rearrange
- Find the middle, reverse the second half, then merge alternately.
- Use for: Reorder List (L0->Ln->L1->Ln-1), Palindrome Linked List.
- Combines fast/slow + reversal + merge -- a common hard-level combo.

### Pattern 5: Two Pointers (Offset / Gap)
- Advance one pointer N steps ahead, then move both until the leader hits the end.
- Use for: Remove Nth Node From End, find kth from end.
- Key: use a dummy head so the Nth-from-end removal works even for the head node.

### Pattern 6: Multiple Lists / Intersection
- Advance both pointers through their lists; when one ends, redirect to the other list's head.
- After at most 2 passes each, they meet at the intersection or both hit null simultaneously.
- Use for: Intersection of Two Linked Lists, Find Duplicate Number (cycle variant).

## Key Design Decisions

### When to Use a Dummy/Sentinel Head
- **Required**: in-place reversal of sublists (head may change), merge operations (head selection logic), removal operations (head may be the target)
- **Not required**: simple fast/slow traversal, intersection detection

### Floyd's Cycle Detection -- Three Variants
1. **Cycle detection**: Fast moves 2 steps, slow moves 1. If they meet, cycle exists.
2. **Finding cycle start**: After detection, reset slow to head. Move both at speed 1. The node where they meet is the cycle start.
3. **Finding the middle**: Run fast/slow without cycle logic. When fast hits end, slow is at middle. For even-length lists, `while fast.next and fast.next.next` gives the first middle.

## Complexity and Sentinel Requirements

| Pattern | Time | Space | Dummy Head Required | Key Problems |
|---------|------|-------|---------------------|--------------|
| Fast / Slow Pointers | O(n) | O(1) | No | LC 141, LC 142, LC 876, LC 287 |
| In-Place Reversal | O(n) | O(1) | Yes (for sublist/head removal) | LC 206, LC 92, LC 25 |
| Merge Two Sorted | O(n+m) | O(1) | Yes (eliminates head selection) | LC 21, LC 148 |
| Merge K Sorted (heap) | O(N log k) | O(k) | Yes | LC 23 |
| Two-Pointer Gap | O(n) | O(1) | Yes (head removal case) | LC 19, LC 61 |
| Intersection / Cycle-in-Array | O(m+n) | O(1) | No | LC 160, LC 287 |
| Reorder / Palindrome Combo | O(n) | O(1) | No | LC 143, LC 234 |

## The 4 Most Common Linked List Interview Bugs

1. **Lost forward pointer**: Writing `curr.next = prev` before `next_node = curr.next`. Always save `next_node` first.
2. **Skipping the dummy head**: Handling the head node as a special case in reversal or removal. Use a dummy node; it absorbs all head-change logic.
3. **Wrong termination condition**: Using `while curr.next` when you need `while curr`, or vice versa. Draw the final state before coding.
4. **Heap TypeError on equal values in Merge K Lists**: Comparing `ListNode` objects when two heap entries have the same value. Always add a `counter` as the second tuple element.

## Deep Dive Topics

### Reorder List (LC 143) and Palindrome Check -- Combo Problems
These chain three sub-patterns: **find middle -> reverse second half -> merge/compare**. They test whether candidates know all three sub-patterns.

**Reorder List** (L0 -> Ln -> L1 -> Ln-1 -> ...):
1. Find the middle using fast/slow pointers.
2. Reverse the second half in place.
3. Merge the two halves alternately (first half and reversed second half).

**Palindrome Linked List**: Same steps 1 and 2, but compare values node-by-node instead of merging.

Key: Set `second.next = None` before reversing to cleanly cut the list. In-place approach achieves O(n) time and O(1) space (stack approach fails the follow-up).

### Intersection of Two Linked Lists (LC 160)
Pointer A traverses list A then list B; pointer B traverses list B then list A. After at most `len(A) + len(B)` steps, they meet at the intersection node (or both hit `None` simultaneously). Both pointers walk the same total distance.

### Find the Duplicate Number (LC 287)
An array of n+1 integers where values are in [1, n] can be modeled as a linked list where `arr[i]` is the next pointer from node `i`. The duplicate creates a cycle. Apply Floyd's cycle detection directly on the "linked list" -- no extra space, no sorting.

This is a meta-pattern: recognize when an array or function can be interpreted as a linked list and apply Floyd's algorithm.

## What to Say in the Interview (Before Coding)
1. **Pattern identification**: "This is a [fast/slow pointer / reversal / merge] problem."
2. **Edge cases**: "I'll handle empty list, single node, and two-node cases."
3. **Dummy head decision**: "I'll use a dummy head here because the head node could be modified."
4. **Complexity**: "This will be O(n) time and O(1) space -- I'll reverse in place, not use an array."
5. **Pointer order**: "I'll save `next_node` before overwriting `curr.next` to avoid losing the rest of the list."

Then draw the pointer diagram on the whiteboard before writing any code. Interviewers at Google explicitly credit this step.

## Follow-Up Variations
- How would you reverse nodes in K-groups where partial groups are reversed too?
- What happens when you need to detect a cycle in a doubly-linked list?
- How would you flatten a multilevel doubly-linked list using these patterns?
- Can you merge K sorted lists without a heap (divide-and-conquer approach)?

Source: [Linked List Patterns: Fast/Slow Pointers, Reversal, and Merge (CalibreOS)](https://www.calibreos.com/learn/dsa-linked-lists)
