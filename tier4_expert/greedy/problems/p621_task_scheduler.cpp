/*
 * P621: Task Scheduler (Medium)
 * https://leetcode.com/problems/task-scheduler/
 * Topics: Array, Hash Table, Greedy, Sorting, Heap, Counting
 *
 * Given tasks and cooldown n, return minimum CPU intervals.
 */


#include "cpptest.h"
#include <string>

int leastInterval(const std::string &tasks, int n) {
    abort();
}

int main() {
    std::string task_line = read_line();
    std::vector<int> n_vec = read_ints();
    int n = n_vec[0];
    std::string tasks;
    for (char c : task_line) {
        if (c != ' ' && c != '\t') tasks += c;
    }
    int result = leastInterval(tasks, n);
    write_int(result);
    return 0;
}
