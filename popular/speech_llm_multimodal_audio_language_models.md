# Speech LLMs: Multimodal Audio-Language Models (ALMs)

- **Category**: Speech AI / Multimodal LLM Architecture
- **Difficulty**: Very Hard
- **Target Role**: Senior Machine Learning Engineer / Speech LLM Architect / Core AI Researcher

---

## 1. Question Description

Traditional voice agents rely on **cascaded pipelines** consisting of distinct modules: **Speech-to-Text (STT)** $\rightarrow$ **Large Language Model (LLM)** $\rightarrow$ **Text-to-Speech (TTS)**. While modular, these pipelines suffer from significant disadvantages:
1. **High Latency Accumulation**: Sequential processing of each module aggregates execution and I/O delays, pushing Time-to-First-Audio (TTFA) well above $1.5\text{ seconds}$.
2. **Information Loss**: Cascading discards acoustic cues (paralinguistics) such as pitch, intonation, emotion, sarcasm, accent, pauses, and background environment.
3. **Error Propagation**: Word errors from the ASR/STT module cannot be corrected by the LLM, and punctuation/phrasing inaccuracies lead to robotic TTS synthesis.

To solve this, modern systems implement **native Audio-Language Models (ALMs)** that ingest and generate text and audio tokens end-to-end. 

Explain the full architectural pipeline of an ALM, detailing:
* **Audio Tokenization**: How continuous audio waveforms are converted into discrete audio tokens using Neural Audio Codecs (EnCodec, SoundStream, Descript Audio Codec) via Residual Vector Quantization (RVQ).
* **Audio Encoders**: The role of continuous features (Whisper, AST) vs. discrete codebook indices.
* **Projection Modules**: Bridging the dimensional and temporal gap between audio encoders and LLMs (Linear, MLP, Q-Former).
* **Autoregressive Audio-Text Decoding**: Interleaving strategies (flat interleaving, delayed patterns, multi-stream/hierarchical decoding).
* **Neural Audio Vocoders**: Synthesizing raw audio from model outputs (HiFi-GAN, Vocos, BigVGAN).
* **SOTA Case Studies**: GPT-4o voice, AudioPaLM, SeamlessM4T.

---

## 2. Core Architectural Overview: Cascaded vs. Native Multimodal ALMs

The diagram below contrasts the cascaded pipeline with a native multimodal Audio-Language Model (ALM):

### Cascaded Architecture (STT $\rightarrow$ LLM $\rightarrow$ TTS)
```
[User Audio] 
      │
      ▼  (Acoustic context lost)
┌───────────┐       ┌───────────┐       ┌───────────┐
│  STT/ASR  │──────>│    LLM    │──────>│    TTS    │──────> [Synthesized Audio]
└───────────┘ Text  └───────────┘ Text  └───────────┘
```

### Native Multimodal ALM Architecture
```
                     ┌────────────────────────────────┐
                     │   Joint Audio-Text LLM         │
                     │  (Decoder-Only / Encoder-Dec)  │
                     └────────────────────────────────┘
                               ▲            │
     Continuous Aud. Embeddings│            │ Discrete Audio Tokens
                     ┌─────────┴─┐        ┌─▼─────────┐
                     │ Projection│        │ Neural    │
                     └───────────┘        │ Vocoder   │
                           ▲              └───────────┘
                           │                    │
                     ┌───────────┐              ▼
                     │   Audio   │       [Speech Waveform]
                     │  Encoder  │
                     └───────────┘
                           ▲
                           │
                     [User Audio]
```

By processing audio as primary tokens (or continuous embeddings) directly inside the LLM autoregressive loop, native ALMs preserve paralinguistic features and generate immediate audio responses, reducing TTFA to sub-$200\text{ ms}$ limits.

---

## 3. Speech Tokenization & Neural Audio Codecs

To feed audio into a language model, the continuous, high-frequency waveform must be compressed into a sequence of discrete tokens, analogous to sub-word text tokens. This is achieved using **Neural Audio Codecs** that utilize **Residual Vector Quantization (RVQ)**.

### 3.1 Residual Vector Quantization (RVQ)
Directly quantizing a high-dimensional vector with a single large codebook is computationally infeasible due to exponential codebook size expansion (e.g., a $2^{24}$ codebook is required for $24\text{ bits}$ of information). RVQ solves this by using $R$ cascaded codebooks, where each layer quantizes the quantization error (residual) of the previous layer.

