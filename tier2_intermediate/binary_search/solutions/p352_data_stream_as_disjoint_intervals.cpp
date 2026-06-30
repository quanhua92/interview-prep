/*
 * P352: Data Stream as Disjoint Intervals [PREMIUM] (Hard)
 * https://leetcode.com/problems/data-stream-as-disjoint-intervals/
 * Topics: Binary Search, Design, Ordered Set
 *
 * Given a data stream input of non-negative integers a1, a2, ..., an, summarize the numbers seen so far as a list of disjoint intervals.
 *
 * Implement the SummaryRanges class:
 *
 * SummaryRanges() Initializes the object with an empty stream.
 * void addNum(int value) Adds the integer value to the stream.
 * int[][] getIntervals() Returns a summary of the integers in the stream currently as a list of disjoint intervals [starti, endi]. The answer should be sorted by starti.
 *
 *
 * Example 1:
 *
 * Input
 * ["SummaryRanges", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals"]
 * [[], [1], [], [3], [], [7], [], [2], [], [6], []]
 * Output
 * [null, null, [[1, 1]], null, [[1, 1], [3, 3]], null, [[1, 1], [3, 3], [7, 7]], null, [[1, 3], [7, 7]], null, [[1, 3], [6, 7]]]
 *
 * Explanation
 * SummaryRanges summaryRanges = new SummaryRanges();
 * summaryRanges.addNum(1);      // arr = [1]
 * summaryRanges.getIntervals(); // return [[1, 1]]
 * summaryRanges.addNum(3);      // arr = [1, 3]
 * summaryRanges.getIntervals(); // return [[1, 1], [3, 3]]
 * summaryRanges.addNum(7);      // arr = [1, 3, 7]
 * summaryRanges.getIntervals(); // return [[1, 1], [3, 3], [7, 7]]
 * summaryRanges.addNum(2);      // arr = [1, 2, 3, 7]
 * summaryRanges.getIntervals(); // return [[1, 3], [7, 7]]
 * summaryRanges.addNum(6);      // arr = [1, 2, 3, 6, 7]
 * summaryRanges.getIntervals(); // return [[1, 3], [6, 7]]
 *
 *
 *
 * Constraints:
 *
 * 0 <= value <= 10^4
 * At most 3 * 10^4 calls will be made to addNum and getIntervals.
 * At most 10^2 calls will be made to getIntervals.
 *
 *
 * Follow up: What if there are lots of merges and the number of disjoint intervals is small compared to the size of the data stream?
 */

#include "io.h"
#include <map>
#include <string>
#include <vector>

class SummaryRanges {
    std::map<int, int> intervals;  // start -> end
public:
    SummaryRanges() {}
    void addNum(int value) {
        int start = value, end = value;
        auto it = intervals.upper_bound(value);
        if (it != intervals.begin()) {
            auto prev = std::prev(it);
            if (prev->second >= value - 1) {
                start = prev->first;
                end = std::max(end, prev->second);
                intervals.erase(prev);
            }
        }
        while (it != intervals.end() && it->first <= end + 1) {
            end = std::max(end, it->second);
            it = intervals.erase(it);
        }
        intervals[start] = end;
    }
    std::vector<std::vector<int>> getIntervals() {
        std::vector<std::vector<int>> res;
        for (auto &p : intervals) {
            res.push_back({p.first, p.second});
        }
        return res;
    }
};

int main(void)
{
    int num_ops = read_int();
    SummaryRanges sr;
    for (int i = 0; i < num_ops; i++) {
        std::string op = read_line();
        int argc = read_int();
        std::vector<int> args = (argc > 0) ? read_ints() : std::vector<int>();
        if (op == "getIntervals") {
            std::vector<std::vector<int>> iv = sr.getIntervals();
            write_int((int)iv.size());
            for (auto &p : iv) {
                write_ints(p);
            }
        } else if (op == "addNum") {
            sr.addNum(args[0]);
        }
    }
    return 0;
}
