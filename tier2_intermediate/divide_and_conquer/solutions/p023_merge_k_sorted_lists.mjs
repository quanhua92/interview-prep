/**
 * P23: Merge k Sorted Lists (Hard)
 * https://leetcode.com/problems/merge-k-sorted-lists/
 * Topics: Linked List, Divide and Conquer, Heap (Priority Queue), Merge Sort
 *
 * You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.
 * Merge all the linked-lists into one sorted linked-list and return it.
 *
 * Example 1:
 *     Input: lists = [[1,4,5],[1,3,4],[2,6]]
 *     Output: [1,1,2,3,4,4,5,6]
 *     Explanation: The linked-lists are:
 *     [
 *       1->4->5,
 *       1->3->4,
 *       2->6
 *     ]
 *     merging them into one sorted linked list:
 *     1->1->2->3->4->4->5->6
 *
 * Example 2:
 *     Input: lists = []
 *     Output: []
 *
 * Example 3:
 *     Input: lists = [[]]
 *     Output: []
 *
 * Constraints:
 *     - k == lists.length
 *     - 0 <= k <= 104
 *     - 0 <= lists[i].length <= 500
 *     - -104 <= lists[i][j] <= 104
 *     - lists[i] is sorted in ascending order.
 *     - The sum of lists[i].length will not exceed 104.
 *
 * Template (python3):
 *     # Definition for singly-linked list.
 *     # class ListNode:
 *     #     def __init__(self, val=0, next=None):
 *     #         self.val = val
 *     #         self.next = next
 *     class Solution:
 *         def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
 *
 * Hint: Use divide & conquer: merge pairs of lists recursively until one remains.
 */

function solve(lists) {
  if (!lists || lists.length === 0) return [];
  if (lists.length === 1) return [...lists[0]];

  const mid = Math.floor(lists.length / 2);
  const left = solve(lists.slice(0, mid));
  const right = solve(lists.slice(mid));

  const result = [];
  let i = 0, j = 0;
  while (i < left.length && j < right.length) {
    if (left[i] <= right[j]) {
      result.push(left[i]);
      i++;
    } else {
      result.push(right[j]);
      j++;
    }
  }
  while (i < left.length) {
    result.push(left[i]);
    i++;
  }
  while (j < right.length) {
    result.push(right[j]);
    j++;
  }
  return result;
}

const tests = [
  { label: "example 1", input: [[1, 4, 5], [1, 3, 4], [2, 6]], expected: [1, 1, 2, 3, 4, 4, 5, 6] },
  { label: "empty input", input: [], expected: [] },
  { label: "single empty list", input: [[]], expected: [] },
  { label: "single list", input: [[1, 2, 3]], expected: [1, 2, 3] },
  { label: "all same values", input: [[1, 1], [1, 1], [1, 1]], expected: [1, 1, 1, 1, 1, 1] },
  { label: "negative values", input: [[-5, -3], [-4, -2], [-6, 0]], expected: [-6, -5, -4, -3, -2, 0] },
  { label: "two lists", input: [[1, 3], [2, 4]], expected: [1, 2, 3, 4] },
  { label: "mixed empty and non-empty", input: [[], [], [1], [], [2]], expected: [1, 2] },
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
