/*
 * P621: Task Scheduler (Medium)
 * https://leetcode.com/problems/task-scheduler/
 * Topics: Array, Hash Table, Greedy, Sorting, Heap, Counting
 *
 * Given tasks and cooldown n, return minimum CPU intervals.
 * Tasks are space-separated letters on one line, followed by n on the next line.
 *
 * Constraints:
 *     - 1 <= tasks.length <= 104
 *     - tasks[i] is an uppercase English letter.
 *     - 0 <= n <= 100
 *
 * Template (python3):
 *     class Solution:
 *         def leastInterval(self, tasks: List[str], n: int) -> int:
 */


#include "cpptest.h"
#include <algorithm>
#include <string>
#include <vector>

int leastInterval(const std::string &tasks, int n) {
    int freq[26] = {0};
    for (char c : tasks) freq[c - 'A']++;
    int max_freq = *std::max_element(freq, freq + 26);
    int max_count = 0;
    for (int i = 0; i < 26; i++) if (freq[i] == max_freq) max_count++;
    int formula = (max_freq - 1) * (n + 1) + max_count;
    return std::max(formula, (int)tasks.size());
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
