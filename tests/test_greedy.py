"""Tests for tier4_expert/greedy"""
import sys
sys.path.insert(0, ".")
from tier4_expert.greedy.solutions.p055_jump_game import Solution as P055
from tier4_expert.greedy.solutions.p455_assign_cookies import Solution as P455

class TestP055JumpGame:
    def test_example1(self): assert P055().solve([2,3,1,1,4]) == True
    def test_example2(self): assert P055().solve([3,2,1,0,4]) == False
    def test_single(self): assert P055().solve([0]) == True

class TestP455AssignCookies:
    def test_example1(self): assert P455().solve([1,2,3], [1,1]) == 1
    def test_example2(self): assert P455().solve([1,2], [1,2,3]) == 2
    def test_no_children(self): assert P455().solve([], [1,2,3]) == 0
