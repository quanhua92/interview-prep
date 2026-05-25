/*
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


use rstest::TestCase;

struct ListNode {
    val: i32,
    next: Option<Box<ListNode>>,
}

fn build_list(arr: &[i32]) -> Option<Box<ListNode>> {
    let mut head: Option<Box<ListNode>> = None;
    for &v in arr.iter().rev() {
        head = Some(Box::new(ListNode { val: v, next: head }));
    }
    head
}

fn solve(head: &Option<Box<ListNode>>) -> i32 {
    let mut slow = head.as_ref();
    let mut fast = head.as_ref();
    while fast.is_some() && fast.unwrap().next.is_some() {
        slow = slow.unwrap().next.as_ref();
        fast = fast.unwrap().next.as_ref().unwrap().next.as_ref();
    }
    slow.unwrap().val
}

fn main() {
    let tests: &[TestCase] = &[
        TestCase { label: "middle of odd-length list", input_arr: &[1, 2, 3], target: 0, expected: &[2] },
        TestCase { label: "middle of even-length list", input_arr: &[1, 2, 3, 4], target: 0, expected: &[3] },
        TestCase { label: "single node", input_arr: &[4], target: 0, expected: &[4] },
        TestCase { label: "two nodes", input_arr: &[1, 2], target: 0, expected: &[2] },
        TestCase { label: "three nodes", input_arr: &[5, 6, 7], target: 0, expected: &[6] },
        TestCase { label: "five nodes", input_arr: &[1, 2, 3, 4, 5], target: 0, expected: &[3] },
    ];

    println!("\n============================================================");
    println!("  382. Linked List Random Node");
    println!("============================================================");
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let head = build_list(tc.input_arr);
        let got = solve(&head);
        if got == tc.expected[0] {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
            println!("    Expected: {}", tc.expected[0]);
            println!("    Got:      {}", got);
        }
    }
    let total = tests.len();
    println!("\n  {}/{} passed", passed, total);
    println!("============================================================\n");

    std::process::exit(if passed == total { 0 } else { 1 });
}
