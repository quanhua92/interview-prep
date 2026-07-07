# Assign Cookies

- **Category**: Coding
- **Difficulty**: Easy
- **Target Role**: Software Engineer / QA & Test Engineer
- **Source**: LeetCode 455, Glassdoor

---

## Question Description

Assume you are an awesome parent and want to give your children some cookies. But, you should give each child at most one cookie.

Each child $i$ has a greed factor `g[i]`, which is the minimum size of a cookie that the child will be content with; and each cookie $j$ has a size `s[j]`. If `s[j] >= g[i]`, we can assign the cookie $j$ to the child $i$, and the child $i$ will be content. Your goal is to maximize the number of your content children and output the maximum number.

### Examples
*   **Input**: `g = [1,2,3]`, `s = [1,1]`
    *   **Output**: `1`
    *   **Explanation**: You have 3 children and 2 cookies. The greed factors of the 3 children are 1, 2, 3. Even though you have 2 cookies, since their size is both 1, you can only make the child whose greed factor is 1 content.
*   **Input**: `g = [1,2]`, `s = [1,2,3]`
    *   **Output**: `2`
    *   **Explanation**: You have 2 children and 3 cookies. The greed factors of the 2 children are 1, 2. You have 3 cookies and their sizes are big enough to gratify all children. Return 2.

---

## Detailed Solution (C++)

To satisfy the maximum number of children, we should adopt a **Greedy Strategy**:
1. **Sort** both arrays: `g` (greed factors of children) and `s` (cookie sizes) in ascending order.
2. Use **Two Pointers** (`child` and `cookie`) initialized to `0`.
3. Try to satisfy the child with the smallest greed factor with the smallest possible cookie size.
   * If the current cookie size is sufficient (`s[cookie] >= g[child]`), the child is satisfied, and we move to the next child (`child++`).
   * Regardless of whether the child is satisfied or not, we must move to the next cookie (`cookie++`) because this cookie is either used or too small to satisfy the current child (and thus too small for any subsequent child with a larger greed factor).
4. When we run out of either children or cookies, `child` represents the number of content children.

### Standard C++ Production Code

```cpp
#include <vector>
#include <algorithm>

class Solution {
public:
    int findContentChildren(std::vector<int>& g, std::vector<int>& s) {
        // Sort greed factors and cookie sizes in-place
        std::sort(g.begin(), g.end());
        std::sort(s.begin(), s.end());

        int child = 0;
        int cookie = 0;
        const int num_children = static_cast<int>(g.size());
        const int num_cookies = static_cast<int>(s.size());

        // Greedily match cookies to children
        while (child < num_children && cookie < num_cookies) {
            if (s[cookie] >= g[child]) {
                child++; // Child is content, move to the next child
            }
            cookie++; // Move to the next cookie in all cases
        }

        return child;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the type-hinted, optimized Python implementation using a simplified `for` loop over cookies.

```python
from typing import List

class Solution:
    def findContentChildren(self, g: List[int], s: List[int]) -> int:
        """
        Maximizes the number of content children given greed factors and cookie sizes.
        
        Time Complexity: O(N log N + M log M)
        Space Complexity: O(1) auxiliary (in-place sort)
        """
        # Sort in-place to minimize space allocations
        g.sort()
        s.sort()

        child = 0
        n_children = len(g)

        # Iterating through cookies directly avoids index checks inside the loop,
        # which is faster and more Pythonic.
        for cookie_size in s:
            if child < n_children and cookie_size >= g[child]:
                child += 1
            if child == n_children:
                break  # Early exit if all children are already satisfied

        return child
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Loop Condition Optimization
*   In Python, a standard `while child < len(g) and cookie < len(s):` loop involves multiple dictionary lookups and bounds checks at each step in the bytecode.
*   By rewriting the loop to iterate directly over the elements of `s` (using `for cookie_size in s:`), we delegate index tracking to Python's internal C-iterator, speeding up execution.

### 2. In-Place Sorting vs. Creating Copies
*   Using `g.sort()` and `s.sort()` modifies the input lists in-place, which is highly memory-efficient.
*   Using `sorted(g)` and `sorted(s)` would allocate new list copies, causing $\mathcal{O}(N + M)$ space complexity. Always ask the interviewer if mutating the input parameters is acceptable.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n \log n + m \log m)$ | Where $n$ is the number of children and $m$ is the number of cookies. Sorting dominates the execution time. |
| **Space Complexity** | $\mathcal{O}(\log n + \log m)$ or $\mathcal{O}(n + m)$ | Sorting stack space in C++ is $\mathcal{O}(\log n + \log m)$, while Python's Timsort uses $\mathcal{O}(n + m)$ auxiliary space. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if children can be given more than one cookie (e.g., up to two cookies) to satisfy their greed factor?
*   **Answer**: If a child can receive up to two cookies, we can no longer use the simple two-pointer greedy match. This is because a child's greed could be satisfied by a single large cookie or the sum of two smaller cookies. 
    *   To solve this greedily, we still sort children by greed factor. 
    *   We try to satisfy the child with the smallest greed factor first. We first check if the smallest single cookie can satisfy them. If not, we check if the sum of the two smallest cookies can satisfy them. If so, we assign them; otherwise, the child cannot be satisfied.

### Q2: What if we can divide cookies? (e.g., a cookie of size 10 can be split into sizes 4 and 6)
*   **Answer**: If cookies can be split arbitrarily, the individual cookie boundaries no longer matter. Only the total sum of cookie sizes matters. To maximize the number of content children, we should satisfy the children with the lowest greed factors first. 
    1. Sort the children's greed factors `g`.
    2. Sum the cookie sizes to get `total_cookie_weight`.
    3. Iterate through `g` and subtract `g[child]` from `total_cookie_weight`.
    4. Stop when `total_cookie_weight` becomes negative. The index will represent the maximum satisfied children.

---

## Pro-Tip: How to Impress the Interviewer

*   **Mention Early Exit Optimization**: In the Python solution, adding `if child == n_children: break` allows the program to terminate immediately if we satisfy all children before we run out of cookies. In real-world scenarios with a large number of cookies, this saves significant processing time.
*   **Discuss Constness and Pass-by-Reference in C++**: Show interviewers that you care about performance by passing vectors by reference. If the caller allows input mutation, sort them in-place. If not, explicitly mention that you must copy the vectors first, which shifts auxiliary space complexity to $\mathcal{O}(N + M)$.
