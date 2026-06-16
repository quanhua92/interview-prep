# Day 3 — Fine-Tuning with Unsloth + QLoRA (The Hero Day)

> The single most important day of the curriculum. Run a real SFT on your own data with **Unsloth + QLoRA**, deeply understand the LoRA family and hyperparameters, and export artifacts you can serve. This is the skill that pays.

## Objectives
- Run a complete **SFT** on your Day-2 financial dataset with **Unsloth + QLoRA** on free Colab.
- Deeply understand **QLoRA**, the **LoRA family** (DoRA / rsLoRA / PiSSA / AdaLoRA / LoRA+), and why each exists.
- Know exactly when to choose **full FT vs PEFT** — and how to mitigate catastrophic forgetting.
- Reason about every key hyperparameter with **sensible 2026 defaults**.
- Export artifacts for serving: **LoRA adapter**, **merged HF checkpoint**, and **GGUF** for Ollama.
- Position this in an interview as proof you can ship a domain fine-tune.

---

## Concepts

### 1. What Unsloth is — and why it's the hero

**Unsloth** is an open-source fine-tuning + RL framework that **rewrites GPU kernels in hand-optimized Triton**, bypassing HuggingFace Transformers' default execution path. The result: **~2× faster, ~70% less VRAM**, notebook-first, and it runs on a single free Colab GPU.

- **Backed by NVIDIA + Red Hat.** Supports **500+ models** across text, vision, audio, and embeddings.
- **2026 capabilities:** SFT, DPO, ORPO, GRPO/GSPO, reward modeling, continued pretraining, **full fine-tuning**, **FP8 training**, and 4/16-bit LoRA/QLoRA.
- **Dynamic 4-bit quants** (`unsloth-bnb-4bit`) recover most of the QLoRA accuracy gap — so you rarely pay full NF4 tax.
- **Single-GPU focus.** Multi-GPU is the **paid Pro tier**. For clusters you move to Axolotl/verl.
- **`FastLanguageModel`** is the primary entry point for text LLMs. **`FastModel`** is the broader/lower-level class used for multimodal and specialized architectures.
- **Unsloth Studio** = open-source local web UI (projects, canvas, MCP, RAG/chat-with-files); runs Windows/Linux/macOS. Non-engineers on your team use this.
- **Workflow:** notebook → train → export (**LoRA adapter / GGUF / vLLM**).
- **Docs:** https://docs.unsloth.ai

Why it displaced vanilla `transformers` + `trl` for single-GPU work: less VRAM means you can **train a 7B on a 16GB card**, the API is 5 lines, and it produces **standard HF/PEFT checkpoints** — so you are *never locked in*.

### 2. Alternatives — know when to move beyond Unsloth

| Tool | Sweet spot | Why reach for it |
|---|---|---|
| **Unsloth** | Single-GPU SFT/DPO, speed + low VRAM | 2× faster, 70% less VRAM, notebook-first |
| **Axolotl** | Multi-GPU clusters, full RLHF, multimodal, long context | YAML-config, FSDP2/DeepSpeed, most flexible at scale |
| **LLaMA-Factory** | Breadth + zero-code **LlamaBoard UI** | Huge recipe library, can use Unsloth as backend |
| **Torchtune** | PyTorch-native, **DoRA built-in**, FSDP2 | If you want to stay on native PyTorch primitives |

**2026 verdict:** *Unsloth for speed, Axolotl for scale, LLaMA-Factory for breadth.* All export standard HF checkpoints → **least permanent decision you'll make.** Start in Unsloth, graduate to Axolotl when you outgrow one GPU.

### 3. LoRA explained

Freeze the base weights `W`, add **low-rank adapters** `A (r×d)` and `B (d×r)`:

```
Ŵ = W + (α / r) · A · B
```

- Trainable params drop to **~0.1–3%** of the model.
- Adapters **merge at inference** → **zero added latency**.
- Adapter size is ~**100MB**, so swapping domains is cheap.

