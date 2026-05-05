"""P212: Word Search II (Hard)

TODO: Implement solve() below.
Hint: Build a Trie from the word list, then use DFS on the board to find matching words.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase

class TrieNode:
    def __init__(self):
        self.children: dict[str, TrieNode] = {}
        self.word: str | None = None

class Solution(Problem):
    name = "212. Word Search II"
    test_cases = [
        TestCase(
            input=(
                [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]],
                ["oath","pea","eat","rain"]
            ),
            expected=["eat","oath"],
            label="example 1"
        ),
        TestCase(
            input=([["a","b"],["c","d"]], ["abcb"]),
            expected=[],
            label="example 2"
        ),
    ]

    def solve(self, board: list[list[str]], words: list[str]) -> list[str]:
        rows, cols = len(board), len(board[0])
        result: list[str] = []

        def _build_trie(words: list[str]) -> TrieNode:
            root = TrieNode()
            for w in words:
                node = root
                for ch in w:
                    if ch not in node.children:
                        node.children[ch] = TrieNode()
                    node = node.children[ch]
                node.word = w
            return root

        def dfs(r: int, c: int, parent: TrieNode):
            ch = board[r][c]
            curr = parent.children.get(ch)
            if not curr:
                return
            if curr.word:
                result.append(curr.word)
                curr.word = None  # avoid duplicates
            board[r][c] = "#"
            for dr, dc in [(0,1),(0,-1),(1,0),(-1,0)]:
                nr, nc = r + dr, c + dc
                if 0 <= nr < rows and 0 <= nc < cols and board[nr][nc] != "#":
                    dfs(nr, nc, curr)
            board[r][c] = ch
            if not curr.children:
                parent.children.pop(ch)

        root = _build_trie(words)
        for r in range(rows):
            for c in range(cols):
                dfs(r, c, root)
        return result

if __name__ == "__main__":
    Solution().run()
