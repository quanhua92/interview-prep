/*
 * P565: Array Nesting [PREMIUM] (Medium)
 * https://leetcode.com/problems/array-nesting/
 * Topics: Array, Depth-First Search
 */

#include "io.h"
#include <vector>

int main() {
    auto nums = read_ints();
    std::vector<char> visited(nums.size(), 0);
    int max_len = 0;
    for (size_t i = 0; i < nums.size(); i++) {
        if (!visited[i]) {
            int count = 0;
            int j = (int)i;
            while (!visited[j]) {
                visited[j] = 1;
                j = nums[j];
                count++;
            }
            max_len = std::max(max_len, count);
        }
    }
    write_int(max_len);
    return 0;
}