Given a continuous target vector $\mathbf{z}$:
1. **Layer 1**: $\mathbf{q}_1 = \text{Quantize}_1(\mathbf{z})$
2. **Residual 1**: $\mathbf{e}_1 = \mathbf{z} - \mathbf{q}_1$
3. **Layer 2**: $\mathbf{q}_2 = \text{Quantize}_2(\mathbf{e}_1)$
4. **Residual 2**: $\mathbf{e}_2 = \mathbf{e}_1 - \mathbf{q}_2$
5. **Layer $r$**: $\mathbf{q}_r = \text{Quantize}_r(\mathbf{e}_{r-1})$

The reconstructed vector is the sum of the quantized vectors across all $R$ layers:
$$\mathbf{\hat{z}} = \sum_{r=1}^{R} \mathbf{q}_r$$

This represents each frame of audio as an array of $R$ discrete indices. For a sequence of length $T$ and $R$ quantizers, the representation is a $T \times R$ grid of integers.

```
Continuous Audio Vector (Z)
      │
      ├──> Quantizer 1 ──> Codebook Index 1 [c_1] (Coarse)
      │        │
      │        ▼ (Subtract)
      └──> Residual e_1
               │
               ├──> Quantizer 2 ──> Codebook Index 2 [c_2]
               │        │
               │        ▼ (Subtract)
               └──> Residual e_2 ──> ... ──> Codebook Index R [c_R] (Fine)
```

### 3.2 Key Codec Comparison

| Feature / Codec | **SoundStream** (Google) | **EnCodec** (Meta) | **Descript Audio Codec (DAC)** |
| :--- | :--- | :--- | :--- |
| **Primary Architecture** | CNN Encoder-Decoder + RVQ | CNN Encoder-Decoder + RVQ + LSTM | CNN Encoder-Decoder + RVQ |
| **Quantization Rates** | $3\text{--}18\text{ kbps}$ | $1.5\text{--}24\text{ kbps}$ | $1.5\text{--}9\text{ kbps}$ |
| **Audio Sampling Rate** | $16\text{ kHz}$ or $24\text{ kHz}$ | $24\text{ kHz}$ or $48\text{ kHz}$ (Stereo) | $24\text{ kHz}$ or $44.1\text{ kHz}$ |
| **Frame Downsampling** | $320\times$ (50 Hz frame rate) | $320\times$ or $640\times$ (75/150 Hz) | $512\times$ or $1024\times$ (47/86 Hz) |
| **Codebook Size ($K$)** | 1024 (10 bits per quantizer) | 1024 (10 bits per quantizer) | 1024 (10 bits per quantizer) |
| **Number of Quantizers ($R$)**| up to 16 | up to 32 | up to 9 |
| **Unique Innovation** | Discriminator based on Wavegan | Multi-scale spectrogram discriminators | Periodic activations (Snake function) to prevent alias |

* **Snake Activation Function (DAC)**: The use of $x + \frac{1}{\alpha}\sin^2(\alpha x)$ introduces periodic inductive bias, which is highly effective for representing periodic signals like audio waveforms and eliminates high-frequency artifacts.

---

## 4. Audio Encoders & Projection Modules

While codecs discretize audio for output generation, encoding input audio is often performed using continuous feature representations to preserve maximum semantic and acoustic fidelity.

### 4.1 Audio Encoders
1. **Whisper (OpenAI)**:
   * **Structure**: Transformer Encoder-Decoder trained on $680,000$ hours of weakly supervised multilingual speech.
   * **Input**: $80$-channel log-mel spectrogram computed on $25\text{ ms}$ windows with $10\text{ ms}$ strides.
   * **Representations**: The encoder outputs downsampled (by $2\times$ via 1D convolutions) representations. These vectors contain dense phonetic, lexical, and prosodic embeddings.
2. **Audio Spectrogram Transformer (AST)**:
   * **Structure**: Pure Vision Transformer (ViT) applied to audio.
   * **Input**: Log-mel spectrogram split into overlapping $16 \times 16$ patches.
   * **Projection**: Patches are flattened and linearly projected into embeddings, augmented with 1D/2D positional embeddings, and processed via self-attention. Highly effective for non-speech sounds and music.

### 4.2 Projection Modules
An LLM expects embeddings of dimension $D_{LLM}$, whereas the audio encoder outputs features of dimension $D_{enc}$ at a temporal rate of $F_{enc}$ Hz. The projection module resolves these mismatch dimensions:

