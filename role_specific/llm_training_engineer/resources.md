# Resources — LLM Training, Fine-Tuning & Post-Training (June 2026)

Opinionated, grouped by stage. "★" = start here.

## Foundations & general
- ★ Karpathy — *Intro to LLMs* (1-hr talk, YouTube) — best fast intuition
- ★ Sebastian Raschka — *Practical Tips for Finetuning LLMs Using LoRA* — https://magazine.sebastianraschka.com/p/practical-tips-for-finetuning-llms
- Sebastian Raschka — *LLM Research Papers: The 2026 List* — https://magazine.sebastianraschka.com/p/llm-research-papers-2026-part1
- Hugging Face NLP / LLM course — https://huggingface.co/learn

## Pre-training (understand, don't do)
- *Reuse, Don't Retrain* — continued pre-training recipe — https://arxiv.org/abs/2407.07263
- Nemotron 3 Super tech report (hybrid Mamba-2 + MoE) — https://arxiv.org/abs/2604.12374
- FineWeb (HuggingFace, 15T tokens) — https://huggingface.co/datasets/HuggingFaceFW/fineweb
- Nemotron-CC / NeMo Curator — https://arxiv.org/html/2412.02595v2

## Fine-tuning & PEFT
- ★ **Unsloth docs** — https://docs.unsloth.ai  (start at *Fine-tuning LLMs Guide*, *LoRA Hyperparameters Guide*)
- ★ **Unsloth free Colab notebooks** — https://docs.unsloth.ai/get-started/unsloth-notebooks
- ★ **HF TRL `SFTTrainer` docs** — https://huggingface.co/docs/trl/en/sft_trainer
- HF PEFT library — https://github.com/huggingface/peft
- QLoRA paper (Dettmers et al.) — https://arxiv.org/abs/2305.14314
- DoRA — https://arxiv.org/abs/2402.09353  · code https://github.com/NVlabs/DoRA
- PiSSA — https://arxiv.org/abs/2404.02948  · https://github.com/GraphPKU/PiSSA
- rsLoRA — https://arxiv.org/abs/2312.03732
- Tooling comparison: Unsloth vs Axolotl vs LLaMA-Factory — https://theaiengineer.substack.com/p/unsloth-vs-axolotl-vs-llama-factory

## Post-training / alignment
- ★ DPO (Rafailov et al.) — https://arxiv.org/abs/2305.18290
- ★ GRPO / DeepSeekMath — https://arxiv.org/abs/2402.03300
- ★ DeepSeek-R1 — *Nature* 645 (2025) / https://arxiv.org/abs/2501.12948
- Qwen3 technical report (4-stage post-training) — https://arxiv.org/abs/2505.09388
- Awesome RLVR (surveys + ICML/ICLR 2026 papers) — https://github.com/opendilab/awesome-RLVR
- **AsyncGRPO (TRL 2026)** — rollout worker child-process design to avoid GIL stalls — see TRL changelog / release notes
- **verl hybrid engine** — co-locates actor+reference+vLLM on same GPUs for small clusters — https://github.com/volcengine/verl
- **Tools:** TRL (`DPOTrainer`/`GRPOTrainer`) · **verl** (production RL) — https://github.com/volcengine/verl · **OpenRLHF** (REINFORCE++/RLOO/GRPO) — https://github.com/OpenRLHF/OpenRLHF · **open-r1** (HF's R1 repro) — https://github.com/huggingface/open-r1

## Evaluation
- ★ **lm-evaluation-harness** (EleutherAI) — https://github.com/EleutherAI/lm-evaluation-harness
- lighteval (HuggingFace) — https://github.com/huggingface/lighteval
- Inspect (UK AISI) — https://github.com/UKGovernmentBEIS/inspect_ai
- LLM-as-a-judge guide (Evidently AI) — https://www.evidentlyai.com/llm-guide/llm-as-a-judge
- τ²-bench (agentic eval, Sierra Research) — https://github.com/sierra-research/tau2-bench
- **APEX-Agents** (long-horizon professional domain tasks) — see leaderboards / ICML 2026 workshops
- **Humanity's Last Exam (HLE)** — expert-level multi-domain frontier ceiling — https://agi.safe.ai/hle
- LLM benchmark methodology 2026 (contamination/saturation) — https://www.digitalapplied.com/blog/llm-benchmark-methodology-2026-contamination-leaderboard-guide
- Product eval tools: Braintrust, Promptfoo, DeepEval, RAGAS, Galtea

## Serving & quantization
- ★ **vLLM** — https://docs.vllm.ai  · *Anatomy of vLLM* — https://vllm.ai/blog/2025-09-05-anatomy-of-vllm  · P-EAGLE spec decoding — https://vllm.ai/blog/2026-03-13-p-eagle
- **SGLang** — https://github.com/sgl-project/sglang
- **llama.cpp / Ollama** — https://github.com/ggerganov/llama.cpp  · https://ollama.com
- Quantization methods compared (GGUF/AWQ/GPTQ/EXL2/NVFP4) — https://ai.rs/ai-developer/quantization-methods-compared
- TensorRT-LLM — https://github.com/NVIDIA/TensorRT-LLM

## Observability
- ★ **Langfuse** (OSS, self-hostable) — https://langfuse.com
- Arize Phoenix (OSS) — https://github.com/Arize-ai/phoenix
- Helicone — https://helicone.ai

## Compute (where to train/serve)
- Free/cheap single GPU: **Google Colab** (T4/L4 free), **Kaggle** (P100/T4 free)
- Rent per-hour: **RunPod**, **Lambda**, **CoreWeave** (H100/H200/Blackwell)
- Serverless GPU: RunPod, Modal, Together, fal, Fireworks

## Communities
- HuggingFace forums · Unsloth Discord · r/LocalLLaMA · EleutherAI Discord
