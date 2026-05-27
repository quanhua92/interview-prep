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
    gen->mt[0] = seed & 0xFFFFFFFFUL;
    for (int i = 1; i < MT_N; i++) {
        gen->mt[i] = (1812433253UL * (gen->mt[i - 1] ^ (gen->mt[i - 1] >> 30)) + i) & 0xFFFFFFFFUL;
    }
    gen->mti = MT_N;
}

static void mt_init(MT19937 *gen, const unsigned int *init_key, int key_length) {
    mt_init_genrand(gen, 19650218UL);
    int i = 1, j = 0, k = MT_N > key_length ? MT_N : key_length;
    for (; k; k--) {
        gen->mt[i] = (gen->mt[i] ^ ((gen->mt[i - 1] ^ (gen->mt[i - 1] >> 30)) * 1664525UL)) + init_key[j] + j;
        gen->mt[i] &= 0xFFFFFFFFUL;
        i++;
        j++;
        if (i >= MT_N) { gen->mt[0] = gen->mt[MT_N - 1]; i = 1; }
        if (j >= key_length) j = 0;
    }
    for (k = MT_N - 1; k; k--) {
        gen->mt[i] = (gen->mt[i] ^ ((gen->mt[i - 1] ^ (gen->mt[i - 1] >> 30)) * 1566083941UL)) - i;
        gen->mt[i] &= 0xFFFFFFFFUL;
        i++;
        if (i >= MT_N) { gen->mt[0] = gen->mt[MT_N - 1]; i = 1; }
    }
    gen->mt[0] = 0x80000000UL;
    gen->mti = MT_N;
}

static unsigned int mt_genrand(MT19937 *gen) {
    unsigned int y;
    static const unsigned int mag01[2] = {0x0UL, MATRIX_A};
    if (gen->mti >= MT_N) {
        int kk;
        for (kk = 0; kk < MT_N - MT_M; kk++) {
            y = (gen->mt[kk] & UPPER_MASK) | (gen->mt[kk + 1] & LOWER_MASK);
            gen->mt[kk] = gen->mt[kk + MT_M] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        for (; kk < MT_N - 1; kk++) {
            y = (gen->mt[kk] & UPPER_MASK) | (gen->mt[kk + 1] & LOWER_MASK);
            gen->mt[kk] = gen->mt[kk + (MT_M - MT_N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        y = (gen->mt[MT_N - 1] & UPPER_MASK) | (gen->mt[0] & LOWER_MASK);
        gen->mt[MT_N - 1] = gen->mt[MT_M - 1] ^ (y >> 1) ^ mag01[y & 0x1UL];
        gen->mti = 0;
    }
    y = gen->mt[gen->mti++];
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9D2C5680UL;
    y ^= (y << 15) & 0xEFC60000UL;
    y ^= (y >> 18);
    return y;
}

static int mt_randrange(MT19937 *gen, int n) {
    if (n <= 1) return 0;
    int k = 0, tmp = n;
    while (tmp > 0) { k++; tmp >>= 1; }
    for (;;) {
        unsigned int r = mt_genrand(gen) >> (32 - k);
        if ((int)r < n) return (int)r;
    }
}

typedef struct {
    int *vals;
    int val_cap;
    int val_size;
    Entry map[MAP_SIZE];
    MT19937 rng;
} RandomizedSet;

static void rs_init(RandomizedSet *rs, unsigned int seed) {
    rs->val_cap = 64;
    rs->vals = malloc(rs->val_cap * sizeof(int));
    rs->val_size = 0;
    memset(rs->map, 0, sizeof(rs->map));
    mt_init(&rs->rng, &seed, 1);
}

static void rs_free(RandomizedSet *rs) {
    free(rs->vals);
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
    if (rs_get(rs, val)) return 0;
    if (rs->val_size >= rs->val_cap) {
        rs->val_cap *= 2;
        rs->vals = realloc(rs->vals, rs->val_cap * sizeof(int));
    }
    rs_put(rs, val, rs->val_size);
    rs->vals[rs->val_size++] = val;
    return 1;
}

static int rs_remove(RandomizedSet *rs, int val) {
    int *idx_ptr = rs_get(rs, val);
    if (!idx_ptr) return 0;
    int idx = *idx_ptr;
    int last = rs->vals[rs->val_size - 1];
    rs->vals[idx] = last;
    rs_put(rs, last, idx);
    rs->val_size--;
    rs_del(rs, val);
    return 1;
}

static int rs_get_random(RandomizedSet *rs) {
    return rs->vals[mt_randrange(&rs->rng, rs->val_size)];
}

int main(void)
{
    int n;
    int *n_arr = read_ints(&n);
    int num_ops = n_arr[0];
    free(n_arr);

    RandomizedSet rs;
    rs_init(&rs, 42);

    for (int i = 0; i < num_ops; i++) {
        char *op = read_line();
        int *args = read_ints(&n);
        if (strcmp(op, "insert") == 0) {
            write_bool(rs_insert(&rs, args[0]));
        } else if (strcmp(op, "remove") == 0) {
            write_bool(rs_remove(&rs, args[0]));
        } else if (strcmp(op, "getRandom") == 0) {
            write_int(rs_get_random(&rs));
        }
        free(op);
        free(args);
    }
    rs_free(&rs);
    return 0;
}
