# Linked List Cycle

- **Category**: Coding
- **Difficulty**: Easy
- **Target Role**: Software Engineer / Low-Level Developer
- **Source**: LeetCode 141, Glassdoor

---

## Question Description

Given `head`, the head of a linked list, determine if the linked list has a cycle in it.

There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the `next` pointer. Internally, `pos` is used to denote the index of the node that the tail's `next` pointer is connected to. **Note that `pos` is not passed as a parameter.**

Return `true` if there is a cycle in the linked list. Otherwise, return `false`.

### Examples
*   **Input**: `head = [3,2,0,-4]`, `pos = 1`
    *   **Output**: `true`
    *   **Explanation**: There is a cycle in the linked list, where the tail connects to the 1st node (0-indexed).
*   **Input**: `head = [1,2]`, `pos = 0`
    *   **Output**: `true`
    *   **Explanation**: There is a cycle in the linked list, where the tail connects to the 0th node.
*   **Input**: `head = [1]`, `pos = -1`
    *   **Output**: `false`
    *   **Explanation**: There is no cycle in the linked list.

---

## Detailed Solution (C++)

The standard approach to detect cycles in a singly-linked list without using extra memory is **Floyd's Cycle-Finding Algorithm** (also known as the "Tortoise and the Hare" algorithm). 

We maintain two pointers traversing the list at different speeds:
1.  **Slow Pointer (`slow`)**: Moves forward by 1 node at each step.
2.  **Fast Pointer (`fast`)**: Moves forward by 2 nodes at each step.

If there is no cycle, the fast pointer will eventually reach the end of the list (`nullptr`). If there is a cycle, the fast pointer will enter the cycle first and eventually catch up to the slow pointer, resulting in `slow == fast`.

### Standard C++ Production Code

```cpp
#include <cstddef>

// Definition for singly-linked list node.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    bool hasCycle(ListNode *head) noexcept {
        // Edge Case: An empty list or a list with only one node and no loop cannot have a cycle
        if (!head || !head->next) {
            return false;
        }

        ListNode *slow = head;
        ListNode *fast = head;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;

            // If the fast pointer catches up to the slow pointer, a cycle exists
            if (slow == fast) {
                return true;
            }
        }

        return false;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the iterative, type-hinted Python implementation using Floyd's Cycle-Finding Algorithm.

```python
from typing import Optional

# Definition for singly-linked list.
class ListNode:
    def __init__(self, x: int):
        self.val = x
        self.next = None

class Solution:
    def hasCycle(self, head: Optional[ListNode]) -> bool:
        """
        Determines if a linked list has a cycle using Floyd's Cycle-Finding Algorithm.
        
        Time Complexity: O(N)
        Space Complexity: O(1)
        """
        # Edge Case: empty list or list with a single node
        if not head or not head.next:
            return False

        slow = head
        fast = head

        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next

            # Identical object comparison using 'is' for speed and safety
            if slow is fast:
                return True

        return False
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Object Identity Comparison (`is` vs `==`)
*   In Python, comparing nodes using `==` will invoke the default class representation or custom equivalence operators if defined (checking value equivalence).
*   For cycle detection, we want to know if two pointer variables point to the exact same memory address (object identity).
*   Always use the `is` operator (`slow is fast`) instead of `==`. The `is` operator compares memory addresses directly (like comparing raw pointers in C++), which is faster and prevents unintended side effects from overridden value-comparison methods.

### 2. Guarding against AttributeError
*   When navigating nested properties (`fast.next.next`), we must guarantee that `fast` and `fast.next` are both non-null before dereferencing.
*   Checking `while fast and fast.next:` in Python prevents `AttributeError: 'NoneType' object has no attribute 'next'`.

### 3. Stack Space & Python Optimization
*   While cycles could conceptually be checked recursively, recursive traversal in Python uses $\mathcal{O}(N)$ memory on the execution stack.
*   Given Python's default stack recursion depth limit of $1000$, a long list would trigger a `RecursionError`. The iterative approach guarantees $\mathcal{O}(1)$ auxiliary space.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | In the worst case (with a cycle), the fast pointer will traverse the cycle at most twice before meeting the slow pointer. |
| **Space Complexity** | $\mathcal{O}(1)$ | Only two pointers are tracked, using constant auxiliary space. |

---

## Common Follow-Up Questions & How to Answer

### Q1: How do you find the exact node where the cycle begins? (LeetCode 142)
*   **The Answer**: Once the meeting point is found, reset the `slow` pointer to `head`. Keep the `fast` pointer at the meeting point. Then, move both pointers one step at a time. The node where they meet again is the start of the cycle.
*   **Mathematical Proof**: 
    Let the distance from the head to the cycle start node be $A$. Let the distance from the cycle start to the meeting point be $B$. Let the length of the cycle be $C$.
    *   Distance traveled by `slow` pointer: $A + B + k_1 \cdot C$
    *   Distance traveled by `fast` pointer: $A + B + k_2 \cdot C$
    *   Since the fast pointer runs twice as fast: 
        $$2(A + B + k_1 \cdot C) = A + B + k_2 \cdot C$$
        $$A + B = (k_2 - 2k_1) \cdot C = M \cdot C$$
        $$A = M \cdot C - B$$
    *   This implies that moving a pointer $A$ steps from the head reaches the same node as moving another pointer $A$ steps (which is $M \cdot C - B$ steps) from the meeting point. They will meet exactly at the cycle entrance.

### Q2: What if we cannot modify pointers? How would you solve this with a Hash Table?
*   **The Answer**: We can store the memory addresses of the visited nodes in a hash set. At each node, we check if it is already present in the set. If it is, a cycle is detected.
*   **Trade-off**:
    *   **Time Complexity**: $\mathcal{O}(n)$
    *   **Space Complexity**: $\mathcal{O}(n)$ to store list nodes.
    *   *System constraint*: A hash set requires dynamic memory allocation on the heap for each unique node. In low-level or embedded systems, heap allocations are expensive and can fail due to fragmentation. The two-pointer solution is highly preferred.

---

## Pro-Tip: How to Impress the Interviewer

*   **Mention Cache Locality**: Point out that linked lists inherently have poor cache locality compared to contiguous arrays. When traversing the linked list, dereferencing `next` pointers causes frequent CPU cache misses. In a performance-critical system, data structures like **Arena-allocated linked lists** (where nodes are stored in contiguous memory pages) or flat arrays are preferred to maximize L1/L2 cache hit rates.
*   **Identify the Cycle in Array Representation (LeetCode 287)**: Show that Floyd's Cycle-Finding Algorithm is not restricted to linked lists; it can be used to find duplicate values in arrays where each index points to another index, representing a functional graph.
