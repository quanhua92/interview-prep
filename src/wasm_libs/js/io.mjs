import * as std from "qjs:std";

let _stdinLines = null;
let _stdinIdx = 0;

function _ensureStdin() {
  if (_stdinLines !== null) return;
  const text = std.in.readAsString();
  _stdinLines = text.split("\n");
  if (_stdinLines.length > 0 && _stdinLines[_stdinLines.length - 1] === "") {
    _stdinLines.pop();
  }
}

function _writeStdout(s) {
  std.out.puts(s);
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
  _writeStdout("[OUT] " + String(val) + "\n");
}

export function writeInts(arr) {
  _writeStdout("[OUT] " + arr.join(" ") + "\n");
}

export function writeString(s) {
  _writeStdout("[OUT] " + String(s) + "\n");
}

export function writeBool(b) {
  _writeStdout("[OUT] " + (b ? "true\n" : "false\n"));
}
