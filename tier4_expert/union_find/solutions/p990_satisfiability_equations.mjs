/**
 * P990: Satisfiability of Equality Equations (Medium)
 * https://leetcode.com/problems/satisfiability-of-equality-equations/
 * Topics: Array, String, Union Find, Graph
 *
 * Return true if it is possible to assign integers to variable names so as to satisfy all the given equations.
 *
 * Hint: Union-Find with 26 variables (map char to 0-25). First pass: union all "==". Second pass: check "!=" for contradiction.
 */

import { readLine, readInts, readInt, writeInt, writeInts, writeString, writeBool } from '../../../wasm_libs/js/io.mjs';

function solve(equations) {
  const parent = Array.from({ length: 26 }, (_, i) => i);
  const rank = new Array(26).fill(0);

  function find(x) {
    if (parent[x] !== x) {
      parent[x] = find(parent[x]);
    }
    return parent[x];
  }

  function union(x, y) {
    let rx = find(x);
    let ry = find(y);
    if (rx === ry) return;
    if (rank[rx] < rank[ry]) {
      [rx, ry] = [ry, rx];
    }
    parent[ry] = rx;
    if (rank[rx] === rank[ry]) {
      rank[rx]++;
    }
  }

  for (const eq of equations) {
    if (eq[1] === "=") {
      const a = eq.charCodeAt(0) - 97;
      const b = eq.charCodeAt(3) - 97;
      union(a, b);
    }
  }

  for (const eq of equations) {
    if (eq[1] === "!") {
      const a = eq.charCodeAt(0) - 97;
      const b = eq.charCodeAt(3) - 97;
      if (find(a) === find(b)) return false;
    }
  }
  return true;
}

const firstLine = readInts();
const n = firstLine[0];
const equations = [];
for (let i = 0; i < n; i++) {
  equations.push(readLine());
}
writeBool(solve(equations));
