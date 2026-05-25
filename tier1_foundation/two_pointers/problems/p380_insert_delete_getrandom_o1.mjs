/**
 * P380: Insert Delete GetRandom O(1) [PREMIUM] (Medium)
 * https://leetcode.com/problems/insert-delete-getrandom-o1/
 * Topics: Array, Hash Table, Math, Design, Randomized
 * 
 * Implement the RandomizedSet class:
 * You must implement the functions of the class such that each function works in average O(1) time complexity.
 * Example 1:
 *     Input
 * Example 1:
 *     ["RandomizedSet", "insert", "remove", "insert", "getRandom", "remove", "insert", "getRandom"]
 *     [[], [1], [2], [2], [], [1], [2], []]
 *     Output
 *     [null, true, false, true, 2, true, false, 2]
 * 
 *     Explanation
 *     RandomizedSet randomizedSet = new RandomizedSet();
 *     randomizedSet.insert(1); // Inserts 1 to the set. Returns true as 1 was inserted successfully.
 *     randomizedSet.remove(2); // Returns false as 2 does not exist in the set.
 *     randomizedSet.insert(2); // Inserts 2 to the set, returns true. Set now contains [1,2].
 *     randomizedSet.getRandom(); // getRandom() should return either 1 or 2 randomly.
 *     randomizedSet.remove(1); // Removes 1 from the set, returns true. Set now contains [2].
 *     randomizedSet.insert(2); // 2 was already in the set, so return false.
 *     randomizedSet.getRandom(); // Since 2 is the only number in the set, getRandom() will always return 2.
 * 
 * Constraints:
 *     - -231 <= val <= 231 - 1
 *     - At most 2 * 105 calls will be made to insert, remove, and getRandom.
 *     - There will be at least one element in the data structure when getRandom is called.
 */

function solve(ops, args) {
  throw new Error("NotImplementedError");
}

// --- tests ---
const tests = [
  {
    label: "example 1",
    input: [["insert", "remove", "insert", "remove", "insert", "getRandom"], [[1], [2], [2], [1], [2], []]],
    expected: [true, false, true, true, false, 2],
  },
  {
    label: "insert multiple then remove middle",
    input: [["insert", "insert", "insert", "getRandom", "remove", "getRandom"], [[10], [20], [30], [], [20], []]],
    expected: [true, true, true, 30, true, 10],
  },
  {
    label: "single element cycle",
    input: [["insert", "getRandom", "remove", "insert", "getRandom"], [[5], [], [5], [5], []]],
    expected: [true, 5, true, true, 5],
  },
  {
    label: "remove all then insert new",
    input: [["insert", "insert", "remove", "remove", "insert", "getRandom"], [[1], [2], [1], [2], [3], []]],
    expected: [true, true, true, true, true, 3],
  },
];
let passed = 0;
for (let i = 0; i < tests.length; i++) {
  const t = tests[i];
  const got = solve(t.input[0], t.input[1]);
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
