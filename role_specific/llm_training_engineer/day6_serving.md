# Day 6 — Serving & Inference: Quantize, Deploy, Observe

> Get the fine-tuned model out of the notebook and in front of users — at the right precision, on the right engine, with the signals that let you know it's still healthy.

## Objectives

- Pick a **quantization format** for the scenario (GGUF for local/portable, AWQ for GPU serving, FP4/FP8 on Blackwell) and justify it with the 4-bit-default rule.
- Pick a **serving engine** for the scenario — vLLM as the default, SGLang / TensorRT-LLM when benchmarks justify, Ollama / llama.cpp for local.
- Understand the **throughput techniques** that make LLM serving economic: PagedAttention, continuous batching, speculative decoding, chunked prefill, prefix caching.
- **Deploy locally (Ollama) and to prod (vLLM)** — your Day-3 fine-tune, end to end.
- **Instrument observability** with the four signal categories plain infra monitoring misses.

## Concepts

### Quantization — highest-ROI compression

Quantization is the single biggest lever for serving cost: **~75% memory reduction at <1% accuracy loss for 4-bit**. It's the default first move before anything else.

| Method | Bits | Use case | 2026 status |
|---|:--:|---|---|
| **GGUF** (llama.cpp) | 2–8 (**Q4_K_M** sweet spot) | Portability + local / CPU+GPU offload; Ollama / llama.cpp / LM Studio default | **Dominant for local/edge** |
| **AWQ** | 4 | GPU serving (activation-aware) | Strong; **preferred for vLLM/TGI GPU serving** |
| **GPTQ** | 2 / 3 / 4 / 8 | GPU serving via calibration | Mature; slightly lower quality than AWQ at 4-bit |
| **BitsAndBytes** (NF4 / INT8) | 4 / 8 | Quick QLoRA + easy loading | Ubiquitous for **training/prototyping** |
| **NVFP4 / FP8** | 4 / 8 | NVIDIA Blackwell-native | **2026 frontier**: hardware FP4 near-lossless + speedups |

**Rule of thumb: 4-bit is the 2026 standard.** AWQ for GPU serving, GGUF for local/portable, BitsAndBytes during training. **Avoid 2-bit** for anything user-facing — quality falls off a cliff.

Why 4-bit specifically: it's the knee of the curve. 8-bit buys you almost nothing in quality over 4-bit but doubles memory; below 4-bit you start paying real accuracy. NVFP4 on Blackwell is the exception — hardware-native 4-bit with near-lossless quality.

### Serving engines — pick when

| Engine | Strength | Pick when |
|---|---|---|
| **vLLM** | PagedAttention, continuous batching, widest HW (NVIDIA + AMD), most-deployed | **DEFAULT strong baseline**; prod self-hosting |
| **SGLang** | Fastest on NVIDIA/AMD, RadixAttention prefix caching, structured gen | Heavy prefix reuse (agents / RAG / shared system prompts); max throughput |
| **TensorRT-LLM** | NVIDIA low-level, best p95 latency, FP8/FP4 | Pure-NVIDIA latency-critical; higher integration cost |
| **llama.cpp / Ollama** | Local/dev, GGUF, trivial setup | Local dev, prototyping, privacy, edge, single-GPU |
| **TGI** (HuggingFace) | HF-native | Decreasing mindshare vs vLLM |

**2026 verdict: start with vLLM. Move to SGLang or TensorRT-LLM only if your own benchmarks justify it.** vLLM is the safe default because it runs everywhere, has the largest ecosystem, and is what most production teams know. SGLang wins when your workload is prefix-heavy (shared system prompts, agent loops, multi-turn RAG) because RadixAttention caches shared KV across requests. TensorRT-LLM wins on raw p95 latency but you pay integration tax and lock to NVIDIA.

### Key throughput techniques

The five techniques that make LLM serving economic. Know each in one line.

