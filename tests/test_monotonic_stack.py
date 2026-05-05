"""Tests for tier4_expert/monotonic_stack"""
import sys
sys.path.insert(0, ".")
from tier4_expert.monotonic_stack.solutions.p739_daily_temperatures import Solution as P739
from tier4_expert.monotonic_stack.solutions.p084_largest_rectangle import Solution as P084
from tier4_expert.monotonic_stack.solutions.p853_car_fleet import Solution as P853

class TestP739DailyTemperatures:
    def test_example1(self):
        assert P739().solve([73,74,75,71,69,72,76,73]) == [1,1,4,2,1,1,0,0]
    def test_example2(self): assert P739().solve([30,40,50,60]) == [1,1,1,0]
    def test_example3(self): assert P739().solve([30,60,90]) == [1,1,0]

class TestP084LargestRectangle:
    def test_example1(self): assert P084().solve([2,1,5,6,2,3]) == 10
    def test_example2(self): assert P084().solve([2,4]) == 4

class TestP853CarFleet:
    def test_example1(self): assert P853().solve(12, [10,8,0,5,3], [2,4,1,1,3]) == 3
    def test_single_car(self): assert P853().solve(10, [3], [3]) == 1
    def test_one_fleet(self): assert P853().solve(100, [0,2,4], [4,2,1]) == 1
