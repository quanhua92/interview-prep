"""Tests for tier2_intermediate/bit_manipulation"""
import sys
sys.path.insert(0, ".")
from tier2_intermediate.bit_manipulation.solutions.p0191_number_of_1_bits import Solution as P191
from tier2_intermediate.bit_manipulation.solutions.p136_single_number import Solution as P136
from tier2_intermediate.bit_manipulation.solutions.p338_counting_bits import Solution as P338

class TestP191NumberOf1Bits:
    def test_all(self): assert P191().run_quiet()

    def test_example1(self): assert P191().solve(0b00000000000000000000000000001011) == 3
    def test_power_of_two(self): assert P191().solve(0b00000000000000000000000010000000) == 1
    def test_all_but_one(self): assert P191().solve(0b11111111111111111111111111111101) == 31
    def test_zero(self): assert P191().solve(0) == 0
    def test_large(self): assert P191().solve(0b11111111111111111111111111111111) == 32

class TestP136SingleNumber:
    def test_all(self): assert P136().run_quiet()

    def test_example1(self): assert P136().solve([2,2,1]) == 1
    def test_example2(self): assert P136().solve([4,1,2,1,2]) == 4
    def test_single(self): assert P136().solve([1]) == 1
    def test_negative(self): assert P136().solve([-1,-1,-2]) == -2

class TestP338CountingBits:
    def test_all(self): assert P338().run_quiet()

    def test_example1(self): assert P338().solve(2) == [0,1,1]
    def test_example2(self): assert P338().solve(5) == [0,1,1,2,1,2]
    def test_zero(self): assert P338().solve(0) == [0]
    def test_one(self): assert P338().solve(1) == [0,1]
    def test_seven(self): assert P338().solve(7) == [0,1,1,2,1,2,2,3]
