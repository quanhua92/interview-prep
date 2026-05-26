/*
 * P458: Poor Pigs [PREMIUM] (Hard)
 * https://leetcode.com/problems/poor-pigs/
 * Topics: Math, Dynamic Programming, Combinatorics
 * 
 * There are buckets buckets of liquid, where exactly one of the buckets is poisonous. To figure out which one is poisonous, you feed some number of (poor) pigs the liquid to see whether they will die or not. Unfortunately, you only have minutesToTest minutes to determine which bucket is poisonous.
 * You can feed the pigs according to these steps:
 * Given buckets, minutesToDie, and minutesToTest, return the minimum number of pigs needed to figure out which bucket is poisonous within the allotted time.
 * Example 1:
 *     Input: buckets = 4, minutesToDie = 15, minutesToTest = 15
 *     Output: 2
 *     Explanation: We can determine the poisonous bucket as follows:
 *     At time 0, feed the first pig buckets 1 and 2, and feed the second pig buckets 2 and 3.
 *     At time 15, there are 4 possible outcomes:
 *     - If only the first pig dies, then bucket 1 must be poisonous.
 *     - If only the second pig dies, then bucket 3 must be poisonous.
 *     - If both pigs die, then bucket 2 must be poisonous.
 *     - If neither pig dies, then bucket 4 must be poisonous.
 * 
 * Example 2:
 *     Input: buckets = 4, minutesToDie = 15, minutesToTest = 30
 *     Output: 2
 *     Explanation: We can determine the poisonous bucket as follows:
 *     At time 0, feed the first pig bucket 1, and feed the second pig bucket 2.
 *     At time 15, there are 2 possible outcomes:
 *     - If either pig dies, then the poisonous bucket is the one it was fed.
 *     - If neither pig dies, then feed the first pig bucket 3, and feed the second pig bucket 4.
 *     At time 30, one of the two pigs must die, and the poisonous bucket is the one it was fed.
 * 
 * Constraints:
 *     - 1 <= buckets <= 1000
 *     - 1 <= minutesToDie <= minutesToTest <= 100
 * 
 * Hint: What if you only have one shot? Eg. 4 buckets, 15 mins to die, and 15 mins to test.
 * Hint: How many states can we generate with x pigs and T tests?
 * Hint: Find minimum <code>x</code> such that <code>(T+1)^x >= N</code>
 * 
 * Template (python3):
 *     class Solution:
 *         def poorPigs(self, buckets: int, minutesToDie: int, minutesToTest: int) -> int:
 */
#include "ctest.h"

int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
    abort();
}

int main(void) {
    struct { const char *label; int buckets; int mtd; int mtt; int expected; } tests[] = {
        {"example 1", 4, 15, 15, 2},
        {"example 2", 4, 15, 30, 2},
        {"single bucket", 1, 100, 100, 0},
        {"single test round", 125, 1, 1, 7},
        {"large buckets", 1000, 15, 60, 5},
        {"medium buckets", 8, 15, 30, 2},
    };
    int n = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;
    for (int i = 0; i < n; i++) {
        int got = poorPigs(tests[i].buckets, tests[i].mtd, tests[i].mtt);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL (expected %d, got %d)\n", i + 1, tests[i].label, tests[i].expected, got);
        }
    }
    printf("\n  %d/%d passed\n", passed, n);
    return passed == n ? 0 : 1;
}
