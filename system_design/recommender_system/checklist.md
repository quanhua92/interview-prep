# Design a Recommender System — Working Checklist

Source: [MLSD Case Study: End-to-End Recommender System (CalibreOS)](https://www.calibreos.com/learn/mlsd-recommender-system)

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] What is the serving surface? (home feed, up-next, search, email, sidebar)
  - [ ] What is the item type? (videos, products, articles, music tracks)
  - [ ] What is the p99 latency budget? (typically 200ms end-to-end)
  - [ ] Is freshness critical (news, live events) or can recommendations be cached?
  - [ ] What is the catalog size and user base scale?
- [ ] List functional requirements (3-5 items):
  - [ ] Generate personalized recommendations per user per surface
  - [ ] Handle cold start for new items and new users
  - [ ] Support real-time preference updates within a session
  - [ ] Enable A/B testing of ranking models and strategies
  - [ ] Support explicit feedback (not interested, save for later)
- [ ] List non-functional requirements:
  - [ ] End-to-end latency <200ms (p99)
  - [ ] Scale to 1B+ items and 500M+ DAU
  - [ ] 99.9% availability on the serving path
  - [ ] Offline metrics must correlate with online business metrics
- [ ] State your scale estimates:
  - [ ] 1B+ items in catalog
  - [ ] 500M DAU, ~10K recommendation requests/sec at peak
  - [ ] Retrieval: 1B → ~500 candidates in <50ms
  - [ ] Light ranking: 500 → 100 in <20ms
  - [ ] Heavy ranking: 100 → 20 in <70ms
  - [ ] Re-ranking: final slate in <10ms

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw a box diagram: Client → API Gateway → [Orchestrator] → [Retrieval (Two-Tower + ANN)] → [Light Ranker] → [Heavy Ranker] → [Re-Ranker] → Response
- [ ] Identify the main operations and data flow:
  - [ ] `GET /api/recommendations` — multi-stage funnel (read, latency-critical)
  - [ ] `POST /api/events/click` — log interaction events (write, async)
  - [ ] `POST /api/events/watch-time` — log engagement signals (write, async)
  - [ ] Background: model retraining, embedding reindexing, feature store refresh
- [ ] Explain the multi-stage funnel and why it exists:
  - [ ] Cannot run a cross-encoder over 1B items per request
  - [ ] Each stage reduces candidates: 1B → 500 → 100 → 20 → final slate
  - [ ] Each stage uses a progressively more expensive model
- [ ] Present the diagram and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain the retrieval stage (Two-Tower architecture):
  - [ ] User tower: encodes user context (user_id, history, demographics, session) into 128-256 dim embedding. Runs online (~5ms)
  - [ ] Item tower: encodes item features (item_id, metadata, content embeddings, engagement stats). Precomputed offline for all items
  - [ ] ANN index: FAISS IVF with product quantization, sub-50ms lookup over 1B+ items
  - [ ] Multiple retrievers in parallel (two-tower + trending + content-based + collaborative filtering), merged before ranking
- [ ] Explain negative sampling for two-tower training:
  - [ ] Random negatives: too easy, model doesn't learn fine distinctions
  - [ ] Batch negatives: efficient but introduces false negatives for popular items
  - [ ] Hard negatives (production standard): items retrieved but not engaged, forces fine-grained discrimination
  - [ ] Typical ratio: 1:1:4-8 (positive : batch negative : hard negative)
- [ ] Explain multi-stage ranking:
  - [ ] Light ranker (GBDT): scores 500 candidates on CPU in ~20ms using lightweight features (IDs, rates, context). Reduces to 50-100
  - [ ] Heavy ranker (Multi-Task DNN): scores 100 candidates on GPU in ~70ms. Predicts click, watch-time, satisfaction, retention jointly
  - [ ] Multi-task learning: shared bottom layers + task-specific heads. Weights are product decisions (e.g., 50% watch-time, 20% CTR, 20% satisfaction, 10% retention)
- [ ] Explain re-ranking stage:
  - [ ] Diversity: MMR or DPP to avoid near-duplicate items
  - [ ] Category/creator constraints (e.g., max 2 items from same creator in top-10)
  - [ ] Freshness boost for recently published items
  - [ ] Content policy filtering and promoted content insertion
- [ ] Define API endpoints:
  - [ ] `GET /api/recommendations?surface=home&limit=20` → ranked item list
  - [ ] `POST /api/events/click` → log interaction event
  - [ ] `POST /api/events/watch-time` → log engagement signal
  - [ ] `POST /api/recommendations/feedback` → explicit feedback
- [ ] Sketch the event/interaction schema:
  - [ ] user_id, item_id, event_type (click/watch/like/skip), dwell_time_ms, position (for position bias), surface, timestamp
- [ ] Walk through the main flow end-to-end:
  - [ ] Request arrives → orchestrator calls retrieval → ANN returns 500 candidates → light ranker filters to 100 → heavy ranker scores → re-ranker applies rules → top-20 slate returned
  - [ ] Events logged asynchronously to event bus for model retraining

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss cold-start handling:
  - [ ] New items: use content-based embeddings (text/image from pretrained encoders) until collaborative signals accumulate
  - [ ] New users: popularity-based or demographic-based recommendations until interaction history builds
  - [ ] Generative approach: semantic IDs from content (TIGER) eliminate cold-start for items
- [ ] Address feedback loops and filter bubbles:
  - [ ] Problem: system trained on its own recommendations concentrates engagement on same items
  - [ ] Mitigation: diversity constraints (MMR, DPP), creator exposure fairness caps (Gini < 0.75), exploration budget (2-5% of slots)
  - [ ] Propensity-weighted training to correct for exposure bias
- [ ] Discuss exploration strategies:
  - [ ] Epsilon-greedy: simple, replace top items with random/uncertain items at 1-5% rate
  - [ ] Thompson Sampling / Contextual Bandits: sample from posterior distribution, better exploration-exploitation trade-off
  - [ ] Dropout-based uncertainty: identify items the model is uncertain about, preferentially explore those
- [ ] Explain evaluation approach:
  - [ ] Offline: NDCG@10 for ranking quality, Recall@500 for retrieval, diversity metrics (intra-list dissimilarity)
  - [ ] Online: CTR, watch-time/session, D7 retention. A/B test with holdout group
  - [ ] Guardrails: Gini coefficient on impressions, fresh content share (>20% for video, >50% for news), new-item exposure rate
  - [ ] Offline-online gap: NDCG lift may not translate to retention lift. Calibrate objectives, use counterfactual logging
- [ ] Discuss feature store design:
  - [ ] Online features: session context, recent clicks, time-of-day. Freshness budget <100ms
  - [ ] Offline features: historical engagement rates, user embeddings, item embeddings. Refreshed daily
  - [ ] Training-serving consistency: same feature computation code path for training and serving
- [ ] Flag generative recommenders as the architectural frontier (2024-2026):
  - [ ] Meta HSTU: single transformer replaces multi-stage funnel. +12.4% NE vs DLRM
  - [ ] Google TIGER: semantic IDs for items, sequence-to-sequence prediction. Solves cold-start
  - [ ] Not yet replacing two-tower at billion-item scale — still needs retrieval shortlist
  - [ ] GPU serving cost is the bottleneck (KV cache reuse, speculative decoding needed)

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made and why
- [ ] Mention what you would improve with more time
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
