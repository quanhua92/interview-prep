/**
 * P455: Assign Cookies (Easy)
 * https://leetcode.com/problems/assign-cookies/
 * Topics: Array, Two Pointers, Greedy, Sorting
 *
 * Each child i has a greed factor g[i], and each cookie j has a size s[j].
 * Return the maximum number of content children.
 */

import { readInts, writeInt } from "src/wasm_libs/js/io.mjs";

function solve(g, s) {
  const sg = [...g].sort((a, b) => a - b);
  const ss = [...s].sort((a, b) => a - b);
  let child = 0, cookie = 0;
  while (child < sg.length && cookie < ss.length) {
    if (ss[cookie] >= sg[child]) {
      child++;
    }
    cookie++;
  }
  return child;
}

const g = readInts();
const s = readInts();
writeInt(solve(g, s));
