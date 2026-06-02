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
    int f = nodes[idx].freq;
    int p = nodes[idx].prev;
    int n = nodes[idx].next;
    if (p != -1) nodes[p].next = n; else freq_head[f] = n;
    if (n != -1) nodes[n].prev = p; else freq_tail[f] = p;
}

static void list_push_front(int idx) {
    int f = nodes[idx].freq;
    nodes[idx].prev = -1;
    nodes[idx].next = freq_head[f];
    if (freq_head[f] != -1) nodes[freq_head[f]].prev = idx;
    freq_head[f] = idx;
    if (freq_tail[f] == -1) freq_tail[f] = idx;
}

static void lfu_init(int capacity) {
    lfu_cap = capacity;
    lfu_size = 0;
    min_freq = 0;
    node_cnt = 0;
    memset(key_to_node, 0xFF, sizeof(key_to_node));
    memset(freq_head, 0xFF, sizeof(freq_head));
    memset(freq_tail, 0xFF, sizeof(freq_tail));
}

static int lfu_get(int key) {
    if (key < 0 || key >= MAXKEYS || key_to_node[key] == -1) return -1;
    int idx = key_to_node[key];
    int old_freq = nodes[idx].freq;
    list_remove(idx);
    nodes[idx].freq++;
    list_push_front(idx);
    if (freq_head[old_freq] == -1 && old_freq == min_freq) min_freq++;
    return nodes[idx].val;
}

static void lfu_put(int key, int value) {
    if (lfu_cap == 0) return;
    if (key_to_node[key] != -1) {
        int idx = key_to_node[key];
        int old_freq = nodes[idx].freq;
        list_remove(idx);
        nodes[idx].val = value;
        nodes[idx].freq++;
        list_push_front(idx);
        if (freq_head[old_freq] == -1 && old_freq == min_freq) min_freq++;
        return;
    }
    if (lfu_size >= lfu_cap) {
        int evict = freq_tail[min_freq];
        list_remove(evict);
        key_to_node[nodes[evict].key] = -1;
        lfu_size--;
    }
    int idx = node_cnt++;
    nodes[idx].key = key;
    nodes[idx].val = value;
    nodes[idx].freq = 1;
    nodes[idx].prev = -1;
    nodes[idx].next = freq_head[1];
    if (freq_head[1] != -1) nodes[freq_head[1]].prev = idx;
    freq_head[1] = idx;
    if (freq_tail[1] == -1) freq_tail[1] = idx;
    key_to_node[key] = idx;
    min_freq = 1;
    lfu_size++;
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
