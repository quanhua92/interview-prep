# Multimodal AI in Production — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Problem Framing (2-3 min)
- [ ] State the core shift: 2024 Frankenstein pipeline (OCR + Whisper + vision + TTS) collapsed into single-call frontier models
- [ ] Cite key statistics to establish scope:
  - [ ] 30-60% of enterprise documents contain critical visual information (tables, figures, scans)
  - [ ] Text-only RAG achieves 0.91 Recall@5 on text-native docs but 0.03 on scanned docs
  - [ ] Multimodal costs 3-8x more per query than text-only
  - [ ] MMMU and MMBench benchmarks saturated for frontier models
- [ ] Frame the 2026 reality: the question is no longer "should we be multimodal?" but "which provider, which evals, which guardrails?"

## Phase 2: Vision-Language Models (3-4 min)
- [ ] Walk through the three-stage processing pipeline:
  - [ ] Modality-specific encoding (vision encoder, audio encoder, text tokenization)
  - [ ] Cross-modal fusion (attention creates shared representation spaces)
  - [ ] Unified output generation (single model produces integrated response)
- [ ] Compare frontier models across the modality support matrix:
  - [ ] Gemini 2.5 Pro: native audio in + out, video (3hrs), 1M-2M context, Live API
  - [ ] Claude Opus 4.7: best image reasoning, structured JSON output, 1M context, no native audio out
  - [ ] GPT-5: all modalities, 400K context, broadest tool ecosystem
  - [ ] Claude Sonnet 4.6: 79.6% SWE-bench, cost-effective accuracy
- [ ] Cover open-source VLMs:
  - [ ] Qwen3-VL-235B: rivals Gemini/GPT-5 on multimodal benchmarks, 32-language OCR
  - [ ] GLM-4.6V: native multimodal tool calling, vision-driven tool parameters
  - [ ] DeepSeek-OCR 2: 20x compression at 97% accuracy, 2,500 tok/s on A100
  - [ ] Phi-4-multimodal: 5.6B, on-device, 6.14% WER
  - [ ] LLaMA 4 Scout: 17B MoE, 10M context, runs on single H100
- [ ] Explain token economics for images:
  - [ ] 3-10x higher per semantic unit vs text tokens
  - [ ] GPT-4o: ~765 tokens (512x512), Claude: area-based, Gemini: ~258 tokens/tile
  - [ ] Single high-res page image = tokens equivalent to ~2000 words of text
- [ ] Explain early fusion vs late fusion:
  - [ ] Early (LLaMA 4, Gemini): unified token space from input — most natural reasoning, highest compute
  - [ ] Late (GPT-4o, GPT-5): separate encoders merged at intermediate layers — easier to train
- [ ] Cover on-device multimodal:
  - [ ] Apple Foundation Models, Google Gemini Nano, Qualcomm Snapdragon
  - [ ] Two-tier pattern: local for routine, cloud for hard reasoning

## Phase 3: Multimodal RAG (4-5 min)
- [ ] Explain why text-only RAG fails on enterprise documents:
  - [ ] Scanned docs (44% of engineering firm pages — zero retrieval, not degraded)
  - [ ] Complex tables (flattened structure destroys semantics)
  - [ ] Engineering drawings (spatial relationships lost)
  - [ ] Annotated images (only caption extracted)
- [ ] Walk through the three architectural patterns:
  - [ ] OCR + text chunking: cheapest, weakest visual, high maturity
  - [ ] VLM-based ingestion: excellent visual understanding, 10-50x cost vs OCR
  - [ ] Native visual embeddings (ColPali): architecturally cleanest, 10-50x storage
- [ ] Explain ColPali architecture:
  - [ ] PaliGemma backbone, late interaction (MaxSim scoring)
  - [ ] 1030 vectors x 128 dims per page (multi-vector, not single pooled)
  - [ ] ColQwen2: Qwen2-VL backbone, 18% better on dense tables
  - [ ] Storage: 10K pages = 1.3GB (vs 50MB text), needs multi-vector DB (Qdrant)
  - [ ] Latency: 200-500ms at 100K pages, PLAID indexing optimizes
- [ ] Walk through the table extraction three-tier fallback:
  - [ ] Tier 1: pdfplumber (fast, free) → validate column consistency
  - [ ] Tier 2: Docling (neural layout, 3-5x slower)
  - [ ] Tier 3: VLM (90%+ cell accuracy, $0.01-0.05/table)
  - [ ] Only ~5-10% of tables reach VLM tier
