# Graph Algorithms: BFS, DFS & Topological Sort

## One-Liner
Master graph traversal (BFS, DFS), cycle detection, topological sort, shortest path, and Union-Find with clear templates and complexity analysis.

## Graph Problem Recognition
Graph problems appear in two forms:
1. **Explicit graphs** -- problem gives you nodes and edges (adjacency list/matrix).
2. **Implicit graphs** -- the graph is derived from the problem structure (grid problems, word transformations, state-space search).

Recognizing implicit graphs is a key skill. When you see a grid, think BFS/DFS. When you see "transform word A to word B", think BFS on word states.

## BFS Template -- Shortest Path in Unweighted Graph
```python
from collections import deque

def bfs(graph: dict, start: int, target: int) -> int:
    """Returns shortest distance from start to target."""
    visited = {start}
    queue = deque([(start, 0)])  # (node, distance)

    while queue:
        node, dist = queue.popleft()
        if node == target:
            return dist
        for neighbor in graph.get(node, []):
            if neighbor not in visited:
                visited.add(neighbor)
                queue.append((neighbor, dist + 1))
    return -1  # not reachable

# For grid BFS:
DIRS = [(0,1),(0,-1),(1,0),(-1,0)]
def bfs_grid(grid, start_r, start_c):
    rows, cols = len(grid), len(grid[0])
    visited = {(start_r, start_c)}
    queue = deque([(start_r, start_c, 0)])
    while queue:
        r, c, dist = queue.popleft()
        for dr, dc in DIRS:
            nr, nc = r+dr, c+dc
            if 0<=nr<rows and 0<=nc<cols and (nr,nc) not in visited and grid[nr][nc] != '#':
                visited.add((nr, nc))
                queue.append((nr, nc, dist+1))
```

## DFS Template -- Connected Components & Cycle Detection
```python
def dfs_iterative(graph: dict, start: int) -> set:
    """Returns all nodes reachable from start."""
    visited = set()
    stack = [start]
    while stack:
        node = stack.pop()
        if node in visited:
            continue
        visited.add(node)
        for neighbor in graph.get(node, []):
            if neighbor not in visited:
                stack.append(neighbor)
    return visited

def has_cycle_directed(graph: dict) -> bool:
    """Cycle detection in directed graph using DFS + colors."""
    WHITE, GRAY, BLACK = 0, 1, 2
    color = {node: WHITE for node in graph}

    def dfs(node):
        color[node] = GRAY
        for neighbor in graph.get(node, []):
            if color[neighbor] == GRAY:  # back edge -> cycle
                return True
            if color[neighbor] == WHITE and dfs(neighbor):
                return True
        color[node] = BLACK
        return False

    return any(dfs(n) for n in graph if color[n] == WHITE)
```

## BFS vs DFS -- When to Use Which
| Algorithm | Use When | Time Complexity |
|-----------|----------|-----------------|
| **BFS** | Shortest path in unweighted graph, level-order | O(V + E) |
| **DFS** | Connected components, cycle detection, path finding | O(V + E) |
| **Topological Sort (Kahn)** | Task dependencies, course prerequisites | O(V + E) |
| **Dijkstra** | Shortest path in weighted graph (non-negative weights) | O((V + E) log V) |
| **Union-Find** | Connected components, cycle in undirected graph | O(alpha(V)) per op |
| **Multi-source BFS** | Distance from multiple sources simultaneously | O(V + E) |

## Topological Sort (Kahn's Algorithm, BFS)
```python
from collections import deque

def topological_sort(num_nodes: int, edges: list[list[int]]) -> list[int]:
    """
    Returns topological ordering or [] if cycle exists.
    Use case: Course Schedule, Task Dependencies, Build Order
    """
    graph = {i: [] for i in range(num_nodes)}
    in_degree = [0] * num_nodes

    for src, dst in edges:
        graph[src].append(dst)
        in_degree[dst] += 1

    # Start with all nodes that have no incoming edges
    queue = deque(i for i in range(num_nodes) if in_degree[i] == 0)
    order = []

    while queue:
        node = queue.popleft()
        order.append(node)
        for neighbor in graph[node]:
            in_degree[neighbor] -= 1
            if in_degree[neighbor] == 0:
                queue.append(neighbor)

    return order if len(order) == num_nodes else []  # [] means cycle exists
```

