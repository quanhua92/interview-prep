# Union-Find (Disjoint Set Union)

## Core Idea
Track connected components efficiently using two operations: `find` (determine which set an element belongs to) and `union` (merge two sets). Path compression flattens the tree on every `find`, and union by rank attaches the shorter tree under the taller one.

## When to Recognize
- "Connected components" / "number of provinces"
- "Accounts merge"
- "Redundant connections" / "cycle detection in undirected graph"
- "Minimum spanning tree" (Kruskal's algorithm)
- "Dynamic connectivity" problems

## Complexity
- **Time:** O(alpha(n)) per operation (inverse Ackermann, effectively O(1))
- **Space:** O(n) for parent and rank arrays

## Key Variants
1. **Union-Find with path compression + union by rank** — standard, most common
2. **Union-Find with size tracking** — when you need component sizes
3. **Union-Find with component counting** — when you need to track the number of components

## Problems
- P323: Number of Connected Components in an Undirected Graph
- P684: Redundant Connection
- P990: Satisfiability of Equality Equations