```
     x
     │
     ▼
  ┌─────┐  W (frozen, d×d)         A (r×d)    B (d×r)
  │ base│───────────────────────── + (α/r) · ─── · ───
  │  W  │                                       ▲
  └─────┘                                  trainable
                                              r << d
```

### 4. The LoRA family (2026)

| Variant | Idea | Status / when to use |
|---|---|---|
| **DoRA** | Decompose `W` into magnitude + direction; apply LoRA to direction only | **Leading upgrade** — beats/matches LoRA at half the rank |
| **rsLoRA** | Scale by `α/√r` instead of `α/r`; stable at high rank | Use when `r ≥ 64` (`use_rslora=True`) |
| **PiSSA** | Init `A`/`B` from top-r singular vectors of `W` | Strong upgrade over LoRA; needs a one-time SVD |
| **AdaLoRA** | Dynamically allocate/prune rank across layers | Situational — uneven difficulty |
| **LoRA+** | Different LR for `A` and `B` | Drop-in tweak |

**Practical 2026 advice:**
1. **Start vanilla LoRA** — `r=16/32`, all-linear modules. This is 90% of the value.
2. Reach for **DoRA** (best general upgrade) or **PiSSA** (if you can afford the SVD init).
3. Use **rsLoRA scaling** when `r ≥ 64`.
4. `LoRA+` is a free knob if your framework supports per-matrix LRs.

### 5. QLoRA — the single-GPU default

**QLoRA = 4-bit quantize the frozen base + train LoRA adapters in 16-bit.** Two key tricks:

- **NF4 (4-bit NormalFloat):** a quantization grid matched to the normal distribution of weights → minimizes rounding error.
- **Double Quantization:** quantize the quantization constants themselves → another ~0.4 bits/param saved.

**VRAM footprint (training, with gradient checkpointing + 4-bit base):**

| Model size | ~VRAM | Hardware |
|---|---|---|
| 1.5–3B | 6–8 GB | Free Colab T4 |
| 7B | 10–16 GB | Colab T4/L4, RTX 4090 |
| 8B | 12–16 GB | Colab L4, RTX 4090 |
| 14B | 18–24 GB | RTX 4090, A10 |
| 70B | 40–48 GB | A100 80GB |

**Quality cost:** ~**1–2%** vs fp16 LoRA — almost always worth it to fit on one GPU.

### 6. Full FT vs PEFT

| Dimension | **PEFT (LoRA/QLoRA)** | **Full Fine-Tuning** |
|---|---|---|
| Trainable params | ~0.1–3% | 100% |
| VRAM (7B) | ~10–16 GB | ~80–120 GB |
| Hardware | Single GPU | Multi-GPU cluster |
| Quality ceiling | Slightly lower | Highest |
| Adapter size | ~100 MB | Full model (GB) |
| Forgetting risk | Low (base frozen) | Higher |
| Iteration speed | Fast (minutes) | Slow (hours) |

**When full FT:** multi-GPU cluster + large high-quality data + **major domain shift** or continued pretraining.
**When PEFT:** single GPU, small data, fast iteration, **preserve general capability** (the usual startup case).

**Catastrophic forgetting & mitigation:**
- Use **LoRA** (base frozen) — the strongest single defense.
- **Lower the LR** and run **fewer epochs (1–3)**.
- **Replay/mix ~5–10% general data** into the SFT set.
- **Weight averaging** (e.g. WiSE-FT between adapter and base) for stability.

### 7. Key hyperparameters — sensible 2026 defaults

