/**
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
 *     class Solution:
 *         def deserialize(self, s: str) -> NestedInteger:
 */

class NestedInteger {
  constructor(value) {
    if (value === undefined) {
      this._list = [];
      this._integer = undefined;
    } else {
      this._integer = value;
      this._list = undefined;
    }
  }

  isInteger() {
    return this._list === undefined;
  }

  add(elem) {
    this._list.push(elem);
  }

  setInteger(value) {
    this._integer = value;
    this._list = undefined;
  }

  getInteger() {
    return this._list === undefined ? this._integer : undefined;
  }

  getList() {
    return this._list !== undefined ? this._list : undefined;
  }

  toJS() {
    if (this.isInteger()) return this.getInteger();
    return this.getList().map((item) => item.toJS());
  }
}

function solve(s) {
  if (!s.startsWith("[")) {
    return new NestedInteger(parseInt(s, 10));
  }
  const stack = [];
  let current = new NestedInteger();
  let i = 0;
  while (i < s.length) {
    if (s[i] === "[") {
      const newNi = new NestedInteger();
      if (stack.length > 0) {
        stack[stack.length - 1].add(newNi);
      }
      stack.push(newNi);
      current = newNi;
      i++;
    } else if (s[i] === "]") {
      const finished = stack.pop();
      current = finished;
      i++;
    } else if (s[i] === ",") {
      i++;
    } else {
      let j = i;
      while (j < s.length && (s[j] >= "0" && s[j] <= "9" || s[j] === "-")) {
        j++;
      }
      const num = new NestedInteger(parseInt(s.slice(i, j), 10));
      if (stack.length > 0) {
        stack[stack.length - 1].add(num);
      } else {
        current = num;
      }
      i = j;
    }
  }
  return current;
}

function toJS(result) {
  if (result instanceof NestedInteger) return result.toJS();
  return result;
}

const tests = [
  { label: "example 1", input: "324", expected: 324 },
  { label: "example 2", input: "[123,[456,[789]]]", expected: [123, [456, [789]]] },
  { label: "negative in list", input: "[-1]", expected: [-1] },
  { label: "empty list", input: "[]", expected: [] },
  { label: "nested empty list", input: "[[]]", expected: [[]] },
  { label: "flat list", input: "[1,2,3]", expected: [1, 2, 3] },
  { label: "negative integer", input: "-42", expected: -42 },
];
let passed = 0;
for (let i = 0; i < tests.length; i++) {
  const t = tests[i];
  const got = toJS(solve(t.input));
  if (JSON.stringify(got) === JSON.stringify(t.expected)) {
    passed++;
    console.log(`  Test ${i + 1} (${t.label}): PASS`);
  } else {
    console.log(`  Test ${i + 1} (${t.label}): FAIL`);
    console.log(`    Expected: ${JSON.stringify(t.expected)}\n    Got:      ${JSON.stringify(got)}`);
  }
}
console.log(`\n  ${passed}/${tests.length} passed`);
process.exit(passed === tests.length ? 0 : 1);
