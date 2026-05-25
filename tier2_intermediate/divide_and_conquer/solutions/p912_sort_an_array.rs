/*
 * P912: Sort an Array (Medium)
 * https://leetcode.com/problems/sort-an-array/
 * Topics: Array, Divide and Conquer, Sorting, Heap (Priority Queue), Merge Sort, Bucket Sort, Radix Sort, Counting Sort
 *
 * Given an array of integers nums, sort the array in ascending order and return it.
 * You must solve the problem without using any built-in functions in O(nlog(n)) time complexity and with the smallest space complexity possible.
 *
 * Example 1:
 *     Input: nums = [5,2,3,1]
 *     Output: [1,2,3,5]
 *     Explanation: After sorting the array, the positions of some numbers are not changed (for example, 2 and 3), while the positions of other numbers are changed (for example, 1 and 5).
 *
 * Example 2:
 *     Input: nums = [5,1,1,2,0,0]
 *     Output: [0,0,1,1,2,5]
 *     Explanation: Note that the values of nums are not necessarily unique.
 *
 * Constraints:
 *     - 1 <= nums.length <= 5 * 104
 *     - -5 * 104 <= nums[i] <= 5 * 104
 *
 * Template (python3):
 *     class Solution:
 *         def sortArray(self, nums: List[int]) -> List[int]:
 *
 * Hint: Implement merge sort — divide array in half, sort recursively, merge.
 */


fn sort_array(nums: &[i32]) -> Vec<i32> {
    let n = nums.len();
    if n <= 1 { return nums.to_vec(); }
    let mut arr = nums.to_vec();
    let mut tmp = vec![0i32; n];

    fn merge(arr: &mut Vec<i32>, tmp: &[i32], l: usize, m: usize, r: usize) {
        let mut i = l;
        let mut j = m + 1;
        let mut k = l;
        while i <= m && j <= r {
            if tmp[i] <= tmp[j] { arr[k] = tmp[i]; i += 1; }
            else { arr[k] = tmp[j]; j += 1; }
            k += 1;
        }
        while i <= m { arr[k] = tmp[i]; i += 1; k += 1; }
        while j <= r { arr[k] = tmp[j]; j += 1; k += 1; }
    }

    fn sort(arr: &mut Vec<i32>, tmp: &mut Vec<i32>, l: usize, r: usize) {
        if l >= r { return; }
        let m = l + (r - l) / 2;
        sort(arr, tmp, l, m);
        sort(arr, tmp, m + 1, r);
        for i in l..=r { tmp[i] = arr[i]; }
        merge(arr, tmp, l, m, r);
    }

    sort(&mut arr, &mut tmp, 0, n - 1);
    arr
}

fn main() {
    struct Case<'a> { label: &'a str, input: &'a [i32], expected: &'a [i32] }
    let tests: &[Case] = &[
        Case { label: "example 1", input: &[5, 2, 3, 1], expected: &[1, 2, 3, 5] },
        Case { label: "duplicates", input: &[5, 1, 1, 2, 0, 0], expected: &[0, 0, 1, 1, 2, 5] },
        Case { label: "single element", input: &[1], expected: &[1] },
        Case { label: "empty array", input: &[], expected: &[] },
        Case { label: "already sorted", input: &[1, 2, 3, 4, 5], expected: &[1, 2, 3, 4, 5] },
        Case { label: "reverse sorted", input: &[5, 4, 3, 2, 1], expected: &[1, 2, 3, 4, 5] },
        Case { label: "all same elements", input: &[7, 7, 7, 7], expected: &[7, 7, 7, 7] },
        Case { label: "negative numbers", input: &[-5, -3, -8, -1], expected: &[-8, -5, -3, -1] },
    ];

    println!("\n============================================================");
    println!("  912. Sort an Array");
    println!("============================================================");
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = sort_array(tc.input);
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
