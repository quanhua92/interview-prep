"""Tests for tier1_foundation/two_pointers"""
import sys
sys.path.insert(0, ".")
from tier1_foundation.two_pointers.solutions.p167_two_sum import Solution as P167
from tier1_foundation.two_pointers.solutions.p011_container_water import Solution as P011
from tier1_foundation.two_pointers.solutions.p015_three_sum import Solution as P015

class TestP167TwoSum:
    def test_all(self): assert P167().run_quiet()

class TestP011ContainerWater:
    def test_all(self): assert P011().run_quiet()

class TestP015ThreeSum:
    def test_all(self): assert P015().run_quiet()

    def test_adjacent_duplicate_pairs(self):
        result = P015().solve([-2, 0, 0, 2, 2])
        assert sorted([sorted(t) for t in result]) == [[-2, 0, 2]]

    def test_all_identical_values(self):
        result = P015().solve([0, 0, 0, 0, 0])
        assert sorted([sorted(t) for t in result]) == [[0, 0, 0]]

    def test_skip_i_with_left_right_dup(self):
        result = P015().solve([-3, -3, 0, 1, 1, 2, 2])
        assert sorted([sorted(t) for t in result]) == [[-3, 1, 2]]

    def test_triple_duplicate(self):
        result = P015().solve([-2, 0, 0, 0, 2, 2, 2])
        assert sorted([sorted(t) for t in result]) == [[-2, 0, 2], [0, 0, 0]]
