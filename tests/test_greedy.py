"""Tests for tier4_expert/greedy"""
import sys
sys.path.insert(0, ".")
from tier4_expert.greedy.solutions.p055_jump_game import Solution as P055
from tier4_expert.greedy.solutions.p455_assign_cookies import Solution as P455
from tier4_expert.greedy.solutions.p134_gas_station import Solution as P134
from tier4_expert.greedy.solutions.p135_candy import Solution as P135
from tier4_expert.greedy.solutions.p621b_task_scheduler_multi_machine import Solution as P621b

class TestP055JumpGame:
    def test_all(self): assert P055().run_quiet()

    def test_example1(self): assert P055().solve([2,3,1,1,4]) == True
    def test_example2(self): assert P055().solve([3,2,1,0,4]) == False
    def test_single(self): assert P055().solve([0]) == True

class TestP455AssignCookies:
    def test_all(self): assert P455().run_quiet()

    def test_example1(self): assert P455().solve([1,2,3], [1,1]) == 1
    def test_example2(self): assert P455().solve([1,2], [1,2,3]) == 2
    def test_no_children(self): assert P455().solve([], [1,2,3]) == 0

class TestP134GasStation:
    def test_all(self): assert P134().run_quiet()

    def test_example1(self): assert P134().solve([1,2,3,4,5], [3,4,5,1,2]) == 3
    def test_impossible(self): assert P134().solve([2,3,4], [3,4,3]) == -1
    def test_example2(self): assert P134().solve([5,1,2,3,4], [4,4,1,5,1]) == 4

class TestP135Candy:
    def test_all(self): assert P135().run_quiet()

    def test_example1(self): assert P135().solve([1,0,2]) == 5
    def test_example2(self): assert P135().solve([1,2,2]) == 4
    def test_decreasing_flat(self): assert P135().solve([1,3,2,2,1]) == 7
    def test_single(self): assert P135().solve([1]) == 1

class TestP621bTaskSchedulerMultiMachine:
    def test_all(self): assert P621b().run_quiet()

    def test_lc621_ex1_m1(self): assert P621b().solve(["A","A","A","B","B","B"], 2, 1) == 8
    def test_lc621_ex2_m1(self): assert P621b().solve(["A","C","A","B","D","B"], 1, 1) == 6
    def test_lc621_ex3_m1(self): assert P621b().solve(["A","A","A","B","B","B"], 3, 1) == 10
    def test_fill_idle_m1(self): assert P621b().solve(["A","A","A","B","B","B","C","C","D"], 2, 1) == 9
    def test_single_type_m1(self): assert P621b().solve(["A","A"], 2, 1) == 4
    def test_parallel_m2(self): assert P621b().solve(["A","A","A","B","B","B"], 2, 2) == 4
    def test_unique_m2(self): assert P621b().solve(["A","C","A","B","D","B"], 1, 2) == 3
    def test_large_n_m2(self): assert P621b().solve(["A","A","A","B","B","B"], 3, 2) == 5
    def test_many_machines(self): assert P621b().solve(["A","A","A","B","B","B"], 2, 10) == 1
    def test_single_task_m1(self): assert P621b().solve(["A"], 5, 1) == 1
    def test_single_task_m3(self): assert P621b().solve(["A"], 5, 3) == 1
    def test_more_machines_than_tasks(self): assert P621b().solve(["A","B","C"], 0, 5) == 1
    def test_n0_same_task(self): assert P621b().solve(["A","A","A","A"], 0, 2) == 2
    def test_m3_n1_four_tasks(self): assert P621b().solve(["A","B","C","D"], 1, 3) == 2
