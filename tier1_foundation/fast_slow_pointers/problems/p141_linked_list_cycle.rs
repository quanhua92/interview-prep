/*
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
#[allow(dead_code)]
struct ListNode {
    val: i32,
    next: *mut ListNode,
}

fn build_list(vals: &[i32]) -> *mut ListNode {
    if vals.is_empty() {
    todo!()
}
    let mut nodes: Vec<ListNode> = vals
        .iter()
        .map(|&v| ListNode {
    todo!()
})
        .collect();
    for i in 0..nodes.len() - 1 {
    todo!()
}
    let leaked: &'static mut [ListNode] = nodes.leak();
    leaked.as_mut_ptr()
}

fn create_cycle(head: *mut ListNode, n: usize, pos: i32) {
    todo!()
}

fn has_cycle(head: *mut ListNode, n: usize, pos: i32) -> bool {
    todo!()
}

struct CycleTestCase {
    label: &'static str,
    vals: &'static [i32],
    pos: i32,
    expected: bool,
}

fn main() {
    let tests: &[CycleTestCase] = &[
        CycleTestCase { label: "example 1",            vals: &[3, 2, 0, -4],       pos: 1,   expected: true  },
        CycleTestCase { label: "example 2",            vals: &[1, 2],               pos: 0,   expected: true  },
        CycleTestCase { label: "example 3",            vals: &[1],                  pos: -1,  expected: false },
        CycleTestCase { label: "empty list",           vals: &[],                   pos: -1,  expected: false },
        CycleTestCase { label: "two nodes no cycle",   vals: &[1, 2],               pos: -1,  expected: false },
        CycleTestCase { label: "self-loop at tail",    vals: &[1, 2, 3],            pos: 2,   expected: true  },
        CycleTestCase { label: "long list no cycle",   vals: &[1, 2, 3, 4, 5],     pos: -1,  expected: false },
        CycleTestCase { label: "cycle back to head",   vals: &[1, 2, 3],            pos: 0,   expected: true  },
    ];

    println!("\n============================================================");
    println!("  141. Linked List Cycle");
    println!("============================================================");

    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let head = build_list(tc.vals);
        let got = has_cycle(head, tc.vals.len(), tc.pos);
        if got == tc.expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
            println!("    Expected: {}", tc.expected);
            println!("    Got:      {}", got);
        }
    }

    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");

    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
