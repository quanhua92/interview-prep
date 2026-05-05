# ML/AI Engineer -- Prep Checklist

Use this checklist to track your preparation progress across core machine learning and AI engineering competencies. Aim to complete every item before your interview window opens.

## Topic Prep Checklist per Competency

- [ ] **ML Fundamentals**: Review supervised vs unsupervised learning, bias-variance trade-off, overfitting/underfitting, cross-validation, and evaluation metrics (precision, recall, F1, AUC-ROC).
- [ ] **Unsupervised Learning**: Be prepared to discuss clustering algorithms (k-means, DBSCAN, hierarchical), dimensionality reduction (PCA, t-SNE), anomaly detection, and evaluation without labels (silhouette score, elbow method).
- [ ] **Deep Learning Architectures**: Be prepared to explain CNNs, RNNs, Transformers, attention mechanisms, and when to use each architecture.
- [ ] **MLOps and Model Deployment**: Understand model serving, A/B testing, canary deployments, model versioning, and CI/CD for ML pipelines (MLflow, Kubeflow).
- [ ] **Feature Engineering**: Practice feature selection, encoding strategies, handling missing data, feature stores, and creating training datasets from raw data.
- [ ] **Natural Language Processing**: Review tokenization, embeddings (Word2Vec, BERT), sequence-to-sequence models, and prompt engineering for LLMs.
- [ ] **Large Language Models**: Understand fine-tuning techniques (LoRA, QLoRA), RAG architectures, vector databases, and prompt engineering best practices.
- [ ] **Computer Vision**: Be familiar with image classification, object detection (YOLO), segmentation, and transfer learning with pretrained models.
- [ ] **Bias and Fairness**: Review fairness metrics (disparate impact, equal opportunity), data bias detection techniques, interpretability methods (SHAP, LIME), and responsible AI principles.
- [ ] **Experiment Tracking and Evaluation**: Prepare to discuss experiment management, hyperparameter tuning, statistical significance testing, and model monitoring in production.

## Practice Questions

1. How would you design an end-to-end ML pipeline from data collection to model deployment?
2. Explain the bias-variance trade-off and how you would diagnose whether a model is overfitting or underfitting.
3. How does the Transformer attention mechanism work and why has it replaced RNNs in many applications?
4. Describe how you would implement a RAG system for a question-answering application.
5. What evaluation metrics would you use for an imbalanced classification problem and why?
6. How do you detect and handle data leakage in your ML pipeline?
7. Explain how a neural network learns through backpropagation and how you would debug training issues (vanishing/exploding gradients).
8. Describe transfer learning and when you would use a pretrained model vs training from scratch.
9. How do you handle concept drift in a production ML system?
10. Explain the difference between batch inference and real-time inference. When would you use each?
11. How would you fine-tune a large language model on a custom dataset with limited GPU resources?
12. Describe your approach to feature engineering for a recommendation system.
13. How would you design an A/B testing framework to compare two ML models in production?
14. Explain how vector databases work and their role in LLM applications.
15. What strategies do you use to reduce training time for deep learning models?

## System Design Bridge Items

- [ ] Review [Search Autocomplete](../../system_design/search_autocomplete/) for understanding ranking models, ML inference at scale, and low-latency serving.
- [ ] Study [News Feed](../../system_design/news_feed/) for recommendation model design, ranking pipelines, and personalization at scale.
- [ ] Connect ML model knowledge to [Notification Service](../../system_design/notification_service/) for send-time optimization, engagement prediction, and ML-driven delivery.
- [ ] Review the distributed systems section for understanding model training at scale and GPU cluster design.
- [ ] Map model monitoring requirements to the observability and logging sections in system design.

## Practice Log

- [ ] 2026-05-__: Completed ML fundamentals and deep learning architecture review
- [ ] 2026-05-__: Walked through MLOps and LLM application design problems
- [ ] 2026-05-__: Mock interview session covering all ML/AI engineering competency areas
