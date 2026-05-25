/**
 * P473: Matchsticks to Square [PREMIUM] (Medium)
 * https://leetcode.com/problems/matchsticks-to-square/
 * Topics: Array, Dynamic Programming, Backtracking, Bit Manipulation, Bitmask
 * 
 * You are given an integer array matchsticks where matchsticks[i] is the length of the ith matchstick. You want to use all the matchsticks to make one square. You should not break any stick, but you can link them up, and each matchstick must be used exactly one time.
 * Return true if you can make this square and false otherwise.
 * Example 1:
 *     Input: matchsticks = [1,1,2,2,2]
 *     Output: true
 *     Explanation: You can form a square with length 2, one side of the square came two sticks with length 1.
 * 
 * Example 2:
 *     Input: matchsticks = [3,3,3,3,4]
 *     Output: false
 *     Explanation: You cannot find a way to form a square with all the matchsticks.
 * 
 * Constraints:
 *     - 1 <= matchsticks.length <= 15
 *     - 1 <= matchsticks[i] <= 108
 * 
 * Hint: Treat the matchsticks as an array. Can we split the array into 4 equal parts?
 * Hint: Every matchstick can belong to either of the 4 sides. We don't know which one. Maybe try out all options!
 * Hint: For every matchstick, we have to try out each of the 4 options i.e. which side it can belong to. We can make use of recursion for this.
 * Hint: We don't really need to keep track of which matchsticks belong to a particular side during recursion. We just need to keep track of the <b>length</b> of each of the 4 sides.
 * Hint: When all matchsticks have been used we simply need to see the length of all 4 sides. If they're equal, we have a square on our hands!
 * 
 * Template (python3):
 *     class Solution:
 *         def makesquare(self, matchsticks: List[int]) -> bool:
 */
function solve(matchsticks)
  if (!matchsticks || matchsticks.length === 0) return false;
  const total = matchsticks.reduce((a, b) => a + b, 0);
  if (total % 4 !== 0) return false;
  const side = total / 4;
  matchsticks.sort((a, b) => b - a);
  if (matchsticks[0] > side) return false;
  const sides = [0, 0, 0, 0];

  function backtrack(idx)
    if (idx === matchsticks.length)
      return sides[0] === sides[1] && sides[1] === sides[2] && sides[2] === side;
    }
    for (let i = 0; i < 4; i++)
      if (sides[i] + matchsticks[idx] <= side)
        sides[i] += matchsticks[idx];
        if (backtrack(idx + 1)) return true;
        sides[i] -= matchsticks[idx];
      }
    }
    return false;
  }

  return backtrack(0); {
    throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: [[1, 1, 2, 2, 2]], expected: true },
  { label: "example 2", input: [[3, 3, 3, 3, 4]], expected: false },
  { label: "four equal sticks", input: [[5, 5, 5, 5]], expected: true },
  { label: "all twos cannot form square", input: [[2, 2, 2, 2, 2, 2]], expected: false },
  { label: "minimal square", input: [[1, 1, 1, 1]], expected: true },
  { label: "each stick one side", input: [[3, 3, 3, 3]], expected: true },
];
let passed = 0;
for (let i = 0; i < tests.length; i++) {
  const t = tests[i];
  const got = solve(t.input[0]);
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
