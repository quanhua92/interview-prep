# Matrix Traversal

## Core Idea
Traverse a 2D matrix in non-standard orders: spiral (clockwise/counter-clockwise), diagonal, zigzag, or by rotating/transposing the matrix. The key is to carefully manage boundary conditions.

## When to Recognize
- "Spiral order" / "spiral matrix"
- "Rotate matrix" / "rotate image"
- "Diagonal traversal"
- "Zigzag traversal"
- "Search in a rotated sorted matrix"

## Complexity
- **Time:** O(m * n) — visit each element once
- **Space:** O(1) extra (in-place) or O(m * n) for output

## Key Variants
1. **Spiral order traversal** — use four boundary pointers (top, bottom, left, right)
2. **Rotate image 90 degrees** — transpose then reverse rows
3. **Diagonal traversal** — iterate by sum of indices (i + j = constant per diagonal)

## Problems
- P054: Spiral Matrix
- P048: Rotate Image
