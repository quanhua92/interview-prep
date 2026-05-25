function _saveFilters() {
	const checked = [...document.querySelectorAll(".status-filter:checked")].map(
		(c) => c.value,
	);
	localStorage.setItem("filters", JSON.stringify(checked));
}

function _restoreFilters() {
	const saved = localStorage.getItem("filters");
	if (!saved) return;
	const checked = JSON.parse(saved);
	document.querySelectorAll(".status-filter").forEach((cb) => {
		cb.checked = checked.includes(cb.value);
	});
}

function filterItems() {
	_saveFilters();
	const checked = new Set(
		[...document.querySelectorAll(".status-filter:checked")].map(
			(c) => c.value,
		),
	);
	const query = (document.getElementById("search-input")?.value || "")
		.toLowerCase()
		.trim();
	document.querySelectorAll("[data-section]").forEach((section) => {
		const rows = section.querySelectorAll("[data-status][data-name]");
		let visible = 0;
		rows.forEach((el) => {
			const matchStatus = checked.has(el.dataset.status);
			const matchSearch = !query || el.dataset.name.includes(query);
			el.style.display = matchStatus && matchSearch ? "" : "none";
			if (matchStatus && matchSearch) visible++;
		});
		section.style.display = visible ? "" : "none";
	});
}

// biome-ignore lint/correctness/noUnusedVariables: called from HTML onclick
async function updateStatus(name, status) {
	await fetch("/api/update", {
		method: "POST",
		headers: { "Content-Type": "application/json" },
		body: JSON.stringify({ name: name, status: status }),
	});
	location.reload();
}

// biome-ignore lint/correctness/noUnusedVariables: called from HTML onclick
async function recordAttempt(name) {
	await fetch("/api/attempt", {
		method: "POST",
		headers: { "Content-Type": "application/json" },
		body: JSON.stringify({ name: name }),
	});
	location.reload();
}

// biome-ignore lint/correctness/noUnusedVariables: called from HTML onclick
async function downloadTracker() {
	const res = await fetch("/api/tracker");
	const data = await res.json();
	const blob = new Blob([JSON.stringify(data, null, 2)], {
		type: "application/json",
	});
	const url = URL.createObjectURL(blob);
	const a = document.createElement("a");
	a.href = url;
	a.download = "tracker.json";
	a.click();
	URL.revokeObjectURL(url);
}

// biome-ignore lint/correctness/noUnusedVariables: called from HTML onclick
async function runProblems() {
	const termBody = document.getElementById("terminal-body");
	termBody.innerHTML =
		'<div class="text-zinc-500 animate-pulse">Running problems...</div>';

	try {
		const langMap = { ".py": "py", ".c": "c", ".cpp": "cpp", ".rs": "rs" };
		const langs = [...activeExts].map((ext) => langMap[ext]).filter(Boolean);
		if (langs.length === 0) {
			termBody.innerHTML = '<div class="text-zinc-500">No coding languages selected</div>';
			return;
		}
		const langParams = langs.map((l) => `lang=${l}`).join("&");
		const res = await fetch(`/api/run?${langParams}`, { method: "POST" });
		const data = await res.json();
		if (res.ok && data.results) {
			let fullOutput = "";
			for (const r of data.results) {
				if (langs.length > 1) fullOutput += `=== ${r.lang.toUpperCase()} ===\n`;
				fullOutput += r.output || r.error || "";
				if (r !== data.results[data.results.length - 1]) fullOutput += "\n";
			}
			renderTerminalOutput(fullOutput);
		} else {
			const msg = data.detail || "Unknown error";
			termBody.innerHTML = `<div class="text-red-400">Error: ${msg}</div>`;
		}
	} catch (err) {
		termBody.innerHTML = `<div class="text-red-400">Error: ${err.message}</div>`;
	}
}

