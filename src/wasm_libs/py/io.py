import sys


def read_line() -> str:
    return sys.stdin.readline().rstrip('\n')


def read_ints() -> list[int]:
    line = read_line()
    if not line:
        return []
    return [int(x) for x in line.split()]


def read_int() -> int:
    return int(read_line())


def write_int(val: int):
    print(val)


def write_ints(arr: list[int]):
    print(" ".join(map(str, arr)))


def write_string(s: str):
    print(s)


def write_bool(b: bool):
    print("true" if b else "false")


def write_matrix(mat: list[list[int]]):
    for row in mat:
        print(" ".join(map(str, row)))
