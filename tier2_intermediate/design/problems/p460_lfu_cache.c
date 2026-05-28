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
#include <stdio.h>
#include <string.h>

#define MAXKEYS 100005
#define MAXNODES 200005
#define MAXFREQ 200005

typedef struct {
    int key, val, freq;
    int prev, next;
} Node;

static Node nodes[MAXNODES];
static int node_cnt;
static int freq_head[MAXFREQ], freq_tail[MAXFREQ];
static int key_to_node[MAXKEYS];
static int lfu_cap, lfu_size, min_freq;

static void list_remove(int idx) {
    abort();
}

static void list_push_front(int idx) {
    abort();
}

static void lfu_init(int capacity) {
    abort();
}

static int lfu_get(int key) {
    abort();
}

static void lfu_put(int key, int value) {
    abort();
}

int main(void) {
    int capacity = read_int();
    int num_ops = read_int();
    lfu_init(capacity);

    for (int i = 0; i < num_ops; i++) {
        char *line = read_line();
        int key, value;
        if (line[0] == 'g') {
            sscanf(line + 4, "%d", &key);
            printf("%d\n", lfu_get(key));
        } else {
            sscanf(line + 4, "%d %d", &key, &value);
            lfu_put(key, value);
            printf("null\n");
        }
    }
    return 0;
}
