/**
 * P385: Mini Parser [PREMIUM] (Medium)
 * https://leetcode.com/problems/mini-parser/
 * Topics: String, Stack, Depth-First Search
 */

import { readLine, writeInt, writeString } from '../../../wasm_libs/js/io.mjs';

const s = readLine();
if (!s.startsWith('[')) {
  writeInt(parseInt(s, 10));
} else {
  writeString(s);
}
