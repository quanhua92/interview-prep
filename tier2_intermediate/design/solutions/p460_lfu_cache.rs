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
 *     - 1 <= capacity <= 10^4
 *     - 0 <= key <= 10^5
 *     - 0 <= value <= 10^9
 *     - At most 2 * 10^5 calls will be made to get and put.
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

use wasm_libs::*;
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
        let old_freq = self.cache[&key].freq;
        self.cache.get_mut(&key).unwrap().freq += 1;
        let new_freq = self.cache[&key].freq;
        if let Some(list) = self.freq_map.get_mut(&old_freq) {
            list.retain(|&k| k != key);
        }
        self.freq_map.entry(new_freq).or_insert_with(VecDeque::new).push_front(key);
        if self.freq_map.get(&old_freq).map_or(true, |l| l.is_empty()) && old_freq == self.min_freq {
            self.min_freq += 1;
        }
    }

    fn get(&mut self, key: i32) -> i32 {
        if !self.cache.contains_key(&key) { return -1; }
        let val = self.cache[&key].val;
        self.update_freq(key);
        val
    }

    fn put(&mut self, key: i32, value: i32) {
        if self.cap == 0 { return; }
        if self.cache.contains_key(&key) {
            self.cache.get_mut(&key).unwrap().val = value;
            self.update_freq(key);
            return;
        }
        if self.cache.len() >= self.cap {
            if let Some(list) = self.freq_map.get_mut(&self.min_freq) {
                if let Some(evict) = list.pop_back() {
                    self.cache.remove(&evict);
                }
            }
        }
        self.cache.insert(key, Node { val: value, freq: 1 });
        self.freq_map.entry(1).or_insert_with(VecDeque::new).push_front(key);
        self.min_freq = 1;
    }
}

fn main() {
    let capacity = read_int();
    let num_ops = read_int();
    let mut lfu = LFUCache::new(capacity);

    for _ in 0..num_ops {
        let line = read_line();
        let parts: Vec<&str> = line.split_whitespace().collect();
        match parts[0] {
            "get" => {
                let key: i32 = parts[1].parse().unwrap();
                write_int(lfu.get(key));
            }
            "put" => {
                let key: i32 = parts[1].parse().unwrap();
                let value: i32 = parts[2].parse().unwrap();
                lfu.put(key, value);
                write_string("null");
            }
            _ => {}
        }
    }
    std::process::exit(0);
}
