/*
 * P455: Assign Cookies (Easy)
 * https://leetcode.com/problems/assign-cookies/
 * Topics: Array, Two Pointers, Greedy, Sorting
 * 
 * Assume you are an awesome parent and want to give your children some cookies. But, you should give each child at most one cookie.
 * Each child i has a greed factor g[i], which is the minimum size of a cookie that the child will be content with; and each cookie j has a size s[j]. If s[j] >= g[i], we can assign the cookie j to the child i, and the child i will be content. Your goal is to maximize the number of your content children and output the maximum number.
 * 
 * Example 1:
 *     Input: g = [1,2,3], s = [1,1]
 *     Output: 1
 *     Explanation: You have 3 children and 2 cookies. The greed factors of 3 children are 1, 2, 3.
 *     And even though you have 2 cookies, since their size is both 1, you could only make the child whose greed factor is 1 content.
 *     You need to output 1.
 * 
 * Example 2:
 *     Input: g = [1,2], s = [1,2,3]
 *     Output: 2
 *     Explanation: You have 2 children and 3 cookies. The greed factors of 2 children are 1, 2.
 *     You have 3 cookies and their sizes are big enough to gratify all of the children,
 *     You need to output 2.
 * 
 * Constraints:
 *     - 1 <= g.length <= 3 * 104
 *     - 0 <= s.length <= 3 * 104
 *     - 1 <= g[i], s[j] <= 231 - 1
 * 
 * Template (python3):
 *     class Solution:
 *         def findContentChildren(self, g: List[int], s: List[int]) -> int:
 * 
 * Hint: Sort both arrays and use two pointers to greedily assign the smallest sufficient cookie.
 */
fn find_content_children(mut g: Vec<i32>, mut s: Vec<i32>) -> i32 {
    todo!()
}

fn main() {
    println!("\n============================================================");
    println!("  455. Assign Cookies");
    println!("============================================================");
    let tests: &[(&str, &[i32], &[i32], i32)] = &[
        ("example 1", &[1,2,3], &[1,1], 1),
        ("example 2", &[1,2], &[1,2,3], 2),
        ("no children", &[], &[1,2,3], 0),
        ("no cookies", &[1,2], &[], 0),
        ("all cookies too small", &[10,11], &[1,2,3], 0),
        ("all satisfied", &[1,2,3], &[3,3,3], 3),
        ("exact match", &[5], &[5], 1),
    ];
    let mut passed = 0;
    for (i, (label, g, s, expected)) in tests.iter().enumerate() {
        let got = find_content_children(g.to_vec(), s.to_vec());
        if got == *expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, label);
            println!("    Expected: {}, Got: {}", expected, got);
        }
    }
    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");
    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
