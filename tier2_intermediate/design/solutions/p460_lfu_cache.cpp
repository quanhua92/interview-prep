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

#include "io.h"
#include <cstdio>
#include <cstring>
#include <sstream>
#include <unordered_map>
#include <list>

class LFUCache {
    struct Node {
        int key, val, freq;
        std::list<int>::iterator it;
    };

    int cap, minFreq;
    std::unordered_map<int, Node> cache;
    std::unordered_map<int, std::list<int>> freqMap;

    void touch(int key) {
        auto &node = cache[key];
        int oldFreq = node.freq++;
        freqMap[oldFreq].erase(node.it);
        freqMap[node.freq].push_front(key);
        node.it = freqMap[node.freq].begin();
        if (freqMap[oldFreq].empty() && oldFreq == minFreq) minFreq++;
    }

public:
    LFUCache(int capacity) : cap(capacity), minFreq(0) {}

    int get(int key) {
        if (!cache.count(key)) return -1;
        touch(key);
        return cache[key].val;
    }

    void put(int key, int value) {
        if (cap == 0) return;
        if (cache.count(key)) {
            cache[key].val = value;
            touch(key);
            return;
        }
        if ((int)cache.size() >= cap) {
            int evict = freqMap[minFreq].back();
            freqMap[minFreq].pop_back();
            cache.erase(evict);
        }
        freqMap[1].push_front(key);
        cache[key] = {key, value, 1, freqMap[1].begin()};
        minFreq = 1;
    }
};

static int read_int_val() {
    std::string line = read_line();
    return std::stoi(line);
}

int main(void) {
    int capacity = read_int_val();
    int num_ops = read_int_val();
    LFUCache lfu(capacity);

    for (int i = 0; i < num_ops; i++) {
        std::string line = read_line();
        std::istringstream iss(line);
        std::string op;
        iss >> op;
        if (op == "get") {
            int key;
            iss >> key;
            write_int(lfu.get(key));
        } else {
            int key, value;
            iss >> key >> value;
            lfu.put(key, value);
            write_string("null");
        }
    }
    return 0;
}
