/**
 * P491: Non-decreasing Subsequences [PREMIUM] (Medium)
 * https://leetcode.com/problems/non-decreasing-subsequences/
 * Topics: Array, Hash Table, Backtracking, Bit Manipulation
 * 
 * Given an integer array nums, return all the different possible non-decreasing subsequences of the given array with at least two elements. You may return the answer in any order.
 * Example 1:
 *     Input: nums = [4,6,7,7]
 *     Output: [[4,6],[4,6,7],[4,6,7,7],[4,7],[4,7,7],[6,7],[6,7,7],[7,7]]
 * 
 * Example 2:
 *     Input: nums = [4,4,3,2,1]
 *     Output: [[4,4]]
 * 
 * Constraints:
 *     - 1 <= nums.length <= 15
 *     - -100 <= nums[i] <= 100
 * 
 * Template (python3):
 *     class Solution:
 *         def findSubsequences(self, nums: List[int]) -> List[List[int]]:
 */
function solve(nums)
  const result = [];

  function backtrack(start, path)
    if (path.length >= 2)
      result.push([...path]);
    }
    const used = new Set();
    for (let i = start; i < nums.length; i++)
      if (used.has(nums[i])) continue;
      if (path.length === 0 || nums[i] >= path[path.length - 1])
        used.add(nums[i]);
        path.push(nums[i]);
        backtrack(i + 1, path);
        path.pop();
      }
    }
  }

  backtrack(0, []);
  return result.sort((a, b) =>
    for (let i = 0; i < Math.min(a.length, b.length); i++)
      if (a[i] !== b[i]) return a[i] - b[i];
    }
    return a.length - b.length;
  }); {
    throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: [[4, 6, 7, 7]], expected: [[4, 6], [4, 6, 7], [4, 6, 7, 7], [4, 7], [4, 7, 7], [6, 7], [6, 7, 7], [7, 7]] },
  { label: "example 2", input: [[4, 4, 3, 2, 1]], expected: [[4, 4]] },
  { label: "all same elements", input: [[2, 2, 2]], expected: [[2, 2], [2, 2, 2]] },
  { label: "strictly decreasing", input: [[5, 4, 3, 2, 1]], expected: [] },
  { label: "strictly increasing", input: [[1, 2, 3]], expected: [[1, 2], [1, 2, 3], [1, 3], [2, 3]] },
  { label: "single element", input: [[1]], expected: [] },
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
