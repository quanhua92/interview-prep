/**
 * P514: Freedom Trail [PREMIUM] (Hard)
 * https://leetcode.com/problems/freedom-trail/
 * Topics: String, Dynamic Programming, Depth-First Search, Breadth-First Search
 * 
 * In the video game Fallout 4, the quest "Road to Freedom" requires players to reach a metal dial called the "Freedom Trail Ring" and use the dial to spell a specific keyword to open the door.
 * Given a string ring that represents the code engraved on the outer ring and another string key that represents the keyword that needs to be spelled, return the minimum number of steps to spell all the characters in the keyword.
 * Initially, the first character of the ring is aligned at the "12:00" direction. You should spell all the characters in key one by one by rotating ring clockwise or anticlockwise to make each character of the string key aligned at the "12:00" direction and then by pressing the center button.
 * At the stage of rotating the ring to spell the key character key[i]:
 * Example 1:
 *     Input: ring = "godding", key = "gd"
 *     Output: 4
 *     Explanation:
 *     For the first key character 'g', since it is already in place, we just need 1 step to spell this character.
 *     For the second key character 'd', we need to rotate the ring "godding" anticlockwise by two steps to make it become "ddinggo".
 *     Also, we need 1 more step for spelling.
 *     So the final output is 4.
 * 
 * Example 2:
 *     Input: ring = "godding", key = "godding"
 *     Output: 13
 * 
 * Constraints:
 *     - 1 <= ring.length, key.length <= 100
 *     - ring and key consist of only lower case English letters.
 *     - It is guaranteed that key could always be spelled by rotating ring.
 * 
 * Template (python3):
 *     class Solution:
 *         def findRotateSteps(self, ring: str, key: str) -> int:
 */
function solve(ring, key)
  const charPositions = {};
  for (let i = 0; i < ring.length; i++)
    const ch = ring[i];
    if (!charPositions[ch]) charPositions[ch] = [];
    charPositions[ch].push(i);
  }

  const n = ring.length;
  let dp = new Array(n).fill(0);

  for (let ki = key.length - 1; ki >= 0; ki--)
    const newDp = new Array(n).fill(Infinity);
    for (let pos = 0; pos < n; pos++)
      for (const target of charPositions[key[ki]])
        const diff = Math.abs(pos - target);
        const steps = Math.min(diff, n - diff) + 1;
        if (ki === key.length - 1)
          newDp[pos] = Math.min(newDp[pos], steps);
        } else
          newDp[pos] = Math.min(newDp[pos], steps + dp[target]);
        }
      }
    }
    dp = newDp;
  }

  return dp[0]; {
    throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: ["godding", "gd"], expected: 4 },
  { label: "example 2", input: ["godding", "godding"], expected: 13 },
  { label: "single char ring and key", input: ["a", "a"], expected: 1 },
  { label: "reverse order key", input: ["abc", "cba"], expected: 6 },
  { label: "repeated chars", input: ["aaaaa", "aaa"], expected: 3 },
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