function renderTerminalOutput(output) {
	const body = document.getElementById("terminal-body");
	if (!output) {
		body.innerHTML = '<div class="text-zinc-500">No output.</div>';
		return;
	}

	const lines = output.split("\n");
	let html = "";
	for (const line of lines) {
		if (!line.trim()) {
			html += '<div class="h-3"></div>';
			continue;
		}
		let colorClass = "text-zinc-300";
		if (line.includes("[PASS]")) colorClass = "text-emerald-400";
		else if (line.includes("[FAIL]")) colorClass = "text-red-400";
		else if (line.includes("[SKIP]")) colorClass = "text-amber-400";
		else if (line.startsWith("  !")) colorClass = "text-red-300/70";
		else if (line.includes("Timed out")) colorClass = "text-red-400 font-bold";
		else if (line.includes("TOTAL:")) colorClass = "text-white font-bold";

		const escaped = line
			.replace(/&/g, "&amp;")
			.replace(/</g, "&lt;")
			.replace(/>/g, "&gt;");
		html += `<div class="${colorClass}">${escaped}</div>`;
	}

	body.innerHTML = html;
	body.scrollTop = body.scrollHeight;
}

_restoreFilters();
filterItems();

// --- Editor ---

let cmEditor = null;
let ctrlActive = false;
let ctrlTimeout = null;

document.addEventListener("keydown", (e) => {
	if (e.ctrlKey || e.metaKey) {
		ctrlActive = true;
		clearTimeout(ctrlTimeout);
	}
});
document.addEventListener("keyup", (e) => {
	if (!e.ctrlKey && !e.metaKey) {
		ctrlTimeout = setTimeout(() => {
			ctrlActive = false;
		}, 500);
	}
});
let currentFile = { item: null, filename: null };
let fileTreeOpen = false;
let activePanel = "explorer";
let activeExts = new Set([".py"]);
let _cachedAllFiles = [];

function _matchesActiveExts(filename) {
	if (filename.endsWith(".md")) return true;
	return [...activeExts].some((ext) => filename.endsWith(ext));
}

const SETTINGS_KEY = "interview-prep-settings";
const DEFAULT_SETTINGS = {
	editorFontSize: 14,
	tabSize: 4,
	lineWrapping: true,
	autoCloseBrackets: true,
	matchBrackets: true,
	foldGutter: true,
	lineNumbers: true,
};

function _loadSettings() {
	try {
		const raw = localStorage.getItem(SETTINGS_KEY);
		if (raw) return { ...DEFAULT_SETTINGS, ...JSON.parse(raw) };
	} catch {
		/* ignore malformed JSON */
	}
	return { ...DEFAULT_SETTINGS };
}

function _saveSettings(settings) {
	localStorage.setItem(SETTINGS_KEY, JSON.stringify(settings));
}

function _updateSetting(key, value) {
	const settings = _loadSettings();
	settings[key] = value;
	_saveSettings(settings);
	return settings;
}

function _setActivePanel(panel) {
	activePanel = panel;
	const explorer = document.getElementById("explorer-btn");
	const history = document.getElementById("history-btn");
	const settings = document.getElementById("settings-btn");
	explorer.classList.toggle("text-blue-400", panel === "explorer");
	explorer.classList.toggle("border-l-2", panel === "explorer");
	explorer.classList.toggle("border-blue-400", panel === "explorer");
	history.classList.toggle("text-orange-400", panel === "history");
	history.classList.toggle("border-l-2", panel === "history");
	history.classList.toggle("border-orange-400", panel === "history");
	settings.classList.toggle("text-purple-400", panel === "settings");
	settings.classList.toggle("border-l-2", panel === "settings");
	settings.classList.toggle("border-purple-400", panel === "settings");
}

function toggleFileTree() {
	if (!fileTreeOpen) {
		fileTreeOpen = true;
		document.getElementById("file-tree").classList.remove("hidden");
		_setActivePanel("explorer");
		_reRenderFileTree();
	} else if (activePanel === "explorer") {
		fileTreeOpen = false;
		document.getElementById("file-tree").classList.add("hidden");
		_setActivePanel(null);
	} else {
		_setActivePanel("explorer");
		_reRenderFileTree();
	}
}

