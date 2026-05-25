/**
 * P552: Student Attendance Record II [PREMIUM] (Hard)
 * https://leetcode.com/problems/student-attendance-record-ii/
 * Topics: Dynamic Programming
 * 
 * An attendance record for a student can be represented as a string where each character signifies whether the student was absent, late, or present on that day. The record only contains the following three characters:
 * Any student is eligible for an attendance award if they meet both of the following criteria:
 * Given an integer n, return the number of possible attendance records of length n that make a student eligible for an attendance award. The answer may be very large, so return it modulo 109 + 7.
 * Example 1:
 *     Input: n = 2
 *     Output: 8
 *     Explanation: There are 8 records with length 2 that are eligible for an award:
 *     "PP", "AP", "PA", "LP", "PL", "AL", "LA", "LL"
 *     Only "AA" is not eligible because there are 2 absences (there need to be fewer than 2).
 * 
 * Example 2:
 *     Input: n = 1
 *     Output: 3
 * 
 * Example 3:
 *     Input: n = 10101
 *     Output: 183236316
 * 
 * Constraints:
 *     - 1 <= n <= 105
 * 
 * Template (python3):
 *     class Solution:
 *         def checkRecord(self, n: int) -> int:
 */
function solve(n)
  const mod = 10 ** 9 + 7;
  const dp = Array.from({ length: n + 1 }, () =>
    Array.from({ length: 2 }, () => new Array(3).fill(0))
  );
  dp[0][0][0] = 1;
  for (let i = 0; i < n; i++)
    for (let a = 0; a < 2; a++)
      for (let cl = 0; cl < 3; cl++)
        const val = dp[i][a][cl];
        if (val === 0) continue;
        dp[i + 1][a][0] = (dp[i + 1][a][0] + val) % mod;
        if (a < 1)
          dp[i + 1][a + 1][0] = (dp[i + 1][a + 1][0] + val) % mod;
        }
        if (cl < 2)
          dp[i + 1][a][cl + 1] = (dp[i + 1][a][cl + 1] + val) % mod;
        }
      }
    }
  }
  let result = 0;
  for (let a = 0; a < 2; a++)
    for (let cl = 0; cl < 3; cl++)
      result = (result + dp[n][a][cl]) % mod;
    }
  }
  return result; {
    throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: 2, expected: 8 },
  { label: "example 2", input: 1, expected: 3 },
  { label: "example 3", input: 10101, expected: 183236316 },
  { label: "n=3", input: 3, expected: 19 },
  { label: "n=4", input: 4, expected: 43 },
  { label: "n=10", input: 10, expected: 3536 },
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
