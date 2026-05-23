"""Tests for tier1_foundation/sliding_window"""
import sys
sys.path.insert(0, ".")
from tier1_foundation.sliding_window.solutions.p003_longest_substring import Solution as P003
from tier1_foundation.sliding_window.solutions.p438_find_anagrams import Solution as P438
from tier1_foundation.sliding_window.solutions.p424_longest_repeating_char import Solution as P424

class TestP003LongestSubstring:
    def test_all(self): assert P003().run_quiet()

    def test_example1(self): assert P003().solve("abcabcbb") == 3
    def test_example2(self): assert P003().solve("bbbbb") == 1
    def test_example3(self): assert P003().solve("pwwkew") == 3
    def test_empty(self): assert P003().solve("") == 0

class TestP438FindAnagrams:
    def test_all(self): assert P438().run_quiet()

    def test_example1(self):
        result = P438().solve("cbaebabacd", "abc")
        assert sorted(result) == [0, 6]
    def test_example2(self):
        result = P438().solve("abab", "ab")
        assert sorted(result) == [0, 1, 2]
    def test_no_anagrams(self): assert P438().solve("af", "bf") == []

class TestP424LongestRepeatingChar:
    def test_all(self): assert P424().run_quiet()

    def test_example1(self): assert P424().solve("ABAB", 2) == 4
    def test_example2(self): assert P424().solve("AABABBA", 1) == 4
    def test_all_same(self): assert P424().solve("AAAA", 0) == 4
    def test_no_repeats(self): assert P424().solve("ABCDE", 1) == 2
