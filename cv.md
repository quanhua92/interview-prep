### Quan Hua

**Senior AI Engineer**

Ho Chi Minh City, Vietnam | quanhua92@gmail.com\
[linkedin.com/in/huahongquan](https://linkedin.com/in/huahongquan) | [github.com/quanhua92](https://github.com/quanhua92)

### Professional Summary

Senior AI Engineer (10+ years) specializing in multimodal AI systems, agentic LLM workflows, and production ML pipelines. Patent holder in multimodal sensor fusion (radar+optical) for 3D body measurement at BodiData (3 scanner generations), with prior deep learning work on edge robotics (Maya Personal Robot). Founded two open-source AI products: OpenVideoKit (AI-first video editor with a LangGraph copilot, MCP tool server, and neural TTS pipeline) and AIPriceAction (Rust data pipeline and Agent Skills). End-to-end ownership from model design to cloud/edge deployment with strong MLOps practices.

### Experience

**Oct 2025 – Present: Independent Founder — Open-Source AI Products**

Building and shipping two open-source AI products end-to-end.

  **OpenVideoKit - <https://www.openvideokit.com/>**

  * Built an AI-first video editor with a multimodal rendering pipeline (FastAPI → animated HTML → neural TTS → MP4) and low-latency SSE streaming.
  * Designed a LangGraph copilot that proposes human-gated edits, exposed via a 28-tool FastMCP server for tool-augmented LLM agents.

  **AIPriceAction - <https://www.aipriceaction.com/>**

  * Engineered a Rust backend (Axum, PostgreSQL, Redis) with 22 workers syncing 574 global tickers, plus a multi-agent research pipeline with automated quality gates.
  * Shipped a React 19 + TypeScript SPA and a Python SDK + CLI ([aipriceaction](https://pypi.org/project/aipriceaction/), [aipa-cli](https://pypi.org/project/aipa-cli/)) with 3 Agent Skills for Claude Code, Cursor, and OpenCode.

**2017 – Oct 2025: BodiData, Inc - <https://www.bodidata.com/>**
**Senior Machine Learning Engineer**

3D body measurement and size-matching solutions to reduce clothing returns. Led the multimodal CV engine across 3 generations of the Kora® 3D Body Scanner, fusing depth, RGB, and radar data into accurate body models.

  * **Kora V1 (Surface + RealSense):** Designed the multimodal CV pipeline from scratch — fused RealSense depth with RGB and radar via ORB-SLAM 3 for real-time camera positioning; implemented the C++ application in Qt and collaborated on the radar fusion algorithm.
  * **Kora V2 (RealSense D415):** Ported to far-range camera. Decreased 3D measurement error by ~1 inch through enhanced model fitting against fused point cloud data, improving product accuracy.
  * **Kora V3 (iPad + ESP32 → AWS Lambda):** Rewrote ESP32 firmware to multi-threaded ESP-IDF with BLE to iPad and Vayyar radar integration for depth fusion.
  * **Kora V3 Cloud:** Refactored Qt C++ processing pipeline into a CLI binary and built a Python Lambda to orchestrate S3 downloads, processing, and uploads.
  * Re-engineered Node.js SSE streaming server in Rust (Axum, Tokio), eliminating OOM crashes and boosting throughput 10x on smaller ECS instances.

**2014 – 2017: Autonomous, Inc. - <https://autonomous.ai/>**
**Artificial Intelligence Engineer**

  * Directed 6 AI engineers to build deep learning brain for Maya Personal Robot (CES 2015 TechCrunch Hardware Battlefield finalist), contributing to $161K+ raised on Kickstarter.
  * Integrated and deployed deep learning models for computer vision, facial recognition, emotion detection, and NLP as ROS components with real-time inference on edge hardware.
  * Owned the ML pipeline from data collection to production inference via TensorFlow Serving and Flask across multiple product lines.


### Patents

Co-inventor. "Systems and Methods for Generating a Refined 3D Model Using Radar and Optical Camera Data." [US20190295319A1](https://patents.google.com/patent/US20190295319A1), filed March 14, 2019.

### Education

**2010 – 2014: Bachelor of Science in Computer Science**
Honor Programs - University of Science Ho Chi Minh City. GPA: 8.7 / 10

### Skills

  * **Languages:** Python, Rust, C++, TypeScript
  * **ML/DL:** PyTorch, Multimodal Sensor Fusion, Computer Vision, 3D Reconstruction
  * **AI Agents:** Multi-Agent Pipelines, Tool-Augmented LLMs, LangGraph, Model Context Protocol (MCP)
  * **Frameworks:** FastAPI, FastMCP, LangChain, Qt, ESP-IDF, Axum, Tokio, React
  * **Infrastructure:** Docker, AWS (Lambda, S3, ECS), PostgreSQL, Redis, CI/CD, MLOps

### Publications

**Book: Machine Learning with TensorFlow 1.x (2017)**
Co-authored 5 of 13 chapters on Deep Learning with TensorFlow.

**Book: OpenCV3 Blueprints (2015)**
Co-authored 2 chapters: "Recognizing Facial Expressions with Machine Learning" and "Panoramic Image Stitching Application using Android Studio and NDK."

**2014: Hong-Quan Hua, T. Hoang Ngan Le, and Bac Le, "An Effective Initialization for ASM-based Methods", CISIM 2014 Conference.**
