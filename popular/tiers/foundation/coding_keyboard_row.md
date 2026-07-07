# Keyboard Row

- **Category**: Coding
- **Difficulty**: Easy
- **Target Role**: Software Engineer / Low-Level Developer
- **Source**: LeetCode 500, Glassdoor
- **Flashcards**: [Hashmap deck](../../flash_cards/coding/hashmap.md)

---

## Question Description

Given an array of strings `words`, return the words that can be typed using letters of the alphabet on only **one row** of the American keyboard (QWERTY layout).

Note that the strings are case-insensitive, so both lowercase and uppercase versions of the same letter are treated as if they are in the same row.

The rows on the QWERTY keyboard are defined as:
*   **Row 1**: `"qwertyuiop"`
*   **Row 2**: `"asdfghjkl"`
*   **Row 3**: `"zxcvbnm"`

### Examples

*   **Input**: `words = ["Hello","Alaska","Dad","Peace"]`
    *   **Output**: `["Alaska","Dad"]`
    *   **Explanation**: 
        *   `"Alaska"` can be typed using only characters in Row 2.
        *   `"Dad"` can be typed using only characters in Row 2.
        *   `"Hello"` contains `'H'`, `'e'`, `'l'`, `'o'`, which span multiple rows.

*   **Input**: `words = ["omk"]`
    *   **Output**: `[]`

*   **Input**: `words = ["adsdf","sfd"]`
    *   **Output**: `["adsdf","sfd"]`

### Constraints
*   $1 \le \text{words.length} \le 20$
*   $1 \le \text{words}[i].length \le 100$
*   `words[i]` consists of English letters (both lowercase and uppercase).

---

## Detailed Solution (C++)

To solve this problem efficiently:
1.  Define a static lookup table mapping each of the 26 lowercase English letters directly to its row index ($0$, $1$, or $2$).
2.  For each word, determine the target row based on its first character.
3.  Check all subsequent characters in the word. If any character maps to a different row, discard the word immediately (**early exit**).
4.  If all characters match the target row, add the word to the result vector.

### Standard C++ Production Code

```cpp
#include <vector>
#include <string>
#include <cctype>

class Solution {
public:
    std::vector<std::string> findWords(const std::vector<std::string>& words) {
        // Map from lowercase letter ('a' - 'z') to its row number (0, 1, or 2)
        // Row 0: q,w,e,r,t,y,u,i,o,p
        // Row 1: a,s,d,f,g,h,j,k,l
        // Row 2: z,x,c,v,b,n,m
        static const int char_to_row[26] = {
            1, 2, 2, 1, 0, 1, 1, 1, 0, 1, 1, 1, 2, 2, 0, 0, 0, 0, 1, 0, 0, 2, 0, 2, 0, 2
        };
        
        std::vector<std::string> result;
        
        for (const std::string& word : words) {
            if (word.empty()) continue;
            
            // Get the row of the first character (using static_cast to prevent UB in std::tolower)
            int first_char = std::tolower(static_cast<unsigned char>(word[0])) - 'a';
            int target_row = char_to_row[first_char];
            bool same_row = true;
            
            for (size_t i = 1; i < word.length(); ++i) {
                int curr_char = std::tolower(static_cast<unsigned char>(word[i])) - 'a';
                if (char_to_row[curr_char] != target_row) {
                    same_row = false;
                    break; // Early exit
                }
            }
            
            if (same_row) {
                result.push_back(word);
            }
        }
        
        return result;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

```python
from typing import List

class Solution:
    def findWords(self, words: List[str]) -> List[str]:
        """
        Filters words that can be typed using letters of only one QWERTY row.
        
        Time Complexity: O(L) where L is the total number of characters across all words.
        Space Complexity: O(1) auxiliary space.
        """
        rows = [
            set("qwertyuiop"),
            set("asdfghjkl"),
            set("zxcvbnm")
        ]
        
        result = []
        for word in words:
            # Convert word characters to a lowercase set
            word_set = set(word.lower())
            
            # Check if word_set is a subset of any row
            if any(word_set.issubset(row) for row in rows):
                result.append(word)
                
        return result
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Set Operations and `issubset` Efficiency
*   Python's `issubset` (or the `<=` operator) is written in C and is highly optimized.
*   However, constructing a new set for every word (via `set(word.lower())`) allocates memory on the heap and creates garbage collector overhead. For performance-critical code, using a static mapping dictionary or list lookup is faster.

### 2. Case Folding
*   We use `.lower()` to normalize the word. In internationalized environments, `.casefold()` is generally preferred over `.lower()` for case-insensitive comparisons, though for standard ASCII English keys, `.lower()` is perfectly sufficient.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(L)$ | We process each character of each word at most once, where $L$ is the sum of lengths of all words. |
| **Space Complexity** | $\mathcal{O}(1)$ | The alphabet mappings or row sets are constant size (26 characters). |

---

## Common Follow-Up Questions & How to Answer

### Q1: How would you modify the solution to support a custom or international layout (like Dvorak or Colemak)?
*   **Answer**: The structure of the code remains identical. The only change needed is updating the mapping table (`char_to_row` in C++ or the `rows` sets in Python) to reflect the key positions on the target keyboard.

### Q2: If the input consists of millions of extremely long words, how would you optimize the performance?
*   **Answer**:
    1.  **Early Exit**: Terminate the check on a word immediately on the first character mismatch (already implemented in the C++ version).
    2.  **Concurrency**: Since each word's check is independent, we can divide the word list among multiple threads using OpenMP in C++ or standard thread pools.

---

## Pro-Tip: How to Impress the Interviewer

*   **Avoid Heap Allocations**: Highlight that by using a static lookup table (`static const int char_to_row[26]`) instead of dynamically creating sets or maps at runtime, the C++ solution operates with **zero heap allocations** for validation. This is a critical design pattern in low-latency systems.
*   **Prevent Undefined Behavior in `tolower`**: In C++, passing a `char` directly to `std::tolower` can trigger undefined behavior if the value is negative (due to signed char expansion to EOF). Point out that casting the character to `unsigned char` first (`static_cast<unsigned char>(c)`) is the correct, standard-compliant way to prevent this crash.
