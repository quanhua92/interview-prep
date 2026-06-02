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
 *     - -2^31 <= val <= 2^31 - 1
 *     - At most 2 * 10^5 calls will be made to insert, remove, and getRandom.
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

#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAP_SIZE 200005

typedef struct Entry {
    int key;
    int val;
    int used;
} Entry;

typedef struct {
    int *vals;
    int val_cap;
    int val_size;
    Entry *map;
    unsigned long long seed;
} RandomizedSet;

static void rs_init(RandomizedSet *rs) {
    rs->val_cap = 64;
    rs->vals = malloc(rs->val_cap * sizeof(int));
    rs->val_size = 0;
    rs->map = calloc(MAP_SIZE, sizeof(Entry));
    rs->seed = 42;
}

static void rs_free(RandomizedSet *rs) {
    free(rs->vals);
    free(rs->map);
}

static unsigned int rs_hash(int key) {
    unsigned int h = (unsigned int)key;
    h = ((h >> 16) ^ h) * 0x45d9f3b;
    h = ((h >> 16) ^ h) * 0x45d9f3b;
    h = (h >> 16) ^ h;
    return h % MAP_SIZE;
}

static int *rs_get(RandomizedSet *rs, int key) {
    unsigned int idx = rs_hash(key);
    while (rs->map[idx].used) {
        if (rs->map[idx].key == key) return &rs->map[idx].val;
        idx = (idx + 1) % MAP_SIZE;
    }
    return NULL;
}

static void rs_put(RandomizedSet *rs, int key, int val) {
    unsigned int idx = rs_hash(key);
    while (rs->map[idx].used) {
        if (rs->map[idx].key == key) { rs->map[idx].val = val; return; }
        idx = (idx + 1) % MAP_SIZE;
    }
    rs->map[idx].key = key;
    rs->map[idx].val = val;
    rs->map[idx].used = 1;
}

static void rs_del(RandomizedSet *rs, int key) {
    unsigned int idx = rs_hash(key);
    while (rs->map[idx].used) {
        if (rs->map[idx].key == key) { rs->map[idx].used = 0; return; }
        idx = (idx + 1) % MAP_SIZE;
    }
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

int main(void)
{
    int n;
    int *n_arr = read_ints(&n);
    int num_ops = n_arr[0];
    free(n_arr);

    RandomizedSet rs;
    rs_init(&rs);

    char **ops = malloc(num_ops * sizeof(char *));
    int **all_args = malloc(num_ops * sizeof(int *));
    for (int i = 0; i < num_ops; i++) {
        ops[i] = read_line();
    }
    for (int i = 0; i < num_ops; i++) {
        all_args[i] = read_ints(&n);
    }
    for (int i = 0; i < num_ops; i++) {
        if (strcmp(ops[i], "insert") == 0) {
            write_bool(rs_insert(&rs, all_args[i][0]));
        } else if (strcmp(ops[i], "remove") == 0) {
            write_bool(rs_remove(&rs, all_args[i][0]));
        } else if (strcmp(ops[i], "getRandom") == 0) {
            write_int(rs_get_random(&rs));
        }
        free(ops[i]);
        free(all_args[i]);
    }
    free(ops);
    free(all_args);
    rs_free(&rs);
    return 0;
}