| Technique | One-liner |
|---|---|
| **PagedAttention / paged KV cache** (vLLM) | KV stored in **non-contiguous blocks like virtual memory** — eliminates fragmentation, lets many sequences share GPU. |
| **FlashAttention** | Exact, IO-aware attention kernel — fewer HBM reads, same math. Baseline everywhere. |
| **Continuous / iteration-level batching** | Admit new requests every iteration instead of waiting for the batch to drain — **2–10× vs static batching**, the biggest single unlock. |
| **Speculative decoding** | Fast **draft model proposes** tokens, **target model verifies** in parallel — same outputs, far fewer serial forward passes. |
| **Chunked prefill** | Interleave **long-prompt chunks** with decode steps → stable TTFT under concurrent long prompts. |
| **Prefix caching** | Cache KV for **shared prefixes** (system prompt, tool defs); **SGLang RadixAttention** is best-in-class. vLLM v0.23+ adds **prefix-cache-aware scheduling** across distributed pods — prevents load balancers from scattering related requests, boosting cache hit rates in multi-node deployments. |

**2026 speculative-decoding detail:** the live methods are **EAGLE-3 / P-EAGLE** (~2–3× speedup, production-ready in vLLM v0.23+), plus Medusa, Lookahead decoding, and **n-gram self-speculation** (no draft model needed — a free win for repetitive workloads). P-EAGLE generates draft tokens in a **single parallel forward pass** (vs serial in EAGLE-3), delivering up to 1.69× speedup over vanilla EAGLE-3 on NVIDIA B200. Enable via `"parallel_drafting": true` in your speculative config. For n-gram self-speculation: `--speculative-model "[ngram]" --num-speculative-tokens 5`.

Two latency metrics to internalize:

```
   TTFT  (time-to-first-token)  ── driven by PREFILL (prompt length, chunked prefill helps)
   TPOT  (time-per-output-token) ── driven by DECODE  (batch size, KV cache, spec decoding helps)
```

Throughput (tokens/sec aggregate) scales with batching; per-request latency scales inversely. Continuous batching is what lets you have both.

### Deployment patterns

| Pattern | When | Notes |
|---|---|---|
| **Single-GPU dev / local** | Prototyping, privacy, edge | Ollama easiest; or llama.cpp / LM Studio. GGUF Q4, 7–14B fits consumer GPUs. |
| **Multi-GPU self-hosted prod** | Steady production load | vLLM **tensor parallelism** splits a 30–400B+ model across GPUs; pipeline parallelism for very large models. |
| **Serverless GPU** | Spiky / low-utilization traffic | **RunPod** (fastest setup, per-second billing), **Modal** (lowest managed cost), Together / fal / Fireworks / Lambda (managed). Avoid serverless for steady high-throughput. |
| **Managed / self-hosted cloud GPU** | When you need the metal | RunPod / Lambda / CoreWeave H100 / H200 / Blackwell — run vLLM or TRT-LLM yourself, or use fully-managed APIs. |

**Cost tips, in order of ROI:**

1. **Quantize to 4-bit first** — biggest single win, ~75% memory at <1% loss.
2. **Right-size the model to the task** — don't serve a 70B where a 14B Qwen3 fine-tune wins on your gold set.
3. **Batch aggressively** — continuous batching turns idle GPU into throughput.
4. **Speculative decoding** cuts per-token latency (and often cost) at fixed quality.
5. **Serverless wins below ~30–40% sustained utilization** — above that, dedicated is cheaper.
6. **Cache prefixes** — shared system prompts / tool defs are free hits with prefix caching.

### Observability — the four signal categories infra monitoring misses

Plain CPU/GPU/latency monitoring tells you the box is up. It does **not** tell you the model is still good. LLM-specific observability covers four categories infra can't:

| Category | What it catches |
|---|---|
| **Span traces** | Which retriever / tool / model call in a chain blew the budget or returned garbage. |
| **Output quality** | Hallucination spikes, format regressions, refusals — via sampled LLM-judge evals on live traffic. |
| **Cost / token** | Per-feature cost attribution; runaway context windows; over-prompting. |
| **User feedback** | Thumbs up/down, explicit corrections — the ground truth your judges can't generate. |

**Key metrics:**

| Metric | Means |
|---|---|
| **TTFT** | Time-to-first-token — prefill latency; user-perceived "is it working?" |
| **TPOT** | Time-per-output-token — decode speed; typing-speed feel |
| **Throughput** | Tokens/sec aggregate — economics |
| **Cost** | Tokens × price, attributed per feature |
| **Drift** | Input/output distribution shift vs baseline — early warning of data/prompt drift |
| **Live evals** | Judges run on sampled production traffic — quality regression in the wild |

**Tools:**

