# Interview Q&A — LLM Training Engineer

Answer each **out loud**, 1–3 sentences. These are the questions the JD (*Fullstack LLM Engineer — Pre-training & Post-training*) will probe.

## Lifecycle
**Q: Walk me through the LLM training lifecycle.**
A: Pre-train (next-token prediction on trillions of tokens — you don't do this) → optional "mid-training" capability shaping → SFT on instruction pairs (makes it a chat model) → post-training alignment (DPO or RLHF/GRPO+RLVR) → eval → serve.

**Q: Pre-training vs fine-tuning vs post-training — what changes at each stage?**
A: Pre-training builds language fluency from raw text; fine-tuning/SFT adapts to a task from labeled instruction pairs; post-training aligns to preferences or verifiable rewards. Data, compute, and objective differ at each.

**Q: What would you actually do vs. never do at a startup?**
A: Start from an open base (Qwen3/Llama 4/DeepSeek), then SFT + DPO/GRPO + eval + serve. Never pre-train from scratch (costs $10M+) and avoid reward-model + PPO unless you have frontier-lab infra.

## LoRA / PEFT
**Q: What is LoRA?**
A: Freeze the base weights and train small low-rank adapter matrices (~1% of params); the update is `W + (α/r)·AB`. Near full-FT quality at a fraction of the VRAM, and adapters merge at inference for zero added latency.

**Q: QLoRA vs full fine-tuning — when which?**
A: QLoRA (4-bit base + LoRA) is the single-GPU default for small datasets and fast iteration, and preserves general capability. Full FT needs a multi-GPU cluster and suits continued pre-training or major domain shifts where LoRA plateaus.

**Q: DoRA vs PiSSA vs rsLoRA?**
A: DoRA decomposes weights into magnitude + direction and LoRAs the direction (best general upgrade); PiSSA initializes adapters from the top singular vectors (best if you can do the SVD); rsLoRA changes scaling to α/√r to stay stable at rank ≥64.

**Q: Your fine-tuned model regressed on general tasks — what do you do?**
A: Lower the LR, fewer epochs, switch to LoRA (less catastrophic forgetting than full FT), replay ~5–10% general data, and always re-run a general benchmark alongside the domain eval.

**Q: Which modules do you attach LoRA to and why?**
A: All seven linear modules (q/k/v/o + gate/up/down) — attention + MLP beats attention-only, per the QLoRA paper.

## Post-training / alignment
**Q: DPO vs RLHF?**
A: RLHF trains a reward model + PPO (4 models in memory, unstable). DPO skips both — it optimizes a single loss directly on chosen/rejected preference pairs, which is why it displaced RLHF in open work.

**Q: The DPO family — IPO, KTO, SimPO, ORPO?**
A: IPO adds regularization for noisy data; KTO works on unpaired thumbs-up/down; SimPO is reference-free and length-normalized (often beats DPO); ORPO fuses SFT + preference in one stage (no separate SFT→DPO).

**Q: What is GRPO and why does it matter?**
A: Group Relative Policy Optimization (DeepSeek). Unlike PPO it has no critic — it samples a group of completions and uses the group mean/std as the advantage baseline. Removing the value model made large-scale reasoning RL (DeepSeek-R1) tractable. Related: **REINFORCE++** (simpler, often more stable; built into OpenRLHF) and **RLOO** (leave-one-out advantage, lower variance). **AsyncGRPO** (TRL 2026) runs rollouts in a separate child process with its own GIL, preventing autograd engine stalls at scale.

**Q: What is RLVR?**
A: Reinforcement Learning with Verifiable Rewards — use deterministic checkable rewards (math answer match, code passing tests) instead of a noisy reward model. It's central to reasoning models like DeepSeek-R1 and Qwen3-thinking because sparse high-precision rewards drive genuine exploration. Caveat (2026): some gains may be selection over existing capability rather than new reasoning.

**Q: How is a reasoning model like R1 trained?**
A: Cold-start SFT on long chain-of-thought seeds → RLVR (GRPO) on verifiable tasks → rejection sampling to build clean traces → distillation into smaller models. Qwen3 adds a thinking-mode fusion SFT (the `</think>` toggle) and a general-RL stage.

**Q: How do you build preference data?**
A: Sample k completions per prompt and rank them with a stronger model (LLM-as-judge) to form chosen/rejected pairs; or use real user feedback (→ KTO). Watch for judge bias and self-confirming loops.

## Data
**Q: How much data do you need to fine-tune?**
A: 100–500 high-quality pairs to shift tone/style; 1k–10k for task specialization; tens of thousands+ for continued pre-training. Quality beats quantity — a few hundred expert pairs beat thousands of noisy synthetic ones.

**Q: What's the #1 mistake in SFT data prep?**
A: Getting the chat template wrong — you must train and infer with the exact same template (ChatML for Qwen, the Llama-3 header format, etc.). Second: not masking the prompt (use completion-only loss).

## Evaluation
**Q: How would you evaluate a fine-tuned model?**
A: Don't trust public benchmarks alone — build a domain gold set (50–500 examples), score base vs fine-tuned with an LLM-as-judge on a rubric, and re-run a public benchmark to catch general-ability regression. Triangulate; treat any single number as a hypothesis.

**Q: Which benchmarks still matter in 2026?**
A: Reasoning + coding + agentic: AIME, LiveCodeBench, SWE-bench Verified, GPQA Diamond, ARC-AGI-2, τ²-bench, APEX-Agents, and **Humanity's Last Exam (HLE)** as the expert-level frontier ceiling. MMLU/GSM8K/HellaSwag are saturated/contaminated — useful for ranking small models, not differentiating frontier.

**Q: LLM-as-judge bias — how do you handle it?**
A: Use pointwise (not pairwise) scoring, swap position and average, normalize for length, and use a *different, stronger* model as judge (never self-grading). Run the full battery only on a held-out gold set.

**Q: What is eval-driven development?**
A: Gating releases on gold-set regression thresholds wired into CI (Braintrust/Promptfoo), so a model change can't ship if it regresses quality — same discipline as test-driven engineering applied to model behavior.

## Serving / production
**Q: How do you serve a fine-tuned model?**
A: Export the merged model (or adapter), quantize to 4-bit (GGUF for local/Ollama, AWQ for GPU), and serve with vLLM (PagedAttention + continuous batching) for production, or Ollama for local dev.

**Q: vLLM vs SGLang vs Ollama?**
A: vLLM is the default (broadest HW, most-deployed); SGLang wins on prefix-cache-heavy workloads (agents/RAG); Ollama/llama.cpp for local/edge. Move to TensorRT-LLM only for pure-NVIDIA latency-critical deployments.

**Q: How do you make inference fast/cheap?**
A: 4-bit quantize first, right-size the model, use continuous batching (2–10×), speculative decoding (EAGLE-3 ~2–3×; **P-EAGLE** with `parallel_drafting: true` adds another ~1.69× on B200 by drafting tokens in one parallel pass; n-gram self-speculation is a free win for repetitive workloads with no draft model), and prefix caching. Serverless GPU beats reserved below ~30–40% sustained utilization.

**Q: How do you monitor an LLM in production?**
A: Track TTFT, TPOT, throughput, and per-feature cost; log traces with Langfuse/Phoenix; run LLM-judge evals on sampled traffic to catch silent quality regressions; watch for drift.

## Behavioral bridge (your existing stories)
- **"Hardest problem you've solved"** → Kora V1: replacing an immovable radar booth with a portable device by isolating the one capability that mattered (through-fabric radar) and re-architecting the rest (depth camera for positioning + radar for measurement). Patent US20190295319A1. Shows problem-framing under uncertainty — the senior skill.
- **"Monitor/troubleshoot in production"** → Rust SSE rewrite: re-engineered a Node.js streaming server in Rust (Axum/Tokio), eliminating OOM crashes and boosting throughput 10× on smaller ECS instances. Direct hit on "production-grade apps."
- **"Fullstack AI product"** → AIPriceAction end-to-end: Rust backend (22 workers, 574 tickers) + multi-agent Python pipeline + React SPA + SDK/CLI. Your differentiator: most LLM engineers can't do the infra/fullstack side; you can.
- **"If your teacher/agent is wrong, won't the student learn the wrong thing?"** → Not in the final stage. SFT imitates the teacher (so a wrong teacher can mislead early on — mitigate with rejection-sampling). DPO uses teachers only as a relative ranking. In the final **RLVR** stage the teacher is **irrelevant** — the student is graded on its own call vs the realized outcome, so reality corrects a bad prior. (Same as DeepSeek-R1: SFT to imitate → RLVR to optimize against verifiable rewards.)
- **"Why pivot from CV to LLMs?"** → Same core skill (production ML systems, end-to-end ownership); LLMs are where the leverage is now; you've already shipped LLM agents (multi-agent research pipeline, 3 published agent skills) and now want to own the training/eval layer too.
