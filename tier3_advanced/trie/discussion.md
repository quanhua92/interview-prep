# Trie (Prefix Tree) — Discussion

## One-Liner
A trie organizes strings by shared prefixes, enabling O(L) prefix operations, autocomplete, and efficient backtracking pruning for word search problems.

## When to Use a Trie
- Autocomplete / search suggestions (all words starting with a prefix)
- Spell check (find nearest valid words)
- IP routing (longest prefix match)
- Word game solvers (Boggle, Scrabble)
- Any problem involving "all words starting with X" or "count words with prefix"

## When NOT to Use a Trie
- Exact-match lookups only (hash map is O(1) vs trie's O(L))
- Small vocabulary (overhead of trie nodes not justified)
- Tries have worse cache performance than hash maps (node traversal jumps through heap memory)

## Complexity
- **Insert, Search, StartsWith**: O(L) where L = word length
- **All words with prefix X**: O(L + P) where P = number of matches
- **Count words with prefix X**: O(L) with the count optimization
- **Space**: O(total characters across all inserted words) worst case (no shared prefixes). In practice, shared prefixes compress storage significantly.

## Key Design Decisions

### Node Children: dict vs Array-of-26
- **dict children** (`children: dict[str, TrieNode]`): handles any alphabet (Unicode, mixed case, numbers). Space-efficient for sparse alphabets. Slightly slower due to hash map overhead per character step.
- **Array of 26** (`children: list[Optional[TrieNode]]`): fixed to lowercase English only (`ord(c) - ord('a')` for index). ~3-5x faster character lookup. Wastes memory for sparse alphabets.
- **Production rule**: use dict for correctness and flexibility in interviews unless the problem explicitly states lowercase English only and performance is critical.

### TrieNode Fields
- `is_end: bool` -- marks end of a valid word. CRITICAL: distinguishes `search("app")` from `starts_with("app")`.
- `count: int` -- words passing through this node. Add only if prefix-frequency queries are required.
- `__slots__` -- use for memory efficiency in production implementations.

### Implementation Pattern
1. Insert creates nodes for each character, sets `is_end=True` at the last character.
2. Search reuses the same traversal but checks `is_end` at the end.
3. StartsWith is search without the `is_end` check.
4. Extract the shared traversal into a `_traverse()` helper.

## Prefix Count Optimization
Store a `count` field at each node, incremented during insertion for every node on the path from root to the word's last character (not just at `is_end`). Each node's count equals the number of inserted words that pass through it.

- **Query**: traverse to the prefix's endpoint in O(L), read `node.count` -- O(1) after traversal. Total: O(L).
- **Delete support**: decrement `count` along the path. If count reaches zero, remove the node entirely. Enables O(L) deletion and keeps the trie compact.
- **Real-world application**: search autocomplete systems (Google Suggest, browser URL bar). When a user types 'cari', the system traverses 4 nodes and reads the count at the 'i' node to know how many completions exist without scanning them all.

## Word Search II (LC 212) -- Trie + Backtracking
- **Naive approach**: for each word, run backtracking DFS on the grid. O(W x M x N x 4^L).
- **Trie approach**: build a trie from all words, run ONE backtracking DFS traversal of the grid, simultaneously following the trie. At each cell, check if the current path is a prefix in the trie. If no words start with the current path, prune the entire branch.
- **Critical pruning optimization**: after finding a word, set `node.is_end = False` and remove leaf nodes (children empty and not is_end). This prevents re-finding the same word and prunes future grid exploration.
- **Grid backtracking invariant**: mark cell as visited by setting `grid[r][c] = '#'` before recursing, restore afterward. O(1) extra space vs O(MxN) visited set.

## Wildcard Matching (LC 211)
- Supports search with '.' as wildcard (matches any char).
- **Recursive DFS**: at each '.' character, branch into ALL children of the current node. O(26^k x L) worst case where k = number of wildcards.
- **Iterative BFS alternative**: maintain set of current trie nodes. At each char: if '.', expand to all children of all current nodes. Avoids stack overflow for very long patterns.

## Common Trie Mistakes in Interviews
1. **Forgetting the is_end flag**: Without it, `search('app')` and `starts_with('app')` behave identically.
2. **Not handling empty string**: `search('')` should return True if empty string was inserted (is_end on root). `starts_with('')` should always return True.
3. **Misunderstanding trie depth**: A trie is L levels deep, not one level per word. A 5-letter word adds at most 5 nodes (fewer if prefix already exists).
4. **Mutating the board without restoring in Word Search**: Always restore `board[r][c] = ch` after the recursive call.
5. **Skipping trie branch pruning in Word Search II**: Without removing found words and their leaf nodes, the same word gets found repeatedly.

## Must-Know LeetCode Problems

| LC# | Title | Key Insight |
|-----|-------|-------------|
| 208 | Implement Trie | is_end flag separates search from startsWith |
| 211 | Design Add/Search Words | Branch at '.' nodes via DFS/BFS |
| 212 | Word Search II | One DFS pass + trie pruning beats W separate DFS |
| 421 | Max XOR of Two Numbers | Binary trie, greedily choose opposite bit at each level |
| 648 | Replace Words | Insert roots in trie, find shortest prefix match |
| 677 | Map Sum Pairs | Store value at is_end, prefix sum via DFS or count field |
| 745 | Prefix and Suffix Search | Insert suffix#word in trie for dual prefix matching |
| 1268 | Search Suggestions System | Sort words, binary search prefix, return top 3 matches |

Source: [Tries (Prefix Trees): Autocomplete, Word Search, and Wildcard Matching (CalibreOS)](https://www.calibreos.com/learn/dsa-tries)

---

## Binary Trees & BST: Traversals, LCA, and Classic Patterns

### The Single-Node Mental Model

Tree problems feel hard because candidates try to reason about the whole tree at once. The correct mental model: **think about what a single node needs to compute and what it must return to its parent**. If you can answer that for one node, recursion handles the rest.

Every recursive tree function has the same skeleton:
1. **Base case**: what to return for `None`
2. **Recurse** left and right
3. **Combine** left/right results to produce the current node's return value

The entire art of tree problems is step 3. For **height**: return `1 + max(left_height, right_height)`. For **diameter** (LC 543): the longest path through the current node is `left_height + right_height`, but you return the height to the parent. The diameter is tracked as a side effect via a nonlocal variable. This pattern -- *return one thing, track another as a side effect* -- appears in at least 10 common tree problems.

For tree problems that ask for a path sum (LC 112, 113, 124): distinguish between path-through-root (passes through current node) and any-path (can start and end anywhere). Any-path problems require the side-effect pattern.

Key insight: **inorder traversal of a BST yields a sorted array**. This equivalence converts many BST problems into sorted-array problems. Kth smallest in BST? Inorder traversal, return kth element. Validate BST? Inorder traversal must be strictly increasing.

### How to Approach Any Tree Problem in an Interview

1. **Confirm tree type and constraints**: Is this a BST (values matter) or a general binary tree (structure only)? Are values unique? Can the tree be empty? Unbalanced?
2. **Identify the question category**: traversal (what order?), construction (build from arrays), path (sum/length between nodes), BST operations (insert/delete/validate), or LCA/ancestors.
3. **Write the base case first**: `if not node: return <base>` as the first line. For height, base is 0. For path sum, base is target == 0 at leaf.
4. **Apply the single-node mental model**: What does this node need to return to its parent? If you need to track a global result AND return something, use the 'return one thing, side-effect another' pattern.
5. **Choose traversal order from the dependency**: Preorder (root first) when parent values are needed before children. Postorder (root last) when children must be computed before the parent (height, diameter, path sum all require postorder). BFS for level-based problems.

### What Interviewers Are Actually Testing

1. **Can you write the iterative version?** Recursive DFS is trivially derived from the traversal definition. Iterative inorder and postorder are genuinely non-trivial and are explicitly asked. Know both.
2. **Do you understand the BST invariant precisely?** The wrong answer: "left < root < right for every node." The correct constraint: **every node in the left subtree is less than root, every node in the right subtree is greater**. These are different. The classic trap: a node that is left-right valid at its own level but violates the global BST property.
3. **Can you reason about height, balance, and worst-case BST?** A sorted array inserted into a BST degenerates into a linked list -- O(n) operations instead of O(log n). This is why AVL trees and Red-Black trees exist.

### Recursive Tree Template: Height, Diameter, Path Sum

```python
from __future__ import annotations
from typing import Optional

class TreeNode:
    def __init__(self, val: int = 0,
                 left: Optional['TreeNode'] = None,
                 right: Optional['TreeNode'] = None):
        self.val = val
        self.left = left
        self.right = right

# -- Template: return one value, track side effect --
def diameter_of_binary_tree(root: Optional[TreeNode]) -> int:
    """LC 543. KEY: return height to parent, track diameter as side effect."""
    max_diameter = [0]

    def height(node: Optional[TreeNode]) -> int:
        if not node:
            return 0
        left_h = height(node.left)
        right_h = height(node.right)
        max_diameter[0] = max(max_diameter[0], left_h + right_h)
        return 1 + max(left_h, right_h)

    height(root)
    return max_diameter[0]

# -- Path sum: has path root-to-leaf summing to target --
def has_path_sum(root: Optional[TreeNode], target: int) -> bool:
    """LC 112."""
    if not root:
        return False
    if not root.left and not root.right:
        return root.val == target
    remaining = target - root.val
    return has_path_sum(root.left, remaining) or has_path_sum(root.right, remaining)

# -- Max path sum (any path, LC 124) --
def max_path_sum(root: Optional[TreeNode]) -> int:
    """LC 124: path can start/end anywhere."""
    best = [float('-inf')]

    def gain(node: Optional[TreeNode]) -> int:
        if not node:
            return 0
        left_gain = max(gain(node.left), 0)   # ignore negative branches
        right_gain = max(gain(node.right), 0)
        best[0] = max(best[0], node.val + left_gain + right_gain)
        return node.val + max(left_gain, right_gain)  # single branch upward

    gain(root)
    return best[0]
```

### Tree Traversals: Recursive and Iterative

```python
from collections import deque
from typing import Optional

# -- Recursive traversals --
def inorder_recursive(root: Optional[TreeNode]) -> list[int]:
    return (inorder_recursive(root.left) + [root.val] +
            inorder_recursive(root.right)) if root else []

def preorder_recursive(root: Optional[TreeNode]) -> list[int]:
    return ([root.val] + preorder_recursive(root.left) +
            preorder_recursive(root.right)) if root else []

# -- Iterative inorder (interviewers ask this explicitly) --
def inorder_iterative(root: Optional[TreeNode]) -> list[int]:
    """Stack-based. Go left as far as possible, process, then right."""
    result, stack, curr = [], [], root
    while curr or stack:
        while curr:
            stack.append(curr)
            curr = curr.left
        curr = stack.pop()
        result.append(curr.val)
        curr = curr.right
    return result

# -- Iterative preorder --
def preorder_iterative(root: Optional[TreeNode]) -> list[int]:
    if not root:
        return []
    result, stack = [], [root]
    while stack:
        node = stack.pop()
        result.append(node.val)
        if node.right: stack.append(node.right)
        if node.left:  stack.append(node.left)
    return result

# -- Iterative postorder: reverse of (root, right, left) preorder --
def postorder_iterative(root: Optional[TreeNode]) -> list[int]:
    if not root:
        return []
    result, stack = [], [root]
    while stack:
        node = stack.pop()
        result.append(node.val)
        if node.left:  stack.append(node.left)
        if node.right: stack.append(node.right)
    return result[::-1]

# -- BFS / level-order --
def level_order(root: Optional[TreeNode]) -> list[list[int]]:
    """LC 102. CRITICAL: snapshot queue size at start of each level."""
    if not root:
        return []
    result, queue = [], deque([root])
    while queue:
        level_size = len(queue)  # snapshot before loop
        level = []
        for _ in range(level_size):
            node = queue.popleft()
            level.append(node.val)
            if node.left:  queue.append(node.left)
            if node.right: queue.append(node.right)
        result.append(level)
    return result
```

### BST Operations: Insert, Delete, and Degenerate Cases

BST operations (search, insert, delete) run in O(h) time, where h is tree height. For a balanced BST, h = O(log n). For a **degenerate BST** (inserting already-sorted data), h = O(n), making every operation equivalent to a linked list.

**Delete has three cases**:
- **Leaf node**: simply remove it
- **One child**: replace node with its single child
- **Two children**: replace node's value with **inorder successor** (leftmost node in right subtree), then delete the successor from the right subtree

**BST Validation (LC 98)**: pass `min_val` and `max_val` bounds through recursion. At every node: `min_val < node.val < max_val`. Initially call `validate(root, -inf, +inf)`. Left subtree gets `max_val = node.val`, right gets `min_val = node.val`. This handles the global constraint, not just parent-child comparison.

**The naive wrong approach**: check `node.left.val < node.val < node.right.val` at each node. This fails for a node that satisfies local order but violates global BST property.

```python
def bst_insert(root: Optional[TreeNode], val: int) -> TreeNode:
    """Iterative insert, O(h)."""
    new_node = TreeNode(val)
    if not root:
        return new_node
    curr = root
    while True:
        if val < curr.val:
            if not curr.left:
                curr.left = new_node
                break
            curr = curr.left
        else:
            if not curr.right:
                curr.right = new_node
                break
            curr = curr.right
    return root

def bst_delete(root: Optional[TreeNode], key: int) -> Optional[TreeNode]:
    """Recursive delete, 3 cases. O(h)."""
    if not root:
        return None
    if key < root.val:
        root.left = bst_delete(root.left, key)
    elif key > root.val:
        root.right = bst_delete(root.right, key)
    else:
        if not root.left: return root.right
        if not root.right: return root.left
        # Two children: find inorder successor
        successor = root.right
        while successor.left:
            successor = successor.left
        root.val = successor.val
        root.right = bst_delete(root.right, successor.val)
    return root

def is_valid_bst(root: Optional[TreeNode]) -> bool:
    """LC 98. Validate BST with min/max bounds. O(n)."""
    def validate(node, min_val, max_val):
        if not node:
            return True
        if not (min_val < node.val < max_val):
            return False
        return (validate(node.left, min_val, node.val) and
                validate(node.right, node.val, max_val))
    return validate(root, float('-inf'), float('inf'))
```

### Lowest Common Ancestor: Two Versions

**LCA (LC 236)** is one of the most-asked tree questions. The recursive solution handles all cases with one observation: if both p and q are in different subtrees of a node, that node is the LCA.

**General binary tree (LC 236)**:
- If `root` is None, or `root` is `p` or `q`, return `root`
- Recurse left and right
- Both sides non-None: different subtrees, current root is LCA
- One side non-None: both nodes in that subtree, return that result

**BST version (LC 235)** is simpler, no recursion needed on both sides:
- Both p, q values < root.val: LCA in left subtree
- Both p, q values > root.val: LCA in right subtree
- Otherwise: current root is the LCA (one on each side, or root equals p or q)

**Key interview trap**: the BST version cannot be used for general binary trees. General tree uses post-order recursion. BST uses value-comparison shortcut -- O(h) with no unnecessary recursion.

```python
def lowest_common_ancestor(root, p, q):
    """LC 236. LCA in general binary tree. O(n) time, O(h) space."""
    if not root or root is p or root is q:
        return root
    left = lowest_common_ancestor(root.left, p, q)
    right = lowest_common_ancestor(root.right, p, q)
    if left and right:
        return root
    return left if left else right

def lca_bst(root, p, q):
    """LC 235. LCA in BST. O(h) time, O(1) space (iterative)."""
    curr = root
    while curr:
        if p.val < curr.val and q.val < curr.val:
            curr = curr.left
        elif p.val > curr.val and q.val > curr.val:
            curr = curr.right
        else:
            return curr
    return None
```

### Serialize and Deserialize Binary Tree (LC 297)

**Why PREORDER (not INORDER)** for serialization: Inorder serialization is ambiguous -- trees `[1,2,None]` and `[1,None,2]` produce the same inorder `[2,1]` without a preorder to anchor root position. Preorder + null markers uniquely reconstruct ANY binary tree. Inorder alone only works for BSTs (where value order is meaningful).

```python
SENTINEL = "#"

def serialize(root: Optional[TreeNode]) -> str:
    """Preorder DFS with '#' for null nodes. O(n)."""
    def dfs(node):
        if not node:
            parts.append(SENTINEL)
            return
        parts.append(str(node.val))
        dfs(node.left)
        dfs(node.right)

    parts: list[str] = []
    dfs(root)
    return ",".join(parts)

def deserialize(data: str) -> Optional[TreeNode]:
    """Reconstruct from preorder string. O(n)."""
    tokens = deque(data.split(","))

    def build():
        val = tokens.popleft()
        if val == SENTINEL:
            return None
        node = TreeNode(int(val))
        node.left = build()
        node.right = build()
        return node

    return build()
# Example: Tree [1,2,3,4,5] -> "1,2,4,#,#,5,#,#,3,#,#"
```

### Trees/BST: 12 Must-Know LeetCode Problems

| LC# | Title | Category | Technique | Key Insight |
|-----|-------|----------|-----------|-------------|
| 104 | Maximum Depth | Height | Recursive postorder | Return 1 + max(left, right) |
| 543 | Diameter | Path | Height + side-effect | Track max(left+right) as side effect; return height |
| 102 | Level Order Traversal | BFS | Deque + snapshot size | Snapshot queue length before each level loop |
| 105 | Construct from Pre+Inorder | Construction | Divide and conquer | Preorder root splits inorder into left/right subtrees |
| 112 | Path Sum | Path | DFS + target reduction | Reduce target by node value; leaf check at zero |
| 124 | Max Path Sum | Path | Height + side-effect | Gain = node + max(0, left) + max(0, right); return single branch |
| 98 | Validate BST | BST | Min/max bounds | Pass valid range through recursion, not just parent comparison |
| 235 | LCA of BST | BST / LCA | Value comparison walk | Both < root -> left; both > root -> right; else root is LCA |
| 236 | LCA of Binary Tree | LCA | Postorder recursion | Both non-null from left and right -> current node is LCA |
| 297 | Serialize/Deserialize | Construction | Preorder + null markers | Preorder uniquely reconstructs; inorder alone is ambiguous |
| 230 | Kth Smallest in BST | BST | Inorder traversal | Inorder of BST = sorted; stop at kth element |
| 199 | Right Side View | BFS | Level-order, take last | BFS level order; last node in each level is visible from right |

### Common Tree Mistakes in Interviews

1. **Not handling null early.** Every recursive tree function must handle `if not node: return <base>` as the first line. Forgetting this crashes on empty trees or single-node trees.
2. **BST validation with only local check.** `node.left.val < node.val < node.right.val` at every node is WRONG. A node inserted deep in the tree can violate the BST property relative to its grandparent. Always use propagated min/max bounds.
3. **Off-by-one in level-order grouping.** Snapshot `level_size = len(queue)` BEFORE the inner loop, then iterate exactly `level_size` times. If you use `while queue` as the inner loop, all levels collapse into one.
4. **Confusing preorder vs inorder for tree reconstruction.** Inorder + preorder together can reconstruct a tree. Inorder ALONE cannot (ambiguous). Preorder ALONE with null markers CAN reconstruct.
5. **Returning None from LCA when one node isn't found yet.** The LCA recursion propagates partial results upward. A non-None return means "I found something in my subtree." Don't confuse "not found here" with "doesn't exist."

Source: [Binary Trees & BST: Traversals, LCA, and Classic Patterns (CalibreOS)](https://www.calibreos.com/learn/dsa-trees-bst)
