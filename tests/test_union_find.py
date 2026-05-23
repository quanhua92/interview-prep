"""Tests for tier4_expert/union_find"""
import sys
sys.path.insert(0, ".")
from tier4_expert.union_find.solutions.p323_connected_components import Solution as P323
from tier4_expert.union_find.solutions.p684_redundant_connection import Solution as P684
from tier4_expert.union_find.solutions.p990_satisfiability_equations import Solution as P990

class TestP323ConnectedComponents:
    def test_all(self): assert P323().run_quiet()

    def test_example(self): assert P323().solve(5, [[0,1],[1,2],[3,4]]) == 2
    def test_fully_connected(self): assert P323().solve(5, [[0,1],[1,2],[2,3],[3,4]]) == 1
    def test_no_edges(self): assert P323().solve(3, []) == 3

class TestP684RedundantConnection:
    def test_all(self): assert P684().run_quiet()

    def test_example1(self): assert P684().solve([[1,2],[1,3],[2,3]]) == [2,3]
    def test_example2(self): assert P684().solve([[1,2],[2,3],[3,4],[1,4],[1,5]]) == [1,4]

class TestP990SatisfiabilityEquations:
    def test_all(self): assert P990().run_quiet()

    def test_contradiction(self): assert P990().solve(["a==b","b!=a"]) == False
    def test_consistent(self): assert P990().solve(["b==a","a==b"]) == True
    def test_transitive(self): assert P990().solve(["a==b","b==c","a==c"]) == True
    def test_self_unequal(self): assert P990().solve(["a!=a"]) == False
