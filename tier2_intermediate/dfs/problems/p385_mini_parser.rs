/*
 * P385: Mini Parser [PREMIUM] (Medium)
 * https://leetcode.com/problems/mini-parser/
 * Topics: String, Stack, Depth-First Search
 * 
 * Given a string s represents the serialization of a nested list, implement a parser to deserialize it and return the deserialized NestedInteger.
 * Each element is either an integer or a list whose elements may also be integers or other lists.
 * Example 1:
 *     Input: s = "324"
 *     Output: 324
 *     Explanation: You should return a NestedInteger object which contains a single integer 324.
 * 
 * Example 2:
 *     Input: s = "[123,[456,[789]]]"
 *     Output: [123,[456,[789]]]
 *     Explanation: Return a NestedInteger object containing a nested list with 2 elements:
 *     1. An integer containing value 123.
 *     2. A nested list containing two elements:
 *     i.  An integer containing value 456.
 *     ii. A nested list with one element:
 *     a. An integer containing value 789
 * 
 * Constraints:
 *     - 1 <= s.length <= 5 * 104
 *     - s consists of digits, square brackets "[]", negative sign '-', and commas ','.
 *     - s is the serialization of valid NestedInteger.
 *     - All the values in the input are in the range [-106, 106].
 * 
 * Template (python3):
 *     # '''
 *     # This is the interface that allows for creating nested lists.
 *     # You should not implement it, or speculate about its implementation
 *     # '''
 *     #class NestedInteger:
 *     #    def __init__(self, value=None):
 *     #        '''
 *     #        If value is not specified, initializes an empty list.
 *     #        Otherwise initializes a single integer equal to value.
 *     #        '''
 *     #
 *     #    def isInteger(self):
 *     #        '''
 *     #        @return True if this NestedInteger holds a single integer, rather than a nested list.
 *     #        :rtype bool
 *     #        '''
 *     #
 *     #    def add(self, elem):
 *     #        '''
 *     #        Set this NestedInteger to hold a nested list and adds a nested integer elem to it.
 *     #        :rtype void
 *     #        '''
 *     #
 *     #    def setInteger(self, value):
 *     #        '''
 *     #        Set this NestedInteger to hold a single integer equal to value.
 *     #        :rtype void
 *     #        '''
 *     #
 *     #    def getInteger(self):
 *     #        '''
 *     #        @return the single integer that this NestedInteger holds, if it holds a single integer
 *     #        Return None if this NestedInteger holds a nested list
 *     #        :rtype int
 *     #        '''
 *     #
 *     #    def getList(self):
 *     #        '''
 *     #        @return the nested list that this NestedInteger holds, if it holds a nested list
 *     #        Return None if this NestedInteger holds a single integer
 *     #        :rtype List[NestedInteger]
 *     #        '''
 * 
 *     class Solution:
 *         def deserialize(self, s: str) -> NestedInteger:
 */
#[allow(unused_imports)]
use rstest;

#[derive(Clone, Debug)]
enum NestedInteger {
    Int(i32),
    List(Vec<NestedInteger>),
}

fn ni_eq(a: &NestedInteger, b: &NestedInteger) -> bool {
    todo!()
}

fn deserialize(s: &str) -> NestedInteger {
    todo!()
}

fn print_ni(ni: &NestedInteger) {
    todo!()
}

struct TestCase<'a> {
    label: &'a str,
    input: &'a str,
    expected: NestedInteger,
}

fn main() {
    println!("\n============================================================");
    println!("  385. Mini Parser");
    println!("============================================================");

    let tests: Vec<TestCase> = vec![
        TestCase { label: "example 1", input: "324", expected: NestedInteger::Int(324) },
        TestCase { label: "example 2", input: "[123,[456,[789]]]", expected: NestedInteger::List(vec![NestedInteger::Int(123), NestedInteger::List(vec![NestedInteger::Int(456), NestedInteger::List(vec![NestedInteger::Int(789)])])]) },
        TestCase { label: "negative in list", input: "[-1]", expected: NestedInteger::List(vec![NestedInteger::Int(-1)]) },
        TestCase { label: "empty list", input: "[]", expected: NestedInteger::List(vec![]) },
        TestCase { label: "nested empty list", input: "[[]]", expected: NestedInteger::List(vec![NestedInteger::List(vec![])]) },
        TestCase { label: "flat list", input: "[1,2,3]", expected: NestedInteger::List(vec![NestedInteger::Int(1), NestedInteger::Int(2), NestedInteger::Int(3)]) },
        TestCase { label: "negative integer", input: "-42", expected: NestedInteger::Int(-42) },
    ];

    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = deserialize(tc.input);
        if ni_eq(&got, &tc.expected) {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
            print!("    Expected: "); print_ni(&tc.expected); println!();
            print!("    Got:      "); print_ni(&got); println!();
        }
    }

    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");

    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
