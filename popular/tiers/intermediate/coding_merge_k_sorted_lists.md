# Merge k Sorted Lists

- **Category**: Coding
- **Difficulty**: Hard
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 23, Glassdoor

---

## Question Description

You are given an array of `k` linked-lists `lists`, where each linked-list is sorted in ascending order. Merge all the linked-lists into one sorted linked-list and return it.

### Examples
*   **Input**: `lists = [[1,4,5],[1,3,4],[2,6]]`
    *   **Output**: `[1,1,2,3,4,4,5,6]`
    *   **Explanation**: The linked-lists are:
        ```text
        [
          1 -> 4 -> 5,
          1 -> 3 -> 4,
          2 -> 6
        ]
        ```
        Merging them into one sorted list yields: `1 -> 1 -> 2 -> 3 -> 4 -> 4 -> 5 -> 6`.
*   **Input**: `lists = []`
    *   **Output**: `[]`
*   **Input**: `lists = [[]]`
    *   **Output**: `[]`

---

## Detailed Solution (C++)

The solution uses the **Divide and Conquer** paradigm. Instead of merging the lists sequentially (which would result in an $\mathcal{O}(N \cdot k)$ runtime where $N$ is the total number of elements), we pair up the lists and merge each pair. This is repeated until only one merged list remains.

The process resembles a reverse merge-sort:
1. Divide the array of lists into two halves: left and right.
2. Recursively merge the lists in the left half and the lists in the right half.
3. Merge the two resulting sorted lists in $\mathcal{O}(\text{length}_1 + \text{length}_2)$ time.

This reduces the number of merge steps from $k$ to $\log k$, bringing the overall time complexity to $\mathcal{O}(N \log k)$ and requiring only logarithmic call-stack space.

### Standard C++ Production Code

```cpp
#include <vector>

// Definition for singly-linked list node.
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeKLists(std::vector<ListNode*>& lists) {
        if (lists.empty()) {
            return nullptr;
        }
        return divideAndConquer(lists, 0, static_cast<int>(lists.size()) - 1);
    }

private:
    ListNode* divideAndConquer(const std::vector<ListNode*>& lists, int left, int right) {
        if (left > right) {
            return nullptr;
        }
        if (left == right) {
            return lists[left];
        }
        
        int mid = left + (right - left) / 2;
        ListNode* l1 = divideAndConquer(lists, left, mid);
        ListNode* l2 = divideAndConquer(lists, mid + 1, right);
        
        return mergeTwoLists(l1, l2);
    }

    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* tail = &dummy;
        
        while (l1 && l2) {
            if (l1->val <= l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        
        // Append the remaining list
        tail->next = l1 ? l1 : l2;
        
        return dummy.next;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

```python
from typing import List, Optional

# Definition for singly-linked list.
class ListNode:
    def __init__(self, val: int = 0, next: Optional['ListNode'] = None):
        self.val = val
        self.next = next

class Solution:
    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
        """
        Merges k sorted linked-lists using divide and conquer.
        
        Time Complexity: O(N log k)
        Space Complexity: O(log k) due to recursion stack
        """
        if not lists:
            return None
        return self._divide_and_conquer(lists, 0, len(lists) - 1)

    def _divide_and_conquer(self, lists: List[Optional[ListNode]], left: int, right: int) -> Optional[ListNode]:
        if left > right:
            return None
        if left == right:
            return lists[left]
        
        mid = left + (right - left) // 2
        l1 = self._divide_and_conquer(lists, left, mid)
        l2 = self._divide_and_conquer(lists, mid + 1, right)
        
        return self._merge_two_lists(l1, l2)

    def _merge_two_lists(self, l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
        dummy = ListNode(0)
        tail = dummy
        
        while l1 and l2:
            if l1.val <= l2.val:
                tail.next = l1
                l1 = l1.next
            else:
                tail.next = l2
                l2 = l2.next
            tail = tail.next
            
        tail.next = l1 or l2
        return dummy.next
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Priority Queue / Heap Gotcha in Python
*   If we use a min-heap (`heapq`) in Python, we store tuples like `(node.val, node)`. If two nodes have the same value, Python will attempt to compare the `ListNode` objects to break the tie, resulting in a `TypeError: '<' not supported between instances of 'ListNode' and 'ListNode'`.
*   To avoid this, we can insert a unique counter in the tuple: `(node.val, counter, node)`. This guarantees unique comparison keys.

### 2. Recursion Limit
*   The divide-and-conquer strategy has a maximum recursion depth of $\mathcal{O}(\log k)$. Since the constraint is $k \le 10^4$, the maximum depth is $\approx 14$. This is well within Python's default stack limit of $1000$ and does not risk `RecursionError`.

### 3. GC and Reference Cycles
*   Python's reference-counting garbage collector handles linked lists easily. However, if your list contains circular links (which shouldn't happen under correct execution), they will stay in memory until the cycle-detecting garbage collector runs. In performance-sensitive code, manually clearing reference fields (`node.next = None`) as you dismantle lists is a useful defensive programming practice.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(N \log k)$ | There are $\log k$ levels of merging. At each level, we merge pairs of lists, scanning a total of $N$ nodes. |
| **Space Complexity** | $\mathcal{O}(\log k)$ | Auxiliary stack space for the recursion tree. If implemented iteratively (in-place), space is $\mathcal{O}(1)$. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if the lists are too large to fit in memory?
*   **Answer**: This calls for **External Sorting**. We can perform a K-way merge using a min-heap, reading small portions of each list from disk (as streams or buffered inputs). We only keep the current head element of each list in memory inside the heap, processing and writing the merged output to disk continuously.

### Q2: Heap vs. Divide and Conquer — which is better?
*   **Answer**: 
    *   **Min-Heap**: Time is $\mathcal{O}(N \log k)$ and space is $\mathcal{O}(k)$ (for the heap size). Good if the input lists are arriving dynamically as streams.
    *   **Divide and Conquer**: Time is $\mathcal{O}(N \log k)$ and space is $\mathcal{O}(1)$ if implemented iteratively (merging lists in-place in the input vector). It avoids the overhead of managing a dynamic heap structure and offers better cache locality.

---

## Pro-Tip: How to Impress the Interviewer

*   **Mention Iterative Merge (O(1) Space)**: Point out that instead of recursive divide-and-conquer, we can merge the lists in a loop (`step = 1`, then `step *= 2`), merging pairs in-place within the array. This gets rid of the recursion stack entirely, yielding true $\mathcal{O}(1)$ auxiliary space.
*   **Cache Locality**: Explain that pointers in linked lists cause cache misses. In high-performance systems, we prefer flat arrays or memory-arena-allocated nodes to ensure nodes are contiguous in physical RAM.
