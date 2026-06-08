let cmEditor = null;
let ctrlActive = false;
let ctrlTimeout = null;
let currentFile = { item: null, filename: null };
let fileTreeOpen = false;
let activePanel = "explorer";
let _settingsVisible = false;
let activeExts = new Set([".py"]);
let _cachedAllFiles = [];
let solutionVisible = false;
let userContent = "";
let _beforeRunHook = null;
let _toggleTerminalHook = null;
let _lastTerminalToggle = 0;

function setBeforeRunHook(fn) {
	_beforeRunHook = fn;
}

function setToggleTerminalHook(fn) {
	_toggleTerminalHook = fn;
}

function _loadLangs() {
	try {
		const saved = localStorage.getItem("interview-prep-langs");
		if (saved) {
			const arr = JSON.parse(saved);
			if (Array.isArray(arr) && arr.length > 0) {
				activeExts = new Set(arr);
				if (document.getElementById("lang-selector")) _syncLangButtons();
			}
		}
	} catch {}
}

function _saveLangs() {
	localStorage.setItem("interview-prep-langs", JSON.stringify([...activeExts]));
}

function _syncLangButtons() {
	document.querySelectorAll("#lang-selector .lang-btn").forEach((btn) => {
		btn.classList.toggle("active", activeExts.has(btn.dataset.ext));
	});
}

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
	} catch {}
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
	if (explorer) {
		explorer.classList.toggle("text-blue-400", panel === "explorer");
		explorer.classList.toggle("border-l-2", panel === "explorer");
		explorer.classList.toggle("border-blue-400", panel === "explorer");
	}
	if (history) {
		history.classList.toggle("text-orange-400", panel === "history");
		history.classList.toggle("border-l-2", panel === "history");
		history.classList.toggle("border-orange-400", panel === "history");
	}
	if (settings) {
		settings.classList.toggle("text-purple-400", panel === "settings");
		settings.classList.toggle("border-l-2", panel === "settings");
		settings.classList.toggle("border-purple-400", panel === "settings");
	}
}

