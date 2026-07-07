# First Bad Version

- **Category**: Coding
- **Difficulty**: Easy
- **Target Role**: Software Engineer / QA & Test Engineer
- **Source**: LeetCode 278, Glassdoor

---

## Question Description

You are a product manager and currently leading a team to develop a new product. Unfortunately, the latest version of your product fails the quality check. Since each version is developed based on the previous version, all the versions after a bad version are also bad.

Suppose you have $n$ versions `[1, 2, ..., n]` and you want to find out the first bad one, which causes all the following ones to be bad.

You are given an API `bool isBadVersion(version)` which returns whether `version` is bad. Implement a function to find the first bad version. You should minimize the number of calls to the API.

### Examples

*   **Input**: `n = 5`, `bad = 4`
    *   **Output**: `4`
    *   **Explanation**:
        *   `isBadVersion(3)` returns `false`
        *   `isBadVersion(5)` returns `true`
        *   `isBadVersion(4)` returns `true`
        *   Then `4` is the first bad version.
*   **Input**: `n = 1`, `bad = 1`
    *   **Output**: `1`

### Constraints
* $1 \le \text{bad} \le n \le 2^{31} - 1$

---

## Detailed Solution (C++)

The problem requires finding the smallest version $v \in [1, n]$ such that `isBadVersion(v)` is `true`. Since the versions are monotonically partitioned into a sequence of `false` values followed by `true` values (e.g., `[F, F, F, T, T]`), we can apply **Binary Search** to find the boundary in $\mathcal{O}(\log n)$ steps.

We check the version at `mid`. If `isBadVersion(mid)` is `true`, then the first bad version is either `mid` or lies to the left of `mid` (`right = mid`). If it is `false`, then the first bad version must be strictly to the right of `mid` (`left = mid + 1`).

### Standard C++ Production Code

```cpp
// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        int left = 1;
        int right = n;

        while (left < right) {
            // Prevent integer overflow: left + right could exceed 2^31 - 1
            int mid = left + (right - left) / 2;

            if (isBadVersion(mid)) {
                right = mid;       // The first bad version is mid or to the left
            } else {
                left = mid + 1;    // The first bad version is strictly to the right
            }
        }

        // When left == right, we have found the first bad version
        return left;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the iterative, type-hinted Python implementation.

```python
# The isBadVersion API is already defined for you.
# def isBadVersion(version: int) -> bool:

class Solution:
    def firstBadVersion(self, n: int) -> int:
        """
        Finds the first bad version using binary search.
        
        Time Complexity: O(log N)
        Space Complexity: O(1)
        """
        left, right = 1, n

        while left < right:
            mid = left + (right - left) // 2

            if isBadVersion(mid):
                right = mid       # Mid is bad, search left half including mid
            else:
                left = mid + 1    # Mid is good, search right half excluding mid

        return left
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Integer Arithmetic Safety
* In C++ or Java, `(left + right) / 2` is a famous source of overflow bugs when $n \approx 2^{31} - 1$, since the sum can exceed the maximum value of a signed 32-bit integer.
* Python automatically promotes integers to arbitrary precision, meaning `(left + right) // 2` will never overflow the underlying memory. However, using `left + (right - left) // 2` is still considered best practice in interviews to demonstrate awareness of fixed-width architecture limitations.

### 2. Mocking the API for Local Testing
* For offline development or automated testing, we can define a class wrapper or closure that mocks the API:
  ```python
  def make_bad_version_check(bad: int):
      return lambda v: v >= bad
  ```

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(\log n)$ | The version range is halved at each iteration, resulting in at most $\approx 31$ calls to `isBadVersion`. |
| **Space Complexity** | $\mathcal{O}(1)$ | The search uses constant memory space for pointers. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if the API calls are extremely expensive (e.g., hitting a remote database or network call)?
* **Answer**: If calling `isBadVersion` is costly, we must minimize calls. 
  1. We can cache the results of past queries in a hash map to avoid querying the same version twice.
  2. If versions are requested in batches, we can load-balance version verification.

### Q2: What if we don't know the upper bound $n$? (Infinite version stream)
* **Answer**: If $n$ is unknown or infinite, we cannot initialize `right = n`. We can use **Exponential Search**:
  1. Start with `right = 1`.
  2. Double `right` (`right *= 2`) repeatedly as long as `isBadVersion(right)` is `false`.
  3. Once we find a `right` where the version is bad, the first bad version must be in the range `[right // 2, right]`. We then perform standard binary search on this interval.
  4. This takes $\mathcal{O}(\log k)$ time, where $k$ is the index of the first bad version.

---

## Pro-Tip: How to Impress the Interviewer

* **Proactive Overflow Discussion**: Before writing the code, mention the `left + (right - left) / 2` overflow issue. Interviewers love candidates who preemptively write bug-free code for corner cases.
* **Explain Interactive Systems Design**: Discuss how to handle flaky network connections in an interactive environment. For instance, if `isBadVersion(mid)` could fail/time out, how do we introduce retries or exponential backoff in our binary search loop?
