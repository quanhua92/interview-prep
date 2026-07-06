#!/usr/bin/env bash
# Convert interview prep guides to a single compiled PDF via Pandoc + XeLaTeX.
# Usage: ./scripts/popular-to-pdf.sh [output.pdf]
#
# Requirements: pandoc, xelatex (MacTeX or TeX Live)
#   brew install pandoc && brew install --cask mactex

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(dirname "$SCRIPT_DIR")"
POPULAR_DIR="$ROOT_DIR/popular"
OUTPUT="${1:-$ROOT_DIR/popular.pdf}"

# List of files in exact Roadmap order:
FILES=(
  # Directory Index & Study Roadmap
  "$POPULAR_DIR/README.md"

  # Phase 1: Core Fundamentals & Culture
  "$POPULAR_DIR/hackerrank_and_inperson_coding.md"
  "$POPULAR_DIR/behavioral_star_intellectual_honesty.md"
  "$POPULAR_DIR/behavioral_star_one_team.md"
  "$POPULAR_DIR/coding_search_rotated_array.md"
  "$POPULAR_DIR/coding_number_of_islands.md"
  "$POPULAR_DIR/coding_merge_intervals.md"
  "$POPULAR_DIR/qa_automate_test_environment.md"

  # Phase 2: Advanced Systems Coding & Interoperability
  "$POPULAR_DIR/coding_lru_cache.md"
  "$POPULAR_DIR/coding_course_schedule.md"
  "$POPULAR_DIR/coding_trie.md"
  "$POPULAR_DIR/system_lowlevel_memory_aligned_malloc.md"
  "$POPULAR_DIR/system_lowlevel_concurrency_producer_consumer.md"
  "$POPULAR_DIR/system_lowlevel_python_gil_concurrency.md"
  "$POPULAR_DIR/system_lowlevel_python_c_bindings_ctypes.md"
  "$POPULAR_DIR/qa_cpu_gpu_bottleneck_isolation.md"

  # Phase 3: GPU Hardware & Lock-Free Execution
  "$POPULAR_DIR/system_lowlevel_cuda_warp_divergence.md"
  "$POPULAR_DIR/system_lowlevel_cuda_bank_conflicts.md"
  "$POPULAR_DIR/system_lowlevel_cuda_global_memory_coalescing.md"
  "$POPULAR_DIR/system_lowlevel_concurrency_lock_free_queue.md"
  "$POPULAR_DIR/system_lowlevel_python_memory_gc.md"
  "$POPULAR_DIR/qa_vietnam_hardware_verification.md"
  "$POPULAR_DIR/qa_debug_hardware_software_integration.md"

  # Phase 4: High-Performance System Design & Voice AI
  "$POPULAR_DIR/system_lowlevel_pytorch_systems_optimization.md"
  "$POPULAR_DIR/speech_llm_nemo_riva_stack.md"
  "$POPULAR_DIR/speech_llm_voice_agent_architecture.md"
  "$POPULAR_DIR/speech_llm_latency_optimization.md"
  "$POPULAR_DIR/speech_llm_multimodal_audio_language_models.md"
  "$POPULAR_DIR/speech_llm_agent_benchmarking_evaluation.md"
  "$POPULAR_DIR/system_design_autonomous_driving_perception.md"
  "$POPULAR_DIR/system_design_distributed_gpu_training.md"
  "$POPULAR_DIR/system_design_triton_inference_server.md"
  "$POPULAR_DIR/system_design_realtime_video_analytics.md"
  "$POPULAR_DIR/system_design_gpu_microservices_bottleneck.md"
  "$POPULAR_DIR/system_design_task_scheduler_multiple_machines.md"
)

# Validate that all files exist
for file in "${FILES[@]}"; do
  if [ ! -f "$file" ]; then
    echo "Error: Required file not found: $file"
    exit 1
  fi
done

# Clean up stale build artifacts
rm -f "$OUTPUT"

echo "Compiling ${#FILES[@]} markdown files into a single PDF..."
pandoc "${FILES[@]}" \
  --from markdown \
  --pdf-engine=xelatex \
  --variable=geometry:"margin=0.75in" \
  --variable=fontsize:"11pt" \
  --variable=fontfamily:"helvet" \
  --variable=linkcolor:"blue" \
  --variable=urlcolor:"blue" \
  --variable=linestretch:"1.15" \
  --number-sections \
  --toc \
  --standalone \
  --output "$OUTPUT"

echo "Done: $OUTPUT"
