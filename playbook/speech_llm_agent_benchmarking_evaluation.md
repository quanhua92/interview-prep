# Speech LLMs: Agent Benchmarking & Evaluation Frameworks

- **Category**: Speech AI / System Benchmarking & QA
- **Difficulty**: Hard
- **Target Role**: Senior QA Engineer / Voice AI Systems Architect / Infrastructure Engineer
- **Flashcards**: [Speech LLM deck](flash_cards/speech/speech_llm.md)

---

## 1. Question Description

Deploying voice-first conversational agents in production requires robust benchmarking frameworks to evaluate speech quality, transcript accuracy, latency profile, and multi-turn conversational reliability. Unlike text-based chatbots, voice agents must operate under real-world degradation: acoustic noise, room reverberation, microphone clipping, packet loss, and varying network latency.

Design a comprehensive evaluation framework for a streaming, interactive voice agent. Specifically, detail:
1. **Speech Quality Metrics**: PESQ, POLQA, Mel-Cepstral Distortion (MCD), and ViSQOL.
2. **Transcription Performance**: Word Error Rate (WER) and Character Error Rate (CER) calculations.
3. **Latency Benchmarking**: Time-to-First-Token (TTFT) vs. Time-to-First-Audio (TTFA) and how to measure them.
4. **Reliability & Turn-Taking**: Barge-in success rate and turn-taking accuracy.
5. **Simulator Code**: A Python-based automated test simulator that injects audio noise, simulates network latency/jitter, and uses LLM-as-a-judge to grade task success and conversational naturalness.

---

## 2. Speech Quality & Transcription Metrics

Evaluating the synthesis quality of TTS engines and the degradation of streaming audio requires objective perceptual metrics.

### 2.1 Speech Quality Metrics

#### PESQ (Perceptual Evaluation of Speech Quality - ITU-T P.862)
* **How it works**: Compares a reference signal (original clean audio) and a degraded signal (processed through network/codec). It aligns the signals in time, applies an auditory transform (modeling human ear response), and evaluates difference in loudness and pitch.
* **Score Range**: $-0.5$ to $4.5$ (MOS - Mean Opinion Score scale).
* **Limitations**: Designed primarily for narrow-band ($8\text{ kHz}$) and wide-band ($16\text{ kHz}$) telephony. It struggles with modern high-fidelity audio ($24\text{ kHz}$ to $48\text{ kHz}$) and voice agents utilizing vocoders.

#### POLQA (Perceptual Objective Listener Quality Assessment - ITU-T P.863)
* **How it works**: The successor to PESQ. Supports super-wideband ($32\text{ kHz}$) and full-band ($48\text{ kHz}$) audio. It models modern codecs, temporal stretching/compression (jitter buffer behavior), and acoustic acoustic environments.
* **Score Range**: $1.0$ to $4.75$.

