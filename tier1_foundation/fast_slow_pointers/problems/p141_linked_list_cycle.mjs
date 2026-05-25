/**
 * P141: Linked List Cycle (Easy)
 * https://leetcode.com/problems/linked-list-cycle/
 * Topics: Hash Table, Linked List, Two Pointers
 *
 * Given head, the head of a linked list, determine if the linked list has a cycle in it.
 * There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the next pointer. Internally, pos is used to denote the index of the node that tail's next pointer is connected to. Note that pos is not passed as a parameter.
 * Return true if there is a cycle in the linked list. Otherwise, return false.
 *
 * Example 1:
 *     Input: head = [3,2,0,-4], pos = 1
 *     Output: true
 *     Explanation: There is a cycle in the linked list, where the tail connects to the 1st node (0-indexed).
 *
 * Example 2:
 *     Input: head = [1,2], pos = 0
 *     Output: true
 *     Explanation: There is a cycle in the linked list, where the tail connects to the 0th node.
 *
 * Example 3:
 *     Input: head = [1], pos = -1
 *     Output: false
 *     Explanation: There is no cycle in the linked list.
 *
 * Constraints:
 *     - The number of the nodes in the list is in the range [0, 104].
 *     - -105 <= Node.val <= 105
 *     - pos is -1 or a valid index in the linked-list.
 *
 * Follow up:
 *     - Can you solve it using O(1) (i.e. constant) memory?
 *
 * Template (python3):
 *     # Definition for singly-linked list.
 *     # class ListNode:
 *     #     def __init__(self, x):
 *     #         self.val = x
 *     #         self.next = None
 *
 *     class Solution:
 *         def hasCycle(self, head: Optional[ListNode]) -> bool:
 *
 * Hint: Use Floyd's cycle-finding algorithm with fast and slow pointers.
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

function solve(head, pos) {
  throw new Error("NotImplementedError");
}

// --- tests ---
const tests = [
  { label: "example 1", input: buildList([3, 2, 0, -4]), args: [1], expected: true },
  { label: "example 2", input: buildList([1, 2]), args: [0], expected: true },
  { label: "example 3", input: buildList([1]), args: [-1], expected: false },
  { label: "empty list", input: null, args: [-1], expected: false },
  { label: "two nodes no cycle", input: buildList([1, 2]), args: [-1], expected: false },
  { label: "self-loop at tail", input: buildList([1, 2, 3]), args: [2], expected: true },
  { label: "long list no cycle", input: buildList([1, 2, 3, 4, 5]), args: [-1], expected: false },
  { label: "cycle back to head", input: buildList([1, 2, 3]), args: [0], expected: true },
];
let passed = 0;
for (let i = 0; i < tests.length; i++) {
  const t = tests[i];
  const got = solve(t.input, t.args[0]);
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
