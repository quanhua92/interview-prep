
from src.wasm_libs.py.io import read_line, write_ints

NL = 2147483647


def build_tree(vals):
    if not vals or vals[0] is None:
        return None
    root = {"val": vals[0], "left": None, "right": None}
    queue = [root]
    i = 1
    while queue and i < len(vals):
        node = queue.pop(0)
        if i < len(vals) and vals[i] is not None:
            node["left"] = {"val": vals[i], "left": None, "right": None}
            queue.append(node["left"])
        i += 1
        if i < len(vals) and vals[i] is not None:
            node["right"] = {"val": vals[i], "left": None, "right": None}
            queue.append(node["right"])
        i += 1
    return root


def subtree_sum(node):
    if not node:
        return 0
    s = node["val"] + subtree_sum(node.get("left")) + subtree_sum(node.get("right"))
    return s


def collect_sums(node, freq):
    if not node:
        return 0
    s = node["val"] + collect_sums(node.get("left"), freq) + collect_sums(node.get("right"), freq)
    freq[s] = freq.get(s, 0) + 1
    return s


def main():
    line = read_line()
    parts = line.split()
    vals = [None if x == "null" else int(x) for x in parts]
    root = build_tree(vals)
    freq = {}
    collect_sums(root, freq)
    max_count = max(freq.values())
    result = sorted(s for s, c in freq.items() if c == max_count)
    write_ints(result)


if __name__ == "__main__":
    main()
