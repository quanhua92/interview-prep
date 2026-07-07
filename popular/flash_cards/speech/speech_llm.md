# Speech LLM & Voice Agents (Flashcards)

Click the bold text to reveal the answer. Click the file link for the full deep dive.

---

<details><summary><b>Design a low-latency voice agent (TTFA &lt; 500 ms, with barge-in)</b></summary>

Topic: Voice Agent Architecture
Key concepts:
- Batch pipelines (speak → full ASR → LLM → full TTS) accumulate 2.5-4.0 s; a fully streaming pipeline keeps TTFA under 500 ms by overlapping stages.
- Latency budget: VAD 20 ms → streaming ASR (FastConformer-RNNT, 80 ms chunks) 120 ms → orchestrator 10 ms → LLM prefill/TTFT 150 ms → decode chunk 50 ms → streaming TTS (FastPitch + Vocos) 90 ms → client jitter buffer 30 ms ≈ 470 ms.
- Barge-in: hybrid energy + neural VAD cancels ongoing TTS playback and resets prompt state; an async orchestrator supports cooperative dual-model responders (fast backchannel vs. deep reasoning).
File: [speech_llm_voice_agent_architecture.md](../../speech_llm_voice_agent_architecture.md)
</details>

<details><summary><b>What metrics diagnose a speech pipeline, and why is decoding memory-bound?</b></summary>

Topic: Speech LLM Latency Optimization & Profiling
Key concepts:
- Quality: WER = (S+D+I)/N; PESQ (-0.5-4.5, need > 3.8 for production); MCD (mel-cepstral distance, lower = closer timbre). Latency: RTF (real-time factor), TTFT, TTFA.
- Roofline analysis: streaming LLM decode and TTS vocoders are memory-bound because each token/vocoder step reads the full model weights from HBM for tiny arithmetic intensity → arithmetic/byte ratio sits below the roofline knee.
- Levers: TensorRT-LLM in-flight batching + Paged KV Cache cut memory waste; FP8 quantization halves weight bytes/step, raising tokens/s/GPU toward a < 500 ms TTFA target.
File: [speech_llm_latency_optimization.md](../../speech_llm_latency_optimization.md)
</details>

<details><summary><b>Walk through the NeMo → Riva NIM deploy flow and NeMo Guardrails</b></summary>

Topic: NVIDIA Speech Stack & Guardrails
Key concepts:
- NeMo fine-tunes ASR (FastConformer, 8x downsampling) and TTS (FastPitch). CTC decoder is fast but assumes frame independence; RNNT adds a prediction network for lower WER at higher decode cost.
- Riva NIM packages the fine-tuned checkpoint and compiles it via Triton/TensorRT for low-latency serving; the pipeline exposes streaming ASR/TTS behind one runtime.
- NeMo Guardrails (Colang) enforces Sovereign AI policy: input/output rails, dialog rails, and retrieval rails block PII leakage, jailbreaks, and off-topic answers via a configurable rail graph.
File: [speech_llm_nemo_riva_stack.md](../../speech_llm_nemo_riva_stack.md)
</details>

<details><summary><b>How do native multimodal Audio-Language Models work (audio tokenization)?</b></summary>

Topic: Multimodal Audio-Language Models (ALMs)
Key concepts:
- Cascaded STT→LLM→TTS pipelines lose paralinguistics (emotion, accent) and propagate errors; native ALMs ingest and emit audio tokens end-to-end to preserve prosody.
- Audio tokenization via neural codecs (EnCodec, SoundStream, DAC) using Residual Vector Quantization (RVQ): a continuous waveform becomes stacks of discrete codebook indices that an LLM can attend to like text tokens.
- Continuous features (Whisper/AST encoders) are bridged to the LLM via projection (Linear/MLP/Q-Former); outputs are decoded back to waveforms by vocoders (HiFi-GAN, Vocos, BigVGAN). SOTA: GPT-4o voice, AudioPaLM, SeamlessM4T.
File: [speech_llm_multimodal_audio_language_models.md](../../speech_llm_multimodal_audio_language_models.md)
</details>

<details><summary><b>How do you benchmark and evaluate a voice agent in production?</b></summary>

Topic: Voice Agent Benchmarking & Evaluation
Key concepts:
- Speech quality: PESQ (narrow/wideband, -0.5-4.5), POLQA (super-wide/full-band, 1.0-4.75), ViSQOL, MCD. Transcription: WER and CER.
- Latency: TTFT (time to first token) vs TTFA (time to first audio), plus barge-in success rate and turn-taking accuracy under noise/reverb/clipping/packet loss.
- Automated simulator injects acoustic noise and network jitter, drives multi-turn scenarios, and uses LLM-as-a-judge to grade task success and conversational naturalness across percentiles.
File: [speech_llm_agent_benchmarking_evaluation.md](../../speech_llm_agent_benchmarking_evaluation.md)
</details>

---

[Flashcard Index](../README.md)
