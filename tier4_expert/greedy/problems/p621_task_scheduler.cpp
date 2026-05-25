/*
 * P621: Task Scheduler (Medium)
 * https://leetcode.com/problems/task-scheduler/
 * Topics: Array, Hash Table, Greedy, Sorting, Heap, Counting
 * 
 * You are given an array of CPU tasks, each labeled with a letter from A to Z, and a number n.
 * Each CPU interval can be idle or allow the completion of one task. Tasks can be completed in any order, but there's a constraint: there has to be a gap of at least n intervals between two tasks with the same label.
 * Return the minimum number of CPU intervals required to complete all tasks.
 * 
 * Example 1:
 *     Input: tasks = ["A","A","A","B","B","B"], n = 2
 *     Output: 8
 *     Explanation: A possible sequence is: A -> B -> idle -> A -> B -> idle -> A -> B.
 *     After completing task A, you must wait two intervals before doing A again. The same applies to task B. In the 3rd interval, neither A nor B can be done, so you idle.
 * 
 * Example 2:
 *     Input: tasks = ["A","C","A","B","D","B"], n = 1
 *     Output: 6
 *     Explanation: A possible sequence is: A -> B -> C -> D -> A -> B.
 * 
 * Example 3:
 *     Input: tasks = ["A","A","A", "B","B","B"], n = 3
 *     Output: 10
 *     Explanation: A possible sequence is: A -> B -> idle -> idle -> A -> B -> idle -> idle -> A -> B.
 * 
 * Constraints:
 *     - 1 <= tasks.length <= 104
 *     - tasks[i] is an uppercase English letter.
 *     - 0 <= n <= 100
 * 
 * Template (python3):
 *     class Solution:
 *         def leastInterval(self, tasks: List[str], n: int) -> int:
 * 
 * Hint: The idle slots are determined by the most frequent task. Formula: max((maxFreq - 1) * (n + 1) + countMaxFreq, len(tasks)).
 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#include "cpptest.h"
#pragma GCC diagnostic pop
#include <algorithm>
#include <string>
#include <vector>

int leastInterval(const std::string &tasks, int n) {
    abort();
}

int main() {
    printf("\n============================================================\n");
    printf("  621. Task Scheduler\n");
    printf("============================================================\n");
    struct T { const char *label; std::string tasks; int n; int expected; };
    std::vector<T> tests = {
        {"example 1", "AAABBB", 2, 8},
        {"example 2", "ACABDB", 1, 6},
        {"example 3", "AAABBB", 3, 10},
        {"tasks fill all idle slots", "AAABBBCCD", 2, 9},
        {"single task type with long cooldown", "AA", 2, 4},
        {"no cooldown", "AABB", 0, 4},
        {"single task", "A", 5, 1},
        {"all same task", "AAAA", 2, 10},
        {"unique tasks large n", "ABC", 100, 3},
    };
    int passed = 0;
    for (int i = 0; i < (int)tests.size(); i++) {
        int got = leastInterval(tests[i].tasks, tests[i].n);
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
