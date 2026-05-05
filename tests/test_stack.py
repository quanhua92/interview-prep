"""Tests for tier2_intermediate/stack"""
import sys
sys.path.insert(0, ".")
from tier2_intermediate.stack.solutions.p020_valid_parentheses import Solution as P020
from tier2_intermediate.stack.solutions.p394_decode_string import Solution as P394
from tier2_intermediate.stack.solutions.p155_min_stack import Solution as P155

class TestP020ValidParentheses:
    def test_simple_pair(self): assert P020().solve("()") == True
    def test_mixed(self): assert P020().solve("()[]{}") == True
    def test_mismatched(self): assert P020().solve("(]") == False
    def test_interleaved(self): assert P020().solve("([)]") == False
    def test_nested(self): assert P020().solve("{[]}") == True
    def test_empty(self): assert P020().solve("") == True
    def test_single_open(self): assert P020().solve("(") == False

class TestP394DecodeString:
    def test_example1(self): assert P394().solve("3[a]2[bc]") == "aaabcbc"
    def test_nested(self): assert P394().solve("3[a2[c]]") == "accaccacc"
    def test_multiple(self): assert P394().solve("2[abc]3[cd]ef") == "abcabccdcdcdef"
    def test_no_encoding(self): assert P394().solve("abc") == "abc"
    def test_deep_nesting(self): assert P394().solve("2[2[2[a]]]") == "aaaaaaaa"

class TestP155MinStack:
    def test_example1(self):
        result = P155().solve(
            ["MinStack","push","push","push","getMin","pop","top","getMin"],
            [[],[5],[-2],[3],[],[],[],[]],
        )
        assert result == [None,None,None,None,-2,None,-2,-2]

    def test_negative_values(self):
        result = P155().solve(
            ["MinStack","push","push","getMin","getMin","push","getMin","top","getMin","pop","getMin"],
            [[],[0],[1],[],[],[-3],[],[],[],[],[]],
        )
        assert result == [None,None,None,0,0,None,-3,-3,-3,None,0]
