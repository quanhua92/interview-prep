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


use wasm_libs::*;
use std::collections::HashMap;

const MT_N: usize = 624;
const MT_M: usize = 397;
const MATRIX_A: u32 = 0x9908B0DF;
const UPPER_MASK: u32 = 0x80000000;
const LOWER_MASK: u32 = 0x7FFFFFFF;

struct MT19937 {
    mt: [u32; MT_N],
    mti: usize,
}

impl MT19937 {
    fn new() -> Self {
        MT19937 { mt: [0u32; MT_N], mti: 0 }
    }

    fn init_genrand(&mut self, seed: u32) {
        self.mt[0] = seed & 0xFFFFFFFF;
        for i in 1..MT_N {
            self.mt[i] = (1812433253u32.wrapping_mul(self.mt[i - 1] ^ (self.mt[i - 1] >> 30)).wrapping_add(i as u32)) & 0xFFFFFFFF;
        }
        self.mti = MT_N;
    }

    fn init_by_array(&mut self, key: &[u32]) {
        self.init_genrand(19650218);
        let klen = key.len();
        let mut i = 1usize;
        let mut j = 0usize;
        let mut k = if MT_N > klen { MT_N } else { klen };
        while k > 0 {
            self.mt[i] = (self.mt[i] ^ ((self.mt[i - 1] ^ (self.mt[i - 1] >> 30)).wrapping_mul(1664525))).wrapping_add(key[j]).wrapping_add(j as u32) & 0xFFFFFFFF;
            i += 1;
            j += 1;
            if i >= MT_N { self.mt[0] = self.mt[MT_N - 1]; i = 1; }
            if j >= klen { j = 0; }
            k -= 1;
        }
        k = MT_N - 1;
        while k > 0 {
            self.mt[i] = (self.mt[i] ^ ((self.mt[i - 1] ^ (self.mt[i - 1] >> 30)).wrapping_mul(1566083941))).wrapping_sub(i as u32) & 0xFFFFFFFF;
            i += 1;
            if i >= MT_N { self.mt[0] = self.mt[MT_N - 1]; i = 1; }
            k -= 1;
        }
        self.mt[0] = 0x80000000;
        self.mti = MT_N;
    }

    fn genrand(&mut self) -> u32 {
        if self.mti >= MT_N {
            let mag01: [u32; 2] = [0, MATRIX_A];
            let mut kk = 0usize;
            while kk < MT_N - MT_M {
                let y = (self.mt[kk] & UPPER_MASK) | (self.mt[kk + 1] & LOWER_MASK);
                self.mt[kk] = self.mt[kk + MT_M] ^ (y >> 1) ^ mag01[(y & 1) as usize];
                kk += 1;
            }
            while kk < MT_N - 1 {
                let y = (self.mt[kk] & UPPER_MASK) | (self.mt[kk + 1] & LOWER_MASK);
                self.mt[kk] = self.mt[kk.wrapping_add(MT_M).wrapping_sub(MT_N)] ^ (y >> 1) ^ mag01[(y & 1) as usize];
                kk += 1;
            }
            let y = (self.mt[MT_N - 1] & UPPER_MASK) | (self.mt[0] & LOWER_MASK);
            self.mt[MT_N - 1] = self.mt[MT_M - 1] ^ (y >> 1) ^ mag01[(y & 1) as usize];
            self.mti = 0;
        }
        let mut y = self.mt[self.mti];
        self.mti += 1;
        y ^= y >> 11;
        y ^= (y << 7) & 0x9D2C5680;
        y ^= (y << 15) & 0xEFC60000;
        y ^= y >> 18;
        y
    }

    fn randrange(&mut self, n: usize) -> usize {
        if n <= 1 { return 0; }
        let mut k = 0usize;
        let mut tmp = n;
        while tmp > 0 { k += 1; tmp >>= 1; }
        loop {
            let r = (self.genrand() >> (32 - k)) as usize;
            if r < n { return r; }
        }
    }
}

struct RandomizedSet {
    vals: Vec<i32>,
    idx_map: HashMap<i32, usize>,
    rng: MT19937,
}

impl RandomizedSet {
    fn new(seed: u32) -> Self {
        let mut rng = MT19937::new();
        rng.init_by_array(&[seed]);
        RandomizedSet { vals: Vec::new(), idx_map: HashMap::new(), rng }
    }

    fn insert(&mut self, val: i32) -> bool {
        if self.idx_map.contains_key(&val) { return false; }
        self.idx_map.insert(val, self.vals.len());
        self.vals.push(val);
        true
    }

    fn remove(&mut self, val: i32) -> bool {
        if let Some(&idx) = self.idx_map.get(&val) {
            let last = *self.vals.last().unwrap();
            self.vals[idx] = last;
            self.idx_map.insert(last, idx);
            self.vals.pop();
            self.idx_map.remove(&val);
            true
        } else {
            false
        }
    }

    fn get_random(&mut self) -> i32 {
        let idx = self.rng.randrange(self.vals.len());
        self.vals[idx]
    }
}

fn main() {
    let header = read_ints();
    let num_ops = header[0] as usize;

    let mut rs = RandomizedSet::new(42);

    for _ in 0..num_ops {
        let op = read_line();
        let args = read_ints();
        if op == "insert" {
            write_bool(rs.insert(args[0]));
        } else if op == "remove" {
            write_bool(rs.remove(args[0]));
        } else if op == "getRandom" {
            write_int(rs.get_random());
        }
    }
    std::process::exit(0);
}