| Param | Default | Notes |
|---|---|---|
| `r` (rank) | **16 / 32** | 8 = fast smoke test; 64–128 = complex task, pair with rsLoRA |
| `lora_alpha` | **= r or 2r** | keep `α/r ≥ 1`; Unsloth often sets `α = r` |
| `target_modules` | **ALL 7 linear** | `q,k,v,o,gate,up,down_proj` — never just `q,v` |
| `lora_dropout` | **0** (Unsloth) | 0.05–0.1 only if overfitting |
| `learning_rate` | **2e-4** (LoRA/QLoRA) | range 2e-4 → 5e-6; 5e-6 for RL; 1e-5→2e-5 for full FT |
| `epochs` | **1–3** | more epochs ≠ better; watch for overfitting |
| `per_device_batch` | **2** | raise VRAM permitting, but prefer raising `grad_accum` |
| `gradient_accumulation` | **8** | → effective batch 16; **raise THIS not batch to avoid OOM** |
| `packing` | **True** | 20–30% faster; concatenates short sequences |
| `gradient_checkpointing` | **True** (`"unsloth"`) | saves ~30% VRAM + enables long context |
| `lr_scheduler` | **cosine / linear** | cosine for slightly better final quality |
| `warmup` | **5–10%** of steps | stabilizes early training |
| `weight_decay` | **0.01–0.1** | mild regularization |
| `dtype` | **bf16** | (fp16 fallback on older GPUs) |
| `optim` | **adamw_8bit** | paged 8-bit AdamW saves memory |
| `seed` | **fixed** | reproducibility for eval comparison |

**Overfitting signals & fixes:** train loss dropping **below ~0.2** while eval stalls → reduce epochs, lower LR, raise dropout, get more diverse data. **Data quality beats every hyperparameter.**

---

## Hands-on exercise

**Fine-tune Qwen2.5-7B-Instruct on your Day-2 financial-analysis dataset with Unsloth + QLoRA on free Colab.**

1. Open Colab → **Runtime → Change runtime type → T4 GPU** (L4 if available).
2. Upload your Day-2 `day2_financial_qa.jsonl` (one record per line, `{"messages": [{"role":...,"content":...}]}`).
3. Run the cells below in order.
4. Sanity-check inference, then export both adapter and GGUF.

