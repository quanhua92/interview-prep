/*
 * P621b: Task Scheduler with Multiple Machines (Hard)
 * Extension of LeetCode 621 - Task Scheduler
 * https://leetcode.com/problems/task-scheduler/
 *
 * Topics: Array, Hash Table, Greedy, Counting
 *
 * You are given an array of CPU tasks, each labeled with a letter from A to Z,
 * a cooldown period n, and m identical parallel machines.
 *
 * Each machine can execute at most one task per time interval. Tasks can be
 * completed in any order across the machines. Cooldown is tracked per-machine:
 * if machine M runs task A at time t, that machine M cannot run task A again
 * until time t + n + 1. Other machines are unaffected and may run task A at
 * any time (including simultaneously with M).
 *
 * Return the minimum number of time intervals required to complete all tasks
 * across all m machines.
 *
 * Example 1:
 *     Input: tasks = ["A","A","A","B","B","B"], n = 2, m = 1
 *     Output: 8
 *     Explanation: This is the original LeetCode 621 problem.
 *     A -> B -> idle -> A -> B -> idle -> A -> B
 *
 * Example 2:
 *     Input: tasks = ["A","A","A","B","B","B"], n = 2, m = 2
 *     Output: 4
 *     Explanation: Cooldown is per-machine, so machines can swap tasks.
 *     t=0: M1=A, M2=B | t=1: M1=B, M2=A | t=2: idle | t=3: M1=A, M2=B
 *     At t=1, M1 can run B (M1 never ran B) and M2 can run A (M2 never ran A).
 *
 * Example 3:
 *     Input: tasks = ["A","C","A","B","D","B"], n = 1, m = 2
 *     Output: 3
 *     Explanation: Each task appears at most twice. With 2 machines:
 *     t=0: M1=A, M2=B | t=1: M1=C, M2=D | t=2: M1=A, M2=B | Done in 3.
 *
 * Example 4:
 *     Input: tasks = ["A","A","A","B","B","B"], n = 3, m = 2
 *     Output: 5
 *     Explanation: Machines swap tasks at t=1, then wait for cooldown.
 *     t=0: M1=A, M2=B | t=1: M1=B, M2=A | t=2-3: idle | t=4: M1=A, M2=B
 *
 * Example 5:
 *     Input: tasks = ["A"], n = 5, m = 3
 *     Output: 1
 *     Explanation: Only one task, completed in a single interval regardless of
 *     cooldown or number of machines.
 *
 * Constraints:
 *     - 1 <= tasks.length <= 10^4
 *     - tasks[i] is an uppercase English letter.
 *     - 0 <= n <= 100
 *     - 1 <= m <= 26
 *
 * Template (python3):
 *     class Solution:
 *         def leastInterval(self, tasks: List[str], n: int, m: int) -> int:
 *
 * Hint: At each time step, greedily assign the highest-frequency remaining task
 * to each machine, respecting that machine's per-task cooldown. When no machine
 * can run any remaining task, jump directly to the next cooldown expiry.
 */


#include "io.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#define MAX_M 26
#define MAX_TASKS 10000

int leastIntervalMulti(char *tasks, int tasksSize, int n, int m) {
    int freq[26] = {0};
    for (int i = 0; i < tasksSize; i++) freq[tasks[i] - 'A']++;
    int cooldown[MAX_M][26];
    for (int i = 0; i < m; i++)
        for (int j = 0; j < 26; j++) cooldown[i][j] = INT_MIN;
    int time = 0, remaining = tasksSize;
    while (remaining > 0) {
        int assigned = 0;
        for (int mi = 0; mi < m; mi++) {
            int best_task = -1, best_count = 0;
            for (int t = 0; t < 26; t++) {
                if (freq[t] > best_count && cooldown[mi][t] <= time) {
                    best_task = t;
                    best_count = freq[t];
                }
            }
            if (best_task >= 0) {
                freq[best_task]--;
                cooldown[mi][best_task] = time + n + 1;
                remaining--;
                assigned = 1;
            }
        }
        if (assigned) {
            time++;
        } else {
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

int main(void) {
    char *task_line = read_line();
    int n_arr_n, m_arr_n;
    int *n_arr = read_ints(&n_arr_n);
    int *m_arr = read_ints(&m_arr_n);
    int n = n_arr[0], m = m_arr[0];
    int len = (int)strlen(task_line);
    int tasksSize = 0;
    char tasks[MAX_TASKS];
    for (int i = 0; i < len; i++) {
        if (task_line[i] != ' ' && task_line[i] != '\t') {
            tasks[tasksSize++] = task_line[i];
        }
    }
    int result = leastIntervalMulti(tasks, tasksSize, n, m);
    write_int(result);
    free(task_line);
    free(n_arr);
    free(m_arr);
    return 0;
}
