# Linked List Random Node

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer
- **Source**: LeetCode 382, Glassdoor

---

## Question Description

Given a singly linked list, return a random node's value from the linked list. Each node must have the **same probability** of being chosen.

Implement the `Solution` class:

*   `Solution(ListNode head)` Initializes the object with the head of the singly-linked list.
*   `int getRandom()` Chooses a node randomly from the list and returns its value. All the nodes of the list should be equally likely to be chosen.

### Follow up:
*   What if the linked list is extremely large and its length is unknown to you?
*   Could you solve this efficiently without using extra space?

### Examples
*   **Input**:
    ```
    ["Solution", "getRandom", "getRandom", "getRandom", "getRandom", "getRandom"]
    [[[1, 2, 3]], [], [], [], [], []]
    ```
*   **Output**:
    ```
    [null, 1, 3, 2, 2, 3]
    ```
*   **Explanation**:
    ```cpp
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    Solution solution(head);
    
    // getRandom() should return either 1, 2, or 3 randomly. 
    // Each element should have equal probability of returning.
    solution.getRandom(); // returns 1
    solution.getRandom(); // returns 3
    solution.getRandom(); // returns 2
    ```

---

## Detailed Solution (C++)

When the list size is unknown or extremely large (streaming data), storing all values in memory is not feasible. We use **Reservoir Sampling**:
1.  Initialize `res = head->val`.
2.  Traverse the list starting from the second node (`head->next`). Let the current index be $i$ (2-indexed).
3.  For each node, generate a random number between $1$ and $i$.
4.  If the random number is $1$, we replace the reservoir value `res` with the current node's value.
5.  Move to the next node and repeat.

### Standard C++ Production Code

```cpp
#include <random>

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
private:
    ListNode* head;
    mutable std::mt19937 rng;

public:
    Solution(ListNode* h) : head(h), rng(std::random_device{}()) {}

    int getRandom() const {
        int res = head->val;
        ListNode* cur = head->next;
        int i = 2;
        
        while (cur) {
            // Pick a random number in [1, i]
            std::uniform_int_distribution<int> dist(1, i);
            if (dist(rng) == 1) {
                res = cur->val;
            }
            cur = cur->next;
            i++;
        }
        
        return res;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

```python
import random
from typing import Optional

# Definition for singly-linked list.
class ListNode:
    def __init__(self, val: int = 0, next: Optional['ListNode'] = None):
        self.val = val
        self.next = next

class Solution:
    def __init__(self, head: Optional[ListNode]):
        """
        Initializes the object with the head of the singly-linked list.
        """
        self.head = head

    def getRandom(self) -> int:
        """
        Chooses a node randomly from the list and returns its value.
        Uses Reservoir Sampling to handle unknown length in O(1) auxiliary space.
        """
        if not self.head:
            raise ValueError("The list is empty.")
            
        res = self.head.val
        cur = self.head.next
        i = 2
        
        while cur:
            # Generate a random integer in the range [1, i] (inclusive)
            if random.randint(1, i) == 1:
                res = cur.val
            cur = cur.next
            i += 1
            
        return res
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Inclusive Range in `random.randint`
*   In Python, `random.randint(a, b)` generates an integer inclusive of both bounds $[a, b]$. 
*   This is different from standard range-based functions like `range()` or `random.randrange(a, b)` which exclude the upper bound. Using `random.randint(1, i)` correctly gives a $1/i$ chance of selecting $1$.

### 2. Stream Data vs Precomputation Trade-off
*   If `getRandom()` is called many times, traversing the linked list of length $N$ on each call takes $\mathcal{O}(N)$ time.
*   In standard Python environments where memory is not extremely tight, pre-loading all list values into a Python `list` during initialization allows $\mathcal{O}(1)$ random lookup via `random.choice(self.vals)`, but requires $\mathcal{O}(N)$ memory.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(N)$ | We traverse the entire linked list of length $N$ to sample the stream. |
| **Space Complexity** | $\mathcal{O}(1)$ | We only maintain a few pointer variables and a counter, regardless of the list size. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if we need to select $k$ random nodes instead of 1? (Algorithm R)
*   **Answer**: To sample $k$ items, we maintain a reservoir array of size $k$ containing the first $k$ nodes. 
    *   For the $i$-th node (where $i > k$), we generate a random index $j$ in $[0, i-1]$.
    *   If $j < k$, we replace `reservoir[j]` with the $i$-th node.
    *   This ensures all nodes have a uniform $k/N$ chance of being selected.

### Q2: What is the math proof of Reservoir Sampling?
*   **Answer**: By induction, the probability of selecting the $i$-th item at step $i$ is $1/i$.
    *   For the last item $N$, its final probability of survival is $1/N$.
    *   For any previous item $k$, the probability of survival is the probability it was chosen at step $k$, multiplied by the probability it was not replaced at any subsequent step:
        $$\mathbb{P}(\text{survives}) = \frac{1}{k} \times \left(1 - \frac{1}{k+1}\right) \times \left(1 - \frac{1}{k+2}\right) \times \dots \times \left(1 - \frac{1}{N}\right)$$
        $$\mathbb{P}(\text{survives}) = \frac{1}{k} \times \frac{k}{k+1} \times \frac{k+1}{k+2} \times \dots \times \frac{N-1}{N} = \frac{1}{N}$$

---

## Pro-Tip: How to Impress the Interviewer

*   **Mention Modulo Bias**: Point out that doing `rand() % i` in C/C++ introduces **modulo bias** if the range of the random engine is not a multiple of $i$. Explain that modern standard libraries provide `std::uniform_int_distribution` to avoid this and ensure a mathematically uniform distribution.
*   **Explain Hardware Cache Inefficiency**: Explain that traversing a linked list for random selection is highly cache-inefficient because nodes are scattered in heap memory, causing frequent CPU cache line misses. In a production system, converting the linked list to a contiguous array (`std::vector`) is significantly faster unless memory constraints prevent it.
