from src.wasm_libs.py.io import read_line, read_ints, write_int


def main():
    meta = read_ints()
    rows, cols = meta[0], meta[1]
    if rows == 0 or cols == 0:
        write_int(0)
        return
    grid = [list(read_line()) for _ in range(rows)]
    count = 0

    def dfs(r, c):
        if r < 0 or r >= rows or c < 0 or c >= cols or grid[r][c] != "1":
            return
        grid[r][c] = "0"
        dfs(r + 1, c)
        dfs(r - 1, c)
        dfs(r, c + 1)
        dfs(r, c - 1)

    for r in range(rows):
        for c in range(cols):
            if grid[r][c] == "1":
                count += 1
                dfs(r, c)
    write_int(count)


if __name__ == "__main__":
    main()
