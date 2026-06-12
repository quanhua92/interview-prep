const PYTHON_KEYWORDS = [
	"False", "None", "True", "and", "as", "assert", "async", "await", "break",
	"class", "continue", "def", "del", "elif", "else", "except", "finally",
	"for", "from", "global", "if", "import", "in", "is", "lambda", "match",
	"nonlocal", "not", "or", "pass", "raise", "return", "try", "while", "with", "yield",
	"abs", "all", "any", "ascii", "bin", "bool", "breakpoint", "bytearray", "bytes",
	"callable", "chr", "classmethod", "compile", "complex", "copy", "deepcopy",
	"delattr", "dict", "dir", "divmod", "enumerate", "eval", "exec", "exit", "filter",
	"float", "format", "frozenset", "getattr", "globals", "hasattr", "hash", "help",
	"hex", "id", "input", "int", "isinstance", "issubclass", "iter", "len", "list",
	"locals", "map", "max", "memoryview", "min", "next", "object", "oct", "open", "ord",
	"pow", "print", "property", "range", "repr", "reversed", "round", "set", "setattr",
	"slice", "sorted", "staticmethod", "str", "sum", "super", "tuple", "type", "vars", "zip",
	"self", "__init__", "__name__", "__main__", "__repr__", "__str__", "__len__", "__eq__",
	"__lt__", "__gt__", "__le__", "__ge__", "__hash__", "__getitem__", "__setitem__",
	"__delitem__", "__iter__", "__next__", "__call__", "__contains__", "__enter__", "__exit__",
	"Exception", "BaseException", "ArithmeticError", "AssertionError", "AttributeError",
	"FileNotFoundError", "ImportError", "IndexError", "KeyError", "MemoryError",
	"NotImplementedError", "OSError", "OverflowError", "RecursionError", "RuntimeError",
	"StopIteration", "TypeError", "ValueError", "ZeroDivisionError",
	"collections", "defaultdict", "Counter", "deque", "OrderedDict", "namedtuple",
	"itertools", "functools", "lru_cache", "partial", "reduce", "wraps", "total_ordering",
	"heapq", "bisect", "math", "re", "json", "os", "sys", "pathlib", "Path", "random",
	"typing", "List", "Dict", "Set", "Tuple", "Optional", "Union", "Callable", "Iterator",
	"dataclass", "frozenset", "abstractmethod", "property", "staticmethod", "classmethod",
	"append", "extend", "insert", "remove", "pop", "clear", "index", "count",
	"keys", "values", "items", "get", "update", "pop",
	"add", "discard", "union", "intersection", "difference",
	"join", "split", "strip", "replace", "startswith", "endswith", "lower", "upper",
	"title", "capitalize", "find", "format", "isdigit", "isalpha", "isalnum",
	"encode", "decode", "read", "readline", "readlines", "write", "writelines", "close",
];

CodeMirror.registerHelper("hint", "python", (cm) => {
	const cursor = cm.getCursor();
	const token = cm.getTokenAt(cursor);
	const wordMatch = token.string.match(/[\w$]+/);
	if (!wordMatch) return null;
	const wordIdx = token.string.indexOf(wordMatch[0]);
	const start = token.start + wordIdx;
	const end = token.start + wordIdx + wordMatch[0].length;
	const currentWord = wordMatch[0];
	const list = PYTHON_KEYWORDS.filter((item) => item.lastIndexOf(currentWord, 0) === 0);
	if (list.length === 0) return null;
	return { list, from: CodeMirror.Pos(cursor.line, start), to: CodeMirror.Pos(cursor.line, end) };
});
