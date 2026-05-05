# Graph

## Core Idea
Represent relationships as nodes (vertices) and edges. Traverse the graph using BFS (queue) or DFS (stack/recursion), and detect cycles using topological sort (for DAGs) or visited-state tracking (for general graphs).

## When to Recognize
- "Course schedule" / "prerequisites"
- "Clone graph"
- "Graph traversal" / "BFS" / "DFS"
- "Topological sort" / "dependency resolution"
- "Number of islands"
- "Word ladder" / "shortest path in unweighted graph"

## Complexity
- **Time:** O(V + E) for standard BFS/DFS traversal
- **Space:** O(V) for adjacency list and visited set

## Key Variants
1. **Clone graph (BFS)** — copy a graph using BFS with a visited map
2. **DFS graph traversal** — recursive or iterative DFS with cycle detection
3. **Topological sort (Kahn's algorithm)** — BFS-based, uses in-degree counting

## Problems
- P207: Course Schedule
- P210: Course Schedule II
- P997: Find the Town Judge
