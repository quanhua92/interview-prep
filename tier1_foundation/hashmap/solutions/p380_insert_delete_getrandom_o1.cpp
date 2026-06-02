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
 *     - -2^31 <= val <= 2^31 - 1
 *     - At most 2 * 10^5 calls will be made to insert, remove, and getRandom.
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
#include <cstdlib>
#include <unordered_map>
#include <vector>

class RandomizedSet {
    std::vector<int> vals;
    std::unordered_map<int, int> idx_map;
    unsigned long long seed;

    int next_rand(int n) {
        if (n <= 1) return 0;
        seed = seed * 6364136223846793005ULL + 1;
        return (int)((seed >> 33) % (unsigned long long)n);
    }

public:
    RandomizedSet() { seed = 42; }

    bool insert(int val) {
        if (idx_map.count(val)) return false;
        idx_map[val] = (int)vals.size();
        vals.push_back(val);
        return true;
    }

    bool remove(int val) {
        auto it = idx_map.find(val);
        if (it == idx_map.end()) return false;
        int idx = it->second;
        int last = vals.back();
        vals[idx] = last;
        idx_map[last] = idx;
        vals.pop_back();
        idx_map.erase(it);
        return true;
    }

    int getRandom() {
        return vals[next_rand((int)vals.size())];
    }
};

int main(void)
{
    std::vector<int> header = read_ints();
    int num_ops = header[0];

    std::vector<std::string> ops;
    for (int i = 0; i < num_ops; i++) {
        ops.push_back(read_line());
    }
    std::vector<std::vector<int>> args_list;
    for (int i = 0; i < num_ops; i++) {
        std::vector<int> args = read_ints();
        args_list.push_back(args);
    }

    RandomizedSet rs;

    for (int i = 0; i < num_ops; i++) {
        if (ops[i] == "insert") {
            write_bool(rs.insert(args_list[i][0]));
        } else if (ops[i] == "remove") {
            write_bool(rs.remove(args_list[i][0]));
        } else if (ops[i] == "getRandom") {
            write_int(rs.getRandom());
        }
    }
    return 0;
}