async function _reRenderFileTree() {
	const res = await fetch("/api/files/in-progress");
	const data = await res.json();
	_cachedAllFiles = data.files || [];
	_renderCachedFiles();
}

// biome-ignore lint/correctness/noUnusedVariables: called from HTML onclick
function toggleSettings() {
	if (!fileTreeOpen) {
		fileTreeOpen = true;
		document.getElementById("file-tree").classList.remove("hidden");
		_setActivePanel("settings");
		_showSettingsPanel();
	} else if (activePanel === "settings") {
		fileTreeOpen = false;
		document.getElementById("file-tree").classList.add("hidden");
		_setActivePanel(null);
	} else {
		_setActivePanel("settings");
		_showSettingsPanel();
	}
}

function _showSettingsPanel() {
	const tree = document.getElementById("file-tree");
	const s = _loadSettings();

	const fontSizes = [8, 9, 10, 11, 12, 14, 16, 18, 20, 24];
	const fontOptions = fontSizes
		.map(
			(v) =>
				`<option value="${v}" ${v === s.editorFontSize ? "selected" : ""}>${v}px</option>`,
		)
		.join("");

	const tabSizes = [2, 4, 8];
	const tabOptions = tabSizes
		.map(
			(v) =>
				`<option value="${v}" ${v === s.tabSize ? "selected" : ""}>${v}</option>`,
		)
		.join("");

	const checkbox = (label, key) =>
		`<label class="flex items-center gap-2 text-zinc-300 text-sm py-1 cursor-pointer">
			<input type="checkbox" data-setting="${key}" ${s[key] ? "checked" : ""}
				class="accent-purple-500 w-3.5 h-3.5 cursor-pointer">
			${label}
		</label>`;

	tree.innerHTML = `
		<div class="tree-group">Settings</div>
		<div class="px-3 py-2 space-y-3">
			<div>
				<label class="block text-zinc-400 mb-1 text-xs">Font Size</label>
				<select data-setting="editorFontSize"
					class="w-full bg-zinc-800 border border-zinc-700 rounded px-2 py-1.5 text-sm text-white focus:outline-none focus:border-purple-500 cursor-pointer">
					${fontOptions}
				</select>
			</div>
			<div>
				<label class="block text-zinc-400 mb-1 text-xs">Tab Size</label>
				<select data-setting="tabSize"
					class="w-full bg-zinc-800 border border-zinc-700 rounded px-2 py-1.5 text-sm text-white focus:outline-none focus:border-purple-500 cursor-pointer">
					${tabOptions}
				</select>
			</div>
			<div class="border-t border-zinc-800 pt-2">
				${checkbox("Line Numbers", "lineNumbers")}
				${checkbox("Line Wrapping", "lineWrapping")}
				${checkbox("Auto Close Brackets", "autoCloseBrackets")}
				${checkbox("Match Brackets", "matchBrackets")}
				${checkbox("Code Folding", "foldGutter")}
			</div>
		</div>
	`;

	tree.querySelectorAll("select[data-setting]").forEach((el) => {
		el.addEventListener("change", (e) => {
			_updateSetting(e.target.dataset.setting, Number(e.target.value));
			_applyAllSettings();
		});
	});

	tree.querySelectorAll("input[type=checkbox][data-setting]").forEach((el) => {
		el.addEventListener("change", (e) => {
			_updateSetting(e.target.dataset.setting, e.target.checked);
			_applyAllSettings();
		});
	});
}

function _applyAllSettings() {
	if (!cmEditor) return;
	const s = _loadSettings();
	cmEditor.getWrapperElement().style.fontSize = `${s.editorFontSize}px`;
	cmEditor.setOption("tabSize", s.tabSize);
	cmEditor.setOption("indentUnit", s.tabSize);
	cmEditor.setOption("lineWrapping", s.lineWrapping);
	cmEditor.setOption("autoCloseBrackets", s.autoCloseBrackets);
	cmEditor.setOption("matchBrackets", s.matchBrackets);
	cmEditor.setOption("foldGutter", s.foldGutter);
	cmEditor.setOption("lineNumbers", s.lineNumbers);
	cmEditor.refresh();
}

