/**
 * P907: Sum of Subarray Minimums (Medium)
 * https://leetcode.com/problems/sum-of-subarray-minimums/
 * Topics: Array, Dynamic Programming, Stack, Monotonic Stack
 * 
 * Given an array of integers arr, find the sum of min(b), where b ranges over every (contiguous) subarray of arr. Since the answer may be large, return the answer modulo 109 + 7.
 * 
 * Example 1:
 *     Input: arr = [3,1,2,4]
 *     Output: 17
 *     Explanation:
 *     Subarrays are [3], [1], [2], [4], [3,1], [1,2], [2,4], [3,1,2], [1,2,4], [3,1,2,4].
 *     Minimums are 3, 1, 2, 4, 1, 1, 2, 1, 1, 1.
 *     Sum is 17.
 * 
 * Example 2:
 *     Input: arr = [11,81,94,43,3]
 *     Output: 444
 * 
 * Constraints:
 *     - 1 <= arr.length <= 3 * 104
 *     - 1 <= arr[i] <= 3 * 104
 * 
 * Template (python3):
 *     class Solution:
 *         def sumSubarrayMins(self, arr: List[int]) -> int:
 * 
 * Hint: Use a monotonic stack to find the number of subarrays where each element is the minimum.
 */
function solve(arr)
  const MOD = 10 ** 9 + 7;
  const n = arr.length;
  const left = new Array(n).fill(-1);
  const right = new Array(n).fill(n);
  const stack = [];

  for (let i = 0; i < n; i++)
    while (stack.length > 0 && arr[stack[stack.length - 1]] >= arr[i])
      stack.pop();
    }
    left[i] = stack.length > 0 ? stack[stack.length - 1] : -1;
    stack.push(i);
  }

  stack.length = 0;
  for (let i = n - 1; i >= 0; i--)
    while (stack.length > 0 && arr[stack[stack.length - 1]] > arr[i])
      stack.pop();
    }
    right[i] = stack.length > 0 ? stack[stack.length - 1] : n;
    stack.push(i);
  }

  let total = 0;
  for (let i = 0; i < n; i++)
    const countLeft = i - left[i];
    const countRight = right[i] - i;
    total = (total + arr[i] * countLeft * countRight) % MOD;
  }
  return total; {
    throw new Error("NotImplementedError");
}

const tests = [
  { input: [3, 1, 2, 4], expected: 17, label: "example 1" },
  { input: [11, 81, 94, 43, 3], expected: 444, label: "example 2" },
  { input: [1], expected: 1, label: "single element" },
  { input: [2, 1], expected: 4, label: "two elements" },
  { input: [3, 3, 3], expected: 18, label: "all same" },
  { input: [1, 2, 3], expected: 10, label: "strictly increasing" },
  { input: [3, 2, 1], expected: 10, label: "strictly decreasing" },
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
process.exit(passed === tests.length ? 0 : 1);
