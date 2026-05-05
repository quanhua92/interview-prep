"""Trie (prefix tree) template: three core variants.

Variant 1 -- Basic Trie: insert, search, startsWith.
Variant 2 -- Trie with word counting: track insertion count per word.
Variant 3 -- Trie with delete: remove words and prune empty branches.
"""

from __future__ import annotations


class TrieNode:
    """A single node in the trie.

    Attributes:
        children: Mapping from character to child TrieNode.
        is_end:   Whether this node marks the end of a complete word.
        count:    Number of times this node has been marked as end-of-word
                  (used in Variant 2).
    """

    __slots__ = ("children", "is_end", "count")

    def __init__(self) -> None:
        self.children: dict[str, TrieNode] = {}
        self.is_end: bool = False
        self.count: int = 0


class Trie:
    """Variant 1: Basic Trie with insert, search, and starts_with.

    Time:  O(m) per operation where m = word length
    Space: O(N * m) where N = number of words
    """

    def __init__(self) -> None:
        self.root = TrieNode()

    def insert(self, word: str) -> None:
        """Insert *word* into the trie."""
        node = self.root
        for ch in word:
            if ch not in node.children:
                node.children[ch] = TrieNode()
            node = node.children[ch]
        node.is_end = True

    def search(self, word: str) -> bool:
        """Return True if *word* exists in the trie."""
        node = self._find(word)
        return node is not None and node.is_end

    def starts_with(self, prefix: str) -> bool:
        """Return True if any word in the trie starts with *prefix*."""
        return self._find(prefix) is not None

    def _find(self, prefix: str) -> TrieNode | None:
        """Traverse the trie following *prefix*. Return the terminal node or None."""
        node = self.root
        for ch in prefix:
            if ch not in node.children:
                return None
            node = node.children[ch]
        return node


class CountingTrie(Trie):
    """Variant 2: Trie that tracks how many times each word was inserted."""

    def insert(self, word: str) -> None:
        node = self.root
        for ch in word:
            if ch not in node.children:
                node.children[ch] = TrieNode()
            node = node.children[ch]
        node.count += 1
        node.is_end = True

    def count_word(self, word: str) -> int:
        """Return how many times *word* was inserted."""
        node = self._find(word)
        return node.count if node is not None else 0


class DeletableTrie(Trie):
    """Variant 3: Trie that supports deletion of words.

    After deletion, empty branches are pruned to save space.
    """

    def delete(self, word: str) -> bool:
        """Delete *word* from the trie. Return True if the word was found and removed."""
        nodes: list[tuple[TrieNode, str]] = [(self.root, "")]

        # Walk down the trie, recording the path
        node = self.root
        for ch in word:
            if ch not in node.children:
                return False
            nodes.append((node.children[ch], ch))
            node = node.children[ch]

        if not node.is_end:
            return False

        node.is_end = False
        node.count = 0

        # Prune empty branches from the leaf up
        for i in range(len(nodes) - 1, 0, -1):
            parent_node, child_ch = nodes[i - 1]
            child_node = nodes[i][0]
            if not child_node.is_end and not child_node.children:
                parent_node.children.pop(child_ch)
            else:
                break  # stop pruning as soon as we hit a non-empty node

        return True
