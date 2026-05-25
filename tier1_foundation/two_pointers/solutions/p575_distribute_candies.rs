/*
 * P575: Distribute Candies [PREMIUM] (Easy)
 * https://leetcode.com/problems/distribute-candies/
 * Topics: Array, Hash Table
 *
 * Alice has n candies, where the ith candy is of type candyType[i]. Alice noticed that she started to gain weight, so she visited a doctor.
 * The doctor advised Alice to only eat n / 2 of the candies she has (n is always even). Alice likes her candies very much, and she wants to eat the maximum number of different types of candies while still following the doctor's advice.
 * Given the integer array candyType of length n, return the maximum number of different types of candies she can eat if she only eats n / 2 of them.
 * Example 1:
 *     Input: candyType = [1,1,2,2,3,3]
 *     Output: 3
 *     Explanation: Alice can only eat 6 / 2 = 3 candies. Since there are only 3 types, she can eat one of each type.
 *
 * Example 2:
 *     Input: candyType = [1,1,2,3]
 *     Output: 2
 *     Explanation: Alice can only eat 4 / 2 = 2 candies. Whether she eats types [1,2], [1,3], or [2,3], she still can only eat 2 different types.
 *
 * Example 3:
 *     Input: candyType = [6,6,6,6]
 *     Output: 1
 *     Explanation: Alice can only eat 4 / 2 = 2 candies. Even though she can eat 2 candies, she only has 1 type.
 *
 * Constraints:
 *     - n == candyType.length
 *     - 2 <= n <= 104
 *     - n is even.
 *     - -105 <= candyType[i] <= 105
 *
 * Hint: To maximize the number of kinds of candies, we should try to distribute candies such that Alice will gain all kinds.
 * Hint: What is the upper limit of the number of kinds of candies Alice will gain? Remember candies are to distributed equally.
 * Hint: Which data structure is the most suitable for finding the number of kinds of candies?
 * Hint: Will hashset solves the problem? Inserting all candies kind in the hashset and then checking its size with upper limit.
 *
 * Template (python3):
 *     class Solution:
 *         def distributeCandies(self, candyType: List[int]) -> int:
 */


use std::collections::HashSet;

fn distribute_candies(candy_type: &[i32]) -> i32 {
    let unique: HashSet<&i32> = candy_type.iter().collect();
    std::cmp::min(unique.len() as i32, candy_type.len() as i32 / 2)
}

fn main() {
    let mut passed = 0;
    let total = 7;
    println!("\n============================================================");
    println!("  575. Distribute Candies");
    println!("============================================================");

    {
        let got = distribute_candies(&[1, 1, 2, 2, 3, 3]);
        if got == 3 { passed += 1; println!("  Test 1 (example 1): PASS"); }
        else { println!("  Test 1 (example 1): FAIL\n  Expected: 3, Got: {}", got); }
    }
    {
        let got = distribute_candies(&[1, 1, 2, 3]);
        if got == 2 { passed += 1; println!("  Test 2 (example 2): PASS"); }
        else { println!("  Test 2 (example 2): FAIL\n  Expected: 2, Got: {}", got); }
    }
    {
        let got = distribute_candies(&[6, 6, 6, 6]);
        if got == 1 { passed += 1; println!("  Test 3 (example 3): PASS"); }
        else { println!("  Test 3 (example 3): FAIL\n  Expected: 1, Got: {}", got); }
    }
    {
        let got = distribute_candies(&[1, 2, 3, 4]);
        if got == 2 { passed += 1; println!("  Test 4 (all unique types): PASS"); }
        else { println!("  Test 4 (all unique types): FAIL\n  Expected: 2, Got: {}", got); }
    }
    {
        let got = distribute_candies(&[-1, -1, 2, 2]);
        if got == 2 { passed += 1; println!("  Test 5 (negative candy types): PASS"); }
        else { println!("  Test 5 (negative candy types): FAIL\n  Expected: 2, Got: {}", got); }
    }
    {
        let got = distribute_candies(&[100000, -100000, 0, 50000]);
        if got == 2 { passed += 1; println!("  Test 6 (boundary values): PASS"); }
        else { println!("  Test 6 (boundary values): FAIL\n  Expected: 2, Got: {}", got); }
    }
    {
        let got = distribute_candies(&[1, 2, 1, 2, 1, 2, 3, 4]);
        if got == 4 { passed += 1; println!("  Test 7 (eight candies mixed): PASS"); }
        else { println!("  Test 7 (eight candies mixed): FAIL\n  Expected: 4, Got: {}", got); }
    }

    println!("\n  {}/{} passed", passed, total);
    println!("============================================================\n");
    std::process::exit(if passed == total { 0 } else { 1 });
}
