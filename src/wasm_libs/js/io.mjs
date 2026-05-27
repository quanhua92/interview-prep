let _stdinLines = null;
let _stdinIdx = 0;

function _writeStdout(s) {
  if (typeof Javy !== "undefined" && Javy.IO && Javy.IO.write) {
    Javy.IO.write(s);
    return;
  }
  const enc = new TextEncoder();
  const view = enc.encode(s);
  if (typeof globalThis.__wasi_imports !== "undefined") {
    const { fd_write } = globalThis.__wasi_imports.wasi_snapshot_preview1;
    const buf = new Uint8Array(view.buffer, view.byteOffset, view.byteLength);
    const iovs = new Uint8Array(new BigUint64Array([BigInt(buf.byteOffset), BigInt(buf.byteLength)]).buffer);
    const nwritten = new Uint8Array(new BigUint64Array([0n]).buffer);
    fd_write(1, iovs.byteOffset, 1, nwritten.byteOffset);
    return;
  }
}

function _initStdin() {
  const chunks = [];
  const buf = new Uint8Array(4096);
  while (true) {
    const n = _readStdin(buf);
    if (n === 0) break;
    chunks.push(new TextDecoder().decode(buf.subarray(0, n)));
  }
  const text = chunks.join("");
  _stdinLines = text.split("\n");
  if (_stdinLines.length > 0 && _stdinLines[_stdinLines.length - 1] === "") {
    _stdinLines.pop();
  }
}

function _readStdin(buf) {
  if (typeof Javy !== "undefined" && Javy.IO && Javy.IO.read) {
    return Javy.IO.read(buf);
  }
  return 0;
}

export function readLine() {
  if (_stdinLines === null) _initStdin();
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
  _writeStdout(String(val) + "\n");
}

export function writeInts(arr) {
  _writeStdout(arr.join(" ") + "\n");
}

export function writeString(s) {
  _writeStdout(String(s) + "\n");
}

export function writeBool(b) {
  _writeStdout(b ? "true\n" : "false\n");
}