| Tool | Position |
|---|---|
| **Langfuse** | **#1 OSS**, self-hostable, tracing + eval + prompt mgmt — the default pick |
| **Arize Phoenix** | OSS, ML-monitoring heritage, strong on drift/quality |
| **Helicone** | OSS, lightweight + gateway in one |
| **LangSmith** | LangChain-native; tightest if you're already in LangChain |
| **Braintrust** | Eval-first; great if your eval platform and observability should be one |

**The practical loop:**

```
   instrument with OSS tracer (Langfuse/Phoenix)
              │
              ▼
   log traces + cost + latency on every request
              │
              ▼
   run LLM-judge evals on a SAMPLE of traffic
              │
              ▼
   gate releases on gold-set regression (from Day 5)
              │
              ▼
   label interesting traces back into the gold set  ── compounding asset
```

This closes the loop with Day 5: production traces feed the gold set, the gold set gates releases, the judge calibrates against humans. Eval and observability are one system, not two.

## Hands-on exercise

**(a) Export your Day-3 fine-tune to GGUF and run it in Ollama locally; (b) serve the merged/adapter model with vLLM.** ~3h.

### (a) GGUF → Ollama, local

**Step 1 — Export to GGUF with Unsloth.** From your Day-3 Unsloth notebook, save the merged model and convert to GGUF:

```python
# In your Unsloth notebook (Day 3) — merge LoRA + export GGUF
model.save_pretrained_merged("model", tokenizer, save_method="merged_16bit")
# Quantize to Q4_K_M (the sweet spot) — Unsloth wraps llama.cpp's quantize
model.save_pretrained_gguf("model", tokenizer, quantization_method="q4_k_m")
# → produces model.Q4_K_M.gguf (and others) in ./model/
```

