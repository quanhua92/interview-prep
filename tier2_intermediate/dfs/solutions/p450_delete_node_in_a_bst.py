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


def delete_node(root, key):
    if not root:
        return None
    if key < root["val"]:
        root["left"] = delete_node(root["left"], key)
    elif key > root["val"]:
        root["right"] = delete_node(root["right"], key)
    else:
        if not root["left"]:
            return root["right"]
        if not root["right"]:
            return root["left"]
        min_node = root["right"]
        while min_node["left"]:
            min_node = min_node["left"]
        root["val"] = min_node["val"]
        root["right"] = delete_node(root["right"], min_node["val"])
    return root


def main():
    tree_line = read_line()
    key = int(read_line())
    parts = tree_line.split()
    vals = [None if x == "null" else int(x) for x in parts]
    if not vals or vals[0] is None:
        root = None
    else:
        root = build_tree(vals)
    root = delete_node(root, key)
    result = tree_to_bfs(root)
    output = " ".join("null" if v is None else str(v) for v in result) if result else "null"
    print(output)


if __name__ == "__main__":
    main()
