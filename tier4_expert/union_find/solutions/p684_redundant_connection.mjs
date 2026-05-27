/**
 * P684: Redundant Connection (Medium)
 * https://leetcode.com/problems/redundant-connection/
 * Topics: Depth-First Search, Breadth-First Search, Union Find, Graph
 *
 * Return an edge that can be removed so that the resulting graph is a tree of n nodes.
 * If there are multiple answers, return the answer that occurs last in the input.
 *
 * Hint: Use Union-Find to detect the first edge that connects two already-connected nodes.
 */

import { readLine, readInts, readInt, writeInt, writeInts, writeString, writeBool } from '../../../wasm_libs/js/io.mjs';

function solve(edges) {
  const n = edges.length;
  const parent = Array.from({ length: n + 1 }, (_, i) => i);
  const rank = new Array(n + 1).fill(0);

  function find(x) {
    if (parent[x] !== x) parent[x] = find(parent[x]);
    return parent[x];
  }

  function union(x, y) {
    let rx = find(x), ry = find(y);
    if (rx === ry) return false;
    if (rank[rx] < rank[ry]) [rx, ry] = [ry, rx];
    parent[ry] = rx;
    if (rank[rx] === rank[ry]) rank[rx]++;
    return true;
  }

  for (const [u, v] of edges) {
    if (!union(u, v)) return [u, v];
  }
  return [];
}

const firstLine = readInts();
const n = firstLine[0];
const edges = [];
for (let i = 0; i < n; i++) {
  const row = readInts();
  edges.push([row[0], row[1]]);
}
const result = solve(edges);
writeInts(result);
