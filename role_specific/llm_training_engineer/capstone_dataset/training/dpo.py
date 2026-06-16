#!/usr/bin/env python3
"""DPO (TRL) on build/dpo_train.jsonl, on top of the SFT adapter. GPU required.

Input rows (from build_dataset.py --mode dpo):
    {"prompt": <question/evidence>, "chosen": <right teacher prose>,
     "rejected": <wrong teacher prose>, "system": <optional>}
ref_model=None + peft_config => TRL disables the adapter for the reference policy.

pip install trl peft transformers accelerate
"""
from __future__ import annotations
import torch
from datasets import load_dataset
from peft import LoraConfig
from transformers import AutoModelForCausalLM, AutoTokenizer
from trl import DPOTrainer, DPOConfig

SFT_MODEL = "qwen-finance-sft"   # your SFT adapter dir
TRAIN = "build/dpo_train.jsonl"


def main():
    tok = AutoTokenizer.from_pretrained(SFT_MODEL)
    model = AutoModelForCausalLM.from_pretrained(SFT_MODEL, torch_dtype=torch.bfloat16)
    ds = load_dataset("json", data_files=TRAIN, split="train")

    trainer = DPOTrainer(
        model=model, ref_model=None, processing_class=tok, train_dataset=ds,
        args=DPOConfig(
            per_device_train_batch_size=2, gradient_accumulation_steps=4,
            learning_rate=5e-6, beta=0.1, num_train_epochs=1,
            max_length=2048, max_prompt_length=1024,
            bf16=True, logging_steps=10, optim="adamw_8bit",
            lr_scheduler_type="cosine", output_dir="outputs_dpo", report_to="none"),
        peft_config=LoraConfig(
            r=16, lora_alpha=16,
            target_modules=["q_proj", "k_proj", "v_proj", "o_proj"],
            lora_dropout=0, bias="none", task_type="CAUSAL_LM"))

    trainer.train()
    trainer.save_model("qwen-finance-dpo")


if __name__ == "__main__":
    main()
