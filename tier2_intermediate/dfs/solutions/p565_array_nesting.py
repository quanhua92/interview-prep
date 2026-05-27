from src.wasm_libs.py.io import read_ints, write_int


def main():
    nums = read_ints()
    max_len = 0
    visited = [False] * len(nums)
    for i in range(len(nums)):
        if not visited[i]:
            count = 0
            j = i
            while not visited[j]:
                visited[j] = True
                j = nums[j]
                count += 1
            max_len = max(max_len, count)
    write_int(max_len)


if __name__ == "__main__":
    main()
