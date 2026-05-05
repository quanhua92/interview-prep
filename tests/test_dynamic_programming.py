"""Tests for tier2_intermediate/dynamic_programming"""
import sys
sys.path.insert(0, ".")
from tier2_intermediate.dynamic_programming.solutions.p070_climbing_stairs import Solution as P070
from tier2_intermediate.dynamic_programming.solutions.p322_coin_change import Solution as P322
from tier2_intermediate.dynamic_programming.solutions.p198_house_robber import Solution as P198

class TestP070ClimbingStairs:
    def test_example1(self): assert P070().solve(2) == 2
    def test_example2(self): assert P070().solve(3) == 3
    def test_base(self): assert P070().solve(1) == 1
    def test_larger(self): assert P070().solve(10) == 89

class TestP322CoinChange:
    def test_example1(self): assert P322().solve([1,2,5], 11) == 3
    def test_example2(self): assert P322().solve([2], 3) == -1
    def test_zero_amount(self): assert P322().solve([1], 0) == 0

class TestP198HouseRobber:
    def test_example1(self): assert P198().solve([1,2,3,1]) == 4
    def test_example2(self): assert P198().solve([2,7,9,3,1]) == 12
    def test_single(self): assert P198().solve([1]) == 1
    def test_empty(self): assert P198().solve([]) == 0
