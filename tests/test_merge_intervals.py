"""Tests for tier1_foundation/merge_intervals"""
import sys
sys.path.insert(0, ".")
from tier1_foundation.merge_intervals.solutions.p056_merge_intervals import Solution as P056
from tier1_foundation.merge_intervals.solutions.p253_meeting_rooms import Solution as P253
from tier1_foundation.merge_intervals.solutions.p057_insert_interval import Solution as P057

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

class TestP057InsertInterval:
    def test_example1(self):
        assert P057().solve([[1,3],[6,9]], [2,5]) == [[1,5],[6,9]]
    def test_example2(self):
        assert P057().solve([[1,2],[3,5],[6,7],[8,10],[12,16]], [4,8]) == [[1,2],[3,10],[12,16]]
    def test_empty_intervals(self):
        assert P057().solve([], [5,7]) == [[5,7]]
    def test_inside_existing(self):
        assert P057().solve([[1,5]], [2,3]) == [[1,5]]
