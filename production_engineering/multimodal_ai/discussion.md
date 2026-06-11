# Multimodal AI in Production

Sources:
- [Multimodal AI in 2026: GPT-5, Claude Opus 4.7, Gemini 2.5 Pro Picked Apart (Future AGI)](https://futureagi.com/blog/multimodal-ai-2025/)
- [Top 6 Multimodal AI Models Leading Innovation in 2026 (Kanerika)](https://kanerika.com/blogs/multimodal-ai/)
- [Multimodal AI: Complete Guide to Next-Gen Systems 2026 (Ruh AI)](https://www.ruh.ai/blogs/multimodal-ai-complete-guide-2026)
- [Multimodal AI: The Best Open-Source Vision Language Models in 2026 (BentoML)](https://www.bentoml.com/blog/multimodal-ai-a-guide-to-open-source-vision-language-models)
- [Multimodal RAG: Retrieving from Images, PDFs, and Tables (Tensoria)](https://tensoria.fr/en/blog/multimodal-rag-images-pdfs-tables)
- [ColPali: Redefining Multimodal RAG (LearnOpenCV)](https://learnopencv.com/multimodal-rag-with-colpali/)
- [Multi-Modal RAG with ColPali on Azure Kubernetes Service (Microsoft)](https://github.com/microsoft/multi-modal-rag-with-colpali)
- [The Best Open Source LLM for Document Screening in 2026 (SiliconFlow)](https://www.siliconflow.com/articles/en/best-open-source-LLM-for-Document-screening)
- [Multimodal AI Enterprise Applications: 2026 Production Guide (BuildMVPFast)](https://www.buildmvpfast.com/blog/multimodal-ai-enterprise-production-applications-2026)
- [5 AI Priorities Every Enterprise Must Get Right in 2026 (Konica Minolta)](https://kmbs.konicaminolta.us/blog/5-ai-priorities-every-enterpeise-must-get-right-in-2026/)
- [LLM Research Papers: The 2026 List (Sebastian Raschka)](https://magazine.sebastianraschka.com/p/llm-research-papers-2026-part1)

## One-Liner
Multimodal AI in production means building systems that natively process text, images, audio, and video in unified inference pipelines — replacing the 2024-era Frankenstein of OCR + Whisper + separate vision + TTS glue code with single-call frontier models, vision-native RAG, and multimodal agents — while managing the 3-8x cost multiplier, latency budgets, and evaluation complexity that come with cross-modal reasoning.

## Core Competencies Table

| Area | Description | Proficiency Expectation |
|------|-------------|------------------------|
| Vision-Language Models | Frontier VLMs (GPT-5, Gemini 2.5 Pro, Claude Opus 4.7), open-source VLMs (Qwen3-VL, GLM-4.6V, DeepSeek-OCR), architecture (early fusion vs late fusion), modality support matrix, context windows, token economics for images | Compare frontier VLMs across modality support, context window, cost, and deployment model; choose the right model for a given production use case with latency and cost justification |
| Multimodal RAG | ColPali/ColQwen2 native visual retrieval, VLM-based ingestion, OCR fallback chains, table extraction (pdfplumber → Docling → VLM), multi-index retrieval, query routing, hybrid text + visual search | Design a multimodal RAG pipeline for an enterprise document corpus with mixed text/table/diagram content; justify architecture choices with cost and latency analysis |
| Multimodal Agents | Screen-control agents (Project Mariner, GPT-5 computer use), vision-grounded coding agents, document processing agents, multimodal tool calling, agentic perception and action patterns | Design a vision-enabled agent that reads UI screenshots and takes actions; implement guardrails, allowlists, and observability for screen-control workflows |
| Image Understanding Pipeline | Preprocessing (resolution, format, DPI), OCR vs VLM decision matrix, structured extraction from images, layout-aware parsing (Docling, Marker, Unstructured), VLM fallback for complex tables | Design an image-to-structured-data pipeline with OCR + VLM fallback; explain when each technology is appropriate and the cost-quality tradeoffs |
| Video Understanding | Frame sampling strategies, temporal analysis, video-native models (Gemini 2.5 Pro, Qwen3-VL 256K context), production constraints (storage, latency, cost) | Design a video analysis pipeline for a production use case; explain frame sampling, token economics for video, and when to use video-native models vs frame extraction |
| Audio + Speech | Speech-to-text with LLMs, text-to-speech, voice agents (Gemini Live API, GPT-5 Realtime), on-device ASR (Phi-4-multimodal), latency budgets for real-time voice | Design a voice agent pipeline with sub-second time-to-first-audio; explain the architecture of real-time speech-to-speech systems |
| Production Patterns | Cost management (3-8x multiplier), latency budgets per modality, semantic caching for multimodal, fallbacks, model routing, on-device vs cloud tiering | Calculate total cost of ownership for a multimodal pipeline; design a model routing strategy that minimizes cost while maintaining quality SLAs |
| Multimodal Evaluation | Cross-modal consistency metrics, custom regression sets, LLM-as-judge for visual outputs, benchmark saturation (MMMU), observability across modalities | Design an evaluation framework for a multimodal system; explain why public benchmarks are saturated and how to build domain-specific evals |

## 1. Vision-Language Models

### The Multimodal Shift: 2024 to 2026

The 2024 multimodal stack was a Frankenstein pipeline: OCR pulled text from images, Whisper transcribed audio, a separate vision model captioned scenes, an LLM stitched everything together, and a TTS service generated voice output. Five services, four pipelines, dozens of moving parts.

By mid-2026, that collapsed. GPT-5 accepts text, image, audio, and video in one prompt. Claude Opus 4.7 ships strong vision plus structured outputs. Gemini 2.5 Pro adds native audio output through the Live API. Multimodal is no longer a feature — it is the default API surface.

**Production implication**: A receipt-to-CRM workflow that needed OCR + parser + LLM is one API call. A meeting-to-action-items workflow that needed Whisper + GPT-4 + TTS is one Live API call. If your product still has separate vision, audio, and text branches in 2026, you are paying for plumbing that does not need to exist.

### Three-Stage Multimodal Processing

All multimodal models follow the same three-stage architecture:

1. **Modality-Specific Encoding** — Each input type is processed by specialized encoders: vision encoder for images (typically ViT-based), audio encoder for speech (spectrogram-based), text tokenization for language input
2. **Cross-Modal Fusion** — Attention mechanisms create shared representation spaces where information from different modalities interacts. Early fusion (LLaMA 4: unified token space from the start) vs late fusion (separate encoders merged at intermediate layers) vs intermediate fusion (interaction at various transformer layers)
3. **Unified Output Generation** — Single model produces responses integrating all modalities. No separate vision model + language model stitched together

### Frontier Model Comparison (May 2026)

| Model | Image | Audio In | Audio Out | Video In | Context | Structured Output | Best For |
|-------|-------|----------|-----------|---------|---------|-------------------|----------|
| **Gemini 2.5 Pro** | Yes | Native | Native TTS | Yes (3hrs) | 1M–2M (Vertex) | Yes | Voice assistants, video analysis, long multimodal docs |
| **Claude Opus 4.7** | Yes | Limited | No (text only) | Limited | 1M | Yes (JSON/tool calls) | Document understanding, screen reading, image-grounded coding |
| **GPT-5** | Yes | Yes | Yes | Yes | 400K | Yes | General purpose, broad tool ecosystem |
| **GPT-5.5** | Yes | Yes | Yes | Limited | 1M (128K output) | Yes | Sustained reasoning, complex professional workflows |
| **Claude Sonnet 4.6** | Yes | Limited | No | Limited | 200K (1M beta) | Yes | Agentic coding, cost-effective accuracy (79.6% SWE-bench) |

### Open-Source VLMs

| Model | Params | Context | Key Strength | Notes |
|-------|--------|---------|-------------|-------|
| **Qwen3-VL-235B-A22B** | 235B (22B active MoE) | 256K–1M | Visual agents, 32-language OCR, video understanding | Rivals Gemini 2.5 Pro and GPT-5 on multimodal benchmarks |
| **GLM-4.6V** | 106B (9B Flash) | 128K | Native multimodal tool calling, frontend replication | Vision-driven tool use: images as tool parameters without text conversion |
| **DeepSeek-OCR 2** | 3B (MoE) | Long document | Document extraction, 10x visual compression at 97% accuracy (accuracy degrades at higher ratios) | 2,500 tokens/sec on single A100-40G; 100-language OCR |
| **Molmo-72B** | 72B (1B/7B variants) | Standard | Pointing capabilities, open architecture | Can "point" to visual elements; useful for web agents |
| **Pixtral 12B** | 12B | 128K | Instruction following, multi-image processing | Apache 2.0 license; no built-in moderation |
| **Gemma 3** | 1B–27B | 128K (32K for 1B) | On-device, 35+ languages, function calling | Lightweight; limited video comprehension |
| **Phi-4-multimodal** | 5.6B | 128K | Edge/on-device, voice + vision | 6.14% WER on OpenASR leaderboard |
| **LLaMA 4 Scout** | 17B (MoE) | 10M | Long-document analysis, open-source, data residency | Runs on single H100; 10M token context window |
| **LLaMA 4 Maverick** | 400B+ (MoE) | 1M | Strong general multimodal | More infrastructure than Scout |

### Token Economics for Images

Image inputs consume tokens differently than text, and the cost varies significantly by model:

| Model | Image Token Cost (512x512) | High-Detail Mode | Cost per Image (approx.) |
|-------|---------------------------|-------------------|--------------------------|
| GPT-4o/GPT-5 | ~765 tokens | ~1105 tokens | $0.004–0.006 |
| Claude (Opus/Sonnet) | Variable (area-based) | Higher resolution = more tokens | $0.003–0.008 |
| Gemini 2.5 Pro | ~258 tokens (per 768px tile) | Up to 16 tiles per image | $0.001–0.005 |

**Key insight**: Image token costs are 3-10x higher per "semantic unit" than text tokens. A single high-resolution page image can consume as many tokens as 2000 words of text. This is the primary driver of the 3-8x cost multiplier for multimodal vs text-only pipelines.

### Architecture Patterns: Early vs Late Fusion

| Pattern | Description | Models | Tradeoff |
|---------|-------------|--------|----------|
| **Early Fusion** | Vision and text tokens share a unified vocabulary and attention space from input | LLaMA 4, Gemini 2.5 Pro | Most natural cross-modal reasoning; highest compute cost |
| **Late Fusion** | Separate vision encoder + language model, merged at intermediate layers | GPT-4o, GPT-5 | Easier to train; slightly less natural cross-modal transfer |
| **Intermediate Fusion** | Cross-attention layers connect modality-specific streams | Many research models | Flexible but complex to implement |

### On-Device Multimodal (2026 State)

| Platform | Model | Capabilities | Latency |
|----------|-------|-------------|----------|
| **Apple Intelligence** | Apple Foundation Models | Image input, text generation, ASR | Local only |
| **Google Pixel** | Gemini Nano | Image understanding, on-device summarization | Sub-100ms |
| **Qualcomm Snapdragon** | Various sub-3B models | Multimodal on Android | Local only |

**Production pattern**: Two-tier architecture — small local model for routine multimodal tasks (PII redaction, basic document scanning), cloud frontier model for hard reasoning. Apple Foundation Models API and Google AI Core expose routing natively.

## 2. Multimodal RAG

### Why Text-Only RAG Fails on Enterprise Documents

Standard RAG assumes documents are text-extractable. This breaks in four common ways:

| Failure Mode | Prevalence | Impact |
|-------------|-----------|--------|
| **Scanned documents with no text layer** | 44% of pages in engineering firms (observed) | Zero retrieval capability — not degraded, absent |
| **Tables with complex structure** | 30-60% of enterprise docs contain tables | Flattened structure destroys row-column semantics |
| **Engineering/technical drawings** | Common in manufacturing, construction | Spatial relationships lost in text extraction |
| **Annotated images and figures** | Maintenance photos, diagrams, infographics | Only caption extracted; figure content invisible |

**Key stat**: On a RAG project for an engineering firm, text-only retrieval achieved Recall@5 of 0.91 on text-native documents but 0.03 on scanned documents. The overall metric was misleading because it averaged over a corpus where nearly half the documents were effectively invisible.

### Three Architectural Patterns for Multimodal RAG

#### Pattern 1: OCR + Text Chunking

Convert images to text using OCR, then index normally.

- **Maturity**: High — integrates with existing pipeline
- **Visual understanding**: Weak — OCR destroys spatial layout, mangles tables
- **Cost**: Low (~$0.001/page)
- **Latency**: Low (~200ms)
- **Best for**: Simple scanned text, incremental addition to existing pipeline

#### Pattern 2: VLM-Based Ingestion

Render each page to a high-resolution PNG, send to a VLM (GPT-4o, Claude, Gemini) during ingestion to generate structured text descriptions or extract structured data. At query time, optionally send page images to the LLM for visual grounding.

- **Maturity**: Good
- **Visual understanding**: Excellent — preserves table structure, figure content, spatial relationships
- **Cost**: High ($0.01–0.05/page)
- **Latency**: High (2–5s at generation time)
- **Best for**: Complex tables, diagrams, high-accuracy document understanding

**Implementation detail**: Render at 150–200 DPI minimum (300 DPI sweet spot). Use domain-specific prompts: financial reports need "Reproduce all financial tables in Markdown"; engineering documents need "Identify component labels, measurements, reference codes."

#### Pattern 3: Native Visual Embeddings (ColPali)

Encode pages directly as visual embeddings, skipping OCR. Retrieval operates entirely in visual embedding space. Retrieved page images passed to VLM for generation.

- **Maturity**: Emerging (production-ready with caveats)
- **Visual understanding**: Good — handles dense tables, diagrams, visual layout
- **Cost**: Medium (compute for encoding)
- **Latency**: Medium (500ms–1s retrieval)
- **Best for**: Visually rich corpora, slides, reports, no OCR tolerance

### ColPali: Architecture and Tradeoffs

ColPali (Faysse et al., 2024) encodes entire page images into multi-vector embeddings using a PaliGemma backbone. Key innovation: **late interaction** — rather than compressing a page into a single pooled vector (losing spatial/typographic structure), ColPali produces a 1030-token embedding matrix (one vector per image patch). At query time, **MaxSim scoring** computes maximum dot product between each query token and all page patch embeddings, enabling fine-grained alignment between query terms and specific page regions.

**ColQwen2** (Qwen2-VL backbone) extends ColPali with stronger multilingual document understanding and better performance on dense tables. In tests on financial reports, ColQwen2 retrieves correct table pages 18% more often than ColPali-3B on queries referencing specific row/column values.

**Practical constraints**:

| Constraint | Detail |
|-----------|--------|
| **Storage** | ~1030 vectors x 128 dims per page. 10K-page corpus = ~1.3GB float32 (vs ~50MB for text embeddings). 10–50x larger than text index. |
| **Latency** | MaxSim over large index: 200–500ms at 100K pages without optimization. PLAID-style indexing (centroid compression) reduces significantly. |
| **Vector DB requirement** | Need multi-vector storage: Qdrant multi-vector collections most production-ready in 2026 |
| **Fine-tuning** | Out-of-box works on generic documents; underperforms on specialized domains. Needs 500–2000 domain-specific query pairs for fine-tuning. |

### Table Extraction Pipeline (Production Pattern)

The three-tier fallback pattern that handles 95%+ of enterprise PDF tables:

```
Tier 1: pdfplumber (fast, free)
  → Validate: column count consistent, <15% empty cells
  → If valid: convert to Markdown, index

Tier 2: Docling (neural layout analysis, 3-5x slower)
  → Validate: same checks
  → If valid: convert to Markdown, index

Tier 3: VLM extraction (expensive, highest accuracy)
  → Send cropped table image to GPT-4o or Claude
  → Structured prompt for Markdown output
  → 90%+ cell accuracy on standard tables, 75%+ on merged cells
  → Cost: $0.01–0.05 per table
```

### Production Multimodal RAG Architecture

```
INGESTION:
  Document → Classifier (rule-based)
    → Text-native (>100 chars/page): text extraction + table extraction (pdfplumber/Docling)
    → Scanned (<100 chars/page): OCR + VLM ingestion for complex pages
    → Figure-heavy (>40% image area): augment with VLM descriptions
  → Index types: text chunks, table chunks (Markdown), visual description chunks, ColPali embeddings (optional)

RETRIEVAL:
  Query → Query Classifier
    → Text queries: hybrid BM25 + dense retrieval, cross-encoder reranking
    → Visual queries ("the diagram on...", "the chart showing..."): ColPali index + RRF fusion
    → Table queries (numerical precision): table-specific index + page image to VLM

GENERATION:
  Text-only retrieval → Standard LLM (cheaper)
  Visual retrieval → Multimodal LLM (GPT-4o, Claude, Gemini) with both text chunks + source page images

ROUTING:
  ~70–85% queries use text-only path
  ~15–30% queries consume image tokens at generation time
  Significant per-query cost savings from modality-aware routing
```

### Cost and Latency Reality Check

| Metric | Text-Only RAG | Multimodal RAG | Multiplier |
|--------|--------------|----------------|------------|
| **Ingestion cost (10K pages)** | $5–20 | $30–500 | 3–25x (depends on routing) |
| **Per-query cost** | $0.002–0.005 | $0.01–0.03 | 3–8x |
| **Response latency P95** | 800ms–1.5s | 2–5s | 2–3x |
| **ColPali storage (10K pages)** | N/A | ~1.3GB | 26x vs text embeddings |
| **Monthly storage cost (10K pages)** | ~$0.01 | ~$0.03–0.13 | 3–13x |

**When NOT to build multimodal RAG**: Before investing, audit your corpus. If <25% of documents carry critical visual information, fix text-only RAG first (chunking, hybrid search). Multimodal RAG is not a drop-in upgrade — it requires a more complex ingestion pipeline, more expensive infrastructure, and more disciplined observability.

## 3. Multimodal Agents

### The 2026 Shift: Perception Plus Action

The bigger 2026 shift is not just multimodal input — it is multimodal action. An agent perceives across modalities (text, image, audio, video) and acts in modalities (typed text, generated images, voice output, screen control).

### Three Production Patterns

#### Pattern 1: Screen-Control Agents

A model reads a screenshot, decides what to click or type, and acts in a browser or app. Gemini 2.5 Pro's Project Mariner and OpenAI's computer-use API both ship this.

**Architecture**:
```
Screenshot → VLM (action planning) → Action execution (browser automation)
  → New screenshot → VLM (observe result) → Next action...
```

**Production requirements**:
- Guardrails on every action (allowlist URLs, block destructive operations)
- URL allowlists to prevent navigating to unauthorized sites
- Observability on every step (screenshot + action + reasoning logged)
- Persona-driven simulation before launch (load test with realistic user flows)
- Human-in-the-loop for high-risk actions (payments, data deletion, settings changes)
- Loop detection: if same action repeats 3+ times, abort with diagnostic

#### Pattern 2: Voice Agents

A model accepts spoken input, reasons, and speaks back. Gemini Live API and GPT-5 Realtime API support this with sub-second time-to-first-audio.

**Architecture**:
```
Audio stream → STT (native, not separate) → LLM reasoning → TTS (native, not separate) → Audio stream
```

**Key**: In 2026, STT and TTS are integrated into the model itself, not separate services. This eliminates the latency of external speech processing pipelines and enables natural conversational flow.

#### Pattern 3: Vision-Grounded Coding Agents

A model accepts a screenshot of a UI mockup or diagram and produces working code. Claude Opus 4.7 leads here.

**Use cases**: Design-to-code conversion, debugging from error screenshots, reviewing architecture diagrams, generating frontend code from UI designs.

### Multimodal Tool Calling

GLM-4.6V introduces native multimodal tool use: images, UI screenshots, and visual snippets provided directly as tool parameters without converting to text first. The model also interprets visual outputs returned by tools (charts, search results, webpage snapshots).

**Production benefit**: Reduces information loss from modality conversion and lowers system complexity compared with text-only tool pipelines.

### Agent vs Model: Key Distinction

| Aspect | Multimodal Model | Multimodal Agent |
|--------|-----------------|-------------------|
| Autonomy | Requires external direction per task | Decides which tools to use, plans multi-step sequences |
| Memory | Single context window | Short-term (conversation) + long-term (knowledge base) |
| Action | Generates responses | Calls functions, interacts with APIs, controls systems |
| Loop handling | None | Detects loops, manages retries, escalates failures |

## 4. Image Understanding Pipeline

### OCR vs VLM Decision Matrix

| Factor | OCR (Tesseract, Azure DI, Google DocAI) | VLM (GPT-4o, Claude, Gemini) |
|--------|----------------------------------------|------------------------------|
| **Best for** | Clean, structured text; high-volume bulk processing | Complex layouts, tables, diagrams, handwriting |
| **Accuracy (clean docs)** | 95–99% | 95–99% |
| **Accuracy (complex)** | 60–80% (tables, handwriting, noise) | 85–95% |
| **Cost per page** | $0.001–0.01 | $0.01–0.05 |
| **Latency** | 100–500ms | 1–5s |
| **Spatial awareness** | None (produces flat text) | Full (understands layout, position, relationships) |
| **Structured output** | Raw text, needs post-processing | Direct Markdown/JSON extraction |

**Decision rule**: Use OCR for high-volume clean documents. Use VLM for complex layouts, tables with merged cells, handwriting, or when spatial understanding matters. In production, run OCR first and validate output; fall back to VLM when validation fails.

### Layout-Aware Parsing Tools

| Tool | Approach | Table Accuracy | Speed | Cost |
|------|----------|---------------|-------|------|
| **pdfplumber** | Programmatic table extraction from native PDFs | Good (structured tables) | Fast | Free |
| **Camelot** | Stream-mode (whitespace) + lattice-mode (line-based) | Good (two detection modes) | Fast | Free |
| **Docling (IBM)** | Neural layout analysis (DocLayNet) + specialized extractors | Very good (merged cells) | 3–5x slower than pdfplumber | Free (self-hosted) |
| **Marker (Datalab)** | Layout detection + table recognition + OCR pipeline | Good (87% on mixed PDFs vs 63% naive) | Medium | Free (self-hosted) |
| **Unstructured.io** | Element classification + coordinate-based table detection | Good (HTML output preserves structure) | Medium | Free / hosted API |
| **Azure Document Intelligence** | Cloud OCR with layout analysis | Excellent (enterprise-grade) | 500ms–2s | $0.01–0.05/page |
| **Google Document AI** | Cloud OCR with specialized processors | Excellent | 500ms–2s | $0.01–0.05/page |

### Structured Extraction from Images

**Production pattern for invoice/receipt processing**:
```
1. Preprocessing: resize to 300 DPI, deskew, binarize if needed
2. Classification: is this an invoice, receipt, contract, or other?
3. OCR extraction: fast text extraction with layout
4. Field extraction: amount, date, vendor, line items (regex + NER + VLM)
5. Table extraction: line items table (pdfplumber → Docling → VLM fallback)
6. Validation: cross-check extracted fields (date format, amount ranges, vendor lookup)
7. Confidence scoring: flag low-confidence extractions for human review
```

### Image Preprocessing Best Practices

| Step | Why | Implementation |
|------|-----|---------------|
| **DPI normalization** | Below 100 DPI, small text unreliable for VLMs | Render at 150–300 DPI minimum |
| **Format standardization** | Some models prefer PNG over JPEG | Convert to PNG for highest quality |
| **Deskewing** | Rotated images reduce OCR accuracy | OpenCV `minAreaRect` or specialized tools |
| **Binarization** | Improves OCR on low-contrast documents | Adaptive thresholding for noisy scans |
| **Cropping** | Remove margins/headers that consume image tokens | PyMuPDF bounding box extraction |
| **Multi-page splitting** | Process one page at a time for granular retrieval | PyMuPDF page-by-page rendering |

## 5. Video Understanding

### Video as a Modality in 2026

Video understanding has matured significantly. Gemini 2.5 Pro processes up to 3 hours of video. Qwen3-VL handles video with 256K token context (expandable to 1M) with second-level indexing. GPT-5 supports native video input.

### Frame Sampling Strategies

| Strategy | Description | When to Use | Tradeoff |
|----------|-------------|-------------|----------|
| **Uniform sampling** | Extract frames at fixed intervals (e.g., 1 fps) | General video analysis | Simple but may miss key moments |
| **Keyframe extraction** | Detect scene changes, extract keyframes | Long videos with distinct scenes | Efficient but misses gradual changes |
| **Adaptive sampling** | More frames for complex scenes, fewer for static | Production quality analysis | Higher accuracy, more compute |
| **Semantic sampling** | Use CLIP/SigLIP to select visually diverse frames | Search and retrieval over video | Best for building video indices |
| **Full video (native)** | Feed entire video to video-native model | Short videos, high-value content | Highest quality, highest cost |

### Token Economics for Video

| Video Length | Frames (1fps) | Approx Tokens (Gemini) | Approx Cost |
|-------------|--------------|----------------------|-------------|
| 30 seconds | 30 | ~7,500 | $0.01 |
| 5 minutes | 300 | ~75,000 | $0.10 |
| 30 minutes | 1,800 | ~450,000 | $0.60 |
| 3 hours | 10,800 | ~2.7M | ~$3.50 |

### Production Video Pipeline

```
Video Input
  → Preprocessing (format conversion, resolution normalization)
  → Frame Sampling (strategy depends on use case)
  → Frame Selection (keyframe / semantic / uniform)
  → Encoding (image encoding per frame or video-native model)
  → Analysis (VLM per frame OR video-native model)
  → Temporal Reasoning (cross-frame analysis, event detection)
  → Output (structured extraction, summary, alert)
```

### Production Considerations

- **Storage**: Video files are large; consider frame extraction at ingest time rather than reprocessing
- **Latency**: Video-native models (Gemini) can process long video but at significant latency; frame-by-frame VLM is more parallelizable
- **Cost**: Video is the most expensive modality; implement selective processing (only analyze flagged segments)
- **Real-time**: For live video analysis, use streaming frame extraction with lightweight models (Gemma 3 4B, Phi-4-multimodal) for detection, escalate to frontier model for detailed analysis

## 6. Audio + Speech

### Speech-to-Speech Architecture in 2026

The 2024 pipeline was: Audio → Whisper (STT) → LLM → ElevenLabs (TTS) → Audio. Three separate services, 2–4 seconds of latency, context lost at each modality boundary.

By 2026, frontier models integrate STT and TTS natively:

| Model | STT + TTS Integrated | Time to First Audio | Voice Customization |
|-------|---------------------|--------------------|--------------------|
| **Gemini 2.5 Pro (Live API)** | Yes | <1s | Adjustable voices, emotive styles |
| **GPT-5 (Realtime API)** | Yes | <1s | Preset voices |
| **Phi-4-multimodal** | STT only (6.14% WER) | N/A | On-device ASR |

### Voice Agent Architecture

```
Audio Stream (WebRTC/WebSocket)
  → Native STT (integrated in model)
  → LLM Reasoning (with conversation context)
  → Native TTS (integrated in model)
  → Audio Stream Output

Latency budget:
  STT: <200ms (native, not external)
  LLM reasoning: <500ms
  TTS: <200ms (native, not external)
  Network overhead: <100ms
  Total target: <1s time-to-first-audio
```

### STT/TTS for Non-Voice-Native Models

When using models without native audio (e.g., Claude, which has limited audio):

| Component | Tool Options | Latency | Quality |
|-----------|-------------|---------|---------|
| **STT** | Whisper large-v3, Deepgram Nova-2, AssemblyAI | 200–500ms | WER 3–6% |
| **TTS** | ElevenLabs, PlayHT, Azure Neural TTS, OpenAI TTS | 75–200ms | Natural prosody, voice cloning |
| **Streaming** | WebSocket, Server-Sent Events | Per-token | Enables conversational flow |

### On-Device ASR

Phi-4-multimodal (5.6B params) leads the HuggingFace OpenASR leaderboard with 6.14% WER. Designed for mobile and edge deployment where cloud round-trips are too slow or data privacy requires local processing.

**Use cases**: Medical dictation (HIPAA), financial voice memos (data residency), warehouse voice commands (low-latency requirements).

## 7. Production Patterns

### Cost Management

The 3–8x cost multiplier for multimodal vs text-only is the primary production challenge. Key strategies:

| Strategy | Savings | Implementation |
|----------|---------|---------------|
| **Modality-aware routing** | 50–70% vs all-multimodal | Query classifier routes only visual queries to VLMs; text queries use cheaper text-only models |
| **Selective VLM ingestion** | 60–75% vs all-pages VLM | Document classifier: only route pages with <100 chars text or >40% image area through VLM |
| **Semantic caching** | 30–50% for repeated queries | Cache multimodal responses keyed by image hash + text query embedding |
| **Model tiering** | 40–60% per query | Use Claude Haiku / GPT-4o-mini for classification/extraction; frontier models only for synthesis |
| **Resolution management** | 20–40% image token savings | Render at minimum viable DPI (150–200); resize images before sending |
| **Prompt caching** | 10–30% for repeated system prompts | Claude/OpenAI prompt caching amortizes system prompt cost across batches |
| **Batch processing** | Variable | Non-real-time workloads (ingestion, batch extraction) use cheaper batch APIs |

### Latency Budget Design

```
Total SLA: 5s (document search use case)
  ├─ Query routing: <50ms
  ├─ Retrieval (text index): <200ms
  ├─ Retrieval (ColPali, if needed): <500ms
  ├─ Reranking: <100ms
  ├─ LLM prefill (text + images): <2s
  ├─ LLM decode (streaming): <2s (perceived)
  └─ Total: <4.85s at P95
```

For real-time voice: total SLA <1s. This requires native STT/TTS (no external services) and lightweight models for classification.

### Fallback Strategies

```
Primary: Frontier VLM (GPT-5, Claude Opus 4.7)
  ↓ (rate limit / timeout / error)
Fallback 1: Alternative frontier VLM (different provider)
  ↓ (continued failure)
Fallback 2: Open-source VLM (self-hosted Qwen3-VL or LLaVA)
  ↓ (continued failure)
Fallback 3: Text-only pipeline (OCR + text LLM)
  ↓ (total failure)
Error response with graceful degradation message
```

### On-Device vs Cloud Tiering

```
Request → Complexity Estimator
  → Simple/routine (classification, PII detection, basic OCR)
    → On-device model (Phi-4-multimodal, Apple Foundation Models, Gemini Nano)
    → Latency: <100ms, Cost: $0
  → Complex (cross-modal reasoning, document understanding, synthesis)
    → Cloud frontier model (GPT-5, Gemini 2.5 Pro, Claude Opus 4.7)
    → Latency: 1–5s, Cost: $0.01–0.05
```

### Caching for Multimodal

| Cache Type | Key | Use Case | Savings |
|-----------|-----|----------|---------|
| **Exact match** | Image hash + text query | Identical document queries | 30–50% in document review workflows |
| **Semantic** | Image embedding similarity + text embedding similarity | Similar-but-not-identical queries | 20–30% additional |
| **VLM description cache** | Page image hash → VLM description | Ingestion-time caching | Eliminates re-ingestion |
| **Prompt cache** | System prompt hash | Amortizes system prompt tokens | 10–30% on Claude/GPT |

## 8. Multimodal Evaluation

### Why Public Benchmarks Are Saturated

MMMU, MMBench, ChartQA, DocVQA, and MathVista are the standard VLM benchmarks. By 2026, frontier models have saturated or near-saturated these benchmarks, making them poor discriminators for production model selection.

| Benchmark | What It Tests | Saturation Status |
|-----------|--------------|-------------------|
| **MMMU** (11.5K questions) | College-level subject knowledge + reasoning | Near-saturated for frontier models |
| **MMBench** (3K+ questions, 20 abilities) | Comprehensive multimodal capabilities | Near-saturated |
| **ChartQA** | Information extraction from charts | Saturated for frontier; still useful for open-source |
| **DocVQA** | Document comprehension (forms, receipts, diagrams) | Useful for document-specific evals |
| **MathVista** | Math reasoning with visual elements | Partially saturated |
| **ViDoRe** | Visually rich document retrieval | Key benchmark for ColPali/ColQwen2 |

### Custom Regression Sets

The 2026 question is no longer "can the model do it?" but "how reliably does it do it in my specific workflow?" Custom regression sets are the answer:

**Design principles**:
- 30–50 ground truth question-answer pairs minimum per document type
- Include edge cases: low-quality scans, merged cells, handwritten annotations, multi-language
- Each pair specifies: input (image + text), expected output, acceptable variance, and difficulty tier
- Frozen reference set checked into git alongside prompt templates
- Run on every model/provider change as part of CI

### Cross-Modal Consistency Metric

A critical eval for multimodal systems: does the model correctly fuse information from multiple modalities?

```
Metric: cross_modal_consistency
Rubric:
  1.0 — Answer correctly fuses information from both text and image inputs
  0.5 — Partially correct; ignores some cross-modal relationship
  0.0 — Ignores one modality entirely or contradicts the other
```

Implemented via LLM-as-judge with a dedicated rubric prompt. Track this metric per query type and per document type to identify which cross-modal fusion patterns your system handles reliably.

### Multimodal Observability

Production multimodal flows need observability that captures image tokens, audio segments, tool calls, and reasoning across every span:

**Required trace attributes**:
- Input modalities present (text, image, audio, video)
- Output modality
- Image token count and resolution
- Audio segment duration
- Retrieval index used (text / ColPali / both)
- Retrieval scores from each modality
- Whether generation step received images
- VLM model used
- Total token counts (text tokens + image tokens + audio tokens)
- Latency per component (encoding, fusion, generation)

**Tools**: OpenInference span kinds (LLM, RETRIEVER, TOOL, GUARDRAIL) extended with modality attributes. traceAI (Apache 2.0) instruments across providers for multimodal tracing.

### Evaluation Framework for Multimodal Systems

```
Level 1: Unit Tests
  - Per-document extraction accuracy (table cells, figure descriptions, OCR quality)
  - Golden set CI checked into git

Level 2: Component Tests
  - Retrieval recall@5 by document type (text-native vs scanned vs visual)
  - Table extraction accuracy by complexity tier
  - Cross-modal consistency score

Level 3: Integration Tests
  - End-to-end query accuracy with real document corpus
  - Latency percentiles (P50, P90, P99) by retrieval path
  - Cost per query by modality mix

Level 4: Shadow Evaluation
  - Run new model on production traffic, compare outputs
  - Track cross-modal recall regression before canary rollout

Level 5: Online A/B
  - Canary deployment with 1–5% traffic
  - Automated rollback on quality metric degradation
```

## Interview Questions

1. **Compare Gemini 2.5 Pro, Claude Opus 4.7, and GPT-5 for a production document understanding system. Which do you choose and why?**

   Gemini 2.5 Pro leads on modality breadth (native audio + video + 1M–2M context) and video understanding. Claude Opus 4.7 leads on image-grounded reasoning and structured outputs — best for document understanding, screen reading, and code-from-screenshot. GPT-5 has the broadest tool ecosystem and native video. For document understanding specifically, I'd choose Claude Opus 4.7 for its structured output quality and image reasoning, with Gemini as fallback for any video content or audio inputs. Cost matters: Claude Sonnet 4.6 achieves 79.6% SWE-bench at a fraction of Opus cost — use Sonnet for 80% of traffic, Opus for complex documents.

2. **Design a multimodal RAG system for a law firm with 50,000 scanned contracts, many with handwritten annotations and tables.**

   Start with document audit to classify: estimate 40–60% scanned with no text layer, 20–30% with complex tables, 10–20% with handwritten annotations. Architecture: (1) Classifier routes documents by type on ingest. (2) Text-native contracts → standard text extraction + embedding. (3) Scanned contracts → Azure Document Intelligence OCR + VLM-based ingestion (Claude/GPT-4o) for pages where OCR confidence is low. (4) Tables → pdfplumber → Docling → VLM fallback. (5) Handwritten pages → VLM extraction exclusively. (6) ColPali index for pages where visual layout matters. (7) Query routing: text queries → hybrid BM25+dense; visual queries ("the clause marked on page 5") → ColPali; table queries → table-specific index. Retrieval results go to a multimodal LLM with source page images for visual grounding. Expected cost: $500–2000 ingestion (selective VLM routing reduces by 60–75%), $0.01–0.03 per query. Latency P95: 3–5s acceptable for legal research.

3. **What is ColPali and how does it differ from standard text-based RAG? When would you use it vs VLM-based ingestion?**

   ColPali encodes entire page images into multi-vector embeddings (1030 vectors per page) using a PaliGemma backbone with late interaction (MaxSim scoring). It skips OCR entirely, operating in visual embedding space. This preserves spatial and typographic structure that OCR destroys. Use ColPali when your corpus is visually rich (slides, reports, diagrams) and you need fine-grained retrieval that respects visual layout. Use VLM-based ingestion when you need structured text descriptions for indexing into existing text-based retrieval infrastructure, or when the downstream generation model works better with text context than page images. In production, combine both: ColPali for retrieval of visual content, VLM descriptions as supplementary indexed text.

4. **How do you manage cost in a multimodal pipeline? Walk through the math for 10,000 daily queries with 30% requiring visual processing.**

   Text-only queries (70% = 7,000/day) at $0.003/query = $21/day. Visual queries (30% = 3,000/day) at $0.02/query = $60/day. Total: $81/day = ~$2,430/month. Without modality-aware routing (all queries through VLM): $0.02 × 10,000 = $200/day = $6,000/month. Routing saves ~60%. Additional savings: semantic caching (30% hit rate on repeated queries) → $2,430 × 0.70 = $1,700/month. Prompt caching for VLM calls: additional 15% on image token processing → ~$1,450/month. Total savings from routing + caching: ~76% vs naive all-multimodal approach.

5. **Design a screen-control agent for automating CRM updates from email attachments. What guardrails do you implement?**

   Architecture: Email arrives → attachment extraction → VLM reads document → agent plans CRM update → executes via CRM API. Guardrails: (1) URL/domain allowlist: only CRM API endpoints allowed, no arbitrary web navigation. (2) Action allowlist: only CRUD operations on specific CRM objects (contacts, deals, notes). (3) Data validation: VLM-extracted fields validated against CRM schema before write. (4) Human-in-the-loop: updates exceeding $100K deal value or modifying protected fields require approval. (5) Loop detection: hash action + target; abort after 3 identical retries. (6) Audit logging: every screenshot, action, and decision logged with timestamp. (7) Rate limiting: max 50 CRM updates per hour to prevent runaway agents. (8) Fallback: if VLM extraction confidence <0.8, flag for human review instead of auto-updating.

6. **Explain the three-stage multimodal processing pipeline. What is early fusion vs late fusion and why does it matter?**

   Three stages: (1) Modality-specific encoding — vision encoder for images, audio encoder for speech, text tokenization. (2) Cross-modal fusion — attention mechanisms create shared representation spaces. (3) Unified output generation — single model produces integrated response. Early fusion (LLaMA 4, Gemini) unifies all modality tokens into a single vocabulary and attention space from the start — most natural cross-modal reasoning but highest compute. Late fusion (GPT-4o, GPT-5) uses separate encoders merged at intermediate layers — easier to train but potentially less natural cross-modal transfer. Early fusion models tend to perform better on tasks requiring tight visual-textual reasoning (e.g., "what does the arrow in this diagram point to?") because attention operates natively across modalities at every layer.

7. **Your multimodal RAG system achieves 0.92 faithfulness on text documents but only 0.65 on documents with tables and diagrams. How do you diagnose and fix this?**

   Diagnosis: (1) Segment eval set by document type — confirm the gap is specifically on table/diagram pages. (2) Check retrieval recall by type — are visual pages being retrieved at all? If recall is low on visual pages, the problem is in retrieval (ingestion or indexing). If recall is high but faithfulness is low, the problem is in generation (model can't reason about the retrieved visual content). (3) Inspect table extraction quality — are tables being converted to Markdown correctly? Run the three-tier validation (column count consistency, empty cell rate). (4) Check if ColPali retrieval is being used for visual queries. Fix: If retrieval is the issue, add ColPali index for visual pages and update query routing. If extraction is the issue, move from pdfplumber to Docling to VLM fallback. If generation is the issue, ensure the generation model receives source page images alongside text chunks (not just extracted text).

8. **Design a voice agent for a customer support hotline. What is your latency budget and how do you achieve sub-second response?**

   Latency budget for natural conversation: <1s time-to-first-audio. Architecture: (1) Audio stream via WebSocket to backend. (2) Native STT integrated in model (Gemini Live API or GPT-5 Realtime) — <200ms. (3) LLM reasoning with conversation context — <500ms. (4) Native TTS integrated in model — <200ms. (5) Audio stream response via WebSocket. Total: <900ms. Key decisions: use native STT/TTS (not external Whisper + ElevenLabs, which adds 1–2s). Keep conversation context window bounded (last N turns) to control prefill latency. Use streaming TTS to start audio output before full response is generated. For non-critical queries, use a smaller model (Gemini Flash, GPT-4o-mini) to reduce reasoning latency. For escalation to human agent, implement smooth handoff with context transfer.

9. **How do you evaluate a multimodal system when public benchmarks like MMMU are saturated? What does your evaluation framework look like?**

   Public benchmarks are saturated for frontier models — they don't discriminate between GPT-5, Claude Opus 4.7, and Gemini 2.5 Pro on MMMU/MMBench. Build domain-specific evals: (1) Golden set: 50–100 question-answer pairs with image + text inputs, covering your actual production document types and query patterns. (2) Cross-modal consistency metric: LLM-as-judge scoring whether the model fuses multi-modal information correctly. (3) Per-type segmentation: separate accuracy metrics for text queries, table queries, visual queries, and cross-modal queries. (4) Regression CI: golden set runs on every model/prompt change, gates deployment. (5) Shadow evaluation: run candidate model on production traffic alongside current model, compare outputs. (6) Online A/B: canary with 1–5% traffic, automated rollback on quality degradation. Track not just accuracy but latency and cost per query type.

10. **What are the key production challenges of deploying multimodal AI that don't exist in text-only systems?**

    Five key challenges: (1) **Cost multiplier**: 3–8x per query due to image tokens. Requires modality-aware routing, selective VLM usage, and aggressive caching. (2) **Latency**: Image processing adds 1.5–3s to generation. Rules out sub-2s SLAs for multimodal queries. (3) **Pipeline complexity**: Multiple ingestion paths (text, OCR, VLM, ColPali), multi-index retrieval, query routing logic, and more expensive observability. (4) **Evaluation difficulty**: Standard text evals don't capture visual understanding quality. Need image-based evals with per-modality segmentation. (5) **Storage**: ColPali embeddings are 10–50x larger than text embeddings. At scale (1M+ pages), vector storage becomes a real cost line. (6) **Data privacy**: Multimodal inputs carry more sensitive information per request (biometrics in audio, faces in images, confidential data in documents). Attack surface is larger.

11. **A user uploads a mix of photos and documents to your RAG system. How does your system handle the different content types in a single query?**

    At ingestion: (1) Classifier determines content type per item — photos get CLIP/SigLIP embeddings stored in image retrieval index; documents get text extraction + table extraction + ColPali embeddings. (2) Photos are described via VLM (caption + object detection + scene description) and indexed as text chunks alongside visual embeddings. At query time: (3) Query classifier determines if query is text-oriented, image-oriented, or mixed. (4) For mixed queries, run parallel retrieval across both text index and image index. (5) Fuse results with reciprocal rank fusion (RRF). (6) Route to multimodal LLM with both retrieved text chunks and source images. This two-tower approach (SigLIP for images + text embedding for documents) handles mixed content without forcing everything through visual retrieval.

12. **How would you design the ingestion pipeline for a corpus of 1 million financial documents (10M pages) with mixed native PDFs, scanned PDFs, and images?**

    Architecture: (1) Document classifier (rule-based, not neural) routes by type. (2) Native PDFs (>100 chars/page): pdfplumber for text + table extraction → text embedding index. (3) Scanned PDFs (<100 chars/page): Azure Document Intelligence OCR → if confidence >0.9, index as text. If <0.9, VLM ingestion (Claude Haiku for cost efficiency). (4) Image files: SigLIP embedding for image index + VLM captioning for text index. (5) Complex tables across all types: three-tier fallback (pdfplumber → Docling → VLM). (6) ColPali index for visually complex pages only (estimated 20–30% of corpus). Cost estimate: text extraction $200–500, OCR $500–1000, selective VLM ingestion $2000–5000 (only 25–30% of pages), ColPali encoding $500–1500 (GPU compute). Total: $3200–8000 one-time ingestion. Storage: text embeddings ~500MB, ColPali ~130GB, image embeddings ~50GB. Monthly storage cost: ~$15–20 at managed vector DB pricing.

## Key Terminology

**Vision-Language Model (VLM)** -- A model that processes both visual and textual inputs within a unified architecture, enabling cross-modal reasoning (e.g., answering questions about images, extracting structured data from document scans). Frontier VLMs in 2026 include GPT-5, Gemini 2.5 Pro, and Claude Opus 4.7; open-source options include Qwen3-VL, GLM-4.6V, and DeepSeek-OCR 2.

**ColPali** -- Visual document retrieval model that encodes entire page images into multi-vector embeddings using a PaliGemma backbone. Uses late interaction (MaxSim scoring) where each query token is matched against all page patch embeddings, preserving spatial and typographic structure that OCR destroys. Produces 1030 vectors of 128 dimensions per page. Key alternative: ColQwen2 (Qwen2-VL backbone) with stronger multilingual and table performance.

**MaxSim Scoring** -- Maximum similarity scoring used in ColPali/ColBERT-style retrieval: for each query token embedding, find the maximum dot product with all document patch embeddings. Produces a fine-grained relevance score that aligns query terms with specific regions of a page, unlike single-vector ANN search that matches the whole document at once.

**Early Fusion** -- Multimodal architecture where vision and text tokens share a unified vocabulary and attention space from the input layer (e.g., LLaMA 4, Gemini). Enables the most natural cross-modal reasoning because attention operates across modalities at every transformer layer, but requires the highest compute.

**Late Fusion** -- Multimodal architecture where separate modality-specific encoders process each input type independently, then merge representations at intermediate or late layers (e.g., GPT-4o, GPT-5). Easier to train and extend with new modalities but potentially less natural cross-modal transfer than early fusion.

**Multimodal RAG** -- Retrieval-augmented generation extended to handle documents with visual content (tables, diagrams, scanned pages, images). Three approaches: OCR + text chunking (cheapest, weakest visual understanding), VLM-based ingestion (structured extraction during indexing), native visual embeddings via ColPali (architecturally cleanest, highest storage cost).

**Cross-Modal Consistency** -- Evaluation metric measuring whether a model correctly fuses information from multiple input modalities (e.g., text + image) rather than ignoring one modality or producing outputs that contradict the other. Scored 0–1 via LLM-as-judge with domain-specific rubrics.

**Video-Native Model** -- A model that processes video as a native input modality rather than requiring frame-by-frame extraction. Gemini 2.5 Pro (up to 3 hours video), Qwen3-VL (256K token context with second-level indexing), and GPT-5 support video natively, understanding temporal relationships between frames without explicit frame extraction.

**Native STT/TTS** -- Speech-to-text and text-to-speech integrated directly into the LLM rather than using external services (Whisper, ElevenLabs). Gemini Live API and GPT-5 Realtime API both support this, reducing voice agent latency from 2–4 seconds to <1 second by eliminating modality boundary processing.

**Screen-Control Agent** -- An AI agent that reads UI screenshots, reasons about what actions to take, and executes actions (clicks, typing, navigation) in a browser or application. Built on models like Gemini 2.5 Pro (Project Mariner) and GPT-5 (computer use). Requires guardrails: URL allowlists, action allowlists, loop detection, human-in-the-loop for high-risk actions.

**ViDoRe Benchmark** -- Visually Rich Document Retrieval benchmark covering slides, financial reports, research papers, and technical tables. Standard evaluation set for comparing ColPali, ColQwen2, and text-extraction baselines on document retrieval accuracy when visual layout matters.

**DeepSeek-OCR / Contexts Optical Compression** -- Technique that encodes images into compact high-density vision tokens, decodes them back to text using a language model. Compresses visual context by up to 20x while maintaining 97% OCR accuracy at compression ratios below 10x. Achieves nearly 2,500 tokens/second on a single A100-40G GPU.

**Phi-4-multimodal** -- Microsoft's 5.6B parameter model processing text, images, and speech/audio within 128K context. Designed for on-device and edge deployment. Leads HuggingFace OpenASR leaderboard with 6.14% word error rate. Available through Azure AI Foundry.

## Cross-References

- **production_engineering/llm_in_production** -- Model portfolio management, LLM gateways (LiteLLM, OpenRouter for multi-provider routing), prompt caching, cost management patterns that extend to multimodal
- **production_engineering/ai_safety_compliance** -- Multimodal prompt injection (steganography, image scaling attacks), PII detection across modalities (faces in images, biometrics in audio), guardrails for screen-control agents
- **production_engineering/multi_model_gateway** -- Multi-provider routing for multimodal models (route text queries to Claude, visual queries to Gemini, voice to GPT-5 Realtime)
- **production_engineering/llm_cost_engineering** -- Token economics for image/audio/video inputs, cost modeling for multimodal pipelines, budget planning
- **system_design/rag_system** -- Core RAG architecture (chunking, embedding, retrieval, reranking) that multimodal RAG extends with visual indexing and cross-modal retrieval
- **role_specific/senior_ai_engineer** -- RAG & agentic AI section (Round 1), hands-on system design (Round 2) — multimodal adds vision/audio inputs to existing RAG and agent patterns
- **role_specific/ml_ai_engineer** -- Embedding models, vector databases (extended to multi-vector for ColPali), evaluation frameworks
- **production_engineering/slo_error_budgets** -- Latency SLO design for multimodal (higher budgets for visual queries, tighter for voice), error budgets across modality paths
- **cs_fundamentals** -- Computer vision fundamentals (CNNs, ViT, attention mechanisms) that underpin vision encoders in multimodal models
