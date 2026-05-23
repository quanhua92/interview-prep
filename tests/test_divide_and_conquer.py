"""Tests for tier2_intermediate/divide_and_conquer"""
import sys
sys.path.insert(0, ".")
from tier2_intermediate.divide_and_conquer.solutions.p023_merge_k_sorted_lists import Solution as P023
from tier2_intermediate.divide_and_conquer.solutions.p912_sort_an_array import Solution as P912
from tier2_intermediate.divide_and_conquer.solutions.p169_majority_element import Solution as P169

class TestP023MergeKSortedLists:
    def test_all(self): assert P023().run_quiet()

    def test_example1(self):
        assert P023().solve([[1,4,5],[1,3,4],[2,6]]) == [1,1,2,3,4,4,5,6]
    def test_empty(self): assert P023().solve([]) == []
    def test_single_empty(self): assert P023().solve([[]]) == []
    def test_single_list(self): assert P023().solve([[1,2,3]]) == [1,2,3]
    def test_two_lists(self): assert P023().solve([[1,2],[3,4]]) == [1,2,3,4]

class TestP912SortAnArray:
    def test_all(self): assert P912().run_quiet()

    def test_example1(self): assert P912().solve([5,2,3,1]) == [1,2,3,5]
    def test_duplicates(self): assert P912().solve([5,1,1,2,0,0]) == [0,0,1,1,2,5]
    def test_single(self): assert P912().solve([1]) == [1]
    def test_empty(self): assert P912().solve([]) == []
    def test_negative(self): assert P912().solve([-3,-1,0,2,4]) == [-3,-1,0,2,4]

class TestP169MajorityElement:
    def test_all(self): assert P169().run_quiet()

    def test_example1(self): assert P169().solve([3,2,3]) == 3
    def test_example2(self): assert P169().solve([2,2,1,1,1,2,2]) == 2
    def test_single(self): assert P169().solve([1]) == 1
