/**
 * P380: Insert Delete GetRandom O(1) [PREMIUM] (Medium)
 * https://leetcode.com/problems/insert-delete-getrandom-o1/
 * Topics: Array, Hash Table, Math, Design, Randomized
 *
 * Implement the RandomizedSet class:
 * You must implement the functions of the class such that each function works in average O(1) time complexity.
 * Example 1:
 *     Input
 * Example 1:
 *     ["RandomizedSet", "insert", "remove", "insert", "getRandom", "remove", "insert", "getRandom"]
 *     [[], [1], [2], [2], [], [1], [2], []]
 *     Output
 *     [null, true, false, true, 2, true, false, 2]
 *
 *     Explanation
 *     RandomizedSet randomizedSet = new RandomizedSet();
 *     randomizedSet.insert(1); // Inserts 1 to the set. Returns true as 1 was inserted successfully.
 *     randomizedSet.remove(2); // Returns false as 2 does not exist in the set.
 *     randomizedSet.insert(2); // Inserts 2 to the set, returns true. Set now contains [1,2].
 *     randomizedSet.getRandom(); // getRandom() should return either 1 or 2 randomly.
 *     randomizedSet.remove(1); // Removes 1 from the set, returns true. Set now contains [2].
 *     randomizedSet.insert(2); // 2 was already in the set, so return false.
 *     randomizedSet.getRandom(); // Since 2 is the only number in the set, getRandom() will always return 2.
 *
 * Constraints:
 *     - -2^31 <= val <= 2^31 - 1
 *     - At most 2 * 10^5 calls will be made to insert, remove, and getRandom.
 *     - There will be at least one element in the data structure when getRandom is called.
 */


import { readInts, readLine, readInt, writeInt, writeBool } from '../../wasm_libs/js/io.mjs';

class RandomizedSet {
  constructor() {
      throw new Error("NotImplementedError");
  }

  insert(val) {
      throw new Error("NotImplementedError");
  }

  remove(val) {
      throw new Error("NotImplementedError");
  }

  getRandom() {
      throw new Error("NotImplementedError");
  }
}

function solve(ops, args) {
    const rs = new RandomizedSet();
    const results = [];
    for (let i = 0; i < ops.length; i++) {
        if (ops[i] === "insert") {
            results.push(rs.insert(args[i][0]));
        } else if (ops[i] === "remove") {
            results.push(rs.remove(args[i][0]));
        } else if (ops[i] === "getRandom") {
            results.push(rs.getRandom());
        }
    }
    return results;
}

const n = readInt();
const ops = [];
for (let i = 0; i < n; i++) ops.push(readLine());
const args = [];
for (let i = 0; i < n; i++) {
  const line = readLine();
  args.push(line ? line.trim().split(/\s+/).map(Number) : []);
}
const result = solve(ops, args);
for (const r of result) {
  if (typeof r === "boolean") {
    writeBool(r);
  } else {
    writeInt(r);
  }
}
