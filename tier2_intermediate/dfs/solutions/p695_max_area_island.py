from src.wasm_libs.py.io import read_ints, write_int


def main():
    meta = read_ints()
    rows, cols = meta[0], meta[1]
    if rows == 0 or cols == 0:
        write_int(0)
        return
    grid = [read_ints() for _ in range(rows)]
    max_area = 0

    def dfs(r, c):
        if r < 0 or r >= rows or c < 0 or c >= cols or grid[r][c] != 1:
            return 0
        grid[r][c] = 0
        return 1 + dfs(r + 1, c) + dfs(r - 1, c) + dfs(r, c + 1) + dfs(r, c - 1)

    for r in range(rows):
        for c in range(cols):
            if grid[r][c] == 1:
                max_area = max(max_area, dfs(r, c))
    write_int(max_area)


if __name__ == "__main__":
    main()
