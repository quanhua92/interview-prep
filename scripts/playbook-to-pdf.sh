#!/usr/bin/env bash
# Convert interview prep guides to PDFs via Pandoc + XeLaTeX.
#
# Outputs:
#   playbook/pdfs/playbook.pdf         — curated cross-topic study guide
#   playbook/pdfs/foundation.pdf      — Tier 1: Foundation (39 problems)
#   playbook/pdfs/intermediate.pdf    — Tier 2: Intermediate (63 problems)
#   playbook/pdfs/advanced.pdf        — Tier 3: Advanced (19 problems)
#   playbook/pdfs/expert.pdf          — Tier 4: Expert (24 problems)
#   playbook/pdfs/llm.pdf             — LLM Systems (34 topics)
#
# Usage:
#   ./scripts/playbook-to-pdf.sh              # build all 6 PDFs
#   ./scripts/playbook-to-pdf.sh --tiers-only # skip playbook.pdf, build 5 tier/topic PDFs
#   ./scripts/playbook-to-pdf.sh --main-only  # build playbook.pdf only
#
# Requirements: pandoc, xelatex (MacTeX or TeX Live)
#   brew install pandoc && brew install --cask mactex

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(dirname "$SCRIPT_DIR")"
POPULAR_DIR="$ROOT_DIR/playbook"
TIERS_DIR="$POPULAR_DIR/tiers"
PDFS_DIR="$POPULAR_DIR/pdfs"

# --------------------------------------------------------------------------- #
# Flags
# --------------------------------------------------------------------------- #
BUILD_MAIN=true
BUILD_TIERS=true

for arg in "$@"; do
  case "$arg" in
    --tiers-only) BUILD_MAIN=false ;;
    --main-only)  BUILD_TIERS=false ;;
  esac
done

# --------------------------------------------------------------------------- #
# Shared pandoc options
# --------------------------------------------------------------------------- #
PANDOC_OPTS=(
  --from markdown-smart
  --pdf-engine=xelatex
  --lua-filter="$SCRIPT_DIR/strip-emoji.lua"
  --variable=geometry:"margin=0.75in"
  --variable=fontsize:"11pt"
  --variable=fontfamily:"helvet"
  --variable=monofont:"Menlo"
  --variable=linkcolor:"blue"
  --variable=urlcolor:"blue"
  --variable=linestretch:"1.15"
  --number-sections
  --toc
  --standalone
)

# --------------------------------------------------------------------------- #
# Helper: compile an ordered list of markdown files into a PDF
# --------------------------------------------------------------------------- #
compile_pdf() {
  local OUTPUT="$1"
  shift
  local FILES=("$@")

  # Validate every file exists
  for f in "${FILES[@]}"; do
    if [ ! -f "$f" ]; then
      echo "  ERROR: file not found: $f"
      exit 1
    fi
  done

  rm -f "$OUTPUT"
  echo "  Compiling ${#FILES[@]} files → $(basename "$OUTPUT") ..."
  pandoc "${FILES[@]}" "${PANDOC_OPTS[@]}" --output "$OUTPUT"
  echo "  ✓ $(basename "$OUTPUT")"
}

