/**
 * P488: Zuma Game [PREMIUM] (Hard)
 * https://leetcode.com/problems/zuma-game/
 * Topics: String, Dynamic Programming, Stack, Breadth-First Search, Memoization
 * 
 * You are playing a variation of the game Zuma.
 * In this variation of Zuma, there is a single row of colored balls on a board, where each ball can be colored red 'R', yellow 'Y', blue 'B', green 'G', or white 'W'. You also have several colored balls in your hand.
 * Your goal is to clear all of the balls from the board. On each turn:
 * Given a string board, representing the row of balls on the board, and a string hand, representing the balls in your hand, return the minimum number of balls you have to insert to clear all the balls from the board. If you cannot clear all the balls from the board using the balls in your hand, return -1.
 * Example 1:
 *     Input: board = "WRRBBW", hand = "RB"
 *     Output: -1
 *     Explanation: It is impossible to clear all the balls. The best you can do is:
 *     - Insert 'R' so the board becomes WRRRBBW. WRRRBBW -> WBBW.
 *     - Insert 'B' so the board becomes WBBBW. WBBBW -> WW.
 *     There are still balls remaining on the board, and you are out of balls to insert.
 * 
 * Example 2:
 *     Input: board = "WWRRBBWW", hand = "WRBRW"
 *     Output: 2
 *     Explanation: To make the board empty:
 *     - Insert 'R' so the board becomes WWRRRBBWW. WWRRRBBWW -> WWBBWW.
 *     - Insert 'B' so the board becomes WWBBBWW. WWBBBWW -> WWWW -> empty.
 *     2 balls from your hand were needed to clear the board.
 * 
 * Example 3:
 *     Input: board = "G", hand = "GGGGG"
 *     Output: 2
 *     Explanation: To make the board empty:
 *     - Insert 'G' so the board becomes GG.
 *     - Insert 'G' so the board becomes GGG. GGG -> empty.
 *     2 balls from your hand were needed to clear the board.
 * 
 * Constraints:
 *     - 1 <= board.length <= 16
 *     - 1 <= hand.length <= 5
 *     - board and hand consist of the characters 'R', 'Y', 'B', 'G', and 'W'.
 *     - The initial row of balls on the board will not have any groups of three or more consecutive balls of the same color.
 * 
 * Template (python3):
 *     class Solution:
 *         def findMinStep(self, board: str, hand: str) -> int:
 */
function solve(board, hand)
  function collapse(s)
    let changed = true;
    while (changed)
      changed = false;
      let i = 0;
      while (i < s.length)
        let j = i;
        while (j < s.length && s[j] === s[i]) j++;
        if (j - i >= 3)
          s = s.slice(0, i) + s.slice(j);
          changed = true;
        } else
          i = j;
        }
      }
    }
    return s;
  }

  const memo = new Map();

  function dfs(boardStr, handSorted)
    boardStr = collapse(boardStr);
    if (boardStr === "") return 0;
    if (handSorted.length === 0) return -1;
    const key = boardStr + "|" + handSorted.join("");
    if (memo.has(key)) return memo.get(key);
    let minBalls = -1;
    for (let i = 0; i <= boardStr.length; i++)
      for (let hi = 0; hi < handSorted.length; hi++)
        if (hi > 0 && handSorted[hi] === handSorted[hi - 1]) continue;
        const color = handSorted[hi];
        const newBoard = boardStr.slice(0, i) + color + boardStr.slice(i);
        const newHand = [...handSorted.slice(0, hi), ...handSorted.slice(hi + 1)];
        const result = dfs(newBoard, newHand);
        if (result !== -1)
          if (minBalls === -1 || result + 1 < minBalls)
            minBalls = result + 1;
          }
        }
      }
    }
    memo.set(key, minBalls);
    return minBalls;
  }

  return dfs(board, [...hand].sort()); {
    throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: ["WRRBBW", "RB"], expected: -1 },
  { label: "example 2", input: ["WWRRBBWW", "WRBRW"], expected: 2 },
  { label: "example 3", input: ["G", "GGGGG"], expected: 2 },
  { label: "one insertion clears chain reaction", input: ["RBYYBBRR", "YRB"], expected: 1 },
  { label: "insert triggers cascade", input: ["RRWWRRBB", "WWB"], expected: 2 },
  { label: "insufficient balls single", input: ["R", "R"], expected: -1 },
  { label: "pair plus one makes triple", input: ["RR", "RR"], expected: 1 },
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
