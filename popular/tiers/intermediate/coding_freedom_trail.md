# Freedom Trail

- **Category**: Coding
- **Difficulty**: Hard
- **Target Role**: Software Engineer / AI Systems Architect
- **Source**: LeetCode 514, Glassdoor

---

## Question Description

In the video game Fallout 4, the quest "Road to Freedom" requires players to reach a metal dial called the "Freedom Trail Ring" and use the dial to spell a specific keyword to open the door.

Given a string `ring` that represents the code engraved on the outer ring and another string `key` that represents the keyword that needs to be spelled, return *the minimum number of steps to spell all the characters in the keyword*.

Initially, the first character of the `ring` is aligned at the "12:00" direction. You should spell all the characters in `key` one by one by rotating `ring` clockwise or anticlockwise to make each character of the string `key` aligned at the "12:00" direction and then by pressing the center button.

At the stage of rotating the ring to spell the key character `key[i]`:
*   You can rotate the ring clockwise or anticlockwise by one place, which counts as 1 step. The coordinate of the character on the ring to be spelled is aligned at the "12:00" direction.
*   Spelling a character counts as 1 step. 

### Examples
*   **Input**: `ring = "godding"`, `key = "gd"`
    *   **Output**: `4`
    *   **Explanation**:
        *   For the first key character `'g'`, since it is already at index 0 (the "12:00" direction), we just need 1 step to press the center button.
        *   For the second key character `'d'`, we can rotate the ring anticlockwise by 2 steps to align `'d'` (at index 2 or 3) at "12:00". Let's align the `'d'` at index 2. This takes 2 steps of rotation.
        *   Pressing the center button to spell `'d'` takes 1 step.
        *   Total steps: $1 + 2 + 1 = 4$.
*   **Input**: `ring = "godding"`, `key = "godding"`
    *   **Output**: `13`

**Constraints**:
*   $1 \le \text{ring.length}, \text{key.length} \le 100$
*   `ring` and `key` consist of only lowercase English letters.
*   It is guaranteed that `key` can always be spelled.

---

## Detailed Solution (C++)

This problem can be modeled as finding the shortest path through a multi-stage decision graph, which is best solved using Dynamic Programming.

*   **State**: `dp[pos]` represents the minimum steps needed to spell the remaining suffix of the `key` (from index `ki` to the end) when the dial is currently aligned at index `pos` of the `ring`.
*   **Transition**: To spell the character `key[ki]`, we must rotate the dial from the current position `pos` to some target position `target` where `ring[target] == key[ki]`.
    *   The cost to rotate from `pos` to `target` in a circular ring of length $n$ is:
        $$\text{rotation\_steps} = \min(|pos - target|, n - |pos - target|)$$
    *   The total cost for this step is $\text{rotation\_steps} + 1$ (1 step for spelling/pressing the button).
    *   Therefore, the transition is:
        $$\text{new\_dp}[pos] = \min_{\text{target s.t. } \text{ring}[\text{target}] = \text{key}[ki]} \Big( \text{rotation\_steps} + 1 + \text{dp}[target] \Big)$$

We compute the states bottom-up starting from the last character of the `key` ($ki = \text{key.length} - 1$ down to $0$). Finally, we return `dp[0]` because the ring starts aligned at index $0$.

### Standard C++ Production Code

```cpp
#include <string>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>

class Solution {
public:
    int findRotateSteps(std::string ring, std::string key) {
        int n = static_cast<int>(ring.size());
        int klen = static_cast<int>(key.size());

        // Precompute the positions of each character in the ring to avoid scanning s1 on every transition.
        std::vector<std::vector<int>> positions(26);
        for (int i = 0; i < n; ++i) {
            positions[ring[i] - 'a'].push_back(i);
        }

        // dp[pos] stores the min steps to spell the key suffix from current ring position pos
        std::vector<int> dp(n, 0);

        // Process bottom-up from the last key character to the first key character
        for (int ki = klen - 1; ki >= 0; --ki) {
            std::vector<int> new_dp(n, INT_MAX);
            int ch = key[ki] - 'a';

            // Find best target on the ring for current key[ki] for every starting position pos
            for (int pos = 0; pos < n; ++pos) {
                for (int target : positions[ch]) {
                    int diff = std::abs(pos - target);
                    int steps = std::min(diff, n - diff) + 1; // Rotation steps + 1 step to press button
                    
                    int cost = (ki == klen - 1) ? steps : steps + dp[target];
                    if (cost < new_dp[pos]) {
                        new_dp[pos] = cost;
                    }
                }
            }
            dp = std::move(new_dp);
        }

        return dp[0];
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the space-optimized bottom-up Python implementation using a `defaultdict` for character positions.

```python
from collections import defaultdict
from typing import Dict, List

