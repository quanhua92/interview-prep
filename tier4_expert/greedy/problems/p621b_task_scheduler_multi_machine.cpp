/*
 * P621b: Task Scheduler with Multiple Machines (Hard)
 * Extension of LeetCode 621 - Task Scheduler
 * https://leetcode.com/problems/task-scheduler/
 * Topics: Array, Hash Table, Greedy, Counting
 *
 * Given tasks, cooldown n, and m machines, return minimum time intervals.
 */


#include "cpptest.h"
#include <string>

int leastIntervalMulti(const std::string &tasks, int n, int m) {
    abort();
}

int main() {
    std::string task_line = read_line();
    std::vector<int> n_vec = read_ints();
    std::vector<int> m_vec = read_ints();
    int n = n_vec[0], m = m_vec[0];
    std::string tasks;
    for (char c : task_line) {
        if (c != ' ' && c != '\t') tasks += c;
    }
    int result = leastIntervalMulti(tasks, n, m);
    write_int(result);
    return 0;
}
