"""Tests for tier4_expert/graph"""
import sys
sys.path.insert(0, ".")
from tier4_expert.graph.solutions.p207_course_schedule import Solution as P207
from tier4_expert.graph.solutions.p210_course_schedule_ii import Solution as P210
from tier4_expert.graph.solutions.p997_town_judge import Solution as P997

class TestP207CourseSchedule:
    def test_all(self): assert P207().run_quiet()

    def test_example1(self): assert P207().solve(2, [[1,0]]) == True
    def test_example2(self): assert P207().solve(2, [[1,0],[0,1]]) == False
    def test_no_prereqs(self): assert P207().solve(1, []) == True

class TestP210CourseScheduleII:
    def test_all(self): assert P210().run_quiet()

    def test_example1(self): assert P210().solve(2, [[1,0]]) == [0,1]
    def test_example2(self):
        result = P210().solve(4, [[1,0],[2,0],[3,1],[3,2]])
        assert result.index(0) < result.index(1)
        assert result.index(0) < result.index(2)
        assert result.index(1) < result.index(3)
        assert result.index(2) < result.index(3)
    def test_no_prereqs(self): assert P210().solve(1, []) == [0]

class TestP997TownJudge:
    def test_all(self): assert P997().run_quiet()

    def test_example1(self): assert P997().solve(2, [[1,2]]) == 2
    def test_example2(self): assert P997().solve(3, [[1,3],[2,3]]) == 3
    def test_no_judge(self): assert P997().solve(3, [[1,3],[2,3],[3,1]]) == -1
    def test_single_person(self): assert P997().solve(1, []) == 1
