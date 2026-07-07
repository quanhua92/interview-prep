# Union Find — Flashcards

3 cards. Drill: read the trigger, recall the pattern + move, then click to verify.

<details><summary><b>n nodes and a list of undirected edges — return the number of connected components</b></summary>

Pattern: Union Find &nbsp;|&nbsp; O(E * α(V))
Move: DSU with a parent[] array; for each edge call union(u, v); the answer is the count of distinct roots (or decrement a counter on each successful union).
File: [coding_connected_components.md](../../tiers/expert/coding_connected_components.md)
</details>

<details><summary><b>Tree edges plus one extra edge that closes a cycle — return the edge whose removal restores a tree</b></summary>

Pattern: Union Find &nbsp;|&nbsp; O(E * α(V))
Move: Iterate edges through DSU; the first edge whose two endpoints already share a root is the redundant cycle-closer — return it.
File: [coding_redundant_connection.md](../../tiers/expert/coding_redundant_connection.md)
</details>

<details><summary><b>List of "a==b" / "a!=b" equations — can they all be satisfied simultaneously?</b></summary>

Pattern: Union Find &nbsp;|&nbsp; O(E * α(V))
Move: Process every "==" equation first, unioning the variables; then verify each "!=" pair has different roots under find().
File: [coding_satisfiability_equations.md](../../tiers/expert/coding_satisfiability_equations.md)
</details>

---

[Back to Flashcard Index](../README.md) | [Expert Tier README](../../tiers/expert/README.md)
