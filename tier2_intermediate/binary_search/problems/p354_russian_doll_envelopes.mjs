/**
 * P354: Russian Doll Envelopes [PREMIUM] (Hard)
 * https://leetcode.com/problems/russian-doll-envelopes/
 * Topics: Array, Binary Search, Dynamic Programming, Sorting
 * 
 * You are given a 2D array of integers envelopes where envelopes[i] = [wi, hi] represents the width and the height of an envelope.
 * One envelope can fit into another if and only if both the width and height of one envelope are greater than the other envelope's width and height.
 * Return the maximum number of envelopes you can Russian doll (i.e., put one inside the other).
 * Note: You cannot rotate an envelope.
 * Example 1:
 *     Input: envelopes = [[5,4],[6,4],[6,7],[2,3]]
 *     Output: 3
 *     Explanation: The maximum number of envelopes you can Russian doll is 3 ([2,3] => [5,4] => [6,7]).
 * 
 * Example 2:
 *     Input: envelopes = [[1,1],[1,1],[1,1]]
 *     Output: 1
 * 
 * Constraints:
 *     - 1 <= envelopes.length <= 105
 *     - envelopes[i].length == 2
 *     - 1 <= wi, hi <= 105
 * 
 * Template (python3):
 *     class Solution:
 *         def maxEnvelopes(self, envelopes: List[List[int]]) -> int:
 */
function solve(envelopes)
  envelopes.sort((a, b) => a[0] - b[0] || b[1] - a[1]);

  const heights = [];
  for (const [, h] of envelopes)
    let lo = 0;
    let hi = heights.length;
    while (lo < hi)
      const mid = (lo + hi) >> 1;
      if (heights[mid] < h)
        lo = mid + 1;
      } else
        hi = mid;
      }
    }
    if (lo === heights.length)
      heights.push(h);
    } else
      heights[lo] = h;
    }
  }
  return heights.length; {
    throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: [[5, 4], [6, 4], [6, 7], [2, 3]], expected: 3 },
  { label: "example 2", input: [[1, 1], [1, 1], [1, 1]], expected: 1 },
  { label: "single envelope", input: [[1, 1]], expected: 1 },
  { label: "strictly increasing", input: [[1, 2], [2, 3], [3, 4]], expected: 3 },
  { label: "width ties sorted by height desc", input: [[4, 5], [4, 6], [6, 7], [2, 3], [1, 1]], expected: 4 },
  { label: "height breaks chain", input: [[2, 100], [3, 200], [4, 300], [5, 250]], expected: 3 },
];
let passed = 0;
for (let i = 0; i < tests.length; i++) {
  const t = tests[i];
  const got = solve(t.input);
  if (JSON.stringify(got) === JSON.stringify(t.expected)) {
    passed++;
    console.log(`  Test ${i + 1} (${t.label}): PASS`);
  } else {
    console.log(`  Test ${i + 1} (${t.label}): FAIL`);
    console.log(`    Expected: ${JSON.stringify(t.expected)}\n    Got:      ${JSON.stringify(got)}`);
  }
}
console.log(`\n  ${passed}/${tests.length} passed`);
