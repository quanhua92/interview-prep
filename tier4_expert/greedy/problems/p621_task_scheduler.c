/*
 * P621: Task Scheduler (Medium)
 * https://leetcode.com/problems/task-scheduler/
 * Topics: Array, Hash Table, Greedy, Sorting, Heap, Counting
 *
 * Given tasks and cooldown n, return minimum CPU intervals.
 */


#include "ctest.h"

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