#### MCD (Mel-Cepstral Distortion)
* **How it works**: A pure physical metric measuring the difference between two sequences of Mel-Frequency Cepstral Coefficients (MFCCs).
* **Mathematical Formulation**:
  $$MCD = \frac{10\sqrt{2}}{\ln 10} \frac{1}{T} \sum_{t=1}^{T} \sqrt{\sum_{k=1}^{D} (mc_{t,k} - mc'_{t,k})^2}$$
  Where $mc_{t,k}$ and $mc'_{t,k}$ are the $k$-th MFCC coefficients of the reference and test signals at frame $t$, $T$ is the total number of frames, and $D$ is the number of cepstral coefficients evaluated (typically $13$ or $24$, discarding the 0th coefficient representing overall energy).
* **Score Range**: Lower is better ($0.0$ means identical spectra). Excellent TTS systems target an MCD $< 2.5\text{ dB}$.

#### ViSQOL (Virtual Speech Quality Objective Listener - Google)
* **How it works**: Uses a signal-matching algorithm based on the **spectrogram similarity** of the reference and degraded signals. It compares frequency bands and measures structural similarity index (SSIM) over time.
* **Score Range**: $1.0$ to $5.0$. Excellent for assessing quality changes induced by neural codecs (e.g., EnCodec/DAC compression) or packet loss concealment (PLC) algorithms.

### 2.2 Speech Transcription Metrics

ASR transcriptions are compared to a ground-truth transcript using Levenshtein distance (edit distance).

#### Word Error Rate (WER)
$$WER = \frac{S + D + I}{N}$$
Where:
* $S = \text{Substitutions}$ (incorrect words)
* $D = \text{Deletions}$ (missing words)
* $I = \text{Insertions}$ (extra words added)
* $N = \text{Number of words in reference transcript}$

#### Character Error Rate (CER)
Calculated identically to WER, but at the character level instead of the word level. CER is vital for phonetically dense languages (e.g., Mandarin) or evaluating word boundaries and suffix endings in morphology-rich languages.

---

## 3. Latency & Reliability Metrics

```
User Audio Start
   │
   ▼
[Client VAD (Silence End)] ────┐
   │                           │
   ▼                           ▼
[ASR First Word Emitted]    [ASR Complete Sentence]
   │                           │
   ▼                           ▼
[LLM First Token (TTFT)]    [LLM Sentence Done]
   │                           │
   ▼                           ▼
[TTS First Audio (TTFA)] ──> [TTS Playback Begins]
```

### 3.1 Latency Benchmarking Definitions
* **Time-to-First-Token (TTFT)**: The latency from the moment the user stops speaking (silence detected by VAD) to the moment the LLM generates its first output token. This is a text-level server metric.
* **Time-to-First-Audio (TTFA)**: The latency from the moment the user stops speaking (silence detected by VAD) to the client-side speaker playing the first chunk of synthesized audio. This represents the actual user experience and includes ASR processing, network propagation, LLM generation, TTS synthesis, client buffer accumulation, and audio hardware initialization.

### 3.2 Measuring TTFA in Streaming Pipelines
To measure TTFA accurately, we inject markers into the streaming WebSocket connection:
1. **Timestamp A**: Client marks the end of speech ($T_{EOS}$) based on VAD state transition to silence.
2. **Timestamp B**: The first audio buffer block ($20\text{ ms}$ of PCM) is received and processed by the client speaker callback.
3. $$\text{TTFA} = T_{\text{playbackStart}} - T_{EOS}$$

### 3.3 Reliability & Conversation Flow Metrics
* **Barge-In Success Rate**: The percentage of times the system successfully mutes the speaker, halts server-side processing, and flushes the buffer within $150\text{ ms}$ of the user starting to interrupt.
  $$\text{Barge-In Success Rate} = \frac{\text{Successful Interruption Actions}}{\text{Total Interruption Attempts}} \times 100\%$$
* **Turn-Taking Accuracy**: Evaluates how well the Voice Activity Detector (VAD) handles mid-sentence pauses.
  * **False Interruptions**: System cuts the user off while they were just pausing to think.
  * **Dead Air / Sluggish Turn**: System waits too long (e.g., $> 1.0\text{ second}$) before realizing the user has fully finished their turn.

---

## 4. Python Automated Test Simulator

Below is a complete, self-contained Python program demonstrating a simulated voice agent testing framework. 
It performs the following:
1. **Acoustic Degradation**: Injects Gaussian white noise into a clean mono raw audio waveform.
2. **Network Network Simulation**: Passes audio through a jitter buffer simulator that adds random delay and simulates packet drop/corruption.
3. **LLM-as-a-Judge Evaluation**: Calls a simulated LLM API to evaluate the transcript alignment, correctness, and naturalness of the interaction.

```python
import time
import random
import numpy as np
import math
from typing import Dict, Any, Tuple

# ============================================================================
# 1. Acoustic Degradation & Noise Injection
# ============================================================================
def inject_gaussian_noise(audio_signal: np.ndarray, target_snr_db: float) -> np.ndarray:
    """
    Injects Gaussian white noise to achieve a target Signal-to-Noise Ratio (SNR) in dB.
    Formula: SNR_dB = 10 * log10(Signal_Power / Noise_Power)
    """
    # Calculate signal power
    signal_power = np.mean(audio_signal ** 2)
    if signal_power == 0:
        return audio_signal
    
    # Calculate required noise power
    snr_linear = 10 ** (target_snr_db / 10.0)
    noise_power = signal_power / snr_linear
    
    # Generate noise
    noise = np.random.normal(0, math.sqrt(noise_power), audio_signal.shape)
    
    # Return degraded signal
    return audio_signal + noise

# ============================================================================
# 2. Network Latency & Jitter Simulator
# ============================================================================
class NetworkSimulator:
    """
    Simulates packet delivery over network with configurable delay, jitter, and packet loss.
    """
    def __init__(self, mean_delay_ms: float = 40.0, jitter_ms: float = 15.0, packet_loss_rate: float = 0.05):
        self.mean_delay_ms = mean_delay_ms
        self.jitter_ms = jitter_ms
        self.packet_loss_rate = packet_loss_rate

    def transit_packet(self, packet: bytes) -> Tuple[Optional[bytes], float]:
        """
        Simulates packet transit.
        Returns: Tuple of (packet_data, delay_seconds). If packet is lost, returns (None, infinity).
        """
        if random.random() < self.packet_loss_rate:
            return None, float('inf') # Packet dropped
        
        # Log-Normal or Gaussian distribution for network latency modeling
        delay = np.random.normal(self.mean_delay_ms, self.jitter_ms)
        delay = max(5.0, delay) # Minimum physical routing delay is 5ms
        
        # Convert ms to seconds
        delay_sec = delay / 1000.0
        return packet, delay_sec

# ============================================================================
# 3. LLM-as-a-Judge Evaluation Engine (Mocked API)
# ============================================================================
class LLMasJudgeEvaluator:
    """
    Simulates LLM-as-a-judge queries to grade conversational transcript quality.
    """
    def evaluate_turn(self, prompt: str, reference: str, transcript: str) -> Dict[str, Any]:
        """
        Evaluates task success and conversational naturalness based on the transcripts.
        """
        # In production, this would execute a prompt via openai, anthropic, or a local Llama model.
        print("\n--- LLM-as-a-Judge Evaluation Execution ---")
        
        # Simple simulated analysis:
        # Check if key concepts from reference appear in the transcript.
        words_ref = set(reference.lower().split())
        words_trans = set(transcript.lower().split())
        intersection = words_ref.intersection(words_trans)
        
        # Grade calculations
        coverage = len(intersection) / len(words_ref) if len(words_ref) > 0 else 1.0
        
        task_success = "SUCCESS" if coverage > 0.7 else "FAILED"
        naturalness_score = round(coverage * 5.0, 1) # Map to a 1.0 - 5.0 scale
        
        # Introduce some human-like reasoning
        justification = (
            f"The transcript captured {len(intersection)} out of {len(words_ref)} keywords "
            f"({coverage:.1%} coverage). The message intent was preserved."
            if task_success == "SUCCESS" else "Critical instructions or keywords were missing in transcription."
        )
        
        return {
            "task_success": task_success,
            "naturalness_score": max(1.0, naturalness_score),
            "justification": justification
        }

# ============================================================================
# 4. Simulation Test Runner / Coordinator
# ============================================================================
def run_benchmarking_simulation():
    # 1. Create clean audio signal (a sine wave simulating speech)
    sample_rate = 16000
    duration = 2.0  # 2 seconds
    t = np.linspace(0, duration, int(sample_rate * duration), endpoint=False)
    clean_audio = np.sin(2 * np.pi * 440 * t)  # 440 Hz Sine wave
    
    # 2. Inject noise (Acoustic phase)
    target_snr = 15.0  # 15 dB SNR (noisy room environment)
    degraded_audio = inject_gaussian_noise(clean_audio, target_snr)
    print(f"Acoustic Degradation: Injected {target_snr}dB SNR noise. Signal RMS went from "
          f"{np.std(clean_audio):.3f} to {np.std(degraded_audio):.3f}")
    
    # 3. Simulate Network Transmission (Network phase)
    net_sim = NetworkSimulator(mean_delay_ms=80.0, jitter_ms=25.0, packet_loss_rate=0.02)
    packet_size = 3200  # 3200 bytes = 100ms of 16kHz 16-bit audio
    raw_bytes = (degraded_audio * 32767).astype(np.int16).tobytes()
    
    total_packets = math.ceil(len(raw_bytes) / packet_size)
    delivered_packets = 0
    total_delay = 0.0
    
    for i in range(total_packets):
        chunk = raw_bytes[i*packet_size:(i+1)*packet_size]
        result, delay = net_sim.transit_packet(chunk)
        if result is not None:
            delivered_packets += 1
            total_delay += delay
            
    avg_transit_delay = (total_delay / delivered_packets) * 1000 if delivered_packets > 0 else 0.0
    loss_percent = ((total_packets - delivered_packets) / total_packets) * 100.0
    
    print(f"Network Simulation: Sent {total_packets} packets. Loss rate: {loss_percent:.1f}%. "
          f"Average transit delay: {avg_transit_delay:.1f}ms")
    
    # 4. Evaluate conversation result using LLM-as-a-Judge
    reference_script = "Hello I would like to book a flight to Seattle for tomorrow morning please."
    # Simulate ASR errors in transcription
    mock_transcript = "Hello I would like to book a flight to Seattle tomorrow morning."
    
    evaluator = LLMasJudgeEvaluator()
    eval_report = evaluator.evaluate_turn(
        prompt="Book a flight to Seattle for tomorrow morning.",
        reference=reference_script,
        transcript=mock_transcript
    )
    
    print(f"Evaluation Result:")
    print(f"  - Task Success: {eval_report['task_success']}")
    print(f"  - Naturalness Score: {eval_report['naturalness_score']} / 5.0")
    print(f"  - Justification: {eval_report['justification']}")

if __name__ == "__main__":
    run_benchmarking_simulation()
