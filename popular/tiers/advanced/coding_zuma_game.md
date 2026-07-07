# Zuma Game

- **Category**: Coding
- **Difficulty**: Hard
- **Target Role**: Software Engineer / AI Systems Architect / QA & Test Engineer
- **Source**: LeetCode 488, Glassdoor
- **Flashcards**: [Backtracking deck](../../flash_cards/coding/backtracking.md)

---

## Question Description

You are playing a variation of the game Zuma.

There is a single row of colored balls on a board, where each ball can be colored red `'R'`, yellow `'Y'`, blue `'B'`, green `'G'`, or white `'W'`. You also have several colored balls in your hand.

Your goal is to clear all of the balls from the board. On each turn:
1.  Choose a ball from your hand and insert it into the row (including the left-most and right-most ends).
2.  If the insertion results in a group of **three or more** consecutive balls of the same color, those balls are removed.
3.  If this removal causes other groups of three or more consecutive balls of the same color to form, they are also removed. This process (collapsing) continues until no more groups can be removed.
4.  Repeat the above steps until either the board is cleared or you run out of balls.

Given a string `board` and a string `hand`, return the **minimum number of balls** you have to insert to clear all the balls from the board. If you cannot clear all the balls, return `-1`.

### Examples

*   **Input**: `board = "WRRBBW"`, `hand = "RB"`
    *   **Output**: `-1`
    *   **Explanation**: It is impossible to clear all the balls. The best you can do is:
        *   Insert `'R'` so the board becomes `"WRRRBBW"`. `"WRRRBBW"` -> `"WBBW"`.
        *   Insert `'B'` so the board becomes `"WBBBW"`. `"WBBBW"` -> `"WW"`.
        *   There are still balls remaining on the board, and you are out of balls.
*   **Input**: `board = "WWRRBBWW"`, `hand = "WRBRW"`
    *   **Output**: `2`
    *   **Explanation**: To make the board empty:
        *   Insert `'R'` so the board becomes `"WWRRRBBWW"`. `"WWRRRBBWW"` -> `"WWBBWW"`.
        *   Insert `'B'` so the board becomes `"WWBBBWW"`. `"WWBBBWW"` -> `"WWWW"` -> `""` (empty).
        *   `2` balls from your hand were needed to clear the board.
*   **Input**: `board = "G"`, `hand = "GGGGG"`
    *   **Output**: `2`

### Constraints
*   $1 \le \text{board.length} \le 16$
*   $1 \le \text{hand.length} \le 5$
*   `board` and `hand` consist of the characters `'R'`, `'Y'`, `'B'`, `'G'`, and `'W'`.
*   The initial row of balls on the board will not have any groups of three or more consecutive balls of the same color.

---

## Detailed Solution (C++)

This problem can be modeled as a shortest path search in a state space where each state is a pair of `(board, hand)`. Since we want to find the minimum steps, we can use Backtracking (DFS) with Memoization.

### Core Components
1.  **Collapse Function**: A helper function `collapse()` recursively removes consecutive groups of $3$ or more identical balls from the board.
2.  **Memoization Key**: Since the order of balls in our hand does not affect the decisions, we sort the `hand` string. The state can then be represented as a pair: `std::pair<std::string, std::string>` representing `(board, sorted_hand)`.
3.  **Backtracking Transitions**: At each step:
    *   Collapse the current board.
    *   If the board is empty, return $0$.
    *   If hand is empty (but board is not), return $-1$.
    *   Try inserting every unique ball in our hand at every possible insertion index from $0$ to `board.length()`.
    *   Recurse on the new board and hand, returning the minimum steps.

### Standard C++ Production Code

```cpp
#include <string>
#include <vector>
#include <algorithm>
#include <map>

class Solution {
private:
    // Repeatedly removes any contiguous blocks of 3 or more identical characters
    std::string collapse(const std::string& s) {
        std::string result = s;
        bool changed = true;
        while (changed) {
            changed = false;
            std::string next;
            int i = 0;
            int n = static_cast<int>(result.size());
            while (i < n) {
                int j = i;
                while (j < n && result[j] == result[i]) {
                    j++;
                }
                if (j - i >= 3) {
                    changed = true; // Block of >=3 collapsed
                } else {
                    next.append(result, i, j - i);
                }
                i = j;
            }
            result = next;
        }
        return result;
    }

    int dfs(const std::string& board, const std::string& hand,
            std::map<std::pair<std::string, std::string>, int>& memo) {
        std::string b = collapse(board);
        if (b.empty()) return 0;
        if (hand.empty()) return -1;

        auto key = std::make_pair(b, hand);
        if (memo.count(key)) {
            return memo[key];
        }

        int minBalls = -1;
        int blen = static_cast<int>(b.size());
        int hlen = static_cast<int>(hand.size());

        // Try inserting each ball from hand at every possible index
        for (int i = 0; i <= blen; ++i) {
            for (int hi = 0; hi < hlen; ++hi) {
                // Deduplicate: Skip duplicate balls in the sorted hand
                if (hi > 0 && hand[hi] == hand[hi - 1]) {
                    continue;
                }

                char color = hand[hi];
                std::string newBoard = b.substr(0, i) + color + b.substr(i);
                std::string newHand = hand.substr(0, hi) + hand.substr(hi + 1);

                int result = dfs(newBoard, newHand, memo);
                if (result != -1) {
                    if (minBalls == -1 || result + 1 < minBalls) {
                        minBalls = result + 1;
                    }
                }
            }
        }

        memo[key] = minBalls;
        return minBalls;
    }

public:
    int findMinStep(std::string board, std::string hand) {
        // Sorting the hand ensures unique representation of remaining balls
        std::sort(hand.begin(), hand.end());
        std::map<std::pair<std::string, std::string>, int> memo;
        return dfs(board, hand, memo);
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

```python
from typing import Dict, Tuple

