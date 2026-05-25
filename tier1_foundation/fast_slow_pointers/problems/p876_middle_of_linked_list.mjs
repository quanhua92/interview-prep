/**
 * P876: Middle of the Linked List (Easy)
 * https://leetcode.com/problems/middle-of-the-linked-list/
 * Topics: Linked List, Two Pointers
 *
 * Given the head of a singly linked list, return the middle node of the linked list.
 * If there are two middle nodes, return the second middle node.
 *
 * Example 1:
 *     Input: head = [1,2,3,4,5]
 *     Output: [3,4,5]
 *     Explanation: The middle node of the list is node 3.
 *
 * Example 2:
 *     Input: head = [1,2,3,4,5,6]
 *     Output: [4,5,6]
 *     Explanation: Since the list has two middle nodes with values 3 and 4, we return the second one.
 *
 * Constraints:
 *     - The number of nodes in the list is in the range [1, 100].
 *     - 1 <= Node.val <= 100
 *
 * Template (python3):
 *     # Definition for singly-linked list.
 *     # class ListNode:
 *     #     def __init__(self, val=0, next=None):
 *     #         self.val = val
 *     #         self.next = next
 *     class Solution:
 *         def middleNode(self, head: Optional[ListNode]) -> Optional[ListNode]:
 *
 * Hint: Fast pointer moves 2 steps, slow moves 1, return slow.to_list().
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

function toList(node) {
  const result = [];
  while (node) {
    result.push(node.val);
    node = node.next;
  }
  return result;
}

function solve(input) {
  throw new Error("NotImplementedError");
}

// --- tests ---
const tests = [
  { label: "odd length", input: buildList([1, 2, 3, 4, 5]), expected: [3, 4, 5] },
  { label: "even length", input: buildList([1, 2, 3, 4, 5, 6]), expected: [4, 5, 6] },
  { label: "single node", input: buildList([1]), expected: [1] },
  { label: "two nodes", input: buildList([1, 2]), expected: [2] },
  { label: "three nodes", input: buildList([1, 2, 3]), expected: [2, 3] },
  { label: "negative values", input: buildList([1, -2, 3, -4, 5]), expected: [3, -4, 5] },
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
