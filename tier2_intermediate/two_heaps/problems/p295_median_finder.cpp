/*
 * P295: Find Median from Data Stream (Hard)
 * https://leetcode.com/problems/find-median-from-data-stream/
 * Topics: Two Pointers, Design, Sorting, Heap (Priority Queue), Data Stream
 * 
 * The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value, and the median is the mean of the two middle values.
 * Implement the MedianFinder class:
 * 
 * Example 1:
 *     Input
 *     ["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
 *     [[], [1], [2], [], [3], []]
 *     Output
 *     [null, null, null, 1.5, null, 2.0]
 * 
 *     Explanation
 *     MedianFinder medianFinder = new MedianFinder();
 *     medianFinder.addNum(1);    // arr = [1]
 *     medianFinder.addNum(2);    // arr = [1, 2]
 *     medianFinder.findMedian(); // return 1.5 (i.e., (1 + 2) / 2)
 *     medianFinder.addNum(3);    // arr[1, 2, 3]
 *     medianFinder.findMedian(); // return 2.0
 * 
 * Constraints:
 *     - -105 <= num <= 105
 *     - There will be at least one element in the data structure before calling findMedian.
 *     - At most 5 * 104 calls will be made to addNum and findMedian.
 * 
 * Template (python3):
 *     class MedianFinder:
 * 
 *         def __init__(self):
 * 
 * 
 *         def addNum(self, num: int) -> None:
 * 
 * 
 *         def findMedian(self) -> float:
 * 
 * 
 * 
 *     # Your MedianFinder object will be instantiated and called as such:
 *     # obj = MedianFinder()
 *     # obj.addNum(num)
 *     # param_2 = obj.findMedian()
 * 
 * Hint: Use a max-heap for the lower half and a min-heap for the upper half.
 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#include "cpptest.h"
#pragma GCC diagnostic pop
#include <cmath>
#include <queue>
#include <vector>

class MedianFinder {
    std::priority_queue<int> small;
    std::priority_queue<int, std::vector<int>, std::greater<int>> large;
public:
    void addNum(int num) {
        small.push(num);
        large.push(small.top());
        small.pop();
        if (large.size() > small.size()) {
            small.push(large.top());
            large.pop();
        }
    }
    double findMedian() {
        if (small.size() > large.size()) return (double)small.top();
        return (small.top() + large.top()) / 2.0;
    }
};

std::vector<double> solve(const std::vector<int> &stream)
{
    abort();
}

static bool feq(double a, double b) {
    abort();
}

int main(void)
{
    struct {
        const char *label;
        std::vector<int> input;
        std::vector<double> expected;
    } tests[] = {
        {"stream median", {5, 15, 1, 3}, {5.0, 10.0, 5.0, 4.0}},
        {"two elements", {1, 2}, {1.0, 1.5}},
        {"single element", {42}, {42.0}},
        {"all same", {3, 3, 3, 3}, {3.0, 3.0, 3.0, 3.0}},
        {"negative numbers", {-5, -3, -1, 0}, {-5.0, -4.0, -3.0, -2.0}},
        {"alternating high low", {100, 0, 100, 0, 100, 0}, {100.0, 50.0, 100.0, 50.0, 100.0, 50.0}},
        {"descending order", {10, 9, 8, 7, 6, 5}, {10.0, 9.5, 9.0, 8.5, 8.0, 7.5}},
        {"extreme values", {-100000, 100000}, {-100000.0, 0.0}},
    };
    int n_tests = sizeof(tests) / sizeof(tests[0]);

    printf("\n============================================================\n");
    printf("  295. Find Median from Data Stream\n");
    printf("============================================================\n");
    int passed = 0;
    for (int i = 0; i < n_tests; i++) {
        std::vector<double> got = solve(tests[i].input);
        bool ok = got.size() == tests[i].expected.size();
        if (ok) {
            for (size_t j = 0; j < got.size(); j++) {
                if (!feq(got[j], tests[i].expected[j])) { ok = false; break; }
            }
        }
        if (ok) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: [");
            for (size_t j = 0; j < tests[i].expected.size(); j++) { if (j) printf(","); printf("%.1f", tests[i].expected[j]); }
            printf("]\n    Got:      [");
            for (size_t j = 0; j < got.size(); j++) { if (j) printf(","); printf("%.1f", got[j]); }
            printf("]\n");
        }
    }
    printf("\n  %d/%d passed\n", passed, n_tests);
    printf("============================================================\n\n");
    return passed == n_tests ? 0 : 1;
}