function toggleFileTree() {
	_settingsVisible = false;
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
	_settingsVisible = true;
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

let _settingsPanelExtraHtml = "";
let _settingsPanelExtraBind = null;

function registerSettingsPanelExtra(htmlFn, bindFn) {
	_settingsPanelExtraHtml = htmlFn;
	_settingsPanelExtraBind = bindFn;
}

function _showSettingsPanel() {
	_showSettingsPanelCore();
}

function _showSettingsPanelCore() {
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

	const langCheckbox = (label, ext) =>
		`<label class="flex items-center gap-2 text-zinc-300 text-sm py-1 cursor-pointer">
			<input type="checkbox" data-lang="${ext}" ${activeExts.has(ext) ? "checked" : ""}
				class="accent-blue-500 w-3.5 h-3.5 cursor-pointer">
			${label}
		</label>`;

	const extraHtml = _settingsPanelExtraHtml ? _settingsPanelExtraHtml() : "";

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
			<div class="border-t border-zinc-800 pt-2">
				<div class="text-zinc-400 text-xs mb-1">Languages</div>
				${langCheckbox("Python", ".py")}
				${langCheckbox("C", ".c")}
				${langCheckbox("C++", ".cpp")}
				${langCheckbox("Rust", ".rs")}
				${langCheckbox("JavaScript", ".mjs")}
			</div>
			${extraHtml}
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

	tree.querySelectorAll("input[type=checkbox][data-lang]").forEach((el) => {
		el.addEventListener("change", (e) => {
			toggleExt(e.target.dataset.lang);
		});
	});

	if (_settingsPanelExtraBind) _settingsPanelExtraBind(tree);
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
	versions.forEach((v) => {
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
	_cachedAllFiles = data.files || [];
	_openEditorWithFiles(data.files.length > 0 ? data.files : [], "Code Editor");
}

async function openAllInProgress() {
	const res = await fetch("/api/files/in-progress");
	const data = await res.json();

	_cachedAllFiles = data.files || [];
	_openEditorWithFiles(data.files.length > 0 ? data.files : [], "Code Editor");
}

function _initEditor() {
	if (cmEditor) return;

	const container = document.getElementById("code-editor");
	if (!container) return;

	cmEditor = CodeMirror(container, {
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

	cmEditor.on("keydown", (cm, e) => {
		if ((e.ctrlKey || e.metaKey) && e.code === "Backquote") {
			e.preventDefault();
			_lastTerminalToggle = Date.now();
			if (_toggleTerminalHook) _toggleTerminalHook();
		}
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
		cm.showHint({
			hint: (cm) => {
				const mode = cm.getOption("mode");
				const customHint = CodeMirror.hint[mode] ? CodeMirror.hint[mode](cm) : null;
				const wordHint = CodeMirror.hint.anyword(cm);
				const combined = [
					...new Set([
						...(customHint ? customHint.list : []),
						...(wordHint ? wordHint.list : []),
					]),
				];
				if (combined.length === 0) return null;
				return {
					list: combined,
					from: customHint ? customHint.from : wordHint.from,
					to: customHint ? customHint.to : wordHint.to,
				};
			},
			completeSingle: false,
		});
	});

	_applyAllSettings();
}

function _openEditorWithFiles(files, title, focus) {
	const card = document.getElementById("editor-card");
	if (card) {
		card.classList.remove("hidden");
	}

	const titleEl = document.getElementById("editor-title");
	if (titleEl) titleEl.textContent = title;

	_initEditor();

	_renderFileTree(files);
	if (!fileTreeOpen) {
		fileTreeOpen = true;
		document.getElementById("file-tree").classList.remove("hidden");
	}
	_setActivePanel("explorer");

	const firstFiltered = _cachedAllFiles.find((f) =>
		_matchesActiveExts(f.name),
	);
	if (firstFiltered) {
		loadFile(firstFiltered.item, firstFiltered.name).then(() => {
			const card = document.getElementById("editor-card");
			if (card) card.scrollIntoView({ behavior: "smooth", block: "start" });
		});
	}
}

function toggleExt(ext) {
	if (activeExts.has(ext)) {
		if (activeExts.size > 1) activeExts.delete(ext);
	} else {
		activeExts.add(ext);
	}
	_syncLangButtons();
	_saveLangs();
	_renderCachedFiles();
}

const LANG_TABS = [
	{ ext: ".py", label: "Python" },
	{ ext: ".c", label: "C" },
	{ ext: ".cpp", label: "C++" },
	{ ext: ".rs", label: "Rust" },
	{ ext: ".mjs", label: "JavaScript" },
	{ ext: ".md", label: "Markdown" },
];

function _renderFileTree(files) {
	_cachedAllFiles = files;
	_renderCachedFiles();
}

function _renderCachedFiles() {
	if (_settingsVisible) return;
	const tree = document.getElementById("file-tree");
	if (!tree) return;
	const filtered = _cachedAllFiles.filter((f) =>
		_matchesActiveExts(f.name),
	);

	if (filtered.length === 0) {
		tree.innerHTML = `
			<div class="tree-group">No files</div>
			<div class="px-3 py-2 text-xs text-zinc-500 leading-relaxed">
				No problems loaded yet. Start a topic on the
				<a href="/#details" class="text-blue-400 hover:text-blue-300 underline">dashboard</a>
				and its files will show up here.
			</div>`;
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
			html += `<div class="tree-item" data-file="${key}" onclick="loadFile('${item}','${name}')" title="${name}">${name}</div>`;
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
	_hideHint();
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

	const filenameDisplay = document.getElementById("current-filename");
	if (filenameDisplay) filenameDisplay.textContent = filename;
}

// biome-ignore lint/correctness/noUnusedVariables: called from HTML onclick
async function toggleHint() {
	if (!currentFile.item || !currentFile.filename) return;

	if (solutionVisible) {
		_hideHint();
		return;
	}

	try {
		const res = await fetch(
			`/api/files/solution?name=${encodeURIComponent(currentFile.item)}&file=${encodeURIComponent(currentFile.filename)}`,
		);
		if (!res.ok) {
			const data = await res.json().catch(() => ({}));
			showToast(data.detail || "No solution available");
			return;
		}
		const data = await res.json();
		userContent = cmEditor.getValue();
		cmEditor.setValue(data.content);
		cmEditor.setOption("mode", data.language || "text");
		cmEditor.setOption("readOnly", true);
		cmEditor.clearHistory();

		solutionVisible = true;
		const hintBtn = document.getElementById("hint-btn");
		const hintLabel = document.getElementById("hint-label");
		if (hintBtn) {
			hintBtn.classList.remove("bg-purple-600", "hover:bg-purple-500");
			hintBtn.classList.add("bg-purple-800");
		}
		if (hintLabel) hintLabel.textContent = "Hide";

		const saveBtn = document.getElementById("save-btn");
		const runBtn = document.getElementById("run-btn");
		if (saveBtn) saveBtn.disabled = true;
		if (runBtn) runBtn.disabled = true;
	} catch (err) {
		showToast("Error: " + err.message);
	}
}

function _hideHint() {
	if (!solutionVisible) return;
	solutionVisible = false;

	if (userContent !== undefined && cmEditor) {
		cmEditor.setValue(userContent);
		cmEditor.setOption("readOnly", false);
		cmEditor.clearHistory();
		cmEditor.markClean();
		_updateSaveBtn();
	}
	userContent = "";

	const hintBtn = document.getElementById("hint-btn");
	const hintLabel = document.getElementById("hint-label");
	if (hintBtn) {
		hintBtn.classList.remove("bg-purple-800");
		hintBtn.classList.add("bg-purple-600", "hover:bg-purple-500");
	}
	if (hintLabel) hintLabel.textContent = "Hint";

	const saveBtn = document.getElementById("save-btn");
	const runBtn = document.getElementById("run-btn");
	if (saveBtn) saveBtn.disabled = false;
	if (runBtn) runBtn.disabled = false;
}

// biome-ignore lint/correctness/noUnusedVariables: called from HTML onclick
function toggleEditorBody() {
	const body = document.getElementById("editor-body");
	const actions = document.getElementById("editor-actions");
	if (!body || !actions) return;
	const hidden = body.classList.toggle("hidden");
	actions.querySelectorAll("button:not(#editor-toggle-btn)").forEach((b) => {
		b.classList.toggle("hidden", hidden);
	});
	const toggleIcon = document.getElementById("toggle-icon");
	if (toggleIcon) {
		toggleIcon.innerHTML = hidden
			? '<path stroke-linecap="round" stroke-linejoin="round" d="M19.5 8.25l-7.5 7.5-7.5-7.5"/>'
			: '<path stroke-linecap="round" stroke-linejoin="round" d="M4.5 15.75l7.5-7.5 7.5 7.5"/>';
	}
}

function _updateSaveBtn() {
	const label = document.getElementById("save-label");
	const btn = document.getElementById("save-btn");
	if (!cmEditor || !btn) return;
	const clean = cmEditor.isClean();
	if (label) label.textContent = clean ? "Saved" : "Save";
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
	if (btn) btn.disabled = true;
	if (label) label.textContent = "Saving...";

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
		if (btn) btn.disabled = false;
		_updateSaveBtn();
	}
}

// biome-ignore lint/correctness/noUnusedVariables: called from HTML onclick
async function runProblems() {
	if (_beforeRunHook) _beforeRunHook();

	const termBody = document.getElementById("terminal-body");
	if (!termBody) return;
	termBody.innerHTML =
		'<div class="text-zinc-500 animate-pulse">Running problems...</div>';

	try {
		const langMap = { ".py": "py", ".c": "c", ".cpp": "cpp", ".rs": "rs", ".mjs": "js" };
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
	if (!body) return;
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
		else if (line.includes("[DEBUG]")) colorClass = "text-zinc-500 italic";
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

function copyTerminal() {
	const termBody = document.getElementById("terminal-body");
	if (!termBody) return;
	const text = termBody.innerText || termBody.textContent || "";
	if (!text.trim()) {
		showToast("Nothing to copy");
		return;
	}
	navigator.clipboard.writeText(text).then(
		() => showToast("Copied to clipboard"),
		() => showToast("Failed to copy"),
	);
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
