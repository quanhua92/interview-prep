# ML/AI Engineer

Building, evaluating, and deploying machine learning models that solve real-world problems reliably and at scale.

## Core Competencies

| Area | Description | Proficiency Expectation |
|------|-------------|------------------------|
| Supervised Learning | Regression, classification, ensemble methods, regularization, cross-validation | Select appropriate algorithms; tune hyperparameters systematically |
| Unsupervised Learning | Clustering (k-means, DBSCAN), dimensionality reduction (PCA, t-SNE), anomaly detection | Apply to real problems; evaluate without labels |
| Model Evaluation | Precision/recall, F1, ROC-AUC, confusion matrix, bias-variance trade-off, statistical tests | Choose the right metric for the business problem |
| Feature Engineering | Feature selection, encoding, scaling, feature stores, temporal features | Transform raw data into effective model inputs |
| MLOps & Deployment | Model serving, A/B testing, canary deployments, model monitoring, feature stores, pipelines | Deploy and monitor models in production |
| Neural Networks | CNNs, RNNs/Transformers, backpropagation, activation functions, regularization | Explain architecture choices; debug training issues |
| NLP & CV Basics | Tokenization, embeddings, attention mechanism, image preprocessing, transfer learning | Apply pre-trained models; fine-tune for specific tasks |
| Bias & Fairness | Fairness metrics, disparate impact, data bias detection, interpretability, responsible AI | Identify and mitigate bias; explain model decisions |
| Recommender Systems | Two-tower retrieval, multi-stage ranking, cold-start, exploration-exploitation, NDCG | Design end-to-end recommendation pipelines from retrieval to serving |

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

## Cross-References

- **System Design**: [Search Autocomplete](../../system_design/search_autocomplete/) (ranking models, ML inference), [News Feed](../../system_design/news_feed/) (recommendation models), [Recommender System](../../system_design/recommender_system/) (two-tower retrieval, multi-stage ranking, cold-start), [Notification Service](../../system_design/notification_service/) (send-time optimization)
- **CS Fundamentals**: Algorithms (gradient descent, dynamic programming), Linear Algebra (matrices, vectors), Probability & Statistics (distributions, hypothesis testing), Optimization
