const CODE_SETTINGS_KEY = "code-settings";
const DEFAULTS = {
	layout: "bottom",
	termWidth: window.innerWidth <= 768 ? 250 : 450,
	termHeight: 350,
	termVisible: false,
};
const TERM_WIDTHS = [200, 250, 300, 350, 400, 450, 500, 550, 600, 700, 800];
const TERM_HEIGHTS = [150, 250, 350, 450, 550];

function _loadCodeSettings() {
	try {
		const raw = localStorage.getItem(CODE_SETTINGS_KEY);
		if (raw) return { ...DEFAULTS, ...JSON.parse(raw) };
	} catch {}
	return { ...DEFAULTS };
}

function _saveCodeSettings(s) {
	localStorage.setItem(CODE_SETTINGS_KEY, JSON.stringify(s));
}

function _getLayout() {
	return _loadCodeSettings().layout;
}

function _setLayout(layout) {
	const s = _loadCodeSettings();
	s.layout = layout;
	_saveCodeSettings(s);
	const card = document.getElementById("editor-card");
	card.className = card.className.replace(/layout-\w+/g, "").trim() + " layout-" + layout;
	_applyTermSize();
}

function _applyTermSize() {
	const s = _loadCodeSettings();
	const panel = document.getElementById("terminal-panel");
	if (!panel) return;
	panel.style.setProperty("--term-width", s.termWidth + "px");
	panel.style.setProperty("--term-height", s.termHeight + "px");
	if (cmEditor) setTimeout(() => cmEditor.refresh(), 50);
}

function _layoutSettingsHtml() {
	const s = _loadCodeSettings();
	const radio = (value, label) =>
		`<label class="flex items-center gap-2 text-zinc-300 text-sm py-1 cursor-pointer">
			<input type="radio" name="layout" value="${value}" ${s.layout === value ? "checked" : ""}
				class="accent-emerald-500 w-3.5 h-3.5 cursor-pointer">
			${label}
		</label>`;
	const selOpts = (vals, cur) =>
		vals.map((v) => `<option value="${v}" ${v === cur ? "selected" : ""}>${v}px</option>`).join("");
	return `
		<div class="border-t border-zinc-800 pt-2">
			<div class="text-zinc-400 text-xs mb-1">Terminal Position</div>
			${radio("right", "Right")}
			${radio("left", "Left")}
			${radio("bottom", "Bottom")}
			${radio("top", "Top")}
			<div class="border-t border-zinc-800 pt-2 mt-2">
				<div class="text-zinc-400 text-xs mb-1">Terminal Width</div>
				<select id="term-width-select"
					class="w-full bg-zinc-800 border border-zinc-700 rounded px-2 py-1.5 text-sm text-white focus:outline-none focus:border-emerald-500 cursor-pointer">
					${selOpts(TERM_WIDTHS, s.termWidth)}
				</select>
			</div>
			<div>
				<div class="text-zinc-400 text-xs mb-1">Terminal Height</div>
				<select id="term-height-select"
					class="w-full bg-zinc-800 border border-zinc-700 rounded px-2 py-1.5 text-sm text-white focus:outline-none focus:border-emerald-500 cursor-pointer">
					${selOpts(TERM_HEIGHTS, s.termHeight)}
				</select>
			</div>
		</div>`;
}

function _layoutSettingsBind(tree) {
	tree.querySelectorAll("input[name=layout]").forEach((el) => {
		el.addEventListener("change", (e) => {
			_setLayout(e.target.value);
		});
	});
	const widthSel = tree.querySelector("#term-width-select");
	if (widthSel) {
		widthSel.addEventListener("change", (e) => {
			const s = _loadCodeSettings();
			s.termWidth = Number(e.target.value);
			_saveCodeSettings(s);
			_applyTermSize();
		});
	}
	const heightSel = tree.querySelector("#term-height-select");
	if (heightSel) {
		heightSel.addEventListener("change", (e) => {
			const s = _loadCodeSettings();
			s.termHeight = Number(e.target.value);
			_saveCodeSettings(s);
			_applyTermSize();
		});
	}
}

function _showTerminal() {
	const panel = document.getElementById("terminal-panel");
	if (panel) panel.classList.remove("auto-hidden");
	const s = _loadCodeSettings();
	s.termVisible = true;
	_saveCodeSettings(s);
	if (cmEditor) setTimeout(() => cmEditor.refresh(), 50);
}

registerSettingsPanelExtra(_layoutSettingsHtml, _layoutSettingsBind);

setBeforeRunHook(() => {
	_showTerminal();
});

setToggleTerminalHook(() => {
	const panel = document.getElementById("terminal-panel");
	if (!panel) return;
	if (panel.classList.contains("auto-hidden")) {
		_showTerminal();
	} else {
		const s = _loadCodeSettings();
		s.termVisible = false;
		_saveCodeSettings(s);
		panel.classList.add("auto-hidden");
		if (cmEditor) setTimeout(() => cmEditor.refresh(), 50);
	}
});

document.addEventListener("keydown", (e) => {
	if ((e.ctrlKey || e.metaKey) && e.code === "Backquote") {
		e.preventDefault();
		if (Date.now() - _lastTerminalToggle < 300) return;
		_lastTerminalToggle = Date.now();
		if (_toggleTerminalHook) _toggleTerminalHook();
	}
});

const _init = _loadCodeSettings();
_setLayout(_init.layout);
_applyTermSize();
if (!_init.termVisible) {
	const panel = document.getElementById("terminal-panel");
	if (panel) panel.classList.add("auto-hidden");
}
_loadLangs();
_initEditor();
openAllInProgress();
