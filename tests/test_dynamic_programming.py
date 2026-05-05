"""Tests for tier2_intermediate/dynamic_programming"""
import sys
sys.path.insert(0, ".")
from tier2_intermediate.dynamic_programming.solutions.p070_climbing_stairs import Solution as P070
from tier2_intermediate.dynamic_programming.solutions.p322_coin_change import Solution as P322

class TestP070ClimbingStairs:
    def test_example1(self): assert P070().solve(2) == 2
    def test_example2(self): assert P070().solve(3) == 3
    def test_base(self): assert P070().solve(1) == 1
    def test_larger(self): assert P070().solve(10) == 89

class TestP322CoinChange:
    def test_example1(self): assert P322().solve([1,2,5], 11) == 3
    def test_example2(self): assert P322().solve([2], 3) == -1
    def test_zero_amount(self): assert P322().solve([1], 0) == 0