- [ ] Present the production architecture:
  - [ ] Ingestion: classifier routes by document type → text-native, scanned, figure-heavy
  - [ ] Multi-index: text chunks, table chunks (Markdown), visual descriptions, ColPali embeddings
  - [ ] Query routing: text queries → hybrid BM25+dense, visual → ColPali+RRF, table → table index
  - [ ] Generation: modality-aware routing — ~70-85% text-only, ~15-30% with images
- [ ] Give cost and latency reality check:
  - [ ] Ingestion: $30-100 for 10K pages with selective routing (vs $100-500 all-VLM)
  - [ ] Per-query: $0.002-0.005 text-only vs $0.01-0.03 multimodal
  - [ ] Latency: 800ms-1.5s text vs 2-5s multimodal
- [ ] State when NOT to build multimodal RAG:
  - [ ] Audit corpus first; if <25% visual content, fix text-only first
  - [ ] Text RAG must be solid (faithfulness >0.80) before adding multimodal complexity

## Phase 4: Multimodal Agents (3-4 min)
- [ ] Explain the 2026 shift from multimodal input to multimodal action:
  - [ ] Agents perceive across modalities AND act in modalities
- [ ] Walk through three production patterns:
  - [ ] Screen-control agents (Project Mariner, GPT-5 computer use)
    - [ ] Screenshot → VLM → action → new screenshot → observe → next action
    - [ ] Guardrails: URL allowlists, action allowlists, loop detection (3 retries → abort)
  - [ ] Voice agents (Gemini Live API, GPT-5 Realtime)
    - [ ] Native STT + LLM + TTS in one call, <1s time-to-first-audio
    - [ ] Eliminates Whisper + ElevenLabs latency
  - [ ] Vision-grounded coding agents (Claude Opus 4.7)
    - [ ] Screenshot/mockup → working code, error screenshot → debug
- [ ] Cover native multimodal tool calling (GLM-4.6V):
  - [ ] Images as tool parameters without text conversion
  - [ ] Model interprets visual tool outputs (charts, search results, page snapshots)
- [ ] Distinguish agent vs model:
  - [ ] Agent adds autonomy (tool selection, multi-step planning, memory, loop handling)

## Phase 5: Image Understanding Pipeline (3-4 min)
- [ ] Present OCR vs VLM decision matrix:
  - [ ] OCR: clean docs 95-99%, complex 60-80%, $0.001/page, no spatial awareness
  - [ ] VLM: complex 85-95%, $0.01-0.05/page, full spatial understanding
  - [ ] Decision rule: OCR first, validate, fall back to VLM on failure
- [ ] Walk through layout-aware parsing tools:
  - [ ] pdfplumber: fast, free, programmatic table extraction
  - [ ] Docling: neural layout analysis, best on merged cells, 3-5x slower
  - [ ] Marker: layout + table + OCR pipeline, 87% vs 63% naive extraction
  - [ ] Azure/Google Document Intelligence: enterprise-grade, $0.01-0.05/page
- [ ] Cover preprocessing best practices:
  - [ ] DPI normalization (150-300 minimum), format (PNG preferred), deskewing, cropping

## Phase 6: Video + Audio (3-4 min)
- [ ] Video understanding in 2026:
  - [ ] Gemini 2.5 Pro: up to 3 hours video
  - [ ] Qwen3-VL: 256K-1M context, second-level indexing
  - [ ] Frame sampling strategies: uniform, keyframe, adaptive, semantic, full native
- [ ] Token economics for video:
  - [ ] 30s video ≈ $0.01, 5min ≈ $0.10, 3hrs ≈ $3.50
  - [ ] Video is most expensive modality — implement selective processing
- [ ] Voice agent architecture:
  - [ ] Native STT/TTS (Gemini Live, GPT-5 Realtime) — <1s total
  - [ ] External pipeline (Whisper + LLM + ElevenLabs) — 2-4s total
  - [ ] Latency budget: STT <200ms, LLM <500ms, TTS <200ms
- [ ] On-device ASR: Phi-4-multimodal 5.6B, 6.14% WER

## Phase 7: Production Patterns (3-4 min)
- [ ] Walk through cost management strategies:
  - [ ] Modality-aware routing (50-70% savings)
  - [ ] Selective VLM ingestion (60-75% fewer VLM calls)
  - [ ] Semantic caching (30-50% hit rate)
  - [ ] Model tiering (Haiku/4o-mini for extraction, frontier for synthesis)
  - [ ] Resolution management (minimum viable DPI)
  - [ ] Prompt caching (10-30% on Claude/GPT)
