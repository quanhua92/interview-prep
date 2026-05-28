import { readFileSync } from "fs";

let _stdinLines = null;
let _stdinIdx = 0;

function _ensureStdin() {
  if (_stdinLines !== null) return;
  const text = readFileSync(0, "utf8");
  _stdinLines = text.split("\n");
  if (_stdinLines.length > 0 && _stdinLines[_stdinLines.length - 1] === "") {
    _stdinLines.pop();
  }
}

export function readLine() {
  _ensureStdin();
  if (_stdinIdx >= _stdinLines.length) return "";
  return _stdinLines[_stdinIdx++];
}

export function readInts() {
  const line = readLine();
  if (!line) return [];
  return line.trim().split(/\s+/).map(Number);
}

export function readInt() {
  return parseInt(readLine(), 10);
}

export function writeInt(val) {
  process.stdout.write(String(val) + "\n");
}

export function writeInts(arr) {
  process.stdout.write(arr.join(" ") + "\n");
}

export function writeString(s) {
  process.stdout.write(String(s) + "\n");
}

export function writeBool(b) {
  process.stdout.write(b ? "true\n" : "false\n");
}
