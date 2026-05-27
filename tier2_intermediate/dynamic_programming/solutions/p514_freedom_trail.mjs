/**
 * P514: Freedom Trail [PREMIUM] (Hard)
 * https://leetcode.com/problems/freedom-trail/
 * Topics: String, Dynamic Programming, Depth-First Search, Breadth-First Search
 *
 * In the video game Fallout 4, the quest "Road to Freedom" requires players to reach a metal dial called the "Freedom Trail Ring" and use the dial to spell a specific keyword to open the door.
 * Given a string ring that represents the code engraved on the outer ring and another string key that represents the keyword that needs to be spelled, return the minimum number of steps to spell all the characters in the keyword.
 * Initially, the first character of the ring is aligned at the "12:00" direction. You should spell all the characters in key one by one by rotating ring clockwise or anticlockwise to make each character of the string key aligned at the "12:00" direction and then by pressing the center button.
 * At the stage of rotating the ring to spell the key character key[i]:
 * Example 1:
 *     Input: ring = "godding", key = "gd"
 *     Output: 4
 *     Explanation:
 *     For the first key character 'g', since it is already in place, we just need 1 step to spell this character.
 *     For the second key character 'd', we need to rotate the ring "godding" anticlockwise by two steps to make it become "ddinggo".
 *     Also, we need 1 more step for spelling.
 *     So the final output is 4.
 *
 * Example 2:
 *     Input: ring = "godding", key = "godding"
 *     Output: 13
 *
 * Constraints:
 *     - 1 <= ring.length, key.length <= 100
 *     - ring and key consist of only lower case English letters.
 *     - It is guaranteed that key could always be spelled by rotating ring.
 *
 * Template (python3):
 *     class Solution:
 *         def findRotateSteps(self, ring: str, key: str) -> int:
 */

import { readLine, readInts, readInt, writeInt, writeInts, writeString, writeBool } from '../../wasm_libs/js/io.mjs';

function solve(ring, key) {
  const n = ring.length;
  const klen = key.length;
  const positions = Array.from({length: 26}, () => []);
  for (let i = 0; i < n; i++) {
    positions[ring.charCodeAt(i) - 97].push(i);
  }
  let dp = new Array(n).fill(0);
  for (let ki = klen - 1; ki >= 0; ki--) {
    const newDp = new Array(n).fill(Infinity);
    const ch = key.charCodeAt(ki) - 97;
    for (let pos = 0; pos < n; pos++) {
      for (const target of positions[ch]) {
        const diff = Math.abs(pos - target);
        const steps = Math.min(diff, n - diff) + 1;
        const val = ki === klen - 1 ? steps : steps + dp[target];
        if (val < newDp[pos]) newDp[pos] = val;
      }
    }
    dp = newDp;
  }
  return dp[0];
}

const ring = readLine();
const key = readLine();
writeInt(solve(ring, key));