class Solution:
    def findMinStep(self, board: str, hand: str) -> int:
        """
        Finds the minimum number of balls to insert to clear the board.
        
        Time Complexity: O(N * H * H! * (B + H)) in the worst case.
        Space Complexity: O(H! * B) for memoization and call stack.
        """
        def collapse(s: str) -> str:
            changed = True
            while changed:
                changed = False
                i = 0
                while i < len(s):
                    j = i
                    while j < len(s) and s[j] == s[i]:
                        j += 1
                    if j - i >= 3:
                        s = s[:i] + s[j:]
                        changed = True
                    else:
                        i = j
            return s

        memo: Dict[Tuple[str, Tuple[str, ...]], int] = {}

        def dfs(board_str: str, hand_sorted: Tuple[str, ...]) -> int:
            board_str = collapse(board_str)
            if not board_str:
                return 0
            if not hand_sorted:
                return -1

            key = (board_str, hand_sorted)
            if key in memo:
                return memo[key]

            min_balls = -1

            # Iterate over all possible insertion indices
            for i in range(len(board_str) + 1):
                # Try inserting each ball from our hand
                for hi in range(len(hand_sorted)):
                    # Deduplicate: Skip duplicate balls in the sorted hand
                    if hi > 0 and hand_sorted[hi] == hand_sorted[hi - 1]:
                        continue

                    color = hand_sorted[hi]
                    new_board = board_str[:i] + color + board_str[i:]
                    new_hand = hand_sorted[:hi] + hand_sorted[hi + 1:]

                    result = dfs(new_board, new_hand)
                    if result != -1:
                        if min_balls == -1 or result + 1 < min_balls:
                            min_balls = result + 1

            memo[key] = min_balls
            return min_balls

        return dfs(board, tuple(sorted(hand)))
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Hashable Types in Memoization Key
*   In Python, dict keys must be immutable (hashable). Thus, we cannot use a list for `hand` in the memo key. We must convert it to a sorted `tuple` (e.g. `tuple(sorted(hand))`) or string.

### 2. String Concatenation and Performance
*   Python string slicing (`s[:i] + color + s[i:]`) produces a new string. Since Zuma's board is small ($B \le 16$), the overhead is negligible. However, for larger strings, list-based mutation is generally preferred.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}((B+H)! \cdot B)$ | Where $B$ is the initial board length and $H$ is the hand length. In the worst case without memoization, we have $B+1$ insertion positions and $H$ choices. Memoization restricts the state space to at most $\mathcal{O}(2^B \cdot 2^H)$ configurations. |
| **Space Complexity** | $\mathcal{O}(H! \cdot B)$ | The maximum depth of the call stack is $H$. The space is primarily consumed by the memoization table mapping unique board and hand pairs to results. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What are advanced pruning techniques to speed up the execution?
*   **The Answer**:
    1.  **Adjacent Color Rule**: Only insert a ball of color $C$ next to another ball of color $C$ on the board. Inserting a ball next to a different color is only useful in rare cases (like splitting a pair to trigger secondary collapses), but restricting it to adjacent matches prunes $90\%$ of useless moves.
    2.  **Immediate Double Collapse**: If we insert a ball to complete a group of 3, the collapse happens immediately.

### Q2: Why is BFS typically preferred over DFS for Zuma-like puzzles?
*   **The Answer**: Because we are looking for the **shortest path** to the goal state (empty board). BFS searches level by level (steps of balls used). As soon as BFS finds a state with an empty board, it is guaranteed to be the minimum step solution, allowing us to return immediately and prune all remaining deep branches. DFS, on the other hand, must search the entire tree to ensure the path is optimal.

---

## Pro-Tip: How to Impress the Interviewer

*   **Symmetry and Sorting**: Emphasize that sorting the hand simplifies the state key for memoization. Hand configurations `['R', 'B']` and `['B', 'R']` represent the same state, and sorting merges these identical paths, which is a classic dynamic programming optimization.
*   **Identify NP-Hard nature**: Mention that Zuma Game is NP-Hard under general conditions (arbitrary hand size and board length). Acknowledging this helps explain why backtracking with heuristic pruning is the standard and necessary approach rather than a greedy or polynomial-time DP.
