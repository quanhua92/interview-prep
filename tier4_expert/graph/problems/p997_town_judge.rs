/*
 * P997: Find the Town Judge (Easy)
 * https://leetcode.com/problems/find-the-town-judge/
 * Topics: Array, Hash Table, Graph
 * 
 * In a town, there are n people labeled from 1 to n. There is a rumor that one of these people is secretly the town judge.
 * If the town judge exists, then:
 * You are given an array trust where trust[i] = [ai, bi] representing that the person labeled ai trusts the person labeled bi. If a trust relationship does not exist in trust array, then such a trust relationship does not exist.
 * Return the label of the town judge if the town judge exists and can be identified, or return -1 otherwise.
 * 
 * Example 1:
 *     Input: n = 2, trust = [[1,2]]
 *     Output: 2
 * 
 * Example 2:
 *     Input: n = 3, trust = [[1,3],[2,3]]
 *     Output: 3
 * 
 * Example 3:
 *     Input: n = 3, trust = [[1,3],[2,3],[3,1]]
 *     Output: -1
 * 
 * Constraints:
 *     - 1 <= n <= 1000
 *     - 0 <= trust.length <= 104
 *     - trust[i].length == 2
 *     - All the pairs of trust are unique.
 *     - ai != bi
 *     - 1 <= ai, bi <= n
 * 
 * Template (python3):
 *     class Solution:
 *         def findJudge(self, n: int, trust: List[List[int]]) -> int:
 * 
 * Hint: Trust score array: for each [a,b], scores[a]-=1 and scores[b]+=1. Judge has score n-1.
 */
fn find_judge(n: i32, trust: &[(i32, i32)]) -> i32 {
    todo!()
}

struct TC {
    label: &'static str,
    n: i32,
    trust: &'static [(i32, i32)],
    expected: i32,
}

fn main() {
    let tests: &[TC] = &[
        TC { label: "example 1", n: 2, trust: &[(1,2)], expected: 2 },
        TC { label: "example 2", n: 3, trust: &[(1,3),(2,3)], expected: 3 },
        TC { label: "no judge", n: 3, trust: &[(1,3),(2,3),(3,1)], expected: -1 },
        TC { label: "single person", n: 1, trust: &[], expected: 1 },
        TC { label: "judge candidate trusts someone", n: 4, trust: &[(1,3),(2,3),(4,3),(3,4)], expected: -1 },
        TC { label: "no trust relationships n>1", n: 3, trust: &[], expected: -1 },
        TC { label: "mutual trust no judge", n: 2, trust: &[(1,2),(2,1)], expected: -1 },
    ];

    println!("\n============================================================");
    println!("  997. Find the Town Judge");
    println!("============================================================");

    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = find_judge(tc.n, tc.trust);
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
