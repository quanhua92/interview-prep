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


#include "ctest.h"

int leastInterval(char *tasks, int tasksSize, int n) {
    int freq[26] = {0};
    for (int i = 0; i < tasksSize; i++) freq[tasks[i] - 'A']++;
    int max_freq = 0, max_count = 0;
    for (int i = 0; i < 26; i++) {
        if (freq[i] > max_freq) { max_freq = freq[i]; max_count = 1; }
        else if (freq[i] == max_freq) max_count++;
    }
    int formula = (max_freq - 1) * (n + 1) + max_count;
    return formula > tasksSize ? formula : tasksSize;
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