```
[Audio Encoder] (T_audio x D_enc)
        │
        ▼
 ┌─────────────┐
 │ Projector   │ (e.g., Linear, MLP, or Q-Former)
 └─────────────┘
        │
        ▼
[LLM Token Space] (T_compressed x D_LLM)
```

1. **Linear Projection**:
   $$\mathbf{X}_{LLM} = \mathbf{X}_{enc} \mathbf{W}_p$$
   Fast, memory-efficient, but does not perform temporal downsampling, resulting in very long context lengths (e.g., 50 tokens per second of audio).
2. **Multi-Layer Perceptron (MLP)**:
   $$\mathbf{X}_{LLM} = \text{GELU}(\mathbf{X}_{enc} \mathbf{W}_1) \mathbf{W}_2$$
   Provides non-linear mapping capabilities. Often combined with frame stacking (concatenating adjacent frames) to reduce the sequence length by $2\times$ or $4\times$.
3. **Q-Former (Querying Transformer)**:
   Introduced in BLIP-2. Uses a set of learnable **query embeddings** ($N_{queries} \ll T_{audio}$) that attend to the audio encoder representations via cross-attention. This compresses variable-length audio inputs into a fixed, compact number of tokens, drastically reducing LLM context overhead.

---

## 5. Autoregressive Audio-Text Decoding & Interleaving

Generating audio tokens alongside text tokens requires specialized interleaving patterns to model joint distributions. Since RVQ provides $R$ tokens per timestep $t$, models must serialize or parallelize these tokens.

### 5.1 Token Formatting & Serialization Patterns
Assume text tokens are denoted by $T$ and audio tokens at frame $t$ by $A_{t,1}, A_{t,2}, \dots, A_{t,R}$.

```
1. Flat Serialization (Concat-Time):
[Text] [A_1,1] [A_1,2] ... [A_1,R] [A_2,1] [A_2,2] ... [A_2,R]

2. Delayed Pattern (Sequence shift):
Stream 1: [A_1,1] [A_2,1] [A_3,1] [A_4,1]
Stream 2: <pad>   [A_1,2] [A_2,2] [A_3,2]
Stream 3: <pad>   <pad>   [A_1,3] [A_2,3]

3. Multi-Stream / Hierarchical:
Main LLM Decoder:  [Text]  ──>  [A_1,1]  ──>  [A_2,1]  ──>  [A_3,1]  (Coarse autoregressive)
                                 │            │            │
Fine Autoencoder:                ▼            ▼            ▼
                           [A_1,2..R]   [A_2,2..R]   [A_3,2..R] (Parallel/non-autoregressive)
```

1. **Flat Serialization (Concat-Time)**:
   Linearizes all tokens: $T_1, T_2, A_{1,1}, A_{1,2}, \dots, A_{1,R}, A_{2,1}, \dots$.
   * *Pros*: Simple to train; standard decoder-only architecture.
   * *Cons*: Sequential length increases by $R \times$, resulting in $\mathcal{O}((T \cdot R)^2)$ self-attention complexity.
2. **Delayed Pattern (Time-Shifted Multi-Book)**:
   Generates all $R$ streams in parallel but shifts each stream by $1$ token step relative to the previous stream.
   * *Pros*: Captures cross-codebook dependencies while maintaining a single token step per frame.
   * *Cons*: Requires custom attention masking and modified vocabulary headers.
3. **Hierarchical / Coarse-to-Fine Generation**:
   The LLM generates only the first quantizer stream $A_{t,1}$ (coarse audio) along with text. A secondary, faster model (e.g., a smaller Transformer, diffusion model, or non-autoregressive feedforward net) generates the remaining $R-1$ streams conditioned on the first.
   * *Pros*: Keeps the LLM context extremely short; fast inference.
   * *Cons*: Multi-stage training pipeline.

---

## 6. Audio Synthesis & Neural Vocoders

Once the discrete audio tokens are generated by the LLM, they must be converted back to continuous, high-fidelity waveforms. This is done by a neural vocoder.

```
[Discrete Codebook Indices]
           │
           ▼
┌───────────────────────┐
│ Frame-level Embedding │
└───────────────────────┘
           │
           ▼ (Transpose Convolutions)
┌───────────────────────┐
│ Mel-Spectrogram       │ (Intermediate representation, if applicable)
└───────────────────────┘
           │
           ▼ (Up-sampling & Phase Reconstruction)
┌───────────────────────┐
│ Neural Vocoder        │ (HiFi-GAN, Vocos, BigVGAN)
└───────────────────────┘
           │
           ▼
 [Audio Waveform (PCM)]
```

