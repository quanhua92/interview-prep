# Backtracking — Discussion

Source: [Backtracking: Permutations, Combinations, Subsets & Word Search (CalibreOS)](https://www.calibreos.com/learn/dsa-backtracking)

## One-Liner
Systematically explore all possibilities by building candidates incrementally and pruning paths that cannot lead to a valid solution.

## The Backtracking Mental Model
Backtracking is a structured form of brute force. You build a solution step-by-step, and at each step you try all valid choices. If a partial solution can never lead to a valid complete solution, you prune it, undo the last choice, and try the next one. This "try, fail, undo" loop gives backtracking its name.

### The Recursion Tree Visualization
Every backtracking problem maps to a tree where:
- Each **node** is a partial solution (choices made so far)
- Each **edge** is one new choice
- **Leaves** are either complete valid solutions or dead ends (pruned)
- The algorithm does a **DFS** over this tree

### When to Recognize Backtracking
The problem asks you to "find all" or "generate all" combinations/permutations/subsets, or "find one valid arrangement" (N-Queens, Sudoku). Key signals: *enumerate all*, *generate all*, *find all valid*, *count arrangements*.

### The Complexity Reality
Backtracking problems are inherently exponential in the worst case (2^n for subsets, n! for permutations). The goal isn't to beat exponential — it's to prune the search tree aggressively so that only the relevant branch of the exponential space is explored.

## What Interviewers Evaluate

| Score | Description |
|-------|-------------|
| **6/10** | Recognizes backtracking is needed. Gets a working but unpruned solution. Code is messy and hard to follow. |
| **8/10** | Uses a clean recursive structure. Adds the key pruning condition. Handles duplicates correctly in combination/subset problems. Explains the recursion tree. |
| **10/10** | Writes a clean, general template and adapts it to the problem. Explains why the time complexity is O(n x n!) for permutations or O(2^n) for subsets. Identifies the exact pruning condition and explains what portion of the search tree it eliminates. Handles the "sorted input + skip duplicates" trick for problems with repeated elements without being prompted. |

## The Universal Backtracking Template

### Step 1: Define the State
Each recursive call represents: "I have made certain choices (path/current), and I need to continue building from position `start` using `candidates` choices."
State parameters: `current` partial solution, `start` index (for combination problems, prevents re-use of earlier elements), and sometimes a `visited` set (for permutations).

### Step 2: Base Case
- When `len(current) == target_length` (permutations)
- When `start == len(candidates)` (subsets)
- When `current` satisfies the constraint (N-Queens: `row == n`)
- **Critical**: Always add a COPY — `results.append(current[:])` not `results.append(current)`, because `current` is mutated.

### Step 3: Pruning (Before the Recursive Call)
- **Combination sum**: if running total > target, return early
- **N-Queens**: if placing a queen would attack an existing queen, skip
- **Word search**: if character doesn't match, return

### Step 4: Iteration — Choose, Recurse, Undo
```python
for i in range(start, len(candidates)):
    current.append(nums[i])        # make choice
    backtrack(i + 1, current)      # recurse
    current.pop()                  # undo choice (CRITICAL)
```
The undo step is critical — without it, choices from one branch pollute the next.

### Step 5: Duplicate Handling (for Repeated Elements)
- Sort the input first
- In the loop: `if i > start and candidates[i] == candidates[i-1]: continue`
- This skips duplicate choices at the same level of the recursion tree without skipping within a single branch.

## Core Problem Templates

### Subsets (Power Set)
```python
def subsets(nums: list[int]) -> list[list[int]]:
    result = []
    def backtrack(start: int, current: list[int]):
        result.append(current[:])       # record current state (even partial)
        for i in range(start, len(nums)):
            current.append(nums[i])
            backtrack(i + 1, current)
            current.pop()
    backtrack(0, [])
    return result
# Time: O(n * 2^n), 2^n subsets, each takes O(n) to copy
# Space: O(n) recursion depth
```

### Permutations
```python
def permutations(nums: list[int]) -> list[list[int]]:
    result = []
    def backtrack(current: list[int], remaining: set):
        if not remaining:
            result.append(current[:])
            return
        for num in list(remaining):
            current.append(num)
            remaining.remove(num)
            backtrack(current, remaining)
            current.pop()
            remaining.add(num)
    backtrack([], set(nums))
    return result
# Time: O(n * n!), n! permutations, O(n) to copy each
```

### Combination Sum (Reuse Allowed, Sum = Target)
```python
def combination_sum(candidates: list[int], target: int) -> list[list[int]]:
    result = []
    candidates.sort()               # enables early termination pruning
    def backtrack(start: int, current: list[int], remaining: int):
        if remaining == 0:
            result.append(current[:])
            return
        for i in range(start, len(candidates)):
            if candidates[i] > remaining:   # pruning: sorted, all future >= this
                break
            current.append(candidates[i])
            backtrack(i, current, remaining - candidates[i])  # i (not i+1): reuse allowed
            current.pop()
    backtrack(0, [], target)
    return result
```

### N-Queens
```python
def solve_n_queens(n: int) -> list[list[str]]:
    result = []
    cols = set()
    diag1 = set()   # (row - col) is constant on each '/' diagonal
    diag2 = set()   # (row + col) is constant on each '\' diagonal
    board = [['.' for _ in range(n)] for _ in range(n)]

    def backtrack(row: int):
        if row == n:
            result.append([''.join(r) for r in board])
            return
        for col in range(n):
            if col in cols or (row-col) in diag1 or (row+col) in diag2:
                continue        # queen would be attacked: prune
            cols.add(col); diag1.add(row-col); diag2.add(row+col)
            board[row][col] = 'Q'
            backtrack(row + 1)
            cols.remove(col); diag1.remove(row-col); diag2.remove(row+col)
            board[row][col] = '.'
    backtrack(0)
    return result
# Time: O(n!), at most n choices per row, n rows
```

## Problem Types and Key Decisions

| Problem Type | Start Index? | Reuse Elements? | Duplicate Skip? | Base Case |
|---|---|---|---|---|
| **Subsets** | Yes (i+1) | No | If input has duplicates: sort + skip | Add at every node (not just leaves) |
| **Permutations** | No (use visited/remaining set) | No (each element once) | Use sorted + visited logic | remaining is empty |
| **Combinations (choose k from n)** | Yes (i+1) | No | Sort + skip if needed | len(current) == k |
| **Combination Sum (reuse)** | Yes (i for reuse, i+1 for no reuse) | Yes | Sort enables early break (pruning) | remaining == 0 |
| **N-Queens / Sudoku** | No (try each column/digit) | No | Constraint check (attack/valid) | row == n / board filled |
| **Word Search** | No (try 4 directions) | No (mark visited) | Bounds + char match | word fully matched |

## Classic Mistakes

1. **Appending current instead of current[:]**: `result.append(current)` appends a reference. When `current` is later modified (popped), all entries in result change. Always `result.append(current[:])` for lists or `result.append(tuple(current))`.

2. **Missing the undo step**: `current.append(x)` -> recurse -> forget `current.pop()`. The next iteration of the loop now has a polluted `current`. Every make-choice must be paired with an undo-choice.

3. **Wrong start index**: For combinations (no reuse): next call is `backtrack(i+1, ...)`. For combination sum (reuse allowed): next call is `backtrack(i, ...)`. Using i+1 when reuse is allowed causes missed solutions; using i when reuse isn't allowed causes duplicates.

4. **Not sorting for duplicate removal**: The "skip if same as previous at same level" trick only works if the input is sorted. Without sorting, duplicates can appear in different orders and the skip condition misses some.

5. **No pruning in combination sum**: Without `if candidates[i] > remaining: break`, the algorithm explores all combinations even when they can't possibly sum to target. Sorting the candidates enables this O(1) pruning at each level.

## Interview Delivery Script

When you see "find all" or "generate all" with combinatorial structure: *"This is a backtracking problem, I'll build solutions incrementally using a DFS over the decision tree, pruning invalid paths early."*

State the template explicitly: **choose -> recurse -> undo.** Draw the first 2 levels of the recursion tree to confirm the structure before coding.

Always state complexity from the tree: *"The recursion tree has O(2^n) nodes for subsets [or O(n!) for permutations], and we copy O(n) per solution, so total time is O(n x 2^n)."*

The staff signal: proactively sort the input and add the duplicate-skip condition before the interviewer asks. Explain what the sort enables: *"Sorting lets me break early when candidates[i] > remaining — every element after i is also too large, so I can skip the rest of this branch."*

## Follow-Up Variations
- How would you handle generating subsets when the input has duplicates?
- What if you need to generate permutations of very large arrays (n > 20)? Can you optimize?
- How would you solve Sudoku using backtracking? What pruning strategy would you use?
- How does backtracking relate to dynamic programming (overlapping subproblems)?
