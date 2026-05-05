"""Graph traversal template with three variants.

Variant 1: Clone graph (BFS)
Variant 2: DFS graph traversal with cycle detection
Variant 3: Topological sort (Kahn's algorithm)
"""

from collections import deque


# ── Variant 1: Clone graph (BFS) ─────────────────────────────────────────────
#
# Note: This variant uses a simple adjacency-list representation (dict[int, list[int]])
# rather than a Node class, to keep the template dependency-free.

def clone_graph_bfs(adj: dict[int, list[int]]) -> dict[int, list[int]]:
    """Clone an undirected graph using BFS.

    Given an adjacency list, create a deep copy of the graph.
    Uses a dictionary to map original nodes to their clones.

    Time: O(V + E), Space: O(V)
    """
    if not adj:
        return {}
    clones: dict[int, list[int]] = {}
    queue: deque[int] = deque()

    start = next(iter(adj))
    clones[start] = []
    queue.append(start)

    while queue:
        node = queue.popleft()
        for neighbor in adj[node]:
            if neighbor not in clones:
                clones[neighbor] = []
                queue.append(neighbor)
            clones[node].append(neighbor)

    return clones


# ── Variant 2: DFS graph traversal with cycle detection ──────────────────────

def has_cycle_dfs(n: int, edges: list[tuple[int, int]]) -> bool:
    """Detect if a directed graph has a cycle using DFS with three states.

    States: 0 = unvisited, 1 = visiting (in current path), 2 = visited (done).
    If we encounter a node in state 1 during DFS, there is a cycle.

    Time: O(V + E), Space: O(V)
    """
    graph: dict[int, list[int]] = {i: [] for i in range(n)}
    for u, v in edges:
        graph[u].append(v)

    state: list[int] = [0] * n  # 0=unvisited, 1=visiting, 2=visited

    def dfs(node: int) -> bool:
        """Return True if a cycle is found starting from node."""
        state[node] = 1
        for neighbor in graph[node]:
            if state[neighbor] == 1:
                return True
            if state[neighbor] == 0 and dfs(neighbor):
                return True
        state[node] = 2
        return False

    for i in range(n):
        if state[i] == 0 and dfs(i):
            return True
    return False


# ── Variant 3: Topological sort (Kahn's algorithm) ──────────────────────────

def topological_sort(n: int, edges: list[tuple[int, int]]) -> list[int]:
    """Return a topological ordering of a directed graph using Kahn's algorithm.

    Kahn's algorithm:
    1. Compute in-degree for every node.
    2. Enqueue all nodes with in-degree 0.
    3. Repeatedly dequeue a node, add it to the result, and decrease
       in-degrees of its neighbors. If a neighbor's in-degree reaches 0, enqueue it.
    4. If the result contains fewer than n nodes, a cycle exists.

    Time: O(V + E), Space: O(V)
    """
    graph: dict[int, list[int]] = {i: [] for i in range(n)}
    in_degree: list[int] = [0] * n
    for u, v in edges:
        graph[u].append(v)
        in_degree[v] += 1

    queue: deque[int] = deque(i for i in range(n) if in_degree[i] == 0)
    order: list[int] = []

    while queue:
        node = queue.popleft()
        order.append(node)
        for neighbor in graph[node]:
            in_degree[neighbor] -= 1
            if in_degree[neighbor] == 0:
                queue.append(neighbor)

    return order  # len(order) < n means there is a cycle
