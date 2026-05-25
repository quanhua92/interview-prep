/*
 * P575: Distribute Candies [PREMIUM] (Easy)
 * https://leetcode.com/problems/distribute-candies/
 * Topics: Array, Hash Table
 * 
 * Alice has n candies, where the ith candy is of type candyType[i]. Alice noticed that she started to gain weight, so she visited a doctor.
 * The doctor advised Alice to only eat n / 2 of the candies she has (n is always even). Alice likes her candies very much, and she wants to eat the maximum number of different types of candies while still following the doctor's advice.
 * Given the integer array candyType of length n, return the maximum number of different types of candies she can eat if she only eats n / 2 of them.
 * Example 1:
 *     Input: candyType = [1,1,2,2,3,3]
 *     Output: 3
 *     Explanation: Alice can only eat 6 / 2 = 3 candies. Since there are only 3 types, she can eat one of each type.
 * 
 * Example 2:
 *     Input: candyType = [1,1,2,3]
 *     Output: 2
 *     Explanation: Alice can only eat 4 / 2 = 2 candies. Whether she eats types [1,2], [1,3], or [2,3], she still can only eat 2 different types.
 * 
 * Example 3:
 *     Input: candyType = [6,6,6,6]
 *     Output: 1
 *     Explanation: Alice can only eat 4 / 2 = 2 candies. Even though she can eat 2 candies, she only has 1 type.
 * 
 * Constraints:
 *     - n == candyType.length
 *     - 2 <= n <= 104
 *     - n is even.
 *     - -105 <= candyType[i] <= 105
 * 
 * Hint: To maximize the number of kinds of candies, we should try to distribute candies such that Alice will gain all kinds.
 * Hint: What is the upper limit of the number of kinds of candies Alice will gain? Remember candies are to distributed equally.
 * Hint: Which data structure is the most suitable for finding the number of kinds of candies?
 * Hint: Will hashset solves the problem? Inserting all candies kind in the hashset and then checking its size with upper limit.
 * 
 * Template (python3):
 *     class Solution:
 *         def distributeCandies(self, candyType: List[int]) -> int:
 */
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <unordered_set>
#include <algorithm>

static int distributeCandies(const std::vector<int> &candyType) {
    /* TODO: Implement */
    return 0;
}

int main(void) {
    int passed = 0, total = 7;
    printf("\n============================================================\n");
    printf("  575. Distribute Candies\n");
    printf("============================================================\n");

    {
        int got = distributeCandies({1, 1, 2, 2, 3, 3});
        if (got == 3) { passed++; printf("  Test 1 (example 1): PASS\n"); }
        else { printf("  Test 1 (example 1): FAIL\n  Expected: 3, Got: %d\n", got); }
    }
    {
        int got = distributeCandies({1, 1, 2, 3});
        if (got == 2) { passed++; printf("  Test 2 (example 2): PASS\n"); }
        else { printf("  Test 2 (example 2): FAIL\n  Expected: 2, Got: %d\n", got); }
    }
    {
        int got = distributeCandies({6, 6, 6, 6});
        if (got == 1) { passed++; printf("  Test 3 (example 3): PASS\n"); }
        else { printf("  Test 3 (example 3): FAIL\n  Expected: 1, Got: %d\n", got); }
    }
    {
        int got = distributeCandies({1, 2, 3, 4});
        if (got == 2) { passed++; printf("  Test 4 (all unique types): PASS\n"); }
        else { printf("  Test 4 (all unique types): FAIL\n  Expected: 2, Got: %d\n", got); }
    }
    {
        int got = distributeCandies({-1, -1, 2, 2});
        if (got == 2) { passed++; printf("  Test 5 (negative candy types): PASS\n"); }
        else { printf("  Test 5 (negative candy types): FAIL\n  Expected: 2, Got: %d\n", got); }
    }
    {
        int got = distributeCandies({100000, -100000, 0, 50000});
        if (got == 2) { passed++; printf("  Test 6 (boundary values): PASS\n"); }
        else { printf("  Test 6 (boundary values): FAIL\n  Expected: 2, Got: %d\n", got); }
    }
    {
        int got = distributeCandies({1, 2, 1, 2, 1, 2, 3, 4});
        if (got == 4) { passed++; printf("  Test 7 (eight candies mixed): PASS\n"); }
        else { printf("  Test 7 (eight candies mixed): FAIL\n  Expected: 4, Got: %d\n", got); }
    }

    printf("\n  %d/%d passed\n", passed, total);
    printf("============================================================\n\n");
    return passed == total ? 0 : 1;
}
