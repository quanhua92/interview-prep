# Trie (Prefix Tree) — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Recognize & Set Up (1-2 min)
- [ ] Identify the signal words: "autocomplete", "prefix matching", "word search", "dictionary"
- [ ] Confirm the operation involves prefixes (not just exact match -- hash map would suffice)
- [ ] State complexity: all operations O(L) where L = word length
- [ ] State space: O(total characters across all inserted words)
- [ ] Choose node structure:
  - [ ] dict children -- any alphabet (Unicode, mixed case, numbers), flexible
  - [ ] array of 26 -- lowercase English only, 3-5x faster lookup
- [ ] Define TrieNode fields: children, is_end (required), count (only if prefix-frequency needed)

## Phase 2: Implement Core Operations (3-5 min)
- [ ] Write TrieNode class with __slots__ for memory efficiency
- [ ] Implement insert:
  - [ ] Traverse from root, create missing nodes
  - [ ] Set is_end = True at last character only
  - [ ] Increment count on every node along the path (if using prefix count)
- [ ] Implement search:
  - [ ] Traverse all characters
  - [ ] Return is_end of final node (not just that the node exists)
- [ ] Implement starts_with:
  - [ ] Traverse prefix characters
  - [ ] Return True if traversal succeeds (no is_end check)
- [ ] Extract shared traversal into a _traverse() helper
- [ ] Handle edge case: empty string (search('') returns is_end on root)

## Phase 3: Problem-Specific Extensions (5-8 min, interviewer-directed)
- [ ] For autocomplete / prefix frequency:
  - [ ] Use prefix count optimization: O(L) count query via node.count
  - [ ] Explain delete: decrement count, remove nodes where count reaches zero
- [ ] For Word Search II (LC 212):
  - [ ] Build trie from all target words
  - [ ] Run one DFS from every grid cell, walking trie simultaneously
  - [ ] Mark visited: set grid[r][c] = '#' before recursing, restore after
  - [ ] On finding a word: set is_end = False and prune empty leaf nodes
  - [ ] Explain why trie pruning beats W separate DFS passes
- [ ] For wildcard matching (LC 211):
  - [ ] At '.' character: branch into ALL children via DFS
  - [ ] State worst-case complexity: O(26^k x L) where k = number of wildcards
  - [ ] Mention iterative BFS alternative to avoid stack overflow
- [ ] For bit trie (LC 421 Max XOR):
  - [ ] Store bits (0/1) instead of characters
  - [ ] Greedily choose the opposite bit at each level for max XOR

## Phase 4: Verify & Edge Cases (2-3 min)
- [ ] Empty string: search('') returns True only if empty string was inserted
- [ ] Prefix of inserted word: search("app") returns False if only "apple" was inserted (is_end check)
- [ ] Word is prefix of another: starts_with("app") returns True after inserting "apple"
- [ ] Duplicate inserts: count field increments, is_end stays True (idempotent)
- [ ] Grid boundary checks in Word Search: 0 <= nr < rows, 0 <= nc < cols
- [ ] Board restoration in Word Search: always restore grid[r][c] = ch after recursion

## Phase 5: Wrap-Up (1-2 min)
- [ ] Summarize: trie enables O(L) prefix operations by sharing common prefixes
- [ ] State the key trade-off: trie vs hash map (prefix capability vs cache performance)
- [ ] Mention real-world use: autocomplete systems, IP routing, spell checkers

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:

Source: [Tries (Prefix Trees): Autocomplete, Word Search, and Wildcard Matching (CalibreOS)](https://www.calibreos.com/learn/dsa-tries)
