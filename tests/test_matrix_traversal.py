"""Tests for tier4_expert/matrix_traversal"""
import sys
sys.path.insert(0, ".")
from tier4_expert.matrix_traversal.solutions.p054_spiral_matrix import Solution as P054
from tier4_expert.matrix_traversal.solutions.p048_rotate_image import Solution as P048
from tier4_expert.matrix_traversal.solutions.p498_diagonal_traverse import Solution as P498

class TestP054SpiralMatrix:
    def test_all(self): assert P054().run_quiet()

    def test_example1(self):
        assert P054().solve([[1,2,3],[4,5,6],[7,8,9]]) == [1,2,3,6,9,8,7,4,5]
    def test_example2(self):
        assert P054().solve([[1,2,3,4],[5,6,7,8],[9,10,11,12]]) == [1,2,3,4,8,12,11,10,9,5,6,7]
    def test_single(self): assert P054().solve([[7]]) == [7]

class TestP048RotateImage:
    def test_all(self): assert P048().run_quiet()

    def test_example1(self):
        result = P048().solve([[1,2,3],[4,5,6],[7,8,9]])
        assert result == [[7,4,1],[8,5,2],[9,6,3]]
    def test_example2(self):
        result = P048().solve([[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]])
        assert result == [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]

class TestP498DiagonalTraverse:
    def test_all(self): assert P498().run_quiet()

    def test_example1(self):
        assert P498().solve([[1,2,3],[4,5,6],[7,8,9]]) == [1,2,4,7,5,3,6,8,9]
    def test_example2(self):
        assert P498().solve([[1,2],[3,4],[5,6]]) == [1,2,3,5,4,6]
    def test_single(self):
        assert P498().solve([[1]]) == [1]
