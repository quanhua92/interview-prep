from src.wasm_libs.py.io import read_line, write_bool

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


def is_same(a, b):
    if not a and not b:
        return True
    if not a or not b:
        return False
    return (
        a["val"] == b["val"]
        and is_same(a.get("left"), b.get("left"))
        and is_same(a.get("right"), b.get("right"))
    )


def is_subtree(root, sub_root):
    if not sub_root:
        return True
    if not root:
        return False
    if is_same(root, sub_root):
        return True
    return is_subtree(root.get("left"), sub_root) or is_subtree(
        root.get("right"), sub_root
    )


def main():
    root_line = read_line()
    sub_line = read_line()
    root_vals = [None if x == "null" else int(x) for x in root_line.split()]
    sub_vals = [None if x == "null" else int(x) for x in sub_line.split()]
    root = build_tree(root_vals)
    sub_root = build_tree(sub_vals)
    write_bool(is_subtree(root, sub_root))


if __name__ == "__main__":
    main()