```python
# Day 3 hands-on — Fine-tune Qwen2.5-7B-Instruct with Unsloth + QLoRA
# Target: Google Colab T4/L4 (free tier). Select a GPU runtime first.

# === Install (Colab) ===
%%capture
!pip install "unsloth[colab-new] @ git+https://github.com/unslothai/unsloth.git"
!pip install --upgrade --no-cache-dir "trl<0.9" "peft" "accelerate" "bitsandbytes"

# === Imports ===
import torch
from datasets import load_dataset
from unsloth import FastLanguageModel
from unsloth.chat_templates import get_chat_template, train_on_responses_only
from trl import SFTTrainer, SFTConfig

# 1. Load base in 4-bit (QLoRA) — dynamic 4-bit recovers most accuracy
max_seq_len = 2048
model, tokenizer = FastLanguageModel.from_pretrained(
    model_name      = "unsloth/Qwen2.5-7B-Instruct",
    max_seq_length  = max_seq_len,
    dtype           = None,           # auto: bf16 on Ampere+, fp16 on older
    load_in_4bit    = True,           # QLoRA: NF4 + double quant on frozen base
)

# 2. Attach LoRA adapters — r=16, alpha=16, ALL 7 linear modules
model = FastLanguageModel.get_peft_model(
    model,
    r              = 16,
    target_modules = ["q_proj", "k_proj", "v_proj", "o_proj",
                      "gate_proj", "up_proj", "down_proj"],
    lora_alpha              = 16,     # alpha = r  -> alpha/r = 1
    lora_dropout            = 0,      # Unsloth: 0 is optimal; 0.05-0.1 if overfitting
    bias                    = "none",
    use_gradient_checkpointing = "unsloth",   # ~30% VRAM saved + long context
    random_state            = 3407,
    use_rslora              = False,  # set True when r >= 64
    loftq_config            = None,
)

# 3. Apply ChatML chat template
tokenizer = get_chat_template(
    tokenizer,
    chat_template = "chatml",
    mapping = {"role": "role", "content": "content",
               "user": "user", "assistant": "assistant"},
)

# 4. Load Day-2 dataset (JSONL with "messages": [{"role","content"}, ...])
dataset = load_dataset("json", data_files="day2_financial_qa.jsonl", split="train")

def formatting_prompts_func(examples):
    texts = [
        tokenizer.apply_chat_template(conv, tokenize=False, add_generation_prompt=False)
        for conv in examples["messages"]
    ]
    return {"text": texts}

dataset = dataset.map(formatting_prompts_func, batched=True)

# 5. Build the SFT trainer
trainer = SFTTrainer(
    model            = model,
    tokenizer        = tokenizer,
    train_dataset    = dataset,
    dataset_text_field = "text",
    max_seq_length   = max_seq_len,
    args = SFTConfig(
        per_device_train_batch_size = 2,
        gradient_accumulation_steps = 4,    # effective batch = 8
        warmup_steps         = 10,
        num_train_epochs     = 1,           # start at 1; raise only if underfit
        learning_rate        = 2e-4,        # QLoRA default
        fp16                 = not torch.cuda.is_bf16_supported(),
        bf16                 = torch.cuda.is_bf16_supported(),
        logging_steps        = 10,
        optim                = "adamw_8bit",
        weight_decay         = 0.01,
        lr_scheduler_type    = "cosine",
        seed                 = 3407,
        output_dir           = "outputs",
        report_to            = "none",
    ),
)

# 6. Mask user/system tokens — only train on assistant responses
trainer = train_on_responses_only(
    trainer,
    instruction_part = "<|im_start|>user\n",
    response_part    = "<|im_start|>assistant\n",
)

# 7. Train
trainer_stats = trainer.train()

# 8. Sanity-check inference
FastLanguageModel.for_inference(model)
messages = [{"role": "user", "content": "Analyze VIC's price action this week."}]
inputs = tokenizer.apply_chat_template(
    messages, tokenize=True, add_generation_prompt=True, return_tensors="pt"
).to("cuda")
outputs = model.generate(
    input_ids=inputs, max_new_tokens=256, temperature=0.7, do_sample=True
)
print(tokenizer.decode(outputs[0], skip_special_tokens=True))

# 9. Save LoRA adapter (HF format) — ~100MB, swappable
model.save_pretrained("qwen25-7b-fin-qlora")
tokenizer.save_pretrained("qwen25-7b-fin-qlora")

# 10. (Optional) Export to GGUF for Ollama — q4_k_m is the standard deploy quant
# model.save_pretrained_gguf(
#     "qwen25-7b-fin-gguf",
#     tokenizer,
#     quantization_method = "q4_k_m",
# )
# Then locally:
#   echo 'FROM ./qwen25-7b-fin-gguf-Q4_K_M.gguf' > Modelfile
#   ollama create fin-qwen -f Modelfile && ollama run fin-qwen
```

**Equivalent minimal pure-TRL reference (no Unsloth)** — same result, slower, more VRAM. Useful to demystify what Unsloth automates:

```python
import torch
from transformers import AutoModelForCausalLM, BitsAndBytesConfig, AutoTokenizer
from peft import LoraConfig, get_peft_model, prepare_model_for_kbit_training
from trl import SFTTrainer, SFTConfig
from datasets import load_dataset

bnb = BitsAndBytesConfig(
    load_in_4bit=True,
    bnb_4bit_quant_type="nf4",
    bnb_4bit_use_double_quant=True,
    bnb_4bit_compute_dtype=torch.bfloat16,
)
model = AutoModelForCausalLM.from_pretrained("Qwen/Qwen2.5-7B-Instruct",
                                             quantization_config=bnb,
                                             device_map="auto")
model = prepare_model_for_kbit_training(model)
peft_cfg = LoraConfig(r=16, lora_alpha=16, lora_dropout=0, bias="none",
                      task_type="CAUSAL_LM",
                      target_modules=["q_proj","k_proj","v_proj","o_proj",
                                      "gate_proj","up_proj","down_proj"])
model = get_peft_model(model, peft_cfg)
ds = load_dataset("json", data_files="day2_financial_qa.jsonl", split="train")
trainer = SFTTrainer(model=model, train_dataset=ds, dataset_text_field="text",
                     args=SFTConfig(per_device_train_batch_size=2,
                                    gradient_accumulation_steps=4,
                                    learning_rate=2e-4, num_train_epochs=1,
                                    bf16=True, output_dir="outputs"))
trainer.train()
```

