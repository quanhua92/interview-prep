"""Tests for tier2_intermediate/prefix_sum"""
import sys
sys.path.insert(0, ".")
from tier2_intermediate.prefix_sum.solutions.p0560_subarray_sum_equals_k import Solution as P560
from tier2_intermediate.prefix_sum.solutions.p0238_product_except_self import Solution as P238
from tier2_intermediate.prefix_sum.solutions.p0713_subarray_product_less_than_k import Solution as P713

class TestP560SubarraySumEqualsK:
    def test_all(self): assert P560().run_quiet()

    def test_example1(self):
        assert P560().solve([1,1,1], 2) == 2
    def test_example2(self):
        assert P560().solve([1,2,3], 3) == 2
    def test_empty(self):
        assert P560().solve([], 0) == 0
    def test_all_zero(self):
        assert P560().solve([0,0,0], 0) == 6

class TestP238ProductExceptSelf:
    def test_all(self): assert P238().run_quiet()

    def test_example1(self):
        assert P238().solve([1,2,3,4]) == [24,12,8,6]
    def test_example2(self):
        assert P238().solve([-1,1,0,-3,3]) == [0,0,9,0,0]
    def test_two_elements(self):
        assert P238().solve([1,2]) == [2,1]

class TestP713SubarrayProductLessThanK:
    def test_all(self): assert P713().run_quiet()

    def test_example1(self):
        assert P713().solve([10,5,2,6], 100) == 8
    def test_zero_k(self):
        assert P713().solve([1,2,3], 0) == 0
    def test_all_ones(self):
        assert P713().solve([1,1,1], 2) == 6