### 6.1 HiFi-GAN
* **Architecture**: Combines multi-receptive field fusion (MRF) with generative adversarial networks.
* **Discriminators**:
  * **Multi-Scale Discriminator (MSD)**: Operates on smoothed/downsampled versions of the raw waveform at different scales.
  * **Multi-Period Discriminator (MPD)**: Splits the 1D waveform into 2D matrices of varying periods (e.g., $2, 3, 5, 7, 11$) to evaluate disjoint periodic features, capturing pitch harmonics.
* **Loss Functions**: Adversarial loss + Least Squares loss + Feature Matching Loss (minimizing differences in intermediate discriminator layers between real and fake audio).

### 6.2 Vocos
* **Architecture**: Uses a Fourier-domain based backbone. Rather than using slow transposed convolutions to upscale in the time domain, Vocos predicts the **Magnitude Spectrogram** and **Phase Spectrogram** directly from the discrete embeddings in a single forward pass.
* **Synthesis**: An Inverse Short-Time Fourier Transform (ISTFT) is applied to reconstruct the waveform.
* **Pros**: Extremely fast; avoids time-domain artifacts; lower computational complexity.

### 6.3 BigVGAN
* **Architecture**: A large-scale neural vocoder designed to scale up to massive, diverse datasets.
* **Key Innovations**:
  * Replaces leaky ReLU with the **Snake Activation Function** ($x + \frac{1}{\alpha}\sin^2(\alpha x)$) to prevent high-frequency aliasing during upsampling.
  * Integrates **filtered activations** (anti-aliasing filters before upsampling layers) to guarantee mathematical continuity of generated waveforms.
  * Capable of zero-shot synthesis of highly noisy, musical, or multi-speaker out-of-distribution audio.

---

## 7. State-of-the-Art Case Studies

### 7.1 GPT-4o Voice (Native Multimodal)
* **Mechanics**: Combines Text, Audio, and Vision natively in a single Transformer model.
* **Architecture**: End-to-end tokenization. Instead of cascades, OpenAI trained a custom neural audio tokenizer and decoder capable of low-latency streams.
* **Latency**: Resolves the TTFA budget down to a mean of $232\text{ ms}$ (matching human response speeds of $200\text{--}300\text{ ms}$). It natively captures and synthesizes vocal inflections, laughter, whispers, and interruptions.

### 7.2 AudioPaLM (Google)
* **Mechanics**: Bridges text-based LLM capabilities (PaLM-2) with discrete audio tokens.
* **Acoustic Prep**: Uses SoundStream tokens for audio generation and w2v-BERT tokens for audio understanding.
* **Interleaving**: Serializes tokens within a decoder-only architecture.
* **Capability**: Excels at voice transfer. By prompting the model with a short audio clip, it can generate translation audio in a target language while preserving the original speaker's voice profile.

### 7.3 SeamlessM4T (Meta)
* **Mechanics**: End-to-end multilingual model.
* **Architecture**: Uses **w2v-BERT 2.0** as the audio encoder. The decoder uses the **UnitY2** architecture:
  1. An LLM first autoregressively generates text translation.
  2. A second-stage UnitY2 decoder generates discrete acoustic units (representing downsampled EnCodec representations).
  3. A final vocoder generates the audio.

---

## 8. Complete PyTorch Implementation: Audio-Language Projection & Sequence Generation

Below is a complete, self-contained PyTorch module demonstrating:
1. An **Audio Projector** combining convolutional frame-stacking (to reduce sequences) with a linear projection to map Audio Encoder features to the LLM token dimension.
2. A **Decoder-Only Multimodal Forward Pass** showing how text and projected audio embeddings are interleaved, padded, and prepared with attention masks for the LLM.

