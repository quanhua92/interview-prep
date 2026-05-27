/*
 * P514: Freedom Trail [PREMIUM] (Hard)
 * https://leetcode.com/problems/freedom-trail/
 * Topics: String, Dynamic Programming, Depth-First Search, Breadth-First Search
 *
 * In the video game Fallout 4, the quest "Road to Freedom" requires players to reach a metal dial called the "Freedom Trail Ring" and use the dial to spell a specific keyword to open the door.
 * Given a string ring that represents the code engraved on the outer ring and another string key that represents the keyword that needs to be spelled, return the minimum number of steps to spell all the characters in the keyword.
 * Initially, the first character of the ring is aligned at the "12:00" direction. You should spell all the characters in key one by one by rotating ring clockwise or anticlockwise to make each character of the string key aligned at the "12:00" direction and then by pressing the center button.
 * At the stage of rotating the ring to spell the key character key[i]:
 * Example 1:
 *     Input: ring = "godding", key = "gd"
 *     Output: 4
 *     Explanation:
 *     For the first key character 'g', since it is already in place, we just need 1 step to spell this character.
 *     For the second key character 'd', we need to rotate the ring "godding" anticlockwise by two steps to make it become "ddinggo".
 *     Also, we need 1 more step for spelling.
 *     So the final output is 4.
 *
 * Example 2:
 *     Input: ring = "godding", key = "godding"
 *     Output: 13
 *
 * Constraints:
 *     - 1 <= ring.length, key.length <= 100
 *     - ring and key consist of only lower case English letters.
 *     - It is guaranteed that key could always be spelled by rotating ring.
 *
 * Template (python3):
 *     class Solution:
 *         def findRotateSteps(self, ring: str, key: str) -> int:
 */

#include "io.h"
#include <vector>
#include <cstring>
#include <climits>

int findRotateSteps(const std::string &ring, const std::string &key) {
    int n = (int)ring.size();
    int klen = (int)key.size();
    int positions[26][100];
    int pos_count[26] = {};
    for (int i = 0; i < n; i++) {
        positions[ring[i] - 'a'][pos_count[ring[i] - 'a']++] = i;
    }
    std::vector<int> dp(n, 0);
    for (int ki = klen - 1; ki >= 0; ki--) {
        std::vector<int> new_dp(n, INT_MAX);
        int ch = key[ki] - 'a';
        for (int pos = 0; pos < n; pos++) {
            for (int ti = 0; ti < pos_count[ch]; ti++) {
                int target = positions[ch][ti];
                int diff = pos - target;
                if (diff < 0) diff = -diff;
                int steps = std::min(diff, n - diff) + 1;
                int val = (ki == klen - 1) ? steps : steps + dp[target];
                if (val < new_dp[pos]) new_dp[pos] = val;
            }
        }
        dp = std::move(new_dp);
    }
    return dp[0];
}

int main(void) {
    std::string ring = read_line();
    std::string key = read_line();
    write_int(findRotateSteps(ring, key));
    return 0;
}
