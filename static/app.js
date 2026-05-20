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

_restoreFilters();
filterByStatus();
