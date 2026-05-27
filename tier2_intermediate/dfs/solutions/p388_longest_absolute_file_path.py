from src.wasm_libs.py.io import read_line, write_int


def main():
    lines = []
    while True:
        line = read_line()
        if not line:
            break
        lines.append(line)
    input_str = "\n".join(lines)
    stack: list[int] = [0]
    max_len = 0
    for part in input_str.split("\n"):
        depth = part.count("\t")
        name = part.lstrip("\t")
        while len(stack) > depth + 1:
            stack.pop()
        if "." in name:
            max_len = max(max_len, stack[-1] + len(name))
        else:
            stack.append(stack[-1] + len(name) + 1)
    write_int(max_len)


if __name__ == "__main__":
    main()
