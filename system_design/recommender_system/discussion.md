# Design a Recommender System

Source: [MLSD Case Study: End-to-End Recommender System (CalibreOS)](https://www.calibreos.com/learn/mlsd-recommender-system)

## One-Liner
Build a multi-stage recommendation pipeline that retrieves candidate items from a large catalog, ranks them by relevance and engagement, and applies diversity/exploration rules before serving.

## Functional Requirements
- Generate personalized item recommendations (videos, products, articles) per user
- Support multiple serving surfaces (home feed, up-next, email, sidebar)
- Handle new items and new users with no interaction history (cold start)
- Enable real-time updates when user preferences shift within a session
- Support A/B testing of ranking models and re-ranking strategies

## Non-Functional Requirements
- End-to-end latency under 200ms (p99) from request to rendered recommendations
- Scale to 1B+ items in the catalog with sub-50ms retrieval
- Support 500M+ daily active users with varying engagement patterns
- 99.9% availability for the serving path (retrieval + ranking)
- Offline evaluation metrics (NDCG@10) must correlate with online metrics (CTR, retention)

## Key Scale Questions
- 500M DAU, 1B+ items in catalog
- ~10K recommendation requests per second at peak
- Retrieval must narrow 1B+ items down to ~500 candidates in <50ms
- Light ranker must score 500 candidates in <20ms
- Heavy ranker must score 100 candidates in <70ms
- Re-ranking must produce final top-20 slate in <10ms
- Feature store: ~100ms freshness budget for online features, daily refresh for offline features

## Core Components
- **Two-Tower Retrieval**: User tower (online) and item tower (offline precomputed) produce embeddings for ANN lookup via FAISS/ScaNN
- **Light Ranker (GBDT)**: LightGBM/XGBoost scoring 500 candidates on CPU in ~20ms, filtering to 50-100
- **Heavy Ranker (Multi-Task DNN)**: Deep neural network on GPU predicting click, watch-time, satisfaction, and retention jointly
- **Re-Ranking Service**: Applies diversity (MMR/DPP), exploration (epsilon-greedy, bandits), and business rules (freshness boosts, content policy, promoted content slots)
- **Feature Store**: Online features (real-time session signals, <100ms freshness) and offline features (historical aggregates, daily refresh)
- **ANN Index**: FAISS IVF with product quantization, sub-50ms lookup over 1B+ items, daily reindexing
- **Evaluation Pipeline**: Offline (NDCG@K, Recall@K) and online (A/B tests on CTR, watch-time, D7 retention) with guardrails (Gini coefficient, fresh content share)

## Key Design Decisions

### Retrieval Architecture
- **Option A: Two-Tower + ANN**: Decouple user/item encoding. Precompute item embeddings offline, index in FAISS. Sub-50ms retrieval from 1B+ items. Production standard at YouTube, Spotify, Pinterest
- **Option B: Collaborative Filtering (Matrix Factorization)**: Simpler, but limited to users/items with interaction history. Poor cold-start. Good as a supplementary retriever
- **Option C: Generative (HSTU/TIGER)**: Transformer over interaction sequences, generates next-item predictions. Handles cold-start via semantic IDs from content embeddings. Emerging (2024-2026), GPU-expensive, not yet replacing two-tower at billion-item scale

### Ranking Stages
- **Option A: Single heavy ranker**: Score all 500 candidates with DNN. Too slow (~350ms), blows latency budget
- **Option B: Multi-stage (light → heavy)**: GBDT filters 500→100, then DNN scores 100→20. Fits within 200ms budget. 95%+ recall@50 vs heavy-only baseline. Industry standard (Netflix, YouTube)
- **Option C: Retrieval-only (no ranking)**: Use retrieval scores directly. Fast but low quality — retrieval optimizes for recall, not fine-grained relevance

### Exploration Strategy
- **Option A: Epsilon-greedy**: Replace top items with random/uncertain items with probability epsilon (1-5%). Simple, effective
- **Option B: Thompson Sampling / Contextual Bandits**: Model engagement as a distribution, sample from posterior. Better exploration-exploitation balance, used for artwork A/B testing (Netflix)
- **Option C: No exploration**: Pure exploitation. Maximizes short-term metrics but causes feedback loops, filter bubbles, and popularity concentration

## API Endpoints
| Method | Path | Description |
|--------|------|-------------|
| GET | /api/recommendations?surface=home&limit=20 | Get personalized recommendations for a surface |
| POST | /api/events/click | Log click event for model training |
| POST | /api/events/watch-time | Log watch-time / dwell-time signal |
| GET | /api/recommendations/explain?item_id=x | Get explanation for why item was recommended |
| POST | /api/recommendations/feedback | Submit explicit feedback (not interested, save) |

## Database Schema
| Column | Type | Notes |
|--------|------|-------|
| user_id | BIGINT | User identifier |
| item_id | BIGINT | Item identifier |
| event_type | ENUM | click, watch, like, skip, dislike |
| dwell_time_ms | INT | Time spent on item |
| position | INT | Slot position shown (for position bias correction) |
| surface | ENUM | home_feed, up_next, email, sidebar |
| timestamp | TIMESTAMP | Event time |

## Deep Dive Topics
- Negative sampling strategies: random (easy), batch (medium), hard negatives (items retrieved but not engaged, 1:1:4 ratio). Hard negatives are the single biggest lever in two-tower quality
- Cold-start handling: content-based fallback using text/image embeddings from pretrained encoders for new items; popularity-based fallback for new users
- Feedback loop mitigation: popularity bias compounds over time in purely collaborative systems. Diversity constraints (MMR, DPP), creator exposure fairness caps, and exploration budgets break the cycle
- Offline-online metric gap: NDCG lift may not translate to retention lift. Root causes: train-serve skew, objective mismatch, feedback-loop effects. Mitigate with counterfactual logging, calibrated objectives, A/A tests
- Generative recommenders (2024-2026): Meta HSTU replaces multi-stage funnel with single transformer. Google TIGER uses semantic IDs for cold-start. Still needs retrieval shortlist at billion-item scale. GPU serving cost is the bottleneck
- Multi-task ranking: weighted value model (e.g., 50% watch-time, 20% CTR, 20% satisfaction, 10% retention). Weights are product decisions, not modeling decisions

## Follow-Up Variations
- How would you handle a recommender for a new platform with no historical interaction data?
- Your CTR improved 5% but D7 retention dropped 2%. What do you investigate?
- How would you design the system to support real-time model updates within a user session?
- How do you prevent the recommender from creating filter bubbles?
- What changes when the catalog is only 10K items vs 1B items?