**What to watch during training:**
- Loss should fall smoothly; a flat ~1.0–2.0 region is normal for instruction data.
- If loss dives under ~0.2 you're memorizing — stop early / lower LR / add data.
- Compare **base vs fine-tuned** on 5 held-out prompts before declaring victory (Day 5 formalizes this).

---

## Checklist
- [ ] Selected a GPU runtime; installed Unsloth + TRL + peft.
- [ ] Loaded `Qwen2.5-7B-Instruct` in 4-bit and confirmed VRAM headroom.
- [ ] Attached LoRA with `r=16`, `alpha=16`, **all 7** target modules, `use_gradient_checkpointing="unsloth"`.
- [ ] Applied ChatML template and verified a sample renders correctly.
- [ ] Used `train_on_responses_only` with `<|im_start|>user\n` / `<|im_start|>assistant\n`.
- [ ] Trained 1 epoch; logged loss; stopped before overfitting.
- [ ] Ran inference sanity-check on held-out prompts; **base vs fine-tuned** side by side.
- [ ] Saved the **LoRA adapter**; (optionally) exported **GGUF `q4_k_m`** for Ollama.
- [ ] Can explain QLoRA, DoRA, and every hyperparameter choice out loud.

## What to explain in interview

**Q: What is QLoRA and why use it?**
QLoRA freezes a 4-bit NF4-quantized base and trains low-rank adapters in 16-bit, so a 7B model fits on a 16GB GPU with only ~1–2% quality cost vs fp16 LoRA.

**Q: LoRA vs DoRA — when do you switch?**
LoRA is the safe default (r=16/32, all-linear). DoRA decomposes weights into magnitude + direction and applies LoRA to direction only — it matches/beats LoRA at half the rank, so it's the first upgrade I reach for when I have a small quality budget.

**Q: How do you choose target modules and rank?**
I target **all 7 linear projections** (q/k/v/o/gate/up/down), never just q,v. Rank 16–32 covers most tasks; I bump to 64–128 **with rsLoRA scaling** (`α/√r`) only for complex domain shifts.

**Q: When would you do full fine-tuning instead of PEFT?**
Only when I have a multi-GPU cluster, a large high-quality dataset, and a **major domain shift** (e.g. continued pretraining). For everything else PEFT is faster, cheaper, and forgets less because the base is frozen.

**Q: How do you prevent catastrophic forgetting?**
Freeze the base (LoRA), use a modest LR with 1–3 epochs, and replay ~5–10% general-domain data; weight averaging between adapter and base is a cheap extra safeguard.

**Q: Why Unsloth specifically?**
It rewrites the GPU kernels in hand-optimized Triton, giving ~2× speed and ~70% less VRAM, which puts a real 7B fine-tune on a free Colab GPU — while still exporting standard HF/PEFT checkpoints, so there's no lock-in.

**Q: Does `assistant_only_loss=True` in TRL work out of the box?**
In 2026 TRL, `assistant_only_loss=True` requires the model's chat template to include `{% generation %}` / `{% endgeneration %}` keywords. TRL auto-patches templates for most Qwen and Llama families, but always verify — and it's currently incompatible with `use_liger_kernel=True`. When in doubt, use Unsloth's `train_on_responses_only` helper instead, which is more robust.
