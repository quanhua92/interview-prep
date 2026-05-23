"""Tests for tier1_foundation/bfs"""
import sys
sys.path.insert(0, ".")
from tier1_foundation.bfs.solutions.p102_level_order import Solution as P102
from tier1_foundation.bfs.solutions.p994_rotting_oranges import Solution as P994
from tier1_foundation.bfs.solutions.p1091_shortest_path_binary import Solution as P1091
from src.utils import TreeNode

class TestP102LevelOrder:
    def test_all(self): assert P102().run_quiet()

    def test_example1(self):
        result = P102().solve(TreeNode.from_list([3,9,20,None,None,15,7]))
        assert result == [[3],[9,20],[15,7]]
    def test_example2(self):
        assert P102().solve(TreeNode.from_list([1])) == [[1]]
    def test_empty(self): assert P102().solve(None) == []

class TestP994RottingOranges:
    def test_all(self): assert P994().run_quiet()

    def test_example1(self):
        assert P994().solve([[2,1,1],[1,1,0],[0,1,1]]) == 4
    def test_example2(self):
        assert P994().solve([[2,1,1],[0,1,1],[1,0,1]]) == -1
    def test_no_fresh(self): assert P994().solve([[0,2]]) == 0

class TestP1091ShortestPathBinary:
    def test_all(self): assert P1091().run_quiet()

    def test_example1(self): assert P1091().solve([[0,1],[1,0]]) == 2
    def test_example2(self): assert P1091().solve([[0,0,0],[1,1,0],[1,1,0]]) == 4
    def test_impossible(self): assert P1091().solve([[1,0],[0,1]]) == -1
    def test_single_cell(self): assert P1091().solve([[0]]) == 1
