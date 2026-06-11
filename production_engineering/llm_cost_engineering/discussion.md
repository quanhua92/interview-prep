# LLM Cost Engineering: Token Economics, Optimization & Budget Enforcement

## One-Liner
LLM cost engineering is the discipline of minimizing per-request inference spend while maintaining output quality — spanning token economics, prompt caching, semantic caching, model tier routing, batch processing, self-hosted economics, and budget enforcement architecture.

## Sources
- [OpenAI Pricing](https://platform.openai.com/docs/pricing) — current model pricing per 1M tokens (June 2026)
- [OpenAI Cost Optimization Guide](https://platform.openai.com/docs/guides/cost-optimization) — Batch API, flex processing, prompt caching strategies
- [OpenAI Prompt Caching Guide](https://platform.openai.com/docs/guides/prompt-caching) — automatic caching, extended retention, prefix matching
- [Anthropic Pricing](https://docs.anthropic.com/en/about-claude/pricing) — Claude model pricing, cache pricing tiers
- [Anthropic Prompt Caching](https://docs.anthropic.com/en/docs/build-with-claude/prompt-caching) — explicit/automatic breakpoints, TTL, pre-warming, 20-block lookback
- [Google Gemini Pricing](https://ai.google.dev/gemini-api/docs/pricing) — Gemini 3.x/2.5/2.0 model pricing, context caching, batch API
- [DeepSeek Pricing](https://api-docs.deepseek.com/quick_start/pricing) — DeepSeek V4 Flash/Pro pricing, cache hit discounts
- [Qwen Pricing](https://www.alibabacloud.com/help/en/model-studio/model-pricing) — Alibaba Cloud Model Studio Qwen model pricing
- [Kimi/Moonshot Pricing](https://platform.kimi.ai/docs/pricing/chat) — Kimi K2.6/K2.5/Moonshot V1 pricing
- [Z.AI/GLM Pricing](https://docs.z.ai/guides/overview/pricing) — Zhipu AI GLM-5/GLM-4.7 pricing
- [Datadog State of AI Engineering Report 2026](https://lp.datadoghq.com/rs/875-UVY-685/images/ResearchReport-2026StateofAIEngineering.pdf) — 28% cache adoption, 69% system prompt tokens, 5% error rate
- [GPTCache GitHub](https://github.com/zilliztech/GPTCache) — open-source semantic caching
- [vLLM Documentation](https://docs.vllm.ai/) — high-throughput serving engine
- [LiteLLM GitHub](https://github.com/BerriAI/litellm) — multi-model proxy with cost tracking
- [AWS Bedrock Pricing](https://aws.amazon.com/bedrock/pricing/) — Claude, Llama, Mistral, Amazon Titan/Nova per-token rates, provisioned throughput, batch inference
- [Google Vertex AI Pricing](https://cloud.google.com/gemini-enterprise-agent-platform/generative-ai/pricing) — Gemini model rates, agent builder, vector search, grounding surcharges
- [Azure OpenAI Pricing](https://azure.microsoft.com/en-us/pricing/details/azure-openai/) — GPT model rates, PTU pricing, batch API, deployment types (Global/Data Zone/Regional)

## Core Competencies Table

| Competency | Why It Matters | Interview Trigger |
|------------|---------------|-------------------|
| Token Economics | Understand pricing models, per-token costs, and how they compound at scale | "Calculate the monthly cost for..." |
| Prompt Caching | Exploit provider-side KV-cache reuse for 50-90% input cost reduction | "How do you reduce costs for repeated prompts?" |
| Semantic Caching | Cache semantically similar (not identical) queries for 30-50% savings | "How do you handle repeated questions?" |
| Prompt Compression | Reduce token count without losing quality | "Your prompt is too long, what do you do?" |
| Model Tier Routing | Route to the cheapest model that handles the task — 70-80% savings | "How would you cut LLM costs by 80%?" |
| Batch Processing | Offline/async processing at 50% cost reduction | "How do you process large datasets with LLMs?" |
| Self-Hosted Economics | Know when to rent GPUs vs use hosted APIs | "When does self-hosting make sense?" |
| Budget Enforcement | Per-team/per-feature caps, burn rate alerts, hard limits | "How do you prevent cost overruns?" |
| Cost Attribution | Track spend per feature, team, tenant | "What does feature X cost per month?" |
| ROI Calculation | Compare AI cost to alternative approaches (human, rules) | "Is this AI feature worth the cost?" |

## 1. Token Economics 101

### How LLM Pricing Works

LLM providers charge per **million tokens** (MTok). A token is roughly 3/4 of an English word or 4 characters. Pricing is split into **input tokens** and **output tokens**, with output typically 4-8x more expensive than input.

### 2026 Provider Pricing (Key Models)

> Pricing changes frequently. Verify current rates at [openai.com/pricing](https://openai.com/pricing), [anthropic.com/pricing](https://docs.anthropic.com/en/about-claude/pricing), [ai.google.dev/pricing](https://ai.google.dev/gemini-api/docs/pricing), [deepseek.com/pricing](https://api-docs.deepseek.com/quick_start/pricing), [alibabacloud.com/qwen](https://www.alibabacloud.com/help/en/model-studio/model-pricing), and [kimi.ai/pricing](https://platform.kimi.ai/docs/pricing/chat) before interviews.

#### OpenAI (June 2026)

**Flagship models** (GPT-5.4/5.5 series — short context pricing; long context doubles input cost):

| Model | Input | Cached Input | Output | Context |
|-------|-------|-------------|--------|---------|
| **GPT-5.5** | $5.00/MTok | $0.50/MTok | $30.00/MTok | 1M |
| **GPT-5.4** | $2.50/MTok | $0.25/MTok | $15.00/MTok | 1M |
| **GPT-5.4-mini** | $0.75/MTok | $0.075/MTok | $4.50/MTok | 400K |
| **GPT-5.4-nano** | $0.20/MTok | $0.02/MTok | $1.25/MTok | — |
| **GPT-5.5-pro** | $30.00/MTok | — | $180.00/MTok | 1M |
| **GPT-5.4-pro** | $30.00/MTok | — | $180.00/MTok | 1M |

**Previous generation** (GPT-5.x / GPT-4.1 / GPT-4o / o-series):

| Model | Input | Cached Input | Output | Context |
|-------|-------|-------------|--------|---------|
| **GPT-5.2** | $1.75/MTok | $0.175/MTok | $14.00/MTok | 128K |
| **GPT-5.1** | $1.25/MTok | $0.125/MTok | $10.00/MTok | 128K |
| **GPT-5** | $1.25/MTok | $0.125/MTok | $10.00/MTok | 128K |
| **GPT-5-mini** | $0.25/MTok | $0.025/MTok | $2.00/MTok | 128K |
| **GPT-5-nano** | $0.05/MTok | $0.005/MTok | $0.40/MTok | 400K† |
| **GPT-5.2-pro** | $21.00/MTok | — | $168.00/MTok | — |
| **GPT-5-pro** | $15.00/MTok | — | $120.00/MTok | — |
| **GPT-4.1** | $2.00/MTok | $0.50/MTok | $8.00/MTok | 2M |
| **GPT-4.1-mini** | $0.40/MTok | $0.10/MTok | $1.60/MTok | 2M |
| **GPT-4.1-nano** | $0.10/MTok | $0.025/MTok | $0.40/MTok | 2M |
| **GPT-4o** | $2.50/MTok | $1.25/MTok | $10.00/MTok | 128K |
| **GPT-4o-mini** | $0.15/MTok | $0.075/MTok | $0.60/MTok | 128K |
| **o3** | $2.00/MTok | $0.50/MTok | $8.00/MTok | 200K |
| **o4-mini** | $1.10/MTok | $0.275/MTok | $4.40/MTok | 200K |
| **o3-pro** | $20.00/MTok | — | $80.00/MTok | 200K |
| **o1** | $15.00/MTok | $7.50/MTok | $60.00/MTok | 200K |
| **o1-pro** | $150.00/MTok | — | $600.00/MTok | 200K |
| **GPT-Realtime** | $4.00/MTok | $0.40/MTok | $16.00/MTok | — |
| **GPT-Realtime-mini** | $0.60/MTok | $0.06/MTok | $2.40/MTok | — |

† Context windows change frequently. Verify against [OpenAI's model docs](https://developers.openai.com/api/docs/models) for current limits.

**Note**: GPT-5.5/5.4/5.4-mini/5.4-nano use short/long context pricing — the prices above are short context (<270K tokens). Long context doubles the input cost.

Key observations:
- **GPT-5.4-nano at $0.20 input replaces GPT-5-nano** as the new ultra-cheap tier, but GPT-5-nano ($0.05) remains cheapest
- **GPT-5.5 is the new flagship** at $5.00/$30.00, replacing GPT-5.2's top position
- **Cached input = 90% discount** on GPT-5.x models ($1.75 → $0.175)
- **GPT-4.1-nano at $0.10 input is 25x cheaper** than GPT-4o ($2.50)
- **o1-pro at $150/$600** is the most expensive model — 30x more than o3-pro ($20/$80)
- **Processing tiers** (Standard/Batch/Flex/Priority) affect pricing: Batch and Flex = 50% of Standard; Priority = 2.5x Standard

#### Anthropic (Claude, June 2026)

| Model | Input | Cache Read (5m) | Output | Context |
|-------|-------|-----------------|--------|---------|
| **Claude Fable 5** | $10.00/MTok | $1.00/MTok | $50.00/MTok | 1M |
| **Claude Mythos 5**† | $10.00/MTok | $1.00/MTok | $50.00/MTok | 1M |
| **Claude Opus 4.8** | $5.00/MTok | $0.50/MTok | $25.00/MTok | 1M |
| **Claude Opus 4.7** | $5.00/MTok | $0.50/MTok | $25.00/MTok | 1M |
| **Claude Opus 4.6** | $5.00/MTok | $0.50/MTok | $25.00/MTok | 1M |
| **Claude Opus 4.5** | $5.00/MTok | $0.50/MTok | $25.00/MTok | 200K |
| **Claude Sonnet 4.6** | $3.00/MTok | $0.30/MTok | $15.00/MTok | 1M |
| **Claude Sonnet 4.5** | $3.00/MTok | $0.30/MTok | $15.00/MTok | 200K |
| **Claude Haiku 4.5** | $1.00/MTok | $0.10/MTok | $5.00/MTok | 200K |

Anthropic cache pricing tiers:
- **5-min cache write**: 1.25x base input price
- **1-hour cache write**: 2.0x base input price
- **Cache read**: 0.1x base input price (90% savings)

† Claude Mythos 5 has limited availability via [Anthropic Glasswing](https://anthropic.com/glasswing). Same pricing and context window as Claude Fable 5 ($10/$50/MTok, 1M tokens). Minimum cacheable prompt: 512 tokens.

#### Google Gemini (June 2026)

**Gemini 3.x series** (current generation):

| Model | Input | Cached Input | Output | Context | Notes |
|-------|-------|-------------|--------|---------|-------|
| **Gemini 3.5 Flash** | $1.50/MTok | $0.15/MTok | $9.00/MTok | 1M | Current flagship Flash; thinking tokens included in output |
| **Gemini 3.1 Pro** | $2.00/$4.00/MTok | $0.20/$0.40/MTok | $12.00/$18.00/MTok | 1M | Preview; short/long context (≤200K / >200K) |
| **Gemini 3.1 Flash** | $0.50/$1.00/MTok | $0.05/$0.10/MTok | $3.00/$4.50/MTok | 1M | Standard/Live/Flash Image variants |
| **Gemini 3.1 Flash-Lite** | $0.25/$0.50/MTok | $0.025/$0.05/MTok | $1.50/$2.70/MTok | 1M | Short/long context; most cost-efficient 3.x |
| **Gemini 3 Flash** | $0.75/$1.50/MTok | $0.075/$0.15/MTok | $4.50/$5.40/MTok | 1M | Preview; short/long context |

**Gemini 2.5 series** (previous generation):

| Model | Input | Cached Input | Output | Context | Notes |
|-------|-------|-------------|--------|---------|-------|
| **Gemini 2.5 Pro** | $1.25/$2.50/MTok | $0.125/$0.25/MTok | $10.00/$15.00/MTok | 1M | Coding & complex reasoning; short/long context (≤200K / >200K) |
| **Gemini 2.5 Flash** | $0.15/$0.30/MTok | $0.03/$0.06/MTok | $1.25/$2.50/MTok | 1M | Hybrid reasoning; thinking budgets |
| **Gemini 2.5 Flash-Lite** | $0.05/$0.10/MTok | $0.01/$0.02/MTok | $0.20/$0.40/MTok | 1M | Smallest & most cost-effective |
| **Gemini 2.5 Pro (thinking)** | $2.25/$4.50/MTok | $0.225/$0.45/MTok | $18.00/$27.00/MTok | 1M | Thinking mode at 1.8x output multiplier |

**Gemini 2.0 series** (legacy):

| Model | Input | Cached Input | Output | Context | Notes |
|-------|-------|-------------|--------|---------|-------|
| **Gemini 2.0 Flash** | $0.10/$0.20/MTok | $0.025/MTok | $0.40/$0.60/MTok | 1M | Stable workhorse; free tier available |
| **Gemini 2.0 Flash-Lite** | $0.075/MTok | — | $0.30/MTok | 1M | No caching support |

Google caching notes:
- **Context caching**: 0.1x base input price on cache reads (90% savings), plus $1.00/MTok/hr storage
- **Short/long context pricing**: Many Gemini models double input cost for prompts >200K tokens (shown as `short/long` above)
- **Thinking tokens**: Included in output price on Gemini 3.x; Gemini 2.5 Pro thinking mode has separate 1.8x multiplier
- **Batch API**: 50% cost reduction on input and output tokens
- **Free tier**: Available on select models with generous limits but content used to improve products
- **Processing tiers**: Standard, Batch (50% off), Flex (lower cost, lower priority), Priority (higher cost, faster)

Key observations:
- **Gemini 3.1 Flash-Lite at $0.25/$1.50** is competitive with GPT-5-nano ($0.05/$0.40) on a quality-adjusted basis
- **Gemini 2.5 Flash at $0.15/$1.25** is 8-12x cheaper than GPT-5.4 ($2.50/$15.00) for comparable tasks
- **Gemini 2.5 Pro at $1.25/$10.00** matches GPT-5.1 pricing exactly but with 1M context (vs 128K)
- **Context caching at 0.1x** matches OpenAI's 90% discount and beats Anthropic's explicit cache write surcharge (1.25x-2x)
- **All Gemini models support 1M context** — the largest free context window of any provider (OpenAI: 1M on GPT-5.5 only; Anthropic: 1M on Opus 4.6+)

#### Chinese AI Models (June 2026)

> Pricing changes frequently. Verify current rates at the official docs: [DeepSeek](https://api-docs.deepseek.com/quick_start/pricing), [Qwen](https://www.alibabacloud.com/help/en/model-studio/model-pricing), [Kimi](https://platform.kimi.ai/docs/pricing/chat), [Z.AI/GLM](https://docs.z.ai/guides/overview/pricing).

**DeepSeek** — Aggressive MoE pricing, 1M context, optional thinking mode:

| Model | Input | Cached Input | Output | Context | Notes |
|-------|-------|-------------|--------|---------|-------|
| **DeepSeek-V4-Pro** | $0.435/MTok | $0.003625/MTok | $0.87/MTok | 1M | Flagship; supports thinking mode |
| **DeepSeek-V4-Flash** | $0.14/MTok | $0.0028/MTok | $0.28/MTok | 1M | Best-value tier; replaces V3 & R1 API names |

Cache hit on DeepSeek is **98% discount** ($0.14 → $0.0028) — the most aggressive cache pricing of any provider.

**Qwen (Alibaba Cloud / Tongyi)** — Largest model family (145+ model IDs), MoE architecture, open-weight:

| Model | Input | Cached Input | Output | Context | Notes |
|-------|-------|-------------|--------|---------|-------|
| **Qwen3.7-Max** | $1.25/MTok | $0.125/MTok | $3.75/MTok | 1M | Flagship; 50% promo pricing |
| **Qwen3-Max** | $1.20/MTok | $0.12/MTok | $6.00/MTok | 262K | Agent-optimized |
| **Qwen3.7-Plus** | $0.32–$0.96/MTok | ~$0.06–$0.19/MTok | $1.28–$3.84/MTok | 1M | Native multimodal; tiered by input length |
| **Qwen3.6-Plus** | $0.50–$2.00/MTok | — | $3.00–$6.00/MTok | 1M | Agentic coding; multimodal |
| **Qwen3-235B-A22B** | $0.70/MTok | ~$0.14/MTok | $2.80/MTok | 131K | MoE open-weight flagship; thinking mode $8.40/MTok output |
| **Qwen-Plus** | $0.40/MTok | $0.08/MTok | $1.20/MTok | 1M | Stable production alias; thinking mode $4.00/MTok output |
| **Qwen3-30B-A3B** | $0.20/MTok | ~$0.04/MTok | $0.80/MTok | 131K | Balanced MoE; thinking mode $2.40/MTok output |
| **Qwen-Turbo** | $0.05/MTok | — | $0.20/MTok | 131K | Cheapest text tier; 5M TPM throughput |

Implicit caching at ~20% of standard input rate on most models. Thinking mode output billed at 3-10x standard output rate. All Qwen3 models are Apache 2.0 open-weight.

**Kimi / Moonshot AI** — Frontier reasoning at low cost, strong coding/agent capabilities:

| Model | Input | Cached Input | Output | Context | Notes |
|-------|-------|-------------|--------|---------|-------|
| **Kimi K2.6** | $0.95/MTok | $0.16/MTok | $4.00/MTok | 256K | Latest; improved long-context coding |
| **Kimi K2.5** | $0.60/MTok | $0.10/MTok | $3.00/MTok | 256K | Multimodal; thinking & non-thinking modes |
| **Moonshot V1** | $2.00/MTok | — | $5.00/MTok | 131K | First-generation; limited features |

**Z.AI / GLM (Zhipu AI)** — Competitive pricing with free Flash tiers and explicit caching:

| Model | Input | Cached Input | Output | Context | Notes |
|-------|-------|-------------|--------|---------|-------|
| **GLM-5.1** | $1.40/MTok | $0.26/MTok | $4.40/MTok | 128K | Latest flagship |
| **GLM-5** | $1.00/MTok | $0.20/MTok | $3.20/MTok | 128K | Previous flagship |
| **GLM-5-Turbo** | $1.20/MTok | $0.24/MTok | $4.00/MTok | 128K | Speed-optimized GLM-5 |
| **GLM-4.7** | $0.60/MTok | $0.11/MTok | $2.20/MTok | 128K | Workhorse |
| **GLM-4.7-FlashX** | $0.07/MTok | $0.01/MTok | $0.40/MTok | 128K | Fast推理 |
| **GLM-4.5-Air** | $0.20/MTok | $0.03/MTok | $1.10/MTok | 128K | Lightweight |
| **GLM-4.7-Flash** | Free | Free | Free | 128K | Free tier model |
| **GLM-4.5-Flash** | Free | Free | Free | 128K | Free tier model |

Cached input storage is **free** (limited-time promotion). Cache read pricing is ~15-18% of standard input across the board.

##### Chinese Models vs US Providers: Price Comparison

| Tier | US Provider | Chinese Equivalent | Price Ratio |
|------|------------|-------------------|-------------|
| **Ultra-cheap** | GPT-5-nano $0.05/$0.40 | Qwen-Turbo $0.05/$0.20 | **1x input, 0.5x output** — Qwen wins on output |
| **Budget** | GPT-4o-mini $0.15/$0.60 | DeepSeek-V4-Flash $0.14/$0.28 | **~1x input, 0.5x output** — comparable input, cheaper output |
| **Mid-range** | GPT-4.1-mini $0.40/$1.60 | Qwen-Plus $0.40/$1.20 | **1x input, 0.75x output** — similar input, cheaper output |
| **Standard** | GPT-5.4 $2.50/$15.00 | Qwen3.7-Max $1.25/$3.75 | **0.5x input, 0.25x output** — 4-10x cheaper |
| **Frontier** | GPT-5.5 $5.00/$30.00 | Kimi K2.6 $0.95/$4.00 | **0.19x input, 0.13x output** — 5-7x cheaper |
| **Reasoning** | o3 $2.00/$8.00 | DeepSeek-V4-Pro $0.435/$0.87 | **0.22x input, 0.11x output** — 5-9x cheaper |

**Key takeaways for interviews:**
- Chinese models are **3-10x cheaper** than US equivalents at every tier except ultra-cheap (where they're competitive)
- **DeepSeek-V4-Flash** at $0.14/$0.28 is the best-value frontier-adjacent model — comparable quality to GPT-4.1-mini at half the output cost
- **Qwen-Turbo** matches GPT-5-nano on input ($0.05) but at half the output cost ($0.20 vs $0.40)
- **Kimi K2.6** at $0.95/$4.00 is 5-7x cheaper than GPT-5.5 ($5.00/$30.00) with competitive benchmark scores
- Chinese models offer **MoE architecture** (DeepSeek, Qwen) enabling frontier performance at dense-model inference cost
- **Caveat**: Chinese models tend to generate more verbose outputs, partially offsetting the per-token savings
- **Caveat**: Enterprise adoption may be limited by China-origin compliance reviews in regulated industries; self-hosting open-weight models (Qwen3, DeepSeek) sidesteps this
- Free tiers exist (GLM-4.7-Flash, GLM-4.5-Flash) — useful for prototyping before committing budget

#### Open-Source / Self-Hosted (Per-Request Cost)

| Model | GPU | Throughput | Effective Cost/MTok* |
|-------|-----|-----------|---------------------|
| **Llama 4 Maverick** | 1x H100 | ~3,000 tok/s | ~$0.10-0.30 |
| **Llama 3.3 70B** | 1x A100 | ~2,000 tok/s | ~$0.20-0.50 |
| **Qwen3 235B** | 2x H100 | ~1,500 tok/s | ~$0.30-0.80 |
| **Mixtral 8x22B** | 1x A100 | ~2,500 tok/s | ~$0.15-0.40 |
| **Gemma 3 27B** | 1x A100 40GB | ~3,500 tok/s | ~$0.08-0.20 |

*Assumes $2-4/hr A100, $3-5/hr H100 on cloud spot pricing; amortized at 70% utilization

### Cloud Provider Managed Inference Services

Most enterprises don't call model providers directly. They route inference through their cloud provider's managed AI service. The token rates match or closely mirror direct API pricing, but cloud providers add operational features (VPC endpoints, IAM auth, data residency, compliance) and hidden costs (support plans, egress, idle endpoints, observability) that make total cost 15-40% higher.

#### Why Enterprises Use Cloud Providers Over Direct API

| Reason | Detail |
|--------|--------|
| **Private inference / VPC endpoints** | Traffic stays within your VPC — no data traverses the public internet. Required by most enterprise security policies |
| **Data residency** | Inference runs in a specific region/country. EU workloads stay in EU, HIPAA workloads stay in approved regions. Cross-region inference adds ~10% markup on Bedrock |
| **Compliance umbrellas** | AWS Bedrock inherits AWS's HIPAA, FedRAMP, SOC 2, IL5/IL6 certifications. Azure inherits Microsoft's. Vertex AI inherits Google Cloud's. Using direct API requires separate compliance reviews |
| **IAM authentication** | No API key management. Use existing IAM roles/policies. Centralized access control, audit logging, rotation handled by the cloud provider |
| **Consolidated billing** | One invoice for all AI spend + compute + storage. Easier for finance, procurement, and FinOps. Existing committed spend discounts (EDP, EA) may apply |
| **Multi-model single endpoint** | Bedrock: Claude + Llama + Mistral + Amazon Titan + Cohere through one API. Vertex AI: Gemini + Claude + Llama + Mistral through one API. One integration, not five |
| **Existing cloud contracts** | If you're already committed to AWS/Azure/GCP spend, routing AI through the same provider leverages existing relationships, support tiers, and negotiated rates |

#### AWS Bedrock

**Models available** (June 2026):

| Provider | Models | Notes |
|----------|--------|-------|
| **Anthropic** | Claude Haiku 4.5, Claude Sonnet 4.6, Claude Opus 4.6, Claude Opus 4.7, Claude Opus 4.8 | Flagship models; same pricing as direct Anthropic API |
| **Meta** | Llama 3.1 8B, Llama 3.1 70B, Llama 3.1 405B, Llama 3.3 70B, Llama 4 Scout (109B MoE), Llama 4 Maverick (402B MoE) | Open-weight models served via Bedrock; 10M context on Llama 4 Scout |
| **Mistral** | Mistral Large, Mistral Large 2, Mistral Small | European data residency support |
| **Amazon** | Amazon Titan (Text, Embeddings, Image), Amazon Nova (Pro, Lite, Micro) | First-party models; cheapest tier (Nova Micro at $0.035/$0.14) |
| **Cohere** | Command R+, Embed v3 | Enterprise search and RAG focus |
| **Stability AI** | Stable Diffusion, Stable Image | Image generation |

**Pricing structure** — three billing modes:

| Mode | Pricing | Best For |
|------|---------|----------|
| **On-Demand** (Standard) | Per-token, pay-as-you-go. Rates match direct API. Claude Sonnet 4.6: $3.00/$15.00/MTok | Variable/unpredictable workloads, prototyping |
| **Batch Inference** | 50% off on-demand rates. Submit via S3, results within 24 hours | Offline processing, data pipelines |
| **Provisioned Throughput** | Hourly rate for reserved capacity. 1-month or 6-month commitment. ~$40-200/hr depending on model. No per-token charges | Steady production traffic, guaranteed latency |

**Prompt caching**: Supported for Claude models on Bedrock. Up to 90% discount on cached input tokens. Feature availability can lag behind Anthropic's direct API by 1-4 weeks.

**Unique features**:
- **VPC endpoints**: Private inference within your VPC, no public internet exposure
- **Cross-region inference**: Route requests to models in different AWS regions; adds ~10% markup
- **Knowledge Bases**: Managed RAG pipeline (document chunking, vector search via OpenSearch Serverless, retrieval). Minimum ~$700/month (4 OCUs of OpenSearch Serverless). Expensive for simple use cases — use Pinecone ($50/month) or pgvector (free) alongside direct API instead
- **Bedrock Agents**: Orchestration charges per agent step — multi-step workflows cost more per step than single invocations
- **Model蒸馏 (Distillation)**: Supported for select models
- **Fine-tuning**: Supported for Amazon Titan and some Llama variants. Fine-tuned models require Provisioned Throughput to serve

**Hidden costs**: Knowledge Bases minimum (~$700/month OpenSearch floor), cross-region inference (~+10%), Bedrock Agents per-step charges, standard AWS data transfer costs between regions.

**Key insight**: Bedrock's per-token rates match direct API pricing almost exactly. The value proposition is operational (IAM, VPC, CloudWatch, single endpoint), not cost savings. If you're not on AWS, there's no pricing reason to choose Bedrock.

#### Google Vertex AI

**Models available** (June 2026):

| Provider | Models | Notes |
|----------|--------|-------|
| **Google** | Gemini 3.1 Pro, Gemini 3.1 Flash, Gemini 3.1 Flash-Lite, Gemini 3 Flash, Gemini 2.5 Pro, Gemini 2.5 Flash, Gemini 2.5 Flash-Lite | Full Gemini lineup; 1M context on all models |
| **Anthropic** | Claude Haiku 4.5, Claude Sonnet 4.6, Claude Opus 4.5+ | Anthropic models via Vertex AI |
| **Meta** | Llama 3.1, Llama 3.3, Llama 4 | Open-weight models |
| **Mistral** | Mistral Large, Mistral Small | European provider |
| **200+ third-party models** | Via Model Garden | One platform, many models |

**Pricing structure** — per-token with tiered throughput:

| Mode | Pricing | Best For |
|------|---------|----------|
| **Standard (Pay-as-you-go)** | Per-token. Auto-scales throughput as rolling 30-day spend grows | General use, variable workloads |
| **Batch API** | 50% off standard rates | Async workloads, document processing |
| **Provisioned Throughput** | Per GSU-hour ($42-158/hr depending on model). Guaranteed latency and capacity | Production SLA workloads |
| **Committed Use Discounts** | ~30% off (1-year), ~50% off (3-year) on GPU/compute | Steady, predictable workloads |

**Vertex AI vs direct Google API pricing**: Token rates match Gemini Developer API pricing almost exactly. Vertex AI adds enterprise features: SLAs, Provisioned Throughput, VPC Service Controls, compliance certifications, and integration with GCP data stack (BigQuery, Cloud Storage, Dataflow).

**Context caching**: 0.1x base input price on cache reads (90% savings), plus $1.00/MTok/hr storage. Matches the direct API caching behavior.

**Unique features**:
- **VPC Service Controls**: Data perimeter enforcement — prevent data exfiltration
- **Google Search Grounding**: $14/1K queries (Gemini 3.x) or $35/1K queries (Gemini 2.x). Often costs more than the model inference itself — a common surprise on invoices
- **Agent Builder + Agent Engine**: $4-6/1K search queries + $0.0864/vCPU-hour runtime + $0.009/GB-hour memory + $0.25/1K session events. Four separate billing events per user interaction
- **Vector Search**: Infrastructure-based (node-hour billing). ~$700-800/month for a moderately sized index on 3 replicas
- **OpenAI compatibility endpoint**: Port existing OpenAI SDK code to Gemini without rewrites
- **Model Optimizer**: Auto-routes requests to cheapest adequate model based on task complexity

**Hidden costs**: Grounding surcharges (can exceed model cost), idle endpoints ($2,642/month for a deployed A100 endpoint whether handling requests or not), thinking token inflation (billed as output — can 2-3x effective cost), agent orchestration stacking (4+ SKUs per user interaction), LiveAPI session re-billing (turn 10 bills for all tokens from turns 1-9).

**Key insight**: Vertex AI is the best choice if your data already lives in GCP (BigQuery, Cloud Storage). The integration friction is near-zero. Flash-Lite at $0.10/$0.40 is among the cheapest foundation models from any major provider.

#### Azure AI (Azure OpenAI Service + Azure AI Models)

**Models available** (June 2026):

| Provider | Models | Notes |
|----------|--------|-------|
| **OpenAI** | GPT-5.5, GPT-5.4, GPT-5.4-mini, GPT-5.4-nano, GPT-5.3, GPT-5.2, GPT-5.1, GPT-5, GPT-4.1, GPT-4o, GPT-4o-mini, o3, o4-mini, o1, Sora 2, GPT-Image | Full OpenAI lineup via Azure; often available before public OpenAI API |
| **Meta** | Llama 3.1, Llama 3.3, Llama 4 | Via Azure AI Models (formerly Azure AI Studio) |
| **Mistral** | Mistral Large, Mistral Small | Via Azure AI Models |
| **Cohere** | Command R+ | Via Azure AI Models |
| **Open-source** | gpt-oss-120b, gpt-oss-20b | Open-weight models |
| **Microsoft** | Phi-4 family | First-party small models |

**Pricing structure** — five deployment types:

| Deployment | Pricing | Discount | Best For |
|------------|---------|----------|----------|
| **Standard (Regional PAYG)** | Per-token, single region | Baseline | Strict single-region data residency |
| **Global Standard** | Per-token, routed globally | Same or lower | No specific residency requirement |
| **Data Zone Standard** | Per-token, EU or US zone | ~5% over Global | Mid-tier residency (EU/US block) |
| **Provisioned (PTU)** | Per PTU-hour, reserved capacity | Up to 70% on steady workloads | Predictable production traffic |
| **Batch API** | Per-token, 24-hr SLA | 50% off Global Standard | Async workloads, evals, backfills |

**Azure vs direct OpenAI API pricing**: Token prices match OpenAI's direct API to the cent. But Azure bills land 15-40% higher due to auxiliary costs.

**Azure's hidden cost stack** (the "why is my bill 2x the calculator?" problem):

| Hidden Cost | Typical Range | What Triggers It |
|-------------|---------------|-------------------|
| **Support plan** | $100-$1,000+/month | Production SLA tier |
| **Data egress** | $0.087/GB (after 100GB free) | Cross-region or cross-cloud calls |
| **Log Analytics ingest** | ~$2.30/GB | Default verbose logging |
| **Private Link** | Per endpoint-hour | Network isolation requirements |
| **Fine-tuned model hosting** | $1.70-$3.00/hour | One deployed fine-tune; bills 24/7 even at zero requests |
| **File search storage** | $0.10/GB/day (1GB free) | Assistants API + RAG |

**Prompt caching**: Automatic 50-90% discount on repeated prompt prefixes. Same mechanics as direct OpenAI API.

**PTU decision rule**:
- Below 150M tokens/month: stay on PAYG
- 150M-500M tokens/month: model both; PTU usually wins if utilization is steady (>50%)
- Above 500M tokens/month with steady traffic: PTU almost always cheaper

**Unique features**:
- **Three deployment scopes**: Global (cheapest, no residency), Data Zone (EU or US), Regional (specific region, most expensive but strictest residency)
- **Content filtering**: Enterprise-grade content safety built in (configurable)
- **Private Link**: Traffic stays on Microsoft's backbone network
- **Azure AI Search integration**: Managed RAG with Azure AI Search (replaces OpenAI's file search)
- **Early access**: Some OpenAI models debut on Azure before the public API (GPT-4o was Azure-first)
- **Compliance**: Inherits Microsoft's full compliance portfolio (HIPAA, FedRAMP, ISO, SOC, GDPR)

**Key insight**: Teams choose Azure for compliance, data residency, or enterprise procurement — not price. Token rates are identical to direct OpenAI. Budget 20-40% overhead on top of token math for auxiliary costs. The most common billing surprise is idle fine-tuned model hosting ($50-70/day per deployment whether it serves requests or not).

#### Comparison Table: Direct API vs Cloud Provider

| Dimension | Direct API | AWS Bedrock | Google Vertex AI | Azure AI |
|-----------|-----------|-------------|-------------------|----------|
| **Per-token pricing** | Baseline | Same (±0%) | Same (±0%) | Same (±0%) |
| **Total cost** | Baseline | +0-15% | +0-20% | +15-40% |
| **Model availability lag** | First (same day) | 1-4 weeks behind | 1-2 weeks behind | Same day to 1 week ahead (OpenAI) |
| **Caching support** | Full (all providers) | Full for Claude; limited for others | Full (Gemini) | Full (OpenAI models) |
| **Batch discount** | 50% (OpenAI, Anthropic) | 50% | 50% | 50% |
| **Provisioned throughput** | No | Yes (1-6 month commitment) | Yes (GSU-hourly) | Yes (PTU hourly/monthly/annual) |
| **VPC / private endpoints** | No | Yes (VPC endpoints) | Yes (VPC Service Controls) | Yes (Private Link) |
| **IAM integration** | API keys only | AWS IAM | Google IAM | Azure AD / Entra ID |
| **Data residency** | Depends on provider | Region-specific | Region-specific | Region / Data Zone / Global |
| **Compliance** | Provider-level only | AWS umbrella (HIPAA, FedRAMP, SOC) | GCP umbrella | Microsoft umbrella |
| **Multi-model access** | Per-provider API keys | Single endpoint, all providers | Single platform, all providers | Single platform (OpenAI) + Azure AI Models |
| **Monitoring** | Provider dashboard | CloudWatch integration | Cloud Logging integration | Azure Monitor + Log Analytics |
| **SLA** | 99.9% typical | 99.9% (Standard tier) | 99.9% (Standard) | 99.9% |
| **Free tier** | Limited (some providers) | No | $300 credit + limited free tier | No permanent free tier |
| **Biggest hidden cost** | None significant | Knowledge Bases (~$700/mo floor) | Grounding surcharges, idle endpoints | Fine-tune hosting ($50-70/day), Log Analytics |

#### When to Use Each

| Scenario | Recommended Approach | Why |
|----------|---------------------|-----|
| **Startup / prototype (<50K req/mo)** | Direct API | Simplest setup, lowest overhead, no cloud commitment |
| **Growing startup on AWS** | AWS Bedrock on-demand | IAM auth, VPC endpoints, single endpoint for multi-model |
| **Enterprise with compliance requirements** | Cloud provider matching your cloud | Compliance umbrellas (HIPAA, FedRAMP, SOC) without separate reviews |
| **Regulated industry (healthcare, finance)** | Azure or AWS Bedrock | Strongest compliance certifications, data residency controls |
| **Multi-cloud enterprise** | Direct API + LiteLLM/proxy | Avoid lock-in, route across providers; use proxy for unified billing |
| **High volume, steady traffic (>500M tok/mo)** | Provisioned throughput (PTU/GSU) | 50-70% savings vs on-demand at high utilization |
| **Bursty traffic** | On-demand (any provider) | No commitment, pay only for what you use |
| **Data already in GCP (BigQuery, GCS)** | Vertex AI | Zero integration friction, best data pipeline synergy |
| **Need OpenAI models + Microsoft ecosystem** | Azure OpenAI | Earliest access to new OpenAI models, Azure AD/Entra ID integration |
| **Cost-sensitive, non-compliance** | Direct API + cheapest provider | No hidden costs, pick best price per token (DeepSeek, Gemini Flash-Lite) |
| **European data residency** | AWS Bedrock (Mistral, EU regions) or Vertex AI (EU) | EU-specific inference, GDPR-friendly |
| **AI agents with orchestration** | Evaluate total cost carefully | Agent features (Bedrock Agents, Vertex Agent Builder) add per-step/per-query charges that compound |

**Key interview point**: The 2026 reality is that per-token pricing is nearly identical across direct API and all three cloud providers. The decision framework is about operational requirements (compliance, data residency, IAM, existing cloud contracts), not price. However, total cost of ownership (TCoO) differs significantly due to hidden costs — especially on Azure (15-40% overhead) and Vertex AI (grounding surcharges, idle endpoints). Always model TCoO, not just per-token rates.

### How Pricing Has Changed (2024 → 2026)

| Trend | Detail |
|-------|--------|
| Prices dropped 80-95% for equivalent capability | GPT-4 ($30/MTok in) → GPT-5-nano ($0.05/MTok in) for many tasks |
| New ultra-cheap tier emerged | GPT-5-nano at $0.05, GPT-5.4-nano at $0.20 input — for classification, extraction |
| Cache discounts standardized | OpenAI: automatic 90% cache read; Anthropic: 0.1x on cache hits |
| Context windows expanded | 128K → 1M tokens (GPT-5.5), 400K (GPT-5.4-mini), 2M (GPT-4.1) — but cost per token didn't decrease proportionally |
| Short/long context pricing introduced | GPT-5.5/5.4 series: input cost doubles for context >270K tokens |
| Output/input price ratio widened | Frontier models: output is 5-8x input cost (was 2-3x in 2024) |
| Batch API discount deepened | 50% on both input and output for async workloads |
| Provider competition increased | Anthropic, Google, Meta (open-source), and Chinese providers (DeepSeek, Qwen, Kimi, GLM) driving prices down |
| Chinese models disrupted pricing floor | DeepSeek V4-Flash at $0.14/$0.28 and Qwen-Turbo at $0.05/$0.20 forced US providers to compete at lower tiers |

---

## 2. Cost Per Request Math

### The Universal Formula

```
Cost/Request = (Input Tokens × Input Price) + (Output Tokens × Output Price)

Monthly Cost = Cost/Request × Requests/Month
```

### Worked Examples (Real 2026 Numbers)

#### Example 1: Simple Chat Bot (GPT-4.1-mini)

| Component | Tokens | Price/MTok | Cost/Request |
|-----------|--------|-----------|--------------|
| System prompt | 500 | $0.40 (uncached) | $0.0002 |
| System prompt | 500 | $0.10 (cached) | $0.00005 |
| User message (avg) | 200 | $0.40 | $0.00008 |
| RAG context | 3,000 | $0.10 (cached) | $0.0003 |
| Output | 400 | $1.60 | $0.00064 |
| **Total (cached)** | 4,100 | | **$0.00107** |
| **Total (uncached)** | 4,100 | | **$0.00122** |

At **100K requests/month**: $107-$122/month (cached vs uncached)
At **1M requests/month**: $1,070-$1,220/month

#### Example 2: Enterprise RAG System (Claude Sonnet 4.6)

| Component | Tokens | Price/MTok | Cost/Request |
|-----------|--------|-----------|--------------|
| System prompt + tools | 2,000 | $0.30 (cache read) | $0.0006 |
| Retrieved docs (5 chunks) | 8,000 | $0.30 (cache read) | $0.0024 |
| User query | 150 | $3.00 (uncached) | $0.00045 |
| Output (detailed) | 1,200 | $15.00 | $0.018 |
| **Total** | 11,350 | | **$0.02145** |

At **50K requests/month**: **$1,072.50/month**
At **500K requests/month**: **$10,725/month** — needs optimization

#### Example 3: Code Review Agent (GPT-5.1)

| Component | Tokens | Price/MTok | Cost/Request |
|-----------|--------|-----------|--------------|
| System + rules | 1,500 | $0.125 (cached) | $0.0001875 |
| Git diff (avg) | 5,000 | $1.25 (uncached) | $0.00625 |
| Context files | 10,000 | $0.125 (cached) | $0.00125 |
| Output (review) | 2,000 | $10.00 | $0.02 |
| **Total** | 18,500 | | **$0.02769** |

At **10K PRs/month**: **$276.90/month** — reasonable
At **100K PRs/month**: **$2,769/month** — model tier routing could cut 70%

### Cost Scaling Patterns

| Volume | GPT-4.1-mini | Claude Sonnet 4.6 | GPT-5.4 |
|--------|-------------|-------------------|---------|
| 1K/day (~30K/mo) | ~$33/mo | ~$640/mo | ~$830/mo |
| 10K/day (~300K/mo) | ~$330/mo | ~$6,400/mo | ~$8,300/mo |
| 100K/day (~3M/mo) | ~$3,300/mo | ~$64,000/mo | ~$83,000/mo |
| 1M/day (~30M/mo) | ~$33,000/mo | ~$640,000/mo | ~$830,000/mo |

**Key insight**: At scale (>100K req/day), every 10% token reduction = $3K-640K/month saved. Optimization becomes existential.

---

## 3. Prompt Caching

Prompt caching reuses the computed KV-cache from prior requests that share the same prompt prefix, avoiding redundant computation.

### OpenAI Prompt Caching (Automatic)

- **Enabled automatically** for all gpt-4o+ models — no code changes needed
- Requires **1024+ tokens** in the prompt
- **90% discount on cached input tokens** ($1.75 → $0.175 for GPT-5.2)
- **No extra charge for cache writes** — zero cost to create cache entries
- **5-10 minutes inactivity** retention (in-memory), up to **24 hours** (extended on GPT-5.x, GPT-4.1)
- Cache hits require **exact prefix match** — static content must be at the beginning
- ~15 requests/min per prefix before cache overflow to other machines
- `prompt_cache_key` parameter to influence routing for better hit rates
- Up to **80% latency reduction** on cache hits

**Extended retention** (available on GPT-5.2, GPT-5.1, GPT-4.1):
- KV-tensors offloaded to GPU-local storage
- Retains cache up to **24 hours**
- Not Zero Data Retention eligible (tensors derived from customer content persisted to local storage)

### Anthropic Prompt Caching (Explicit + Automatic)

Two modes:

**Automatic caching**: Add `"cache_control": {"type": "ephemeral"}` at request top level. System automatically places breakpoint on last cacheable block.

**Explicit cache breakpoints**: Place `cache_control` on individual content blocks for fine-grained control. Up to 4 breakpoints per request.

**Pricing multipliers** (relative to base input):
- **5-min cache write**: 1.25x
- **1-hour cache write**: 2.0x
- **Cache read**: 0.1x (90% savings)

**Minimum cacheable prompt length** (varies by model):
- **512 tokens**: Claude Fable 5, Claude Mythos 5
- **1,024 tokens**: Claude Opus 4.8, Claude Sonnet 4.6, Claude Sonnet 4.5
- **2,048 tokens**: Claude Opus 4.7
- **4,096 tokens**: Claude Opus 4.6, Claude Opus 4.5, Claude Haiku 4.5

**20-block lookback**: If your breakpoint doesn't match, the system walks back up to 20 blocks looking for a prior cache write. If no match found, full cache miss.

**Pre-warming**: Send `max_tokens: 0` request with cached system prompt to populate cache before users arrive. Incurs cache write cost but zero output cost.

**Cache invalidation rules**:
- Changing tool definitions → invalidates entire cache
- Changing images → invalidates messages cache
- Changing system prompt → invalidates system + messages cache
- Adding thinking blocks → model-specific behavior (preserved on Opus 4.5+/Sonnet 4.6+, stripped on earlier)

### Cache Hit Rate Optimization

| Strategy | Impact | Effort |
|----------|--------|--------|
| Static content at prompt start | High | Low |
| Pre-warm cache before traffic | High (first-request latency) | Low |
| Use 1-hour TTL for low-frequency prompts | Medium | Low |
| Monitor `cached_tokens` in response | Operational | Low |
| Use `prompt_cache_key` (OpenAI) for routing | Medium | Low |
| Minimize changes to cached prefix | High | Medium |
| Use explicit breakpoints (Anthropic) for multi-frequency content | High | Medium |
| Maintain 15 req/min per prefix (OpenAI) | Prevents overflow | Medium |

**Datadog 2026 finding**: Only **28% of LLM calls** show any cached-read input tokens despite widespread support. Most common cause: dynamic content injected too early in prompt, breaking prefix match.

### Prefix Layout Best Practice

```
[SYSTEM PROMPT - STATIC]        ← Cache this
[TOOL DEFINITIONS - STATIC]     ← Cache this
[FEW-SHOT EXAMPLES - STATIC]   ← Cache this
[RAG DOCUMENTS - SEMI-STATIC]  ← Cache this (separate breakpoint)
────────── CACHE BREAKPOINT ──────────
[USER MESSAGE - DYNAMIC]        ← NOT cached
[CONVERSATION HISTORY - GROWING] ← Cache via automatic (Anthropic)
```

---

## 4. Semantic Caching

Semantic caching stores responses for **semantically similar** (not just identical) queries, using embeddings-based similarity matching.

### How It Works

```
1. User query arrives
2. Embed query using embedding model (e.g., text-embedding-3-small at $0.02/MTok)
3. Search vector store for similar cached queries (cosine similarity > threshold)
4. If match found → return cached response (no LLM call)
5. If no match → call LLM, cache result
```

### Tools & Implementations

| Tool | Type | Key Features |
|------|------|-------------|
| **GPTCache** | Open-source (Python) | Embeddings + similarity search, supports multiple vector DBs, TTL, eviction |
| **Custom (Redis + embeddings)** | Self-built | Full control, integrate with existing infra, production-ready at scale |
| **LangChain Cache** | Library | Semantic caching built into LangChain chain |
| **Portkey** | Gateway | Semantic caching in gateway proxy |
| **Zilliz/GPTCache** | Open-source | FAISS/Chroma/Milvus backends, supports multiple LLM providers |

### Design Decisions

| Decision | Options | Recommendation |
|----------|---------|---------------|
| **Embedding model** | OpenAI text-embedding-3-small ($0.02/MTok), Cohere, local | Use provider embedding or local model for cost |
| **Vector store** | FAISS (in-memory), Chroma, Redis, Milvus | Redis if already in infra, FAISS for dev |
| **Similarity threshold** | cosine > 0.85 (strict), > 0.75 (medium), > 0.65 (loose) | Start at 0.85, tune based on quality |
| **TTL** | 5 min, 1 hour, 1 day, forever | Match data freshness needs |
| **Cache key** | Full query embedding, normalized query | Normalize before embedding (lowercase, strip punctuation) |

### When Semantic Caching Helps vs Hurts

**Helps** (30-50% cost reduction):
- FAQ / knowledge base queries — many users ask the same thing differently
- Documentation lookup — similar questions about same topics
- Customer support — repetitive issues
- Code generation — common patterns ("sort a list in Python")

**Hurts** (quality degradation, wasted cache space):
- Personalized queries — "summarize MY document" can't be cached for others
- Time-sensitive queries — stock prices, news
- Creative generation — each request should be unique
- Multi-turn conversations — context grows, making similarity matching unreliable
- High-cardinality queries — every query is different (IDs, names, specific data)

### Cost of Semantic Caching

Embedding cost is negligible: 200 tokens × $0.02/MTok = $0.000004 per embedding call. The real cost is:
- Vector store storage (typically <1 cent per 10K entries)
- Latency: +5-20ms for similarity search
- Engineering effort to build and maintain

---

## 5. Prompt Compression

Techniques to reduce token count while maintaining output quality.

### Techniques

| Technique | How It Works | Compression Ratio | Quality Impact | Tool |
|-----------|-------------|-------------------|---------------|------|
| **LLMLingua-2** | Trains a small classifier to identify and remove unimportant tokens | 2-4x (50-75% reduction) | Minimal on instruction-following tasks | [GitHub](https://github.com/microsoft/LLMLingua) |
| **Selective Context** | Uses perplexity-based scoring to remove least informative tokens | 2-3x (50-66%) | Low on factual tasks | [GitHub](https://github.com/liujch1998/Selective-Context) |
| **Instruction Pruning** | Remove redundant instructions, merge overlapping examples | 20-40% | Very low | Manual |
| **Example Culling** | Remove low-value few-shot examples, keep most representative | 20-60% | Task-dependent | Manual + eval |
| **Context Chunking** | Only include relevant chunks from retrieved documents | 30-70% | High (if retrieval is good) | RAG pipeline |
| **System Prompt Minification** | Compress verbose system prompts to essential instructions | 30-60% | Low | Manual |
| **Conversation Summarization** | Summarize old messages instead of full history | 50-80% | Medium | Automated |

### Practical Prompt Compression Playbook

1. **Start with instruction pruning** (lowest effort, lowest risk):
   - Remove redundant rules ("be helpful" + "be useful" → keep one)
   - Merge similar examples
   - Remove filler phrases in system prompts

2. **Then example culling**:
   - Run eval with all examples, then iteratively remove examples that don't affect accuracy
   - Keep minimum set that maintains quality on golden eval set

3. **Then context optimization**:
   - Rerank retrieved chunks by relevance before including in prompt
   - Set max context tokens per request (e.g., 8K for RAG)
   - Use reranker model to filter top-K most relevant chunks

4. **Then automated compression** (highest effort):
   - Apply LLMLingua-2 or Selective Context for large documents
   - Measure quality impact with eval suite
   - Roll back if quality drops below threshold

### When NOT to Compress

- **Structured output tasks**: Compression can break JSON formatting instructions
- **Legal/compliance prompts**: Every word may carry regulatory weight
- **Low token count prompts**: If already <2K tokens, compression savings are minimal
- **Tasks with high sensitivity to context**: Reasoning tasks where removing any token changes the answer

---

## 6. Model Tier Routing (Cascade Architecture)

The single most impactful cost optimization: route each request to the cheapest model that can handle it.

### The Cascade Pattern

```
User Request
    │
    ▼
    [Step 1: Cheap Classifier] (GPT-5-nano / GPT-5.4-nano / Claude Haiku 4.5 / Gemini Flash)
    │  Cost: $0.00005-0.0002/request
    │  Classifies: simple | standard | complex
    │
    ├─ simple → [Fast Model] (GPT-5.4-mini / GPT-5-mini / Claude Haiku 4.5)
    │             Cost: $0.0003-0.002/request
    │
    ├─ standard → [Standard Model] (GPT-4.1-mini / GPT-5.4 / Claude Sonnet 4.6)
    │              Cost: $0.001-0.01/request
    │
    └─ complex → [Frontier Model] (GPT-5.5 / GPT-5.1 / Claude Sonnet 4.6 / Claude Opus 4.5)
                  Cost: $0.01-0.05/request
                  Only if confidence < threshold on standard tier
```

### Typical Distribution & Savings

| Query Complexity | % of Traffic | Model | Cost/Request | Avg Cost/Request |
|-----------------|-------------|-------|-------------|-----------------|
| Simple (classification, extraction) | 50-60% | GPT-5-nano ($0.05/$0.40) | $0.0003 | $0.0002 |
| Standard (summarization, Q&A) | 25-35% | GPT-5.4-mini ($0.75/$4.50) | $0.0012 | $0.0004 |
| Complex (reasoning, multi-step) | 10-15% | GPT-5.4 ($2.50/$15) | $0.0127 | $0.0015 |
| **Blended average** | 100% | Mixed | | **$0.0022** |

**If all traffic went to GPT-5.4**: $0.0127/request
**With tier routing**: $0.0022/request
**Savings: 83%**

### Routing Approaches

| Approach | How It Works | Accuracy | Latency Overhead |
|----------|-------------|----------|-----------------|
| **Rule-based** | If task=extraction → fast tier; if needs reasoning → frontier | Medium | ~0ms |
| **Classifier-based** | Separate classifier model predicts complexity tier | High | +50-100ms |
| **Cascade/escalation** | Try fast model, check confidence, escalate if low | High | +latency on escalation (10-15% of requests) |
| **ML-based** | Train on historical data (query → best model) | Highest | +50-100ms |
| **Signal-driven** | Use token count, user tier, feature flags | Medium | ~0ms |

### Cascade Escalation Detail

```python
def route_request(prompt):
    # Step 1: Try fast model
    result = call_model(prompt, model="gpt-5-nano")
    confidence = result.confidence_score

    if confidence >= 0.85:
        return result  # 80%+ of requests handled here

    # Step 2: Escalate to standard model
    result = call_model(prompt, model="gpt-5.4-mini")
    confidence = result.confidence_score

    if confidence >= 0.80:
        return result  # 15% of requests

    # Step 3: Frontier model for edge cases
    return call_model(prompt, model="gpt-5.4")  # 5% of requests
```

**Cost of misrouting**: If a simple query goes to the frontier model, you overpay 10-50x. If a complex query goes to a fast model, quality suffers and you may need a retry (doubling cost).

---

## 7. Batch API & Offline Processing

### OpenAI Batch API

- **50% cost reduction** on both input and output tokens
- Async processing: results available within 24 hours (typically 1-6 hours)
- Minimum batch size: none, but cost-effective at 100+ requests
- Max batch size: varies by tier (typically 50K-200K requests)
- Streaming not supported (all requests are non-streaming)
- Use for: embeddings, fine-tuning evals, data enrichment, content moderation, document processing

**Batch API pricing example** (GPT-5.1):
- Standard: $1.25 input + $10.00 output
- Batch: **$0.625 input + $5.00 output** (50% off)

### OpenAI Flex Processing

- Significantly lower costs for non-production, lower-priority workloads
- Exchange: slower response times and occasional resource unavailability
- Use for: model evaluations, data enrichment, async workloads

### Anthropic Message Batches

- **50% discount** on input and output tokens
- Same quality as standard API
- Results within 24 hours
- Good for: large-scale content processing, evaluation runs, data labeling

### When to Batch vs Real-Time

| Use Case | Mode | Reason |
|----------|------|--------|
| User-facing chat | Real-time | User waiting for response |
| Search ranking | Real-time | Part of request path |
| Content moderation | Batch | Can process offline |
| Document summarization | Batch | No user waiting |
| Embedding generation | Batch | Pre-compute, not on critical path |
| Data labeling/annotation | Batch | Offline task |
| Eval suite runs | Batch | CI pipeline, not user-facing |
| Nightly report generation | Batch | No urgency |
| Code review | Real-time | Developer waiting |
| Log analysis | Batch | Can wait hours |

### Batch Architecture

```
[Application] → [Queue (SQS/Kafka)] → [Batch Collector] → [Batch Job File]
                                                       ↓
                                              [Batch API Submission]
                                                       ↓
                                              [Poll for Completion]
                                                       ↓
                                              [Results → Store/Notify]
```

Design for:
- **Batch window**: Collect requests for N minutes before submitting (5-60 min typical)
- **Max batch size**: Cap at provider limits to avoid rejection
- **Retry failed batches**: Some requests may fail within the batch, handle individually
- **Result delivery**: Push to S3/pubsub when complete, or pull on demand

---

## 8. Self-Hosted vs Hosted Cost Analysis

### GPU Rental Math (2026 Cloud Pricing)

| GPU | Provider | Spot Price | On-Demand | VRAM | Throughput (70B model) |
|-----|----------|-----------|-----------|------|----------------------|
| **A100 80GB** | AWS/GCP | ~$1.50/hr | ~$3.00/hr | 80GB | ~2,000 tok/s |
| **A100 40GB** | AWS/GCP | ~$0.80/hr | ~$1.50/hr | 40GB | ~1,500 tok/s (quantized) |
| **H100 80GB** | AWS/GCP | ~$2.50/hr | ~$4.00/hr | 80GB | ~4,000 tok/s |
| **H200 141GB** | AWS/GCP | ~$3.50/hr | ~$5.50/hr | 141GB | ~5,000 tok/s |
| **8x A100** | AWS p4d | ~$12/hr | ~$32/hr | 640GB | ~16,000 tok/s |

### Break-Even Calculations

**Scenario: GPT-4.1-mini ($0.40/$1.60) vs self-hosted Llama 3.3 70B on 1x A100**

| Volume | Hosted (GPT-4.1-mini) | Self-Hosted (1x A100 spot) |
|--------|----------------------|--------------------------|
| 100K req/mo (3K tok avg) | ~$120/mo | ~$1,080/mo (GPU) |
| 1M req/mo | ~$1,200/mo | ~$1,080/mo |
| 10M req/mo | ~$12,000/mo | ~$1,080/mo |
| 100M req/mo | ~$120,000/mo | ~$4,320/mo (4x A100) |

**Break-even for GPT-4.1-mini**: ~800K requests/month (at ~3K tokens each)

**Scenario: Claude Sonnet 4.6 ($3/$15) vs self-hosted Qwen3 235B on 2x H100**

| Volume | Hosted (Claude Sonnet) | Self-Hosted (2x H100 spot) |
|--------|----------------------|---------------------------|
| 100K req/mo (5K tok avg) | ~$4,500/mo | ~$3,600/mo |
| 1M req/mo | ~$45,000/mo | ~$3,600/mo |
| 10M req/mo | ~$450,000/mo | ~$14,400/mo (4x H100) |

**Break-even for Claude Sonnet 4.6**: ~80K requests/month (at ~5K tokens each)

### Self-Hosted Total Cost of Ownership

GPU rental is only part of the cost:

| Cost Category | Estimate (1x A100, 24/7) | Notes |
|---------------|------------------------|-------|
| GPU rental | ~$1,000-2,000/mo | Spot vs on-demand |
| Serving framework (vLLM/TGI) | $0 (open-source) | Engineering time to set up |
| Monitoring & observability | $100-500/mo | Datadog, Prometheus, etc. |
| Redundancy (multi-GPU for HA) | 2x GPU cost | Single GPU = single point of failure |
| Engineering maintenance | ~$5K-15K/mo (FTE fraction) | Model updates, scaling, incidents |
| **Total** | **$7K-20K/mo** | Including engineering |

### When Self-Hosting Makes Sense

- **High volume**: >1M requests/month with consistent traffic
- **Data privacy**: Can't send data to external providers (HIPAA, on-prem requirements)
- **Custom models**: Fine-tuned models for specific domains
- **Cost at scale**: Break-even for expensive models at relatively low volumes
- **Latency control**: No network round-trip to external provider, controllable queuing

### When Hosted APIs Win

- **Low-moderate volume**: <500K requests/month
- **Bursty traffic**: Pay-per-request is cheaper than provisioning for peak
- **Rapid iteration**: No infra to manage, swap models instantly
- **Multi-model strategy**: One API call accesses GPT-5, Claude, Gemini — no GPU per model
- **Reliability**: Provider handles scaling, failover, model updates
- **Compliance**: ZDR (Zero Data Retention) options from Anthropic/OpenAI

### Serving Frameworks for Self-Hosted

| Framework | Language | Key Features |
|-----------|----------|-------------|
| **vLLM** | Python | PagedAttention, continuous batching, 10x throughput vs naive |
| **TGI (Text Generation Inference)** | Rust | HuggingFace's serving engine, quantization, Flash Attention |
| **TensorRT-LLM** | C++ | NVIDIA-optimized, best throughput on NVIDIA GPUs |
| **llama.cpp** | C/C++ | CPU/GPU hybrid, quantized models, local deployment |
| **Ollama** | Go | Easy local deployment, good for development |
| **SGLang** | Python | RadixAttention, speculative decoding |

---

## 9. Budget Enforcement Architecture

### Budget Hierarchy

```
Organization Budget
  └── Team Budget
       └── Feature Budget
            └── Per-Request Budget
                 └── Per-Component Budget (system prompt, RAG context, output)
```

### Architecture Components

```
                    ┌──────────────────┐
                    │  Budget Service   │
                    │  (centralized)    │
                    └────────┬─────────┘
                             │
              ┌──────────────┼──────────────┐
              │              │              │
     ┌────────▼──────┐ ┌───▼──────────┐ ┌──▼──────────┐
     │ Cost Tracker  │ │ Alert Engine │ │ Enforcement │
     │ (per request) │ │ (thresholds) │ │ (hard caps) │
     └──────────────┘ └──────────────┘ └─────────────┘
              │              │              │
     ┌────────▼──────────────▼──────────────▼────────┐
     │              LLM Gateway / Proxy               │
     │  (LiteLLM, TensorZero, custom)                │
     │  - Pre-counts tokens before routing            │
     │  - Tags requests with team/feature/tenant      │
     │  - Rejects if over budget                      │
     │  - Routes to cheaper model if near cap         │
     └──────────────────────────────────────────────┘
```

### Budget Policies

| Policy Level | Implementation | Example |
|-------------|---------------|---------|
| **Per-request cap** | Max tokens per request | Max 10K input tokens, 2K output tokens |
| **Per-user cap** | Tokens/day per user ID | 100K tokens/day per free-tier user |
| **Per-feature cap** | Monthly budget per feature flag | $5K/month for "AI summary" feature |
| **Per-team cap** | Monthly budget per team | $20K/month for "platform" team |
| **Per-tenant cap** | Budget per enterprise customer | $500/month per SaaS tenant |
| **Organization cap** | Hard monthly limit | $100K/month org-wide |
| **Burn rate alerts** | Spend rate exceeds threshold | Alert if daily spend > $5K (projected $150K/mo) |
| **Hard caps** | Reject requests when budget exhausted | Return 429/gated message when cap reached |

### Alert Thresholds

```
Alert at 50% of budget → "Feature X has spent $2.5K of $5K budget"
Alert at 75% → "Feature X approaching budget limit ($3.75K / $5K)"
Alert at 90% → "URGENT: Feature X at $4.5K of $5K budget — investigate or cap"
Hard cap at 100% → All requests for feature X rejected or downgraded to free tier model
```

### Implementation Pattern

```python
class BudgetEnforcer:
    def __init__(self, budget_service, gateway):
        self.budget_service = budget_service
        self.gateway = gateway

    async def call_llm(self, request):
        budget = await self.budget_service.get_budget(
            team=request.team,
            feature=request.feature,
            tenant=request.tenant
        )

        estimated_cost = self.estimate_cost(request)
        if budget.remaining < estimated_cost:
            return self.downgrade_or_reject(request, budget)

        result = await self.gateway.call_llm(request)
        actual_cost = self.calculate_actual_cost(result.usage)

        await self.budget_service.record_spend(
            team=request.team,
            feature=request.feature,
            tenant=request.tenant,
            cost=actual_cost,
            tokens_in=result.usage.input_tokens,
            tokens_out=result.usage.output_tokens
        )

        self.check_alerts(budget, actual_cost)
        return result

    def downgrade_or_reject(self, request, budget):
        if budget.fallback_model:
            return self.gateway.call_llm(request, model=budget.fallback_model)
        raise BudgetExceededError(budget)
```

### Quota Management for Multi-Tenant

| Dimension | Free Tier | Pro Tier | Enterprise |
|-----------|-----------|----------|-----------|
| Requests/day | 100 | 10,000 | Unlimited |
| Tokens/day | 50K | 5M | Custom |
| Max input tokens/request | 2K | 32K | 128K |
| Model tier | Nano only | All except Pro | All |
| Rate limit | 10 RPM | 100 RPM | Custom |

---

## 10. Cost Optimization Playbook

Ordered from easiest wins (do first) to complex changes (do later):

### Tier 1: Quick Wins (Day 1, 0-1 week)

| Strategy | Expected Savings | Effort |
|----------|-----------------|--------|
| **Enable prompt caching** | 20-40% on repeated prompts | Low — add `cache_control` or just use OpenAI auto-caching |
| **Route classification/extraction to nano models** | 60-80% on those tasks | Low — change model parameter |
| **Set output token limits** | 10-30% (prevent runaway generation) | Low — `max_tokens` parameter |
| **Track cost per request** | Enables all other optimizations | Low — add logging in gateway |
| **Set per-request token caps** | Prevents cost spikes | Low — add validation before LLM call |

### Tier 2: Medium Effort (Week 1-2)

| Strategy | Expected Savings | Effort |
|----------|-----------------|--------|
| **Model tier routing (cascade)** | 70-80% overall | Medium — classifier + routing logic |
| **Prompt compression (manual)** | 20-40% token reduction | Medium — review and compress prompts |
| **Batch API for async work** | 50% on batched workloads | Medium — queue + batch collector |
| **Semantic caching** | 30-50% on repetitive queries | Medium — embeddings + vector store |
| **A/B test cheaper models** | Variable (may find 90%+ quality at 10% cost) | Medium — eval suite + gradual rollout |

### Tier 3: Complex (Week 2-4)

| Strategy | Expected Savings | Effort |
|----------|-----------------|--------|
| **Self-hosting for high-volume workloads** | 80-95% at scale | High — GPU infra, serving, monitoring |
| **Fine-tuned small models replacing prompts** | 90%+ for specific tasks | High — training data, fine-tuning, eval |
| **Budget enforcement architecture** | Prevents overruns (saves unlimited) | High — budget service, quotas, alerts |
| **Custom semantic caching with ML** | 40-60% | High — embedding model, similarity tuning |
| **Automated prompt compression pipeline** | 30-50% | High — compression model, quality eval |

### Combined Savings Estimate

Starting from baseline (no optimization):

| Optimization Stack | Cumulative Savings |
|--------------------|-------------------|
| Tier 1 only (caching + nano routing + caps) | **40-60%** |
| Tier 1 + Tier 2 (cascade + compression + batch) | **70-85%** |
| Tier 1 + 2 + 3 (self-hosting + fine-tuning + budgets) | **85-95%** |

### Cost Optimization Anti-Patterns

1. **Optimizing too early**: Don't optimize before you have traffic. $100/month doesn't justify a week of engineering.
2. **Optimizing the wrong thing**: Focus on the highest-cost feature first, not the easiest.
3. **Ignoring quality**: Cutting costs by 80% but dropping accuracy from 95% to 60% is not a win.
4. **No baseline**: Can't measure savings without knowing starting cost.
5. **Single strategy dependency**: Relying only on caching means you're vulnerable when cache misses spike.
6. **Forgetting engineering cost**: Self-hosting saves $50K/year on API costs but costs $100K/year in engineering time.

---

## Interview Questions & Model Answers

### Q1: "Calculate the monthly cost for a customer support chatbot handling 200K conversations/month, each averaging 3K input tokens and 500 output tokens, using Claude Sonnet 4.6."

A: Input: 200K × 3,000 = 600M tokens × $3/MTok = $1,800. Output: 200K × 500 = 100M tokens × $15/MTok = $1,500. Total: **$3,300/month uncached**. With 70% cache hit on system prompt (2K of 3K input): 70% × 200K × 2K = 280M cached input × $0.30/MTok = $84, plus 30% × 200K × 2K = 120M uncached × $3/MTok = $360, plus 200K × 1K uncached user input × $3/MTok = $600. Total cached input: $84 + $360 + $600 = $1,044. Output unchanged: $1,500. **Total with caching: ~$2,544/month (~23% savings)**. For more savings, I'd add model tier routing: route 50% simple queries to Haiku 4.5 ($1/$5) which drops those from ~$0.012 to ~$0.004/request — saving ~$800/month.

### Q2: "How would you reduce LLM costs by 80% for a production system?"

A: Five strategies, in order of impact: (1) **Model tier routing** — the biggest lever. Route 60% of traffic to nano/mini models (classification, extraction, simple Q&A), 25% to mid-tier, only 15% to frontier. This alone achieves 70-80% savings. (2) **Prompt caching** — 20-40% on cached portions. Structure prompts with static content first. (3) **Batch API** for all async workloads — 50% savings on embeddings, evaluations, data processing. (4) **Semantic caching** for FAQ-style queries — 30-50% reduction on repetitive traffic. (5) **Prompt compression** — reduce token count 20-40% with instruction pruning and example culling. Combined: 85-95% savings. The critical part: measure before and after with an eval suite to ensure quality doesn't degrade.

### Q3: "Explain how prompt caching works and why your team might not be benefiting from it."

A: Prompt caching reuses the KV-cache (key-value attention layers) from prior requests with the same prompt prefix. OpenAI does this automatically (90% discount on cached tokens, 1024+ token minimum). Anthropic requires explicit or automatic `cache_control` breakpoints. The Datadog 2026 report found only 28% of LLM calls use caching. Why teams miss out: (1) Dynamic content injected too early in the prompt, breaking the prefix match. (2) System prompts change between requests (timestamps, user-specific data at the start). (3) Below minimum token threshold. (4) Not monitoring cache hit rate — you can't fix what you don't measure. Fix: restructure prompts with all static content first, monitor `cached_tokens` in API response, pre-warm cache before traffic with `max_tokens: 0` requests.

### Q4: "When would you choose self-hosting over hosted APIs? Walk through the math."

A: Break-even depends on volume and model tier. For GPT-4.1-mini ($0.40/$1.60 input/output): self-hosted on 1x A100 spot (~$1,080/month including overhead) breaks even around 800K requests/month at 3K tokens avg. For Claude Sonnet 4.6 ($3/$15): breaks even around 80K requests/month. I'd self-host when: (1) consistent high volume (>1M req/month), (2) data can't leave infrastructure (HIPAA, on-prem), (3) custom fine-tuned models are needed. I'd use hosted APIs when: (1) traffic is bursty, (2) I need multiple models (GPT, Claude, Gemini), (3) I'm in prototype/early growth phase. The engineering cost of self-hosting (vLLM setup, monitoring, scaling, model updates) is often $5-15K/month in FTE time — include that in the TCO calculation.

### Q5: "Design a budget enforcement system for a multi-tenant AI platform."

A: Four layers: (1) **Per-request**: max token caps enforced at gateway before calling the LLM. Reject requests exceeding limits. (2) **Per-tenant**: monthly token/cost budget per tenant. Track in Redis or budget service. (3) **Per-feature**: each AI feature has its own budget. If exceeded, fall back to cheaper model or disable feature. (4) **Organization**: hard monthly cap. Alerts at 50%, 75%, 90%. Hard stop at 100%. Implementation: budget service that tracks cumulative spend per (tenant, feature, team) tuple. Gateway checks budget before every LLM call. If budget exceeded, return graceful error or route to free-tier model. Burn rate alerts: project current daily spend to monthly, alert if projection exceeds budget. Quota tiers: free users get token caps, enterprise gets custom limits.

### Q6: "What is semantic caching and when would you use it vs prompt caching?"

A: Semantic caching caches responses for semantically similar (not identical) queries using embedding similarity. Prompt caching reuses KV-cache for exact prefix matches at the provider level. Key difference: semantic caching catches "What's the refund policy?" and "How do I get a refund?" as the same query. Prompt caching only catches identical prompt prefixes. I'd use prompt caching for: repeated system prompts, tool definitions, multi-turn conversations — any scenario where the prefix is literally the same. I'd use semantic caching for: FAQ systems, documentation lookup, customer support — where users ask the same question differently. Both can be combined: prompt caching reduces per-request cost for static context, semantic caching eliminates the LLM call entirely for similar queries.

### Q7: "You notice your LLM costs tripled in a month. Walk through your debugging process."

A: (1) Check cost attribution dashboard — which feature, team, or tenant drove the spike? (2) Check per-request token distribution — did average token count increase? (3) Check request volume — did traffic spike, or is cost-per-request higher? (4) Check model routing — did the cascade classifier break, sending everything to frontier model? (5) Check cache hit rate — did a prompt change break caching? (6) Check for retry storms — did a provider outage trigger cascading retries? Common culprits: runaway agent loops (agent calling LLM in unbounded loop), cache misses from prompt changes, a new feature launched without budget cap, retry storms during partial outage. Fix: add per-request token caps, fix the routing classifier, restore cache-friendly prompt structure, cap retries, add budget alerts.

### Q8: "Compare the cost optimization strategies available across OpenAI, Anthropic, and Google."

A: **Caching**: OpenAI has automatic caching (no code changes, 90% discount, 1024+ tokens). Anthropic has explicit/automatic breakpoints with 5-min or 1-hour TTL (0.1x on reads, 1.25x/2x on writes). Google has similar prefix-based caching on Gemini. **Batch API**: OpenAI offers 50% discount on async batches. Anthropic offers 50% on message batches. Google has batch prediction. **Model tiers**: All three have cheap/fast models (GPT-4.1-mini, Claude Haiku 4.5, Gemini Flash) at $0.10-0.40/MTok input — 10-25x cheaper than their frontier models. **Key difference**: Anthropic charges for cache writes (1.25x-2x), OpenAI doesn't. OpenAI's extended retention (24h) is available on newer models. Anthropic's explicit breakpoints give finer control. Google's 1M token context window is largest, which can paradoxically increase costs if teams stuff it unnecessarily.

### Q9: "Explain the cascade architecture for model routing. What are the failure modes?"

A: Cascade routing tries the cheapest model first, escalates to more expensive models if confidence is low. Typically: nano/mini classifier → standard model → frontier model. Handles 80%+ of traffic on the cheapest tier. Failure modes: (1) **Misclassification** — simple query routed to expensive model (overpay) or complex query handled by cheap model (bad quality). Mitigated by eval-driven classifier tuning. (2) **Cascade latency** — escalation adds latency (cheap model call + expensive model call). Mitigated by parallel speculative calls on the standard tier. (3) **Classifier drift** — query distribution shifts over time, classifier becomes inaccurate. Mitigated by periodic retraining on production data. (4) **Cost of classifier itself** — the routing classifier adds cost. Mitigated by using nano models ($0.05/MTok) which add negligible cost. (5) **Confidence calibration** — cheap model's confidence score may not be well-calibrated. Mitigated by calibrating thresholds on eval data.

### Q10: "Your PM wants to add AI-powered features across the product. How do you ensure costs don't spiral out of control?"

A: Four-pronged approach: (1) **Cost-per-feature estimation before building**: Calculate tokens per request × traffic × price per token. Present projected monthly cost to PM before any engineering work. (2) **Budget caps at the feature level**: Each feature gets a monthly budget. Gateway enforces the cap. If exceeded, feature degrades to cheaper model or disables. (3) **Phased rollout**: Start every feature on the cheapest model that's "good enough." Measure quality with evals. Only upgrade model tier if evals show quality gap. (4) **Continuous optimization**: Monthly cost review per feature. Identify the highest-cost feature and optimize it. Track cost per successful outcome (not just cost per request) — if the AI feature costs $5K/month but saves $50K/month in human labor, it's a good investment regardless of absolute cost.

### Q11: "How do prompt compression techniques affect output quality? How would you measure the tradeoff?"

A: Different techniques have different quality profiles. LLMLingua-2 (token pruning) achieves 2-4x compression with minimal quality loss on instruction-following tasks, but can degrade on tasks requiring precise reasoning. Selective Context (perplexity-based removal) works well for factual tasks but can remove crucial context for complex reasoning. Manual instruction pruning has near-zero quality impact — it removes genuinely redundant instructions. The way to measure: build an eval suite with 200+ golden examples. Run the eval at full prompt and at each compression level. Plot accuracy vs compression ratio. Find the sweet spot where compression is maximized without accuracy dropping below your threshold (typically 2-3% degradation tolerance). This becomes a regression test — any prompt change that falls below the threshold fails CI.

### Q12: "What are the hidden costs of LLMs that people forget to budget for?"

A: Beyond the per-token API cost: (1) **Embedding costs** — semantic caching, RAG retrieval: text-embedding-3-small at $0.02/MTok adds up at scale. (2) **Retry costs** — a 3-retry policy on 5% error rate means 15% extra API calls. (3) **Rate limit backoff** — queued requests consume engineering infra (SQS, Kafka). (4) **Engineering time** — prompt iteration, eval maintenance, monitoring, incident response. Often 2-3x the API cost in FTE time. (5) **Overhead tokens** — system prompts, tool definitions, formatting instructions. Datadog found 69% of input tokens are system prompts, not user input. (6) **Reasoning tokens** (OpenAI o-series) — invisible tokens that are billed as output. A "simple" answer might use 10K reasoning tokens you can't see. (7) **Data egress** — streaming responses, image inputs, file uploads. (8) **Evaluation costs** — running evals against new models burns tokens.

---

## Key Terminology

| Term | Definition |
|------|-----------|
| Token | Smallest unit of text processed by an LLM; ~3/4 English word or 4 characters |
| MTok | Million tokens; standard pricing unit |
| KV-Cache | Key-Value cache from transformer attention layers; reused in prompt caching |
| Cache Hit | When a prompt prefix matches a previously cached computation |
| Cache Miss | When no cached prefix is found; full computation required |
| Prompt Compression | Reducing token count while maintaining output quality |
| Semantic Caching | Caching responses for semantically similar (not identical) queries |
| Model Tier Routing | Directing requests to the cheapest adequate model based on complexity |
| Cascade Architecture | Try cheap model first, escalate if confidence is low |
| Batch API | Async processing at 50% discount for non-real-time workloads |
| Flex Processing | Lower cost for non-production, lower-priority workloads (OpenAI) |
| Cache Write | Initial computation stored in cache; costs 1.25x-2x base (Anthropic) or free (OpenAI) |
| Cache Read | Reuse of cached computation; costs 0.1x base (90% savings) |
| Token Budget | Maximum tokens allowed per request/team/feature/time window |
| Burn Rate | Current spend rate projected over a time period |
| Break-Even Volume | Number of requests where self-hosting becomes cheaper than hosted API |
| Reasoning Tokens | Invisible output tokens in o-series models, billed at output rate |
| Extended Retention | Cache persistence beyond in-memory (24h for OpenAI, 1h for Anthropic) |
| Pre-warming | Populating cache with `max_tokens: 0` requests before traffic arrives |
| vLLM | Open-source high-throughput LLM serving engine with PagedAttention |
| TGI | Text Generation Inference — HuggingFace's production serving engine |
| Provisioned Throughput | Reserved model capacity billed hourly; no per-token charges. Available on Bedrock (1-6 month commitment), Vertex AI (GSU-hourly), Azure (PTU) |
| PTU | Provisioned Throughput Unit — Azure's unit of reserved model capacity, billed per PTU-hour |
| GSU | GPU Streaming Unit — Vertex AI's unit for provisioned throughput, billed per GSU-hour |
| Knowledge Bases | AWS Bedrock's managed RAG pipeline using OpenSearch Serverless; minimum ~$700/month |
| Private Inference | LLM inference within a VPC/private network, no public internet exposure. Available on all three cloud providers |
| TCoO | Total Cost of Ownership — includes token costs, infrastructure overhead, engineering time, compliance, and hidden costs |

## Cross-References

| Topic | Connection |
|-------|-----------|
| [Multi-Model Gateway](../multi_model_gateway/discussion.md) | Gateway is the enforcement point for cost tracking, model routing, caching — cost engineering implements the strategies the gateway executes |
| [AI Product Engineering](../ai_product_engineering/discussion.md) | Cost per feature analysis and feasibility assessment — cost engineering provides the calculation framework |
| [LLM in Production](../llm_in_production/discussion.md) | System prompt tax (69% of tokens), cache underutilization (28% adoption), context engineering — cost engineering addresses the monetary impact |
| [Security](../security/discussion.md) | PII redaction cost (extra LLM call for scanning), data residency affecting provider choice, private inference via VPC endpoints, compliance umbrellas (HIPAA, FedRAMP) |
| [SLO & Error Budgets](../slo_error_budgets/discussion.md) | Cost budgeting parallels error budgeting — same alerting and enforcement patterns |
| [RAG System](../../system_design/rag_system/discussion.md) | RAG context is the largest token consumer — chunking strategy, reranking, and retrieval quality directly affect cost |
| [Feature Flags](../feature_flags/discussion.md) | Enable/disable expensive AI features per user segment; gradual model tier rollout |
| [Cloud Cost](../cloud_cost/discussion.md) | GPU rental costs, infrastructure TCO for self-hosted models; cloud provider managed inference hidden costs (egress, support plans, idle endpoints) |
| [Capacity Planning](../capacity_planning/discussion.md) | Planning for LLM traffic growth and its impact on API costs, GPU provisioning, and provisioned throughput decisions |
