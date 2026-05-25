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
#include "ctest.h"
#include <string.h>
#include <limits.h>

int findRotateSteps(const char *ring, const char *key) {
    abort();
}

int main(void) {
    int passed = 0;
    int total = 5;
    struct TC { const char *label; const char *ring; const char *key; int expected; };
    struct TC tests[] = {
        {"example 1", "godding", "gd", 4},
        {"example 2", "godding", "godding", 13},
        {"single char ring and key", "a", "a", 1},
        {"reverse order key", "abc", "cba", 6},
        {"repeated chars", "aaaaa", "aaa", 3},
    };
    for (int i = 0; i < total; i++) {
        int got = findRotateSteps(tests[i].ring, tests[i].key);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL (expected %d, got %d)\n", i + 1, tests[i].label, tests[i].expected, got);
        }
    }
    printf("\n  %d/%d passed\n", passed, total);
    return passed == total ? 0 : 1;
}
