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
#include <string.h>
#include <limits.h>

int findRotateSteps(const char *ring, const char *key) {
    int n = (int)strlen(ring);
    int klen = (int)strlen(key);
    int positions[26][100];
    int pos_count[26] = {0};
    for (int i = 0; i < n; i++) {
        positions[(unsigned char)ring[i] - 'a'][pos_count[(unsigned char)ring[i] - 'a']++] = i;
    }
    int dp[100];
    for (int i = 0; i < n; i++) dp[i] = 0;
    for (int ki = klen - 1; ki >= 0; ki--) {
        int new_dp[100];
        for (int i = 0; i < n; i++) new_dp[i] = INT_MAX;
        int ch = (unsigned char)key[ki] - 'a';
        for (int pos = 0; pos < n; pos++) {
            for (int ti = 0; ti < pos_count[ch]; ti++) {
                int target = positions[ch][ti];
                int diff = pos - target;
                if (diff < 0) diff = -diff;
                int steps = (diff < n - diff ? diff : n - diff) + 1;
                int val;
                if (ki == klen - 1) {
                    val = steps;
                } else {
                    val = steps + dp[target];
                }
                if (val < new_dp[pos]) new_dp[pos] = val;
            }
        }
        memcpy(dp, new_dp, sizeof(dp));
    }
    return dp[0];
}

int main(void) {
    char *ring = read_line();
    char *key = read_line();
    write_int(findRotateSteps(ring, key));
    free(ring);
    free(key);
    return 0;
}