// biome-ignore lint/correctness/noUnusedVariables: called from HTML onclick
async function revertFile() {
	if (!currentFile.item || !currentFile.filename) {
		showToast("No file open");
		return;
	}

	try {
		const res = await fetch(
			`/api/files/history?name=${encodeURIComponent(currentFile.item)}&file=${encodeURIComponent(currentFile.filename)}`,
		);
		const data = await res.json();
		if (!data.versions || data.versions.length === 0) {
			showToast("No versions available");
			return;
		}
		_showHistoryPanel(data.versions);
	} catch (err) {
		showToast("Error: " + err.message);
	}
}

function _showHistoryPanel(versions) {
	const tree = document.getElementById("file-tree");
	if (!fileTreeOpen) {
		fileTreeOpen = true;
		tree.classList.remove("hidden");
	}
	_setActivePanel("history");

	let html = `<div class="tree-group">History</div>`;
	versions.forEach((v, i) => {
		html += `<div class="tree-item" onclick="revertToVersion('${v.label}')">${v.label}</div>`;
	});
	tree.innerHTML = html;
}

async function revertToVersion(label) {
	if (!currentFile.item || !currentFile.filename) return;

	try {
		const res = await fetch(
			`/api/files/revert?name=${encodeURIComponent(currentFile.item)}&file=${encodeURIComponent(currentFile.filename)}&label=${encodeURIComponent(label)}`,
			{ method: "POST" },
		);
		if (res.ok) {
			await loadFile(currentFile.item, currentFile.filename);
			showToast("Reverted");
			revertFile();
		} else {
			const data = await res.json();
			showToast("Error: " + (data.detail || "Revert failed"));
		}
	} catch (err) {
		showToast("Error: " + err.message);
	}
}

function _fileKey(item, filename) {
	return `${item}/${filename}`;
}

// biome-ignore lint/correctness/noUnusedVariables: called from HTML onclick
async function openEditor(itemName) {
	const res = await fetch(`/api/files/ls?name=${encodeURIComponent(itemName)}`);
	const data = await res.json();

	if (!data.has_files || data.files.length === 0) {
		showToast("No editable files for this topic");
		return;
	}

	const files = data.files.map((f) => ({ item: itemName, name: f.name }));
	_openEditorWithFiles(
		files,
		itemName.replace(/_/g, " ").replace(/\b\w/g, (c) => c.toUpperCase()),
	);
}

async function openAllInProgress() {
	const res = await fetch("/api/files/in-progress");
	const data = await res.json();

	if (!data.files || data.files.length === 0) return;
	_openEditorWithFiles(data.files, "Code Editor");
}

