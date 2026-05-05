"""Tests for tier2_intermediate/two_heaps"""
import sys
sys.path.insert(0, ".")
from tier2_intermediate.two_heaps.solutions.p295_median_finder import Solution as P295
from tier2_intermediate.two_heaps.solutions.p480_sliding_window_median import Solution as P480

class TestP295MedianFinder:
    def test_example1(self):
        result = P295().solve([5,15,1,3], "median")
        assert result == [5.0, 10.0, 5.0, 4.0]
    def test_two_elements(self):
        assert P295().solve([1,2], "median") == [1.0, 1.5]

class TestP480SlidingWindowMedian:
    def test_example1(self):
        assert P480().solve([1,3,-1,-3,5,3,6,7], 3) == [1.0,-1.0,-1.0,3.0,5.0,6.0]
    def test_window_one(self):
        assert P480().solve([1,2], 1) == [1.0, 2.0]
