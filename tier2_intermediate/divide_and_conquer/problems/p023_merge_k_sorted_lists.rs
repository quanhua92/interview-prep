/*
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
fn merge_sorted(a: &[i32], b: &[i32]) -> Vec<i32> {
    todo!()
}

fn divide_merge(lists: &[&[i32]], left: usize, right: usize) -> Vec<i32> {
    todo!()
}

fn merge_k_lists(lists: &[&[i32]]) -> Vec<i32> {
    todo!()
}

fn main() {
    struct Case<'a> { label: &'a str, input: &'a [&'a [i32]], expected: &'a [i32] }
    let tests: &[Case] = &[
        Case { label: "example 1", input: &[&[1,4,5],&[1,3,4],&[2,6]], expected: &[1,1,2,3,4,4,5,6] },
        Case { label: "empty input", input: &[], expected: &[] },
        Case { label: "single empty list", input: &[&[]], expected: &[] },
        Case { label: "single list", input: &[&[1,2,3]], expected: &[1,2,3] },
        Case { label: "all same values", input: &[&[1,1],&[1,1],&[1,1]], expected: &[1,1,1,1,1,1] },
        Case { label: "negative values", input: &[&[-5,-3],&[-4,-2],&[-6,0]], expected: &[-6,-5,-4,-3,-2,0] },
        Case { label: "two lists", input: &[&[1,3],&[2,4]], expected: &[1,2,3,4] },
        Case { label: "mixed empty and non-empty", input: &[&[],&[],&[1],&[],&[2]], expected: &[1,2] },
    ];

    println!("\n============================================================");
    println!("  23. Merge k Sorted Lists");
    println!("============================================================");
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = merge_k_lists(tc.input);
        if got == tc.expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
            println!("    Expected: {:?}\n    Got:      {:?}", tc.expected, got);
        }
    }
    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");
    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