# --------------------------------------------------------------------------- #
# 1. playbook.pdf — curated cross-topic guide (unchanged)
# --------------------------------------------------------------------------- #
if $BUILD_MAIN; then
  MAIN_OUTPUT="$PDFS_DIR/playbook.pdf"
  MAIN_FILES=(
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
  echo "[1/6] Building playbook.pdf ..."
  compile_pdf "$MAIN_OUTPUT" "${MAIN_FILES[@]}"
fi

# --------------------------------------------------------------------------- #
# 2. foundation.pdf — Tier 1 (39 problems, module order from README)
# --------------------------------------------------------------------------- #
if $BUILD_TIERS; then
  F="$TIERS_DIR/foundation"
  echo "[2/6] Building foundation.pdf ..."
  compile_pdf "$PDFS_DIR/foundation.pdf" \
    "$F/README.md" \
    \
    "$F/coding_container_water.md" \
    "$F/coding_three_sum.md" \
    "$F/coding_two_sum.md" \
    "$F/coding_is_subsequence.md" \
    "$F/coding_heaters.md" \
    \
    "$F/coding_longest_uncommon_subsequence_ii.md" \
    "$F/coding_longest_word_in_dictionary_through_deleting.md" \
    "$F/coding_k_diff_pairs_in_an_array.md" \
    "$F/coding_number_of_segments_in_a_string.md" \
    "$F/coding_license_key_formatting.md" \
    "$F/coding_detect_capital.md" \
    "$F/coding_longest_uncommon_subsequence_i.md" \
    \
    "$F/coding_linked_list_cycle.md" \
    "$F/coding_happy_number.md" \
    "$F/coding_middle_of_linked_list.md" \
    \
    "$F/coding_longest_substring.md" \
    "$F/coding_longest_substring_with_at_least_k_repeating_characters.md" \
    "$F/coding_longest_repeating_char.md" \
    "$F/coding_find_anagrams.md" \
    "$F/coding_permutation_in_string.md" \
    \
    "$F/coding_merge_intervals.md" \
    "$F/coding_insert_interval.md" \
    "$F/coding_meeting_rooms.md" \
    "$F/coding_teemo_attacking.md" \
    \
    "$F/coding_insert_delete_getrandom_o1.md" \
    "$F/coding_linked_list_random_node.md" \
    "$F/coding_perfect_rectangle.md" \
    "$F/coding_random_pick_index.md" \
    "$F/coding_number_of_boomerangs.md" \
    "$F/coding_keyboard_row.md" \
    "$F/coding_encode_and_decode_tinyurl.md" \
    "$F/coding_distribute_candies.md" \
    \
    "$F/coding_level_order.md" \
    "$F/coding_shortest_path_binary.md" \
    "$F/coding_serialize_and_deserialize_bst.md" \
    "$F/coding_island_perimeter.md" \
    "$F/coding_find_bottom_left_tree_value.md" \
    "$F/coding_find_largest_value_in_each_tree_row.md" \
    "$F/coding_rotting_oranges.md"

  # -------------------------------------------------------------------------- #
  # 3. intermediate.pdf — Tier 2 (63 problems, module order from README)
  # -------------------------------------------------------------------------- #
  I="$TIERS_DIR/intermediate"
  echo "[3/6] Building intermediate.pdf ..."
  compile_pdf "$PDFS_DIR/intermediate.pdf" \
    "$I/README.md" \
    \
    "$I/coding_product_except_self.md" \
    "$I/coding_subarray_sum_equals_k.md" \
    "$I/coding_subarray_product_less_than_k.md" \
    "$I/coding_continuous_subarray_sum.md" \
    "$I/coding_contiguous_array.md" \
    "$I/coding_random_pick_with_weight.md" \
    \
    "$I/coding_find_min_rotated.md" \
    "$I/coding_first_bad_version.md" \
    "$I/coding_data_stream_as_disjoint_intervals.md" \
    "$I/coding_russian_doll_envelopes.md" \
    "$I/coding_smallest_good_base.md" \
    "$I/coding_random_point_in_non_overlapping_rectangles.md" \
    "$I/coding_binary_search.md" \
    \
    "$I/coding_valid_parentheses.md" \
    "$I/coding_min_stack.md" \
    "$I/coding_decode_string.md" \
    \
    "$I/coding_jump_game_three.md" \
    "$I/coding_number_of_islands.md" \
    "$I/coding_mini_parser.md" \
    "$I/coding_longest_absolute_file_path.md" \
    "$I/coding_delete_node_in_a_bst.md" \
    "$I/coding_most_frequent_subtree_sum.md" \
    "$I/coding_convert_bst_to_greater_tree.md" \
    "$I/coding_array_nesting.md" \
    "$I/coding_subtree_of_another_tree.md" \
    "$I/coding_max_area_island.md" \
    \
    "$I/coding_merge_k_sorted_lists.md" \
    "$I/coding_majority_element.md" \
    "$I/coding_construct_quad_tree.md" \
    "$I/coding_reverse_pairs.md" \
    "$I/coding_sort_an_array.md" \
    \
    "$I/coding_median_finder.md" \
    "$I/coding_design_twitter.md" \
    "$I/coding_sliding_window_median.md" \
    \
    "$I/coding_kth_largest.md" \
    "$I/coding_top_k_frequent.md" \
    "$I/coding_trapping_rain_water_ii.md" \
    "$I/coding_k_closest_points.md" \
    \
    "$I/coding_implement_rand10_using_rand7.md" \
    "$I/coding_random_flip_matrix.md" \
    \
    "$I/coding_number_of_1_bits.md" \
    "$I/coding_single_number.md" \
    "$I/coding_counting_bits.md" \
    "$I/coding_number_complement.md" \
    \
    "$I/coding_poor_pigs.md" \
    "$I/coding_generate_random_point_in_a_circle.md" \
    "$I/coding_largest_palindrome_product.md" \
    "$I/coding_next_greater_element_iii.md" \
    "$I/coding_find_the_closest_palindrome.md" \
    \
    "$I/coding_climbing_stairs.md" \
    "$I/coding_house_robber.md" \
    "$I/coding_coin_change.md" \
    "$I/coding_frog_jump.md" \
    "$I/coding_count_the_repetitions.md" \
    "$I/coding_unique_substrings_in_wraparound_string.md" \
    "$I/coding_freedom_trail.md" \
    "$I/coding_longest_palindromic_subsequence.md" \
    "$I/coding_coin_change_ii.md" \
    "$I/coding_student_attendance_record_ii.md" \
    "$I/coding_optimal_division.md" \
    "$I/coding_out_of_boundary_paths.md" \
    "$I/coding_super_egg_drop.md" \
    \
    "$I/coding_lfu_cache.md"

  # -------------------------------------------------------------------------- #
  # 4. advanced.pdf — Tier 3 (19 problems, module order from README)
  # -------------------------------------------------------------------------- #
  A="$TIERS_DIR/advanced"
  echo "[4/6] Building advanced.pdf ..."
  compile_pdf "$PDFS_DIR/advanced.pdf" \
    "$A/README.md" \
    \
    "$A/coding_missing_number.md" \
    "$A/coding_find_duplicates.md" \
    "$A/coding_find_disappeared.md" \
    \
    "$A/coding_search_rotated.md" \
    "$A/coding_split_array_sum.md" \
    "$A/coding_koko_bananas.md" \
    \
    "$A/coding_letter_combinations.md" \
    "$A/coding_combination_sum.md" \
    "$A/coding_subsets.md" \
    "$A/coding_matchsticks_to_square.md" \
    "$A/coding_zuma_game.md" \
    "$A/coding_non_decreasing_subsequences.md" \
    \
    "$A/coding_permutations.md" \
    "$A/coding_combinations.md" \
    "$A/coding_subsets_ii.md" \
    \
    "$A/coding_implement_trie.md" \
    "$A/coding_design_add_search.md" \
    "$A/coding_word_search_ii.md" \
    "$A/coding_concatenated_words.md"

  # -------------------------------------------------------------------------- #
  # 5. expert.pdf — Tier 4 (24 problems, module order from README)
  # -------------------------------------------------------------------------- #
  E="$TIERS_DIR/expert"
  echo "[5/6] Building expert.pdf ..."
  compile_pdf "$PDFS_DIR/expert.pdf" \
    "$E/README.md" \
    \
    "$E/coding_rotate_image.md" \
    "$E/coding_spiral_matrix.md" \
    "$E/coding_diagonal_traverse.md" \
    "$E/coding_01_matrix.md" \
    \
    "$E/coding_course_schedule.md" \
    "$E/coding_course_schedule_ii.md" \
    "$E/coding_town_judge.md" \
    "$E/coding_connected_components.md" \
    "$E/coding_redundant_connection.md" \
    "$E/coding_satisfiability_equations.md" \
    \
    "$E/coding_jump_game.md" \
    "$E/coding_gas_station.md" \
    "$E/coding_candy.md" \
    "$E/coding_minimum_number_of_arrows_to_burst_balloons.md" \
    "$E/coding_assign_cookies.md" \
    "$E/coding_ipo.md" \
    "$E/coding_task_scheduler.md" \
    "$E/coding_task_scheduler_multi_machine.md" \
    \
    "$E/coding_largest_rectangle.md" \
    "$E/coding_132_pattern.md" \
    "$E/coding_next_greater_element_ii.md" \
    "$E/coding_daily_temperatures.md" \
    "$E/coding_car_fleet.md" \
    "$E/coding_sum_of_subarray_minimums.md"

  # -------------------------------------------------------------------------- #
  # 6. llm.pdf — LLM Systems (34 topics, module order from TODO)
  # -------------------------------------------------------------------------- #
  LLM_DIR="$POPULAR_DIR/llm"
  echo "[6/6] Building llm.pdf ..."
  compile_pdf "$PDFS_DIR/llm.pdf" \
    "$LLM_DIR/README.md" \
    \
    "$LLM_DIR/llm_normalization.md" \
    "$LLM_DIR/llm_tokenization.md" \
    "$LLM_DIR/llm_rope.md" \
    "$LLM_DIR/llm_mlp_activation.md" \
    "$LLM_DIR/llm_causal_mask.md" \
    \
    "$LLM_DIR/llm_kv_cache.md" \
    "$LLM_DIR/llm_flash_attention.md" \
    "$LLM_DIR/llm_gqa.md" \
    "$LLM_DIR/llm_quantization.md" \
    \
    "$LLM_DIR/llm_sampling.md" \
    "$LLM_DIR/llm_paged_attention.md" \
    "$LLM_DIR/llm_block_manager.md" \
    "$LLM_DIR/llm_scheduler.md" \
    "$LLM_DIR/llm_prefix_cache.md" \
    "$LLM_DIR/llm_cuda_graphs.md" \
    \
    "$LLM_DIR/llm_peft_lora.md" \
    "$LLM_DIR/llm_gradient_checkpointing.md" \
    \
    "$LLM_DIR/llm_nccl_collectives.md" \
    "$LLM_DIR/llm_ddp.md" \
    "$LLM_DIR/llm_tensor_parallel.md" \
    "$LLM_DIR/llm_pipeline_parallel.md" \
    "$LLM_DIR/llm_zero.md" \
    "$LLM_DIR/llm_distributed_gpu_training.md" \
    \
    "$LLM_DIR/llm_moe_routing.md" \
    "$LLM_DIR/llm_speculative_decoding.md" \
    "$LLM_DIR/llm_lmcache.md" \
    "$LLM_DIR/llm_disaggregated_serving.md" \
    "$LLM_DIR/llm_ktransformers_offload.md" \
    "$LLM_DIR/llm_jax_xla_tpu.md" \
    \
    "$LLM_DIR/llm_nemo_riva_stack.md" \
    "$LLM_DIR/llm_voice_agent_architecture.md" \
    "$LLM_DIR/llm_latency_optimization.md" \
    "$LLM_DIR/llm_multimodal_audio.md" \
    "$LLM_DIR/llm_agent_benchmarking.md"

  echo ""
  echo "Tier and LLM PDFs written to: $PDFS_DIR/"
fi

echo ""
echo "All done!"
