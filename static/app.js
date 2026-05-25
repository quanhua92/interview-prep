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

_restoreFilters();
filterItems();
_loadLangs();
_initEditor();
openAllInProgress();
