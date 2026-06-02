/*
 * P621: Task Scheduler (Medium)
 * https://leetcode.com/problems/task-scheduler/
 * Topics: Array, Hash Table, Greedy, Sorting, Heap, Counting
 *
 * Given tasks and cooldown n, return minimum CPU intervals.
 * Tasks are space-separated letters on one line, followed by n on the next line.
 *
 * Constraints:
 *     - 1 <= tasks.length <= 10^4
 *     - tasks[i] is an uppercase English letter.
 *     - 0 <= n <= 100
 *
 * Template (python3):
 *     class Solution:
 *         def leastInterval(self, tasks: List[str], n: int) -> int:
 */


#include "io.h"
#include <stdlib.h>
#include <string.h>

int leastInterval(char *tasks, int tasksSize, int n) {
    abort();
}

int main(void) {
    char *task_line = read_line();
    int n_arr_n;
    int *n_arr = read_ints(&n_arr_n);
    int n = n_arr[0];
    int len = (int)strlen(task_line);
    int tasksSize = 0;
    char tasks[10000];
    for (int i = 0; i < len; i++) {
        if (task_line[i] != ' ' && task_line[i] != '\t') {
            tasks[tasksSize++] = task_line[i];
        }
    }
    int result = leastInterval(tasks, tasksSize, n);
    write_int(result);
    free(task_line);
    free(n_arr);
    return 0;
}
