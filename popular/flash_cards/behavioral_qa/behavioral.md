# Behavioral STAR Stories (Flashcards)

Click the bold text to reveal the answer. Click the file link for the full deep dive.

---

<details><summary><b>Tell me about a time you were wrong or didn't know something (Intellectual Honesty)</b></summary>

Topic: Intellectual Honesty (STAR)
Key concepts:
- Situation: a 30-stream RTSP video pipeline dropped from 30 to 18 FPS, H2D transfers erratic; you proposed refactoring onto multiple CUDA streams.
- Action (the core): a week's work on async CUDA streams actually *decreased* throughput another 15%. Practiced intellectual honesty — admitted the hypothesis was wrong rather than defending it, profiled the data, and pivoted (e.g., the real bottleneck was CPU decode / pageable memory, fixed with pinned memory + NVDEC).
- Result/learning: early admission of error prevents wasted GPU/HW resources and downstream delays; ego-free debugging follows the profile, not the personal design choice. "I don't know" + pulling in an SME is the correct move over guessing.
File: [behavioral_star_intellectual_honesty.md](../../behavioral_star_intellectual_honesty.md)
</details>

<details><summary><b>Tell me about resolving a cross-functional conflict under deadline (One Team)</b></summary>

Topic: One Team (STAR)
Key concepts:
- Situation: a Jetson pre-release blocker — PCIe ASPM L1.2 transition crashed the SoC; the driver team blamed silicon, hardware validation blamed the driver, 3 days from firmware freeze.
- Action: bypassed Jira/management chains and walked to the hardware validation lab for a joint debug session framed around shared truth ("we both want the board booting by Friday"), tracing from the driver register write to the physical PCIe lanes.
- Result/learning: zero finger-pointing; align on system truth, not winning the argument; proactive high-bandwidth cross-functional sync beats formal ticket routes when a deadline is at risk.
File: [behavioral_star_one_team.md](../../behavioral_star_one_team.md)
</details>

---

[Flashcard Index](../README.md)
