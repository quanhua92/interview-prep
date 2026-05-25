/*
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
use rstest::TestCase;

struct ListNode {
    val: i32,
    next: Option<Box<ListNode>>,
}

fn build_list(arr: &[i32]) -> Option<Box<ListNode>> {
    todo!()
}

fn solve(head: &Option<Box<ListNode>>) -> Vec<i32> {
    todo!()
}

fn main() {
    let tests: &[TestCase] = &[
        TestCase { label: "odd length", input_arr: &[1, 2, 3, 4, 5], target: 0, expected: &[3, 4, 5] },
        TestCase { label: "even length", input_arr: &[1, 2, 3, 4, 5, 6], target: 0, expected: &[4, 5, 6] },
        TestCase { label: "single node", input_arr: &[1], target: 0, expected: &[1] },
        TestCase { label: "two nodes", input_arr: &[1, 2], target: 0, expected: &[2] },
        TestCase { label: "three nodes", input_arr: &[1, 2, 3], target: 0, expected: &[2, 3] },
        TestCase { label: "negative values", input_arr: &[1, -2, 3, -4, 5], target: 0, expected: &[3, -4, 5] },
    ];

    println!("\n============================================================");
    println!("  876. Middle of the Linked List");
    println!("============================================================");
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let head = build_list(tc.input_arr);
        let got = solve(&head);
        if got == tc.expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
            println!("    Expected: {:?}", tc.expected);
            println!("    Got:      {:?}", got);
        }
    }
    let total = tests.len();
    println!("\n  {}/{} passed", passed, total);
    println!("============================================================\n");

    std::process::exit(if passed == total { 0 } else { 1 });
}
