from src.wasm_libs.py.io import read_ints, read_line, write_bool


def main():
    arr = read_ints()
    start = int(read_line())
    n = len(arr)
    visited: set[int] = set()

    def dfs(i: int) -> bool:
        if i < 0 or i >= n or i in visited:
            return False
        if arr[i] == 0:
            return True
        visited.add(i)
        jump = arr[i]
        return dfs(i + jump) or dfs(i - jump)

    write_bool(dfs(start))


if __name__ == "__main__":
    main()
