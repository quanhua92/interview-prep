/*
 * P621b: Task Scheduler with Multiple Machines (Hard)
 * https://leetcode.com/problems/task-scheduler/
 * Topics: Array, Hash Table, Greedy, Counting
 *
 * Given tasks, cooldown n, and m machines, return minimum time intervals.
 * Tasks are space-separated letters on line 1, n on line 2, m on line 3.
 *
 * Constraints:
 *     - 1 <= tasks.length <= 10^4
 *     - 0 <= n <= 100
 *     - 1 <= m <= 26
 */


#include "io.h"
#include <climits>
#include <string>
#include <vector>

int leastIntervalMulti(const std::string &tasks, int n, int m) {
    int freq[26] = {0};
    for (char c : tasks) freq[c - 'A']++;
    std::vector<std::vector<int>> cooldown(m, std::vector<int>(26, INT_MIN));
    int time = 0, remaining = (int)tasks.size();
    while (remaining > 0) {
        bool assigned = false;
        for (int mi = 0; mi < m; mi++) {
            int best_task = -1, best_count = 0;
            for (int t = 0; t < 26; t++) {
                if (freq[t] > best_count && cooldown[mi][t] <= time) {
                    best_task = t; best_count = freq[t];
                }
            }
            if (best_task >= 0) {
                freq[best_task]--;
                cooldown[mi][best_task] = time + n + 1;
                remaining--;
                assigned = true;
            }
        }
        if (assigned) { time++; }
        else {
            int next_time = INT_MAX;
            for (int mi = 0; mi < m; mi++)
                for (int t = 0; t < 26; t++)
                    if (cooldown[mi][t] > time && cooldown[mi][t] < next_time)
                        next_time = cooldown[mi][t];
            time = next_time;
        }
    }
    return time;
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
