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
        todo!()
    }

    fn init_by_array(&mut self, key: &[u32]) {
        todo!()
    }

    fn genrand(&mut self) -> u32 {
        todo!()
    }

    fn randrange(&mut self, n: usize) -> usize {
        todo!()
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
        todo!()
    }

    fn remove(&mut self, val: i32) -> bool {
        todo!()
    }

    fn get_random(&mut self) -> i32 {
        todo!()
    }
}

fn main() {
    let mut passed = 0;
    let total = 4;
    println!("\n============================================================");
    println!("  380. Insert Delete GetRandom O(1)");
    println!("============================================================");

    {
        let mut rs = RandomizedSet::new(42);
        let mut results = vec![];
        results.push(if rs.insert(1) { 1 } else { 0 });
        results.push(if rs.remove(2) { 1 } else { 0 });
        results.push(if rs.insert(2) { 1 } else { 0 });
        results.push(if rs.remove(1) { 1 } else { 0 });
        results.push(if rs.insert(2) { 1 } else { 0 });
        results.push(rs.get_random());
        let expected = [1, 0, 1, 1, 0, 2];
        let ok = results.iter().zip(expected.iter()).all(|(a, b)| a == b);
        if ok { passed += 1; println!("  Test 1 (example 1): PASS"); }
        else { println!("  Test 1 (example 1): FAIL"); }
    }
    {
        let mut rs = RandomizedSet::new(42);
        let mut results = vec![];
        results.push(if rs.insert(10) { 1 } else { 0 });
        results.push(if rs.insert(20) { 1 } else { 0 });
        results.push(if rs.insert(30) { 1 } else { 0 });
        results.push(rs.get_random());
        results.push(if rs.remove(20) { 1 } else { 0 });
        results.push(rs.get_random());
        let expected = [1, 1, 1, 30, 1, 10];
        let ok = results.iter().zip(expected.iter()).all(|(a, b)| a == b);
        if ok { passed += 1; println!("  Test 2 (insert multiple then remove middle): PASS"); }
        else { println!("  Test 2 (insert multiple then remove middle): FAIL"); }
    }
    {
        let mut rs = RandomizedSet::new(42);
        let mut results = vec![];
        results.push(if rs.insert(5) { 1 } else { 0 });
        results.push(rs.get_random());
        results.push(if rs.remove(5) { 1 } else { 0 });
        results.push(if rs.insert(5) { 1 } else { 0 });
        results.push(rs.get_random());
        let expected = [1, 5, 1, 1, 5];
        let ok = results.iter().zip(expected.iter()).all(|(a, b)| a == b);
        if ok { passed += 1; println!("  Test 3 (single element cycle): PASS"); }
        else { println!("  Test 3 (single element cycle): FAIL"); }
    }
    {
        let mut rs = RandomizedSet::new(42);
        let mut results = vec![];
        results.push(if rs.insert(1) { 1 } else { 0 });
        results.push(if rs.insert(2) { 1 } else { 0 });
        results.push(if rs.remove(1) { 1 } else { 0 });
        results.push(if rs.remove(2) { 1 } else { 0 });
        results.push(if rs.insert(3) { 1 } else { 0 });
        results.push(rs.get_random());
        let expected = [1, 1, 1, 1, 1, 3];
        let ok = results.iter().zip(expected.iter()).all(|(a, b)| a == b);
        if ok { passed += 1; println!("  Test 4 (remove all then insert new): PASS"); }
        else { println!("  Test 4 (remove all then insert new): FAIL"); }
    }

    println!("\n  {}/{} passed", passed, total);
    println!("============================================================\n");
    std::process::exit(if passed == total { 0 } else { 1 });
}
