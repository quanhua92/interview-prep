"""Tests for tier4_expert/union_find"""
import sys
sys.path.insert(0, ".")
from tier4_expert.union_find.solutions.p323_connected_components import Solution as P323
from tier4_expert.union_find.solutions.p684_redundant_connection import Solution as P684

class TestP323ConnectedComponents:
    def test_example(self): assert P323().solve(5, [[0,1],[1,2],[3,4]]) == 2
    def test_fully_connected(self): assert P323().solve(5, [[0,1],[1,2],[2,3],[3,4]]) == 1
    def test_no_edges(self): assert P323().solve(3, []) == 3

class TestP684RedundantConnection:
    def test_example1(self): assert P684().solve([[1,2],[1,3],[2,3]]) == [2,3]
    def test_example2(self): assert P684().solve([[1,2],[2,3],[3,4],[1,4],[1,5]]) == [1,4]
