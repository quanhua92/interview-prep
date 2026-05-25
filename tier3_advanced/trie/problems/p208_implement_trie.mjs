/**
 * P208: Implement Trie (Prefix Tree) (Medium)
 * https://leetcode.com/problems/implement-trie-prefix-tree/
 * Topics: Hash Table, String, Design, Trie
 * 
 * A trie (pronounced as "try") or prefix tree is a tree data structure used to efficiently store and retrieve keys in a dataset of strings. There are various applications of this data structure, such as autocomplete and spellchecker.
 * Implement the Trie class:
 * 
 * Example 1:
 *     Input
 *     ["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
 *     [[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
 *     Output
 *     [null, null, true, false, true, null, true]
 * 
 *     Explanation
 *     Trie trie = new Trie();
 *     trie.insert("apple");
 *     trie.search("apple");   // return True
 *     trie.search("app");     // return False
 *     trie.startsWith("app"); // return True
 *     trie.insert("app");
 *     trie.search("app");     // return True
 * 
 * Constraints:
 *     - 1 <= word.length, prefix.length <= 2000
 *     - word and prefix consist only of lowercase English letters.
 *     - At most 3 * 104 calls in total will be made to insert, search, and startsWith.
 * 
 * Template (python3):
 *     class Trie:
 * 
 *         def __init__(self):
 * 
 * 
 *         def insert(self, word: str) -> None:
 * 
 * 
 *         def search(self, word: str) -> bool:
 * 
 * 
 *         def startsWith(self, prefix: str) -> bool:
 * 
 * 
 * 
 *     # Your Trie object will be instantiated and called as such:
 *     # obj = Trie()
 *     # obj.insert(word)
 *     # param_2 = obj.search(word)
 *     # param_3 = obj.startsWith(prefix)
 * 
 * Hint: Build a Trie class with insert, search, and starts_with methods.
 */
class TrieNode
  constructor()
    this.children = {};
    this.isEnd = false;
  } {
    throw new Error("NotImplementedError");
}

class Trie
  constructor()
    this.root = new TrieNode();
  }

  insert(word)
    let node = this.root;
    for (const ch of word)
      if (!(ch in node.children))
        node.children[ch] = new TrieNode();
      }
      node = node.children[ch];
    }
    node.isEnd = true;
  }

  search(word)
    const node = this._find(word);
    return node !== null && node.isEnd;
  }

  startsWith(prefix)
    return this._find(prefix) !== null;
  }

  _find(prefix)
    let node = this.root;
    for (const ch of prefix)
      if (!(ch in node.children)) return null;
      node = node.children[ch];
    }
    return node;
  } {
    throw new Error("NotImplementedError");
}

function solve(operations)
  const trie = new Trie();
  const results = [];
  for (const [op, val] of operations)
    if (op === "insert")
      trie.insert(val);
      results.push(null);
    } else if (op === "search")
      results.push(trie.search(val));
    } else if (op === "starts_with")
      results.push(trie.startsWith(val));
    }
  }
  return results; {
    throw new Error("NotImplementedError");
}

const tests = [
  {
    label: "full sequence",
    input: [[["insert", "apple"], ["search", "apple"], ["search", "app"], ["starts_with", "app"], ["insert", "app"], ["search", "app"]]],
    expected: [null, true, false, true, null, true],
  },
  {
    label: "single character",
    input: [[["insert", "a"], ["search", "a"], ["search", "b"], ["starts_with", "a"], ["starts_with", "b"]]],
    expected: [null, true, false, true, false],
  },
  {
    label: "search non-existent word/prefix",
    input: [[["insert", "hello"], ["search", "world"], ["starts_with", "world"], ["search", "hel"], ["starts_with", "hel"]]],
    expected: [null, false, false, false, true],
  },
  {
    label: "overlapping prefixes",
    input: [[["insert", "a"], ["insert", "ab"], ["insert", "abc"], ["search", "a"], ["search", "ab"], ["search", "abc"], ["search", "abcd"], ["starts_with", "ab"], ["starts_with", "abcd"]]],
    expected: [null, null, null, true, true, true, false, true, false],
  },
  {
    label: "duplicate insert",
    input: [[["insert", "test"], ["insert", "test"], ["search", "test"], ["starts_with", "te"]]],
    expected: [null, null, true, true],
  },
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
