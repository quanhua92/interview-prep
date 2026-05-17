# Union-Find (Disjoint Set Union) — Discussion & Deep Dive

## One-Liner
Track connected components efficiently using two operations: `find` (which set does an element belong to?) and `union` (merge two sets). With path compression and union by rank, each operation is O(a(n)) — effectively O(1).

Source: [Union-Find (DSU): Dynamic Connectivity in Near-Constant Time (CalibreOS)](https://www.calibreos.com/learn/dsa-union-find)

---

## What Union-Find Solves — Dynamic Connectivity

Union-Find answers one question efficiently: **are nodes X and Y in the same connected component?** It supports two core operations:

- `union(x, y)` — merge the components containing x and y
- `find(x)` — return the root representative of x's component
- `connected(x, y)` — returns `find(x) == find(y)`

The key word is **dynamic**: union-find answers connectivity queries as edges are added incrementally, without rebuilding the data structure. This is where union-find beats BFS/DFS — when the graph is constructed edge-by-edge and you need to answer connectivity queries between edge additions.

### Performance Tiers
| Implementation | find() | union() |
|---|---|---|
| Naive (no optimizations) | O(n) | O(n) |
| Path compression only | O(a(n)) amortized | O(a(n)) amortized |
| Union by rank only | O(log n) | O(log n) |
| **Both optimizations** | **O(a(n)) amortized** | **O(a(n)) amortized** |

For all practical n (including n = 10^80, the number of atoms in the observable universe), a(n) <= 4. Effectively O(1) amortized.

---

## When to Use Union-Find — Decision Framework

1. **Check if the graph is undirected and dynamic.** Union-Find only models undirected connectivity. For directed graphs, use DFS with coloring. Dynamic means edges are added incrementally — if you have all edges upfront and need one-time connectivity, simple BFS/DFS is simpler.
2. **Identify what gets "unioned".** The "nodes" don't have to be integers. For strings (emails, names), build an `email_to_id` mapping first. For grid cells (row, col), convert to linear index: `r * cols + c`. For variable names, assign monotonic integer IDs.
3. **Initialize with the right size.** If nodes are 1-indexed (common in LeetCode), initialize `UnionFind(n+1)` to avoid index-0 confusion. If 0-indexed, `UnionFind(n)`. Set `num_components = n` initially, decrement by 1 per successful union.
4. **Always implement both optimizations.** Path compression: one line in `find()`. Union by rank: compare ranks, attach smaller under larger. Without both: O(log n) or worse instead of O(a(n)).
5. **Use union's return value for cycle detection.** `union(u, v)` returns `False` when u and v are already connected. This is cycle detection for free — the first edge where union returns False is the redundant edge.

---

## The Two Optimizations — Both Required for O(a(n))

### Path Compression (on find)
After finding the root, update every node on the traversal path to point directly to the root. One recursive call does this automatically:
```python
if parent[x] != x:
    parent[x] = find(parent[x])
```
Without this: O(log n) per find even with union by rank. With both: O(a(n)).

### Union by Rank (on union)
Always attach the shorter tree under the taller tree's root. Track the approximate height (rank) of each root. When two trees have the same rank, one becomes the child and the child's root rank increments by 1.

Without this (always attach y under x): degenerate chains can form even with path compression alone in adversarial cases.

**Memory trick:** path compression is one line in find. Union by rank is one check in union. If you implement either but not both, you're leaving performance on the table. Interviewers expect both.

---

## Key Applications

### Connected Components (LC 323)
Given n nodes and a list of edges, count distinct components. Initialize `UnionFind(n)`, union each edge, return `uf.num_components`. Time: O(n + E * a(n)).

### Cycle Detection in Undirected Graphs (LC 684, 261)
Union edges one by one. If `union(u, v)` returns False, u and v were already in the same component — adding this edge creates a cycle. The "redundant connection" is the first edge where union returns False.

**Why DSU beats DFS for cycle detection when the graph is built edge-by-edge:** DFS must traverse the entire graph, O(V+E) per query. DSU's union returns the cycle indicator immediately, O(a(n)) per edge. If you're adding 10^6 edges and checking for cycles after each one, DSU is orders of magnitude faster.

**The equivalence:** Both DFS and DSU correctly detect cycles. DSU is not more "correct", it's more efficient for incremental edge insertion. For a static graph where you just need to know if a cycle exists, DFS is simpler. For dynamic graphs where you add edges and query connectivity alternately, DSU is the right tool.

### Accounts Merge (LC 721) — DSU with Non-Integer Keys
This is the problem that separates candidates who memorize DSU from those who understand it.

**Algorithm:**
1. Assign an integer ID to each unique email (use `email_to_id` dict)
2. Store `email_to_name` (map email -> account name)
3. Initialize `UnionFind(number of unique emails)`
4. For each account, union all emails together (union first email with each subsequent email)
5. After all unions: group emails by their root ID
6. For each group, look up the account name, sort the emails, prepend the name

**Key insight:** You only need to union each email to the FIRST email in the same account. You don't need to union all pairs. If account has emails [A, B, C], `union(A,B)` and `union(A,C)` is sufficient — union is transitive.

### Valid Tree Check (LC 261)
Tree conditions: (1) exactly n-1 edges, (2) no cycles = fully connected.

---

## Classic Union-Find Problems (8 Must-Know)

| LC# | Title | What Gets Unioned | Special Consideration | Difficulty |
|-----|-------|-------------------|----------------------|------------|
| 547 | Number of Provinces | Cities by direct connection | Count remaining roots after all unions | Medium |
| 323 | Connected Components | Nodes by edges | num_components starts at n, decrements per union | Medium |
| 684 | Redundant Connection | Nodes by edges (undirected) | First edge where union returns False is the answer | Medium |
| 721 | Accounts Merge | Emails within same account | Email-to-int mapping needed; group by find root | Medium |
| 200 | Number of Islands (DSU) | Land cells by adjacency | DSU wins when islands grow dynamically (adding cells) | Medium |
| 399 | Evaluate Division | Variables in same equation group | Weight edges with division ratios, weighted DSU | Medium |
| 1202 | Smallest String With Swaps | Indices connected by swap pairs | Group chars by component, sort each group | Medium |
| 1584 | Min Cost to Connect All Points | Points by Kruskal's MST | Sort all edges by distance, union until n-1 merges | Medium |

---

## Common Union-Find Mistakes in Interviews

1. **Implementing find without path compression.** Without path compression, repeated find operations on deep trees cost O(n) per call. A loop of n union + find operations becomes O(n^2). Always add the path-compression line.

2. **Not using union by rank.** Without rank, union always attaches the second tree under the first, regardless of height. Adversarial inputs can create a chain of length n even with path compression if union order is controlled. Both optimizations are needed for O(a(n)) amortized guarantee.

3. **Using 1-indexed nodes with 0-indexed UnionFind (or vice versa).** LC problems mix 0-indexed and 1-indexed node numbering. For a problem with nodes 1 to n, initialize `UnionFind(n+1)` and use node values directly as indices.

4. **Trying to use DSU for directed graphs.** Union-Find only models undirected connectivity. For directed graphs (detecting cycles, topological sort), use DFS with coloring. DSU's `union(x, y)` is symmetric — it cannot represent a one-way edge.

5. **Forgetting to decrement num_components in union.** num_components is the most useful derived field but must be explicitly maintained. Every successful union (where union returns True) merges two components — decrement by 1.

---

## Interview Questions

### Q1: What is a(n) and why can we say Union-Find is "effectively O(1)" per operation?
The inverse Ackermann function a(n) grows so slowly that for any practical input size (even n = 10^80), a(n) <= 4. This means each find/union operation takes at most ~4 steps regardless of how large n is, making it effectively constant time.

### Q2: DSU vs BFS/DFS for connected components — when does each win?
- **DSU wins** when edges are added dynamically and you need to query connectivity between additions (incremental edge insertion)
- **BFS/DFS wins** when you have all edges upfront and need one-time connectivity (static graph, simpler code)
- They are equally correct; the difference is efficiency in the dynamic case

### Q3: How does Kruskal's MST algorithm use Union-Find?
Sort all edges by weight. For each edge in ascending order, if `union(u, v)` returns True (nodes were in different components), include this edge in the MST. Stop after n-1 edges. Union-Find prevents cycles efficiently.

### Q4: What is weighted Union-Find and when is it used?
Weighted DSU tracks additional information per edge (e.g., division ratios in Evaluate Division, LC 399). During find, the weights are accumulated along the path. This allows answering queries about relationships between nodes, not just connectivity.