class Solution:
    def findRotateSteps(self, ring: str, key: str) -> int:
        """
        Spells key using the minimum steps of rotating ring.
        
        Time Complexity: O(K * R^2) where K is key.length, R is ring.length.
        Space Complexity: O(R)
        """
        n = len(ring)
        klen = len(key)
        
        # Precompute positions of each character
        char_positions: Dict[str, List[int]] = defaultdict(list)
        for i, ch in enumerate(ring):
            char_positions[ch].append(i)
            
        dp = [0] * n

        for ki in range(klen - 1, -1, -1):
            new_dp = [float("inf")] * n
            target_indices = char_positions[key[ki]]
            
            for pos in range(n):
                for target in target_indices:
                    diff = abs(pos - target)
                    steps = min(diff, n - diff) + 1
                    
                    cost = steps if ki == klen - 1 else steps + dp[target]
                    if cost < new_dp[pos]:
                        new_dp[pos] = cost
            dp = new_dp
            
        return dp[0]
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Precomputing Character Positions
*   Scanning `ring` inside the DP transitions to find matching characters would degrade performance to $\mathcal{O}(K \cdot R^2 \cdot R) = \mathcal{O}(K \cdot R^3)$.
*   Using a `defaultdict` to map each character to its index list reduces the inner loop complexity significantly, as we only iterate over indexes that actually match `key[ki]`.

### 2. Move Semantics in Python vs C++
*   In Python, assigning `dp = new_dp` is a constant time reference reassignment. 
*   In C++, using `dp = std::move(new_dp)` avoids deep-copying the vector elements, ensuring standard $O(1)$ transfer of resources.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(K \cdot R^2)$ | Where $K$ is the length of `key` and $R$ is the length of `ring`. For each of the $K$ stages, we perform $R \times R$ work in the worst case (if all characters in `ring` are the same). |
| **Space Complexity** | $\mathcal{O}(R)$ | We only store two arrays (`dp` and `new_dp`) of size $R$, plus the character position lists of combined size $R$. |

---

## Common Follow-Up Questions & How to Answer

### Q1: Can we use Dijkstra's Algorithm instead of DP?
*   **Answer**: Yes. We can view this as finding the shortest path in a layered graph where layer $i$ contains nodes corresponding to the matching positions of `key[i]` in the ring. The number of states is $K \cdot R$. Dijkstra's algorithm would find the shortest path in $\mathcal{O}(E \log V)$ which is $\mathcal{O}(K \cdot R^2 \log(K \cdot R))$. For the constraints $K, R \le 100$, DP runs faster and uses less memory because it does not have priority queue overhead.

### Q2: What if we can also rotate the ring clockwise or anticlockwise multiple steps per operation?
*   **Answer**: The question already supports rotating multiple steps. If it meant rotating by any distance $d$ in 1 operation (e.g. random access dial), then `min(diff, n - diff)` would simply be constant cost 1.

---

## Pro-Tip: How to Impress the Interviewer

*   **Highlight Cache Friendliness**: Discuss that since the `dp` vector size is at most 100, the data fits entirely in L1 cache. The memory layout is contiguous, minimizing cache misses.
*   **State Pruning**: Explain that instead of calculating `new_dp[pos]` for all $pos$ from $0$ to $n-1$, we can restrict `pos` to only the indices of the ring containing `key[ki-1]` (for $ki > 0$) or index $0$ (for $ki = 0$). This reduces the constant factor dramatically in cases where the character frequencies are small.
