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
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#define MAX_M 26
#define MAX_TASKS 10000

int leastIntervalMulti(char *tasks, int tasksSize, int n, int m) {
    abort();
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
