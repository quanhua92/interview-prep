# ML/AI Engineer

Building, evaluating, and deploying machine learning models that solve real-world problems reliably and at scale.

## Core Competencies

| Area | Description | Proficiency Expectation |
|------|-------------|------------------------|
| Supervised Learning | Regression, classification, ensemble methods, regularization, cross-validation | Select appropriate algorithms; tune hyperparameters systematically |
| Unsupervised Learning | Clustering (k-means, DBSCAN), dimensionality reduction (PCA, t-SNE), anomaly detection | Apply to real problems; evaluate without labels |
| Model Evaluation | Precision/recall, F1/F-beta, ROC-AUC, PR-AUC, MCC, confusion matrix, bias-variance trade-off, statistical tests, threshold optimization | Choose the right metric for the business problem; tune thresholds for operating point |
| Feature Engineering | Feature selection, encoding, scaling, feature stores, temporal features | Transform raw data into effective model inputs |
| MLOps & Deployment | Model serving, A/B testing, canary deployments, model monitoring, feature stores, pipelines | Deploy and monitor models in production |
| Neural Networks | CNNs, RNNs/Transformers, backpropagation, activation functions, regularization | Explain architecture choices; debug training issues |
| NLP & CV Basics | Tokenization, embeddings, attention mechanism, image preprocessing, transfer learning | Apply pre-trained models; fine-tune for specific tasks |
| Bias & Fairness | Fairness metrics, disparate impact, data bias detection, interpretability, responsible AI | Identify and mitigate bias; explain model decisions |
| Recommender Systems | Two-tower retrieval, multi-stage ranking, cold-start, exploration-exploitation, NDCG | Design end-to-end recommendation pipelines from retrieval to serving |
| Decision Trees & Ensembles | CART algorithm, split criteria (Gini/entropy/MSE), cost-complexity pruning, surrogate splits, oblivious trees, feature importance bias, TreeSHAP | Explain why single trees are never deployed alone; tune ensemble depth and pruning strategy |
| Regression Metrics | MAE, RMSE, MAPE, SMAPE, R-squared, Huber Loss, Pinball (Quantile) Loss | Select loss/metric aligned with error cost structure (outlier sensitivity, relative vs absolute) |
| Model Calibration | Reliability diagrams, ECE, Brier score, Platt scaling, isotonic regression, temperature scaling | Audit and fix probability outputs when downstream decisions require trusted probabilities |
| Multiclass Evaluation | Macro/micro/weighted averaging, per-class OvR analysis, confusion matrices for multi-label | Report the right aggregate; debug per-class failures |
| Linear & Logistic Regression | OLS normal equation and MLE equivalence, Gauss-Markov BLUE (LINE assumptions), QR decomposition, residual diagnostics (QQ plot, Cook's D, VIF, leverage/hat matrix), sigmoid/log-odds/log-loss, MSE non-convexity for classification, IRLS/Newton-Raphson, L1/L2/ElasticNet geometry and sparsity (subdifferential argument), perfect separation, GLM unification (exponential family, canonical link functions), multinomial softmax, FTRL-Proximal, linear vs tree ensemble trade-offs | Derive OLS two ways; explain why MSE fails for classification (non-convexity + vanishing gradient); argue L1 sparsity geometrically; name FTRL-Proximal and why it beats SGD for sparse online learning |
| Computer Vision | Convolutions, weight sharing, translation equivariance, receptive fields, 1x1 convolutions, pooling, CNN architectures (LeNet to EfficientNet), ResNet skip connections, ViT vs CNNs, Swin Transformer, object detection (YOLO, R-CNN), NMS | Explain convolution mechanics; choose architecture for data scale and latency constraints; design transfer learning pipelines |
| Tokenization (Subword) | BPE (frequency-based merge), WordPiece (likelihood-based merge, ## prefix), SentencePiece/Unigram LM (language-agnostic, prunes vocab), byte-level BPE (zero OOV), tiktoken | Choose the right tokenizer for the language/domain; explain vocab-size vs sequence-length tradeoff; diagnose domain-mismatch tokenization |
| NLP Embeddings | Static (Word2Vec, GloVe, FastText) vs contextual (BERT, GPT); BERT layer roles (1-4 syntax, 5-8 semantics, 9-12 task-specific); SBERT/sentence-transformers for semantic search | Select embedding strategy for the task; explain why static embeddings fail for polysemy; pick pooling strategy (mean pool vs [CLS]) |
| BERT vs GPT Architecture | Encoder (bidirectional attention, MLM) vs decoder (causal/autoregressive attention, CLM); MLM 15% masking rule (80/10/10 split); NSP (removed by RoBERTa); T5 span corruption | Explain why BERT cannot generate text; justify architecture choice for classification vs generation tasks |
| Fine-Tuning Strategies | Full fine-tuning, linear probe, gradual unfreezing, LoRA (W' = W + BA, rank r << d), QLoRA (4-bit NF4 + LoRA), prompt/prefix tuning; Hugging Face PEFT library | Choose fine-tuning regime based on hardware/data budget; configure LoRA rank and target modules; explain when full fine-tuning beats LoRA |
| Bias-Variance Diagnosis | Formal decomposition (Bias^2 + Variance + Irreducible Noise), learning curves, train/val gap analysis, double descent (Belkin 2019), regularization strength vs model behavior | Diagnose high bias vs high variance from learning curves; state whether more data helps before collecting it; explain why over-parameterized models can still generalize |
| Regularization Methods | L1/L2/ElasticNet geometry and mechanisms, dropout (inverted, co-adaptation prevention), batch normalization as implicit regularizer, early stopping (Bishop 1995 equivalence to L2), AdamW vs Adam+L2, gradient clipping, data augmentation | Choose the right regularizer by model family and data regime; explain AdamW decoupling; identify when regularization masks a data problem |
| Imbalanced Classification | PR-AUC vs ROC-AUC under imbalance, class weights, focal loss, SMOTE (and when it hurts), Pozzolo calibration correction after undersampling, cost-sensitive threshold tuning, anomaly detection for extreme imbalance | Diagnose which of three imbalance conditions applies (bad metric, biased loss, asymmetric costs); derive Bayes-optimal threshold from cost matrix; explain why SMOTE often backfires on tabular+GBDT |
| Categorical Encoding | One-hot, target/mean encoding with K-fold CV smoothing, hashing trick, embeddings, CatBoost ordered stats; encoding choice by cardinality x model family | Pick encoding by cardinality (<15 one-hot, 15-1000 target with smoothing, >1000 hashing/embeddings); implement leakage-safe K-fold target encoder; explain why one-hot wastes tree depth at high cardinality |
| Data Leakage & Training-Serving Skew | 4 leakage types (target leakage, temporal leakage, feature definition leakage, train/test contamination), ColumnTransformer + Pipeline, point-in-time joins, PSI for drift detection, feature parity contracts | Identify and fix each leakage type; design leakage-safe feature pipelines; explain why training-serving skew is the #1 production bug in tabular ML |
| Missing Data Strategies | MCAR/MAR/MNAR (Rubin 1976), mean/median imputation, MICE, indicator columns, native handling by XGBoost/CatBoost vs manual imputation for sklearn | Diagnose missingness mechanism; choose strategy by model family (trees handle natively, linear/NN need imputation); explain when indicator columns add signal |
| Feature Selection | Filter (correlation, mutual information), wrapper (recursive feature elimination), embedded (L1, tree importance), permutation importance, SHAP | Choose method by dataset size and model family; explain why MDI is biased (Strobl 2007) and permutation importance is the production fix |
| Temporal Feature Engineering | Cyclical encoding (sin/cos for hour, day-of-week), lag features, rolling aggregations, time-since features, expanding-window statistics | Build temporal features that avoid look-ahead; choose between fixed-window and expanding-window aggregations; encode cyclical features correctly |
| Loss Function Design | MSE/MAE/Huber for regression, cross-entropy/focal loss for classification, Triplet/InfoNCE for embeddings, label smoothing, loss-metric alignment | Select loss function derived from business objective, target distribution, and class balance; diagnose loss-metric misalignment |
| Optimization & Training | SGD with momentum, Adam/AdamW, learning rate warmup + cosine/linear decay, gradient clipping, mixed precision (FP16/BF16), gradient accumulation | Configure optimizer and schedule by model family; debug training instability; explain AdamW vs Adam+L2 |
| Recommendation Fundamentals | Multi-stage funnel (retrieval -> ranking -> re-ranking), collaborative filtering, matrix factorization, two-tower architecture, pointwise/pairwise/listwise ranking, negative sampling, ANN search | Design end-to-end recommendation pipeline; explain retrieval-first principle; configure two-tower training with InfoNCE and hard negatives |
| A/B Testing & Experimentation | 6-step lifecycle, sample size calculation, SRM checks, CUPED variance reduction, novelty effect, peeking, multiple comparisons, guardrail metrics, quasi-experiments (DiD, RDD) | Design valid experiments; diagnose common pitfalls (peeking, novelty, network effects); apply CUPED to reduce experiment duration |
| XGBoost & Gradient Boosting | Regularized objective (gamma + lambda), second-order Taylor expansion, optimal leaf weight w*=-G/(H+lambda), split gain formula, histogram approximation, sparsity-aware splits, SHAP values | Derive the XGBoost objective step by step; configure hyperparameters by bias-variance diagnostic; compare XGBoost/LightGBM/CatBoost |
| Neural Network Fundamentals | Backpropagation (chain rule, computational graphs), activation functions (ReLU, GELU, SiLU, sigmoid, tanh), weight initialization (He/Xavier), BatchNorm/LayerNorm/RMSNorm, forward/backward pass, universal approximation theorem | Derive backprop for a 2-layer network from scratch; choose activation by architecture; debug vanishing/exploding gradients from layer-wise gradient norms |
| RNN/LSTM/GRU Sequence Models | Vanilla RNN recurrence and BPTT, vanishing/exploding gradients (Pascanu 2013), LSTM cell state and gates (Hochreiter & Schmidhuber 1997), GRU (Cho 2014), seq2seq with Bahdanau attention, state-space models (Mamba 2023) | Derive BPTT gradient product and explain vanishing; explain LSTM's Constant Error Carousel; justify architecture choice by sequence length, streaming vs batched, and compute budget |
| Transformer Architecture | Scaled dot-product attention (Q/K/V, sqrt(d_k) scaling), multi-head attention, positional encodings (sinusoidal, learned, RoPE, ALiBi), encoder/decoder/encoder-decoder variants, GQA, RMSNorm, SwiGLU FFN, parameter count formula (~12L * d_model^2) | Derive self-attention from scratch; explain sqrt(d_k) scaling via variance argument; calculate parameter count and FLOPs for a given architecture; distinguish BERT vs GPT vs T5 |
| Bootstrap & Resampling | Efron's bootstrap (1979), BCa confidence intervals, permutation tests, block bootstrap for time series, jackknife, bagging/OOB connection, cluster bootstrap | Construct BCa CI from scratch; distinguish bootstrap (uncertainty) from permutation (hypothesis testing); identify 4 failure modes (extremes, dependence, small n, heavy tails) |
| Probability Distributions for ML | Bernoulli/Binomial (logistic regression, BCE), Poisson (count models, overdispersion), Gaussian (linear regression, CLT), Log-Normal (revenue modeling), Exponential (inter-arrival times), Beta (Thompson Sampling, conjugate prior), Dirichlet (LDA, topic models), heavy tails/Pareto, KL divergence, MLE framework | Match distribution to data-generating process; explain why MSE on log-normal targets is wrong; identify overdispersion (Poisson vs Negative Binomial); state when CLT fails |
| Hypothesis Testing | Null/alternative hypotheses, p-value interpretation, Type I/II errors, test selection (t-test, z-test, chi-square, ANOVA), Bonferroni/BH-FDR multiple testing correction, Cohen's d effect size, one-tailed vs two-tailed tests, practical vs statistical significance | Correctly interpret p-values; choose appropriate test by data type and sample size; apply multiple testing corrections; distinguish statistical from practical significance |
| Statistics & Probability Foundations | CLT mechanics and failure modes, confidence intervals, Bayesian vs frequentist framing, A/B testing pipeline, power analysis, peeking and novelty effects, unit-of-randomization matching | Explain why CLT justifies normal approximations but requires checking tail behavior; design valid A/B tests with pre-committed decision rules; choose Bayesian vs frequentist by decision context |
| Agent Memory Systems | In-context buffer, rolling summarization, semantic memory (vector DB), episodic memory (time-stamped event logs), procedural memory (fine-tuning), lost-in-the-middle effect, memory layout optimization, write gates, staleness/conflict detection | Design hierarchical memory by retrieval cost and scope; explain why context layout matters as much as content; implement write gates with durability/confidence/reuse checks; handle memory staleness and supersession |
| Instruction Tuning | SFT on (instruction, response) pairs, FLAN multi-task diversity, Alpaca self-instruct, Orca reasoning traces, Lima quality-over-quantity, conversation templates (ChatML, Llama 3), catastrophic forgetting, instruction tuning vs RAG decision framework | Explain what instruction tuning changes (behavior, not knowledge); choose between instruction tuning and RAG for a given problem; configure QLoRA for instruction tuning; mitigate catastrophic forgetting with data mixing and LoRA |
| Embeddings for RAG | word2vec to instruction-tuned embeddings evolution, Sentence-BERT, cosine similarity normalization, Matryoshka Representation Learning (MRL), embedding model comparison (text-embedding-3, BGE-M3, E5), FAISS index types, hybrid BM25+dense search, model version mismatch traps | Choose embedding model by task type, multilingual needs, and latency budget; design two-stage retrieval with MRL truncation; explain why embedding model version must match between indexing and query time; evaluate with domain-specific Recall@K not just MTEB averages |
| Structured Outputs & Constrained Decoding | Grammar-constrained decoding via FSM token masking (Outlines, Guidance, llama.cpp GBNF), OpenAI strict structured outputs, Instructor auto-retry pattern, Pydantic validation, streaming JSON with incremental parsing (ijson), schema versioning, SGLang RadixAttention for batch extraction, token budget economics | Explain FSM token masking and why it guarantees structural validity; choose between retry, strict mode, and constrained decoding by volume and SLA; design schema versioning as prompt-model-schema release triple; architect 10M-document batch extraction with self-hosted SGLang |
| Prompt Engineering for Production | Zero-shot / few-shot / CoT prompting, few-shot pitfalls (label bias, order sensitivity, format contamination), system prompt mechanics and prefix caching, CoT when it helps vs hurts, self-consistency, structured output strategies, prompt injection, token budget management, diagnostic framework | Design prompt engineering pipeline with evaluation; diagnose failure modes (format vs accuracy vs safety); estimate token cost impact of strategies; know when prompting beats fine-tuning; implement prefix caching for cost optimization |
| Tokenization for LLMs | BPE algorithm (byte-level via tiktoken), WordPiece (likelihood-based merge, ## prefix), SentencePiece/Unigram LM (language-agnostic, ▁ whitespace), vocabulary size tradeoffs, multilingual token inflation, tokenization artifacts (r-counting, arithmetic inconsistency, string reversal), token/word ratios by domain | Explain algorithmic distinctions between tokenizers; estimate token counts and costs by language/domain; trace model failures to tokenization artifacts; justify vocabulary size decisions for multilingual systems |
| AI Agents & Agentic Systems | ReAct pattern (Reason+Act+Observe loop), tool design principles and error contracts, termination semantics, agent memory types (working/episodic/semantic/procedural), context window management, agent failure modes (lost context, tool hallucination, infinite loops), safety guardrails, agent evaluation metrics, PEARL decision framework, MCP tool catalogs | Design agent architecture with tool contracts and loop guards; choose between chain, single-agent, and multi-agent by task structure; implement safety guardrails for production agents; evaluate agents on trajectory correctness not just final answer |
| Multi-Agent Systems | Orchestrator+worker pattern, single-agent failure modes (context saturation, error accumulation, no parallelization), LangGraph state machines vs LangChain Agents, AutoGen debate/critique patterns, map-reduce parallelization, shared typed state, failure modes (oscillation, hallucinated handoffs, agent-to-agent injection, privilege escalation), production evaluation (trajectory efficiency, handoff quality) | Decide when multi-agent is warranted using 5-question framework; design orchestrator-worker with typed state and checkpoints; prevent oscillation and injection attacks; evaluate on trajectory quality not just task completion; explain why demo-to-production gap is enormous |
| LLM Fine-Tuning (RLHF & DPO) | Full fine-tuning vs PEFT decision framework, LoRA math (W' = W + BA, rank r, alpha/r scaling, Q/V target modules), QLoRA (NF4 + double quantization + paged optimizers), SFT pipeline (response-only loss masking), RLHF 3-stage pipeline (SFT -> reward model -> PPO), DPO loss (bypasses reward model, beta KL control), fine-tuning failure modes (catastrophic forgetting, data contamination, reward hacking, knowledge injection anti-pattern) | Choose fine-tuning method by hardware/data budget; derive LoRA parameter savings; explain when DPO beats RLHF; configure QLoRA for consumer GPU; identify and mitigate fine-tuning failure modes |
| Chain-of-Thought & Reasoning | CoT prompting (Wei 2022), self-consistency (k-sample majority vote), Tree of Thoughts (search over verbal states), test-time compute, reasoning-tuned models, CoT overthinking on simple tasks, CoT faithfulness (post-hoc rationales vs actual computation), routing cheap vs expensive reasoning paths, verifiers vs LLM-as-judge | Design routing architecture for reasoning tiers; explain when CoT hurts; implement self-consistency with failure-mode awareness; argue for executable verifiers over LLM judges; treat exposed CoT as leak surface |
| Function & Tool Calling | Tool calling as RPC boundary, JSON Schema arguments, strict mode (token masking), parallel vs sequential tool calls, idempotency keys for mutations, OAuth scope mapping, MCP trust boundaries, tool-calling safety boundaries (schema, identity, network, tool-output), evaluator traps for structured output | Design tool contracts with authZ and idempotency; distinguish JSON mode from strict structured outputs; prevent MCP tool poisoning; evaluate full RPC contract not just valid JSON |
| LLM Evaluation & Benchmarking | HELM multi-metric design (7 metric families), MMLU contamination (13-gram overlap detection), MT-Bench, LMSYS Arena Elo, IFEval format constraints, RAGAS (faithfulness, context precision/recall), LLM-as-judge bias controls (position, verbosity, reference anchoring, rubric-order), private canary decks, offline-to-online eval bridge, contamination and eval gaming | Design regression harness with frozen prompts and thresholds; choose metric by task shape and risk surface; implement LLM-as-judge with debiasing protocol; argue public benchmarks are hints not SLAs |
| LLM Foundations & Architecture | Attention O(n^2) complexity, KV cache memory cost formula, Flash Attention (tiling + online softmax), MoE routing tradeoffs, pre-RMSNorm + residual structure, decoder dominance, architecture-to-serving constraints (decode memory-bound, prefill compute-bound), TTFT/TPS per GPU, foundation model upgrade evaluator traps | Connect every architecture choice to serving SLA; calculate KV cache memory for a given model; explain Flash Attention mechanism; gate model upgrades on canary quality not just MMLU |
| GenAI System Design | 6-phase design playbook, technique escalation ladder (prompt -> few-shot -> RAG -> LoRA -> continued pretrain), 5-layer LLM application architecture, constraints driving technique selection, research-track vs production-track interview calibration, cost-per-request math, multi-model routing | Design LLM applications from blank whiteboard in 45 minutes; justify each technique choice with a specific constraint; distinguish research vs production interview signals |
| Advanced RAG & Hybrid Retrieval | Hybrid BM25+dense retrieval, Reciprocal Rank Fusion (RRF), two-stage reranking (cross-encoder), HyDE query expansion, RAPTOR hierarchical indexing, query decomposition for multi-hop reasoning, embedding model lock-in, RAGAS evaluation metrics, production RAG failure modes | Design production RAG beyond naive vector search; explain why BM25 beats dense on exact matches; architect hybrid retrieval with latency budgets; evaluate with RAGAS faithfulness and context precision |
| RAG Architecture | Chunking strategies (fixed, semantic, hierarchical), vector database selection, ANN index types (FAISS Flat/IVF-PQ/HNSW/ScaNN), embedding model selection (BGE-M3, GTE, E5), agentic RAG (ReAct pattern), long-context vs RAG vs hybrid decision matrix, position-aware context assembly, context window strategy | Design end-to-end RAG pipeline from chunking to generation; choose ANN index by corpus size and latency target; architect agentic RAG for multi-hop queries; decide between long-context and RAG |
| LLM Serving Stack | vLLM PagedAttention, continuous batching, speculative decoding, quantisation (INT8/FP8/INT4/AWQ/GPTQ), prefix caching, GPU sizing from weights+KV cache math, TTFT/ITL targets, concurrent request capacity, self-hosted vs hosted cost analysis | Size a serving cluster from model parameters and QPS; explain PagedAttention's virtual memory analogy; calculate concurrent capacity on given hardware; design multi-model routing for cost optimization |
| GenAI Interview Strategy | 5 GenAI interviewer signals (architectural fluency, decision discipline, production realism, quantitative grounding, failure-mode awareness), 8 mindset rules, escalation ladder drill, research vs production track, level expectations (L4-L7), time-budgeting, eval as first-class component | Approach GenAI interviews with signal awareness; recover gracefully from math blanks; time-budget design problems; demonstrate cost discipline and failure-mode awareness unprompted |

## Common Interview Topics

- Explain the bias-variance trade-off and how you diagnose each
- Walk through how you would build a recommendation system
- How do you handle the cold-start problem in recommendations?
- Explain two-tower retrieval and why it scales better than cross-encoder approaches
- Your recommender's CTR improved 5% but retention dropped 2%. What do you investigate?
- How do you handle imbalanced datasets?
- Describe your approach to feature engineering for a tabular dataset
- How would you deploy a model to production and monitor it?
- Explain how a neural network learns through backpropagation
- What is the difference between precision and recall? When is each more important?
- How do you detect and handle data leakage?
- Describe how you would evaluate a fraud detection model
- Explain transfer learning and when you would use it
- Why would you use PR-AUC instead of ROC-AUC for fraud detection? Construct a concrete example where ROC-AUC is 0.99 but the model is nearly useless
- Your model has 95% accuracy but stakeholders are unhappy. What happened and what metric should you use?
- How do you choose the classification threshold for a deployed model? Walk through the math for expected-value maximization
- Explain NDCG. Calculate NDCG@3 for model-returned relevance scores [2, 0, 1] vs. ideal [2, 1, 0]
- What is model calibration? Why can a model with perfect AUC still be poorly calibrated?
- How would you evaluate a multi-label classification model where each sample can have multiple labels?
- What is the difference between RMSE and MAE? Give a scenario where choosing the wrong one leads to a bad model
- How would you evaluate a recommendation system end to end: offline metrics, online metrics, and guardrails?
- When would you use F-beta score instead of F1? What does beta control?
- Explain the difference between macro, micro, and weighted averaging for multiclass metrics
- Walk through CART's greedy recursive binary splitting algorithm. Why binary and not multi-way? Why greedy instead of optimal?
- Compare Gini impurity vs entropy vs MSE as split criteria. When does the choice actually matter in practice?
- Explain cost-complexity pruning. What is alpha, how do you select it (1-SE rule), and why do ensembles skip pruning entirely?
- Why is sklearn's default feature_importances_ biased? Describe the fix and cite Strobl 2007.
- Why are single decision trees always ensembled in production? Walk through the bias-variance logic.
- How does CART handle high-cardinality categorical features? Explain Fisher's optimal partition trick and why one-hot encoding is wrong for trees.
- How do different ML libraries handle missing values at inference time: surrogate splits (CART), learned default direction (XGBoost), vs manual imputation (sklearn)?
- What are oblivious trees (CatBoost) and why do they enable ~100x faster vectorized inference than standard trees?
- Decision trees cannot extrapolate. Why is this a structural limitation, and when does it matter in production?
- Explain convolution mechanics: how does a 3x3 filter achieve weight sharing, and why does this give translation equivariance?
- Why did deeper networks get worse before ResNet? Explain the degradation problem and how skip connections solve it (gradient highway, identity default, ensemble interpretation)
- Compare CNNs vs Vision Transformers. When does ViT win, and when does CNN still win? What is the data-scale crossover point?
- Explain the ResNet bottleneck block (1x1 -> 3x3 -> 1x1). Why does it cost 4x fewer FLOPs than a plain 3x3, 3x3 block?
- What is Global Average Pooling (GAP) and why do ResNet, EfficientNet, and ViT all use it before the final linear layer instead of a dense classifier head?
- You have 20K labeled images for defect detection (5% defective). Walk through architecture choice, transfer learning strategy (linear probe vs partial vs full fine-tuning), and how you handle the class imbalance
- Your object detection model has 0.85 mAP on test but too many false positives in production. How do you debug this? What role does NMS play?
- Explain layer-wise learning rate decay in transfer learning. Why does the head need 10x higher LR than the backbone?
- Compare YOLO (one-stage) vs R-CNN family (two-stage) for object detection. When would you pick each?
- What is Swin Transformer and why does it bridge the gap between CNNs and ViTs for dense prediction tasks like object detection?
- Compare BPE, WordPiece, and SentencePiece tokenizers. When does the choice materially affect model quality?
- Static embeddings give the same vector for "bank" (financial) and "bank" (river). How do contextual embeddings fix this, and what does each BERT layer capture?
- Why can't BERT be used directly for text generation, while GPT can? What property of the pre-training objective determines this?
- Explain LoRA. What is the rank r, what does lora_alpha control, and why does training ~0.3% of parameters match full fine-tuning on most tasks?
- Your BERT classifier scores 92% offline but 85% in production. What are the most likely causes (tokenizer domain mismatch, train-serving skew, distribution drift)?
- How would you embed 10M product descriptions for semantic search? What embedding model, what pooling, what vector DB, and how do you handle daily updates of 100K new products?
- Derive the OLS estimator two ways: as the least-squares projection and as MLE under Gaussian noise. Explain why they coincide and what that tells you about when OLS is the wrong tool
- Why does MSE fail as a loss function for logistic regression? Explain both the non-convexity argument and the vanishing-gradient argument
- Explain geometrically and algebraically why L1 regularization produces exactly-zero coefficients while L2 does not. Give a scenario where L1 is strictly better and one where L2 is strictly better
- What is perfect separation in logistic regression? Why does it make the MLE diverge, and what is the production fix?
- Explain FTRL-Proximal. Why is it preferred over SGD for online CTR models at Google and Facebook? How does it produce genuine sparsity that SGD with L1 does not?
- State the Gauss-Markov theorem. What are the LINE assumptions, which ones does it NOT require, and what do you do when each assumption breaks?
- What are the five residual diagnostics a senior engineer checks after fitting OLS? What does each detect and what is the fix?
- Explain the GLM unification. How do linear regression, logistic regression, and Poisson regression relate through the exponential family and link functions?
- When would you choose logistic regression over a tree ensemble in production? Name at least three dimensions where linear models win
- Prove the bias-variance decomposition. Where does the irreducible noise term come from?
- Your model achieves 99% training accuracy but only 60% validation accuracy. What do you do first?
- What is double descent and why does it challenge the classical bias-variance view?
- Your training error is 5% but validation error is 7%. A colleague says "add more regularization". Is this advice correct?
- How does the number of training examples affect bias and variance independently?
- What is training-serving skew and why does it cause silent model failures?
- Your model works in training but fails in production. Walk through the top 5 causes.
- How do you choose between L1, L2, and Elastic Net in production tabular models?
- Why does early stopping act like regularization, and how does it compare to explicit L2?
- How do you know whether regularization helped or merely hid a label-noise problem?
- Why can L1 be risky for interpretability even though it produces sparse models?
- How do you choose dropout rates in a neural network without cargo-culting 0.5?
- Why does AdamW outperform Adam+L2 for transformer fine-tuning? Explain the decoupling mechanism.
- Your model has both high training and high validation error. Should you add regularization?
- You have a fraud detection dataset with 0.17% positive rate. Walk through your evaluation, resampling, and threshold strategy.
- When does SMOTE hurt rather than help? Give a concrete scenario.
- Derive the Bayes-optimal classification threshold from a cost matrix. If FP costs $12 and FN costs $50K, what is the optimal threshold?
- Why is ROC-AUC optimistic under class imbalance? Cite Davis & Goadrich 2006.
- What is the Pozzolo correction after undersampling, and when do you need it?
- When should you stop framing an imbalanced problem as classification and switch to anomaly detection?
- How would you encode a categorical feature with 500 unique values for a tree model vs a linear model?
- What is leakage-safe target encoding? Why must you use K-fold CV and not the full training set?
- Your offline AUC is 0.92 but production performance is 0.78. Walk through debugging steps focusing on data leakage and training-serving skew.
- What are the 4 types of data leakage? Give a concrete example of each and the fix.
- How do you handle missing values differently for tree models vs linear models? What is MCAR/MAR/MNAR?
- How do you encode cyclical temporal features (hour of day, day of week) correctly? Why is one-hot wrong?
- What is the difference between permutation importance and tree-based MDI importance? Why is MDI biased?
- What are the five signals ML interviewers actually score? Which do junior vs senior candidates typically miss?
- When asked "tell me about overfitting" in an interview, what three layers should your answer cover in 2-3 minutes?
- What is the most expensive mistake in ML interviews: memorized formulas without understanding mechanisms?
- Why is "Adam is always better than SGD" wrong? When does SGD+momentum generalize better?
- How do you recover when you blank on a derivation during an interview?
- Why is MSE a bad loss for heavy-tailed regression targets like revenue? What loss would you use instead?
- What loss does a two-tower recommendation model use and why? Explain InfoNCE with in-batch negatives.
- What is label smoothing and why does it improve both calibration and generalization?
- You are building a fraud detection model where FN costs 100x FP. How do you adjust your loss function?
- Why does triplet loss sometimes stop learning? What is the fix?
- Why does SGD with momentum often generalize better than Adam for CNNs, but Adam wins for transformers?
- Explain the Adam update rule (first moment, second moment, bias correction). Why does AdamW decouple weight decay?
- What learning rate schedule would you use for fine-tuning BERT? What warmup fraction?
- Your transformer training loss goes to NaN at step 200. Walk through your debugging checklist.
- Why does increasing batch size from 256 to 8192 sometimes hurt generalization? What is the linear scaling rule?
- When would you use gradient accumulation? How does it simulate a larger batch?
- How does a multi-stage recommendation funnel work? Why is retrieval quality the ceiling?
- Compare user-based CF, item-based CF, matrix factorization, and two-tower DNN for retrieval. When is each appropriate?
- Explain pointwise vs pairwise vs listwise ranking. Which does LambdaMART use?
- What is the negative sampling ratio for two-tower training? What happens with too many hard negatives?
- Your A/B test shows p=0.048 on day 4. Should you ship? Why or why not?
- What is Sample Ratio Mismatch? How do you detect it and what causes it?
- Explain CUPED. How does it reduce experiment duration, and what is the requirement?
- Your ML ranking experiment improves CTR by 4% in week 1 but drops to 0.5% by week 3. What happened?
- What is the difference between Bonferroni and Benjamini-Hochberg for multiple comparisons?
- When can you not run an A/B test? Name three quasi-experimental methods and when each applies.
- Derive XGBoost's optimal leaf weight w* = -G/(H+lambda). What happens as lambda -> infinity?
- Why does XGBoost use second-order Taylor expansion and not first-order? What does the Hessian add?
- Compare XGBoost's exact greedy vs histogram approximation. When would you use each?
- How does XGBoost handle missing values at inference time? Why should you NOT impute NaN before passing to XGBoost?
- XGBoost vs LightGBM: level-wise vs leaf-wise growth. Which overfits more and why?
- Explain feature importance in XGBoost: weight vs gain vs cover vs SHAP. Which is most reliable and why?
- For a fraud dataset with 0.1% positive rate, walk through your complete XGBoost configuration.
- Derive the backpropagation gradient for a 2-layer network with ReLU hidden and softmax output. Why does the softmax + cross-entropy gradient simplify to p_hat - y?
- Your 10-layer network isn't learning. Walk through your debugging checklist in order.
- Why do skip connections solve vanishing gradients mathematically? What is the "gradient highway"?
- Compare sigmoid, tanh, ReLU, GELU, and SiLU. Which would you use for a transformer and why?
- Explain He vs Xavier initialization. Why does He use 2/n_in and Xavier use 2/(n_in + n_out)?
- What is Batch Normalization? Why does it help training? What are its limitations and what alternatives exist?
- Derive the BPTT gradient for a vanilla RNN. Where exactly do vanishing/exploding gradients come from?
- How does the LSTM's Constant Error Carousel fix vanishing gradients? Does it fix exploding gradients too?
- Compare GRU vs LSTM. When would you pick one over the other?
- Explain Bahdanau attention in seq2seq. How is it different from self-attention in a transformer?
- Why did transformers replace LSTMs, and where do RNN-shaped models (Mamba, RWKV) still win?
- Derive scaled dot-product attention from scratch. Why is the 1/sqrt(d_k) scaling critical?
- Explain multi-head attention. Why multiple heads instead of one large attention?
- What is RoPE positional encoding? Why is it better than learned absolute positional encodings?
- Calculate the parameter count and FLOPs for a Llama 3 70B forward pass with 1K tokens.
- What is the difference between encoder-only (BERT), decoder-only (GPT), and encoder-decoder (T5) architectures? When would you pick each?
- Walk through constructing a BCa confidence interval from scratch. Why is BCa the production default over percentile CIs?
- You run a bootstrap on time-series data and get a very narrow CI. What went wrong and what do you use instead?
- Explain why each bootstrap sample contains ~63.2% unique observations and how this is exploited in random forests.
- Your ML team wants uncertainty estimates for a deep neural network. Should you bootstrap the training set? What would you do instead?
- A product manager asks whether treatment B beats control A. Do you use a bootstrap CI or a permutation test, and why?
- What distribution models daily API request counts? What if variance >> mean?
- Revenue per user is heavy-tailed. How does that change A/B test analysis?
- When does the Central Limit Theorem fail to justify normal confidence intervals?
- What distribution would you use as a prior for A/B test conversion rates? Why?
- What is KL divergence? How is it used in VAEs and model monitoring?
- Walk me through what a p-value means. What is it NOT? Give me the most common misinterpretation
- Your experiment shows 8 of 10 tested metrics are significant at p < 0.05. Your manager wants to ship. What do you do?
- A junior DS reports p=0.049 for the primary metric and wants to ship. You find they ran the analysis twice, once at day 7 and once at day 14. How do you respond?
- When should you use a one-tailed test? A PM says they only care about improvement, so they want one-tailed for more power
- Explain the Central Limit Theorem. Why does it justify z-tests on non-normal data, and when does it fail?
- What is the difference between a Bayesian credible interval and a frequentist confidence interval? When would you use each?
- Why is "unit of randomization must match unit of analysis" critical in A/B testing? Give an example where this breaks
- Design a memory system for a long-lived customer support agent. What memory types do you use and how do you handle stale preferences?
- What is the lost-in-the-middle problem? How does it affect how you structure prompts for RAG systems?
- When would you fine-tune for procedural memory vs use RAG for semantic memory in an agent system?
- What does instruction tuning actually change in an LLM? Does it add knowledge or change behavior?
- You have 50,000 auto-generated instruction pairs and 1,000 expert-curated pairs. Which do you use and why? Cite Lima
- What is catastrophic forgetting during instruction tuning? How do you mitigate it without losing the instruction-following gains?
- How do you decide between instruction tuning and RAG for a given task? Walk through the decision framework
- Why must conversation templates match exactly between training and inference? What happens mechanically when they don't?
- Trace the evolution of embeddings from word2vec to instruction-tuned embeddings. What specific failure did each generation fix?
- Why is BERT's [CLS] token not a good sentence embedding? What did Sentence-BERT change?
- What is Matryoshka Representation Learning and why does it matter for production RAG cost optimization?
- Your team upgraded from text-embedding-ada-002 to text-embedding-3-small and retrieval quality dropped 30%. What went wrong?
- When should you use hybrid BM25+dense search instead of dense-only retrieval? What types of queries fail with dense embeddings alone?
- Your LLM extraction pipeline fails 4% of the time due to malformed JSON. Walk through your fix from naive retry to production architecture.
- Explain how grammar-constrained decoding works. Why does FSM token masking guarantee structural validity while OpenAI strict mode does not always provide the same guarantee?
- You need to extract structured data from 10M documents overnight. API rate limits are the binding constraint, not cost. What is your architecture?
- What is the difference between OpenAI strict structured outputs and self-hosted grammar-constrained decoding (Outlines)? When would you use each?
- How do you handle schema versioning in a production extraction pipeline? What happens when you update a Pydantic model without updating cached outputs?
- Explain the Instructor auto-retry pattern. Why does injecting the validation error message back into the conversation help the model self-correct?
- Explain BPE tokenization from first principles. How does tiktoken's byte-level BPE differ from character-level BPE?
- A model performs well on English arithmetic (247 + 583) but fails on larger numbers (14,728 + 39,452). Trace this failure to tokenization and explain the mitigation.
- You are building a multilingual embedding service for English, Korean, and Arabic documents. How does tokenizer choice affect retrieval quality and infrastructure cost?
- Why did GPT-4 double the vocabulary from 50K to 100K tokens? What are the tradeoffs between vocabulary size, embedding matrix memory, and sequence length?
- What are tokenization artifacts? Give three examples of model failures caused by tokenization, not model capacity.
- Your product manager asks you to add Chain-of-Thought to improve accuracy on a classification task. What do you say?
- How does prefix caching work, and how would you structure a multi-tenant production prompt system to maximize cache efficiency?
- What is prompt injection and why is it considered an unsolved problem? Compare direct injection, indirect injection, and production mitigations.
- You are building a production extraction pipeline. The model returns valid text but not always valid JSON. Walk through your diagnostic framework and fix.
- What are the three pitfalls of few-shot prompting that kill accuracy? How do you mitigate each?
- When does Chain-of-Thought prompting hurt performance rather than help? Give a concrete example.
- How do you decide between prompting and fine-tuning for a production task? Walk through the decision dimensions.
- How do you handle tool call failures in a production agent? Describe the three error classes and your retry strategy.
- Design the context management strategy for an agent working on a large codebase. How do you prevent lost-in-the-middle failures?
- When should you NOT use an agentic architecture, and what should you use instead?
- How do you design cost and runaway guardrails for a production agent? What metrics do you monitor?
- How do you decide whether to build a true agent or a deterministic workflow? Walk through the PEARL framework.
- What are the four non-negotiables for production agents? What happens when you skip any one of them?
- Why do single agents become unreliable beyond 8-step chains? Name the three compounding failure modes.
- Why should the orchestrator use a higher-capability model than the worker agents in a multi-agent system?
- How do you prevent oscillation loops in a multi-agent code review system (writer and reviewer going back and forth)?
- Why is a typed shared state object safer than letting agents message each other directly?
- When is multi-agent architecture warranted? Walk through the 5-question decision framework.
- Why does LangGraph beat LangChain Agents for production workflows? Name three specific advantages.
- What is the demo-to-production gap in multi-agent systems? Why do >80% of engineering hours go into reliability?
- When should you fine-tune vs use RAG vs just prompt? Walk through the 3-question decision framework.
- Explain LoRA's initialization trick (B=0). Why is this critical for stable training from a pre-trained checkpoint?
- Your team wants to fine-tune a 70B model on a single GPU. Walk through the QLoRA configuration and the three innovations that make this possible.
- What is DPO and why has it largely replaced RLHF+PPO for modern alignment? Explain the mathematical equivalence.
- You have 500 customer support examples. Walk through your fine-tuning pipeline from data prep to evaluation.
- What are the 5 fine-tuning failure modes? Which one is "fine-tuning to inject knowledge" and why does it fail?
- Why can CoT reduce quality on simple tasks? Give a concrete example of overthinking.
- Design a routing architecture that sends easy queries to a cheap path and hard queries to an expensive reasoning tier. What signals drive the router?
- What is CoT faithfulness and why is it not guaranteed? What should you evaluate instead of reasoning length?
- Self-consistency fails in three scenarios. Name them and explain the fix for each.
- Walk through a production architecture for 40+ internal tools without blowing context or reliability.
- Why must schema validation and authorization happen on the server even if the model "supports" function calling natively?
- What is MCP tool poisoning and how do you design around it? Explain the supply-chain dependency model.
- Distinguish JSON mode from strict structured outputs (tool calls with token masking). When do you use each?
- How do you test tool-calling in CI if outputs are non-deterministic?
- Explain HELM's multi-metric design. Why does MMLU alone never ship a product?
- What is training data contamination and how do you detect it (13-gram overlap, perplexity, post-cutoff held-out)?
- Your model upgrade improves MMLU by 3 points but regresses tool-call JSON compliance. Walk through your response.
- Design an LLM-as-judge protocol with debiasing controls. Name 4 bias types and their mitigations.
- What is the offline-to-online evaluation gap? Why do offline judge scores not predict production behavior?
- Calculate the KV cache memory for LLaMA-3 70B at 128K context in BF16. Why does this make inference memory-bound?
- Explain Flash Attention's tiling and online softmax. How does it reduce HBM accesses from O(n^2) to O(n)?
- A model upgrade changes the GQA ratio and tokenizer. What evaluator traps should you watch for?
- Connect GQA, MoE, RoPE scaling, and Flash Attention to specific production serving constraints (TTFT, TPS, memory, cost).
- An interviewer says "design an AI customer support assistant." Walk through everything you would do in the first 7 minutes: what you ask, what you say, what you don't do.
- Why don't we just fine-tune the model on our company docs instead of doing RAG? Wouldn't that be faster at inference time?
- You are 25 minutes into a GenAI design interview. You have designed retrieval and generation but haven't talked about evaluation, prompt injection defences, or cost. The interviewer hasn't pushed on these yet. What do you do?
- Walk through the technique escalation ladder (prompt -> few-shot -> RAG -> LoRA -> continued pretrain). What constraint moves you up each rung?
- Design a RAG system from scratch for legal document Q&A. Walk through chunking, embedding, index, retrieval, reranking, generation, and evaluation.
- Your naive RAG system retrieves chunks by cosine similarity but users complain about wrong answers. Diagnose the three classes of failure (vocabulary mismatch, semantic conflation, multi-hop questions) and propose fixes.
- When should you use hybrid BM25+dense retrieval instead of dense-only? What types of queries fail with dense embeddings alone?
- Explain Reciprocal Rank Fusion (RRF). Why does rank-based fusion outperform score-based fusion when combining BM25 and dense retrieval results?
- You are building a RAG system for a corpus that updates weekly with 10K new documents. Walk through the indexing pipeline, embedding model selection, and how you handle staleness.
- Compare chunking strategies: fixed-size vs semantic vs hierarchical. When does hierarchical chunking win and why?
- Design a two-stage reranking pipeline. Why retrieve top-50 with a fast bi-encoder then rerank to top-5 with a cross-encoder? What is the latency budget?
- What is HyDE (Hypothetical Document Embeddings)? When does it help and when does it hurt retrieval quality?
- Your team upgraded the embedding model from BGE-M3 to a newer model and retrieval quality dropped. What went wrong? Explain the embedding model lock-in problem.
- Walk through the RAGAS evaluation metrics: faithfulness, context precision, context recall, answer relevance. Which metric catches hallucination?
- When should you use agentic RAG (ReAct pattern with tool calls) vs simple single-shot RAG? What types of questions require multi-hop retrieval?
- Size a vLLM serving cluster for Llama-3-70B: derive weight memory, KV cache per request at 8K context, concurrent capacity on A100-80G, and estimate $/1M tokens.
- When should you NOT use an LLM for a problem? Name four categories where traditional approaches win.
- Compare hosted (GPT-4, Claude) vs self-hosted (Llama, Mistral) for an LLM application. What constraints drive the choice?
- Design multi-model routing (small model for easy queries, large model for hard ones). What is the classifier, what are the routing signals, and what cost savings do you expect?
- What is the 6-phase GenAI design playbook? How do you time-budget a 45-minute design interview?
- Explain PagedAttention. How does treating KV cache like virtual memory pages increase concurrent request capacity from ~5 to ~100?
- What is speculative decoding? When does it help ITL and when does it hurt?
- Your production RAG system has 95% recall@10 on your golden set but users report frequent hallucination. Where is the gap? Walk through context assembly, prompt engineering, and confidence thresholds.
- Compare long-context models (128K tokens) vs RAG vs hybrid for a document QA system. What is the decision matrix?
- Explain position-aware context assembly. Why does "lost in the middle" affect how you order retrieved chunks in the prompt?
- What are the top 5 RAG failure modes in production, ranked by frequency? What is the fix for each?

## Key Terminology

- **Overfitting/Underfitting** -- Model performs well on training data but poorly on unseen data (over) or poorly on both (under)
- **Gradient descent** -- Optimization algorithm that iteratively adjusts weights to minimize the loss function
- **Cross-validation** -- Technique using multiple train/test splits to estimate model generalization performance
- **Feature store** -- Centralized repository for storing, managing, and serving ML features
- **A/B testing** -- Controlled experiment comparing two model versions to measure performance impact
- **Embeddings** -- Dense vector representations that capture semantic relationships between items
- **Confusion matrix** -- Table showing true/false positives and negatives for classification evaluation
- **Drift detection** -- Monitoring for changes in data distribution or model performance over time
- **Two-Tower model** -- Dual-encoder architecture that separately embeds users and items into a shared space for efficient ANN retrieval
- **NDCG** -- Normalized Discounted Cumulative Gain; ranking quality metric that discounts relevance by log of position
- **Cold-start** -- Challenge of making recommendations for new users or items with no interaction history
- **Hard negatives** -- Items similar to positives but not engaged by the user; critical for fine-grained discrimination in retrieval training
- **Multi-task ranking** -- Single model predicting multiple engagement signals (click, watch-time, satisfaction) with task-specific heads
- **PR-AUC** -- Area under the Precision-Recall curve; more informative than ROC-AUC when positive class is less than 10% of data
- **MCC** -- Matthews Correlation Coefficient; best single metric for binary classification with any class balance, uses all four confusion-matrix cells
- **F-beta Score** -- Generalized F1 where beta>1 weights recall more (medical), beta<1 weights precision more (spam); F1 is beta=1
- **Calibration** -- Property where predicted probabilities match empirical frequencies; P=0.70 means ~70% actually positive. Audited via reliability diagrams, ECE, Brier score
- **ECE** -- Expected Calibration Error; weighted average gap between predicted confidence and actual accuracy across bins. Below 0.05 is well-calibrated
- **Platt Scaling** -- Fits logistic regression on model scores to calibrate probabilities; simple and effective for SVMs and uncalibrated scores
- **Temperature Scaling** -- Divides neural network logits by scalar T before softmax; T>1 softens probabilities (overconfident), single parameter, standard for deep learning calibration
- **MRR** -- Mean Reciprocal Rank; measures where the first relevant result appears across queries (1/rank). Best for single-answer QA and site search
- **MAP** -- Mean Average Precision; computes precision at each relevant result position and averages. Good for multi-relevant document retrieval with binary relevance
- **Threshold Selection** -- Picking the operating point on the PR or ROC curve; methods include expected-value maximization, F-score maximization, Youden's J, and precision/recall constraints
- **Huber Loss** -- Loss that is quadratic for small residuals and linear for large ones; robust to outliers while still penalizing moderate errors. Delta is a hyperparameter
- **Pinball Loss** -- Loss for quantile regression; enables prediction intervals. tau=0.9 predicts the 90th percentile of the target distribution
- **CART** -- Classification and Regression Trees (Breiman 1984); greedy, top-down, recursive binary splitter that tries every feature-threshold combination at each node and picks the best impurity reduction
- **Gini impurity** -- 1 - sum(p_k^2); default CART split criterion for classification, ~10% faster than entropy (no log call), agrees on >98% of splits (Raileanu & Stoffel 2004)
- **Entropy / Information Gain** -- -sum(p log p); split criterion used by ID3/C4.5, rarely worth the cost over Gini in practice
- **Cost-complexity pruning** -- Post-pruning method (Breiman 1984) that scores subtrees as R_alpha(T) = R(T) + alpha * |T|; alpha selected via k-fold CV, typically using the 1-SE rule for robustness
- **Surrogate split** -- Backup split at each node that mimics the primary split's routing, used when the primary feature is missing at inference; implemented in R's rpart but NOT in sklearn
- **MDI (Mean Decrease in Impurity)** -- Default feature importance in sklearn; statistically biased toward high-cardinality features (Strobl 2007); use permutation importance or TreeSHAP instead
- **TreeSHAP** -- Exact Shapley value computation for tree models in polynomial time (Lundberg 2020); gold standard for tree-based model explanations, satisfies efficiency/symmetry/dummy axioms
- **Oblivious tree** -- Symmetric tree where every node at level d uses the same (feature, threshold); enables branchless SIMD inference (~100x throughput); used by CatBoost
- **Fisher's partition trick** -- Sorting k categories by target mean reduces the optimal binary partition search from 2^(k-1)-1 to k-1 candidates (Fisher 1958); exploited by LightGBM/CatBoost for native categorical handling
- **Pre-pruning vs post-pruning** -- Pre-pruning stops growth early (max_depth, min_samples_leaf); post-pruning grows full tree then collapses weak subtrees; pre-pruning is myopic (can miss XOR-like interactions)
- **OLS (Ordinary Least Squares)** -- Estimator that minimizes sum of squared residuals; closed form via normal equation beta_hat = (X^T X)^(-1) X^T y; also the MLE under Gaussian noise. Two derivations, same answer
- **Gauss-Markov Theorem** -- Under Linearity, Independence, Normal mean (not distribution), and Equal variance (LINE), OLS is BLUE (Best Linear Unbiased Estimator): minimum variance among all linear unbiased estimators. Does NOT require Gaussian errors
- **Normal Equation** -- X^T X beta = X^T y; the first-order condition for OLS. Geometrically, X*beta_hat is the orthogonal projection of y onto the column space of X. Condition number of X^T X is cond(X)^2, so numerically unstable for multicollinear features
- **QR Decomposition for OLS** -- Factor X = QR, solve R*beta = Q^T y; avoids forming X^T X (which squares the condition number). What sklearn and R use internally for numerical stability
- **IRLS (Iteratively Reweighted Least Squares)** -- Newton-Raphson on log-loss rewritten as weighted OLS; each iteration fits beta = (X^T W X)^(-1) X^T W z where W = diag(p(1-p)) and z is the working response. Canonical GLM fitting algorithm; quadratic convergence in 5-10 iterations
- **Log-Odds (Logit)** -- log(p / (1-p)) = x^T beta; the linear predictor in logistic regression. A one-unit increase in x_j multiplies the odds by e^(beta_j); this odds ratio is why logistic regression is used in regulated domains
- **Log-Loss / Binary Cross-Entropy** -- -sum[y log p + (1-y) log(1-p)]; the negative log-likelihood under Bernoulli model. Not a design choice but the unique correct loss for binary outcomes from MLE. Provably convex with sigmoid; MSE-with-sigmoid is not
- **Perfect Separation** -- When a feature perfectly splits positives from negatives, the logistic MLE diverges to infinity (coefficients grow without bound). Fix: always add at least small L2 regularization (lambda=1e-4) to make the objective strictly convex
- **Ridge (L2) Regularization** -- Adds lambda * sum(beta_j^2); closed form beta = (X^T X + lambda*I)^(-1) X^T y. Shrinks all coefficients proportionally toward zero but rarely reaches exactly zero. Distributes weight across correlated features
- **Lasso (L1) Regularization** -- Adds lambda * sum(|beta_j|); no closed form (coordinate descent / proximal gradient). Produces exact zeros because the L1 constraint diamond has corners on the coordinate axes where loss contours naturally rest
- **ElasticNet** -- Combines L1 + L2: lambda_1 * sum(|beta_j|) + lambda_2 * sum(beta_j^2). Solves Lasso's pathology of arbitrarily dropping correlated features by grouping them (Zou & Hastie 2005)
- **VIF (Variance Inflation Factor)** -- VIF_j = 1 / (1 - R^2_j) where R^2_j comes from regressing feature j on all others. Above 10 signals multicollinearity; coefficients unstable because model cannot distinguish correlated features' effects
- **Cook's Distance** -- Measures how much beta_hat would change if data point i were dropped. D_i > 4/n flags influential outliers that reshape the fit; investigate the data story, do not blindly delete
- **FTRL-Proximal** -- Follow-The-Regularized-Leader with L1 proximal (McMahan 2013). Per-coordinate cumulative gradient z_i and learning rate n_i; hard threshold |z_i| <= lambda_1 sets w_i = 0 exactly. Produces genuine sparsity at Google Ads scale (billions of features, 99%+ zero weights), unlike SGD+L1 which leaves weights oscillating near zero
- **GLM (Generalized Linear Model)** -- Unifies linear/logistic/Poisson regression: (1) exponential family response distribution, (2) linear predictor eta = x^T beta, (3) link function g(E[y]) = eta. All fit via IRLS; canonical links (identity for Gaussian, logit for Bernoulli, log for Poisson) make sufficient statistic X^T y the natural conjugate
- **Softmax (Multinomial Logistic)** -- Generalizes logistic regression to K classes: P(y=k|x) = exp(x^T beta_k) / sum_j exp(x^T beta_j). Same gradient structure as binary logistic: (prediction - truth) * input. For extreme K, use hierarchical softmax or negative sampling (as in word2vec)
- **Weight sharing (CNN)** -- A single filter (e.g., 3x3 = 27 params) is applied across all spatial positions; drastically reduces parameters vs dense connections and enables translation equivariance
- **Receptive field** -- The spatial extent of input that influences a single output neuron. Grows with depth: 3x3 after 1 layer, 5x5 after 2, 21x21 after 10 layers of 3x3 convolutions
- **1x1 convolution** -- Channel-only projection without spatial mixing; C_in x C_out params per position. Used in ResNet bottleneck blocks, MobileNet depthwise separable convs, and dimension changes
- **Global Average Pooling (GAP)** -- Averages each feature map to a single scalar, replacing the fully connected classifier. Cheaper, more regularized, and generalizes better than a dense head
- **ResNet skip connection** -- Output of a block is F(x) + x, where F(x) is the residual. Provides gradient highway (derivative includes constant 1), makes identity the easy default, and creates an implicit ensemble of 2^N paths (Veit et al., 2016)
- **Degradation problem** -- Before ResNet, deeper networks trained worse than shallower ones even on training data; not overfitting but failure to learn identity through long layer chains
- **ResNet bottleneck block** -- 1x1 conv (reduce: 256->64), 3x3 conv (64->64), 1x1 conv (expand: 64->256). Costs 4x fewer FLOPs than plain 3x3+3x3 block
- **Vision Transformer (ViT)** -- Splits image into patches, applies global self-attention from layer 1. No inductive biases (no locality, weight sharing, or hierarchy); must learn everything from data. Outperforms CNNs only with 10M+ images or strong pretraining (ImageNet-21K, JFT-300M)
- **Swin Transformer** -- Local window attention with shifted windows for cross-window connectivity. O(N) vs ViT's O(N^2), produces hierarchical multi-scale features compatible with FPN detection heads
- **mAP@50** -- Mean Average Precision at IoU threshold 0.5; standard metric for object detection. YOLOv8-x achieves 53.9 on COCO vs Faster R-CNN ResNet-50 FPN at 37.0
- **NMS (Non-Maximum Suppression)** -- Post-processing for object detection that keeps highest-confidence box and removes overlapping boxes above IoU threshold (typically 0.5). Sequential and hard to parallelize; latency bottleneck at 100+ detections/frame
- **Linear probe** -- Transfer learning baseline: freeze backbone, train only classification head. Fast (minutes), establishes performance floor. Most engineers skip this and waste time on unnecessary fine-tuning
- **DINOv2** -- Meta's self-supervised ViT (2023) trained on 142M images. Features transfer better than supervised ImageNet features for most downstream tasks, especially in low-data regimes
- **BPE (Byte-Pair Encoding)** -- Bottom-up subword tokenizer that starts with characters and iteratively merges the most frequent adjacent pair; used by GPT-2/3/4, LLaMA, RoBERTa. Vocab 30K-100K
- **WordPiece** -- Subword tokenizer that merges based on maximum corpus likelihood (not just frequency); continuation tokens prefixed with ## (e.g., ##ing, ##tion). Used by BERT, DistilBERT. Vocab ~30K
- **SentencePiece / Unigram LM** -- Language-agnostic tokenizer that trains a unigram language model and prunes vocabulary to maximize total likelihood; no space-tokenization assumption. Used by T5, ALBERT, mBART, LLaMA-2
- **Byte-level BPE** -- BPE applied on raw bytes instead of characters; zero OOV since any byte sequence is valid. Used by GPT-2 via tiktoken. Vocab ~50K-100K
- **Tiktoken** -- Fast byte-level BPE tokenizer used by GPT-3.5/4 and Claude API; production standard for OpenAI-compatible systems
- **Static embeddings** -- Each word gets one fixed vector regardless of context (Word2Vec, GloVe, FastText); fails for polysemy. Word2Vec skip-gram predicts surrounding words; GloVe factorizes co-occurrence matrices. Dim 100-300d
- **Contextual embeddings** -- Each token gets a different embedding depending on context; BERT/GPT produce these. Eliminates polysemy problem: "bank" in finance vs geography contexts get different vectors
- **SBERT (Sentence-BERT)** -- Fine-tunes BERT with siamese networks for semantic similarity; produces fixed-size sentence vectors. all-MiniLM-L6-v2 (22M params, 384d) runs ~14K sentences/sec on V100
- **MLM (Masked Language Modeling)** -- BERT pre-training task: mask 15% of tokens (80% [MASK], 10% random token, 10% unchanged), predict originals. Forces bidirectional context understanding
- **CLM (Causal Language Modeling)** -- GPT pre-training task: predict next token given all previous tokens P(x_t | x_1, ..., x_{t-1}). Autoregressive, naturally enables generation
- **NSP (Next Sentence Prediction)** -- BERT's second pre-training task: predict if sentence B follows A. RoBERTa (2019) showed it doesn't help and removed it
- **T5 span corruption** -- Mask contiguous spans (avg 3 tokens, 15% total); decoder predicts masked spans. Better than token-level MLM for seq2seq tasks
- **LoRA (Low-Rank Adaptation)** -- Adds low-rank matrices BA to attention weights: W' = W + BA, rank r << d. Trains ~0.3% of params for BERT-base (r=8). Standard for LLM fine-tuning. r=8 to r=64 covers most tasks
- **QLoRA** -- Quantizes frozen base model to 4-bit (NF4), applies LoRA in 16-bit. Fine-tunes LLaMA-7B on 1x 24GB GPU, LLaMA-70B on 1x 48GB GPU. Key innovations: double quantization, NF4 data type
- **Prompt/prefix tuning** -- Adds trainable soft prefix tokens to input/key/value; model weights frozen. Fewer params than LoRA; allows hot-swapping tasks with single model instance
- **Double Descent** -- Phenomenon (Belkin et al. 2019) where test error first increases at the interpolation threshold then decreases again as model size grows further. Explains why massively over-parameterized models (GPT-4, LLaMA 3) generalize well despite zero training error
- **Learning Curves** -- Plots of training and validation error vs training set size; the most reliable diagnostic for bias vs variance. High variance = curves haven't converged (more data helps). High bias = both plateau high (more data won't help, increase model capacity)
- **Training-Serving Skew** -- When features are computed differently at training vs inference time (e.g., full-history aggregates at training vs 30-day windows at serving). The #1 production bug in tabular ML. Causes silent model degradation with no error logs
- **PSI (Population Stability Index)** -- Measures distribution shift per feature between training and production. Above 0.25 indicates significant drift requiring investigation and possible retraining
- **Inverted Dropout** -- Divides surviving neuron outputs by (1-p) during training so expected activation magnitude matches inference. Without this, activations at inference would be 1/(1-p)x larger, causing distribution shift
- **AdamW** -- Adam with decoupled weight decay (Loshchilov & Hutter 2017). Applies decay directly to weights after Adam step, not as gradient penalty. Standard for transformer training because regularization strength is uniform regardless of gradient history
- **Early Stopping** -- Halts training at the minimum validation loss; equivalent to L2 regularization for quadratic loss (Bishop 1995). Should always be the first regularizer applied (free, no extra hyperparameters)
- **MC Dropout** -- Monte Carlo Dropout: sample K forward passes with dropout active at inference, average outputs, use variance as uncertainty signal. Improves calibration for out-of-distribution inputs
- **Batch Normalization (inference)** -- Uses running statistics (exponential moving average from training) at inference, not per-batch statistics. Fails with batch size 1 at serving time. Always verify model.eval() switches BN correctly
- **Focal Loss** -- Loss that down-weights easy (well-classified) examples and focuses gradient on hard negatives; gamma parameter controls focusing strength. Used in object detection (RetinaNet) and imbalanced classification as alternative to class weights
- **SMOTE** -- Synthetic Minority Over-sampling Technique: interpolates between minority class samples to generate synthetic examples. Often hurts on tabular + gradient boosting (Elor & Averbuch-Elor 2022); creates synthetic samples in feature space that don't correspond to real data manifold
- **Pozzolo Correction** -- Calibration correction after undersampling: p_s = p / (p + (1-p)/beta), where beta is the undersampling ratio. Required when downstream decisions need calibrated probabilities and you've resampled the training data
- **scale_pos_weight** -- XGBoost/LightGBM parameter that scales the loss for positive examples; equivalent to class weight = n_neg / n_pos. Quick fix for mild imbalance but doesn't fix severe imbalance or asymmetric costs
- **Target Encoding** -- Replaces categorical values with the mean target for that category. Must use K-fold CV to avoid leakage; without it, training AUC jumps 5-10 points vs production. Smooth with (n*y_bar_k + alpha*y_bar) / (n + alpha), alpha ~ 10-100
- **Feature Hashing** -- Maps categories to a fixed-size vector via hash function (e.g., 2^18 buckets). Handles unbounded cardinality (URLs, user IDs) without exploding dimensionality. Collision-tolerant for linear models; less suitable for trees
- **Cyclical Encoding** -- Encodes cyclical features (hour, day-of-week, month) as sin/cos pairs to capture periodicity. One-hot or ordinal encoding incorrectly treats hour 23 and hour 0 as maximally distant
- **MCAR / MAR / MNAR** -- Missing Completely At Random (safe to drop/impute), Missing At Random (missingness depends on observed features, imputation safe), Missing Not At Random (missingness depends on unobserved value, imputation biased). Rubin 1976 taxonomy
- **MICE** -- Multiple Imputation by Chained Equations; iteratively imputes each feature using all others as predictors. Gold standard for MAR data. Produces multiple imputed datasets to capture imputation uncertainty
- **Permutation Importance** -- Measures feature importance by permuting a feature and observing degradation in validation metric. Unbiased unlike MDI (Strobl 2007); costs one model evaluation per feature but is the production standard
- **Point-in-Time Join** -- Joins features to labels using the state of the world strictly before the label timestamp. Prevents temporal leakage; implemented via feature stores with event-time semantics
- **DRIFT Checklist** -- Define, Reason, Identify failure, Fix, Test: structured approach for regularization decisions. Ensures you state the regularizer, explain its mechanism, identify failure modes, apply fixes, and validate with proper diagnostics
- **ML Interview Signals** -- Five signals graded in FAANG ML rounds: (1) mathematical fluency under pressure, (2) algorithmic intuition (why, not just what), (3) practical experience (specific numbers and named techniques), (4) failure-mode awareness, (5) honest uncertainty. Senior candidates lose on signal 3; staff+ win on signals 2 and 5
- **Log-Cosh Loss** -- log(cosh(error)); approximation of Huber loss that is smooth everywhere (no delta hyperparameter). Good default regression loss when you want Huber-like robustness without tuning delta
- **InfoNCE / NT-Xent** -- Contrastive loss used by SimCLR, CLIP, two-tower retrieval: -log[exp(sim(q,k+)/tau) / sum_i exp(sim(q,k_i)/tau)]. Temperature tau typically 0.07-0.1. In-batch negatives give N*(N-1) free negatives per batch
- **Triplet Loss** -- max(0, d(anchor, positive) - d(anchor, negative) + margin); margin typically 0.3. Fails with trivial triplets (easy negatives already far); requires hard negative mining (semi-hard negatives close to anchor)
- **Label Smoothing** -- Replaces hard 0/1 labels with (epsilon/K, 1-epsilon+epsilon/K), typically epsilon=0.1. Prevents overconfidence, improves calibration, reduces sensitivity to noisy labels. Standard in BERT, T5, EfficientNet training
- **Focal Loss** -- -(1-p_t)^gamma * log(p_t); gamma=2 down-weights easy examples by factor 0.01 at p_t=0.9. Standard in RetinaNet, YOLO v5+, EfficientDet. Use for severe class imbalance where easy negatives dominate gradient
- **SGD with Momentum** -- v_t = beta*v_{t-1} + grad; theta_{t+1} = theta_t - lr*v_t. Beta=0.9 gives weighted average of last ~10 gradients. Production default for CNNs; converges to wider minima that generalize better
- **Adam** -- Per-parameter adaptive learning rate using first moment (m, beta1=0.9) and second moment (v, beta2=0.999) with bias correction. Default for transformers and LLMs. lr=3e-4 standard
- **Learning Rate Warmup** -- Ramp lr from small (lr/100) to target over 500-2000 steps. Critical for Adam: early second moment estimates are inaccurate, without warmup first updates can corrupt initialization
- **Cosine Decay** -- lr = lr_0/2 * (1 + cos(pi*t/T)); smooth schedule that is the standard default for transformer training. Linear warmup + cosine decay outperforms constant lr by 1-5%
- **Gradient Clipping** -- Caps gradient norm: if ||g|| > max_norm, scale g = g * max_norm/||g||. Preserves direction. Default max_norm=1.0 for transformers/LLMs. If clipping on >80% of steps, lr is too high
- **Mixed Precision (AMP)** -- Train with FP16/BF16 for 2x throughput on A100/H100. BF16 preferred: same exponent range as FP32, no loss scaling needed. Master weights stay FP32 for numerical stability
- **Gradient Accumulation** -- Accumulate gradients over multiple mini-batches before optimizer step to simulate larger batch size. Used in LLM fine-tuning where effective batch sizes of 512-2048 needed but only 8-32 fit in GPU memory
- **Linear Scaling Rule** -- When increasing batch size by k, increase learning rate by k. Works up to ~8x scaling; breaks down at very large batches (Keskar et al. 2017 sharp minima problem)
- **Collaborative Filtering** -- Recommend items liked by similar users (user-based) or items similar to user's history (item-based). Core assumption: interaction matrix is low-rank. Item-based scales better (items don't drift)
- **Matrix Factorization** -- R ~ U*V^T; decompose sparse user-item matrix into user and item latent factors. Netflix Prize winner. Replaced by two-tower DNNs in modern systems
- **Multi-Stage Recommendation Funnel** -- Retrieval (millions -> hundreds in <50ms) -> Ranking (hundreds -> tens in ~100ms) -> Re-ranking (business constraints). Retrieval quality is the ceiling: if the right item is not in top 500 candidates, no ranking model can recover it
- **Pointwise / Pairwise / Listwise Ranking** -- Pointwise: predict relevance score independently (regression). Pairwise: optimize relative order of pairs (LambdaMART). Listwise: optimize entire list order (ListNet, NDCG directly). Pairwise/listwise better for ranking quality
- **Negative Sampling** -- Sampling strategy for retrieval training. 1 positive : 4-8 negatives standard. Random negatives produce trivial triplets (zero gradient). Hard negatives (semi-hard: close but not too close) needed for fine-grained discrimination. Too many hard negatives -> instability
- **ANN (Approximate Nearest Neighbor)** -- FAISS, ScaNN, HNSW for fast retrieval from pre-computed item embeddings. <30ms for 10M+ items. Enables two-tower serving: compute user embedding online, ANN lookup for candidates
- **SRM (Sample Ratio Mismatch)** -- Chi-square test verifying actual control/treatment split matches intended split. If assigned 50/50 but got 48/52, randomization or logging is broken. Always check before analyzing results
- **CUPED** -- Controlled-Experiment Using Pre-Experiment Data (Deng et al. 2013). Y_cuped = Y_post - theta*(X_pre - E[X_pre]). Uses pre-experiment behavior to reduce variance by 20-50%, cutting experiment duration. Requires pre-period measurements of same metric
- **Novelty Effect** -- Metrics spike when users encounter a new feature then decay over 1-2 weeks as users habituate. Fix: run experiments minimum 2 weeks; analyze week 2 separately from week 1
- **Peeking / Optional Stopping** -- Re-running tests daily and stopping when p first crosses threshold. Inflates nominal alpha=0.05 to effective error rate of 0.2-0.3. Fix: pre-commit to sample size and duration; or use sequential testing with alpha-spending
- **Bonferroni Correction** -- Adjust alpha for multiple comparisons: alpha_adjusted = alpha/k. Conservative but simple. Benjamini-Hochberg FDR is less conservative alternative
- **Quasi-Experiments** -- When randomization is impossible: Difference-in-Differences (parallel pre-trends), Regression Discontinuity (threshold-based assignment), Synthetic Control (weighted untreated units match pre-intervention trend)
- **XGBoost Regularized Objective** -- Obj(t) = sum_i L(y_i, y_hat + f_t(x_i)) + gamma*T + 0.5*lambda*sum(w_j^2). gamma penalizes number of leaves (minimum gain per split), lambda does L2 on leaf weights
- **Second-Order Taylor Expansion** -- XGBoost approximates L(y, y_hat+f) ~ L(y, y_hat) + g*f + 0.5*h*f^2 where g=gradient, h=Hessian. Second-order captures curvature: a point with small gradient may still move a lot if curvature is large
- **Optimal Leaf Weight** -- w*_j = -G_j / (H_j + lambda) where G_j = sum of gradients in leaf, H_j = sum of Hessians. As lambda -> infinity, weights -> 0 (heavy regularization). For MSE: h=2 (constant), for log-loss: h=p(1-p) (uncertainty-weighted)
- **Split Gain Formula** -- Gain = 0.5*[G_L^2/(H_L+lambda) + G_R^2/(H_R+lambda) - (G_L+G_R)^2/(H_L+H_R+lambda)] - gamma. Only split if Gain > 0. gamma is the pre-pruning threshold
- **Histogram Approximation** -- Bucket feature values into 256 bins, aggregate gradient/Hessian sums per bin. O(n*b) instead of O(n*log n) for exact greedy. 3-5x faster with nearly identical quality. Always use for n > 50K
- **Sparsity-Aware Splits** -- XGBoost natively handles NaN by trying both left and right directions for missing values at each split, picking the direction with higher gain. Learned default direction stored for inference. Never impute NaN before XGBoost
- **Level-wise vs Leaf-wise Growth** -- XGBoost grows level-wise (balanced depth), LightGBM grows leaf-wise (splits the leaf with highest loss reduction). Leaf-wise is faster and often more accurate but overfits more on small datasets
- **XGBoost Feature Importance Types** -- weight (split count, biased toward high-cardinality), gain (average split improvement, better proxy), cover (average samples per split), SHAP (gold standard, satisfies efficiency/symmetry/dummy axioms)
- **XGBoost Hyperparameter Tuning Order** -- (1) Fix lr=0.1, find best n_estimators with early stopping, (2) tune max_depth + min_child_weight jointly, (3) tune subsample + colsample_bytree, (4) tune reg_lambda + reg_alpha, (5) halve lr and double n_estimators for final model
- **Universal Approximation Theorem** -- A feedforward network with one hidden layer and any non-linear activation can approximate any continuous function on a compact domain to arbitrary accuracy (Cybenko 1989, Hornik 1991). Explains expressiveness, not trainability
- **Forward Pass** -- Data flow through a neural network: composition of affine transformations (Wx + b) interleaved with non-linear activations. Without non-linearities, any depth of linear layers collapses to a single linear transformation
- **Backpropagation** -- Application of the chain rule to compute dL/dW for every weight. Gradients flow backward through the computational graph, each step multiplying by the local Jacobian. Key equations: dL/dW = delta * x^T, dL/dx = W^T * delta
- **Softmax + Cross-Entropy Gradient** -- For softmax output p_hat with cross-entropy loss, the gradient simplifies to dL/dz = p_hat - y (predicted minus true label). This elegant simplification is why softmax + CE is the standard for multi-class classification
- **Dying ReLU** -- Neurons with consistently negative inputs get gradient = 0 forever (ReLU'(x<0) = 0). They stop learning entirely. Fix: Leaky ReLU (small slope for x<0) or proper He initialization
- **GELU (Gaussian Error Linear Unit)** -- x * Phi(x) ~ x * sigmoid(1.702x); smooth approximation of ReLU. Empirically best for transformers/NLP. Used by BERT, GPT, and most modern LLMs
- **SiLU/Swish** -- x * sigma(x); non-monotonic activation. Used by Llama and modern neural nets. Often better than ReLU for large models
- **He Initialization** -- W ~ N(0, 2/n_in) for ReLU-family activations. Factor 2 compensates for ~50% of neurons that ReLU deactivates. Standard for any network with ReLU, Leaky ReLU, GELU, Swish
- **Xavier/Glorot Initialization** -- W ~ N(0, 2/(n_in + n_out)) for sigmoid/tanh. Maintains equal variance of activations and gradients across layers. Not suitable for ReLU
- **Layer Normalization** -- Normalizes across features per sample (not batch). Used in transformers; works with batch=1. y = gamma * (x - mu_layer) / sigma_layer + beta
- **RMSNorm** -- Simplified LayerNorm: only normalizes scale without mean centering. x / rms(x) * gamma. 7% faster, empirically equivalent quality. Used by Llama 1/2/3, Mistral, Gemma
- **BPTT (Backpropagation Through Time)** -- Training algorithm for RNNs: unroll the recurrence over T timesteps, treat as a deep feedforward network with T layers, apply standard backprop. Memory cost O(T * d). Truncated BPTT limits to last k steps (typical k=35)
- **Vanishing Gradients (RNN)** -- BPTT gradient w.r.t. early hidden state h_k is product of T-k Jacobians: prod_{t=k+1}^T (W_h^T * diag(tanh'(z_t))). If spectral radius of W_h < 1, decays exponentially. Sigmoid makes it worse (max grad 0.25)
- **LSTM Cell State** -- Additive update c_t = f_t * c_{t-1} + i_t * g_t gives dc_t/dc_{t-1} = f_t (element-wise, not matrix product). When forget gate f_t ~ 1, gradients flow unchanged. This is the Constant Error Carousel (Hochreiter & Schmidhuber 1997)
- **LSTM Forget Gate Bias** -- Initialize forget-gate bias to +1 or +2 so f_t ~ 1 at init, preserving memory by default (Jozefowicz et al. 2015). Critical practical detail that many implementations miss
- **GRU (Gated Recurrent Unit)** -- Simpler alternative to LSTM with ~25% fewer parameters (3 weight matrices vs 4). Merges cell state and hidden state; combines forget and input gates into one update gate. Start with GRU for small models (<10M params)
- **Teacher Forcing** -- Training technique for seq2seq: feed ground-truth previous token to decoder instead of model's own prediction. Causes exposure bias: model degrades during free-running generation. Fix: scheduled sampling (Bengio 2015)
- **Bahdanau Attention** -- Cross-attention from decoder to encoder hidden states in seq2seq (2014). Instead of a single fixed context vector, produces dynamic context c_t = sum_s alpha_{t,s} * h_s^enc. Direct ancestor of transformer self-attention
- **State-Space Models (SSM)** -- Modern RNN-shaped architectures (Mamba 2023, RWKV, RetNet) with recurrent state update for linear-time inference. Mamba's selective SSM is structurally an RNN with data-dependent transition matrix. Win over transformers for streaming workloads and sequences >100K tokens
- **Scaled Dot-Product Attention** -- Attention(Q,K,V) = softmax(QK^T / sqrt(d_k)) * V. The sqrt(d_k) scaling prevents dot products from growing with dimension, which would push softmax into saturation and kill gradients. Without it, models fail to train
- **Multi-Head Attention** -- Split Q,K,V into h heads, attend independently, concatenate and project. Each head can learn different attention patterns (syntax, semantics, coreference). 4 * d_model^2 parameters per layer (WQ, WK, WV, WO)
- **RoPE (Rotary Positional Encoding)** -- Rotates Q,K vectors by angle proportional to position. Inner product depends only on relative distance m-n, not absolute position. Generalizes to longer sequences. Used by Llama 2/3, Mistral, Falcon, PaLM 2
- **ALiBi (Attention with Linear Biases)** -- Adds linear bias to attention scores: score(i,j) -= alpha * |i-j| with head-specific alpha. Zero extra parameters, excellent extrapolation to longer sequences. Used by MPT, BLOOM
- **GQA (Grouped Query Attention)** -- Shares KV heads across Q heads: n_kv_heads < n_heads. 8x smaller KV cache with near-identical quality. Used by Llama 2/3 70B, Mistral, Gemma
- **SwiGLU FFN** -- Modern FFN replacing ReLU: (Linear_1 * SiLU(Linear_2)) -> Linear_3 (gated). Uses 8/3 * d_model hidden size for parameter parity. Empirically significantly better than ReLU FFN at scale. Used by PaLM, Llama 2/3, Gemma, Mistral
- **Pre-Norm vs Post-Norm** -- Post-Norm (original 2017): LayerNorm after residual addition. Pre-Norm (modern): LayerNorm before sublayer. Pre-Norm is more stable for very deep models, gradients flow more cleanly through residual path
- **Transformer Parameter Formula** -- Total params ~ 12L * d_model^2 (4 attention + 8 FFN per layer). For Llama 3 70B: 12 * 80 * 8192^2 = 64.4B (close to actual ~70B). FLOPs per forward pass ~ 2 * n_params * seq_len
- **Efron's Bootstrap (1979)** -- Plug-in method: treat the empirical distribution F_hat as a stand-in for the true F. Draw B samples of size n with replacement, compute statistic on each. Does NOT create new data; extracts all information about variability that n points can give
- **BCa (Bias-Corrected and Accelerated) CI** -- Production default bootstrap CI (Efron 1987). Adjusts percentile endpoints using bias z_0 and acceleration a via jackknife. Second-order accurate, transformation-invariant. What R's boot package uses
- **Permutation Test** -- Tests H0: exchangeability by shuffling group labels and recomputing the statistic. Exact (no asymptotics, no distributional assumptions, valid at any sample size). For hypothesis testing, prefer over bootstrap CIs which have wrong Type I error under H0
- **Block Bootstrap** -- For dependent/time-series data: resamples contiguous blocks of length l instead of individual observations, preserving local dependence. Moving block (Kunsch 1989), stationary bootstrap (Politis-Romano 1994) with random block lengths. Block length l ~ n^(1/3)
- **Jackknife** -- Leave-one-out resampling: compute statistic n times, each with one observation removed. O(n) cost vs O(B) for bootstrap. Produces bias estimator and BCa acceleration parameter. Fails for non-smooth statistics (median with even n)
- **Cluster Bootstrap** -- Resample at the cluster level (user, city) rather than row level when data has within-group correlation. Row-level bootstrap undercounts correlation and produces CIs that are systematically too narrow
- **.632+ Estimator** -- Efron 1997 improvement on out-of-bag error: combines training error and OOB error with data-dependent weights to de-bias. Theoretically preferred small-n alternative to cross-validation
- **Bernoulli Distribution** -- The atomic unit of classification: P(Y=1) = p, P(Y=0) = 1-p. Mean = p, variance = p(1-p). Logistic regression models P(Y=1|X) as a Bernoulli probability; BCE loss is the negative log-likelihood of this model
- **Poisson Distribution** -- Count data in a fixed interval. Defining property: mean = variance = lambda. If variance >> mean (overdispersion), Poisson is the wrong model; use Negative Binomial instead. Common for requests/sec, word counts
- **Log-Normal Distribution** -- If log(X) ~ Normal, then X is log-normal. Arises when a variable is the product of many small independent factors. Revenue per user, session duration, file sizes. Standard practice: log-transform before modeling, exponentiate predictions back
- **Exponential Distribution** -- Models time between events in a Poisson process. Memoryless: remaining wait time does not depend on how long you've already waited. Used for MTBF, inter-arrival times. Thin right tail makes it poor for user session duration (use Weibull instead)
- **Beta Distribution** -- Continuous distribution on [0,1] with parameters alpha, beta. Conjugate prior for Bernoulli/Binomial. Beta(1,1) = uniform. Maintains posterior over each arm's CTR in Thompson Sampling: update Beta(alpha + clicks, beta + non-clicks)
- **Dirichlet Distribution** -- Multivariate generalization of Beta on the simplex. Conjugate prior for Multinomial. Used in LDA topic models for topic distributions and class priors. Parameters alpha_1,...,alpha_K control concentration
- **Pareto Distribution** -- Heavy-tail distribution: P(X > x) = (x_min/x)^alpha. For alpha < 2, variance is infinite and CLT does not apply. The 80/20 rule is Pareto(alpha ~ 1.16). Wealth distributions, social media virality, earthquake magnitudes
- **KL Divergence** -- KL(P||Q) = sum P(x) log(P(x)/Q(x)). Measures information lost when approximating P with Q. Not symmetric. Used in VAEs (KL term penalizes encoder deviation from prior), model monitoring (distributional drift), and knowledge distillation
- **Overdispersion** -- When variance >> mean for count data, violating Poisson assumption. Dispersion ratio = Var/Mean > 1.5 suggests using Negative Binomial instead of Poisson. Common for social platform data (follower counts, bookings per listing)
- **MLE (Maximum Likelihood Estimation)** -- Framework: choose parameters theta that maximize P(data | theta). Every loss function is an MLE under some distribution: MSE = MLE under Gaussian, BCE = MLE under Bernoulli, Poisson deviance = MLE under Poisson. Wrong distribution = wrong optimization problem
- **Null Hypothesis (H0)** -- The default assumption of no effect, no difference, no relationship. You never "prove" H0 true; you either reject it or fail to reject it. "Fail to reject H0" is not the same as "H0 is true"
- **p-value** -- P(data this extreme or more | H0 is true). NOT the probability that H0 is true, NOT the probability the result is due to chance, NOT 1 minus P(H1 is true). With large n, even trivially small effects become "significant"
- **Type I Error (alpha)** -- False positive: rejecting H0 when it is actually true. Controlled by your pre-specified alpha (typically 0.05). At alpha=0.05, 1 in 20 null experiments will produce a false significant result
- **Type II Error (beta)** -- False negative: failing to reject H0 when H1 is true. Statistical power = 1 - beta. Standard target is power = 0.80. Determined by n, metric variance, and true effect size
- **Cohen's d** -- Standardized effect size measure: difference in group means divided by pooled SD. Small=0.2, medium=0.5, large=0.8. With large n, even d=0.02 can be "significant" but practically worthless
- **Welch's t-test** -- Default test for comparing two independent group means; does not assume equal variance. Use for A/B tests on continuous metrics
- **Two-proportion z-test** -- Test for comparing two proportions (CTR, conversion rates). Requires n*p >= 5 in both groups. Standard for A/B tests on binary outcomes
- **Chi-square test** -- Tests whether observed categorical counts match expected distribution (goodness of fit) or whether two categorical variables are independent. Also used for SRM checks
- **Bonferroni Correction** -- Adjusts alpha for multiple comparisons: alpha_adj = alpha/k. Controls family-wise error rate (FWER). Conservative; assumes independent tests. Use when any false positive is costly
- **Benjamini-Hochberg FDR** -- Controls expected fraction of rejected nulls that are false positives. Procedure: sort p-values, find largest k where p_k <= (k/m)*q. Less conservative than Bonferroni; appropriate for exploratory multi-metric analysis
- **One-Tailed vs Two-Tailed Test** -- Two-tailed (default): splits alpha across both tails, detects effects in either direction. One-tailed: concentrates alpha in one direction; use ONLY when effect in opposite direction has identical business implications as no effect
- **Central Limit Theorem (CLT)** -- For i.i.d. random variables with finite mean and variance, the sample mean converges to Normal regardless of underlying distribution. Justifies z-tests/t-tests on non-normal data. Fails with infinite variance (Pareto alpha < 2) or heavy-tailed metrics (revenue, LTV)
- **Bayesian vs Frequentist** -- Frequentist: parameters are fixed unknowns, p-values measure data consistency with H0. Bayesian: parameters are random variables, posterior = prior x likelihood. Credible intervals have intuitive "95% probability parameter is in range" interpretation. Use frequentist for regulated Type I error control, Bayesian for expected loss and probability-of-superiority communication
- **In-Context Memory** -- Full conversation history prepended to prompt; 0ms retrieval, session-scoped. Breaks beyond ~8K tokens due to lost-in-the-middle effect. Rolling summarization (compress older turns, keep last 3 raw) is the most practical production technique
- **Lost-in-the-Middle Effect** -- LLMs show measurably lower accuracy when relevant information is in the middle of long context vs beginning/end (Liu et al., 2023). Put system prompt at beginning, retrieved memories at end, older summary in middle
- **Rolling Summarization** -- Compress older conversation turns into a summary, keep last 3-5 raw turns verbatim. Reduces token count 5-10x while preserving semantic content. Critical nuance: keep recent raw turns alongside summary to avoid tonal discontinuities
- **Semantic Memory (Agent)** -- Vector DB storing past conversations and learned facts as embeddings (Pinecone, Qdrant, Chroma). Retrieved by cosine similarity at query time. Mem0 wraps extraction and retrieval with LLM-powered conflict detection
- **Episodic Memory (Agent)** -- Time-stamped event logs from Generative Agents paper (Park et al., 2023). Retrieval scored by weighted combination: alpha*recency + beta*relevance + gamma*importance. Surfaces relevant old events that pure recency would miss
- **Procedural Memory (Agent)** -- Knowledge internalized into model weights via fine-tuning. Use for stable skills (output format, code review criteria, persona) not fast-changing facts (prices, policies). Fine-tune for "how to behave", use RAG for "what is true"
- **Memory Write Gate** -- Persistence criteria: durability (will this fact still be true next session?), confidence (verified source vs inferred), reuse value (will storing reduce future cost?), required metadata (source, confidence, created_at, expires_at). Prevents noisy retrieval from append-only logging
- **Instruction Tuning** -- SFT on (instruction, response) pairs that transforms a base LLM from text completion engine into instruction-following assistant. Teaches format and behavior, not new facts. Lima (2023): "Almost all knowledge in LLMs comes from pretraining. Alignment is largely about surface formatting"
- **FLAN (Fine-tuned Language Net)** -- Wei et al., 2021. Demonstrated that fine-tuning on diverse tasks with natural language instruction templates produces zero-shot generalization to unseen tasks. Instruction template diversity (10 phrasings per task) was critical for generalization
- **Alpaca / Self-Instruct** -- Taori et al., 2023. Generated 52K instruction-following pairs from GPT-3.5 for ~$600. Transfers instruction-following capability at 300x lower cost than human annotation. Systematic limitation: inherits teacher model's hallucination patterns
- **Orca** -- Microsoft, 2023. Fine-tuned on GPT-4 explanation traces (step-by-step reasoning), not just final answers. Closed 40% of gap between Vicuna-13B and ChatGPT on AGIEval. Teacher signal quality (reasoning chains) was the key variable
- **Lima (Less Is More for Alignment)** -- Zhou et al., 2023. 1,000 curated expert examples matched ChatGPT-3.5 quality on 43% of evaluations. Quality and diversity dominate quantity: each example should train a different sub-skill
- **Catastrophic Forgetting** -- SFT degrades performance on pretraining skills underrepresented in instruction data. LLaMA-1 instruction-tuned showed 15-20% degradation on HumanEval (code). Mitigations: data mixing (~40% code in SFT), LoRA (5-8x less forgetting), low LR (1e-5), short training (1-3 epochs)
- **Conversation Template** -- Specific delimiter format delineating turns in instruction-tuned models (ChatML, Llama 2/3, Mistral). Must match exactly between training and inference. Mismatch causes mode collapse: model echoes prompt or continues in base completion mode. Always use tokenizer.apply_chat_template()
- **ChatML** -- OpenAI conversation template: `<|im_start|>system\n{system}<|im_end|>\n<|im_start|>user\n{user}<|im_end|>\n<|im_start|>assistant\n`
- **word2vec** -- 300d static embeddings via shallow neural network (skip-gram or CBOW). Negative sampling (15 random negatives per positive) made training practical. Encodes semantic relationships as vector offsets ("king - man + woman = queen"). Fails on polysemy and OOV words
- **Sentence-BERT (SBERT)** -- Siamese BERT fine-tuned on NLI and STS data. Reduces pairwise similarity computation from 65 hours to 5 seconds for 10K sentences. Achieves Spearman 0.869 vs BERT's 0.293 on STS-Benchmark. Enables large-scale semantic search
- **Instruction-Tuned Embeddings** -- Models (E5-instruct, text-embedding-3, GTE-Qwen2) that accept task-specific prompts for different use cases. Asymmetric treatment of query vs document ("Represent for retrieval: {query}") improves NDCG@10 by 8-15 points on out-of-domain retrieval
- **Matryoshka Representation Learning (MRL)** -- Trains single embedding model where any prefix of the vector is meaningful. First 256 dims encode most salient features; dims 257-3072 add finer detail. Enables two-stage retrieval: 256d for coarse recall, 3072d for reranking. 12x smaller index with ~95% of full-quality retrieval
- **Embedding Model Version Mismatch** -- Indexing with model A and querying with model B produces meaningless cosine similarities. Any model change requires full re-index. Track embedding model version as required metadata. Common production incident: env variable update without re-index
- **Hybrid Search (BM25 + Dense)** -- Dense embeddings excel at semantic neighborhoods but miss exact IDs, codes, SKUs, and rare terms. Hybrid combines BM25 for lexical precision with dense retrieval for semantic paraphrases, merges with Reciprocal Rank Fusion (RRF) or learned ranker. Required for production RAG at senior level
- **Grammar-Constrained Decoding** -- Inserts token masker between logit distribution and sampling in autoregressive loop. Schema compiled to FSM; at each decode step, only tokens keeping output syntactically valid are allowed; others set to -inf logit. Adds ~5-15ms per request. Guarantees structural validity (not semantic correctness). Implemented by Outlines, Guidance, llama.cpp GBNF
- **FSM Token Masking** -- Core mechanism of grammar-constrained decoding: JSON Schema compiled to deterministic finite automaton (states: START, OBJECT_OPEN, IN_KEY, etc.). At each step, FSM queries valid character set, maps to valid tokens, masks all others to probability zero. Structural validity is mathematically guaranteed
- **Outlines** -- Python library implementing grammar-constrained generation for JSON Schema, regex, and GBNF grammars on self-hosted models. Compiles schema to FSM once (~2ms for simple schemas), cached in memory. Works with vLLM, SGLang, llama.cpp
- **GBNF (GGML BNF)** -- Native grammar format for llama.cpp constrained generation. Defines context-free grammar for valid output structure. Alternative to JSON Schema compilation; more flexible for non-JSON structured outputs
- **Instructor Library** -- Pragmatic production wrapper (Jason Liu) for OpenAI/Anthropic APIs that adds Pydantic model as return type, automatic retry on ValidationError (injects error message back into conversation as corrective user turn), and configurable max_retries. Reduces observable failure rate from 3-5% to under 0.05% with 3 retries
- **Schema Versioning (Structured Outputs)** -- Production pattern: hash Pydantic model's JSON Schema output, embed hash as schema_version in system prompt, validate extracted outputs against the schema version they were generated under. CI must test the schema x prompt x model triple as a unit. Prevents silent pipeline failures when schemas change
- **RadixAttention (SGLang)** -- SGLang technique that shares KV cache for common prefix tokens across requests. For batch extraction with shared schema + system prompt, the ~500-token prefix KV cache computed once and shared across thousands of in-flight requests. Provides 3-5x throughput improvement for high-volume structured extraction
- **Streaming JSON / Incremental Parsing** -- For UX where users see results token by token: use ijson (event-driven SAX-style parser) to parse partial JSON streams. Combined with grammar-constrained decoding (every token is valid continuation), enables populating UI fields one by one as each key-value pair completes, cutting perceived latency from "wait for EOS" to "see first field in ~100ms"
- **Tokenization Artifacts** -- Production failures traced to tokenization, not model capacity. Examples: r-counting problem ("strawberry" tokenizes as ["straw","berry"], model cannot count characters it never individually processes); arithmetic inconsistency (small round numbers are single memorized tokens, large irregular numbers get split); string reversal failures (reversing a token ID has no meaning)
- **BPE Merge Order** -- Deterministic priority list of merges learned from training corpus; same string always produces same tokens. Merge order depends heavily on training data distribution: tokenizer trained on English-dominant data has fewer merges for Korean/Arabic, creating 2-4x more tokens per word for those languages. This is a direct artifact of corpus composition
- **Vocabulary Size Tradeoff (LLM)** -- Competing pressures: larger vocab = shorter sequences (better context utilization) but larger embedding matrix (100K x 4096 x 4 bytes = 1.6GB) and data sparsity for rare tokens. GPT-2: 50K (English adequate), GPT-4: 100K (multilingual efficiency). Rule of thumb: 32-50K for English-only, 100K+ for multilingual parity
- **Multilingual Token Inflation** -- Tokenizers trained on English-heavy data systematically over-tokenize other languages. Korean sentence taking 2x more tokens means: fewer unique training examples per context window, more attention capacity spent on subword combination vs semantic reasoning, documents truncated at half the semantic depth. Not fixable by fine-tuning; requires tokenizer retraining
- **Few-Shot Pitfalls** -- Three production traps: (1) label bias (imbalanced examples bias model toward majority class), (2) order sensitivity (last example before query has disproportionate influence; randomize order), (3) format contamination (examples in one format bias all outputs toward that format). Few-shot examples often override system prompts in instruction-tuned models
- **Self-Consistency (CoT)** -- Wang et al., 2022: sample same CoT prompt multiple times (temperature > 0), take majority vote across generated answers. Adds 3-7% accuracy on reasoning benchmarks at cost of Nx inference. Useful when accuracy matters more than latency
- **Prompt Injection** -- When malicious content in model input overrides developer instructions; the SQL injection of the LLM era with no complete solution. Direct injection (attacker sends malicious prompt), indirect injection (malicious instruction embedded in retrieved content). Mitigations are partial: constrained output format, privilege separation, treat all external data as untrusted, second-opinion checks
- **Prefix Caching** -- Reuses KV cache computation for shared static prompt prefix across requests. Anthropic: explicit cache_control parameter; OpenAI: automatic for prompts > 1024 tokens. A 4000-token system prompt costs ~$0.003/request without caching vs ~$0.0003 with cache hits (10x cost reduction). Static portion must be byte-for-byte identical; dynamic content goes after static prefix
- **ReAct Pattern** -- Reason+Act+Observe loop for AI agents. At each step: (1) LLM reasons about current state, (2) selects tool and provides structured JSON arguments, (3) tool executes and returns observation, (4) observation added to context, repeat until complete. Catches wrong assumptions early rather than executing stale plan to failure
- **Tool Error Contract** -- Production tool must return structured error: error_code (machine-readable), error_message (human-readable cause), recoverable (boolean), retry_after_sec (for transient). Three error classes: transient (retry with backoff), correctable (let model repair args), terminal (no retry, escalate). Raw "Error: file not found" leaves agent looping
- **Agent Loop Detection** -- Hash (tool, normalized_args) at each step. If same failing call repeats 3+ times, abort with diagnostic. Same-args repetition is the signature of a stuck agent. Cap retries at 3; longer cap risks runaway cost
- **Orchestrator-Worker Pattern** -- Production standard for multi-agent: one coordinator LLM decomposes task into DAG of sub-tasks, routes to specialist workers, synthesizes results. Orchestrator quality is the bottleneck (not workers). Orchestrator uses best model (GPT-4o, Claude Sonnet); workers can be cheaper (GPT-4o-mini, Haiku). Workers return structured outputs, are stateless
- **LangGraph** -- Production framework modeling agent workflows as explicit directed graphs with typed TypedDict state objects. Advantages over LangChain Agents: explicit state (inspectable), cycles for iterative loops (first-class pattern), built-in checkpointing (pause/resume workflows), streaming intermediate steps. Preferred for production workflows needing human-in-the-loop
- **AutoGen Debate Pattern** -- Microsoft Research framework for group chat between agents. Debate/critique pattern: one agent generates, second critiques, first revises. Improves reasoning-heavy tasks by ~15-20%. Limitation: every agent sees every message (quadratic context bloat). Use for debate/brainstorming; use LangGraph for pipeline/DAG workflows
- **Agent Evaluation Metrics** -- Task completion rate, turn efficiency (tool calls per task), tool error rate (% tool calls that fail), quality (human or LLM-as-judge rating). For multi-agent: also trajectory efficiency, handoff quality, tool policy adherence, worker isolation, human escalation correctness. SWE-bench standard benchmark (~50-60% state-of-art as of 2026)
- **PEARL Framework (Agents)** -- Decision framework for agent architecture: P=Problem (what needs dynamic action, what side effects, latency/cost envelope, human approval points), E=Engineering (chain vs ReAct vs plan-and-execute vs graph), A=Accuracy (task success + trajectory correctness), R=Reliability (bounded loops, tool auth, injection defenses), L=Latency/Cost (turns-to-completion, tool fan-out)
- **Map-Reduce Parallelization (Agents)** -- Simplest reliable multi-agent pattern: fan out to N workers processing independent pieces, reduce results with synthesizer. 10 workers processing 5 tickets each vs sequential 50: ~2.5s vs ~25s. Requires sub-tasks to be truly independent (no shared mutable state). Inconsistent worker results add synthesizer complexity
- **LoRA Initialization Trick** -- A is initialized with random Gaussian, B is initialized to zeros. At step 0, delta_W = BA = 0, so the model is mathematically identical to the pre-trained checkpoint. If B were non-zero at init, the first forward pass would produce garbage and loss would spike
- **LoRA Alpha/Scaling** -- delta_W is scaled by alpha/r before adding. Convention alpha = 2r (scale = 2). Treat alpha/r as a regularizer -- change the ratio, not alpha in isolation
- **LoRA Target Modules** -- Q and V projection matrices of attention (WQ, WV). Q/V determine what information gets attended to and mixed. Adding K, O, and FFN gains 1-3% quality at 4-6x parameter count. Start with Q,V for 80% of tasks
- **NF4 (4-bit NormalFloat)** -- Information-theoretically optimal quantization for normally distributed weights. Concentrates quantization buckets where transformer weights actually cluster (near zero, with gaussian tails). Roughly equivalent to 4.5-bit uniform quantization in practice
- **Double Quantization (QLoRA)** -- First quantization produces block-wise scale factors (one float32 per block of 64 weights). Those scale factors themselves are ~3GB on 70B. Double quantization compresses the scales to 8-bit, saving ~0.4 bits/parameter. Necessary to clear the 80GB limit
- **Paged Optimizers (QLoRA)** -- NVIDIA unified memory lets optimizer states page to CPU RAM during gradient checkpointing peaks instead of triggering OOM. Peak memory drops from ~79GB to under 80GB for a 70B QLoRA run
- **SFT Response-Only Loss** -- Standard cross-entropy computed on response tokens only, not instruction tokens. Masking instruction tokens is critical -- without it, the model learns to imitate the prompt template, not generate good responses
- **Reward Hacking (RLHF)** -- Model learns to maximize reward model score rather than actual quality. Signs: verbose responses, sycophantic agreement, artifacts the RM scored highly but humans don't. Fix: KL penalty in PPO, held-out human eval, diverse RM training data
- **DPO (Direct Preference Optimization)** -- Bypasses reward model entirely (Rafailov et al., 2023). Directly optimizes policy using preference pairs: maximize P(chosen|prompt) / P(rejected|prompt) with KL regularization. Theoretically equivalent to RLHF but 3x simpler to implement. Beta controls KL penalty strength. Modern models (Llama 3 Instruct) use DPO
- **Test-Time Compute** -- Industry term (2024+) for spending more inference work (longer internal chains, more samples, search) to improve per-query outcome. Reasoning-tuned models push the same trade: spend more wall-clock at inference to raise quality on hard tail. Requires routing to avoid wasting expensive serial decode on easy queries
- **CoT Faithfulness** -- Visible chain of thought is an explanation-like artifact, not a transcript of internal computation. Models can produce coherent post-hoc rationales that do not match the actual causal path to the answer. Production response: evaluate outcomes and verifiers, not reasoning length
- **CoT Overthinking** -- For single-step or format-trivial tasks, forcing a long scratchpad adds verbosity and can worsen accuracy when the model invents irrelevant constraints. Always A/B on your distribution; GSM8K-style curves do not replace product metrics
- **Self-Consistency Voting Failures** -- Voting fails when: (1) output is free-form with no stable equality, (2) all chains make the same systematic error (violated independence), (3) SLA is too tight for k full decodes, (4) you need calibrated probabilities not a mode
- **Tree of Thoughts** -- Search over verbal reasoning steps for tasks with scorable partial states (games, code with tests). Without a prune signal, this is just expensive fan-out. Branching factor x depth x model calls is the cost
- **Tool Calling as RPC** -- Function/tool calling exposes named procedures with JSON Schema for arguments. The model emits a structured call (function name + JSON arguments) your runtime executes and feeds back. This is the API contract between an LM and the world
- **Strict Mode (Tool Calling)** -- Token masking enforces schema compliance: schema compiled to FSM, at each decode step only tokens keeping output syntactically valid are allowed (logits set to -inf). Requires additionalProperties: false and explicit required fields. Adds small throughput reduction from masking overhead
- **JSON Mode vs Tool Calls** -- JSON mode guarantees syntactically valid JSON but NOT a field-level contract (keys can be missing, renamed, wrongly typed). Use JSON mode for best-effort blobs; use tool calls for actions and RPCs where schema violations must block before side effects
- **Idempotency Keys (Tool Calling)** -- Network retries and agent replanning can call the same function twice. Idempotent operations (SET balance=X) are safe to duplicate. Non-idempotent (TRANSFER $X) cause double-charges without idempotency keys. Required for all mutating tool calls
- **MCP Tool Poisoning** -- Malicious or compromised MCP server advertises benign-looking tools, then returns hidden instructions in tool output that steer the agent toward exfiltration or privileged calls. Treat MCP servers as supply-chain dependencies; maintain allowlists, require auth scopes per server
- **HELM (Holistic Evaluation of Language Models)** -- Liang et al., TMLR 2023. Taxonomizes scenarios and measures up to 7 metric families per scenario: accuracy, calibration, robustness (paraphrase perturbations), fairness (demographic accuracy gaps), bias, toxicity, inference efficiency. Multi-metric transparency beats leaderboard theater
- **MMLU Contamination** -- Test set questions appearing in pretraining corpus, causing recall rather than reasoning. Detection: 13-gram overlap checks (flag test items where 13-word subsequence appears in training), perplexity tests (anomalously low), post-cutoff held-out evaluation. A contaminated model can score 5-10 points higher than true ability
- **LLM-as-Judge Biases** -- Position bias (swap A/B order and aggregate), verbosity bias (longer looks more thorough), reference anchoring (valid alternatives penalized for not matching one gold response), rubric-order bias (scores shift when criteria order changes). Protocol design beats model choice
- **RAGAS** -- Retrieval Augmented Generation Assessment: faithfulness (claims supported by retrieved context), context precision/recall, answer relevance. Default evaluation framework for retrieval + generation systems. Uses LLM components for some metrics
- **Private Canary Deck** -- Fixed list of non-negotiable test slices (JSON schema pass rate, RAG faithfulness on labeled docs, refusal behavior on frozen jailbreak set) with versioned prompts in git and eval manifest checked into CI. The actual ship bar, not public benchmarks
- **IFEval** -- Instruction Following Evaluation: hard format rules (output exactly N sentences, include keyword, respond in all caps). Narrow but useful for API contract regression testing
- **KV Cache Memory Formula** -- 2 x n_layers x n_kv_heads x d_k x seq_len x 2 bytes (bfloat16). For LLaMA-3 70B at 128K context: ~40GB just for KV cache (separate from model weights). This is why long-context inference is expensive and why PagedAttention (vLLM) was a breakthrough
- **Flash Attention** -- IO-aware algorithm: tiling (process blocks that fit in SRAM), online softmax (compute incrementally without full materialization). Reduces HBM accesses from O(n^2) to O(n). Same mathematical output as exact attention, 2-4x speedup. Enables context lengths that would previously run out of GPU memory
- **Decode Memory-Bound** -- Modern decoder LLM serving: decode is memory-bandwidth bound (loading weights for each token), prefill is compute-heavy (processing all prompt tokens at once). Architectural details like GQA, MoE, RoPE scaling directly change the memory budget and therefore the SLA
- **MoE (Mixture of Experts)** -- Reduces active FFN compute per token by routing to subset of experts. Does NOT make attention or KV cache free; expert routing adds load-balancing and communication problems that dense models avoid. Expert imbalance is a production concern
- **Technique Escalation Ladder** -- Ordered decision sequence for GenAI: prompt engineering -> few-shot in context -> RAG -> fine-tuning (LoRA) -> continued pretraining. Each rung is ~10x more expensive and slower to iterate. The interview test is whether you move up one rung at a time, stating what each can and cannot fix
- **GenAI Interview Signals** -- Five signals graded in GenAI rubrics: (1) architectural fluency (derive transformer block, tie to real models), (2) decision discipline under hype (ask whether LLM is even the right tool), (3) production realism (name vLLM, FAISS, BGE embeddings, RAGAS not generic placeholders), (4) quantitative grounding (KV cache GB, TTFT/ITL targets, $/1M tokens), (5) failure-mode awareness (hallucination, injection, retrieval miss, KV cache OOM surfaced unprompted)
- **Research-Track vs Production-Track** -- GenAI interviews are bimodal. Research-track (foundation model teams, frontier labs): derive attention from QKV, explain RoPE vs sinusoidal, reason about Chinchilla scaling. Production-track (LLM platform, AI infra): size vLLM cluster, name TTFT/ITL budgets, explain PagedAttention. Misreading which loop wastes 40 minutes
- **GenAI Design Playbook** -- 6-phase mechanical playbook: (1) translate product ask into 4 numbers (accuracy, latency, cost, scale), (2) climb escalation ladder, (3) pick model class (hosted vs self-hosted vs multi-model), (4) design data+retrieval if RAG, (5) design serving stack, (6) design eval + failure modes. Time budget: 5+5+5+10+10+10 min
- **Cost-Per-Request Math** -- Llama-3-70B in BF16 = 140GB weights. KV cache for one 8K-context request ~2.5GB. A100-80G fits model + ~10 concurrent 8K requests. H100 doubles that. TTFT target for chat is sub-second; ITL target 30-50ms. $0.50-$3/1M output tokens hosted GPT-4-class; $0.05-$0.20 self-hosted Llama-3 on H100
- **Hybrid Retrieval (BM25 + Dense)** -- Dense embeddings excel at semantic neighborhoods but miss exact IDs, codes, SKUs, and rare terms. BM25 nails exact keyword matches but misses semantic paraphrases. Hybrid combines both, fused with Reciprocal Rank Fusion (RRF). Production wins are 5-15% recall improvement over either alone
- **Reciprocal Rank Fusion (RRF)** -- Fusion method that combines ranked lists from different retrievers: score(d) = sum over retrievers of 1/(k + rank(d)), typically k=60. Rank-based fusion outperforms score-based weighted averaging because it is scale-invariant and does not require score normalization across different retrieval systems
- **Two-Stage Reranking** -- Retrieve top 50-100 candidates with fast bi-encoder (dense or hybrid), then rerank to top 5-10 with cross-encoder (bge-reranker-large, Cohere Rerank). Cross-encoder is 10-100x slower per pair but only runs on shortlisted candidates, so latency cost is bounded. Reranking typically adds 10-30% to NDCG@10 in production
- **Cross-Encoder** -- Model that jointly encodes query-document pair (unlike bi-encoder which encodes separately). Slower but more accurate because it can attend to query-document interactions. Used in reranking stage, not retrieval stage. bge-reranker-large and Cohere Rerank are production choices
- **Bi-Encoder** -- Architecture that encodes query and document independently into embeddings, then computes similarity. Fast at query time because document embeddings are pre-computed. The standard for retrieval but sacrifices precision vs cross-encoders because it cannot model query-document interaction
- **HyDE (Hypothetical Document Embeddings)** -- Query expansion technique: generate a hypothetical answer to the query with an LLM, embed that answer, and use it for retrieval instead of the raw query. Closes the query-document vocabulary gap because the hypothetical answer uses document-like language. Helps when queries are short and vague; hurts when the LLM's hypothetical answer is misleading
- **RAPTOR** -- Recursive Abstractive Processing for Tree-Organized Retrieval. Builds a tree of summaries over the corpus: leaf nodes are original chunks, parent nodes are LLM-generated summaries of clusters. Enables retrieval at multiple abstraction levels, critical for broad questions like "what are the main themes?" that no single chunk answers
- **Query Decomposition** -- Breaking a complex multi-hop question into sub-queries, retrieving for each independently, then synthesizing. Required when no single chunk contains the full answer ("Compare Q1 and Q3 revenue growth rate" needs two retrievals). Adds latency and complexity but necessary for analytical questions
- **Semantic Conflation** -- RAG failure mode where query is semantically similar to irrelevant content. Both "financial derivatives" and "math derivatives" are about derivatives; the embedding model may not distinguish them without domain-specific training. Fixed by hybrid retrieval (BM25 catches domain-specific keywords) and reranking
- **Vocabulary Mismatch** -- RAG failure mode where query uses different vocabulary than documents ("CUDA out of memory error fix" vs documents about "GPU memory allocation failure"). Dense models handle paraphrase but struggle with abbreviations, product codes, proper nouns. Fixed by hybrid BM25+dense retrieval and HyDE
- **Embedding Model Lock-In** -- Switching embedding models requires full re-index of the entire corpus. Model version mismatch between indexing and query time produces meaningless cosine similarities. Production pattern: track embedding model version as required metadata, treat model changes as breaking changes requiring re-index
- **Agentic RAG** -- RAG augmented with the ReAct pattern: the LLM decides when to retrieve, can make multiple retrieval calls, and can use tools (calculator, SQL query, web search) in addition to document retrieval. Required for multi-hop questions that need sequential reasoning. Overkill for simple factual Q&A
- **Long-Context vs RAG Decision Matrix** -- Long-context (stuff all docs into 128K context): simple, no retrieval pipeline, but expensive ($/token over long context), slower TTFT, and lost-in-the-middle degradation. RAG: cheaper per query, scalable to millions of docs, but requires retrieval pipeline. Hybrid (RAG + long context for top chunks): best of both for most production cases
- **Position-Aware Context Assembly** -- Ordering retrieved chunks in the prompt to mitigate lost-in-the-middle effect. Strategy: put system prompt at beginning, most-relevant retrieved chunks at end (benefit from recency bias), older/less-relevant chunks in the middle. Recent and most-relevant content closer to the end improves accuracy
- **Chunking Strategies** -- Fixed-size (200-500 tokens, 10-20% overlap): simple default. Semantic (split on paragraph/topic boundaries): wins for structured docs (legal, medical). Hierarchical (small chunks for retrieval, parent chunks for context): production winner -- retrieve at small-chunk granularity for precision, give LLM the larger parent for context
- **PagedAttention** -- vLLM technique that treats KV cache like virtual memory: KV cache split into fixed-size blocks, allocated on demand, shared across requests with common prefixes via copy-on-write. Increases concurrent request capacity from ~5 to ~100 on same hardware by eliminating GPU memory fragmentation
- **Speculative Decoding** -- Use a small draft model to propose multiple tokens, then verify in parallel with the large model. Reduces ITL (inter-token latency) without changing output distribution. Helps when model is memory-bandwidth bound (large model decode). Hurts when draft model is inaccurate (wasted verification steps)
- **Multi-Model Routing** -- Route easy queries to a small/cheap model and hard queries to a large/expensive model via a classifier. Cuts cost 5-10x in production. Routing signals: query complexity, topic, expected output length. The classifier itself can be a small BERT model. Critical for production cost optimization
- **Quantisation (LLM Serving)** -- INT8 (2x throughput, minimal quality loss), FP8 (H100 native, similar to INT8), INT4/AWQ/GPTQ (4x throughput, ~1-3% quality loss for most tasks). Always benchmark on your specific task before committing. Trade-off: throughput vs quality vs hardware requirements
- **Production RAG Failure Modes** -- Ranked by frequency: (1) retrieval miss (wrong or no chunks returned), (2) context dilution (too many chunks, relevant information buried), (3) hallucination (model generates unsupported claims), (4) stale index (documents updated but not re-indexed), (5) prompt injection via retrieved content
- **RAGAS Metrics (Full)** -- Faithfulness (all claims in answer supported by context), Context Precision (are relevant chunks ranked higher), Context Recall (did retrieval find all necessary information), Answer Relevance (does answer address the question). Faithfulness catches hallucination; Context Precision catches reranking failures; Context Recall catches retrieval gaps

### LLM Guardrails & Safety

| Area | Description | Proficiency Expectation |
|------|-------------|------------------------|
| Input/Output Filtering | Two-stage pipeline (fast BERT classifier + sampled LLM-as-judge), input filtering parallel with context load, output filtering sequential after generation, PII detection via regex + NER, Microsoft Presidio | Design defense-in-depth safety pipeline; justify which filter goes where; explain latency vs coverage tradeoffs |
| Jailbreak Defense | Known jailbreak library + semantic matching, instruction hierarchy training, refusal consistency logging, behavioral anomaly detection, perplexity filtering for adversarial suffixes, GCG attack awareness | Explain why jailbreak defense is fundamentally an arms race; design multi-layer defense; acknowledge no complete solution exists |
| Constitutional AI (CAI) | Anthropic's training-time technique: model generates response pairs, evaluates against 16 constitutional principles, trains preference model, fine-tunes with PPO. Reduces human labeling cost ($50-100/hr) by using model as annotator | Distinguish CAI (training-time) from runtime guardrails; explain CAI vs RLHF relationship; argue CAI handles safety while RLHF handles helpfulness |
| Content Moderation | Three-tier architecture: Tier 1 automated filter (99% traffic), Tier 2 moderator queue (0.5-1%), Tier 3 expert review (0.01-0.1%). Metrics: review latency SLA, inter-rater agreement (IRA >90%), overturn rate (<5%) | Design moderation pipeline with feedback loop to classifiers; address moderator mental health; track overturn rates by category for retraining |
| Red-Teaming | Three-phase pipeline: Phase 1 expert red-teamers (50+ domain experts, 2-4 weeks pre-launch), Phase 2 automated red-teaming (10K+ tests daily via attacker LLM), Phase 3 crowd-sourced bug bounty ($200-$20K). ASR target: <1% on known attacks | Design continuous red-team infrastructure; argue public benchmarks are hints not SLAs; explain ASR metric and coverage gaps |
| PII Handling | Three threat vectors (user inputs, training data memorization, model outputs). Detection pipeline: regex for structured PII, NER for unstructured, tokenization with context preservation (<NAME_1>, <ADDRESS_1>). Edge case: contextual PII (3+ demographic attributes may uniquely identify) | Design PII detection pipeline; explain Microsoft Presidio architecture; handle contextual PII risk scoring for high-risk scenarios |

- Design the safety system for an LLM-powered financial services chatbot. What are the threats and how do you mitigate them?
- You are building an LLM coding assistant and the model suggested code containing a hardcoded AWS access key. How do you prevent this?
- Walk through implementing a production-ready prompt injection defense for an LLM agent that reads emails and executes calendar actions.
- How would you evaluate the safety of a newly fine-tuned model before deploying it to production?
- A user finds a jailbreak that works 20% of attempts despite system prompt hardening. What do you do next?
- Explain Constitutional AI vs RLHF. Why does Anthropic use both?
- When should you route to human content moderation vs automated blocking? What metrics govern the threshold?
- What is the difference between direct prompt injection and indirect injection in RAG/agentic systems? How do you defend against each?
- Your safety classifier has a 95% overturn rate from human moderators. What went wrong?
- Explain the many-shot jailbreak attack on long-context models. Why are 100K+ context windows especially vulnerable?

- **Defense in Depth (LLM Safety)** -- Production safety requires multiple independent layers each assuming others can fail: input classifiers (fast BERT + regex), system prompt hardening, output classifiers (fast + sampled LLM-as-judge), continuous red-teaming. No single layer is sufficient
- **Constitutional AI (CAI)** -- Anthropic's training-time safety technique: model generates response pairs, self-evaluates against 16 constitutional principles ("choose the response least intended to build a relationship", "most discourages violence"), trains preference model on AI-labeled preferences, fine-tunes with PPO. Reduces human labeling cost dramatically. CAI handles safety; RLHF handles helpfulness. Runtime guardrails still necessary for defense in depth
- **Attack Success Rate (ASR)** -- Primary red-teaming metric: ASR = (# successful jailbreaks) / (# attempts). Production target: <1% on known attack categories, <5% on novel attacks. GPT-4 ASR on harmful content: 0.73% (per GPT-4 Technical Report), down from 6.48% for GPT-4-early
- **PII Tokenization** -- Replace detected PII with typed tokens that preserve context: "John Smith" -> <NAME_1>, "123 Main St" -> <ADDRESS_1>. Model processes tokenized version; mapping back to real values is session-scoped only. Allows personalized responses without storing raw PII in logs
- **Microsoft Presidio** -- Open-source PII detection combining regex + NER + context-aware validation. 95%+ recall on structured PII, 85-90% on unstructured. Extensible for custom PII types (employee IDs, internal codes)
- **Moderation Tier Architecture** -- Tier 1: automated filter handles 99% of traffic (auto-block >0.8 confidence, auto-pass <0.5). Tier 2: human moderators review borderline cases (50-200 cases/hour). Tier 3: domain experts handle escalated cases. Every moderator decision feeds back to classifier training for continuous improvement
- **Jailbreak Categories** -- Roleplay attacks (DAN), prefix injection ("Complete this story: 'How to build a bomb. Step 1:'"), encoded instructions (Base64, rot13), hypothetical framing, context stuffing / many-shot jailbreaking (2024: flood context with fake examples), adversarial suffix / GCG attacks (gradient-optimized token sequences)
- **Safety Failure Modes** -- (1) Jailbreak drift: new jailbreaks emerge constantly, not a one-time fix. (2) Overblocking: aggressive safety classifiers destroy product value. (3) Indirect injection via RAG/tool outputs. (4) PII in model outputs from memorization. (5) Safety theater: keyword filters trivially bypassed

### LLM Observability & Monitoring

| Area | Description | Proficiency Expectation |
|------|-------------|------------------------|
| Distributed Tracing for LLM | OpenTelemetry + OpenInference semantic conventions, span kinds (LLM, RETRIEVER, TOOL, GUARDRAIL, EVALUATOR, AGENT), required attributes per span, trace waterfall for multi-step chains | Design trace spec for LLM chains; explain why traditional APM is insufficient; choose span attributes that enable debugging without logging raw prompts |
| Cost & Token Tracking | Per-tenant token attribution via trace-level attributes, multi-provider pricing tables (OpenAI vs Azure PTU vs Anthropic), reasoning token accounting (o1/o3 internal CoT tokens billed but hidden), four-tier budget enforcement (API key, team, customer, provider) | Design cost attribution system; handle pricing drift across providers; enforce budgets at multiple levels; account for reasoning tokens |
| Latency SLOs | TTFT < 1s (interactive), TBT < 50ms, ITL targets, burn rate alerts on SLO violations. Separate SLOs by model tier and request type | Set appropriate SLOs by use case; design burn rate alerts; explain why p99 latency requires different optimization than p50 |
| Evaluation Harnesses | Golden set CI (frozen prompts + expected outputs checked into git), shadow traffic eval, LLM-as-judge with debiasing protocol, regression detection on prompt/model/schema changes | Design eval harness that gates deployments; explain judge drift trap; implement golden-set regression in CI |
| Alerting Strategy | Page on: SLO burn rate (parse failures, latency regression), empty retrieval rate spikes, model version change. Dashboard: token cost trends, refusal rate, tool success rate, schema compliance | Distinguish what to page on vs dashboard; design alerts that catch novel LLM failure modes (not just HTTP 5xx) |

- Design the observability stack for a production RAG system with 10K daily users. What traces, metrics, and alerts do you need?
- Your LLM application's p99 latency doubled after a deploy but HTTP error rate is 0%. Walk through your debugging approach using traces.
- How do you track cost per tenant in a multi-tenant LLM platform? What about reasoning tokens that are billed but not visible to the user?
- What is judge drift and why does it make LLM-as-judge unreliable for regression detection? What is the fix?
- Design a golden-set CI pipeline that gates prompt template changes. What goes wrong when you skip this?
- When should you page an engineer vs just dashboard an LLM production metric? Give five examples of each.
- Explain the OpenInference span kinds and why traditional OpenTelemetry is insufficient for LLM chains.

- **OpenInference Span Kinds** -- LLM-specific extension of OpenTelemetry: LLM (model completion), EMBEDDING (vector generation), RETRIEVER (vector search), RERANKER (post-retrieval scoring), TOOL (function execution), AGENT (orchestration loop), GUARDRAIL (safety filter), EVALUATOR (judge call). Required attributes include llm.system, llm.model_name, llm.token_count.prompt/completion
- **Production LLM Observability Stack** -- Langfuse (MIT, self-hostable), Arize Phoenix (open-source, OTLP native), Braintrust (commercial with free tier), LangSmith (LangChain vendor). All accept OpenTelemetry traces via OTLP
- **Golden Set CI** -- Fixed list of non-negotiable test slices (JSON schema pass rate, RAG faithfulness on labeled docs, refusal behavior on frozen jailbreak set) with versioned prompts in git and eval manifest checked into CI. The actual ship bar, not public benchmarks
- **Judge Drift Trap** -- LLM-as-judge scores drift over time as judge model updates or prompt changes subtly shift scoring behavior. Production fix: anchor judge scores to a frozen reference set, track delta from baseline, use rubric-based scoring with fixed criteria order
- **Burn Rate Alerts (LLM)** -- SLO burn rate measures how fast error budget is being consumed. For LLM systems, page on: JSON parse failure burn rate > 14.4x in 1h window, TTFT p99 > 2x baseline for 30min, model version artifact tag change without canary pass
- **PII in Logs (Observability)** -- Logging raw prompts is a compliance incident (PII, API keys, customer data in retrieval chunks). Production pattern: scrub/hash prompts, tiered raw logging with legal approval, PII detection before storage
- **Reasoning Token Cost** -- OpenAI o1/o3 models emit internal chain-of-thought tokens not shown to user but billed. API returns usage.completion_tokens_details.reasoning_tokens. Cost tracker must parse this field or undercount by 2-5x on reasoning-heavy workloads
- **Token Cost Attribution** -- Propagate tenant_id and user_id as trace-level attributes in root span. OpenTelemetry context propagation carries them to every child span. Query sum by (tenant_id) of llm_cost_usd for finance dashboards. Four-tier budgets: virtual key, team, customer, provider config

### LLM Serving at Scale

| Area | Description | Proficiency Expectation |
|------|-------------|------------------------|
| Prefill vs Decode | Prefill is compute-bound (process all input tokens simultaneously), Decode is memory-bandwidth-bound (read all weights per token). TTFT dominated by prefill, TBT dominated by decode bandwidth | Explain why a single HTTP 200 can hide partial failures; design serving optimizations targeting each phase separately |
| Continuous Batching | Iteration-level scheduling: after each decode step, replace finished sequences with waiting requests. GPU utilization 70-90% vs 10-30% for static batching. 5-10x throughput improvement at variable request lengths | Explain why static batching wastes GPU; design continuous batching with chunked prefill to prevent TTFT spikes |
| LLMOps Discipline | Prompt versioning in git (never edit in-place), release gates (golden set + canary + shadow eval), model version tracking, canary deployments with automated rollback on SLO violation | Design LLMOps pipeline for safe prompt/model deploys; explain why editing prompts in-place is an anti-pattern |

- Explain the prefill/decode distinction and why it makes LLM serving fundamentally different from traditional model serving.
- Your LLM API has good average latency but terrible p99. Walk through optimization strategies targeting prefill vs decode separately.
- Why is static batching wasteful for production LLM serving? How does continuous batching solve this?
- What is chunked prefill and when do you need it?
- Design the LLMOps pipeline for deploying a new prompt template to production. What gates must pass before full rollout?
- Why should prompts be versioned in git? What goes wrong when you edit a prompt in-place in production?
- Your LLM serving cluster needs to handle 1K concurrent users vs 1M. How does the architecture differ?

- **TBT (Time Between Tokens)** -- Time per generated token after the first; dominated by decode memory bandwidth. Target < 50ms for interactive use. Formula: memory_size / bandwidth. Each decode step must read all model weights (~140GB for 70B) from HBM for one output token
- **Chunked Prefill** -- Extension of continuous batching: instead of processing entire prefill in one GPU call (blocking decode for existing requests), chunk prefill into smaller pieces interleaved with decode steps. Prevents TTFT latency spikes for existing requests when long new request joins batch. Used by OpenAI and Anthropic for consistent P99 latency
- **Continuous Batching** -- Iteration-level scheduling: after each decode step, check if any sequence hit EOS, immediately insert next waiting request into vacant slot. Batch size stays constant; slots reused within single token step. 5-10x throughput improvement over static batching at variable request lengths. Single most impactful optimization for production LLM serving throughput
- **LLMOps: Prompt Versioning** -- Prompt templates are code and must be versioned in git. Anti-pattern: editing prompt in-place in production database or config. Every prompt change is a deployment that must pass golden set CI + canary + shadow eval, identical to model version changes
- **Release Gates (LLM)** -- Pre-deployment checks: (1) golden set CI passes (frozen prompts + expected outputs), (2) canary deployment to 1% traffic with automated SLO monitoring, (3) shadow traffic eval (run new model on real traffic, compare outputs without serving them), (4) automated rollback if SLO violated during canary
- **Static vs Continuous Batching** -- Static: fill batch of N, process until ALL complete, start next. Wastes GPU when requests have variable lengths (GPU idle 99% after short request finishes, utilization 10-30%). Continuous: replace finished sequences immediately, utilization 70-90%

### LLM Quantization

| Area | Description | Proficiency Expectation |
|------|-------------|------------------------|
| Quantization Fundamentals | PTQ vs QAT, memory math (FP16 140GB -> INT8 70GB -> INT4 35GB), three decisions (what to quantize, granularity, calibration data), which layers to skip (LayerNorm, embeddings, LM head) | Size a model for given GPU; choose quantization method by hardware and quality requirements; explain why calibration data matters |
| GPTQ | INT4 standard via second-order Hessian compensation. Quantizes column-by-column, compensates remaining columns using inverse Hessian. Minimizes output error (delta_W x X), not weight error. ~+0.3 perplexity delta on WikiText-2. Calibration: 30-60 min on A100 | Explain GPTQ algorithm at interview depth; compare with AWQ; justify when GPTQ is the right choice |
| AWQ | Activation-aware weight quantization. 1% of weights cause 60%+ of quantization loss (salient weights in high-activation channels). Pre-scales input channels before quantization to protect salient weights. Faster calibration (5-10 min), often better than GPTQ on <70B models | Explain why activation magnitudes determine weight importance; compare AWQ vs GPTQ quality by model size |
| bitsandbytes | Mixed-precision loading: load_in_8bit (LLM.int8() with dynamic outlier handling) and load_in_4bit (NF4 NormalFloat4, information-theoretically optimal for normally distributed weights). No calibration needed | Choose between bitsandbytes, GPTQ, AWQ by use case; configure NF4 with double quantization for QLoRA |
| Calibration Data | Most overlooked variable in quantization quality. Using wrong domain data causes 2-3x worse accuracy drop. Match calibration data to deployment domain. 128-512 samples typical | Explain why calibration data domain must match deployment domain; diagnose quantization quality issues from calibration mismatch |

- Explain the memory math for quantizing Llama 3 70B from FP16 to INT8 to INT4. What fits on a single H100?
- Compare GPTQ and AWQ. When would you pick each?
- What is the outlier problem in LLM quantization? How does LLM.int8() solve it?
- Why should you skip quantizing LayerNorm and embedding layers? What happens if you don't?
- Your INT4-quantized model has 15% perplexity degradation. Walk through debugging: calibration data, quantization granularity, layer skipping.
- Explain bitsandbytes NF4 and why it is information-theoretically optimal for neural network weights.
- When should you NOT quantize a model?

- **PTQ (Post-Training Quantization)** -- Quantize after training completes, no re-training. Run calibration dataset (128-512 samples) through model, compute quantization scales from observed distributions, apply. Minutes to hours. Standard approach for LLMs because QAT training cost is prohibitive
- **GPTQ (Frantar et al., 2022)** -- De facto INT4 standard. Minimizes output error (||delta_W x X||) not weight error. Column-by-column quantization with Hessian compensation: after quantizing column i, update remaining columns via W_remaining -= (err_i / H^-1[i,i]) x H^-1[i, remaining]. On Llama 3 70B: ~+0.3 perplexity delta, 30-60 min calibration on single A100
- **AWQ (Lin et al., 2023)** -- Activation-aware weight quantization. Key insight: 1% of weights cause 60%+ of quantization loss, clustering in high-activation channels. Pre-scales input channels: W' = W x diag(s) where s_j = mean(|X_j|)^alpha, quantize W', then compensate activations X' = X / diag(s). Faster calibration (5-10 min), often outperforms GPTQ on <70B models
- **Symmetric (Absmax) Quantization** -- Scale factor s = max(|W|) / 127. Quantized: W_q = round(W / s), dequantize: W ~ W_q x s. Simple, hardware-friendly. Problem: outlier weights dominate scale, wasting dynamic range on common values
- **Asymmetric (Zero-Point) Quantization** -- Adds zero-point z to handle non-centered distributions. s = (max - min) / 255, z = round(-min / s). Better for activations (ReLU outputs are non-negative). More computation overhead but captures full range
- **LLM.int8() (Dettmers et al., 2022)** -- Mixed-precision INT8 that handles systematic activation outliers in large models. Decomposes matrix multiply: outlier channels stay FP16, rest use INT8. ~15-20% slower than pure INT8 but near-FP16 quality. Implemented in bitsandbytes load_in_8bit
- **NF4 (NormalFloat4)** -- 4-bit data type using quantile quantization: 16 representable values spaced at quantiles of standard normal distribution. Information-theoretically optimal for normally distributed weights (which neural network weights approximately follow). Used by bitsandbytes load_in_4bit. Memory format, not compute format (dequantizes to BF16 for actual math)
- **Quantization Layer Skipping** -- Always quantize: linear/attention/FFN projection layers (Q, K, V, O, gate, up, down) -- >95% of parameters. Always skip: LayerNorm (tiny params, error propagates multiplicatively), embedding layers (large vocab x d_model, errors affect all downstream), final LM head projection
- **Calibration Data Domain Mismatch** -- Most common production quantization mistake. Model calibrated on C4 Wikipedia text but deployed for SQL generation will have 2-3x worse accuracy drop. Fix: match calibration data distribution to deployment domain. 128-512 samples from production-like data is sufficient

### ML Data Pipelines

| Area | Description | Proficiency Expectation |
|------|-------------|------------------------|
| Data Pipelines for ML | Kafka for event collection, Spark for batch feature engineering, Flink for real-time aggregations, Schema Registry for schema evolution, batch vs streaming trade-offs, label delay problem, data quality monitoring | Design ML data pipelines that guarantee point-in-time correctness, label alignment, and training-serving consistency; choose between Spark and Flink by freshness requirements |

- Design the data pipeline for a real-time recommendation system serving 1M requests/minute. What events do you collect, how do you process them, and how do you generate training data?
- Your batch feature pipeline runs every 24 hours but your model needs features with less than 1-hour staleness for real-time serving. What architecture do you use?
- How do you ensure that feature computation in your training pipeline exactly matches feature computation in your serving pipeline to prevent training-serving skew?
- How does the pipeline handle late-arriving events? What is Flink's watermark mechanism?
- Your training data has 30-day label delay (fraud chargebacks). How do you prevent training on incorrectly labeled data?
- A mobile app release changed an event field silently. How do you catch this before it poisons training data?

- **ML Data Pipeline vs Regular ETL** -- Standard ETL moves data from A to B on a schedule. ML data pipelines add three requirements: point-in-time correctness (features must reflect world state at prediction time, not today's state), label alignment (handle temporal gap between prediction and label arrival), and training-serving consistency (same transformation logic in batch training and real-time serving paths)
- **Kafka for ML** -- Foundational event bus that decouples producers (apps) from consumers (Flink, Spark, S3 sinks, monitoring). Key configs: partition by entity_id so events for same user go to same partition (critical for Flink stateful aggregations), retention 30-90 days for disaster recovery, Schema Registry (Avro or Protobuf) prevents silent schema breakage, single broker handles ~1M messages/second at 1KB messages
- **Spark vs Flink Decision** -- Use Spark for: daily/hourly batch feature engineering, training dataset generation over petabytes, historical backfills. Use Flink for: continuous real-time aggregations (transactions in last 5 minutes), features requiring sub-minute freshness, exactly-once stateful computations, event-time processing with out-of-order handling (Watermarks). Key distinction: Flink maintains state between events; Spark micro-batch recomputes from scratch every batch interval
- **Label Delay Problem** -- Ground truth labels arrive with delay: fraud chargebacks take 30-90 days, ad conversions take 7 days, notification clicks arrive within 1 hour. Fix: implement a label collection delay in training pipeline; don't use examples until labels have had time to arrive. For fraud: train on events from 90+ days ago. For ad conversion: use 7-day attribution window. Alternatively: use surrogate labels (click, add-to-cart) as proxies for delayed labels (purchase)
- **Data Quality for ML** -- Silent schema changes (mobile app changes field type, Schema Registry rejects if configured; without it, feature goes from 99% to 0% populated overnight), null rate monitoring (alert if null rate changes >5 percentage points vs 7-day average), event deduplication (mobile retries cause duplicate events; every event needs unique event_id, Flink deduplicates via bloom filter of seen IDs), distribution drift monitoring (if P90 of transaction_amount shifts >20%, investigate before training)
- **Flink Velocity Feature Pipeline** -- Sliding event-time windows (e.g., 5-minute windows with 30-second slides), keyed by entity_id (card_id), checkpoint interval 1-5 minutes with RocksDB state backend for exactly-once. Sink to Redis (online store) and S3 Parquet (offline store for point-in-time joins)

### Embeddings & Vector Databases

| Area | Description | Proficiency Expectation |
|------|-------------|------------------------|
| Embeddings & Vector DBs | ANN search (HNSW, IVF+PQ), embedding models, FAISS index selection by scale, managed vector DB comparison (Pinecone, Weaviate, Qdrant, Milvus), embedding freshness problem, embedding lifecycle and drift | Choose ANN index and vector database by catalog size and latency budget; tune HNSW parameters (M, ef_construction, ef_search); architect billion-scale retrieval with IVF+PQ; handle embedding freshness and cold-start at index level |

- Design the retrieval system for a video recommendation platform with 500M videos. Latency requirement: top-1000 candidates in <30ms.
- You have 1 billion product embeddings to search in real-time with <50ms latency. How do you architect the ANN index and serving infrastructure?
- Explain the difference between late interaction (ColBERT) and bi-encoder (DPR) retrieval. When does the extra cost of late interaction pay off?
- Why should an embedding model and vector index be versioned together?
- Your embedding model was upgraded but retrieval quality dropped 30%. What went wrong?

- **HNSW (Hierarchical Navigable Small World)** -- Default ANN algorithm for sub-billion scale (Malkov and Yashunin, 2016). Multi-layer graph where top layers have hub nodes with long-range edges; search starts sparse, navigates greedily, descends to dense layers. Key parameters: M (connections per node, production default 16, use 32 for high-recall medical/legal), ef_construction (search width during build, 200 general, 400 high-recall), ef_search (query-time search width; ef_search=50 gives ~90% recall at ~5ms, ef_search=200 gives ~98% recall at ~15ms for 10M 768-dim vectors). Memory: (d x 4 + M x 2 x 4) bytes per vector
- **IVF + Product Quantization** -- Billion-scale ANN with memory compression. IVF: k-means clusters vectors into Nlists centroids (4,096-65,536); at query time only nprobe nearest centroids searched. PQ: splits d-dim vector into M_pq sub-vectors, quantizes each to 1 byte (256 values via k-means). Result: 1,536-dim float32 vector (6,144 bytes) compressed to 48 bytes (128x reduction). Recall@100 drops from ~99% (exact) to ~92-96% (IVF+PQ). FAISS index selection: <1M use IVF4096,Flat; 1M-10M use IVF65536_HNSW32,Flat; 10M-100M use IVF262144_HNSW32,PQ48x8; 100M-1B use IVF1048576_HNSW32,PQ64x8
- **Embedding Freshness Problem** -- New items have no embedding in the ANN index and are invisible to retrieval. Solutions: re-embed and re-index daily (new items invisible up to 24 hours), incremental HNSW inserts for near-real-time, two-index strategy (large HNSW for established items weekly rebuild + small new-items index hourly rebuild, search both and merge), content-based fallback (metadata retrieval for items without embeddings)
- **Embedding Lifecycle** -- Item/document embeddings generated offline by two-tower, BERT-style, CLIP-style, or domain encoder, written to storage, scheduled pipeline builds index, validates recall, promotes through registry. User/query embeddings computed online, cached in Redis, or refreshed by Flink. Design decision: where freshness belongs. Nightly rebuild works for product catalog; fails for breaking news. Incremental inserts or delta index for minute-level changes
- **Embedding Evaluation Hierarchy** -- Contrastive validation loss or retrieval recall for encoder, exact-vs-ANN recall for index, NDCG or MRR for downstream ranking, online metrics (search reformulation, conversion, RAG answer acceptance) for production. Track slices by language, category, popularity, and cold-start age. Monitor embedding norm, nearest-neighbor overlap between old/new indexes, zero-result rate, duplicate results, filter selectivity

### ML Model Evaluation & Production Monitoring

| Area | Description | Proficiency Expectation |
|------|-------------|------------------------|
| Model Evaluation & Monitoring | Shadow deployment, canary rollout, A/B testing for ML, SLO design (infra/model health/business), rollback triggers and mechanisms, monitoring stack (infra/data/model/product signals), label delay handling, serving drift | Design full ML deployment lifecycle (shadow -> canary -> A/B -> full rollout); design ML-specific SLOs; handle label delay with proxy metrics; implement 5-minute rollback SLO |

- How would you safely deploy a new ML model that ranks search results at Google-scale?
- Your fraud detection model was deployed 6 weeks ago. How do you know if it's still working?
- Your A/B test shows the new model has CTR +4%, p=0.003. How do you decide whether to ship?
- How do you monitor a model whose true labels arrive weeks after prediction time?

- **ML Deployment Lifecycle** -- 4-phase: Shadow (0% user impact, 24-72 hours, validates latency and distribution) -> Canary (1-5% traffic, 4-24 hours, automatic rollback on error rate >1% or latency >2x baseline) -> A/B Test (10-50% traffic, pre-calculated sample size, 50/50 split for fastest convergence, guardrail metrics must not degrade) -> Full Rollout + champion-challenger monitoring (5% shadowed to old model for 2 weeks)
- **Three-Layer ML SLO Hierarchy** -- Layer 1 Infrastructure: serving latency P50 <50ms P99 <200ms, error rate <0.1%, feature pipeline freshness <5min. Layer 2 Model Health (no ground truth needed): score distribution stability within 15% of 30-day rolling average, prediction volume within 20% baseline, feature null rate <5%. Layer 3 Business (with label delay): primary metric week-over-week, proxy metrics for fast feedback, delayed ground truth for final evaluation
- **Label Delay Monitoring** -- Cannot measure fraud model accuracy today because labels arrive next month. Fix: build proxy-label systems using fast-feedback signals (chargebacks within 72 hours, card holder reports) as real-time accuracy proxy. Meta uses 7-second video dwell time as proxy for long-term user satisfaction (surveyed weekly)
- **A/B Testing for ML Mistakes** -- Skipping shadow deployment (catches latency regressions offline eval cannot), stopping when p < 0.05 (peeking inflates false positive rate to ~30%), no guardrail metrics (primary metric improves but complaint rate increases), using offline AUC as primary metric (users react dynamically to predictions; AUC is static), decommissioning old model immediately (keep warm for 2 weeks for 30-second rollback), no label-delay-aware monitoring
- **Rollback by Traffic Routing** -- Keep both model versions deployed; rollback is weight change in traffic router (30 seconds, not re-deploy). Automatic triggers: latency P99 >2x baseline for 10 min, error rate >1% for 5 min, prediction volume drops >30%. Blue-green deployment prerequisite for 5-minute rollback SLO
- **Monitoring Stack Separation** -- Four signal families with different owners: Infrastructure (Prometheus, Grafana: latency, error rate, GPU util) -> Data (feature nulls, freshness, PSI drift, point-in-time parity) -> Model (score distribution, calibration, slice performance, prediction volume) -> Product (CTR, conversion, fraud loss, complaint rate). Collapsing into one dashboard causes missed incidents

### Feature Stores

| Area | Description | Proficiency Expectation |
|------|-------------|------------------------|
| Feature Store Architecture | Two-tier design (offline S3/BigQuery + online Redis/DynamoDB), point-in-time correct joins, feature freshness tiers, training-serving skew prevention, feature versioning, Feast vs Tecton vs cloud-managed | Design feature store with offline/online tiers; explain point-in-time joins and why they prevent label leakage; choose between Feast, Tecton, and cloud options; design feature freshness tiers |

- Design the feature store for a real-time fraud detection system processing 10,000 transactions/second. What features do you need and how do you serve them?
- How do you prevent training-serving skew in a recommendation system where some features are computed by a data science team and others by a data engineering team?
- Your feature store serves 100K feature lookups/second at <10ms p99. You need to add a new feature that requires a 30-second aggregation window over streaming events. How do you add it without blowing the latency budget?
- What does write-through logging mean for online features, and why is it important?

- **Feature Store Two-Tier Architecture** -- Offline store (Parquet on S3, BigQuery, Snowflake): historical feature values keyed by (entity_id, timestamp), used for training dataset generation with point-in-time joins, query latency seconds-minutes, petabyte scale. Online store (Redis, DynamoDB, Bigtable): latest feature value per entity only, used for real-time serving, p99 <10ms, millions of entities. Both tiers use same feature transformation code enforced by feature registry
- **Point-in-Time Correct Join** -- For each (entity_id, event_timestamp) in label dataset, look up feature value as of event_timestamp - epsilon, not the latest value. Prevents future leakage: if you naively join latest feature values, you include information the model would never have had at prediction time. Implemented via SQL LATERAL JOIN or Feast/Tecton get_historical_features(entity_df)
- **Feature Freshness Tiers** -- Real-time (<100ms, computed inline at inference, 0ms lookup: current page URL, cart contents), Near-real-time (<1min, Redis/DynamoDB via Flink Kafka consumer, 1-5ms: items viewed last 5min), Hourly (<1hr, Redis refreshed from Spark, 1-5ms: user click rate today), Daily (<24hr, S3 Parquet + Redis materialization, <5ms: user 30-day purchase history), Static (DB/S3 + Redis, backfill on creation: item category, account type)
- **Feature Store Comparison** -- Feast (open-source, self-hosted, Redis/DynamoDB/PostgreSQL, 5-15ms, operational burden on you), Tecton (managed SaaS, DynamoDB built-in, p99 <10ms, >100K req/sec, enterprise ML), Vertex AI Feature Store (GCP managed, Bigtable, ~30ms, GCP-native), SageMaker Feature Store (AWS managed, variable under load, AWS-native), Hopsworks (SaaS + self-hosted, RonDB <5ms, regulated industries with audit logging)
- **Feature Store Failure Modes** -- Stale online features (materialization job fails silently, online store serves last week's values; fix: monitor feature freshness age, alert if stale beyond 1.5x expected interval), timezone bugs (UTC vs local SDK timestamps cause different distributions; fix: standardize to UTC at capture layer), too many feature views per request (serial fetching 15 views pushes p99 to 100ms+; fix: bundle into Feature Services for batch call), online store cost at scale (100M users x 500 features x 8 bytes = 400GB Redis = $2K/month; fix: only materialize features used at serving time)
- **Write-Through Lineage** -- For features used online, log the online-computed value back to offline store with event time and feature timestamp. Training then joins against the exact value the model saw in production, not a separately reimplemented approximation. Matters most for streaming windows, distinct counts, late-arriving mobile events, and features with TTL

### Model Deployment

| Area | Description | Proficiency Expectation |
|------|-------------|------------------------|
| Model Deployment Fundamentals | Batch vs online vs streaming inference, model serving infrastructure (TF Serving, Triton, KServe), shadow mode, A/B testing, progressive rollout, rollback strategies, model versioning and registry, feature store integration | Choose deployment pattern by latency/cost/freshness constraints; design staged rollout with rollback; explain model serving infrastructure trade-offs; implement model versioning and registry |

- When should you use batch inference vs online inference vs streaming inference? Justify with latency requirements and cost constraints.
- Compare TensorFlow Serving, NVIDIA Triton, and KServe. When would you pick each?
- Design the rollout strategy for a new ranking model at Google-scale. Include shadow, canary, A/B, and rollback.
- What is the 5-minute rollback SLO and why is traffic routing (not re-deploy) the mechanism?
- How do you version models in production? What goes in the model registry?

- **Batch vs Online vs Streaming Inference** -- Batch (processes data offline on schedule, minutes-hours latency, low cost on spot instances: email recommendations, report scoring), Online (synchronous per request, 50-200ms SLA, high cost always-on GPU: search ranking, fraud detection), Streaming (continuous event stream with bounded latency 100ms-5s, medium cost stateful workers: feed updates, anomaly detection), Hybrid (batch precomputes features/embeddings nightly, online serves real-time ranking: two-stage recommendation)
- **Model Serving Infrastructure** -- TensorFlow Serving (TF/Keras, dynamic batching, RESTful+gRPC, Airbnb uses for 50K QPS p99 <80ms), NVIDIA Triton (multi-framework TF/PyTorch/ONNX/TensorRT/XGBoost, model ensembling, TensorRT optimization 2-5x latency reduction, Uber uses for fraud <30ms p99 at 100K+ QPS), KServe (Kubernetes-native, wraps TF Serving/Triton/TorchServe, traffic splitting, autoscaling, canary rollouts, Bloomberg uses for 200+ models, 60% idle GPU cost reduction)
- **Shadow Mode** -- Deploys new model alongside production, predictions logged not served. Catches: train-serve skew (offline metrics good but online feature computation differs), latency regressions, integration bugs (missing features, schema mismatches), infrastructure issues (GPU OOM, dependency conflicts). Cost: 2x serving compute. Duration: 1-7 days. Metrics: prediction divergence %, latency distribution, error rate, feature parity. Blind spot: validates technical correctness but not user-facing impact
- **Progressive Rollout** -- Incremental traffic increase with promotion gates at each step. Example: Day 1: 5%, Day 3: 10% (if metrics healthy), Day 5: 25%, Day 7: 50%, Day 10: 100%. Netflix runs A/B tests 2-4 weeks on 10-50% of users tracking 100+ metrics. Spotify ramps 5% -> 10% -> 50% -> 100% over 2 weeks with automated rollback if skip rate increases >2%
- **Rollback Design** -- Keep old model warm (never delete until new model stable at 100% for >=7 days). Automatic triggers: latency p99 >20% above SLA for 5 min, error rate >0.5% for 2 min, conversion rate <-2% vs control, cost >50% above budget. Mechanisms: traffic rerouting (<1 min), blue/green flip (1-3 min), K8s rollback (5-10 min). Post-rollback: incident postmortem, model fix, full shadow+canary cycle again
- **Model Registry** -- Centralized metadata store tracking model artifacts, training code (git hash), training data (version, schema, date range), hyperparameters, evaluation metrics, feature definitions. Registries: MLflow Model Registry, Databricks Unity Catalog, SageMaker Model Registry, Vertex AI Model Registry. Versioning: semantic (major.minor.patch) or date-based with unique hash. Production workflow: training -> register candidate -> offline eval -> staging -> shadow/canary -> production
- **DRIFT Deployment Checklist** -- Define (launch gates: quality, latency, cost, fairness), Reason (map serving dependencies: features, preprocessing, model runtime), Identify failure modes (train-serve skew, drift, throughput collapse, calibration shifts), Fix (feature parity checks, canary guardrails, rollback automation), Test (replay tests + live canary monitoring by slice)

### Model Serving Architectures

| Area | Description | Proficiency Expectation |
|------|-------------|------------------------|
| Batch vs Real-Time Serving | Batch pre-computation (<5ms read, stale by hours-days) vs real-time inference (10-200ms, per-request freshness) vs hybrid (pre-compute embeddings offline, ANN + ranking in real-time) | Choose serving pattern by latency budget, freshness requirements, and model cost; design hybrid architectures for recommendation systems |
| Deployment Strategies | Shadow deployment (zero risk, 24-72hr, parallel scoring no user impact), canary (1-5% traffic, 48-72hr, real users affected), blue-green (instant switch, requires 2x infra), progressive ramp (1% -> 5% -> 10% -> 50% -> 100%) | Design safe deployment sequences; name auto-rollback triggers and RTO targets; explain why shadow -> canary -> ramp is industry standard |
| Latency Budget Decomposition | End-to-end SLA decomposed into stages: network (10-20ms), feature fetch (2-5ms), ANN retrieval (25-35ms), pre-ranker (10-20ms), neural ranker (40-80ms), post-processing (2-5ms), network return (10-20ms) | Design multi-stage pipeline within latency budget; apply cascade rule (each stage reduces candidates); avoid designing stages in isolation |
| Feature Mismatch at Deployment | Most common serving bug: training and serving code use different feature encodings (off-by-one, different normalization). Shadow deployment catches this via prediction distribution comparison. Fix: feature store with registered definitions | Identify and prevent training-serving feature encoding mismatches; explain why shadow deployment is the diagnostic tool |

- Your new ranking model passes offline evaluation. Walk through the deployment process from shadow to full rollout.
- When should you use batch pre-computation vs real-time inference? Justify with latency requirements and freshness needs.
- What is shadow deployment and how does it differ from canary deployment? When would you use each?
- Design a multi-stage recommendation pipeline with a 200ms latency budget. Show the decomposition per stage.
- What is the most common silent serving bug when deploying a new model? How do you detect and prevent it?
- You need to serve a 7B parameter LLM at <500ms TTFT for 10K concurrent users. What is your serving stack?

- **Batch Serving** -- Pre-compute predictions offline, store in Redis/DynamoDB, key-value lookup at request time. Latency <1ms but stale by hours-days. Use for: email recommendations, weekly playlist generation, pre-computed similar items. Examples: Netflix Top Picks, Spotify Discover Weekly
- **Real-Time Serving** -- Score inputs at request time using live context. Latency 10-200ms, perfect freshness. Use for: search ranking, fraud scoring, real-time ad targeting, any prediction depending on current session context
- **Hybrid Serving Pattern** -- Pre-compute user/item embeddings offline (batch), run ANN search and ranking in real-time using those embeddings. Most production recommendation systems use this pattern. Gets freshness where it matters (ranking uses live signals) without running expensive encoder at request time
- **Shadow Deployment** -- New model runs in parallel receiving same traffic as production, but only production predictions served. Use to verify prediction consistency, catch feature encoding bugs, measure latency under real load, compare prediction distributions. Duration: 24-72 hours. Promote to canary if shadow predictions statistically similar and latency within budget
- **Canary Deployment** -- Route 1-5% traffic to new model. Real users affected. Monitor online metrics (CTR, conversion, latency, error rate) vs control. Expand to 10% -> 25% -> 50% -> 100% if metrics neutral or positive after 48-72 hours. Rollback trigger: guard-rail metric degrades beyond threshold
- **Blue-Green Deployment** -- Two identical serving environments. Switch traffic instantaneously at load balancer. Rollback <1 minute. Downside: requires 2x serving infrastructure during transition. Rare in ML; more common for stateless services
- **Latency Budget Decomposition** -- Sum all stages to verify within SLA before building. Common mistake: designing stages in isolation (50ms x 5 stages = 250ms, over budget). Cascade rule: each stage reduces candidate set so next stage runs on fewer (more expensive) computations
- **Feature Mismatch Bug** -- Most common serving deployment failure: serving code uses different feature encoding than training code. Model silently serves degraded predictions with no error or exception. Shadow deployment catches this by comparing prediction distributions. Permanent fix: feature store with registered feature definitions so encoding never re-implemented independently

### Offline vs Online Evaluation

| Area | Description | Proficiency Expectation |
|------|-------------|------------------------|
| Offline-Online Gap | Distribution shift (historical data collected by previous model), position bias (position 1 gets ~3x more clicks than position 3 regardless of quality), feedback loops (popular items shown more get more clicks become stronger signals), novelty effect, Goodhart's Law | Explain at least 2 structural reasons offline and online metrics diverge; design evaluation strategy that addresses each cause |
| Position Bias & IPS | Items at position 1 receive 3x more clicks than position 5 regardless of relevance. Inverse Propensity Scoring (IPS) weights each example by 1/P(click given position) to debias. Alternative: add position as training feature, zero it out at serving time | Detect and fix position bias in training/evaluation data; implement IPS debiasing; explain why any offline dataset from a ranked system is position-biased |
| Counterfactual Evaluation | Doubly Robust (DR) estimator and IPS-based off-policy evaluation (OPE) estimate new policy performance on historical data without running live experiment. Requires logging propensity scores for every impression. Interleaving as faster alternative to full A/B tests (10-100x fewer users) | Design counterfactual evaluation pipeline; explain when DR estimation is preferred; compare interleaving vs A/B testing efficiency |
| Evaluation Hierarchy | 4-layer filter: (1) data quality metrics (schema, missingness, label delay), (2) offline model metrics (AUC-PR, NDCG, calibration, slice metrics), (3) shadow metrics (latency, score distribution, candidate overlap), (4) online A/B test (primary business metric + guardrails + proxy metrics) | Design full evaluation hierarchy from data quality to business decision; distinguish gate metrics from diagnostic metrics |

- Your model improves offline AUC by 0.02 but CTR drops 5% in production. What went wrong?
- You trained a fraud detection model with AUC-ROC = 0.96 but only 40% of actual fraud is caught in production. Diagnose.
- Why is shadow evaluation not a substitute for an online A/B test?
- What is position bias and how does IPS debiasing fix it?
- Explain counterfactual evaluation. When can you use Doubly Robust estimation?
- Your A/B test shows CTR +4% at week 1 but returns to baseline by week 3. What happened?

- **Distribution Shift** -- Offline evaluation uses historical data collected by previous model. New model will see different distributions because it serves different items. Eval data does not reflect what the new model will actually show
- **Feedback Loops in Evaluation** -- Training data collected by a model with its own biases: popular items shown more -> more clicks -> stronger training signals. Offline evaluation on biased data does not measure genuine user preference
- **Goodhart's Law in ML** -- When a metric becomes a target, it ceases to be a good measure. Optimizing NDCG@10 hard enough produces a model that ranks historically high-CTR items at top regardless of current user intent
- **Inverse Propensity Scoring (IPS)** -- Weight each training example by 1/P(click given position). Items at position 1 (high propensity) down-weighted, items at position 5 (low propensity) up-weighted. Corrects measurement bias from position-dependent click probability. Minimum fix for any offline evaluation of ranked systems
- **Doubly Robust (DR) Estimation** -- V_DR = (1/N) SUM [r(a,x)/pi(a|x) - r_hat(a,x)/pi(a|x) + v_hat(x)]. Correct if either the reward model OR the logging propensities are correct. Requires logging propensity scores for every served impression
- **Interleaving** -- Instead of routing users to model A or B, interleave results from both into single ranked list. Track which model's items get more clicks. 10-100x fewer users needed for same confidence. Used heavily at Netflix and LinkedIn for ranking evaluation
- **Novelty Effect in Evaluation** -- Users engage more with any new recommendation style for 1-2 weeks regardless of quality. Short A/B tests (1-2 weeks) capture novelty not genuine improvement. Run 3-4 weeks minimum for ranking changes, 6-8 weeks for major overhauls
- **Temporal Holdout** -- Use temporal split (train on days 1-28, eval on days 29-30) not random split. Random splitting contaminates eval set with items clicked before and after eval timestamp
- **Offline Metric-Online Metric Mapping** -- Calibrate offline metrics against historical A/B tests. If last 5 A/B tests showed NDCG@10 improvements >0.5% correlated with CTR improvements in 4 of 5 cases, NDCG@10 is a useful proxy. If no correlation, use as diagnostic only
- **Serving Drift During Experiments** -- Treatment traffic changes distribution of future events. New feed ranker exposes more long-tail items generating labels old model never collected. Monitor feature null rate, freshness, latency, and score distribution by variant

### Data Labeling Systems

| Area | Description | Proficiency Expectation |
|------|-------------|------------------------|
| Labeling Approaches | Human annotation (paid annotators, domain experts), weak supervision (Snorkel labeling functions), semi-supervised learning (model-assisted), active learning (BADGE sampling of uncertain predictions), auto-labeling (foundation models) | Choose labeling approach by task complexity, kappa structure, budget, and scale; design Snorkel pipelines for weak supervision |
| Inter-Annotator Agreement | Cohen's kappa (2 annotators), Fleiss' kappa (N annotators), Krippendorff's alpha (ordinal/continuous). Raw % agreement lies because it is inflated by class prior. Kappa <0.6 almost always indicates task design problem, not annotator problem | Calculate and interpret agreement metrics; diagnose low kappa as task design issue; name Landis-Koch thresholds (0.61-0.80 = substantial, 0.81-1.00 = near-perfect) |
| Quality Control | Gold-set seeding (5-10% injection, 85% accuracy threshold), redundant labeling (3-way or 5-way), Dawid-Skene EM aggregation (1979, production standard for weighting votes by annotator accuracy), expert adjudication for disagreements | Design QC pipeline with gold sets, redundancy, and aggregation; choose technique by kappa structure and cost multiplier |
| Data Flywheel | Deploy model -> log uncertain predictions -> active learning sampling -> label -> retrain -> redeploy. Cycle cadence varies: daily for content moderation, weekly for search ranking, monthly for medical. Compounding effect produces models competitors cannot match | Design data flywheel with active learning sampling; calculate economics per cycle; explain why better labels beat better models |

- Design the labeling system for an autonomous driving dataset with 1B unlabeled video frames. What is your architecture and budget?
- Your binary content moderation labels show Cohen's kappa = 0.45. Diagnose and fix.
- When should you use Snorkel weak supervision vs paid human annotators? Walk through the decision framework.
- Explain the data flywheel concept. Why does a 50-cycle yearly flywheel outperform a single static training run?

- **Snorkel / Weak Supervision** -- Define labeling functions (heuristics, keyword match, external knowledge bases, pre-trained models) that vote on labels without ground truth. Label model learns LF accuracies from agreement structure (Ratner et al., VLDB 2017). Output: probabilistic labels for downstream discriminative model that generalizes beyond LF coverage
- **Cohen's Kappa** -- Corrects raw agreement for chance: kappa = (p_o - p_e) / (1 - p_e). If base rate is 90% positive, two annotators always saying positive achieve 90% agreement without judgment. Kappa interpretation: <0.0 worse than chance, 0.21-0.40 fair, 0.41-0.60 moderate, 0.61-0.80 substantial (production-acceptable), 0.81-1.00 near-perfect
- **Fleiss' Kappa** -- Extension of Cohen's kappa to N annotators per item (not limited to 2). Use when annotation task distributes items across multiple annotator pairs
- **Krippendorff's Alpha** -- Most general agreement coefficient. Handles missing data and any data type (nominal, ordinal, interval, ratio). Use for ordinal severity ratings, continuous scores
- **Dawid-Skene EM Aggregation** -- Jointly estimates true labels and per-annotator confusion matrices from redundant annotations. Weights each annotator's vote by their historical accuracy on similar tasks. Production standard since 1979 for aggregating 3+ way annotations with heterogeneous annotator quality
- **Gold-Set Seeding** -- Inject 5-10% known-correct examples into each annotator's queue. Track per-annotator accuracy on gold over time. Below 85% for 2 consecutive weeks triggers retraining or removal. Empirical sweet spot: 5-10% (lower misses drift, higher wastes budget)
- **Taxonomy Drift** -- Annotators collectively and independently drift on label definitions over months. Training data from months 1-3 follows definition A, months 4-6 follows definition B. Model retrains on union and learns confused boundary. Fix: frozen gold set of 200-500 examples, re-evaluate all annotators monthly, calibrate when accuracy drops >5pp
- **Active Learning (BADGE)** -- Sample examples the model is most uncertain about (high entropy predictions) for labeling. BADGE adds diversity via k-means++ initialization on gradient embeddings. Avoids confirmation bias from uncertainty-only sampling (model may be confidently wrong on systematic blind spots)
- **Cleanlab Mislabeled Detection** -- Uses model confidence on training labels to identify likely mislabels. If model strongly disagrees with label and example is far from decision boundary on confident examples, label likely wrong. Run before each retraining cycle, route flagged labels to re-annotation
- **Data Versioning (DVC / Delta Lake)** -- DVC: git-LFS-like for datasets, metadata in git, large files in S3. Delta Lake / Iceberg: ACID table formats with time travel, query table as of any past timestamp. Production standard at Netflix, Apple, Uber. Every label should carry (annotator_id, timestamp, schema_version, adjudication_path, gold_set_match) as provenance
- **Label Leakage via Model Predictions** -- Labeling UI shows model prediction as hint to speed annotators up. Annotators anchor on model's prediction, confirm 90% of time, labels converge to model's own predictions, retraining does not move model. Fix: never show model predictions to annotators on first pass, only for adjudication of ambiguous cases

### MLOps Platform Design

| Area | Description | Proficiency Expectation |
|------|-------------|------------------------|
| CI/CD Gate Ladder | 8-gate sequence: data validation -> feature parity -> reproducibility -> offline eval -> slice/fairness -> performance/latency -> shadow eval -> canary. Each gate has explicit threshold and owner/override path. ML CI/CD requires gate ladder (not pass/fail) because quality is statistical not boolean | Design full CI/CD gate ladder with thresholds and owners; explain why software CI/CD does not work for ML (artifact depends on data, quality is statistical, production behavior differs from build time) |
| Orchestrator Selection | Airflow (scheduling power, poor GPU isolation), Kubeflow (K8s-native, per-step containers, native GPU), Metaflow (best DS experience, AWS-first), Prefect (modern Pythonic), Argo Workflows (lightweight K8s primitives). At scale: use multiple orchestrators connected by sensors | Choose orchestrator by team structure and infrastructure; defend each tool by actual strengths; explain why forcing everything into one orchestrator is a mistake |
| Auto-Rollback Design | Rollback is load balancer weight change (not re-deploy), target RTO <5 minutes. Triggers: latency p99 >1.5x SLA for 5 min, guardrail metric drop >0.5pp for 30 min, error rate >0.5% for 2 min, PSI >0.25, cost anomaly >50% for 10 min. Sticky sessions are the rollback killer | Design auto-rollback with specific triggers and RTO; explain why rollback is traffic routing not redeploy; warn about sticky sessions unprompted |
| Multi-Tenant Platform | Namespacing (org/team/project scope), RBAC (viewer/experimenter/model_owner/production_owner/compliance_reviewer), quotas (GPU hours, registry entries, training jobs), cost attribution (cost_center + owner_team per resource), audit logs (7-year retention for regulated industries), paved-road not service-org | Design multi-tenant platform with RBAC and cost attribution; explain four-eyes principle for regulated industries; argue for paved-road over service-org model |

- Design an MLOps platform for 200 data scientists with 1,000 production models in a HIPAA-regulated context.
- Walk through what happens from a data scientist's commit to fully rolled-out deployment. What gates fire at each step?
- A bad model deployment caused $200K loss. Design platform changes to prevent recurrence.
- Compare Airflow, Kubeflow, Metaflow, and Argo Workflows for ML pipeline orchestration. When would you use each?

- **ML CI/CD vs Software CI/CD** -- Software CI/CD assumes deterministic builds. ML breaks this: (1) artifact depends on data not just code, (2) quality is statistical not boolean (AUC improved 0.3% but degraded 1.2% on over-50 demographic), (3) production behavior depends on serving inputs that do not exist at build time. ML CI/CD compensates with gate ladder, each gate capable of halting promotion
- **Data Validation Gate** -- Schema, null rates, distribution drift vs last training run, future leakage, label distribution. Tools: Great Expectations, TFDV, Deequ. Run-time: seconds. Catches: upstream ETL bugs, silent schema changes. Always build as gate 1
- **Feature Parity Gate** -- Compare feature computed by Spark to same feature served from Redis on same entity-timestamp. Threshold: <0.1% mismatch on numeric features. Catches: training-serving skew before it ships
- **Slice / Fairness Gate** -- Per-slice AUC must not drop >2pp absolute. No slice regression beyond threshold. Tools: Fairlearn, What-If Tool, Aequitas. Owner: model risk officer. Bypass requires written exception
- **Shadow Eval Gate** -- Deploy as shadow, score real traffic for 24-48 hours, KS test vs production. Block if KS p-value <0.01 with non-trivial divergence. Catches: real-world distribution mismatch, integration bugs
- **Auto-Rollback Triggers** -- (1) Latency SLA breach: p99 >1.5x SLA sustained 5+ min, (2) Guardrail business metric drop: >0.5pp absolute for 30+ min, (3) Error/exception spike: >0.5% for 2+ min, (4) Drift trigger: feature PSI >0.25 or prediction PSI >0.2, (5) Cost anomaly: >50% above budget for 10+ min, (6) Calibration drift: Brier score regression >10%
- **Rollback Mechanism** -- Previous Production version stays warm in serving cluster. Rollback is load balancer weight change (<30 seconds RTO). New version stays loaded in case trigger was false positive. Sticky sessions are the rollback killer: weight change will not move existing user sessions
- **Multi-Tenant RBAC** -- Roles: viewer, experimenter (can train, cannot promote to Prod), model_owner (can promote to Staging), production_owner (can promote to Prod), compliance_reviewer (read-only, can sign off). Production transitions require at least 2 distinct roles (four-eyes principle) for regulated industries
- **Cost Attribution** -- Every resource tagged with cost_center and owner_team. Costs flow to FinOps dashboards. Build from day 1: cost attribution is the single most-requested feature from finance and most-skipped by engineering
- **Platform Failure Modes** -- Registry without lineage (cannot answer what data trained the model), CI/CD without data validation (model trains on garbage and passes eval), no prod-like staging (latency profiles differ), central platform team becomes bottleneck (fix: paved-road not service-org), manual approvals everywhere (fix: risk-tiered approvals)
- **Production Edge Cases** -- Feedback-loop retraining bug (model collapses to recommending only items it promoted), unregistered feature usage (serving substitutes defaults silently), sticky-session rollback bug (users keep hitting bad model), audit trail gap (predictions during rollback not captured), dependency-drift silent failure (Docker :latest tag breaks CUDA), lineage-gap reproducibility failure (training data deleted under retention policy)

### Privacy-Preserving ML

| Area | Description | Proficiency Expectation |
|------|-------------|------------------------|
| Federated Learning (FL) | FedAvg (McMahan 2017): train locally on device for E epochs, send gradient updates to server, server aggregates and broadcasts. Protects data centralization risk. Challenges: non-IID data (FedProx, SCAFOLD), straggler clients (deadline-based aggregation, over-selection), communication cost (top-k sparsification) | Design FL system with correct hyperparameters; explain FedProx for non-IID; handle straggler and communication challenges |
| Differential Privacy (DP) | DP-SGD (Abadi 2016): clip per-sample gradients, add Gaussian noise calibrated to epsilon. Privacy-accuracy tradeoff: epsilon=8 costs 2-5pp, epsilon=3 costs 5-10pp, epsilon=1 costs 8-15pp. Privacy accountant tracks budget over training. When NOT to use: datasets <10K records (noise drowns signal) | Explain DP-SGD mechanism; choose epsilon for given accuracy constraint; use privacy accountant; name when DP is inappropriate |
| Secure Aggregation | Bonawitz 2017: pairwise masking via Diffie-Hellman key exchange so server computes sum of client updates without seeing individuals. Shamir secret sharing handles client dropouts (up to 30%). Cost: ~2x bandwidth, ~5x client compute. Used by Google Gboard | Explain pairwise masking mechanism; handle client dropouts; justify when secure aggregation is needed beyond FL alone |
| On-Device Inference | Model runs locally, user data never leaves device. Runtimes: CoreML (Apple ANE), TFLite (Android NNAPI), ExecuTorch (Meta), MLC LLM / llama.cpp (on-device LLMs). Constraints: <50MB model, <1GB RAM, <200M params INT8. Apple Neural Engine: ResNet-50 INT8 ~10-15ms, BERT-base INT8 ~20-30ms | Size models for mobile constraints; choose runtime by platform; quantize for mobile deployment; explain when on-device inference alone is sufficient |

- Design a privacy-preserving keyboard next-word prediction model for 1B users. Walk through FL + DP + on-device tradeoffs.
- Your medical imaging model needs DP at epsilon=1 but accuracy drops 8pp. Design the system to recover accuracy.
- Your FL system improves on power-user benchmarks but degrades on casual-user benchmarks. Diagnose and fix.
- When should you use on-device inference alone vs FL vs FL+DP vs the full stack?

- **Federated Learning (FedAvg)** -- McMahan et al., 2017. Each round: server sends global model to selected clients (e.g., 100-10K devices), clients train locally for E epochs (typically 5) on their private data, clients send gradient updates (not raw data) to server, server aggregates via weighted average and broadcasts new global model. Protects data centralization but server still sees individual gradient updates
- **FedProx** -- Adds proximal term mu/2 * ||w - w_global||^2 to local objective. Prevents local models from drifting too far from global when client data distributions are highly non-IID. mu=0.01 is a typical starting value. Required when doctor's phone and teenager's phone produce wildly different gradients
- **DP-SGD (Differentially Private SGD)** -- Abadi et al., 2016. (1) Compute per-sample gradients, (2) clip each gradient to max norm C (bounds influence of any single example), (3) aggregate clipped gradients, (4) add Gaussian noise calibrated to (C, sigma) to aggregated gradient, (5) take optimizer step. Privacy accountant (Renyi DP or moments accountant) tracks cumulative epsilon over all training steps
- **Privacy-Accuracy Tradeoff** -- epsilon >= 50: marketing claim only; epsilon=8: moderate, ~2-5pp accuracy drop (Google FL+DP defaults); epsilon=3: moderate-strong, ~5-10pp (healthcare research); epsilon=1: strong, ~8-15pp (Apple telemetry); epsilon <= 0.5: very strong, ~15-30pp (US Census 2020). Lower epsilon = more noise = less accuracy
- **Secure Aggregation (Bonawitz 2017)** -- Pairwise masking via Diffie-Hellman key exchange: each pair of clients agrees on random shared mask, client adds masks to update before sending, masks cancel out when server sums all updates. Shamir secret sharing handles client dropouts (tolerance up to 30%). Production protocol for Google Gboard FL
- **On-Device Inference Stack** -- CoreML (Apple, ANE 11-35 TOPS), TFLite (Android, NNAPI), ONNX Runtime Mobile (cross-platform), ExecuTorch (PyTorch-native mobile), MLC LLM/llama.cpp (on-device LLMs, 3B-8B via INT4). Quantization: FP16 (2x smaller, near-zero loss), INT8 (4x, ~0.5-1pp loss, production standard), INT4/AWQ (8x, 1-3pp loss for LLMs)
- **Privacy Failure Modes** -- (1) Server-side prediction logging defeats on-device privacy (audit telemetry pipeline), (2) k-anonymity false security (87% of Americans identifiable from ZIP+DOB+gender, Sweeney 2000), (3) LLM memorization (Carlini et al. 2021, models emit training data verbatim under crafted prompts), (4) non-IID FL data corrupts global model (use FedProx/SCAFFOLD), (5) privacy budget exhaustion mid-training (plan budget ahead, not during), (6) side channels in on-device inference (timing, output size leak predictions)
- **Membership Inference** -- Attacker determines if a record was in training set. Shokri et al. 2017: >70% accuracy on overfitted models. Mitigation: DP (any epsilon <10 substantially reduces), regularization, never release training loss curves with model
- **Gradient Leakage (Zhu et al. 2019)** -- For small batches (<8) and unprotected gradients, attacker reconstructs original training images from gradients with near-pixel-perfect fidelity. Mitigation: secure aggregation, DP, local batch sizes >32, gradient clipping
- **Trust Model Decision Matrix** -- On-device inference alone: model trained on public data, inference data is sensitive (Apple Photos). FL alone: server trusted, threat is data centralization (hospital consortium). FL + secure aggregation: server semi-honest (Gboard). FL + DP: strong individual guarantee required (Apple keyboard). FL + DP + on-device: maximum privacy end-to-end (regulated industries). Frame decision as four-level threat model: centralized data (FL defends), gradient access (secure aggregation defends), model release attacks (DP defends), serving-time queries (on-device defends)

## Sources

- [Bias-Variance Tradeoff & ML Debugging (CalibreOS)](https://www.calibreos.com/learn/ml-bias-variance)
- [Feature Engineering: Leakage-Safe Encoding, Interactions, Temporal, and Production Parity (CalibreOS)](https://www.calibreos.com/learn/ml-feature-engineering)
- [Imbalanced Classification: Metrics, Class Weights, SMOTE, and Threshold Tuning (CalibreOS)](https://www.calibreos.com/learn/ml-imbalanced-classification)
- [Regularization in ML: Controlling Variance Without Killing Signal (CalibreOS)](https://www.calibreos.com/learn/ml-regularization)
- [How to Approach an ML Interview Round at FAANG (CalibreOS)](https://www.calibreos.com/learn/ml-how-to-approach)
- [Loss Functions: Choosing the Right Objective for Every ML Problem (CalibreOS)](https://www.calibreos.com/learn/ml-loss-functions)
- [Model Serving Architectures: Batch vs Real-Time, Shadow Deployments & Latency Budgets (CalibreOS)](https://www.calibreos.com/learn/mlsd-model-serving-architectures)
- [Offline vs Online Evaluation: Why Metrics Disagree and What to Do About It (CalibreOS)](https://www.calibreos.com/learn/mlsd-offline-online-evaluation)
- [Data Labeling Systems: Quality, Agreement, and the Flywheel (CalibreOS)](https://www.calibreos.com/learn/mlsd-data-labeling-systems)
- [MLOps Platform Design: Registry, CI/CD, and Production Safety (CalibreOS)](https://www.calibreos.com/learn/mlsd-mlops-platform)
- [Privacy-Preserving ML: Federated Learning, Differential Privacy & On-Device Inference (CalibreOS)](https://www.calibreos.com/learn/mlsd-privacy-preserving-ml)
- [Optimization & Training: SGD to AdamW, Learning Rate Scheduling, and Gradient Flow (CalibreOS)](https://www.calibreos.com/learn/ml-optimization-training)
- [Recommendation Fundamentals: Retrieval, Ranking, and Evaluation (CalibreOS)](https://www.calibreos.com/learn/ml-recommendation-fundamentals)
- [A/B Testing & Experimentation at Scale (CalibreOS)](https://www.calibreos.com/learn/ml-ab-testing)
- [XGBoost: Gradient Boosting Deep Dive (CalibreOS)](https://www.calibreos.com/learn/ml-xgboost)
- [Neural Networks: Backpropagation, Activations & Training (CalibreOS)](https://www.calibreos.com/learn/ml-neural-networks)
- [RNNs, LSTMs & GRUs: Sequence Models Before Transformers (CalibreOS)](https://www.calibreos.com/learn/rnn-lstm-gru)
- [Transformers: Self-Attention, Architecture & Modern LLMs (CalibreOS)](https://www.calibreos.com/learn/ml-transformers)
- [Bootstrap & Resampling: Uncertainty for Arbitrary Statistics (CalibreOS)](https://www.calibreos.com/learn/bootstrap-resampling)
- [Probability Distributions: The Production ML Engineer's Reference (CalibreOS)](https://www.calibreos.com/learn/ml-distributions)
- [Hypothesis Testing for Data Scientists: p-values, Type I/II, Multiple Testing (CalibreOS)](https://www.calibreos.com/learn/ml-hypothesis-testing)
- [Statistics & Probability Foundations (CalibreOS)](https://www.calibreos.com/learn/ml-stats-foundations)
- [Agent Memory Systems: In-Context, Semantic, Episodic, and Procedural (CalibreOS)](https://www.calibreos.com/learn/genai-memory-systems)
- [Instruction Tuning: Teaching LLMs to Follow Instructions (CalibreOS)](https://www.calibreos.com/learn/genai-instruction-tuning)
- [Embeddings: From word2vec to Instruction-Tuned Vectors & Production RAG (CalibreOS)](https://www.calibreos.com/learn/genai-embeddings)
- [Structured Outputs: Grammar-Constrained Decoding and Guaranteed JSON Generation (CalibreOS)](https://www.calibreos.com/learn/genai-structured-outputs)
- [Tokenization, BPE, WordPiece, SentencePiece & Production Artifacts (CalibreOS)](https://www.calibreos.com/learn/genai-tokenization)
- [Prompt Engineering: From Zero-Shot to Production Systems (CalibreOS)](https://www.calibreos.com/learn/genai-prompt-engineering)
- [AI Agents & Agentic Systems Framework (CalibreOS)](https://www.calibreos.com/learn/ai-agents-framework)
- [Multi-Agent Systems: Orchestration, LangGraph, and Production Patterns (CalibreOS)](https://www.calibreos.com/learn/genai-multi-agent)
- [LLM Fine-Tuning: LoRA, QLORA, PEFT & RLHF (CalibreOS)](https://www.calibreos.com/learn/genai-finetuning)
- [Chain-of-Thought, Test-Time Compute & Multi-Step Reasoning (CalibreOS)](https://www.calibreos.com/learn/genai-chain-of-thought)
- [Structured Output, Function & Tool Calling, JSON Schema, Strict Mode, Agent Safety (CalibreOS)](https://www.calibreos.com/learn/genai-function-calling)
- [LLM Evaluation & Benchmarking, HELM, MMLU, MT-Bench, Arena, LLM-as-Judge (CalibreOS)](https://www.calibreos.com/learn/genai-llm-evaluation)
- [LLM Fundamentals, Transformers, Attention & Architecture (CalibreOS)](https://www.calibreos.com/learn/genai-llm-foundations)
- [How to Approach a GenAI / LLM System Interview (CalibreOS)](https://www.calibreos.com/learn/genai-how-to-approach)
- [How to Design GenAI Systems: From Blank Whiteboard to Production (CalibreOS)](https://www.calibreos.com/learn/genai-how-to-design)
- [Advanced RAG: Hybrid Retrieval, Reranking, and Production Architecture (CalibreOS)](https://www.calibreos.com/learn/genai-advanced-rag)
- [Hybrid Search: BM25 + Dense Retrieval with RRF and Cross-Encoder Reranking (CalibreOS)](https://www.calibreos.com/learn/genai-hybrid-search)
- [RAG Architecture: From Basics to Production (CalibreOS)](https://www.calibreos.com/learn/genai-rag-architecture)
- [LLM Guardrails and Safety: Input/Output Filters, Red-Teaming, and Constitutional AI (CalibreOS)](https://www.calibreos.com/learn/genai-guardrails-safety)
- [LLM Observability & Monitoring: Traces, Cost and Latency SLOs, Eval Harnesses, and Alerting (CalibreOS)](https://www.calibreos.com/learn/genai-llm-observability)
- [LLM Serving at Scale: vLLM, KV Cache, Batching, and LLMOps (CalibreOS)](https://www.calibreos.com/learn/genai-llm-serving)
- [LLM Quantization: INT4/INT8, GPTQ, AWQ, and bitsandbytes (CalibreOS)](https://www.calibreos.com/learn/genai-quantization)
- [Data Pipelines for ML: Batch, Streaming, and Event Architecture (CalibreOS)](https://www.calibreos.com/learn/mlsd-data-pipelines)
- [Embeddings & Vector Databases: ANN Search at Scale (CalibreOS)](https://www.calibreos.com/learn/mlsd-embeddings-vector-db)
- [ML Model Evaluation & Production Monitoring: Shadow Mode, A/B Testing & Rollback (CalibreOS)](https://www.calibreos.com/learn/mlsd-evaluation-monitoring)
- [Feature Stores: Online/Offline Architecture & Training-Serving Consistency (CalibreOS)](https://www.calibreos.com/learn/mlsd-feature-stores)
- [ML Model Deployment Fundamentals: Shipping Safely in Production (CalibreOS)](https://www.calibreos.com/learn/mlsd-model-deployment)
- [Two-Stage Retrieval & Ranking: The Architecture Behind Every Large-Scale Recommender (CalibreOS)](https://www.calibreos.com/learn/mlsd-two-stage-retrieval)
- [How to Approach an ML System Design Interview (CalibreOS)](https://www.calibreos.com/learn/mlsd-how-to-approach)
- [How to Design ML Systems: From Requirements to Production Architecture (CalibreOS)](https://www.calibreos.com/learn/mlsd-how-to-design)
- [ML Fairness and Bias: Metrics, Trade-offs, and Mitigation Strategies (CalibreOS)](https://www.calibreos.com/learn/mlsd-fairness-bias)

## Cross-References

- **System Design**: [Search Autocomplete](../../system_design/search_autocomplete/) (ranking models, ML inference), [News Feed](../../system_design/news_feed/) (recommendation models), [Recommender System](../../system_design/recommender_system/) (two-tower retrieval, multi-stage ranking, cold-start), [Notification Service](../../system_design/notification_service/) (send-time optimization)
- **CS Fundamentals**: Algorithms (gradient descent, dynamic programming), Linear Algebra (matrices, vectors), Probability & Statistics (distributions, hypothesis testing), Optimization

---

## Two-Stage Retrieval & Ranking

The fundamental tension in large-scale recommendation: you want to find the most relevant items from a corpus of 100M-1B items for each user, but you cannot afford to run an expensive model on all of them per request. At YouTube scale (2B users, 800M videos), scoring one video takes 0.1ms, so scoring all 800M takes 22 hours per request -- the brute-force impossibility.

The only solution is a **cascade of stages** where each stage dramatically narrows the candidate set before the next, more expensive stage. This is the two-stage (or multi-stage) retrieval-ranking pattern. The trade-off at each stage is **recall vs precision**: retrieval optimizes for recall (must not miss any item the user would love), ranking optimizes for precision (must put the best items at the top). Items not retrieved cannot be ranked, so retrieval quality is the ceiling.

Retrieval is evaluated on Recall@K; ranking is evaluated on NDCG@10 or Precision@1.

### The Two-Tower Model

The dominant architecture for the retrieval stage. It imposes one fundamental constraint: **the user tower and item tower never share computation until the final dot product**. This enables precomputing item embeddings offline (run over all 800M items once per day, store in FAISS index). At serving time, only the user tower runs (one forward pass per request), then ANN search retrieves the 1000 closest item embeddings.

If user and item towers interacted (cross-features, cross-attention), you would need to run the full model for every user-item pair -- back to brute-force impossibility. What the two-tower sacrifices: cross-features. The ranking model can use features like "has user previously viewed this creator's content?" because it only runs on 200 candidates.

Training objective: softmax(dot(u, i+) / sum(dot(u, i-))). Positive: engaged item. Negatives: randomly sampled non-engaged items.

### In-Batch Negatives and Hard Negative Mining

**In-batch negatives**: In a batch of B positive (user, item) pairs, treat all other items in the batch as negatives for each user. A batch of 1024 generates ~1M negative pairs for free. The similarity matrix is BxB; diagonal = positive similarities, off-diagonal = negatives.

**Popularity bias problem**: Popular items appear more often in batches and become negatives more frequently. Fix: LogQ correction -- subtract log(item_frequency) from dot product score before softmax.

**Hard negative mining**: Random negatives are too easy. Hard negatives: items the user viewed but did NOT engage with (scrolled past), or items retrieved but not engaged. Standard production ratio: 1 positive : 1 hard negative : 4-8 random negatives. Too many hard negatives causes training divergence.

### Retrieval vs Ranking: Key Differences

| Dimension | Retrieval (Two-Tower) | Pre-Ranker | Heavy Ranker |
|-----------|----------------------|------------|--------------|
| Input size | 100M-1B items -> 1000 | 1000 -> 200 | 200 -> 50 |
| Model type | Dual encoder (no cross-features) | LightGBM / shallow MLP | DLRM / DIN / Transformer |
| Cross-features | Not possible (decomposable) | Simple pair features | Rich attention across user-item |
| Latency | < 20ms (ANN search) | < 15ms (CPU) | < 80ms (GPU) |
| Primary metric | Recall@1000 > 95% | NDCG@200 | NDCG@10 / Precision@1 |

### Ranking Models: DIN, DLRM, Multi-Task Learning

**Deep Interest Network (DIN, Alibaba 2018)**: Uses attention to weight user's historical interactions by relevance to the current candidate item. Computes attention_score = f(item_embedding, historical_item_embedding). Weighted sum of historical embeddings is the user's contextualized representation.

**DLRM (Meta 2019)**: Standard architecture for CTR prediction. Embeds sparse features via embedding tables (terabytes at Facebook-scale). Combines with dense features via FC layers. Feature interactions via dot products between embedding pairs.

**Multi-task learning**: Train one model to predict CTR, CVR, watch time simultaneously. Prevents gaming a single metric (CTR-only = clickbait). Loss = w1*CTR_loss + w2*CVR_loss + w3*watch_time_loss. Tune weights to align with business objective.

### Exposure Bias / Feedback Loop Trap

The most dangerous failure mode: model recommends items -> those items get shown -> they get clicks -> training positives -> model recommends them more. Items never shown get no clicks -> never become training positives. Self-reinforcing feedback loop collapses diversity.

**Symptom**: offline metrics (NDCG) improve while online metrics (diversity, long-session CTR) degrade.

**Fixes**: (1) Exploration: route 5-10% traffic to exploratory policy (epsilon-greedy, Thompson Sampling). (2) Counterfactual learning: use inverse propensity scoring (IPS) to down-weight frequently-shown items. (3) Don't use non-randomized impression data as training data -- it encodes the previous model's bias.

### Production Retrieval Sources

Production systems never use a single retrieval source. Use 3-5 sources: collaborative filtering (two-tower ANN, strongest personalization), content-based (item metadata similarity, handles cold start), trending/popular (recent high-engagement items), session-based (current session engagement, highest recency signal), social graph (connections' engagement). Merge candidates, deduplicate, then rank.

**New item cold start**: Content-based retrieval using metadata embeddings handles the first 24-48 hours. Add a "new item promotion" source injecting recently added items regardless of predicted score.

### Interview Answer Template

Structure as a cascade: "I'd build a 4-stage pipeline. Stage 1: Two-tower retrieval, user tower embeds real-time signals, item tower precomputed daily for all 100M items in FAISS IVF index, ANN search retrieves top-1000 in ~20ms, Recall@1000 target 95%. Stage 2: LightGBM pre-ranker reduces to 200 on CPU in ~15ms with simple cross-features. Stage 3: Neural ranker (DIN-style transformer) on 200 candidates with GPU in ~60ms, multi-task: CTR, CVR, watch time. Stage 4: Post-processing for diversity, freshness boost, safety filtering, business rules. Feedback loop mitigation: train on stratified impressions with IPS debiasing, route 5% traffic to exploration pool."

- Your ranking stage returns 1000 candidates. How do you design a ranker that maximizes long-term satisfaction, not just CTR?
- How do you train the retrieval tower when you only have implicit positive signals (clicks) and no explicit negatives?
- The light ranker returns 200 candidates to the heavy ranker. How do you know if 200 is the right number? What's the tradeoff?
- Your recommender's NDCG improves but diversity drops. What is the most likely root cause and how do you fix it?
- How do you handle the exposure bias feedback loop in a production recommender system?

Source: [Two-Stage Retrieval & Ranking: The Architecture Behind Every Large-Scale Recommender (CalibreOS)](https://www.calibreos.com/learn/mlsd-two-stage-retrieval)

---

## ML System Design Interview Approach

### The 4-Question Framework (First 5 Minutes)

1. **Problem type**: Is this ranking, classification, regression, clustering, or generative? This determines model family, metrics, and serving architecture. If you start designing without confirming, you risk solving the wrong problem.
2. **Scale and latency**: How many predictions per second? What is the latency budget? This rules in/out model architectures (BERT at 100ms+ inference cannot serve at 50ms P99 SLA).
3. **Data availability**: How much labeled data? How often does it arrive? Is there a feedback loop (labels from user behavior)? This determines training strategy and whether deep learning is feasible.
4. **Business metrics**: What does success look like in business terms? Accuracy is never the business metric. The business metric is revenue, engagement, fraud prevented, or cost saved. Map the ML metric to the business metric explicitly.

### Time-Budgeting the 45-Minute Interview

- Minutes 0-5: Ask clarifying questions (the 4-question framework), get scope and constraints.
- Minutes 5-7: Propose a roadmap. State what you will cover and in what order. Hand the interviewer a redirect opportunity.
- Minutes 7-20: Data pipeline and feature store design. Training data generation, feature definitions, point-in-time correctness, training-serving skew prevention.
- Minutes 20-35: Model architecture deep dive. The interviewer's preferred focus area. Design retrieval and ranking stages, model selection with justification.
- Minutes 35-42: A/B testing, monitoring, failure modes. How to deploy safely, what to monitor, what can go wrong.
- Minutes 42-45: Summary, trade-offs, what you would do differently with more time.

### Interview Questions

- An interviewer says "design a recommendation system for an e-commerce product page." Walk through everything you would do in the first 5 minutes.
- You are 30 minutes into a 45-minute MLSD interview. You designed retrieval and ranking but haven't covered A/B testing, monitoring, or training-serving skew. What do you do?
- An interviewer asks "why didn't you use BERT or a transformer?" How do you handle pushback without being defensive?
- How do you handle an MLSD interview where the prompt is intentionally vague?
- Your interviewer is silent and lets you talk for 30 minutes without interruption. How do you avoid losing signal?

Source: [How to Approach an ML System Design Interview (CalibreOS)](https://www.calibreos.com/learn/mlsd-how-to-approach)

---

## ML System Design in Depth

### Training-Serving Skew: The Math

The single dominant failure mode in production ML. If P_train(x) != P_serve(x) due to feature-computation differences, the model's accuracy on the serving distribution is bounded above by 1 - TV(P_train, P_serve), where TV is total variation distance. A 10% TV between training and serving features can drop AUC by 5-15 points with no error in either pipeline -- silent failure.

**Three causes**: (1) Different code paths: training uses pandas+Python (NaN), serving uses Java+Spark (0 after coalesce). (2) Different data sources: training pulls from warehouse (rounded timestamps), serving reads from Redis (raw timestamps). (3) Time zone drift: training computes in UTC, serving uses local time.

**Fix**: Feature store with shared definitions. Same Python/SQL function registered once, runs in Spark for offline training and Flink for online streaming. Same code = same features = no skew. Name production systems: Uber Michelangelo, Airbnb Zipline, Meta FBLearner, Feast.

### A/B Testing for ML Systems

**Sample size**: For proportions (CTR): n = 2*sigma^2*(z_alpha/2 + z_beta)^2 / delta^2. Rule of thumb: at baseline rate p with relative MDE r, n ~ 16*p*(1-p)/(p*r)^2 per variant. Example: p=5% CTR, r=2% relative MDE: n ~ 760K per variant.

**PSI for feature drift**: PSI = sum(P_actual - P_expected) * log(P_actual / P_expected). Bin into 10 deciles. Thresholds: < 0.1 stable, 0.1-0.2 moderate, > 0.2 significant drift requiring investigation.

**Concept drift**: Feature drift is necessary but not sufficient. Concept drift (P(y|x) changing) requires labels. Backfill labels as they arrive (clicks instant, purchases 1-7 days, fraud chargebacks ~30 days). Alert if metric drops > 5% absolute or 10% relative.

**Auto-rollback**: Track primary online KPI in 5-minute windows. If new variant drops > 2% relative for 3 consecutive windows AND z > 2, auto-rollback without human approval.

**Retraining triggers**: (1) Scheduled: weekly batch on rolling 90-day window. (2) Threshold: retrain if PSI > 0.3 on top 5 features for 3 days, or KPI drops > 2% for 24 hours. (3) Event-based: major product launch, holiday, regulatory change.

**Shadow deployment**: Run new model on production traffic, log predictions but don't use them. Compare prediction distribution vs baseline. Typical window: 1-7 days. Catches regressions before any user is affected.

### Worked Example: Real-Time Fraud Detection

Requirements: 10K TPS peak, 50ms latency budget, 1% fraud rate, regulatory explanation requirement.

**Problem type**: Binary classification with asymmetric cost (FN ~$1000, FP ~$50, ratio ~20:1).

**Metrics**: Offline PR-AUC (99% imbalance makes AUC misleading). Online: fraud loss prevented ($), FPR on legitimate transactions, P99 latency. Guardrails: FPR cannot increase > 0.5pp.

**Scale**: 50ms total = 10ms feature fetch (Redis) + 20ms model inference + 10ms post-processing + 10ms cushion. Rules out BERT without distillation.

**Model**: XGBoost, ~200 features, scale_pos_weight=99. Why XGBoost: sub-ms CPU inference at 10K TPS, SHAP explanations (regulatory requirement), handles NaN natively, interpretable for fraud analysts. Ensemble model for uncertain cases (score 0.3-0.7).

**A/B test**: Randomize by merchant_id (not user_id), 5%/95% split. Primary: fraud loss prevented per $1M GMV. Guardrails: FPR < baseline + 0.5pp. ~5 days at 10K TPS.

**Failure modes**: (1) Adversarial drift -- fraudsters adapt to model, weekly retraining mandatory. (2) Feedback loop -- declined transactions never get "legitimate" label; mitigation: random 0.1% acceptance for counterfactual data. (3) Seasonal patterns -- Black Friday looks like fraud; deploy seasonal model variant.

Source: [How to Design ML Systems: From Requirements to Production Architecture (CalibreOS)](https://www.calibreos.com/learn/mlsd-how-to-design)

---

## ML Fairness and Bias

Fairness in ML systems is a first-class engineering problem, not just a policy concern. High aggregate accuracy hides sliced failure: a 92% headline number can still ship elevated error rates for a protected group in lending, missed diagnoses in medicine, or biased rankings in hiring.

### Why Fairness Is an Engineering Problem

- Bias enters through data, not just model design: historical data contains human biases that the model learns and amplifies
- Fairness metrics conflict mathematically: you cannot simultaneously satisfy demographic parity, equalized odds, and calibration (Chouldechova 2017)
- The choice of fairness metric is a policy decision with legal implications (GDPR, EEOC, ECOA)

### Fairness Metric Definitions

**Demographic Parity (Statistical Parity)**: P(y_hat=1 | A=0) = P(y_hat=1 | A=1). Positive prediction rate must be equal across groups. Use when: anti-discrimination law requires equal selection rates (EEOC 80% rule). Problem: ignores true label Y entirely.

**Equalized Odds (Hardt et al., 2016)**: TPR(A=0) = TPR(A=1) AND FPR(A=0) = FPR(A=1). Use when: cost of FP and FN must be equal across groups (medical screening, fraud detection). Equal Opportunity is a relaxation: only equal TPR.

**Calibration**: P(Y=1 | y_hat=p, A=0) = P(Y=1 | y_hat=p, A=1). For any predicted score p, actual positive rate must be same across groups. Use when: model score is used for resource allocation (credit scores, recidivism risk).

**Individual Fairness (Dwork et al., 2012)**: Similar individuals should receive similar predictions. Use when: group-level definitions are insufficient. Hard in practice: requires defining task-specific similarity metric.

### Fairness Metrics Incompatibility

| Metric | Compatible With | Incompatible With | Legal Framework |
|--------|----------------|-------------------|----------------|
| Demographic Parity | Individual Fairness (sometimes) | Calibration, Equalized Odds (when base rates differ) | EEOC 80% rule, HUD consent decree |
| Equalized Odds | Equal Opportunity (relaxation) | Calibration, Demographic Parity (when base rates differ) | FDA guidance |
| Calibration | None (when base rates differ) | Demographic Parity, Equalized Odds (Chouldechova 2017) | ECOA, risk assessment regulations |

### Bias Sources Across the ML Pipeline

1. **Historical bias**: Training data reflects past human decisions that were biased. Amazon resume screening tool (2014-2017) penalized resumes containing "women's" and downranked all-women's colleges.
2. **Selection bias**: Who is in the dataset? Credit models trained on applicants exclude people who self-selected out. Medical models trained on hospital data exclude people who couldn't afford care.
3. **Measurement bias / Proxy features**: Zip code is a strong proxy for race in the US. Google's 2019 audit found zip code in credit models created 0.18 demographic parity gap. Removing it and using lat/long didn't fix the problem due to geographic clustering.
4. **Label bias**: Labels from human decisions (loan approvals, hiring) carry those biases. Meta's 2021 fairness audit found promotion prediction models amplified existing gender gaps.
5. **Evaluation bias**: Evaluating on unrepresentative benchmarks. Gender Shades study (2018): facial recognition accuracy ~65-80% for dark-skinned women vs >99% for light-skinned men.
6. **Deployment bias**: Model used differently than designed. COMPAS recidivism scores calibrated for Broward County were adopted in other jurisdictions with different base rates.

### Mitigation Strategies

**Pre-processing (before training)**:
- Reweighting: assign higher sample weights to under-represented groups (LinkedIn talent search uses inverse propensity weighting)
- Resampling: oversample minority groups (risk of overfitting on minority)
- Counterfactual data augmentation: flip protected attribute while keeping other features constant, train model to predict same outcome
- Feature removal: remove proxies. Ablation test: if AUC for predicting protected attribute from remaining features > 0.7, you have redundant proxies
- Label correction: use confident learning (Northcutt et al., 2021) to identify and fix biased labels

**In-processing (during training)**:
- Constrained optimization: maximize AUC subject to |FPR(A=0) - FPR(A=1)| <= 0.03. TensorFlow TFCO provides this. Training 10-30% slower.
- Adversarial debiasing: train adversary to predict protected attribute from hidden representations; train main model to minimize adversary's ability. Microsoft Research (2018) applied to word embeddings.
- Fairness-aware loss: L = L_accuracy + lambda * |TPR(A=0) - TPR(A=1)|. Grid search over lambda and plot Pareto frontier.

**Post-processing (after training)**:
- Threshold adjustment: use different decision thresholds per group to achieve equalized FPR or demographic parity. Google ad delivery uses group-specific thresholds for job/housing ads (2019 HUD settlement).
- Calibration scaling: apply Platt scaling or isotonic regression separately per group.
- Reject option classification: defer predictions near decision boundary (e.g., 0.45-0.55) to human review.

**Trade-off summary**: Pre-processing is easiest but doesn't guarantee fairness. In-processing is mathematically strongest but slower. Post-processing is fast to iterate (no retraining) but doesn't address root cause.

### The Fairness-Accuracy Trade-off Frontier

Fairness interventions typically reduce accuracy. Plot the Pareto frontier: for each fairness metric value, what is the maximum achievable accuracy? Present options to stakeholders. The business must decide how much accuracy to sacrifice for fairness gains.

Production example: Apple Card (2019) credit limit algorithm was accused of gender discrimination. The model likely used features like employment history gaps (correlated with maternity leave) as proxies.

### Production Fairness Monitoring

Track per-group metrics weekly: TPR, FPR, demographic parity gap, calibration error per group. Alert on > 3% gap in any metric. Check intersectional fairness (subgroup-level, not just aggregate). Retrain and re-audit quarterly or when drift is detected.

### Interview Questions

- A credit scoring model is calibrated overall but has higher FPR for one racial group. Which fairness metric does this violate, and what are two ways to fix it?
- You discover that zip code is a proxy for race in your lending model. Removing it drops accuracy by 5%. What do you do?
- Can you satisfy both demographic parity and calibration simultaneously when base rates differ? Prove your answer.
- How do you detect proxy discrimination when you cannot access the protected attribute at inference time?
- Your model has equal accuracy across groups but very different false positive rates. Is it "fair"? What framework do you use to decide?

Source: [ML Fairness and Bias: Metrics, Trade-offs, and Mitigation Strategies (CalibreOS)](https://www.calibreos.com/learn/mlsd-fairness-bias)
