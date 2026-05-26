/*
 * P380: Insert Delete GetRandom O(1) [PREMIUM] (Medium)
 * https://leetcode.com/problems/insert-delete-getrandom-o1/
 * Topics: Array, Hash Table, Math, Design, Randomized
 * 
 * Implement the RandomizedSet class:
 * You must implement the functions of the class such that each function works in average O(1) time complexity.
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
 *     - At most 2 * 105 calls will be made to insert, remove, and getRandom.
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAP_SIZE 200005

typedef struct Entry {
    int key;
    int val;
    int used;
} Entry;

#define MT_N 624
#define MT_M 397
#define MATRIX_A 0x9908B0DFUL
#define UPPER_MASK 0x80000000UL
#define LOWER_MASK 0x7FFFFFFFUL

typedef struct {
    unsigned int mt[MT_N];
    int mti;
} MT19937;

static void mt_init_genrand(MT19937 *gen, unsigned int seed) {
    abort();
}

static void mt_init(MT19937 *gen, const unsigned int *init_key, int key_length) {
    abort();
}

static unsigned int mt_genrand(MT19937 *gen) {
    abort();
}

static int mt_randrange(MT19937 *gen, int n) {
    abort();
}

typedef struct {
    int *vals;
    int val_cap;
    int val_size;
    Entry map[MAP_SIZE];
    MT19937 rng;
} RandomizedSet;

static void rs_init(RandomizedSet *rs, unsigned int seed) {
    abort();
}

static void rs_free(RandomizedSet *rs) {
    abort();
}

static unsigned int rs_hash(int key) {
    abort();
}

static int *rs_get(RandomizedSet *rs, int key) {
    abort();
}

static void rs_put(RandomizedSet *rs, int key, int val) {
    abort();
}

static void rs_del(RandomizedSet *rs, int key) {
    abort();
}

static int rs_insert(RandomizedSet *rs, int val) {
    abort();
}

static int rs_remove(RandomizedSet *rs, int val) {
    abort();
}

static int rs_get_random(RandomizedSet *rs) {
    abort();
}

int main(void) {
    int passed = 0, total = 4;
    printf("\n============================================================\n");
    printf("  380. Insert Delete GetRandom O(1)\n");
    printf("============================================================\n");

    {
        RandomizedSet rs;
        rs_init(&rs, 42);
        int results[6];
        results[0] = rs_insert(&rs, 1);
        results[1] = rs_remove(&rs, 2);
        results[2] = rs_insert(&rs, 2);
        results[3] = rs_remove(&rs, 1);
        results[4] = rs_insert(&rs, 2);
        results[5] = rs_get_random(&rs);
        int expected[] = {1, 0, 1, 1, 0, 2};
        int ok = 1;
        for (int i = 0; i < 6; i++) if (results[i] != expected[i]) ok = 0;
        if (ok) { passed++; printf("  Test 1 (example 1): PASS\n"); }
        else { printf("  Test 1 (example 1): FAIL\n"); }
        rs_free(&rs);
    }
    {
        RandomizedSet rs;
        rs_init(&rs, 42);
        int results[6];
        results[0] = rs_insert(&rs, 10);
        results[1] = rs_insert(&rs, 20);
        results[2] = rs_insert(&rs, 30);
        results[3] = rs_get_random(&rs);
        results[4] = rs_remove(&rs, 20);
        results[5] = rs_get_random(&rs);
        int expected[] = {1, 1, 1, 30, 1, 10};
        int ok = 1;
        for (int i = 0; i < 6; i++) if (results[i] != expected[i]) ok = 0;
        if (ok) { passed++; printf("  Test 2 (insert multiple then remove middle): PASS\n"); }
        else { printf("  Test 2 (insert multiple then remove middle): FAIL\n"); }
        rs_free(&rs);
    }
    {
        RandomizedSet rs;
        rs_init(&rs, 42);
        int results[5];
        results[0] = rs_insert(&rs, 5);
        results[1] = rs_get_random(&rs);
        results[2] = rs_remove(&rs, 5);
        results[3] = rs_insert(&rs, 5);
        results[4] = rs_get_random(&rs);
        int expected[] = {1, 5, 1, 1, 5};
        int ok = 1;
        for (int i = 0; i < 5; i++) if (results[i] != expected[i]) ok = 0;
        if (ok) { passed++; printf("  Test 3 (single element cycle): PASS\n"); }
        else { printf("  Test 3 (single element cycle): FAIL\n"); }
        rs_free(&rs);
    }
    {
        RandomizedSet rs;
        rs_init(&rs, 42);
        int results[6];
        results[0] = rs_insert(&rs, 1);
        results[1] = rs_insert(&rs, 2);
        results[2] = rs_remove(&rs, 1);
        results[3] = rs_remove(&rs, 2);
        results[4] = rs_insert(&rs, 3);
        results[5] = rs_get_random(&rs);
        int expected[] = {1, 1, 1, 1, 1, 3};
        int ok = 1;
        for (int i = 0; i < 6; i++) if (results[i] != expected[i]) ok = 0;
        if (ok) { passed++; printf("  Test 4 (remove all then insert new): PASS\n"); }
        else { printf("  Test 4 (remove all then insert new): FAIL\n"); }
        rs_free(&rs);
    }

    printf("\n  %d/%d passed\n", passed, total);
    printf("============================================================\n\n");
    return passed == total ? 0 : 1;
}
