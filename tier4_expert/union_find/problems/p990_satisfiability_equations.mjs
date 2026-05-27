/**
 * P990: Satisfiability of Equality Equations (Medium)
 * https://leetcode.com/problems/satisfiability-of-equality-equations/
 * Topics: Array, String, Union Find, Graph
 *
 * You are given an array of strings equations that represent relationships between variables where each string equations[i] is of length 4 and takes one of two different forms: "xi==yi" or "xi!=yi".Here, xi and yi are lowercase letters (not necessarily different) that represent one-letter variable names.
 * Return true if it is possible to assign integers to variable names so as to satisfy all the given equations, or false otherwise.
 *
 * Hint: Union-Find with 26 variables (map char to 0-25). First pass: union all "==". Second pass: check "!=" for contradiction.
 */

import { readLine, readInts, readInt, writeInt, writeInts, writeString, writeBool } from '../../../wasm_libs/js/io.mjs';

function solve(equations) {
  throw new Error("NotImplementedError");
}

const firstLine = readInts();
const n = firstLine[0];
const equations = [];
for (let i = 0; i < n; i++) {
  equations.push(readLine());
}
writeBool(solve(equations));