function _openEditorWithFiles(files, title) {
	const card = document.getElementById("editor-card");
	card.classList.remove("hidden");
	card.scrollIntoView({ behavior: "smooth", block: "start" });

	document.getElementById("editor-title").textContent = title;

	_renderFileTree(files);
	if (!fileTreeOpen) {
		fileTreeOpen = true;
		document.getElementById("file-tree").classList.remove("hidden");
	}
	_setActivePanel("explorer");

	if (!cmEditor) {
		cmEditor = CodeMirror(document.getElementById("code-editor"), {
			value: "",
			mode: "python",
			theme: "material-darker",
			lineNumbers: true,
			indentUnit: 4,
			tabSize: 4,
			indentWithTabs: false,
			lineWrapping: true,
			autoCloseBrackets: true,
			matchBrackets: true,
			foldGutter: true,
			gutters: ["CodeMirror-linenumbers", "CodeMirror-foldgutter"],
			extraKeys: {
				"Ctrl-S": () => saveFile(),
				"Cmd-S": () => saveFile(),
				"Ctrl-R": () => runProblems(),
				"Cmd-R": () => runProblems(),
				Tab: (cm) => {
					if (cm.somethingSelected()) {
						cm.indentSelection("add");
					} else {
						cm.replaceSelection(" ".repeat(cm.getOption("indentUnit")), "end");
					}
				},
				"Shift-Tab": (cm) => cm.indentSelection("subtract"),
				"Ctrl-/": (cm) => cm.toggleComment({ indent: true }),
				"Cmd-/": (cm) => cm.toggleComment({ indent: true }),
			},
		});

		cmEditor.on("endCompletion", (cm) => {
			requestAnimationFrame(() => cm.focus());
		});

		cmEditor.on("change", () => _updateSaveBtn());

		cmEditor.on("inputRead", (cm, change) => {
			if (ctrlActive) return;
			if (
				change.origin === "paste" ||
				(change.origin === "+input" && change.text.length > 1)
			)
				return;
			if (change.origin === "+delete") return;
			if (
				change.text[0] === " " ||
				change.text[0] === ":" ||
				change.text[0] === ")" ||
				change.text[0] === "]" ||
				change.text[0] === "}" ||
				change.text[0] === "," ||
				change.text[0] === "'" ||
				change.text[0] === '"'
			)
				return;
			const isPython = cm.getOption("mode") === "python";
			if (!isPython) {
				cm.showHint({
					hint: CodeMirror.hint.anyword,
					completeSingle: false,
				});
				return;
			}
			cm.showHint({
				hint: (cm) => {
					const customHint = CodeMirror.hint.python(cm);
					const wordHint = CodeMirror.hint.anyword(cm);
					const combined = [
						...new Set([
							...(customHint ? customHint.list : []),
							...(wordHint ? wordHint.list : []),
						]),
					];
					return {
						list: combined,
						from: customHint ? customHint.from : wordHint.from,
						to: customHint ? customHint.to : wordHint.to,
					};
				},
				completeSingle: false,
			});
		});
	}

	_applyAllSettings();
	const firstFiltered = _cachedAllFiles.find((f) =>
		_matchesActiveExts(f.name),
	);
	if (firstFiltered) loadFile(firstFiltered.item, firstFiltered.name);
}

function toggleExt(ext) {
	if (activeExts.has(ext)) {
		if (activeExts.size > 1) activeExts.delete(ext);
	} else {
		activeExts.add(ext);
	}
	document.querySelectorAll("#lang-selector .lang-btn").forEach((btn) => {
		btn.classList.toggle("active", activeExts.has(btn.dataset.ext));
	});
	_renderCachedFiles();
}

const LANG_TABS = [
	{ ext: ".py", label: "Python" },
	{ ext: ".c", label: "C" },
	{ ext: ".cpp", label: "C++" },
	{ ext: ".rs", label: "Rust" },
	{ ext: ".md", label: "Markdown" },
];

function _renderFileTree(files) {
	_cachedAllFiles = files;
	_renderCachedFiles();
}

function _renderCachedFiles() {
	const tree = document.getElementById("file-tree");
	const filtered = _cachedAllFiles.filter((f) =>
		_matchesActiveExts(f.name),
	);

	if (filtered.length === 0) {
		tree.innerHTML = '<div class="tree-group">No files</div>';
		return;
	}

	const grouped = {};
	for (const f of filtered) {
		if (!grouped[f.item]) grouped[f.item] = [];
		grouped[f.item].push(f.name);
	}

	let html = "";
	for (const [item, names] of Object.entries(grouped)) {
		const label = item
			.replace(/_/g, " ")
			.replace(/\b\w/g, (c) => c.toUpperCase());
		html += `<div class="tree-group">${label}</div>`;
		for (const name of names) {
			const key = _fileKey(item, name);
			html += `<div class="tree-item" data-file="${key}" onclick="loadFile('${item}','${name}')">${name}</div>`;
		}
	}

	tree.innerHTML = html;

	if (currentFile.item && currentFile.filename) {
		const key = _fileKey(currentFile.item, currentFile.filename);
		document.querySelectorAll("#file-tree .tree-item").forEach((el) => {
			el.classList.toggle("active", el.dataset.file === key);
		});
	}
}

