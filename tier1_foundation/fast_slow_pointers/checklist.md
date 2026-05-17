# Fast & Slow Pointers -- Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Problem Classification (1-2 min)
- [ ] Identify the linked list pattern:
  - [ ] Fast/Slow Pointers (cycle detection, middle node, cycle start)
  - [ ] In-Place Reversal (full list, sublist, K-groups)
  - [ ] Merge / Combine (two sorted, K sorted)
  - [ ] Reorder / Rearrange (reorder list, palindrome check)
  - [ ] Two-Pointer Gap (remove Nth from end, kth from end)
  - [ ] Multiple Lists / Intersection (intersection, duplicate number)
- [ ] State edge cases out loud:
  - [ ] Empty list (head is None)
  - [ ] Single node
  - [ ] Two-node list
  - [ ] Even-length vs odd-length list (for middle finding)

## Phase 2: Setup (1-2 min)
- [ ] Decide whether a dummy/sentinel head is needed:
  - [ ] Required if: head node may be modified/removed, sublist reversal, merge, remove operations
  - [ ] Not required if: simple traversal, cycle detection, intersection
- [ ] State the pointer roles:
  - [ ] Fast/slow: `slow = slow.next`, `fast = fast.next.next`
  - [ ] Reversal: `prev`, `curr`, `next_node` (three-pointer template)
  - [ ] Gap: advance leader N steps, then move both
- [ ] State complexity before coding:
  - [ ] Time: O(n) for all linked list traversals
  - [ ] Space: O(1) -- always in-place, never collect into array

## Phase 3: Core Implementation (5-8 min)
- [ ] Write the pointer initialization
- [ ] For cycle detection:
  - [ ] Use `while fast and fast.next` (check `fast.next` before `fast.next.next`)
  - [ ] After meeting, reset slow to head for cycle start
  - [ ] Move both at speed 1 until they meet again
- [ ] For reversal:
  - [ ] **CRITICAL**: Save `next_node = curr.next` BEFORE `curr.next = prev`
  - [ ] After loop, `prev` is the new head
  - [ ] For sublist: reconnect `pre.next = prev` and `tail.next = curr`
- [ ] For K-groups:
  - [ ] Peek ahead K nodes before reversing (check group is complete)
  - [ ] Partial groups (< K nodes) left as-is
- [ ] For merge:
  - [ ] Use dummy head: `curr` starts at `dummy`, return `dummy.next`
  - [ ] Attach remainder: `curr.next = l1 if l1 else l2`
- [ ] For merge K lists:
  - [ ] Use min-heap with tie-breaking counter: `(val, counter, node)`
  - [ ] Pop min, attach to result, push successor
- [ ] For remove Nth from end:
  - [ ] Advance fast N steps, then move both while `fast.next` (not `fast`)
  - [ ] `slow.next = slow.next.next` does the removal

## Phase 4: Edge Case Verification (2-3 min)
- [ ] Trace through with an empty list
- [ ] Trace through with a single node
- [ ] Trace through with two nodes
- [ ] Trace through with the head node as the target (for removal problems)
- [ ] Verify termination condition:
  - [ ] `while curr` vs `while curr.next` vs `while curr.next and curr.next.next`
  - [ ] Which one you need depends on whether you access `curr.next.next`

## Phase 5: Interview Communication (ongoing)
- [ ] Before coding: "This is a [pattern] problem."
- [ ] Before coding: "I'll handle empty list, single node, and two-node cases."
- [ ] Before coding: "I'll use a dummy head because [reason]."
- [ ] Before coding: "This will be O(n) time and O(1) space."
- [ ] Before coding: "I'll save `next_node` before overwriting `curr.next`."
- [ ] Draw the pointer diagram before writing any code

## Phase 6: Common Pitfalls to Avoid
- [ ] Did NOT lose the forward pointer (save `next_node` first)
- [ ] Did NOT forget dummy head when head could change
- [ ] Did NOT use wrong loop termination (`while curr` vs `while curr.next`)
- [ ] Did NOT forget tie-breaking counter in merge K lists heap
- [ ] Did NOT use a stack/array where O(1) space is expected

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:

Source: [Linked List Patterns: Fast/Slow Pointers, Reversal, and Merge (CalibreOS)](https://www.calibreos.com/learn/dsa-linked-lists)
