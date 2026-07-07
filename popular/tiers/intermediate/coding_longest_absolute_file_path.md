# Longest Absolute File Path

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer
- **Source**: LeetCode 388, Glassdoor

---

## Question Description

Suppose we have a file system that stores both files and directories. A system can be represented textually where directories and files are separated by newline characters `\n`, and their depth in the file system is indicated by tab characters `\t`.

Given a string `input` representing the file system, return the length of the **longest absolute path** to a **file** in the file system. If there is no file in the system, return `0`.

Note that a file name must contain at least one `.` character separating its name and extension (e.g., `file.ext` is a file, but `subdir` is a directory).

### Examples
*   **Input**: `input = "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext"`
    *   **Output**: `20`
    *   **Explanation**: We have only one file, and its absolute path is `"dir/subdir2/file.ext"`, which has a length of $20$ (three parts of length 3, 7, 8, plus two `/` separators).
*   **Input**: `input = "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext"`
    *   **Output**: `32`
    *   **Explanation**: We have two files:
        *   `"dir/subdir1/file1.ext"` (length 21)
        *   `"dir/subdir2/subsubdir2/file2.ext"` (length 32)
        We return 32, the longest path.
*   **Input**: `input = "a"`
    *   **Output**: `0`
    *   **Explanation**: The input only contains a single directory `"a"`. Since there are no files, we return 0.

---

## Detailed Solution (C++)

The filesystem layout is structured like a tree. A DFS-like traversal can be done by parsing the string sequentially. We can maintain a stack `stk` where `stk[depth]` holds the absolute path length of the directory at depth `depth`.
To maximize performance and avoid unnecessary heap allocations, we parse the input string in-place in a single pass without using string splittings or regexes.

### Standard C++ Production Code

```cpp
#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    int lengthLongestPath(const std::string& input) noexcept {
        // stk[depth] stores the path length of the directory chain up to that depth.
        // Index 0 acts as a base length of 0.
        std::vector<int> stk = {0}; 
        int max_len = 0;
        int i = 0;
        const int len = static_cast<int>(input.size());

        while (i < len) {
            // 1. Calculate depth by counting consecutive tabs
            int depth = 0;
            while (i < len && input[i] == '\t') {
                depth++;
                i++;
            }

            // 2. Parse name of directory/file and check if it is a file
            int name_start = i;
            bool is_file = false;
            while (i < len && input[i] != '\n') {
                if (input[i] == '.') {
                    is_file = true;
                }
                i++;
            }
            int name_len = i - name_start;

            // Skip the newline character for the next iteration
            if (i < len && input[i] == '\n') {
                i++;
            }

            // 3. Maintain stack to match current depth.
            // stk.size() must be kept at depth + 1.
            while (static_cast<int>(stk.size()) > depth + 1) {
                stk.pop_back();
            }

            // 4. Update max length or push current path length to stack
            if (is_file) {
                max_len = std::max(max_len, stk.back() + name_len);
            } else {
                // If it is a directory, append length + 1 (for the '/' separator)
                stk.push_back(stk.back() + name_len + 1);
            }
        }

        return max_len;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the Python implementation. Python's built-in string methods like `.split('\n')` and `.lstrip('\t')` allow for highly expressive and concise code while remaining linear in time.

```python
class Solution:
    def lengthLongestPath(self, input: str) -> int:
        """
        Computes the length of the longest absolute path to a file.
        
        Time Complexity: O(N) where N is the length of the input string.
        Space Complexity: O(D) where D is the maximum depth of the directory structure.
        """
        # stack[depth] stores the accumulated path length up to that depth
        stack = [0]
        max_len = 0
        
        for part in input.split("\n"):
            # The count of '\t' indicates the depth of the current item (0-indexed)
            depth = part.count("\t")
            name = part.lstrip("\t")
            
            # Pop elements from stack until the stack matches the parent depth
            while len(stack) > depth + 1:
                stack.pop()
                
            # If the item contains a '.', it is a file
            if "." in name:
                max_len = max(max_len, stack[-1] + len(name))
            else:
                # If it is a directory, store path length + 1 for the '/' separator
                stack.append(stack[-1] + len(name) + 1)
                
        return max_len
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. `split('\n')` Memory Overhead
*   Calling `input.split('\n')` in Python creates a list of sub-strings. For large strings ($N \le 10^4$), this creates a list of strings on the heap.
*   While acceptable within typical LeetCode limits, it can cause memory spikes under extreme datasets.
*   **Low-memory Alternative**: Use a custom generator or find index loops (`input.find('\n')`) to yield parts of the string without full materialization of the list.

### 2. Tab Counting & Left Stripping
*   `part.count('\t')` scans the entire line. However, tabs can only appear at the very start of a line in a valid serialization.
*   It is more robust to only strip tabs from the left (`part.lstrip('\t')`) and calculate depth as `len(part) - len(name)`.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | We scan the string of length $n$ exactly once. Each character is checked for delimiters (`\t`, `\n`, `.`) a constant number of times. |
| **Space Complexity** | $\mathcal{O}(d)$ | The maximum depth of the directory tree. In the worst case (deeply nested directory hierarchy), $d \le n$. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if multiple tabs or backslashes represent tabs?
*   **Answer**: In some systems, tabs are represented as spaces (e.g. four spaces `    ` or two spaces `  `). We can adjust the depth detection by counting prefix spaces instead of `\t` and dividing by the tab-to-space factor.

### Q2: How can we return the actual path string instead of just its length?
*   **Answer**: Instead of storing lengths in our stack, we can store the actual directory/file name strings.
*   **Python Modification**:
    ```python
    stack = []
    # when processing a file:
    full_path = "/".join(stack) + "/" + name
    ```

---

## Pro-Tip: How to Impress the Interviewer

*   **Avoid Garbage Collection Stalls**: Mention that the C++ solution uses in-place parsing without allocating sub-strings on the heap. Standard libraries like `std::string::substr` or splitting methods copy parts of the string into new memory regions. An in-place pointer scan is optimal for high-throughput, low-latency microservices.
*   **Discuss Cache Locality of Vector**: Highlight why `std::vector` is ideal for a stack compared to `std::stack` (which wraps `std::deque` by default). `std::deque` allocates elements in chunks (typically 512 bytes), whereas `std::vector` is completely contiguous in memory, maximizing cache line utilization.
