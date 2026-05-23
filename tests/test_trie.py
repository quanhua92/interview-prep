"""Tests for tier3_advanced/trie"""
import sys
sys.path.insert(0, ".")
from tier3_advanced.trie.solutions.p208_implement_trie import Solution as P208
from tier3_advanced.trie.solutions.p212_word_search_ii import Solution as P212
from tier3_advanced.trie.solutions.p211_design_add_search import Solution as P211

class TestP208ImplementTrie:
    def test_all(self): assert P208().run_quiet()

    def test_full_sequence(self):
        result = P208().solve([
            ("insert", "apple"), ("search", "apple"), ("search", "app"),
            ("starts_with", "app"), ("insert", "app"), ("search", "app"),
        ])
        assert result == [None, True, False, True, None, True]

class TestP212WordSearchII:
    def test_all(self): assert P212().run_quiet()

    def test_example1(self):
        result = P212().solve(
            [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]],
            ["oath","pea","eat","rain"]
        )
        assert sorted(result) == ["eat", "oath"]
    def test_example2(self):
        assert P212().solve([["a","b"],["c","d"]], ["abcb"]) == []

class TestP211DesignAddSearch:
    def test_all(self): assert P211().run_quiet()

    def test_example1(self):
        assert P211().solve(["bad","dad","mad"], ["pad","bad",".ad","b.."]) == [False,True,True,True]
    def test_example2(self):
        assert P211().solve(["a","ab"], ["a",".a","ab"]) == [True,False,True]
