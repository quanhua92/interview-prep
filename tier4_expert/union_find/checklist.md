# Union-Find (Disjoint Set Union) — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

Source: [Union-Find (DSU): Dynamic Connectivity in Near-Constant Time (CalibreOS)](https://www.calibreos.com/learn/dsa-union-find)

---

## Phase 1: Recognize & Set Up (2-3 min)
- [ ] Identify the problem type from keywords:
  - [ ] "Connected components" / "number of provinces"
  - [ ] "Redundant connections" / "cycle detection in undirected graph"
  - [ ] "Accounts merge" / "group related items"
  - [ ] "Minimum spanning tree" (Kruskal's algorithm)
  - [ ] "Dynamic connectivity" / "merge groups incrementally"
- [ ] Confirm the graph is undirected (DSU does NOT work for directed graphs)
- [ ] Determine if edges are dynamic (added incrementally) — if yes, DSU is preferred over BFS/DFS
- [ ] Identify what gets "unioned" (may not be integers):
  - [ ] Integers (nodes, indices) — use directly
  - [ ] Strings (emails, names) — build a mapping to integer IDs first
  - [ ] Grid cells (row, col) — convert to linear index: `r * cols + c`
- [ ] Check indexing: nodes 1-indexed -> `UnionFind(n+1)`, 0-indexed -> `UnionFind(n)`

## Phase 2: Implement Union-Find (3-5 min)
- [ ] Write the class skeleton: `__init__`, `find`, `union`, optionally `connected`
- [ ] In `__init__`: initialize `parent = list(range(n))` and `rank = [0] * n`
- [ ] In `find` — implement **path compression**:
  - [ ] `if parent[x] != x: parent[x] = find(parent[x])`
  - [ ] This single recursive line flattens the tree
- [ ] In `union` — implement **union by rank**:
  - [ ] Find roots of both: `rx, ry = find(x), find(y)`
  - [ ] If same root, return False (already connected / cycle detected)
  - [ ] Attach smaller-rank tree under larger-rank tree
  - [ ] If ranks equal, increment rank of new root
  - [ ] Return True (merge happened)
- [ ] If needed, add derived fields:
  - [ ] `num_components`: starts at n, decrement by 1 on each successful union
  - [ ] `size`: track component sizes (union by size instead of rank)
- [ ] Verify: both path compression AND union by rank are present (needed for O(a(n)))
- [ ] Note: for n > 10^4, consider iterative find to avoid recursion limit

## Phase 3: Apply to the Problem (3-5 min)
- [ ] Initialize UnionFind with correct size
- [ ] Process edges/relationships:
  - [ ] For connected components: union each edge, return `num_components`
  - [ ] For cycle detection: return first edge where `union()` returns False
  - [ ] For accounts merge: map strings to IDs, union emails in same account, group by root
  - [ ] For MST (Kruskal): sort edges by weight, union until n-1 successful merges
  - [ ] For grid problems: convert (r,c) to linear index, union adjacent matching cells
- [ ] Extract the answer from UnionFind state

## Phase 4: Verify & Edge Cases (2-3 min)
- [ ] Check indexing consistency (no off-by-one errors)
- [ ] Handle isolated nodes (nodes with no edges — they count as separate components)
- [ ] Handle duplicate edges (union returns False, no issue)
- [ ] Verify time complexity: O((n + E) * a(n)) which is effectively O(n + E)
- [ ] Verify space complexity: O(n) for parent and rank arrays
- [ ] Confirm you didn't accidentally use DSU for a directed graph problem

## Phase 5: Discuss Trade-offs (2-3 min)
- [ ] Explain why DSU over BFS/DFS for this problem:
  - [ ] DSU: O(a(n)) per edge, answers dynamic connectivity queries incrementally
  - [ ] BFS/DFS: O(V+E) per query, better for static one-time connectivity
- [ ] Explain the two optimizations and why both are needed:
  - [ ] Path compression alone: adversarial inputs can still create tall trees
  - [ ] Union by rank alone: O(log n) per find without compression
  - [ ] Both together: O(a(n)) amortized, effectively O(1)
- [ ] Discuss the inverse Ackermann function: a(n) <= 4 for all practical n
- [ ] Mention alternatives if asked: BFS/DFS for static graphs, DFS with coloring for directed graphs

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
