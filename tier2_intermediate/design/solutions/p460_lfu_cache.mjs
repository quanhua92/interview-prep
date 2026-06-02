/**
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

import { readLine, readInt, writeInt, writeString } from '../../wasm_libs/js/io.mjs';

class LFUCache {
  constructor(capacity) {
    this.cap = capacity;
    this.keyToVal = new Map();
    this.keyToFreq = new Map();
    this.freqToKeys = new Map();
    this.minFreq = 0;
  }

  _updateFreq(key) {
    const freq = this.keyToFreq.get(key);
    const keys = this.freqToKeys.get(freq);
    keys.delete(key);
    if (keys.size === 0) {
      this.freqToKeys.delete(freq);
      if (freq === this.minFreq) this.minFreq = freq + 1;
    }
    this.keyToFreq.set(key, freq + 1);
    if (!this.freqToKeys.has(freq + 1)) this.freqToKeys.set(freq + 1, new Set());
    this.freqToKeys.get(freq + 1).add(key);
  }

  get(key) {
    if (!this.keyToVal.has(key)) return -1;
    this._updateFreq(key);
    return this.keyToVal.get(key);
  }

  put(key, value) {
    if (this.cap <= 0) return;
    if (this.keyToVal.has(key)) {
      this.keyToVal.set(key, value);
      this._updateFreq(key);
      return;
    }
    if (this.keyToVal.size >= this.cap) {
      const evictKey = this.freqToKeys.get(this.minFreq).values().next().value;
      this.freqToKeys.get(this.minFreq).delete(evictKey);
      if (this.freqToKeys.get(this.minFreq).size === 0) this.freqToKeys.delete(this.minFreq);
      this.keyToVal.delete(evictKey);
      this.keyToFreq.delete(evictKey);
    }
    this.keyToVal.set(key, value);
    this.keyToFreq.set(key, 1);
    if (!this.freqToKeys.has(1)) this.freqToKeys.set(1, new Set());
    this.freqToKeys.get(1).add(key);
    this.minFreq = 1;
  }
}

const capacity = readInt();
const numOps = readInt();
const cache = new LFUCache(capacity);

for (let i = 0; i < numOps; i++) {
  const parts = readLine().split(/\s+/);
  if (parts[0] === 'get') {
    writeInt(cache.get(parseInt(parts[1], 10)));
  } else {
    cache.put(parseInt(parts[1], 10), parseInt(parts[2], 10));
    writeString('null');
  }
}
