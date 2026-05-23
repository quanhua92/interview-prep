"""Tests for tier2_intermediate/dfs"""
import sys
sys.path.insert(0, ".")
from tier2_intermediate.dfs.solutions.p200_number_of_islands import Solution as P200
from tier2_intermediate.dfs.solutions.p695_max_area_island import Solution as P695
from tier2_intermediate.dfs.solutions.p1306_jump_game_three import Solution as P1306

class TestP200NumberOfIslands:
    def test_all(self): assert P200().run_quiet()

    def test_example1(self):
        grid = [["1","1","1","1","0"],["1","1","0","1","0"],["1","1","0","0","0"],["0","0","0","0","0"]]
        assert P200().solve([row[:] for row in grid]) == 1
    def test_example2(self):
        grid = [["1","1","0","0","0"],["1","1","0","0","0"],["0","0","1","0","0"],["0","0","0","1","1"]]
        assert P200().solve([row[:] for row in grid]) == 3

class TestP695MaxAreaIsland:
    def test_all(self): assert P695().run_quiet()

    def test_example1(self):
        grid = [[0,0,1,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,1,1,0,1,0,0,0,0,0,0,0,0],[0,1,0,0,1,1,0,0,1,0,1,0,0],[0,1,0,0,1,1,0,0,1,1,1,0,0],[0,0,0,0,0,0,0,0,0,0,1,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,0,0,0,0,0,0,1,1,0,0,0,0]]
        assert P695().solve([row[:] for row in grid]) == 6
    def test_example2(self):
        assert P695().solve([[0,0,0,0,0,0,0,0]]) == 0

class TestP1306JumpGameThree:
    def test_all(self): assert P1306().run_quiet()

    def test_example1(self): assert P1306().solve([4,2,3,0,3,1,2], 5) == True
    def test_example2(self): assert P1306().solve([4,2,3,0,3,1,2], 0) == True
    def test_impossible(self): assert P1306().solve([3,0,2,1,2], 2) == False