## Dijkstra's Algorithm -- Shortest Path in Weighted Graph
```python
import heapq

def dijkstra(graph: dict, start: int) -> dict:
    """
    Dijkstra's single-source shortest path.
    graph: {node: [(neighbor, weight), ...]}
    Returns: {node: shortest_distance_from_start}

    Time: O((V + E) log V) with binary heap
    Space: O(V)

    Requirement: ALL edge weights must be non-negative.
    Use Bellman-Ford if negative edges are possible.
    """
    dist = {node: float('inf') for node in graph}
    dist[start] = 0
    # Min-heap: (distance, node)
    heap = [(0, start)]

    while heap:
        d, u = heapq.heappop(heap)

        # Skip if we've already found a better path
        if d > dist[u]:
            continue

        for v, weight in graph.get(u, []):
            new_dist = dist[u] + weight
            if new_dist < dist[v]:
                dist[v] = new_dist
                heapq.heappush(heap, (new_dist, v))

    return dist

# For path reconstruction, track predecessors:
def dijkstra_with_path(graph: dict, start: int, end: int) -> tuple[int, list]:
    dist = {node: float('inf') for node in graph}
    dist[start] = 0
    prev = {node: None for node in graph}
    heap = [(0, start)]

    while heap:
        d, u = heapq.heappop(heap)
        if d > dist[u]:
            continue
        if u == end:
            break
        for v, w in graph.get(u, []):
            if dist[u] + w < dist[v]:
                dist[v] = dist[u] + w
                prev[v] = u
                heapq.heappush(heap, (dist[v], v))

    # Reconstruct path
    path, node = [], end
    while node is not None:
        path.append(node)
        node = prev[node]
    return dist[end], path[::-1]
```

## Union-Find (Disjoint Set Union) -- Fully Optimized
```python
class UnionFind:
    """
    Union-Find with path compression + union by rank.
    Nearly O(1) amortized per operation (O(alpha(n)), alpha = inverse Ackermann).

    Use cases:
    - Cycle detection in undirected graphs
    - Connected components (Kruskal's MST)
    - Grid connectivity (number of islands variant)
    - Dynamic connectivity queries
    """
    def __init__(self, n: int):
        self.parent = list(range(n))
        self.rank   = [0] * n
        self.count  = n  # number of connected components

    def find(self, x: int) -> int:
        """Find root with PATH COMPRESSION, makes future finds O(1)."""
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])  # path compression
        return self.parent[x]

    def union(self, x: int, y: int) -> bool:
        """
        Union by RANK, attach smaller tree under root of taller tree.
        Returns True if x and y were in different components (edge added).
        Returns False if they were already connected (cycle detected).
        """
        rx, ry = self.find(x), self.find(y)
        if rx == ry:
            return False  # Already connected -> adding edge would create cycle

        # Attach smaller rank tree under larger rank
        if self.rank[rx] < self.rank[ry]:
            rx, ry = ry, rx
        self.parent[ry] = rx
        if self.rank[rx] == self.rank[ry]:
            self.rank[rx] += 1

        self.count -= 1
        return True

    def connected(self, x: int, y: int) -> bool:
        return self.find(x) == self.find(y)
```

## Graph Algorithm Summary -- Complexity & Use Cases
| Algorithm | Time | Space | Use When | Key Constraint |
|-----------|------|-------|----------|----------------|
| **BFS** | O(V + E) | O(V) | Shortest path in UNWEIGHTED graph, level-order, min hops | Edge weights must all be equal (or 1) |
| **DFS** | O(V + E) | O(V) | Connected components, cycle detection, topological sort, path finding | None |
| **Topological Sort (Kahn)** | O(V + E) | O(V) | Task dependencies, course prerequisites, build order | Graph must be a DAG |
| **Dijkstra** | O((V+E) log V) | O(V) | Shortest path in WEIGHTED graph | ALL edge weights >= 0 |
| **Bellman-Ford** | O(VE) | O(V) | Shortest path with NEGATIVE edges, detect negative cycles | No negative weight cycles |
| **Floyd-Warshall** | O(V^3) | O(V^2) | All-pairs shortest path | Small graphs (V < 1000) |
| **Union-Find** | O(alpha(V)) per op | O(V) | Connected components, cycle in undirected, Kruskal's MST | Undirected only |
| **Multi-source BFS** | O(V + E) | O(V) | Distance from MULTIPLE sources simultaneously (01-matrix, rotting oranges) | Unweighted |
| **0-1 BFS** | O(V + E) | O(V) | Weighted graph with ONLY weights 0 and 1 | Edge weights in {0, 1} |

## Interview Questions
1. **BFS vs DFS** -- when does each give the wrong answer if misapplied?
2. **Dijkstra** -- implement it; what happens if there are negative edge weights?

## Follow-Up Variations
- How do you detect a cycle in a directed vs undirected graph?
- When would you use Union-Find over DFS for connected components?
- How do you handle graphs with negative weights (Bellman-Ford)?
- What is the difference between 0-1 BFS and Dijkstra?

Source: [Graph Algorithms: BFS, DFS & Topological Sort (CalibreOS)](https://www.calibreos.com/learn/dsa-graphs)
