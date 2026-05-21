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

function filterByStatus() {
	_saveFilters();
	const checked = new Set(
		[...document.querySelectorAll(".status-filter:checked")].map(
			(c) => c.value,
		),
	);
	document.querySelectorAll("[data-status]").forEach((el) => {
		el.style.display = checked.has(el.dataset.status) ? "" : "none";
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
	const btn = document.getElementById("run-btn");
	const spinner = document.getElementById("run-spinner");
	const body = document.getElementById("terminal-body");

	btn.disabled = true;
	spinner.classList.remove("hidden");
	body.innerHTML = '<div class="text-zinc-500 animate-pulse">Running problems...</div>';

	try {
		const res = await fetch("/api/run", { method: "POST" });
		const data = await res.json();
		if (res.ok && data.output) {
			renderTerminalOutput(data.output);
		} else {
			const msg = data.detail || data.output || "Unknown error";
			body.innerHTML = `<div class="text-red-400">Error: ${msg}</div>`;
		}
	} catch (err) {
		body.innerHTML = `<div class="text-red-400">Error: ${err.message}</div>`;
	} finally {
		btn.disabled = false;
		spinner.classList.add("hidden");
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
filterByStatus();
