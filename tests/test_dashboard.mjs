const BASE = process.argv[2] || "http://localhost:8888";

async function getJson(url) {
	const res = await fetch(url);
	return res.json();
}

async function postJson(url, body) {
	const res = await fetch(url, {
		method: "POST",
		headers: { "Content-Type": "application/json" },
		body: JSON.stringify(body),
	});
	return res.json();
}

let passed = 0;
let failed = 0;

function assert(condition, label) {
	if (condition) {
		console.log(`  ✓ ${label}`);
		passed++;
	} else {
		console.log(`  ✗ ${label}`);
		failed++;
	}
}

// GET / — dashboard HTML
console.log("GET /");
const html = await (await fetch(`${BASE}/`)).text();
assert(html.includes("<!DOCTYPE html>"), "returns HTML");
assert(html.includes("Interview Prep"), "has title");
assert(html.includes("Total Topics"), "has stats row");
assert(html.includes("Coding Patterns"), "has coding section");
assert(html.includes("updateStatus"), "has interactive JS");

// GET /api/tracker
console.log("\nGET /api/tracker");
const tracker = await getJson(`${BASE}/api/tracker`);
assert(Array.isArray(tracker.patterns), "has patterns array");
assert(tracker.patterns.length > 0, "patterns non-empty");
assert(tracker.patterns[0].name === "bfs", "patterns sorted");
assert(typeof tracker.patterns[0].status === "string", "items have status");

// POST /api/attempt
console.log("\nPOST /api/attempt");
const before = (await getJson(`${BASE}/api/tracker`)).patterns.find(
	(p) => p.name === "sliding_window",
);
const attemptRes = await postJson(`${BASE}/api/attempt`, {
	name: "sliding_window",
});
assert(attemptRes.ok === true, "succeeds");
assert(attemptRes.item.attempts === before.attempts + 1, "increments attempts");
assert(attemptRes.item.last_attempt !== null, "sets last_attempt");

// POST /api/update
console.log("\nPOST /api/update");
const updateRes = await postJson(`${BASE}/api/update`, {
	name: "sliding_window",
	status: "completed",
});
assert(updateRes.ok === true, "succeeds");
assert(updateRes.item.status === "completed", "changes status");
assert(typeof updateRes.old_status === "string", "returns old_status");

// Verify persistence
console.log("\nPersistence");
const after = (await getJson(`${BASE}/api/tracker`)).patterns.find(
	(p) => p.name === "sliding_window",
);
assert(after.status === "completed", "status persisted");
assert(after.attempts === updateRes.item.attempts, "attempts persisted");

// Reset
await postJson(`${BASE}/api/update`, {
	name: "sliding_window",
	status: "not_started",
});

// Error handling
console.log("\nErrors");
const badItem = await postJson(`${BASE}/api/update`, {
	name: "nonexistent",
	status: "completed",
});
assert(badItem.detail !== undefined, "unknown item fails");

const badStatus = await postJson(`${BASE}/api/update`, {
	name: "sliding_window",
	status: "bad",
});
assert(badStatus.detail !== undefined, "invalid status fails");

const res404 = await fetch(`${BASE}/nonexistent`);
assert(res404.status === 404, "404 for unknown path");

console.log(`\n${passed} passed, ${failed} failed`);
process.exit(failed > 0 ? 1 : 0);
