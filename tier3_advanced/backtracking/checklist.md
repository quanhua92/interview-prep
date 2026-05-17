# Backtracking — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

Source: [Backtracking: Permutations, Combinations, Subsets & Word Search (CalibreOS)](https://www.calibreos.com/learn/dsa-backtracking)

## Phase 1: Recognize & Set Up (2-3 min)
- [ ] Identify that the problem requires backtracking:
  - [ ] Does it ask to "find all", "generate all", "enumerate all"?
  - [ ] Does it involve combinations, permutations, subsets, or constraint satisfaction?
  - [ ] Is it an arrangement problem like N-Queens, Sudoku, or Word Search?
- [ ] Classify the problem type:
  - [ ] Subsets: need all possible subsets/power set
  - [ ] Permutations: need all orderings of elements
  - [ ] Combinations: choose k from n (with or without reuse)
  - [ ] Constraint satisfaction: N-Queens, Sudoku, Word Search
- [ ] State the recursion tree structure:
  - [ ] What does each node represent? (a partial solution)
  - [ ] What does each edge represent? (one new choice)
  - [ ] What is the base case? (complete solution or dead end)
- [ ] Estimate complexity from the tree:
  - [ ] Subsets: O(n * 2^n) time, O(n) space
  - [ ] Permutations: O(n * n!) time, O(n) space
  - [ ] Combinations: O(C(n,k) * k) time
  - [ ] N-Queens: O(n!) time

## Phase 2: Write the Template (3-5 min)
- [ ] Define state parameters:
  - [ ] `current` (list): the partial solution being built
  - [ ] `start` (int): starting index for combination/subset problems (prevents revisiting)
  - [ ] `visited` or `remaining` (set): for permutation problems (tracks what's left)
  - [ ] Additional state as needed (e.g., `remaining` sum, `row` for N-Queens)
- [ ] Write the base case:
  - [ ] Check if current solution is complete (correct length, constraint met)
  - [ ] Add a **COPY** to results: `result.append(current[:])` — never `result.append(current)`
- [ ] Write the iteration loop:
  - [ ] `for i in range(start, len(candidates)):` for combinations/subsets
  - [ ] `for num in list(remaining):` for permutations
  - [ ] `for col in range(n):` for N-Queens
  - [ ] `for direction in [(0,1),(0,-1),(1,0),(-1,0)]:` for Word Search
- [ ] Add the choose-recurse-undo pattern inside the loop:
  - [ ] **Choose**: append/add the choice to current state
  - [ ] **Recurse**: call backtrack with updated state
  - [ ] **Undo**: pop/remove the choice from current state

## Phase 3: Add Pruning (3-5 min, interviewer-directed)
- [ ] Identify pruning opportunities:
  - [ ] Combination Sum: if `candidates[i] > remaining: break` (requires sorted input)
  - [ ] N-Queens: if queen would be attacked (check cols, diag1, diag2 sets)
  - [ ] Word Search: if out of bounds or character doesn't match
  - [ ] General: if partial solution violates any constraint, return early
- [ ] Handle duplicates (if input has repeated elements):
  - [ ] Sort the input first (enables both duplicate skip and early termination)
  - [ ] Add: `if i > start and candidates[i] == candidates[i-1]: continue`
  - [ ] Explain: this skips duplicates at the same tree level without skipping within a branch
- [ ] Verify pruning is correct:
  - [ ] Does pruning happen BEFORE the recursive call?
  - [ ] Does the pruning condition correctly identify invalid paths?
  - [ ] Does early termination (break vs continue) make sense for sorted inputs?

## Phase 4: Walk Through & Verify (2-3 min)
- [ ] Trace through a small example (e.g., subsets of [1,2,3]):
  - [ ] Draw the first 2-3 levels of the recursion tree
  - [ ] Verify each branch produces the expected result
  - [ ] Confirm the undo step restores state correctly
- [ ] Check for the 5 classic mistakes:
  - [ ] Copy on append: `current[:]` not `current`
  - [ ] Undo step present: `current.pop()` after every recursive call
  - [ ] Correct start index: `i+1` (no reuse) vs `i` (reuse allowed)
  - [ ] Sorted input for duplicate handling
  - [ ] Pruning condition present and correct
- [ ] State final time and space complexity:
  - [ ] Count nodes in the recursion tree
  - [ ] Multiply by cost per node (usually O(n) for copying)
  - [ ] Space: recursion depth O(n) + result storage

## Phase 5: Wrap-Up (1-2 min)
- [ ] Summarize your approach in 1-2 sentences
- [ ] Explain the pruning strategy and what it saves
- [ ] Mention how this relates to other patterns:
  - [ ] DP = backtracking + memoization (when subproblems overlap)
  - [ ] DFS on graphs = backtracking with a visited set
  - [ ] Branch and bound = backtracking with optimistic bounds
- [ ] Ask the interviewer if they have questions

## Interview Questions to Practice
- [ ] Q1: Generate all subsets of [1,2,3]. Extend to handle duplicates in [1,1,2].
- [ ] Q2: Generate all valid parentheses strings of length 2n (n pairs).
- [ ] Q3: Word search — given a 2D grid, find if a word exists as a path of adjacent cells.

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
