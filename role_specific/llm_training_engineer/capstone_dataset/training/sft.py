#!/usr/bin/env python3
"""SFT (Unsloth + QLoRA) on build/sft_train.jsonl. Run on a GPU (Colab L4 / RTX 4090).

Input rows (from build_dataset.py --mode sft):
    {"messages": [{"role":"system",...},{"role":"user",...},{"role":"assistant",...}]}
TRL applies the chat template automatically from the "messages" column.

Saves a LoRA adapter (qwen-finance-sft/) and optionally a GGUF for Ollama.

pip install "unsloth[cu124-torch260]" trl peft accelerate bitsandbytes
"""
from __future__ import annotations
import torch
from datasets import load_dataset
from unsloth import FastLanguageModel
from unsloth.chat_templates import get_chat_template, train_on_responses_only
from trl import SFTTrainer, SFTConfig

MODEL = "unsloth/Qwen2.5-7B-Instruct"
TRAIN = "build/sft_train.jsonl"
MAX_SEQ = 4096


def main():
    model, tokenizer = FastLanguageModel.from_pretrained(
        model_name=MODEL, max_seq_length=MAX_SEQ, dtype=None, load_in_4bit=True)

    model = FastLanguageModel.get_peft_model(
        model,
        r=16,
        target_modules=["q_proj", "k_proj", "v_proj", "o_proj",
                        "gate_proj", "up_proj", "down_proj"],
        lora_alpha=16, lora_dropout=0, bias="none",
        use_gradient_checkpointing="unsloth", random_state=3407, use_rslora=False)

    tokenizer = get_chat_template(tokenizer, chat_template="chatml")
    ds = load_dataset("json", data_files=TRAIN, split="train")

    trainer = SFTTrainer(
        model=model, tokenizer=tokenizer, train_dataset=ds,
        args=SFTConfig(
            per_device_train_batch_size=2, gradient_accumulation_steps=4,
            num_train_epochs=1, learning_rate=2e-4,
            bf16=torch.cuda.is_bf16_supported(), fp16=not torch.cuda.is_bf16_supported(),
            logging_steps=10, optim="adamw_8bit", weight_decay=0.01,
            lr_scheduler_type="cosine", warmup_ratio=0.05, seed=3407,
            output_dir="outputs_sft", report_to="none"))

    # mask the prompt; train only on assistant tokens (ChatML markers)
    trainer = train_on_responses_only(
        trainer, instruction_part="<|im_start|>user\n",
        response_part="<|im_start|>assistant\n")

    trainer.train()
    model.save_pretrained("qwen-finance-sft")
    tokenizer.save_pretrained("qwen-finance-sft")

    # Optional: export GGUF (Q4_K_M) for Ollama / llama.cpp
    # model.save_pretrained_gguf("qwen-finance-gguf", tokenizer, quantization_method="q4_k_m")
    # Then: ollama create fin-qwen -f Modelfile   (FROM ./qwen-finance-gguf-Q4_K_M.gguf)


if __name__ == "__main__":
    main()
