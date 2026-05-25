const JS_KEYWORDS = [
	"break", "case", "catch", "class", "const", "continue", "debugger", "default",
	"delete", "do", "else", "export", "extends", "false", "finally", "for",
	"function", "if", "import", "in", "instanceof", "let", "new", "null",
	"of", "return", "super", "switch", "this", "throw", "true", "try",
	"typeof", "undefined", "var", "void", "while", "with", "yield",
	"async", "await", "static", "get", "set",
	"Array", "Map", "Set", "WeakMap", "WeakSet", "Promise", "Proxy", "Symbol",
	"Object", "Function", "Boolean", "Number", "BigInt", "String", "RegExp",
	"Error", "TypeError", "RangeError", "SyntaxError", "ReferenceError",
	"JSON", "Math", "Date", "parseInt", "parseFloat", "isNaN", "isFinite",
	"console", "process", "globalThis", "undefined", "NaN", "Infinity",
	"length", "push", "pop", "shift", "unshift", "splice", "slice", "concat",
	"join", "indexOf", "lastIndexOf", "includes", "find", "findIndex", "filter",
	"map", "reduce", "forEach", "every", "some", "flat", "flatMap", "reverse",
	"sort", "fill", "copyWithin", "entries", "keys", "values", "from", "of",
	"has", "add", "delete", "clear", "size", "get", "set",
	"split", "trim", "startsWith", "endsWith", "replace", "replaceAll", "match",
	"matchAll", "search", "toUpperCase", "toLowerCase", "charAt", "charCodeAt",
	"substring", "slice", "repeat", "padStart", "padEnd",
	"stringify", "parse", "abs", "ceil", "floor", "round", "min", "max",
	"sqrt", "pow", "log", "random", "PI", "E", "sin", "cos", "tan",
	"then", "catch", "finally", "all", "race", "allSettled", "any", "resolve", "reject",
	"exit", "stdin", "stdout", "stderr", "argv", "env", "cwd", "nextTick",
	"Map", "Set", "parseInt", "parseFloat", "isNaN",
	"queue", "stack", "heap", "deque", "priorityQueue",
	"TreeNode", "ListNode", "buildTree", "buildList",
];

CodeMirror.registerHelper("hint", "javascript", (cm) => {
	const cursor = cm.getCursor();
	const token = cm.getTokenAt(cursor);
	const start = token.start;
	const end = cursor.ch;
	const currentWord = token.string;
	const list = JS_KEYWORDS.filter((item) => item.lastIndexOf(currentWord, 0) === 0);
	return { list, from: CodeMirror.Pos(cursor.line, start), to: CodeMirror.Pos(cursor.line, end) };
});
