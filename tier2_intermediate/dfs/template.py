"""DFS (Depth-First Search) — 3 Variants

Variant 1: Tree DFS (pre/in/post-order)
Variant 2: Island / connected components DFS
Variant 3: Path-finding DFS (all paths)
"""

from __future__ import annotations

from typing import Any


# ---------------------------------------------------------------------------
# Variant 1: Tree DFS — pre-order, in-order, post-order
# ---------------------------------------------------------------------------

def dfs_tree_preorder(
    root: Any | None,
    visit_fn=None,
    _depth: int = 0,
) -> list[Any]:
    """Return values of a binary tree in pre-order (root -> left -> right).

    Args:
        root: TreeNode-like object with ``val``, ``left``, ``right`` attrs.
        visit_fn: Optional callable applied to each node value.
        _depth: Current recursion depth (internal).

    Returns:
        List of node values in pre-order traversal order.
    """
    if root is None:
        return []
    result: list[Any] = []
    val = root.val
    if visit_fn is not None:
        val = visit_fn(val, _depth)
    result.append(val)
    result.extend(dfs_tree_preorder(root.left, visit_fn, _depth + 1))
    result.extend(dfs_tree_preorder(root.right, visit_fn, _depth + 1))
    return result


def dfs_tree_inorder(root: Any | None) -> list[Any]:
    """Return values of a binary tree in in-order (left -> root -> right).

    Args:
        root: TreeNode-like object with ``val``, ``left``, ``right`` attrs.

    Returns:
        List of node values in in-order traversal order.
    """
    if root is None:
        return []
    result: list[Any] = []
    result.extend(dfs_tree_inorder(root.left))
    result.append(root.val)
    result.extend(dfs_tree_inorder(root.right))
    return result


def dfs_tree_postorder(root: Any | None) -> list[Any]:
    """Return values of a binary tree in post-order (left -> right -> root).

    Args:
        root: TreeNode-like object with ``val``, ``left``, ``right`` attrs.

    Returns:
        List of node values in post-order traversal order.
    """
    if root is None:
        return []
    result: list[Any] = []
    result.extend(dfs_tree_postorder(root.left))
    result.extend(dfs_tree_postorder(root.right))
    result.append(root.val)
    return result


def dfs_tree(root: Any | None, order: str = "pre") -> list[Any]:
    """Dispatch to the appropriate tree DFS variant.

    Args:
        root: TreeNode-like object.
        order: One of ``"pre"``, ``"in"``, or ``"post"``.

    Returns:
        List of node values in the requested traversal order.
    """
    dispatch = {
        "pre": dfs_tree_preorder,
        "in": dfs_tree_inorder,
        "post": dfs_tree_postorder,
    }
    if order not in dispatch:
        raise ValueError(f"Unknown order: {order!r}. Expected 'pre', 'in', or 'post'.")
    return dispatch[order](root)


# ---------------------------------------------------------------------------
# Variant 2: Island / connected components DFS (grid)
# ---------------------------------------------------------------------------

def dfs_island_count(grid: list[list[str]]) -> int:
    """Count the number of islands in a 2-D character grid.

    An island is a group of adjacent ``'1'`` cells connected horizontally
    or vertically.

    Args:
        grid: 2-D list where each cell is ``'0'`` (water) or ``'1'`` (land).

    Returns:
        Number of distinct islands found.
    """
    if not grid or not grid[0]:
        return 0

    rows: int = len(grid)
    cols: int = len(grid[0])
    count: int = 0

    def _flood(r: int, c: int) -> None:
        """Mark the entire island as visited (set to ``'0'``)."""
        if r < 0 or r >= rows or c < 0 or c >= cols or grid[r][c] != "1":
            return
        grid[r][c] = "0"
        _flood(r + 1, c)
        _flood(r - 1, c)
        _flood(r, c + 1)
        _flood(r, c - 1)

    for r in range(rows):
        for c in range(cols):
            if grid[r][c] == "1":
                count += 1
                _flood(r, c)

    return count


# ---------------------------------------------------------------------------
# Variant 3: Path-finding DFS (all paths)
# ---------------------------------------------------------------------------

def dfs_all_paths(
    graph: dict[int, list[int]],
    start: int,
    end: int,
) -> list[list[int]]:
    """Find all paths from *start* to *end* in a directed acyclic graph.

    Args:
        graph: Adjacency list mapping node -> list of neighbours.
        start: Starting node.
        end: Target node.

    Returns:
        List of paths, where each path is a list of node values.
    """
    paths: list[list[int]] = []

    def _dfs(node: int, path: list[int]) -> None:
        path.append(node)
        if node == end:
            paths.append(list(path))
        else:
            for neighbour in graph.get(node, []):
                _dfs(neighbour, path)
        path.pop()

    _dfs(start, [])
    return paths
