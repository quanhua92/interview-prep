const RUST_KEYWORDS = [
	"as", "async", "await", "break", "const", "continue", "crate", "dyn", "else",
	"enum", "extern", "false", "fn", "for", "if", "impl", "in", "let", "loop",
	"match", "mod", "move", "mut", "pub", "ref", "return", "self", "Self", "static",
	"struct", "super", "trait", "true", "type", "unsafe", "use", "where", "while",
	"abstract", "become", "box", "do", "final", "gen", "macro", "override", "priv",
	"try", "typeof", "unsized", "virtual", "yield",
	"'static", "macro_rules", "raw", "safe", "union",
	"Vec", "VecDeque", "LinkedList", "HashMap", "BTreeMap", "HashSet", "BTreeSet",
	"BinaryHeap", "Option", "Some", "None", "Result", "Ok", "Err",
	"String", "str", "Box", "Rc", "Arc", "Weak", "Cell", "RefCell",
	"Mutex", "RwLock", "Cow", "OsString", "OsStr", "CString", "CStr",
	"Range", "RangeInclusive", "RangeFrom", "RangeTo", "RangeFull",
	"Duration", "Instant", "File", "BufReader", "BufWriter",
	"Path", "PathBuf", "ThreadId", "JoinHandle", "Sender", "Receiver",
	"SyncSender", "AtomicBool", "AtomicIsize", "AtomicUsize", "AtomicPtr",
	"PhantomData", "Once", "OnceLock", "Barrier", "Condvar", "Semaphore",
	"Clone", "Copy", "Debug", "Display", "Default", "Eq", "PartialEq",
	"Ord", "PartialOrd", "Hash", "Iterator", "IntoIterator", "From", "Into",
	"FromIterator", "AsRef", "AsMut", "Borrow", "BorrowMut", "Deref", "DerefMut",
	"Drop", "Fn", "FnMut", "FnOnce", "Send", "Sync", "Sized", "Unpin",
	"Read", "Write", "Seek", "BufRead", "DoubleEndedIterator", "ExactSizeIterator",
	"Extend", "FromStr", "ToString", "ToOwned", "Error", "Future", "Stream",
	"Add", "Sub", "Mul", "Div", "Rem", "Neg", "Not", "Shl", "Shr",
	"BitAnd", "BitOr", "BitXor", "Index", "IndexMut",
	"println", "eprintln", "print", "eprint", "format", "vec", "dbg",
	"assert", "assert_eq", "assert_ne", "panic", "unimplemented", "unreachable",
	"todo", "debug_assert", "debug_assert_eq", "debug_assert_ne",
	"matches", "concat", "concat_idents", "include", "include_str", "include_bytes",
	"env", "option_env", "cfg", "thread_local", "write", "writeln",
	"select", "try", "file", "line", "column", "module_path", "stringify",
	"push", "pop", "insert", "remove", "clear", "len", "is_empty", "capacity",
	"reserve", "shrink_to_fit", "contains", "contains_key", "contains_value",
	"iter", "iter_mut", "into_iter", "drain", "extend", "truncate", "retain",
	"sort", "sort_by", "sort_by_key", "binary_search", "binary_search_by",
	"clone_from", "to_vec", "to_string", "as_slice", "as_mut_slice", "as_str",
	"from_str", "parse", "unwrap", "unwrap_or", "unwrap_or_else",
	"unwrap_or_default", "expect", "is_ok", "is_err", "is_some", "is_none",
	"ok", "err", "map", "map_err", "and_then", "or_else", "filter", "filter_map",
	"flat_map", "fold", "reduce", "collect", "sum", "product", "min", "max",
	"min_by_key", "max_by_key", "count", "any", "all", "find", "position",
	"nth", "last", "rev", "take", "take_while", "skip", "skip_while",
	"enumerate", "zip", "chain", "cycle", "cloned", "copied", "for_each",
	"inspect", "flatten", "step_by", "fuse", "peekable",
	"get", "get_mut", "entry", "or_insert", "or_insert_with", "remove_entry",
	"keys", "values", "iter", "into_keys", "into_values",
	"with_capacity", "from", "into", "new", "default",
	"join", "split", "split_whitespace", "lines", "trim", "trim_start", "trim_end",
	"starts_with", "ends_with", "replace", "replacen", "to_lowercase", "to_uppercase",
	"chars", "bytes", "as_bytes", "as_ptr", "to_owned",
	"read_to_string", "read_to_end", "write_all", "write_fmt", "flush",
	"open", "create", "metadata", "exists", "is_file", "is_dir", "read_dir",
	"args", "current_dir", "set_current_dir", "var", "vars",
	"spawn", "spawn_blocking", "sleep", "thread::spawn",
	"main",
];

CodeMirror.registerHelper("hint", "rust", (cm) => {
	const cursor = cm.getCursor();
	const token = cm.getTokenAt(cursor);
	const wordMatch = token.string.match(/[\w$]+/);
	if (!wordMatch) return null;
	const wordIdx = token.string.indexOf(wordMatch[0]);
	const start = token.start + wordIdx;
	const end = token.start + wordIdx + wordMatch[0].length;
	const currentWord = wordMatch[0];
	const list = RUST_KEYWORDS.filter((item) => item.lastIndexOf(currentWord, 0) === 0);
	if (list.length === 0) return null;
	return { list, from: CodeMirror.Pos(cursor.line, start), to: CodeMirror.Pos(cursor.line, end) };
});
