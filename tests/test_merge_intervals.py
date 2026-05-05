"""Tests for tier1_foundation/merge_intervals"""
import sys
sys.path.insert(0, ".")
from tier1_foundation.merge_intervals.solutions.p056_merge_intervals import Solution as P056
from tier1_foundation.merge_intervals.solutions.p253_meeting_rooms import Solution as P253

class TestP056MergeIntervals:
    def test_example1(self):
        result = P056().solve([[1,3],[2,6],[8,10],[15,18]])
        assert result == [[1,6],[8,10],[15,18]]
    def test_example2(self):
        assert P056().solve([[1,4],[4,5]]) == [[1,5]]
    def test_overlapping_start(self):
        assert P056().solve([[1,4],[0,4]]) == [[0,4]]

class TestP253MeetingRooms:
    def test_example1(self): assert P253().solve([[0,30],[5,10],[15,20]]) == 2
    def test_example2(self): assert P253().solve([[7,10],[2,4]]) == 1
    def test_no_meetings(self): assert P253().solve([]) == 0
