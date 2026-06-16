# Tools Cheatsheet — Copy-Paste Recipes (June 2026)

> Single-GPU-first. Swap model names as needed. All recipes assume `pip install unsloth` (or use a free Colab notebook).

## 1. Unsloth SFT + QLoRA (the hero recipe)

```python
# pip install "unsloth[cu124-torch260]"   # adjust CUDA/torch combo for your env
from unsloth import FastLanguageModel
import torch

# 1) Load base in 4-bit (QLoRA)
max_seq_length = 4096
model, tokenizer = FastLanguageModel.from_pretrained(
    model_name = "unsloth/Qwen2.5-7B-Instruct",   # or unsloth/llama-3.1-8b-Instruct
    max_seq_length = max_seq_length,
    load_in_4bit = True,
    dtype = None,                                  # auto: bf16 on Ampere+
)

# 2) Attach LoRA to ALL 7 linear modules
model = FastLanguageModel.get_peft_model(
    model,
    r = 16,
    target_modules = ["q_proj", "k_proj", "v_proj", "o_proj",
                      "gate_proj", "up_proj", "down_proj"],
    lora_alpha = 16,
    lora_dropout = 0,
    bias = "none",
    use_gradient_checkpointing = "unsloth",        # ~30% VRAM saved
    random_state = 3407,
    use_rslora = False,                            # True if r >= 64
)

# 3) Set chat template (match the base model family!)
from unsloth.chat_templates import get_chat_template
tokenizer = get_chat_template(tokenizer, chat_template = "chatml")  # "llama-3" / "gemma" / "mistral"

def fmt(ex):
    texts = [tokenizer.apply_chat_template(c, tokenize=False, add_generation_prompt=False)
             for c in ex["messages"]]
    return {"text": texts}

from datasets import load_dataset
dataset = load_dataset("your-org/your-dataset", split="train").map(fmt, batched=True)
# dataset rows look like: {"messages": [{"role":"user","content":"..."},{"role":"assistant","content":"..."}]}

# 4) Train
from trl import SFTTrainer, SFTConfig
trainer = SFTTrainer(
    model = model, tokenizer = tokenizer, train_dataset = dataset,
    args = SFTConfig(
        dataset_text_field = "text",
        per_device_train_batch_size = 2,
        gradient_accumulation_steps = 4,     # effective batch 8
        num_train_epochs = 1,                # 1-3; more invites overfitting
        learning_rate = 2e-4,               # QLoRA sweet spot
        bf16 = torch.cuda.is_bf16_supported(),
        fp16 = not torch.cuda.is_bf16_supported(),
        logging_steps = 10,
        optim = "adamw_8bit",
        weight_decay = 0.01,
        lr_scheduler_type = "cosine",
        warmup_ratio = 0.05,
        seed = 3407,
        output_dir = "outputs",
        report_to = "none",                  # or "wandb"
    ),
)

# 5) Mask the prompt — train on assistant tokens only
from unsloth.chat_templates import train_on_responses_only
trainer = train_on_responses_only(
    trainer,
    instruction_part = "<|im_start|>user\n",      # for Qwen/ChatML
    response_part    = "<|im_start|>assistant\n",  # Llama-3: "<|start_header_id|>assistant<|end_header_id|>\n\n"
)

trainer.train()

# 6) Inference sanity check
FastLanguageModel.for_inference(model)
msgs = [{"role": "user", "content": "Summarize why the Fed held rates."}]
inputs = tokenizer.apply_chat_template(msgs, tokenize=True, add_generation_prompt=True, return_tensors="pt").to("cuda")
out = model.generate(input_ids=inputs, max_new_tokens=256, temperature=0.7)
print(tokenizer.batch_decode(out))

# 7) Save adapter (~100 MB) + push to Hub
model.save_pretrained("qwen-finance-lora"); tokenizer.save_pretrained("qwen-finance-lora")
# model.push_to_hub("your-hf-user/qwen-finance-lora", token="hf_...")
```

## 2. Export to GGUF → run in Ollama

```python
# In a fresh cell (Unsloth handles quantized GGUF export)
model.save_pretrained_gguf("qwen-finance-gguf", quantization_method="q4_k_m")
```

```bash
# Create an Ollama model from the GGUF
cat > Modelfile <<'EOF'
FROM ./qwen-finance-gguf/model-q4_k_m.gguf
TEMPLATE """{{ .Prompt }}"""
PARAMETER temperature 0.7
PARAMETER stop "<|im_end|>"
EOF
ollama create qwen-finance -f Modelfile
ollama run qwen-finance

# Or via the API (OpenAI-compatible):
curl http://localhost:11434/v1/chat/completions -H "Content-Type: application/json" \
  -d '{"model":"qwen-finance","messages":[{"role":"user","content":"Will VCB rise this week?"}]}'
```

## 3. Serve with vLLM (production)

