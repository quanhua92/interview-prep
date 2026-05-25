/*
 * P15: 3Sum (Medium)
 * https://leetcode.com/problems/3sum/
 * Topics: Array, Two Pointers, Sorting
 *
 * Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.
 * Notice that the solution set must not contain duplicate triplets.
 *
 * Example 1:
 *     Input: nums = [-1,0,1,2,-1,-4]
 *     Output: [[-1,-1,2],[-1,0,1]]
 *     Explanation:
 *     nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
 *     nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
 *     nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
 *     The distinct triplets are [-1,0,1] and [-1,-1,2].
 *     Notice that the order of the output and the order of the triplets does not matter.
 *
 * Example 2:
 *     Input: nums = [0,1,1]
 *     Output: []
 *     Explanation: The only possible triplet does not sum up to 0.
 *
 * Example 3:
 *     Input: nums = [0,0,0]
 *     Output: [[0,0,0]]
 *     Explanation: The only possible triplet sums up to 0.
 *
 * Constraints:
 *     - 3 <= nums.length <= 3000
 *     - -105 <= nums[i] <= 105
 *
 * Hints:
 *     - So, we essentially need to find three numbers x, y, and z such that they add up to the given value. If we fix one of the numbers say x, we are left with the two-sum problem at hand!
 *     - For the two-sum problem, if we fix one of the numbers, say x, we have to scan the entire array to find the next number y, which is value - x where value is the input parameter. Can we change our array somehow so that this search becomes faster?
 *     - The second train of thought for two-sum is, without changing the array, can we use additional space somehow? Like maybe a hash map to speed up the search?
 *
 * Template (python3):
 *     class Solution:
 *         def threeSum(self, nums: List[int]) -> List[List[int]]:
 *
 * Hint: Sort, iterate i, nested two pointers for remaining pair, skip duplicates.
 */


fn three_sum(mut nums: Vec<i32>) -> Vec<Vec<i32>> {
    nums.sort();
    let n = nums.len();
    let mut result: Vec<Vec<i32>> = Vec::new();
    let mut i = 0;
    while i < n.saturating_sub(2) {
        if i > 0 && nums[i] == nums[i - 1] {
            i += 1;
            continue;
        }
        let (mut left, mut right) = (i + 1, n - 1);
        while left < right {
            let total = nums[i] + nums[left] + nums[right];
            if total < 0 {
                left += 1;
            } else if total > 0 {
                right -= 1;
            } else {
                result.push(vec![nums[i], nums[left], nums[right]]);
                while left < right && nums[left] == nums[left + 1] { left += 1; }
                while left < right && nums[right] == nums[right - 1] { right -= 1; }
                left += 1;
                right -= 1;
            }
        }
        i += 1;
    }
    for t in &mut result { t.sort(); }
    result.sort();
    result
}

fn main() {
    struct Case { label: &'static str, input: &'static [i32], expected: &'static [i32], expected_triplets: usize }
    let tests: &[Case] = &[
        Case { label: "example 1", input: &[-1, 0, 1, 2, -1, -4], expected: &[-1, -1, 2, -1, 0, 1], expected_triplets: 2 },
        Case { label: "no triplets", input: &[0, 1, 1], expected: &[], expected_triplets: 0 },
        Case { label: "all zeros", input: &[0, 0, 0], expected: &[0, 0, 0], expected_triplets: 1 },
        Case { label: "empty", input: &[], expected: &[], expected_triplets: 0 },
        Case { label: "adjacent duplicate pairs", input: &[-2, 0, 0, 2, 2], expected: &[-2, 0, 2], expected_triplets: 1 },
        Case { label: "all identical values", input: &[0, 0, 0, 0, 0], expected: &[0, 0, 0], expected_triplets: 1 },
        Case { label: "skip-i with left/right dup", input: &[-3, -3, 0, 1, 1, 2, 2], expected: &[-3, 1, 2], expected_triplets: 1 },
        Case { label: "triple duplicate", input: &[-2, 0, 0, 0, 2, 2, 2], expected: &[-2, 0, 2, 0, 0, 0], expected_triplets: 2 },
    ];

    println!("\n============================================================");
    println!("  15. 3Sum");
    println!("============================================================");
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = three_sum(tc.input.to_vec());
        let mut exp: Vec<Vec<i32>> = Vec::new();
        for j in 0..tc.expected_triplets {
            exp.push(tc.expected[j*3..j*3+3].to_vec());
        }
        for t in &mut exp { t.sort(); }
        exp.sort();
        if got == exp {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
            println!("    Expected: {:?}\n    Got:      {:?}", exp, got);
        }
    }
    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");
    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
