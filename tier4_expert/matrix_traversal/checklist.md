# Matrix Traversal — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Problem Classification (1-2 min)
- [ ] Identify the pattern family:
  - [ ] Traversal order problem (spiral, rotate, diagonal) — use direction array + boundary simulation
  - [ ] Connectivity/spread problem (islands, flood fill, rotting) — use DFS for components, BFS for spread/distance
- [ ] Identify signal words: "island," "connected," "flood," "rotting," "spread," "spiral," "diagonal," "nearest"
- [ ] Determine connectivity type:
  - [ ] 4-directional (up/down/left/right)
  - [ ] 8-directional (includes diagonals)
- [ ] State complexity target: O(m*n) time for all standard matrix problems

## Phase 2: Setup & Boilerplate (2-3 min)
- [ ] Write direction array at the top:
  - [ ] 4-dir: `DIRS = [(0,1),(0,-1),(1,0),(-1,0)]`
  - [ ] 8-dir: add `(1,1),(1,-1),(-1,1),(-1,-1)`
- [ ] Write bounds check helper or inline: `0 <= nr < rows and 0 <= nc < cols`
- [ ] Decide on visited marking strategy:
  - [ ] In-place marking (modify grid, saves O(m*n) space) — state this tradeoff out loud
  - [ ] Separate visited array (preserves input, costs O(m*n) space)

## Phase 3: Core Algorithm (5-8 min)

### If DFS (connected components):
- [ ] Iterate over all cells
- [ ] On unvisited target cell: start DFS, increment counter
- [ ] DFS: mark cell visited, recurse on all valid neighbors via direction array
- [ ] Return component count (islands) or accumulated value
- [ ] Mention recursion depth risk: for large grids, propose iterative DFS with explicit stack

### If BFS (spread / shortest distance):
- [ ] Determine source type:
  - [ ] Single source: enqueue one cell
  - [ ] Multi-source: enqueue ALL source cells at time/level 0
- [ ] BFS loop: popleft, process all valid unvisited neighbors, enqueue with level+1
- [ ] Track level/time as you go
- [ ] After BFS: check for unreachable cells (e.g., remaining fresh oranges → return -1)

### If Spiral (boundary shrinkage):
- [ ] Initialize top=0, bottom=m-1, left=0, right=n-1
- [ ] Loop while top <= bottom AND left <= right:
  - [ ] Left to right along top row → top++
  - [ ] Top to bottom along right col → right--
  - [ ] Right to left along bottom row (if top <= bottom) → bottom--
  - [ ] Bottom to top along left col (if left <= right) → left++
- [ ] Edge case guards on inner loops for single row/column matrices

## Phase 4: Verification (2-3 min)
- [ ] Trace through a small example (3x3 or 4x4 matrix)
- [ ] Verify boundary cases:
  - [ ] 1x1 matrix
  - [ ] Single row (1xn)
  - [ ] Single column (mx1)
  - [ ] All same value (all land, all water, all rotten)
- [ ] Check for off-by-one errors in spiral traversal
- [ ] Confirm unreachable-cell check is in place for spread problems
- [ ] State final time and space complexity out loud

## Phase 5: Communication Signals (throughout)
- [ ] State approach before coding: "This is a connected components problem, I'll use DFS..."
- [ ] Mention direction array idiom as a conscious choice: "I'll iterate through the 4 neighbors"
- [ ] State bounds check rationale: "This handles all boundary cases without separate conditions"
- [ ] Discuss in-place vs visited array tradeoff
- [ ] For spread problems: explain why BFS (not DFS) gives minimum distance
- [ ] For multi-source: explain why all sources must start at level 0

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:

Source: [Matrix Patterns: Spiral Traversal, Island Problems & Multi-Source BFS (CalibreOS)](https://www.calibreos.com/learn/dsa-matrix-patterns)
