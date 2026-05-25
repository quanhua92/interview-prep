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


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#include "cpptest.h"
#pragma GCC diagnostic pop
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
    printf("\n============================================================\n");
    printf("  621b. Task Scheduler with Multiple Machines\n");
    printf("============================================================\n");
    struct T { const char *label; std::string tasks; int n, m; int expected; };
    std::vector<T> tests = {
        {"LC621 ex1 m=1", "AAABBB", 2, 1, 8},
        {"LC621 ex2 m=1", "ACABDB", 1, 1, 6},
        {"LC621 ex3 m=1", "AAABBB", 3, 1, 10},
        {"fill idle slots m=1", "AAABBBCCD", 2, 1, 9},
        {"single task type m=1", "AA", 2, 1, 4},
        {"basic parallelism m=2", "AAABBB", 2, 2, 4},
        {"unique tasks m=2", "ACABDB", 1, 2, 3},
        {"large cooldown m=2", "AAABBB", 3, 2, 5},
        {"very many machines m=10", "AAABBB", 2, 10, 1},
        {"single task n=5 m=1", "A", 5, 1, 1},
        {"single task n=5 m=3", "A", 5, 3, 1},
        {"more machines than tasks n=0", "ABC", 0, 5, 1},
        {"n=0 same task m=2", "AAAA", 0, 2, 2},
        {"m=3 n=1 four unique tasks", "ABCD", 1, 3, 2},
        {"all same task m=2", "AAAA", 1, 2, 3},
        {"all same task m=3", "AAAAAA", 1, 3, 3},
        {"unique tasks no cooldown m=2", "ABCDE", 0, 2, 3},
    };
    int passed = 0;
    for (int i = 0; i < (int)tests.size(); i++) {
        int got = leastIntervalMulti(tests[i].tasks, tests[i].n, tests[i].m);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: %d, Got: %d\n", tests[i].expected, got);
        }
    }
    printf("\n  %d/%d passed\n", passed, (int)tests.size());
    printf("============================================================\n\n");
    return passed == (int)tests.size() ? 0 : 1;
}
