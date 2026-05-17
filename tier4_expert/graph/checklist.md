# Graph Algorithms -- Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Problem Recognition (1-2 min)
- [ ] Identify if the graph is explicit (given nodes/edges) or implicit (grid, word transformation, state-space)
- [ ] Determine graph type:
  - [ ] Directed vs undirected
  - [ ] Weighted vs unweighted
  - [ ] Cyclic vs acyclic (DAG)
- [ ] Identify what the problem is asking:
  - [ ] Shortest path / minimum distance
  - [ ] Connected components / reachability
  - [ ] Cycle detection
  - [ ] Topological ordering / dependency resolution
  - [ ] MST (minimum spanning tree)

## Phase 2: Algorithm Selection (1-2 min)
- [ ] Match the problem to the right algorithm:
  - [ ] **BFS**: shortest path in unweighted graph, level-order, min hops
  - [ ] **DFS**: connected components, cycle detection, path finding
  - [ ] **Topological Sort (Kahn)**: task dependencies, course prerequisites, build order
  - [ ] **Dijkstra**: shortest path in weighted graph with non-negative edges
  - [ ] **Bellman-Ford**: shortest path with possible negative edges
  - [ ] **Union-Find**: dynamic connectivity, cycle in undirected graph, Kruskal's MST
  - [ ] **Multi-source BFS**: distance from multiple sources (01-matrix, rotting oranges)
  - [ ] **0-1 BFS**: weighted graph with only weights 0 and 1
- [ ] State time and space complexity of your chosen algorithm
- [ ] Confirm the graph constraints allow your algorithm (e.g., Dijkstra requires non-negative weights)

## Phase 3: Build the Graph (2-3 min)
- [ ] Choose representation:
  - [ ] Adjacency list (default for most problems): `graph = {node: [neighbors]}`
  - [ ] Adjacency matrix (dense graphs, Floyd-Warshall)
  - [ ] Edge list (Kruskal's, Union-Find): `edges = [(u, v, w), ...]`
- [ ] Build the graph from input:
  - [ ] For grid problems: use (row, col) tuples as nodes, DIRS = [(0,1),(0,-1),(1,0),(-1,0)]
  - [ ] For weighted graphs: store `(neighbor, weight)` pairs
  - [ ] For directed: add edge in one direction only
  - [ ] For undirected: add edges in both directions
- [ ] Handle edge cases: empty graph, single node, disconnected components

## Phase 4: Implement Traversal (5-8 min)
- [ ] For BFS:
  - [ ] Initialize `visited = {start}`, `queue = deque([(start, 0)])`
  - [ ] Pop from left, process node, enqueue unvisited neighbors
  - [ ] Track distance/level if shortest path needed
- [ ] For DFS:
  - [ ] Iterative: `visited = set()`, `stack = [start]`, pop and push neighbors
  - [ ] Recursive: define `dfs(node)` with visited set, recurse on unvisited neighbors
- [ ] For Topological Sort (Kahn):
  - [ ] Build graph and in-degree array
  - [ ] Enqueue all nodes with in-degree 0
  - [ ] Process queue, decrement in-degree of neighbors, enqueue when in-degree hits 0
  - [ ] If `len(order) != num_nodes`, a cycle exists
- [ ] For Dijkstra:
  - [ ] Initialize `dist = {node: inf}`, `dist[start] = 0`, min-heap `[(0, start)]`
  - [ ] Pop min-distance node, skip if stale (`d > dist[u]`)
  - [ ] Relax edges: if `dist[u] + w < dist[v]`, update and push to heap
- [ ] For Union-Find:
  - [ ] Initialize `parent = list(range(n))`, `rank = [0] * n`
  - [ ] `find(x)` with path compression: recursively set `parent[x] = find(parent[x])`
  - [ ] `union(x, y)` by rank: attach smaller tree under taller, return False if already connected (cycle)

## Phase 5: Verify & Optimize (2-3 min)
- [ ] Walk through the algorithm on a small example (3-5 nodes)
- [ ] Check boundary conditions:
  - [ ] Start == target
  - [ ] Target unreachable (return -1 or empty)
  - [ ] Single node graph
  - [ ] Disconnected components
- [ ] Verify visited set is used correctly to avoid infinite loops
- [ ] Confirm time complexity matches the chosen algorithm
- [ ] Check for common mistakes:
  - [ ] Using DFS for shortest path in unweighted graph (wrong -- use BFS)
  - [ ] Using Dijkstra with negative weights (wrong -- use Bellman-Ford)
  - [ ] Forgetting to check cycle in topological sort
  - [ ] Not handling directed vs undirected edges correctly

## Phase 6: Wrap-Up (1-2 min)
- [ ] State the final time and space complexity
- [ ] Mention alternative approaches and trade-offs
- [ ] Note if there are follow-up variations (e.g., weighted version, multiple sources)

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:

Source: [Graph Algorithms: BFS, DFS & Topological Sort (CalibreOS)](https://www.calibreos.com/learn/dsa-graphs)
