"""
P460: LFU Cache [PREMIUM] (Hard)
https://leetcode.com/problems/lfu-cache/
Topics: Hash Table, Linked List, Design, Doubly-Linked List

Design and implement a data structure for a Least Frequently Used (LFU) cache.
Implement the LFUCache class:
To determine the least frequently used key, a use counter is maintained for each key in the cache. The key with the smallest use counter is the least frequently used key.
When a key is first inserted into the cache, its use counter is set to 1 (due to the put operation). The use counter for a key in the cache is incremented either a get or put operation is called on it.
The functions get and put must each run in O(1) average time complexity.
Example 1:
    Input
Example 1:
    ["LFUCache", "put", "put", "get", "put", "get", "get", "put", "get", "get", "get"]
    [[2], [1, 1], [2, 2], [1], [3, 3], [2], [3], [4, 4], [1], [3], [4]]
    Output
    [null, null, null, 1, null, -1, 3, null, -1, 3, 4]

    Explanation
    // cnt(x) = the use counter for key x
    // cache=[] will show the last used order for tiebreakers (leftmost element is  most recent)
    LFUCache lfu = new LFUCache(2);
    lfu.put(1, 1);   // cache=[1,_], cnt(1)=1
    lfu.put(2, 2);   // cache=[2,1], cnt(2)=1, cnt(1)=1
    lfu.get(1);      // return 1
    // cache=[1,2], cnt(2)=1, cnt(1)=2
    lfu.put(3, 3);   // 2 is the LFU key because cnt(2)=1 is the smallest, invalidate 2.
    // cache=[3,1], cnt(3)=1, cnt(1)=2
    lfu.get(2);      // return -1 (not found)
    lfu.get(3);      // return 3
    // cache=[3,1], cnt(3)=2, cnt(1)=2
    lfu.put(4, 4);   // Both 1 and 3 have the same cnt, but 1 is LRU, invalidate 1.
    // cache=[4,3], cnt(4)=1, cnt(3)=2
    lfu.get(1);      // return -1 (not found)
    lfu.get(3);      // return 3
    // cache=[3,4], cnt(4)=1, cnt(3)=3
    lfu.get(4);      // return 4
    // cache=[4,3], cnt(4)=2, cnt(3)=3

Constraints:
    - 1 <= capacity <= 104
    - 0 <= key <= 105
    - 0 <= value <= 109
    - At most 2 * 105 calls will be made to get and put.

Template (python3):
    class LFUCache:

        def __init__(self, capacity: int):


        def get(self, key: int) -> int:


        def put(self, key: int, value: int) -> None:



    # Your LFUCache object will be instantiated and called as such:
    # obj = LFUCache(capacity)
    # param_1 = obj.get(key)
    # obj.put(key,value)
"""

from src.wasm_libs.py.io import *


class LFUCache:
    def __init__(self, capacity: int):
        self.cap = capacity
        self.key_to_val = {}
        self.key_to_freq = {}
        self.freq_to_keys = {}

    def _update_freq(self, key: int):
        freq = self.key_to_freq[key]
        self.freq_to_keys[freq].discard(key)
        if not self.freq_to_keys[freq]:
            del self.freq_to_keys[freq]
        self.key_to_freq[key] = freq + 1
        self.freq_to_keys.setdefault(freq + 1, set()).add(key)

    def get(self, key: int) -> int:
        if key not in self.key_to_val:
            return -1
        self._update_freq(key)
        return self.key_to_val[key]

    def put(self, key: int, value: int) -> None:
        if self.cap <= 0:
            return
        if key in self.key_to_val:
            self.key_to_val[key] = value
            self._update_freq(key)
        else:
            if len(self.key_to_val) >= self.cap:
                min_freq = min(self.freq_to_keys)
                evict_key = self.freq_to_keys[min_freq].pop()
                del self.key_to_val[evict_key]
                del self.key_to_freq[evict_key]
            self.key_to_val[key] = value
            self.key_to_freq[key] = 1
            self.freq_to_keys.setdefault(1, set()).add(key)


if __name__ == "__main__":
    capacity = read_int()
    num_ops = read_int()
    cache = LFUCache(capacity)
    for _ in range(num_ops):
        parts = read_line().split()
        op = parts[0]
        if op == "get":
            write_string(str(cache.get(int(parts[1]))))
        elif op == "put":
            cache.put(int(parts[1]), int(parts[2]))
            write_string("null")
