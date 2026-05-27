from src.wasm_libs.py.io import read_line

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


def tree_to_bfs(root):
    if not root:
        return []
    result = []
    queue = [root]
    while queue:
        node = queue.pop(0)
        if node:
            result.append(node["val"])
            queue.append(node.get("left"))
            queue.append(node.get("right"))
        else:
            result.append(None)
    while len(result) > 1 and result[-1] is None:
        result.pop()
    return result


def reverse_inorder(node, total):
    if not node:
        return total
    total = reverse_inorder(node.get("right"), total)
    total += node["val"]
    node["val"] = total
    total = reverse_inorder(node.get("left"), total)
    return total


def main():
    line = read_line()
    if not line.strip():
        print()
        return
    parts = line.split()
    vals = [None if x == "null" else int(x) for x in parts]
    if not vals or vals[0] is None:
        print()
        return
    root = build_tree(vals)
    reverse_inorder(root, 0)
    result = tree_to_bfs(root)
    output = " ".join("null" if v is None else str(v) for v in result)
    print(output)


if __name__ == "__main__":
    main()
