/**
 * P211: Design Add and Search Words Data Structure (Medium)
 * https://leetcode.com/problems/design-add-and-search-words-data-structure/
 * Topics: String, Depth-First Search, Design, Trie
 *
 * Design a data structure that supports adding new words and finding if a string matches any previously added string.
 * Implement the WordDictionary class:
 * Example:
 *
 * Example 1:
 *     Input
 *     ["WordDictionary","addWord","addWord","addWord","search","search","search","search"]
 *     [[],["bad"],["dad"],["mad"],["pad"],["bad"],[".ad"],["b.."]]
 *     Output
 *     [null,null,null,null,false,true,true,true]
 *
 *     Explanation
 *     WordDictionary wordDictionary = new WordDictionary();
 *     wordDictionary.addWord("bad");
 *     wordDictionary.addWord("dad");
 *     wordDictionary.addWord("mad");
 *     wordDictionary.search("pad"); // return False
 *     wordDictionary.search("bad"); // return True
 *     wordDictionary.search(".ad"); // return True
 *     wordDictionary.search("b.."); // return True
 *
 * Constraints:
 *     - 1 <= word.length <= 25
 *     - word in addWord consists of lowercase English letters.
 *     - word in search consist of '.' or lowercase English letters.
 *     - There will be at most 2 dots in word for search queries.
 *     - At most 104 calls will be made to addWord and search.
 *
 * Hints:
 *     - You should be familiar with how a Trie works. If not, please work on this problem: <a href="https://leetcode.com/problems/implement-trie-prefix-tree/">Implement Trie (Prefix Tree)</a> first.
 *
 * Template (python3):
 *     class WordDictionary:
 *
 *         def __init__(self):
 *
 *
 *         def addWord(self, word: str) -> None:
 *
 *
 *         def search(self, word: str) -> bool:
 *
 *
 *
 *     # Your WordDictionary object will be instantiated and called as such:
 *     # obj = WordDictionary()
 *     # obj.addWord(word)
 *     # param_2 = obj.search(word)
 *
 * Hint: Build a Trie from the word list, then search with DFS handling '.' wildcards by trying all children.
 */

class TrieNode {
  constructor() {
    this.children = {};
    this.isEnd = false;
  }
}

class WordDictionary {
  constructor() {
    this.root = new TrieNode();
  }

  addWord(word) {
    let node = this.root;
    for (const ch of word) {
      if (!(ch in node.children)) {
        node.children[ch] = new TrieNode();
      }
      node = node.children[ch];
    }
    node.isEnd = true;
  }

  search(word) {
    return this._dfs(this.root, word, 0);
  }

  _dfs(node, word, index) {
    if (index === word.length) return node.isEnd;
    const ch = word[index];
    if (ch === ".") {
      for (const child of Object.values(node.children)) {
        if (this._dfs(child, word, index + 1)) return true;
      }
      return false;
    }
    if (!(ch in node.children)) return false;
    return this._dfs(node.children[ch], word, index + 1);
  }
}

function solve(words, searchWords) {
  const wd = new WordDictionary();
  for (const w of words) {
    wd.addWord(w);
  }
  return searchWords.map((sw) => wd.search(sw));
}

const tests = [
  { label: "example 1", input: [["bad", "dad", "mad"], ["pad", "bad", ".ad", "b.."]], expected: [false, true, true, true] },
  { label: "example 2", input: [["a", "ab"], ["a", ".a", "ab"]], expected: [true, false, true] },
  { label: "all dots pattern", input: [["abc"], ["...", ".."]], expected: [true, false] },
  { label: "single char dot matches multiple", input: [["a", "b"], ["."]], expected: [true] },
  { label: "dot at beginning", input: [["abc", "xbc"], [".bc"]], expected: [true] },
  { label: "dot in middle and at end", input: [["abc"], ["a.c", "a.."]], expected: [true, true] },
];
let passed = 0;
for (let i = 0; i < tests.length; i++) {
  const t = tests[i];
  const got = solve(...t.input);
  if (JSON.stringify(got) === JSON.stringify(t.expected)) {
    passed++;
    console.log(`  Test ${i + 1} (${t.label}): PASS`);
  } else {
    console.log(`  Test ${i + 1} (${t.label}): FAIL`);
    console.log(`    Expected: ${JSON.stringify(t.expected)}\n    Got:      ${JSON.stringify(got)}`);
  }
}
console.log(`\n  ${passed}/${tests.length} passed`);
process.exit(passed === tests.length ? 0 : 1);