```python
import torch
import torch.nn as nn
import torch.nn.functional as F
from typing import List, Optional, Tuple

class AudioProjector(nn.Module):
    """
    Downsamples and projects continuous audio encoder embeddings 
    to target LLM token embedding dimension.
    """
    def __init__(self, enc_dim: int, llm_dim: int, downsample_factor: int = 2):
        super().__init__()
        self.downsample_factor = downsample_factor
        
        # 1D Convolution for temporal downsampling (reduces context length)
        # Stacking frames reduces the number of tokens processed by LLM attention.
        self.conv = nn.Conv1d(
            in_channels=enc_dim,
            out_channels=enc_dim,
            kernel_size=downsample_factor,
            stride=downsample_factor,
            padding=0
        )
        
        # Multilayer Perceptron for feature projection
        self.mlp = nn.Sequential(
            nn.Linear(enc_dim, llm_dim),
            nn.GELU(),
            nn.Linear(llm_dim, llm_dim)
        )
        
    def forward(self, x: torch.Tensor) -> torch.Tensor:
        """
        Args:
            x: Input tensor of shape (batch_size, seq_len, enc_dim)
        Returns:
            Projected embeddings: (batch_size, seq_len // downsample_factor, llm_dim)
        """
        # Conv1d expects (batch_size, channels, seq_len)
        x = x.transpose(1, 2)
        x = self.conv(x)
        x = x.transpose(1, 2)  # Back to (batch_size, compressed_seq_len, enc_dim)
        
        # Project to LLM dimensions
        return self.mlp(x)

class MultimodalLLMOrchestrator(nn.Module):
    """
    Simulates a decoder-only LLM forward pass that ingests interleaved 
    text and audio embeddings.
    """
    def __init__(self, vocab_size: int, llm_dim: int, enc_dim: int):
        super().__init__()
        self.llm_dim = llm_dim
        self.text_embeddings = nn.Embedding(vocab_size, llm_dim)
        self.audio_projector = AudioProjector(enc_dim, llm_dim, downsample_factor=2)
        
        # Simple simulated Decoder layer
        self.decoder_layer = nn.TransformerEncoderLayer(
            d_model=llm_dim,
            nhead=8,
            dim_feedforward=llm_dim * 4,
            batch_first=True,
            norm_first=True
        )
        
        self.output_head = nn.Linear(llm_dim, vocab_size)

    def forward(
        self,
        text_tokens: torch.Tensor,       # Shape: (batch_size, text_len)
        audio_features: torch.Tensor,    # Shape: (batch_size, audio_len, enc_dim)
        interleaving_index: int          # Split position to inject audio
    ) -> torch.Tensor:
        """
        Args:
            text_tokens: Tokenized text tensor.
            audio_features: Continuous audio features from encoder.
            interleaving_index: Index in text sequence where audio tokens are placed.
        Returns:
            Logits of shape (batch_size, total_seq_len, vocab_size)
        """
        batch_size = text_tokens.size(0)
        
        # 1. Embed text tokens
        text_embeds = self.text_embeddings(text_tokens)  # (B, T_text, D_llm)
        
        # 2. Project audio features
        audio_embeds = self.audio_projector(audio_features)  # (B, T_audio_compressed, D_llm)
        
        # 3. Interleave sequences: [Text_Part1] + [Audio] + [Text_Part2]
        t1 = text_embeds[:, :interleaving_index, :]
        t2 = text_embeds[:, interleaving_index:, :]
        
        multimodal_sequence = torch.cat([t1, audio_embeds, t2], dim=1)  # (B, T_total, D_llm)
        
        # 4. Generate Causal Mask (lower-triangular)
        seq_len = multimodal_sequence.size(1)
        causal_mask = torch.triu(torch.full((seq_len, seq_len), float('-inf'), device=text_tokens.device), diagonal=1)
        
        # 5. Pass through Transformer
        hidden_states = self.decoder_layer(multimodal_sequence, mask=causal_mask)
        
        # 6. Project to logits
        logits = self.output_head(hidden_states)
        return logits

# Verification Execution Block
if __name__ == "__main__":
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    print(f"Running simulation on device: {device}")
    
    # Model parameters
    vocab_size = 5000
    llm_dim = 512
    enc_dim = 768
    
    # Initialize system
    model = MultimodalLLMOrchestrator(vocab_size, llm_dim, enc_dim).to(device)
    
    # Mock data inputs
    batch_size = 2
    text_length = 10
    audio_length = 32  # 32 frames of audio features
    
    mock_text = torch.randint(0, vocab_size, (batch_size, text_length)).to(device)
    mock_audio = torch.randn(batch_size, audio_length, enc_dim).to(device)
    
    # Interleave audio in the middle of text (index 5)
    interleave_idx = 5
    
    # Run forward pass
    logits = model(mock_text, mock_audio, interleave_idx)
    
    # Check dimensions:
    # Expected audio tokens after downsampling (downsample_factor=2): 32 // 2 = 16
    # Total sequence length: 10 (text) + 16 (audio) = 26
    expected_seq_len = text_length + (audio_length // 2)
    
    print(f"Input Text Tokens Shape: {mock_text.shape}")
    print(f"Input Audio Features Shape: {mock_audio.shape}")
    print(f"Resulting Multimodal Logits Shape: {logits.shape}")
    
    assert logits.shape == (batch_size, expected_seq_len, vocab_size), "Dimension mismatch!"
    print("Assertion passed successfully! The projection and interleaving logic is valid.")
```

