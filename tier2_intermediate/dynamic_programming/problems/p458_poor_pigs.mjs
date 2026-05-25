/**
 * P458: Poor Pigs [PREMIUM] (Hard)
 * https://leetcode.com/problems/poor-pigs/
 * Topics: Math, Dynamic Programming, Combinatorics
 * 
 * There are buckets buckets of liquid, where exactly one of the buckets is poisonous. To figure out which one is poisonous, you feed some number of (poor) pigs the liquid to see whether they will die or not. Unfortunately, you only have minutesToTest minutes to determine which bucket is poisonous.
 * You can feed the pigs according to these steps:
 * Given buckets, minutesToDie, and minutesToTest, return the minimum number of pigs needed to figure out which bucket is poisonous within the allotted time.
 * Example 1:
 *     Input: buckets = 4, minutesToDie = 15, minutesToTest = 15
 *     Output: 2
 *     Explanation: We can determine the poisonous bucket as follows:
 *     At time 0, feed the first pig buckets 1 and 2, and feed the second pig buckets 2 and 3.
 *     At time 15, there are 4 possible outcomes:
 *     - If only the first pig dies, then bucket 1 must be poisonous.
 *     - If only the second pig dies, then bucket 3 must be poisonous.
 *     - If both pigs die, then bucket 2 must be poisonous.
 *     - If neither pig dies, then bucket 4 must be poisonous.
 * 
 * Example 2:
 *     Input: buckets = 4, minutesToDie = 15, minutesToTest = 30
 *     Output: 2
 *     Explanation: We can determine the poisonous bucket as follows:
 *     At time 0, feed the first pig bucket 1, and feed the second pig bucket 2.
 *     At time 15, there are 2 possible outcomes:
 *     - If either pig dies, then the poisonous bucket is the one it was fed.
 *     - If neither pig dies, then feed the first pig bucket 3, and feed the second pig bucket 4.
 *     At time 30, one of the two pigs must die, and the poisonous bucket is the one it was fed.
 * 
 * Constraints:
 *     - 1 <= buckets <= 1000
 *     - 1 <= minutesToDie <= minutesToTest <= 100
 * 
 * Hint: What if you only have one shot? Eg. 4 buckets, 15 mins to die, and 15 mins to test.
 * Hint: How many states can we generate with x pigs and T tests?
 * Hint: Find minimum <code>x</code> such that <code>(T+1)^x >= N</code>
 * 
 * Template (python3):
 *     class Solution:
 *         def poorPigs(self, buckets: int, minutesToDie: int, minutesToTest: int) -> int:
 */
function solve(buckets, minutesToDie, minutesToTest)
  const tests = Math.floor(minutesToTest / minutesToDie);
  let pigs = 0;
  while (Math.pow(tests + 1, pigs) < buckets)
    pigs++;
  }
  return pigs; {
    throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: [4, 15, 15], expected: 2 },
  { label: "example 2", input: [4, 15, 30], expected: 2 },
  { label: "single bucket", input: [1, 100, 100], expected: 0 },
  { label: "single test round", input: [125, 1, 1], expected: 7 },
  { label: "large buckets", input: [1000, 15, 60], expected: 5 },
  { label: "medium buckets", input: [8, 15, 30], expected: 2 },
];
let passed = 0;
for (let i = 0; i < tests.length; i++) {
  const t = tests[i];
  const got = solve(t.input[0], t.input[1], t.input[2]);
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