async function loadFile(itemName, filename) {
	const key = _fileKey(itemName, filename);
	const res = await fetch(
		`/api/files/read?name=${encodeURIComponent(itemName)}&file=${encodeURIComponent(filename)}`,
	);
	const data = await res.json();

	cmEditor.setValue(data.content);
	cmEditor.setOption("mode", data.language || "text");
	cmEditor.clearHistory();
	cmEditor.markClean();
	_updateSaveBtn();
	_applyAllSettings();

	document.querySelectorAll("#file-tree .tree-item").forEach((el) => {
		el.classList.toggle("active", el.dataset.file === key);
	});

	currentFile = { item: itemName, filename: filename };
}

// biome-ignore lint/correctness/noUnusedVariables: called from HTML onclick
function toggleEditorBody() {
	const body = document.getElementById("editor-body");
	const actions = document.getElementById("editor-actions");
	const hidden = body.classList.toggle("hidden");
	actions.querySelectorAll("button:not(#editor-toggle-btn)").forEach((b) => {
		b.classList.toggle("hidden", hidden);
	});
	document.getElementById("toggle-icon").innerHTML = hidden
		? '<path stroke-linecap="round" stroke-linejoin="round" d="M19.5 8.25l-7.5 7.5-7.5-7.5"/>'
		: '<path stroke-linecap="round" stroke-linejoin="round" d="M4.5 15.75l7.5-7.5 7.5 7.5"/>';
}

function _updateSaveBtn() {
	const label = document.getElementById("save-label");
	const btn = document.getElementById("save-btn");
	if (!cmEditor) return;
	const clean = cmEditor.isClean();
	label.textContent = clean ? "Saved" : "Save";
	btn.classList.toggle("bg-blue-600", !clean);
	btn.classList.toggle("hover:bg-blue-500", !clean);
	btn.classList.toggle("bg-zinc-700", clean);
	btn.classList.toggle("hover:bg-zinc-600", clean);
}

// biome-ignore lint/correctness/noUnusedVariables: called from HTML onclick
async function saveFile() {
	if (!currentFile.item || !currentFile.filename) return;

	const btn = document.getElementById("save-btn");
	const label = document.getElementById("save-label");
	btn.disabled = true;
	label.textContent = "Saving...";

	try {
		const res = await fetch(
			`/api/files/write?name=${encodeURIComponent(currentFile.item)}&file=${encodeURIComponent(currentFile.filename)}`,
			{
				method: "POST",
				headers: { "Content-Type": "application/json" },
				body: JSON.stringify({ content: cmEditor.getValue() }),
			},
		);
		if (res.ok) {
			showToast("File saved");
			cmEditor.markClean();
			_updateSaveBtn();
			if (activePanel === "history") revertFile();
		} else {
			const data = await res.json();
			showToast("Error: " + (data.detail || "Save failed"));
		}
	} catch (err) {
		showToast("Error: " + err.message);
	} finally {
		btn.disabled = false;
		_updateSaveBtn();
	}
}

function showToast(message) {
	const existing = document.getElementById("toast");
	if (existing) existing.remove();

	const toast = document.createElement("div");
	toast.id = "toast";
	toast.className =
		"fixed bottom-6 left-1/2 -translate-x-1/2 px-4 py-2 bg-zinc-700 text-white text-sm rounded-lg shadow-lg z-50 transition-opacity duration-300";
	toast.textContent = message;
	document.body.appendChild(toast);
	setTimeout(() => {
		toast.style.opacity = "0";
		setTimeout(() => toast.remove(), 300);
	}, 2000);
}

// Auto-open editor with all in-progress files
openAllInProgress();

// Ctrl/Cmd+S to save, Ctrl/Cmd+R to run (also bound in CodeMirror extraKeys)
document.addEventListener("keydown", (e) => {
	if ((e.ctrlKey || e.metaKey) && e.key === "s") {
		e.preventDefault();
		saveFile();
	}
	if ((e.ctrlKey || e.metaKey) && e.key === "r") {
		e.preventDefault();
		runProblems();
	}
});
