"""BFS (Breadth-First Search) pattern templates.

Three common variants of the BFS technique:

1. Tree level-order traversal: Process nodes level by level using a queue.
2. Graph shortest path: BFS with visited set to find shortest path in unweighted graphs.
3. Grid BFS: Multi-source BFS on a 2D grid (rotting oranges pattern).
"""

from collections import deque


def bfs_tree(root) -> list[list[int]]:
    """Variant 1: Tree level-order traversal.

    Traverse a binary tree level by level, returning a list of lists
    where each inner list contains the values of nodes at that level.

    Time:  O(V) -- each node is visited exactly once
    Space: O(W) -- queue holds at most one level (W = max width)

    Args:
        root: Root of a binary tree (must have .val, .left, .right attributes).

    Returns:
        List of lists, where each inner list is one level of the tree.

    Example:
        >>> # Tree:     3
        >>> #          / \\
        >>> #         9  20
        >>> #           /  \\
        >>> #          15   7
        >>> bfs_tree(root)  # returns [[3], [9, 20], [15, 7]]
    """
    if not root:
        return []

    result: list[list[int]] = []
    queue: deque = deque([root])

    while queue:
        level_size = len(queue)
        level: list[int] = []
        for _ in range(level_size):
            node = queue.popleft()
            level.append(node.val)
            if node.left:
                queue.append(node.left)
            if node.right:
                queue.append(node.right)
        result.append(level)

    return result


def bfs_shortest_path(graph: dict[int, list[int]], start: int, end: int) -> int:
    """Variant 2: Graph shortest path (unweighted).

    Find the shortest path length from start to end in an unweighted graph
    using BFS. Returns -1 if no path exists.

    Time:  O(V + E) -- each vertex and edge is visited at most once
    Space: O(V + E) -- visited set and queue

    Args:
        graph: Adjacency list representation of the graph.
        start: Starting vertex.
        end: Target vertex.

    Returns:
        Length of the shortest path, or -1 if unreachable.

    Example:
        >>> g = {1: [2, 3], 2: [4], 3: [4], 4: []}
        >>> bfs_shortest_path(g, 1, 4)
        2
    """
    if start == end:
        return 0

    visited: set[int] = {start}
    queue: deque[tuple[int, int]] = deque([(start, 0)])  # (node, distance)

    while queue:
        node, dist = queue.popleft()
        for neighbor in graph.get(node, []):
            if neighbor == end:
                return dist + 1
            if neighbor not in visited:
                visited.add(neighbor)
                queue.append((neighbor, dist + 1))

    return -1


def bfs_grid_rotting(grid: list[list[int]]) -> int:
    """Variant 3: Grid BFS (multi-source rotting oranges pattern).

    Simulate the spread of rot in a grid where:
    - 0 = empty cell
    - 1 = fresh orange
    - 2 = rotten orange

    Every minute, any fresh orange adjacent (4-directional) to a rotten
    orange becomes rotten. Return the minimum number of minutes until all
    oranges are rotten. Return -1 if some fresh oranges can never rot.

    Time:  O(R * C) -- each cell is processed at most once
    Space: O(R * C) -- queue can hold all cells in worst case

    Args:
        grid: 2D grid of integers (0, 1, or 2).

    Returns:
        Minutes until all oranges are rotten, or -1 if impossible.

    Example:
        >>> bfs_grid_rotting([[2,1,1],[1,1,0],[0,1,1]])
        4
    """
    rows = len(grid)
    if rows == 0:
        return 0
    cols = len(grid[0])

    queue: deque[tuple[int, int]] = deque()
    fresh = 0

    # Initialize: find all rotten oranges (multi-source BFS)
    for r in range(rows):
        for c in range(cols):
            if grid[r][c] == 2:
                queue.append((r, c))
            elif grid[r][c] == 1:
                fresh += 1

    if fresh == 0:
        return 0

    minutes = 0
    directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]

    while queue:
        # Process all cells at the current time step
        for _ in range(len(queue)):
            r, c = queue.popleft()
            for dr, dc in directions:
                nr, nc = r + dr, c + dc
                if 0 <= nr < rows and 0 <= nc < cols and grid[nr][nc] == 1:
                    grid[nr][nc] = 2
                    fresh -= 1
                    queue.append((nr, nc))

        # Only increment minutes if there will be more work next step
        if queue:
            minutes += 1

    return minutes if fresh == 0 else -1


if __name__ == "__main__":
    # Quick smoke tests
    assert bfs_shortest_path({1: [2, 3], 2: [4], 3: [4], 4: []}, 1, 4) == 2
    assert bfs_shortest_path({1: [2], 2: [3], 3: []}, 1, 3) == 2
    assert bfs_grid_rotting([[2, 1, 1], [1, 1, 0], [0, 1, 1]]) == 4
    assert bfs_grid_rotting([[0, 2]]) == 0
    print("All template smoke tests passed.")
