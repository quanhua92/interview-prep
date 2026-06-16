# Training scripts — the student side

These consume the data factory's output (`build/*.jsonl` + `outcomes.jsonl`) and
train / evaluate / serve the student model. Run on a GPU (free Colab L4 works for
7B QLoRA; RLVR wants more). Each script is standalone and configurable at the top.

## Run order

```bash
cd capstone_dataset

# 0) (data side, already built) scale questions + gather teachers, then:
python scripts/score.py                         # grade teachers
python scripts/build_dataset.py --mode sft      # -> build/sft_train.jsonl
python scripts/build_dataset.py --mode dpo      # -> build/dpo_train.jsonl

# 1) SFT (cold start) -- student imitates teacher prose
python training/sft.py                          # -> qwen-finance-sft/

# 2) Eval base vs SFT (serve both, then judge)
python training/eval.py \
  --base-url-a http://localhost:8000/v1 --model-a Qwen/Qwen2.5-7B-Instruct \
  --base-url-b http://localhost:8001/v1 --model-b qwen-finance-sft-merged \
  --judge-base-url https://openrouter.ai/api/v1 --judge-model anthropic/claude-3.5-sonnet

# 3) DPO (optional) -- prefer teachers that matched the future
python training/dpo.py                          # -> qwen-finance-dpo/

# 4) RLVR (stretch) -- reward the student's OWN call vs reality; teacher drops out
python training/rlvr.py                         # -> qwen-finance-rlvr/
```

## Files

| script | stage | input | output |
|---|---|---|---|
| `../scripts/sampler.py` | data | aipa dump | many question `.md` + outcomes |
| `sft.py` | SFT | `build/sft_train.jsonl` | `qwen-finance-sft/` (+ optional GGUF) |
| `eval.py` | eval | `build/sft_eval.jsonl` + 2 served endpoints | win-rate |
| `dpo.py` | DPO | `build/dpo_train.jsonl` | `qwen-finance-dpo/` |
| `rlvr.py` | RLVR | questions + `outcomes.jsonl` | `qwen-finance-rlvr/` |

## Notes / caveats

- **TRL/Unsloth APIs move fast.** These follow the mid-2026 patterns; if a config
  kwarg errors, check your installed version (`pip show trl`). The *structure* is
  stable (trainer + dataset + reward); only knob names drift.
- **`sft.py`** uses ChatML completion-only masking (`train_on_responses_only`).
  Swap the marker strings if you change the base model family (Llama-3, Gemma...).
- **`dpo.py`** uses `ref_model=None` + a PEFT config so TRL derives the reference by
  disabling the adapter (no second model in memory).
- **`rlvr.py`** builds its `{prompt, outcome}` dataset from the question files +
  `outcomes.jsonl`. The outcome reaches the reward function **only** as a dataset
  column — it is never placed in the prompt (leakage-safe). The reward mirrors
  `scripts/score.py` exactly (direction core + target/invalidation path). Set
  `use_vllm=False` if vLLM isn't available (much slower).
- GGUF export (for Ollama) is a commented line at the bottom of `sft.py`.
