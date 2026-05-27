/*
 * P502: IPO [PREMIUM] (Hard)
 * https://leetcode.com/problems/ipo/
 * Topics: Array, Greedy, Sorting, Heap (Priority Queue)
 *
 * Given k, w, profits[], capital[], return maximized capital after at most k projects.
 */


#include "cpptest.h"
#include <vector>

int findMaximizedCapital(int k, int w, std::vector<int> &profits, std::vector<int> &capital) {
    abort();
}

int main() {
    std::vector<int> k_vec = read_ints();
    std::vector<int> w_vec = read_ints();
    std::vector<int> profits = read_ints();
    std::vector<int> capital = read_ints();
    int result = findMaximizedCapital(k_vec[0], w_vec[0], profits, capital);
    write_int(result);
    return 0;
}
