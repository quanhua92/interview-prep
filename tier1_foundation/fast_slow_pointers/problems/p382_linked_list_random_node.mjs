/**
 * P382: Linked List Random Node [PREMIUM] (Medium)
 * https://leetcode.com/problems/linked-list-random-node/
 * Topics: Linked List, Math, Reservoir Sampling, Randomized
 *
 * Given a singly linked list, return a random node's value from the linked list. Each node must have the same probability of being chosen.
 * Implement the Solution class:
 * Example 1:
 * Follow up:
 *     Input
 * Example 1:
 *     ["Solution", "getRandom", "getRandom", "getRandom", "getRandom", "getRandom"]
 *     [[[1, 2, 3]], [], [], [], [], []]
 *     Output
 *     [null, 1, 3, 2, 2, 3]
 *
 *     Explanation
 *     Solution solution = new Solution([1, 2, 3]);
 *     solution.getRandom(); // return 1
 *     solution.getRandom(); // return 3
 *     solution.getRandom(); // return 2
 *     solution.getRandom(); // return 2
 *     solution.getRandom(); // return 3
 *     // getRandom() should return either 1, 2, or 3 randomly. Each element should have equal probability of returning.
 *
 * Constraints:
 *     - The number of nodes in the linked list will be in the range [1, 104].
 *     - -104 <= Node.val <= 104
 *     - At most 104 calls will be made to getRandom.
 *
 * Template (python3):
 *     # Definition for singly-linked list.
 *     # class ListNode:
 *     #     def __init__(self, val=0, next=None):
 *     #         self.val = val
 *     #         self.next = next
 *     class Solution:
 *
 *         def __init__(self, head: Optional[ListNode]):
 *
 *
 *         def getRandom(self) -> int:
 *
 *
 *
 *     # Your Solution object will be instantiated and called as such:
 *     # obj = Solution(head)
 *     # param_1 = obj.getRandom()
 */

function buildList(arr) {
  if (arr.length === 0) return null;
  const dummy = { val: 0, next: null };
  let curr = dummy;
  for (const val of arr) {
    curr.next = { val, next: null };
    curr = curr.next;
  }
  return dummy.next;
}

function solve(input) {
  throw new Error("NotImplementedError");
}

// --- tests ---
const tests = [
  { label: "middle of odd-length list", input: buildList([1, 2, 3]), expected: 2 },
  { label: "middle of even-length list", input: buildList([1, 2, 3, 4]), expected: 3 },
  { label: "single node", input: buildList([4]), expected: 4 },
  { label: "two nodes", input: buildList([1, 2]), expected: 2 },
  { label: "three nodes", input: buildList([5, 6, 7]), expected: 6 },
  { label: "five nodes", input: buildList([1, 2, 3, 4, 5]), expected: 3 },
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
