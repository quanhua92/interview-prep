/*
 * P352: Data Stream as Disjoint Intervals [PREMIUM] (Hard)
 * https://leetcode.com/problems/data-stream-as-disjoint-intervals/
 * Topics: Binary Search, Design, Ordered Set
 * 
 * Given a data stream input of non-negative integers a1, a2, ..., an, summarize the numbers seen so far as a list of disjoint intervals.
 * Implement the SummaryRanges class:
 * Example 1:
 * Follow up: What if there are lots of merges and the number of disjoint intervals is small compared to the size of the data stream?
 *     Input
 * Example 1:
 *     ["SummaryRanges", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals"]
 *     [[], [1], [], [3], [], [7], [], [2], [], [6], []]
 *     Output
 *     [null, null, [[1, 1]], null, [[1, 1], [3, 3]], null, [[1, 1], [3, 3], [7, 7]], null, [[1, 3], [7, 7]], null, [[1, 3], [6, 7]]]
 * 
 *     Explanation
 *     SummaryRanges summaryRanges = new SummaryRanges();
 *     summaryRanges.addNum(1);      // arr = [1]
 *     summaryRanges.getIntervals(); // return [[1, 1]]
 *     summaryRanges.addNum(3);      // arr = [1, 3]
 *     summaryRanges.getIntervals(); // return [[1, 1], [3, 3]]
 *     summaryRanges.addNum(7);      // arr = [1, 3, 7]
 *     summaryRanges.getIntervals(); // return [[1, 1], [3, 3], [7, 7]]
 *     summaryRanges.addNum(2);      // arr = [1, 2, 3, 7]
 *     summaryRanges.getIntervals(); // return [[1, 3], [7, 7]]
 *     summaryRanges.addNum(6);      // arr = [1, 2, 3, 6, 7]
 *     summaryRanges.getIntervals(); // return [[1, 3], [6, 7]]
 * 
 * Constraints:
 *     - 0 <= value <= 104
 *     - At most 3 * 104 calls will be made to addNum and getIntervals.
 *     - At most 102 calls will be made to getIntervals.
 * 
 * Template (python3):
 *     class SummaryRanges:
 * 
 *         def __init__(self):
 * 
 * 
 *         def addNum(self, value: int) -> None:
 * 
 * 
 *         def getIntervals(self) -> List[List[int]]:
 * 
 * 
 * 
 *     # Your SummaryRanges object will be instantiated and called as such:
 *     # obj = SummaryRanges()
 *     # obj.addNum(value)
 *     # param_2 = obj.getIntervals()
 */
#include <cstdio>
#include <cstdlib>
#include <vector>

std::vector<std::vector<int>> solve_intervals(const std::vector<int> &values)
{
    /* TODO: Implement */
    return 0;
}

int main(void)
{
    struct Tc {
        const char *label;
        std::vector<int> values;
        std::vector<int> expected_flat;
        bool pass;
    };
    std::vector<Tc> tests = {
        {"example from problem", {1,3,7,2,6}, {1,3,6,7}, false},
        {"adjacent values merge", {1,0}, {0,1}, false},
        {"single zero", {0}, {0,0}, false},
        {"no merges sorted output", {100,1,50}, {1,1,50,50,100,100}, false},
        {"empty stream", {}, {}, false},
    };

    int passed = 0;
    for (auto &tc : tests) {
        auto got = solve_intervals(tc.values);
        std::vector<int> got_flat;
        for (auto &iv : got) { got_flat.push_back(iv[0]); got_flat.push_back(iv[1]); }
        tc.pass = (got_flat == tc.expected_flat);
        if (tc.pass) passed++;
    }

    printf("\n============================================================\n");
    printf("  352. Data Stream as Disjoint Intervals\n");
    printf("============================================================\n");
    for (int i = 0; i < (int)tests.size(); i++)
        printf("  Test %d (%s): %s\n", i + 1, tests[i].label, tests[i].pass ? "PASS" : "FAIL");
    printf("\n  %d/%d passed\n", passed, (int)tests.size());
    printf("============================================================\n");
    return passed == (int)tests.size() ? 0 : 1;
}