---

## 9. Pro-Tip: How to Impress the Interviewer

* **Frame Rate vs. Text Rate Alignment**: Point out that speech audio codecs operate at 50 Hz or 75 Hz (each frame representing $20\text{ ms}$ or $13.3\text{ ms}$). This produces roughly $50\text{--}75$ tokens per second of audio. Compare this to text tokenizers which process roughly $3\text{--}4$ tokens per second of speech. Highlighting this $15\text{--}25\times$ rate mismatch and explaining how to mitigate it (via convolution stride, Q-Formers, or dynamic frame rate pooling) proves you have designed these systems in production.
* **Explain Loss Terms for RVQ**: Explain the quantizer commitment loss ($\beta \|\mathbf{z} - \text{sg}[\mathbf{\hat{z}}]\|^2$) and codebook loss ($\|\text{sg}[\mathbf{z}] - \mathbf{\hat{z}}\|^2$) with stop-gradients (`sg`) to prevent representation collapse. Detail the use of exponential moving averages (EMA) or K-means clustering for codebook index updates.
* **Triton Custom Kernels for Codebook Embedding Lookup**: Mention that sequential serialization (delayed patterns) requires lookup tables of $R$ codebooks in parallel. Propose writing custom Triton or CUDA kernels to do joint codebook gather/embedding lookup in shared memory to bypass launcher latency overhead.

---

## 10. Advanced Follow-Up Questions & How to Answer

### Q1: How do you address the issue of codebook collapse in RVQ training, where only a fraction of the available codebook vectors are actively used?
**Answer**:
* **The Problem**: During training, a few codebook entries can receive the majority of gradient updates, while the remaining entries are ignored. Once an entry is neglected, its probability of selection falls to zero, reducing the effective bandwidth of the codec.
* **The Fix**:
  1. **Random Restart**: If an embedding's usage frequency drops below a predefined threshold (e.g., $10^{-5}$ of active assignments), we randomly re-initialize the embedding vector with a random training sample from the current batch plus minor Gaussian noise.
  2. **K-Means Initialization**: Initialize codebook vectors using K-means clustering on the first batch of encoder features rather than using uniform random initialization.
  3. **L2 Normalization (Cosine Similarity)**: Apply L2 normalization to both the encoder output embeddings and the codebook vectors, computing the assignment using Cosine Similarity instead of Euclidean Distance. This constrains the vector space and forces uniform utilization.

### Q2: For a streaming ALM, how do you handle cross-attention in the decoder if the audio frames arrive packets at a time?
**Answer**:
* **Incremental KV Caching**: Maintain a separate streaming key-value cache (KV Cache) for the audio encoder projections. As new chunk frames of audio arrive (e.g., every $20\text{ ms}$), we run the projection module only on the new frames and append their keys and values to the end of the existing multimodal KV Cache.
* **Relative Positional Embeddings**: Use relative positional encodings (e.g., RoPE) instead of absolute positional encodings for the audio tokens. Absolute encodings break down when audio streams are extended dynamically or interrupted by user barge-ins.

### Q3: How do you evaluate the quality loss of audio generated from discrete audio tokens compared to continuous mel-spectrogram vocoding?
**Answer**:
* **ViSQOL and MCD Metrics**: We measure **Mel-Cepstral Distortion (MCD)** and **Virtual Speech Quality Objective Listener (ViSQOL)** scores.
* **Analysis**: Discrete codebook reconstruction inevitably degrades fine paralinguistic and background phase information. For example, a $3\text{ kbps}$ EnCodec stream yields a ViSQOL score of $\approx 3.4$ (Fair/Good), whereas a continuous mel-spectrogram HiFi-GAN vocoder scores $\approx 4.1$ (Excellent). However, discrete tokenization enables direct coupling with autoregressive LLM architectures, which is a design trade-off where language generation capability is prioritized over audiophile-level fidelity.
