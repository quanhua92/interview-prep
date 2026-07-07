# Most Frequent Subtree Sum

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / AI Systems Architect
- **Source**: LeetCode 508, Glassdoor
- **Flashcards**: [DFS deck](../../flash_cards/coding/dfs.md)

---

## Question Description

Given the root of a binary tree, return the **most frequent subtree sum**. If there is a tie, return all the values with the highest frequency in any order.

The **subtree sum** of a node is defined as the sum of all the node values formed by the subtree rooted at that node (including the node itself).

### Examples
*   **Input**: `root = [5,2,-3]`
    *   **Output**: `[2,-3,4]`
    *   **Explanation**: 
        *   Subtree sum of node `2` is `2`.
        *   Subtree sum of node `-3` is `-3`.
        *   Subtree sum of root node `5` is `5 + 2 + (-3) = 4`.
        All three sums occur exactly once, so we return all of them.
*   **Input**: `root = [5,2,-5]`
    *   **Output**: `[2]`
    *   **Explanation**: 
        *   Subtree sum of node `2` is `2`.
        *   Subtree sum of node `-5` is `-5`.
        *   Subtree sum of root node `5` is `5 + 2 + (-5) = 2`.
        The sum `2` occurs twice, while `-5` occurs once. Thus, the most frequent subtree sum is `2`.

---

## Detailed Solution (C++)

We can compute the subtree sums in a **bottom-up (post-order)** manner using Depth-First Search (DFS).
1. For each node, we recursively compute the sum of its left and right subtrees.
2. The subtree sum for the current node is `node->val + left_sum + right_sum`.
3. We record this sum in a hash map `std::unordered_map<int, int>` to track frequencies.
4. To optimize performance, we update the `max_freq` in a single pass while traversing the tree, avoiding a second iteration over the tree nodes.

### Standard C++ Production Code

```cpp
#include <vector>
#include <unordered_map>
#include <algorithm>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
private:
    int getSubtreeSum(TreeNode* node, std::unordered_map<int, int>& freq, int& max_freq) noexcept {
        if (!node) {
            return 0;
        }

        // Post-order traversal (bottom-up sum calculation)
        int left_sum = getSubtreeSum(node->left, freq, max_freq);
        int right_sum = getSubtreeSum(node->right, freq, max_freq);
        
        // Prevent overflow by performing standard arithmetic 
        // (assuming inputs are bounded as per constraints)
        int total_sum = node->val + left_sum + right_sum;

        freq[total_sum]++;
        max_freq = std::max(max_freq, freq[total_sum]);

        return total_sum;
    }

public:
    std::vector<int> findFrequentTreeSum(TreeNode* root) noexcept {
        std::unordered_map<int, int> freq;
        int max_freq = 0;
        
        getSubtreeSum(root, freq, max_freq);

        std::vector<int> result;
        for (const auto& [sum, count] : freq) {
            if (count == max_freq) {
                result.push_back(sum);
            }
        }
        return result;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the Python implementation using a recursive nested function and `defaultdict`.

```python
from typing import List, Optional
from collections import defaultdict

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:
    def findFrequentTreeSum(self, root: Optional[TreeNode]) -> List[int]:
        """
        Finds the most frequent subtree sums in a binary tree.
        
        Time Complexity: O(N)
        Space Complexity: O(N) for recursion stack and map storage.
        """
        if not root:
            return []

        freq = defaultdict(int)
        max_freq = 0

        def get_subtree_sum(node: Optional[TreeNode]) -> int:
            nonlocal max_freq
            if not node:
                return 0

            # Post-order DFS
            left_sum = get_subtree_sum(node.left)
            right_sum = get_subtree_sum(node.right)
            total_sum = node.val + left_sum + right_sum

            # Update frequencies
            freq[total_sum] += 1
            max_freq = max(max_freq, freq[total_sum])

            return total_sum

        get_subtree_sum(root)
        
        # Gather all sums matching the maximum frequency
        return [s for s, count in freq.items() if count == max_freq]
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. `nonlocal` Keyword Usage
*   In Python, variables defined in outer functions cannot be reassigned in inner helper functions unless declared `nonlocal`.
*   Without `nonlocal max_freq`, Python will raise an `UnboundLocalError` when attempting to write `max_freq = max(...)`.
*   **Alternative**: Store state in a mutable type like a list/dictionary (e.g. `max_freq = [0]`) or an instance variable (`self.max_freq`).

### 2. Hash Map Keys in Python
*   Python's dictionaries are implemented as dynamically resized hash tables. Storing integers as keys is highly optimized, but inserting $\mathcal{O}(n)$ keys into a `defaultdict` can trigger dynamic resizing and rehashing. This results in slight amortized overhead but remains $\mathcal{O}(1)$ average per operation.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | We visit every node in the binary tree exactly once. Map lookups and updates are $\mathcal{O}(1)$ on average. |
| **Space Complexity** | $\mathcal{O}(n)$ | In the worst case (skewed tree), the recursion stack is $\mathcal{O}(n)$. The hash map also stores up to $n$ unique sum values. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if node values can be extremely large, leading to integer overflow?
*   **Answer**: In C++, we should use 64-bit integers (`int64_t` or `long long`) for computing the subtree sums and as keys for the hash map to prevent overflow. Python handles arbitrary-precision integers automatically, so no code adjustments are needed.

### Q2: How can we implement this iteratively to avoid stack overflow?
*   **Answer**: We can perform an iterative post-order traversal using a stack. 
    1. Keep a map of node to its computed subtree sum.
    2. Visit nodes in post-order (e.g., using two stacks, or tracking the last visited node).
    3. Pop a node when both its children's sums are computed, aggregate the sum, store it in the map, and update frequencies.

---

## Pro-Tip: How to Impress the Interviewer

*   **Avoid Two-Pass Frequency Scanning**: Many candidates traverse the tree to build the frequencies, then loop through the map to find the maximum frequency, and finally loop again to gather results. Doing this in **one pass** (updating `max_freq` dynamically during DFS) shows a keen eye for loop-level optimization and minimizes constant-factor overhead.
*   **Mention Cache Friendliness of `std::unordered_map`**: Note that although `std::unordered_map` is $\mathcal{O}(1)$ average time, it uses bucket chains which can result in cache misses because node elements are scattered in heap memory. Discussing the cache performance of node structures versus contiguous arrays highlights hardware-aware engineering.