**Step 2 — Write a `Modelfile`** (Ollama's build file, analogous to a Dockerfile):

```
FROM ./model.Q4_K_M.gguf
TEMPLATE """{{ .Prompt }}"""     # match the chat template you trained with
PARAMETER temperature 0
PARAMETER stop "<|im_end|>"      # use the stop tokens for your base model
```

**Step 3 — Build + run:**

```bash
ollama create mymodel -f Modelfile
ollama run mymodel
# Interactive prompt → type a financial-analysis question, confirm it answers in-domain
```

**Step 4 — Hit the Ollama API** (OpenAI-compatible):

```bash
curl http://localhost:11434/v1/chat/completions -H "Content-Type: application/json" \
  -d '{"model":"mymodel","messages":[{"role":"user","content":"Summarize VIC Q3 earnings risks"}],"temperature":0}'
```

Note VRAM use (`nvidia-smi` / `nvtop`) and TTFT.

### (b) vLLM serve, prod-style

**Step 5 — Serve the merged model with vLLM.** (Use the merged 16-bit checkpoint or an AWQ-quantized version. If you only have the LoRA adapter, merge first with `peft` / Unsloth's `merged_16bit`.)

```bash
# https://docs.vllm.ai
vllm serve ./model \
  --quantization awq \                  # omit if serving FP16; use awq for the AWQ build
  --tensor-parallel-size 1 \            # bump to N to split across N GPUs
  --max-model-len 8192 \
  --enable-prefix-caching               # free wins for shared system prompts
```

**Step 6 — Hit the OpenAI-compatible endpoint:**

```bash
curl http://localhost:8000/v1/chat/completions -H "Content-Type: application/json" \
  -d '{
    "model": "./model",
    "messages": [{"role":"user","content":"Summarize VIC Q3 earnings risks"}],
    "temperature": 0,
    "max_tokens": 256
  }'
```

vLLM streams usage stats to its logs; note **TTFT** (`time_to_first_token`) and **TPOT** from the response/log. If you're on NVIDIA, try `--speculative-model [draft-model]` to measure speculative decoding speedup.

### Bonus — instrument one call with Langfuse

Set env vars before the request:

```bash
export LANGFUSE_HOST="http://localhost:3000"   # self-host or cloud
export LANGFUSE_PUBLIC_KEY="pk-lf-..."
export LANGFUSE_SECRET_KEY="sk-lf-..."
# vLLM supports OpenTelemetry → forward to Langfuse's OTLP endpoint
# or wrap your client call in the Langfuse SDK:
```

```python
from langfuse.openai import openai  # drop-in instrumented client
client = openai.OpenAI(base_url="http://localhost:8000/v1", api_key="dummy")
resp = client.chat.completions.create(
    model="./model",
    messages=[{"role":"user","content":"Summarize VIC Q3 earnings risks"}],
)
# → trace appears in Langfuse UI with latency, tokens, cost
```

Open the Langfuse UI, find the trace, confirm you see TTFT, token counts, and cost attribution.

### Record your numbers

| Model | Quant | Engine | VRAM | TTFT (ms) | tokens/sec | Notes |
|---|---|---|---|---|---|---|
| Qwen3-7B (base) | FP16 | vLLM | | | | baseline |
| Qwen3-7B (base) | Q4_K_M | Ollama | | | | local dev |
| Qwen3-7B (fine-tune) | Q4_K_M | Ollama | | | | local, in-domain |
| Qwen3-7B (fine-tune) | AWQ | vLLM | | | | prod-style |
| Qwen3-7B (fine-tune) | AWQ + spec | vLLM | | | | with EAGLE-3 draft |

Expect the GGUF Q4 local number to be the easiest to set up, and vLLM AWQ to win on throughput. The point of the table is to build the reflex: **every serving decision gets measured, not assumed.**

## Checklist

- [ ] I can pick a quantization format per scenario and justify the **4-bit-default** rule.
- [ ] I exported my Day-3 fine-tune to GGUF (Q4_K_M) and ran it in Ollama locally.
- [ ] I served the merged/adapter model with vLLM (OpenAI-compatible endpoint).
- [ ] I can explain PagedAttention, continuous batching, speculative decoding, chunked prefill, and prefix caching in one line each.
- [ ] I know when to choose vLLM vs SGLang vs TensorRT-LLM vs Ollama, and that vLLM is the default.
- [ ] I can define TTFT vs TPOT and which techniques move each.
- [ ] I can list the four observability categories infra monitoring misses.
- [ ] I instrumented one call with Langfuse and saw trace + cost + latency in the UI.
- [ ] I recorded measured numbers (VRAM, TTFT, tokens/sec) in a table — not vibes.

## What to explain in interview

**Q: How do you serve a fine-tuned LLM in production?**
Default to **vLLM** — PagedAttention + continuous batching on whatever GPUs you have, OpenAI-compatible API. Quantize to 4-bit first (AWQ for GPU serving). Move to SGLang only if the workload is prefix-heavy (agents/RAG/shared system prompts) and benchmarks justify it, or TensorRT-LLM only for pure-NVIDIA p95-critical latency. Instrument with Langfuse from day one.

**Q: Quantization — what do you pick and why?**
4-bit is the 2026 standard — ~75% memory at <1% accuracy loss. **GGUF Q4_K_M** for local/portable (Ollama/llama.cpp), **AWQ** for GPU serving (vLLM/TGI), BitsAndBytes during training. Avoid 2-bit for anything user-facing. On Blackwell, NVFP4 is near-lossless and hardware-native.

**Q: What makes vLLM fast?**
Three things compound: **PagedAttention** (KV in non-contiguous blocks like virtual memory, no fragmentation), **continuous batching** (admit new requests every iteration instead of waiting for the batch to drain — 2–10×), and **prefix caching** for shared prefixes. Speculative decoding (EAGLE-3) stacks another ~2–3× on decode without changing outputs.

**Q: TTFT is high on long prompts — what do you do?**
TTFT is prefill-bound. Fixes: **chunked prefill** (interleave long-prompt chunks with decode so concurrent requests don't stall), reduce prompt length (tighter system prompts, RAG compression), and **prefix caching** if prefixes repeat. Then check you're not memory-bound on KV cache — quantize or raise the batching budget.

**Q: How do you observe an LLM in production beyond standard infra monitoring?**
Four signal categories infra misses: **span traces** (which call in the chain blew the budget), **output quality** (sampled LLM-judge evals on live traffic for hallucination/format regression), **cost/token** per feature, and **user feedback**. Tools: Langfuse (OSS, default), Phoenix, Helicone. The loop: log traces → judge a sample → gate releases on the gold set (Day 5) → feed interesting traces back into the gold set.

**Q: Serverless GPUs or dedicated?**
Serverless (RunPod / Modal) wins below **~30–40% sustained utilization** — spiky or low traffic, per-second billing. Above that, dedicated GPUs running vLLM are cheaper because you're not paying idle markup. For steady high-throughput, self-host on Lambda/CoreWeave/RunPod dedicated and run vLLM/TRT-LLM yourself.