- [ ] Present latency budget:
  - [ ] Document search: 5s SLA — query routing <50ms, retrieval <200ms, ColPali <500ms, LLM <4s
  - [ ] Voice agent: <1s SLA — requires native STT/TTS
- [ ] Walk through fallback chain:
  - [ ] Frontier VLM → alternative provider → open-source → text-only pipeline → error
- [ ] Explain on-device vs cloud tiering:
  - [ ] Complexity estimator routes simple tasks on-device, complex to cloud
- [ ] Cover caching types:
  - [ ] Exact match (image hash + text query), semantic, VLM description cache, prompt cache

## Phase 8: Multimodal Evaluation (3-4 min)
- [ ] Explain benchmark saturation:
  - [ ] MMMU, MMBench near-saturated for frontier models
  - [ ] ViDoRe still useful for ColPali/ColQwen2 comparison
- [ ] Present custom regression set design:
  - [ ] 30-50 QA pairs per document type, edge cases included
  - [ ] Frozen reference set in git, CI-gated
- [ ] Explain cross-modal consistency metric:
  - [ ] 1.0 (correct fusion), 0.5 (partial), 0.0 (ignores modality or contradicts)
  - [ ] Implemented via LLM-as-judge
- [ ] Cover observability requirements:
  - [ ] Trace attributes: input modalities, image token count, retrieval index used, VLM model
  - [ ] Tools: OpenInference + traceAI (Apache 2.0)
- [ ] Present evaluation framework levels:
  - [ ] Level 1: Unit tests (per-doc extraction accuracy)
  - [ ] Level 2: Component tests (retrieval by type, cross-modal consistency)
  - [ ] Level 3: Integration tests (end-to-end, latency by path, cost by modality)
  - [ ] Level 4: Shadow evaluation (new model on production traffic)
  - [ ] Level 5: Online A/B (canary 1-5%, automated rollback)

## Phase 9: System Design Bridge (2-3 min)
- [ ] Connect to related topics:
  - [ ] LLM in production: model portfolio management, LLM gateways for multi-provider routing
  - [ ] AI safety: multimodal prompt injection (steganography), PII across modalities
  - [ ] RAG system: core RAG architecture extended with visual indexing
  - [ ] Senior AI engineer: agent design extended with vision-enabled agents
  - [ ] Cost engineering: token economics for images, audio, video
  - [ ] SLO/error budgets: higher latency budgets for visual, tighter for voice
- [ ] Emphasize: start with text-only RAG, audit corpus, add multimodal incrementally where evidence justifies

## Phase 10: Wrap-Up & Synthesis (2-3 min)
- [ ] Summarize the 8 topic areas covered
- [ ] Reiterate the core insight: multimodal is the default in 2026, but the 3-8x cost multiplier requires disciplined architecture
- [ ] Key takeaway: modality-aware routing and selective VLM usage are the two most impactful cost optimization patterns
- [ ] Connect to evaluation: custom regression sets > saturated public benchmarks
- [ ] Ask the interviewer if they have questions

## Practice Questions

1. Compare Gemini 2.5 Pro, Claude Opus 4.7, and GPT-5 for a production document understanding system. Which do you choose and why?
2. Design a multimodal RAG system for a law firm with 50,000 scanned contracts including handwritten annotations and tables.
3. What is ColPali? How does it differ from standard text-based RAG? When would you use it vs VLM-based ingestion?
4. How do you manage cost in a multimodal pipeline? Walk through the math for 10,000 daily queries with 30% visual processing.
5. Design a screen-control agent for automating CRM updates from email attachments. What guardrails do you implement?
6. Explain early fusion vs late fusion in multimodal models. Why does the distinction matter for production systems?
7. Your multimodal RAG system has 0.92 faithfulness on text documents but 0.65 on table/diagram documents. How do you diagnose and fix this?
8. Design a voice agent for customer support. What is your latency budget and architecture?
9. How do you evaluate a multimodal system when public benchmarks are saturated? What does your evaluation framework look like?
10. What production challenges of multimodal AI don't exist in text-only systems?
11. A user uploads a mix of photos and documents to your RAG system. How does your system handle the different content types?
12. Design the ingestion pipeline for 1 million financial documents (10M pages) with mixed native PDFs, scanned PDFs, and images.

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
