# Middle of the Linked List

- **Category**: Coding
- **Difficulty**: Easy
- **Target Role**: Software Engineer
- **Source**: LeetCode 876, Glassdoor

---

## Question Description

Given the `head` of a singly linked list, return *the middle node of the linked list*.

If there are two middle nodes, return **the second middle node**.

### Examples
*   **Input**: `head = [1,2,3,4,5]`
    *   **Output**: `[3,4,5]` (returns the node with value 3 and the remaining list)
    *   **Explanation**: The middle node of the list is node 3.
*   **Input**: `head = [1,2,3,4,5,6]`
    *   **Output**: `[4,5,6]`
    *   **Explanation**: Since the list has two middle nodes with values 3 and 4, we return the second one.

---

## Detailed Solution (C++)

Using a two-pointer approach (often called the **Tortoise and the Hare**), we can find the middle in a single pass:
1.  Initialize both `slow` and `fast` pointers at the `head`.
2.  Traverse the list:
    *   Move `slow` forward by 1 step: `slow = slow->next`.
    *   Move `fast` forward by 2 steps: `fast = fast->next->next`.
3.  When `fast` reaches the end of the list (meaning `fast` or `fast->next` becomes `nullptr`), the `slow` pointer will be exactly at the middle node of the list.

### Standard C++ Production Code

```cpp
#include <cstddef>

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* middleNode(ListNode* head) noexcept {
        // Edge Case: If the list is empty or has only one element, return head
        if (!head || !head->next) {
            return head;
        }

        ListNode *slow = head;
        ListNode *fast = head;

        // Traverse until fast reach the end of the list
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the type-hinted, iterative Python implementation.

```python
from typing import Optional

# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def middleNode(self, head: Optional[ListNode]) -> Optional[ListNode]:
        """
        Finds the middle of a singly-linked list.
        If there are two middle nodes, returns the second middle node.
        
        Time Complexity: O(N)
        Space Complexity: O(1)
        """
        slow = head
        fast = head

        # Loop terminates when fast reaches the end
        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next

        return slow
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Pointer Dereferencing Safety
*   Just like in C++, checking `while fast and fast.next:` in Python is crucial to avoid a runtime `AttributeError` when accessing `fast.next.next`.
*   If `fast` is `None` or `fast.next` is `None`, the loop ends safely.

### 2. Slicing/Iterative Alternative Risks
*   A common anti-pattern in Python is converting the linked list into a Python `list` (array) to find the middle via index arithmetic (`arr[len(arr) // 2]`).
*   While this achieves $\mathcal{O}(n)$ time complexity, it requires $\mathcal{O}(n)$ auxiliary space to store the node references. Under tight system constraints or memory-bound tasks, the two-pointer solution is highly preferred as it maintains $\mathcal{O}(1)$ space.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | The fast pointer reaches the end in $n/2$ steps, making a single traversal of the list. |
| **Space Complexity** | $\mathcal{O}(1)$ | Only two pointer variables are allocated. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if we want the FIRST middle node in an even-length list?
*   **The Answer**: For a list of length 4 (e.g., `[1, 2, 3, 4]`), the default code returns `3` (the second middle node). If we want to return `2` (the first middle node), we can modify the loop condition to stop one step earlier.
*   **Modification**:
    ```cpp
    ListNode* slow = head;
    ListNode* fast = head;
    // Look ahead 2 nodes: stops fast before it reaches the final node
    while (fast && fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
    ```
    *   *Dry Run on `[1, 2, 3, 4]`*: 
        *   Start: `slow = 1`, `fast = 1`.
        *   `fast->next` is 2, `fast->next->next` is 3 (not null). Advance: `slow = 2`, `fast = 3`.
        *   Next check: `fast = 3`, `fast->next` is 4, but `fast->next->next` is `nullptr`. Loop terminates.
        *   Returns `slow` (which is `2`).

### Q2: How would you delete the middle node of the list? (LeetCode 2095)
*   **The Answer**: To delete a node from a singly linked list, we must know its predecessor.
    *   Maintain a `prev` pointer initialized to `nullptr`.
    *   In the loop, assign `prev = slow` right before updating `slow`.
    *   After the loop, delete the middle node by linking `prev->next = slow->next`, and then freeing the memory of `slow` (in C++).

### Q3: Why is this method critical for sorting a linked list? (LeetCode 148)
*   **The Answer**: This two-pointer split method is the foundation of **Merge Sort** on a linked list. In Merge Sort, we divide the list into two halves, recursively sort them, and merge them. Finding the middle node allows us to disconnect the two halves (`slow->next = nullptr`) in $\mathcal{O}(n)$ time and $\mathcal{O}(1)$ space.

---

## Pro-Tip: How to Impress the Interviewer

*   **Highlight Cache-Friendliness**: Discuss how traversing a linked list causes CPU cache misses because the nodes are scattered across heap memory. Mention that if this list was stored in a contiguous block (like in an custom-allocated pool/arena allocator), the traversal would benefit from CPU prefetching.
*   **Address Multi-threaded Access Safety**: Point out that if the linked list is mutable and shared across multiple threads, read-only traversals like `middleNode` require synchronization or must operate on a local snapshot to avoid race conditions (e.g., another thread deleting a node currently being accessed by `fast->next`).
