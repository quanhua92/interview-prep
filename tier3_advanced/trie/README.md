# Trie (Prefix Tree)

## Core Idea

A trie is a tree where each node represents a character. Paths from the root to nodes form strings. Unlike a hash map, a trie enables efficient prefix matching and autocompletion by sharing common prefixes among words.

## When to Recognize

- "Autocomplete", "word search", "prefix matching"
- "Implement a dictionary", "add and search words"
- Problems involving many string operations with shared prefixes
- "Word Search II" (use a trie to prune the search space)

## Complexity

- **Insert**: O(m) where m = length of the word
- **Search**: O(m)
- **Starts with (prefix)**: O(m)
- **Space**: O(N * m) where N = number of words, m = average word length

## Template

```python
class TrieNode:
    def __init__(self):
        self.children: dict[str, TrieNode] = {}
        self.is_end = False

class Trie:
    def __init__(self):
        self.root = TrieNode()

    def insert(self, word): ...
    def search(self, word): ...
    def starts_with(self, prefix): ...
```

## Key Variants

1. **Basic Trie**: Insert, search, and prefix check with `is_end` marker.
2. **Trie with word counting**: Track how many times each word was inserted (useful for autocomplete ranking).
3. **Trie with delete**: Remove a word by unmarking `is_end` and pruning empty nodes.

## Problems

| Problem | Difficulty | Description |
|---------|-----------|-------------|
| P208 Implement Trie (Prefix Tree) | Medium | Build a trie with insert, search, and startsWith |
| P212 Word Search II | Hard | Find all words from a dictionary on a board using a trie |
| P211 Design Add and Search Words | Medium | Trie with wildcard '.' DFS search |
| P472 Concatenated Words | Hard | DP word break + sorted words |