```bash
# Merge adapter into base first (if you only have the adapter):
# python -c "from peft import AutoPeftModelForCausalLM; m=AutoPeftModelForCausalLM.from_pretrained('qwen-finance-lora'); m.merge_and_unload().save_pretrained('qwen-finance-merged')"

# Basic serve (vLLM v0.23+):
vllm serve qwen-finance-merged \
  --quantization awq \
  --tensor-parallel-size 1 \
  --max-model-len 8192 \
  --enable-prefix-caching

# With P-EAGLE speculative decoding (parallel drafting, ~2-3x decode speedup):
vllm serve qwen-finance-merged \
  --quantization awq \
  --max-model-len 8192 \
  --enable-prefix-caching \
  --speculative-model "lmsys/eagle3-qwen2.5-7b-instruct" \
  --speculative-config '{"parallel_drafting": true}'

# With n-gram self-speculation (no draft model needed — free win for repetitive text):
vllm serve qwen-finance-merged \
  --quantization awq \
  --max-model-len 8192 \
  --speculative-model "[ngram]" \
  --num-speculative-tokens 5

# Query the OpenAI-compatible endpoint:
curl http://localhost:8000/v1/chat/completions -H "Content-Type: application/json" \
  -d '{"model":"qwen-finance-merged","messages":[{"role":"user","content":"Analyze FPT."}]}'
```

## 4. TRL DPO (post-training, no Unsloth)

```python
# pip install trl datasets
from datasets import load_dataset
from trl import DPOTrainer, DPOConfig
from transformers import AutoModelForCausalLM, AutoTokenizer
from peft import LoraConfig

model = AutoModelForCausalLM.from_pretrained("qwen-finance-merged")   # your SFT'd model
tokenizer = AutoTokenizer.from_pretrained("qwen-finance-merged")
# dataset rows: {"prompt": "...", "chosen": "...", "rejected": "..."}
dataset = load_dataset("your-org/your-dpo-pairs", split="train")

trainer = DPOTrainer(
    model = model,
    args = DPOConfig(
        output_dir="dpo-out",
        beta=0.1,
        learning_rate=5e-6,
        num_train_epochs=1,
        per_device_train_batch_size=2,
        gradient_accumulation_steps=4,
        bf16=True,
        max_length=2048, max_prompt_length=1024,
    ),
    train_dataset=dataset,
    processing_class=tokenizer,
    peft_config=LoraConfig(r=16, lora_alpha=16, target_modules=["q_proj","k_proj","v_proj","o_proj"],
                           lora_dropout=0, bias="none", task_type="CAUSAL_LM"),
)
trainer.train()
```

## 5. Eval — LLM-as-judge on a gold set (skeleton)

```python
# eval/judge.py — score base vs fine-tuned on a 100-example gold set
import json, os
from openai import OpenAI   # or anthropic / your judge endpoint

client = OpenAI(base_url="http://localhost:8000/v1", api_key="dummy")  # your vLLM
JUDGE = OpenAI(api_key=os.environ["OPENAI_API_KEY"])                   # a stronger model

RUBRIC = "Score 0-5 on: correctness, grounding, clarity, safety, format. Return JSON {criterion: score}."

def gen(model_name, prompt):
    r = client.chat.completions.create(model=model_name, temperature=0.0,
        messages=[{"role":"user","content":prompt}])
    return r.choices[0].message.content

def judge(prompt, response, gold):
    r = JUDGE.chat.completions.create(model="gpt-4o", temperature=0.0,
        messages=[{"role":"user","content":f"Question: {prompt}\nGold: {gold}\nResponse: {response}\n\n{RUBRIC}"}])
    return json.loads(r.choices[0].message.content)

gold = [json.loads(l) for l in open("eval_gold.jsonl")]   # {prompt, gold}
for model_name in ["qwen-finance-merged", "Qwen/Qwen2.5-7B-Instruct"]:
    scores = []
    for ex in gold:
        resp = gen(model_name, ex["prompt"])
        scores.append(sum(judge(ex["prompt"], resp, ex["gold"]).values()))
    print(f"{model_name}: mean rubric score = {sum(scores)/len(scores):.2f}")
```

## 6. Public benchmark regression check (lm-evaluation-harness)

```bash
pip install lm-eval
# Compare base vs fine-tuned on a general benchmark to catch forgetting:
lm_eval --model hf --model_args pretrained=Qwen/Qwen2.5-7B-Instruct,dtype=bfloat16 \
        --tasks ifeval --batch_size auto --output_path base.json
lm_eval --model hf --model_args pretrained=qwen-finance-merged,dtype=bfloat16 \
        --tasks ifeval --batch_size auto --output_path sft.json
# Inspect ifeval_acc in both; Δ should be small.
```

## 7. Observability with Langfuse (one-line instrumentation)

```bash
pip install langfuse
export LANGFUSE_PUBLIC_KEY=... LANGFUSE_SECRET_KEY=...
export OTEL_EXPORTER_OTLP_ENDPOINT=https://cloud.langfuse.com/api/public/otel
# vLLM has built-in OTLP tracing; set the env vars and every request becomes a traceable span.
```

## Quick reference — hyperparameter defaults

| Knob | Value |
|---|---|
| rank `r` | 16 (32 for harder; 64–128 w/ `use_rslora`) |
| `lora_alpha` | = r (or 2r for aggressive) |
| target modules | q,k,v,o,gate,up,down (all 7) |
| LR (QLoRA) | 2e-4, cosine, 5–10% warmup |
| LR (DPO) | 5e-6, β=0.1 |
| epochs | 1–3 |
| batch / grad_accum | 2 / 4–8 (raise accum, not batch) |
| precision | bf16 (4-bit base for QLoRA) |
| gradient checkpointing | on (`"unsloth"`) |
