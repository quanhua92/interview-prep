# Matrix Traversal — Flashcards

4 cards. Drill: read the trigger, recall the pattern + move, then click to verify.

<details><summary><b>n x n matrix — rotate it 90° clockwise in place</b></summary>

Pattern: Matrix Traversal &nbsp;|&nbsp; O(n^2)
Move: Transpose the matrix (swap across the main diagonal), then reverse each row to reflect horizontally.
File: [coding_rotate_image.md](../../tiers/expert/coding_rotate_image.md)
</details>

<details><summary><b>m x n matrix — return all elements in spiral order (outside-in)</b></summary>

Pattern: Matrix Traversal &nbsp;|&nbsp; O(m * n)
Move: Maintain top/bottom/left/right boundaries; peel one layer per loop, walking the four edges, then shrink the boundaries inward.
File: [coding_spiral_matrix.md](../../tiers/expert/coding_spiral_matrix.md)
</details>

<details><summary><b>m x n matrix — return elements in diagonal zigzag order</b></summary>

Pattern: Matrix Traversal &nbsp;|&nbsp; O(m * n)
Move: Group cells by r + c = const; even sums traverse up-right, odd sums traverse down-left, flipping direction at each boundary.
File: [coding_diagonal_traverse.md](../../tiers/expert/coding_diagonal_traverse.md)
</details>

<details><summary><b>Binary matrix — for each cell return the distance to the nearest 0</b></summary>

Pattern: Matrix Traversal &nbsp;|&nbsp; O(m * n)
Move: Multi-source BFS from every 0 cell, relaxing each neighbor's distance as it is dequeued; equivalently a two-pass 2D DP from opposite corners.
File: [coding_01_matrix.md](../../tiers/expert/coding_01_matrix.md)
</details>

---

[Back to Flashcard Index](../README.md) | [Expert Tier README](../../tiers/expert/README.md)
