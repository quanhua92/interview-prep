/*
 * P460: LFU Cache [PREMIUM] (Hard)
 * https://leetcode.com/problems/lfu-cache/
 * Topics: Hash Table, Linked List, Design, Doubly-Linked List
 * 
 * Design and implement a data structure for a Least Frequently Used (LFU) cache.
 * Implement the LFUCache class:
 * To determine the least frequently used key, a use counter is maintained for each key in the cache. The key with the smallest use counter is the least frequently used key.
 * When a key is first inserted into the cache, its use counter is set to 1 (due to the put operation). The use counter for a key in the cache is incremented either a get or put operation is called on it.
 * The functions get and put must each run in O(1) average time complexity.
 * Example 1:
 *     Input
 * Example 1:
 *     ["LFUCache", "put", "put", "get", "put", "get", "get", "put", "get", "get", "get"]
 *     [[2], [1, 1], [2, 2], [1], [3, 3], [2], [3], [4, 4], [1], [3], [4]]
 *     Output
 *     [null, null, null, 1, null, -1, 3, null, -1, 3, 4]
 * 
 *     Explanation
 *     // cnt(x) = the use counter for key x
 *     // cache=[] will show the last used order for tiebreakers (leftmost element is  most recent)
 *     LFUCache lfu = new LFUCache(2);
 *     lfu.put(1, 1);   // cache=[1,_], cnt(1)=1
 *     lfu.put(2, 2);   // cache=[2,1], cnt(2)=1, cnt(1)=1
 *     lfu.get(1);      // return 1
 *     // cache=[1,2], cnt(2)=1, cnt(1)=2
 *     lfu.put(3, 3);   // 2 is the LFU key because cnt(2)=1 is the smallest, invalidate 2.
 *     // cache=[3,1], cnt(3)=1, cnt(1)=2
 *     lfu.get(2);      // return -1 (not found)
 *     lfu.get(3);      // return 3
 *     // cache=[3,1], cnt(3)=2, cnt(1)=2
 *     lfu.put(4, 4);   // Both 1 and 3 have the same cnt, but 1 is LRU, invalidate 1.
 *     // cache=[4,3], cnt(4)=1, cnt(3)=2
 *     lfu.get(1);      // return -1 (not found)
 *     lfu.get(3);      // return 3
 *     // cache=[3,4], cnt(4)=1, cnt(3)=3
 *     lfu.get(4);      // return 4
 *     // cache=[4,3], cnt(4)=2, cnt(3)=3
 * 
 * Constraints:
 *     - 1 <= capacity <= 104
 *     - 0 <= key <= 105
 *     - 0 <= value <= 109
 *     - At most 2 * 105 calls will be made to get and put.
 * 
 * Template (python3):
 *     class LFUCache:
 * 
 *         def __init__(self, capacity: int):
 * 
 * 
 *         def get(self, key: int) -> int:
 * 
 * 
 *         def put(self, key: int, value: int) -> None:
 * 
 * 
 * 
 *     # Your LFUCache object will be instantiated and called as such:
 *     # obj = LFUCache(capacity)
 *     # param_1 = obj.get(key)
 *     # obj.put(key,value)
 */
#[allow(unused_imports)]
use rstest;
use std::collections::{HashMap, VecDeque};

struct Node {
    val: i32,
    freq: usize,
}

struct LFUCache {
    cap: usize,
    min_freq: usize,
    cache: HashMap<i32, Node>,
    freq_map: HashMap<usize, VecDeque<i32>>,
}

impl LFUCache {
    fn new(capacity: i32) -> Self {
        LFUCache {
            cap: capacity as usize,
            min_freq: 0,
            cache: HashMap::new(),
            freq_map: HashMap::new(),
        }
    }

    fn update_freq(&mut self, key: i32) {
        todo!()
    }

    fn get(&mut self, key: i32) -> i32 {
        todo!()
    }

    fn put(&mut self, key: i32, value: i32) {
        todo!()
    }
}

fn main() {
    println!("\n============================================================");
    println!("  460. LFU Cache");
    println!("============================================================");

    let mut lfu = LFUCache::new(2);
    lfu.put(1, 1);
    lfu.put(2, 2);
    let r1 = lfu.get(1);
    lfu.put(3, 3);
    let r2 = lfu.get(2);
    let r3 = lfu.get(3);
    lfu.put(4, 4);
    let r4 = lfu.get(1);
    let r5 = lfu.get(3);
    let r6 = lfu.get(4);

    println!("  Test 1 (get key=1 after puts): {}", if r1 == 1 { "PASS" } else { "FAIL" });
    println!("  Test 2 (get evicted key=2): {}", if r2 == -1 { "PASS" } else { "FAIL" });
    println!("  Test 3 (get key=3): {}", if r3 == 3 { "PASS" } else { "FAIL" });
    println!("  Test 4 (get evicted key=1): {}", if r4 == -1 { "PASS" } else { "FAIL" });
    println!("  Test 5 (get key=3): {}", if r5 == 3 { "PASS" } else { "FAIL" });
    println!("  Test 6 (get key=4): {}", if r6 == 4 { "PASS" } else { "FAIL" });

    let passed = (r1 == 1) as i32 + (r2 == -1) as i32 + (r3 == 3) as i32 + (r4 == -1) as i32 + (r5 == 3) as i32 + (r6 == 4) as i32;
    println!("\n  {}/6 passed", passed);
    println!("============================================================\n");

    std::process::exit(if passed == 6 { 0 } else { 1 });
}
