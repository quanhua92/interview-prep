/*
 * P380: Insert Delete GetRandom O(1) [PREMIUM] (Medium)
 * https://leetcode.com/problems/insert-delete-getrandom-o1/
 * Topics: Array, Hash Table, Math, Design, Randomized
 * 
 * Implement the RandomizedSet class:
 * You must implement the functions of the class such that each function works in average O(1) time complexity.
 * Example 1:
 *     Input
 * Example 1:
 *     ["RandomizedSet", "insert", "remove", "insert", "getRandom", "remove", "insert", "getRandom"]
 *     [[], [1], [2], [2], [], [1], [2], []]
 *     Output
 *     [null, true, false, true, 2, true, false, 2]
 * 
 *     Explanation
 *     RandomizedSet randomizedSet = new RandomizedSet();
 *     randomizedSet.insert(1); // Inserts 1 to the set. Returns true as 1 was inserted successfully.
 *     randomizedSet.remove(2); // Returns false as 2 does not exist in the set.
 *     randomizedSet.insert(2); // Inserts 2 to the set, returns true. Set now contains [1,2].
 *     randomizedSet.getRandom(); // getRandom() should return either 1 or 2 randomly.
 *     randomizedSet.remove(1); // Removes 1 from the set, returns true. Set now contains [2].
 *     randomizedSet.insert(2); // 2 was already in the set, so return false.
 *     randomizedSet.getRandom(); // Since 2 is the only number in the set, getRandom() will always return 2.
 * 
 * Constraints:
 *     - -231 <= val <= 231 - 1
 *     - At most 2 * 105 calls will be made to insert, remove, and getRandom.
 *     - There will be at least one element in the data structure when getRandom is called.
 * 
 * Template (python3):
 *     class RandomizedSet:
 * 
 *         def __init__(self):
 * 
 * 
 *         def insert(self, val: int) -> bool:
 * 
 * 
 *         def remove(self, val: int) -> bool:
 * 
 * 
 *         def getRandom(self) -> int:
 * 
 * 
 * 
 *     # Your RandomizedSet object will be instantiated and called as such:
 *     # obj = RandomizedSet()
 *     # param_1 = obj.insert(val)
 *     # param_2 = obj.remove(val)
 *     # param_3 = obj.getRandom()
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <unordered_map>

class MT19937 {
    static const int N = 624;
    static const int M = 397;
    static const unsigned int MATRIX_A = 0x9908B0DFUL;
    static const unsigned int UPPER_MASK = 0x80000000UL;
    static const unsigned int LOWER_MASK = 0x7FFFFFFFUL;
    unsigned int mt[N];
    int mti;

    void initGenrand(unsigned int seed) {
        abort();
    }

public:
    void init(const std::vector<unsigned int> &key) {
        abort();
    }

    unsigned int genrand() {
        abort();
    }

    int randrange(int n) {
        abort();
    }
};

class RandomizedSet {
    std::vector<int> vals;
    std::unordered_map<int, int> idx_map;
    MT19937 rng;

public:
    RandomizedSet(unsigned int seed) { rng.init({seed}); }

    bool insert(int val) {
        abort();
    }

    bool remove(int val) {
        abort();
    }

    int getRandom() {
        abort();
    }
};

int main(void) {
    int passed = 0, total = 4;
    printf("\n============================================================\n");
    printf("  380. Insert Delete GetRandom O(1)\n");
    printf("============================================================\n");

    {
        RandomizedSet rs(42);
        int results[6];
        results[0] = rs.insert(1);
        results[1] = rs.remove(2);
        results[2] = rs.insert(2);
        results[3] = rs.remove(1);
        results[4] = rs.insert(2);
        results[5] = rs.getRandom();
        int expected[] = {1, 0, 1, 1, 0, 2};
        int ok = 1;
        for (int i = 0; i < 6; i++) if (results[i] != expected[i]) ok = 0;
        if (ok) { passed++; printf("  Test 1 (example 1): PASS\n"); }
        else { printf("  Test 1 (example 1): FAIL\n"); }
    }
    {
        RandomizedSet rs(42);
        int results[6];
        results[0] = rs.insert(10);
        results[1] = rs.insert(20);
        results[2] = rs.insert(30);
        results[3] = rs.getRandom();
        results[4] = rs.remove(20);
        results[5] = rs.getRandom();
        int expected[] = {1, 1, 1, 30, 1, 10};
        int ok = 1;
        for (int i = 0; i < 6; i++) if (results[i] != expected[i]) ok = 0;
        if (ok) { passed++; printf("  Test 2 (insert multiple then remove middle): PASS\n"); }
        else { printf("  Test 2 (insert multiple then remove middle): FAIL\n"); }
    }
    {
        RandomizedSet rs(42);
        int results[5];
        results[0] = rs.insert(5);
        results[1] = rs.getRandom();
        results[2] = rs.remove(5);
        results[3] = rs.insert(5);
        results[4] = rs.getRandom();
        int expected[] = {1, 5, 1, 1, 5};
        int ok = 1;
        for (int i = 0; i < 5; i++) if (results[i] != expected[i]) ok = 0;
        if (ok) { passed++; printf("  Test 3 (single element cycle): PASS\n"); }
        else { printf("  Test 3 (single element cycle): FAIL\n"); }
    }
    {
        RandomizedSet rs(42);
        int results[6];
        results[0] = rs.insert(1);
        results[1] = rs.insert(2);
        results[2] = rs.remove(1);
        results[3] = rs.remove(2);
        results[4] = rs.insert(3);
        results[5] = rs.getRandom();
        int expected[] = {1, 1, 1, 1, 1, 3};
        int ok = 1;
        for (int i = 0; i < 6; i++) if (results[i] != expected[i]) ok = 0;
        if (ok) { passed++; printf("  Test 4 (remove all then insert new): PASS\n"); }
        else { printf("  Test 4 (remove all then insert new): FAIL\n"); }
    }

    printf("\n  %d/%d passed\n", passed, total);
    printf("============================================================\n\n");
    return passed == total ? 0 : 1;
}
