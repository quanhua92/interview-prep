# Design a Real-Time Fraud Detection System
Source: [Fraud Detection (CalibreOS)](https://www.calibreos.com/learn/mlsd-fraud-detection)

## One-Liner
Detect fraudulent transactions in real-time using a multi-stage cascade of rules, GBDT scoring, and graph-based deep learning, all within a sub-100ms latency budget.

## Functional Requirements
- Score every payment transaction for fraud probability in real-time
- Block, allow, or flag for review based on configurable thresholds
- Provide explainability for declined transactions (regulatory requirement)
- Continuously learn from confirmed fraud labels (chargebacks, analyst reviews)
- Detect coordinated fraud rings via entity-relationship graphs

## Non-Functional Requirements
- End-to-end latency under 100ms at p99 (some networks require 50ms)
- Handle 1K-5K TPS for typical e-commerce; up to 24K TPS at Visa scale
- Support extreme class imbalance (~0.1% fraud rate)
- Resist adversarial drift (fraudsters actively evade the model)
- Satisfy regulatory constraints: explainable decisions, PCI-DSS compliance, audit trails

## Key Scale Questions
- ~0.1% base fraud rate (1 in 1,000 transactions)
- Asymmetric costs: C_FN (missed fraud) is typically 5-10x C_FP (false positive block)
- Typical C_FN ~$535 (avg fraud amount + chargeback fee ~$25-50)
- Typical C_FP ~$100 (customer lifetime value x churn probability)
- Label delay: 7-30 days for confirmed fraud via chargebacks
- ~1K TPS average, ~5K TPS peak for e-commerce

## Core Components
- **Rules Engine**: In-memory hash lookups for blacklists, velocity limits, and hard thresholds (~3ms)
- **Feature Store (Redis)**: Velocity counters (sliding windows), behavioral profiles, graph embeddings
- **GBDT Scorer (LightGBM)**: Primary ML model on tabular features (~10ms, CPU)
- **GNN Embedding Service**: Pre-computed entity embeddings for fraud ring detection (nearline, hourly)
- **Deep Model (MLP)**: Secondary scorer for borderline cases using entity embeddings (~35ms, CPU)
- **Streaming Feature Pipeline (Flink + Kafka)**: Real-time velocity feature computation
- **Training Pipeline**: Daily retraining with label delay handling and calibration correction

## Key Design Decisions

### Multi-Stage Cascade Architecture
- **Stage 1 — Rules** (~3ms, 100% traffic): Hard blocks, blacklists, velocity limits. Eliminates obvious cases.
- **Stage 2 — GBDT** (~25ms, ~30% traffic): LightGBM with 500 trees on tabular + velocity features. Scores the remaining transactions.
- **Stage 3 — Deep Model** (~40ms, ~2% traffic): Shallow MLP on pre-computed GNN entity embeddings. Only for borderline scores between two thresholds.
- CPU chosen over GPU for Stage 3: only ~2% of traffic (~20 TPS), CPU is 30x cheaper and fast enough.

### Optimal Decision Threshold
- Never use threshold = 0.5. It assumes equal costs and balanced classes — both false in fraud.
- Optimal threshold formula: `threshold = C_FP / (C_FN + C_FP)`.
- With typical values: 100 / (535 + 100) ~ 0.157. Block any transaction with P(fraud) > 15.7%.
- Requires calibrated probabilities (Platt scaling or isotonic regression) before applying the formula.

### Why GBDTs Win Over Deep Learning for the Primary Scorer
- **Latency**: LightGBM ~10ms vs comparable MLP ~30ms on CPU.
- **Calibration**: Trees produce naturally well-calibrated probabilities.
- **Missing values**: Trees handle NaN natively; neural nets need imputation.
- **Interpretability**: SHAP on GBDTs is fast and reliable for regulatory requirements.
- **Training speed**: LightGBM trains on 100M rows in <30 min vs hours for neural nets.

### Handling Suppression Bias (Feedback Loop)
- The model's own blocks suppress ground truth labels for those transactions.
- Over time, the model loses signal in regions it aggressively blocks — compounding error.
- Mitigation: approve a small fraction (~0.1%) of borderline declines with monitoring (exploration budget), generating counterfactual ground truth for unbiased retraining.

## API Endpoints
| Method | Path | Description |
|--------|------|-------------|
| POST | /api/transactions/score | Score a transaction for fraud probability |
| GET | /api/transactions/{id}/explain | Get SHAP explanation for a declined transaction |
| POST | /api/rules | Create or update a fraud rule |
| GET | /api/models/performance | Get current model metrics (PR-AUC, recall, EFL) |
| POST | /api/labels | Submit confirmed fraud label (chargeback or analyst review) |

## Database Schema
| Column | Type | Notes |
|--------|------|-------|
| transaction_id | STRING | PK, unique per payment attempt |
| user_id | STRING | Account making the transaction |
| amount | DECIMAL | Transaction amount |
| merchant_id | STRING | Merchant identifier |
| fraud_score | FLOAT | Model output P(fraud) |
| decision | ENUM | ALLOW, BLOCK, REVIEW |
| label | ENUM | CONFIRMED_FRAUD, CONFIRMED_LEGIT, UNLABELED |
| label_source | ENUM | CHARGEBACK, ANALYST, RULE_TRIGGER |
| created_at | TIMESTAMP | Transaction timestamp |
| label_updated_at | TIMESTAMP | When label was last updated |

## Deep Dive Topics
- **Graph Neural Networks for Fraud Rings**: Build bipartite graph of cards, devices, IPs, accounts, merchants. Use GraphSAGE to generate entity embeddings. A new card looks clean in isolation, but 2-hop connections to 5 confirmed fraud accounts via shared device reveal the ring.
- **Geo-Velocity Feature**: If a POS transaction in NYC occurred 2 hours ago and a card-not-present request comes from London, required travel speed is 2,750 km/h — physically impossible. One of the highest-signal features.
- **Label Delay Problem**: Never evaluate on transactions from the last 30 days. Labels are incomplete (chargebacks arrive 14-30 days later). Enforce a hard eval cutoff.
- **Dollar-Weighted Training and Evaluation**: A $50K wire fraud matters 4,000x more than a $12 coffee. Weight training samples by transaction amount and track dollar-weighted recall.
- **Class Imbalance Handling**: Use `scale_pos_weight=999` in LightGBM (no data duplication). If downsampling, apply Bayes' theorem odds-ratio correction to recalibrate probabilities back to production distribution.
- **Calibration Drift**: Model probabilities drift over time as adversarial patterns evolve. Run monthly reliability diagrams and recalibrate with Platt scaling or isotonic regression.
- **A/B Testing Fraud Models**: 50/50 split, minimum 30-day duration for delayed labels. Shadow mode first (score but don't decide). Never declare winner until full label window closes.

## Follow-Up Variations
- How would you adapt this system for account takeover detection instead of payment fraud?
- How would you handle a sudden 40% spike in fraud rate with no change in transaction volume?
- What if regulators require human-readable explanations for every declined transaction?
- How would you design the system to detect first-party fraud (friendly fraud / chargeback abuse)?
- What changes if the latency budget drops to 50ms?
- How would you handle model monoculture risk (all stages failing on the same adversarial pattern)?
