const C_KEYWORDS = [
	"auto", "break", "case", "char", "const", "continue", "default", "do", "double",
	"else", "enum", "extern", "float", "for", "goto", "if", "inline", "int", "long",
	"register", "restrict", "return", "short", "signed", "sizeof", "static", "struct",
	"switch", "typedef", "union", "unsigned", "void", "volatile", "while",
	"alignas", "alignof", "bool", "constexpr", "false", "nullptr",
	"static_assert", "thread_local", "true", "typeof",
	"_Alignas", "_Alignof", "_Atomic", "_Bool", "_Generic", "_Noreturn",
	"_Static_assert", "_Thread_local",
	"NULL", "EOF", "FILE", "size_t", "ssize_t", "ptrdiff_t",
	"intptr_t", "uintptr_t", "int8_t", "int16_t", "int32_t", "int64_t",
	"uint8_t", "uint16_t", "uint32_t", "uint64_t", "intmax_t", "uintmax_t",
	"INT_MAX", "INT_MIN", "LONG_MAX", "UINT_MAX", "SIZE_MAX", "CHAR_BIT",
	"NAN", "INFINITY", "M_PI",
	"printf", "fprintf", "sprintf", "snprintf", "scanf", "fscanf", "sscanf",
	"fopen", "fclose", "fgets", "fputs", "fread", "fwrite", "fseek", "ftell",
	"rewind", "feof", "ferror", "fflush", "fputc", "fgetc", "ungetc",
	"puts", "getchar", "putchar", "perror", "remove", "rename", "tmpfile",
	"vprintf", "vfprintf", "vsprintf", "vsnprintf",
	"malloc", "calloc", "realloc", "free", "atoi", "atol", "atof",
	"strtol", "strtoul", "strtod", "strtof", "abort", "exit", "atexit",
	"system", "rand", "srand", "abs", "labs", "div", "ldiv", "qsort", "bsearch", "getenv",
	"strlen", "strcpy", "strncpy", "strcat", "strncat", "strcmp", "strncmp",
	"strchr", "strrchr", "strstr", "strtok", "strdup", "strerror",
	"memcpy", "memmove", "memset", "memcmp", "memchr",
	"sqrt", "pow", "fabs", "ceil", "floor", "round",
	"sin", "cos", "tan", "asin", "acos", "atan", "atan2",
	"exp", "log", "log10", "log2", "fmod", "hypot", "isnan", "isinf",
	"isalpha", "isdigit", "isalnum", "isspace", "isupper", "islower",
	"toupper", "tolower", "isprint", "ispunct", "isxdigit", "iscntrl",
	"assert", "main",
];

CodeMirror.registerHelper("hint", "text/x-csrc", (cm) => {
	const cursor = cm.getCursor();
	const token = cm.getTokenAt(cursor);
	const wordMatch = token.string.match(/[\w$]+/);
	if (!wordMatch) return null;
	const wordIdx = token.string.indexOf(wordMatch[0]);
	const start = token.start + wordIdx;
	const end = token.start + wordIdx + wordMatch[0].length;
	const currentWord = wordMatch[0];
	const list = C_KEYWORDS.filter((item) => item.lastIndexOf(currentWord, 0) === 0);
	if (list.length === 0) return null;
	return { list, from: CodeMirror.Pos(cursor.line, start), to: CodeMirror.Pos(cursor.line, end) };
});
