#!/usr/bin/env node
/**
 * E2E test: run patterns via HTTP API, one lang at a time.
 *
 * Usage:
 *   node scripts/e2e-test.mjs                         # all patterns, Python solutions
 *   node scripts/e2e-test.mjs sliding_window           # one pattern, Python solutions
 *   node scripts/e2e-test.mjs --all                    # all patterns, Python solutions
 *   node scripts/e2e-test.mjs --all --problems         # all patterns, Python problems (stubs)
 *   node scripts/e2e-test.mjs --all --all-langs        # all patterns, all languages, solutions
 *   node scripts/e2e-test.mjs sliding_window two_pointers  # specific patterns
 */

const BASE = process.env.BASE_URL || "http://localhost:8888";
const TIMEOUT_MS = parseInt(process.env.TIMEOUT_MS || "300000", 10); // 5min per request

const LANGS = ["py", "c", "cpp", "rs", "js"];
const PATTERNS = [
  "sliding_window", "two_pointers", "bfs", "fast_slow_pointers",
  "merge_intervals", "binary_search", "bit_manipulation", "dfs",
  "divide_and_conquer", "dynamic_programming", "prefix_sum", "stack",
  "top_k_elements", "two_heaps", "backtracking", "cyclic_sort",
  "modified_binary_search", "subsets", "trie", "graph", "greedy",
  "matrix_traversal", "monotonic_stack", "union_find", "hashmap",
  "string", "design", "math", "randomized",
];

function parseSummary(text) {
  const totalMatch = text.match(/TOTAL:\s*(\d+)\s+passed,\s*(\d+)\s+failed,\s*(\d+)\s+skipped/);
  const passed = totalMatch ? parseInt(totalMatch[1], 10) : 0;
  const failed = totalMatch ? parseInt(totalMatch[2], 10) : 0;
  const skipped = totalMatch ? parseInt(totalMatch[3], 10) : 0;
  const failures = [...text.matchAll(/\[FAIL\]/g)].length;
  return { passed, failed, skipped, failures };
}

async function run(lang, pattern, isSolution) {
  const params = new URLSearchParams({ pattern });
  if (isSolution) params.set("solution", "true");
  params.append("lang", lang);
  const url = `${BASE}/api/run?${params}`;
  const controller = new AbortController();
  const timer = setTimeout(() => controller.abort(), TIMEOUT_MS);

  const res = await fetch(url, {
    method: "POST",
    signal: controller.signal,
  });
  clearTimeout(timer);

  if (!res.ok) {
    const text = await res.text();
    return { error: `HTTP ${res.status}: ${text.slice(0, 200)}` };
  }

  const data = await res.json();
  if (data.error) return { error: data.error };

  const result = data.results?.[0];
  if (!result) return { error: "no result returned" };
  if (result.exit_code === -1) return { error: result.error || "timed out" };

  const summary = parseSummary(result.output || "");
  return {
    passed: summary.passed,
    failed: summary.failed,
    skipped: summary.skipped,
    failures: summary.failures,
    exitCode: result.exit_code,
    output: result.output,
  };
}

function fmt(label, ok, elapsed) {
  const status = ok ? "PASS" : "FAIL";
  return `  ${status}  ${label.padEnd(30)} ${elapsed.toFixed(1).padStart(6)}s`;
}

async function main() {
  const args = process.argv.slice(2);
  const flags = args.filter((a) => a.startsWith("--"));
  const positional = args.filter((a) => !a.startsWith("--"));

  const patterns = flags.includes("--all") ? PATTERNS : positional;
  const langs = flags.includes("--all-langs") ? LANGS : ["py"];
  const isSolution = !flags.includes("--problems");
  const items = patterns.flatMap((p) => langs.map((l) => [p, l]));

  let totalOk = 0, totalFail = 0, totalTime = 0;

  for (const [pattern, lang] of items) {
    const label = `${pattern} (${lang})`;
    process.stdout.write(`  ${label.padEnd(32)} ... `);

    const t0 = Date.now();
    const r = await run(lang, pattern, isSolution);
    const elapsed = (Date.now() - t0) / 1000;

    if (r.error) {
      console.log(`FAIL  ${elapsed.toFixed(1)}s  ${r.error}`);
      totalFail++;
    } else if (r.failures > 0 || r.exitCode !== 0) {
      console.log(`FAIL  ${elapsed.toFixed(1)}s  ${r.failed}/${r.passed + r.failed} failed`);
      totalFail++;
    } else if (r.skipped > 0) {
      console.log(`PASS  ${elapsed.toFixed(1)}s  ${r.passed} passed, ${r.skipped} skipped`);
      totalOk++;
    } else {
      console.log(`PASS  ${elapsed.toFixed(1)}s  ${r.passed} passed`);
      totalOk++;
    }
    totalTime += elapsed;
  }

  console.log(`\n  ${totalOk} passed, ${totalFail} failed, ${totalTime.toFixed(1)}s total`);
  process.exit(totalFail > 0 ? 1 : 0);
}

main().catch((e) => {
  console.error("Fatal:", e);
  process.exit(1);
});
