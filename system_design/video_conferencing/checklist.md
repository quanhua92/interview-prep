# Design a Video Conferencing System — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] What is the maximum meeting size (small meetings vs 1000-person webinars)?
  - [ ] What platforms must be supported (browser WebRTC, mobile SDK, desktop app)?
  - [ ] What is the latency target (~150ms glass-to-glass for meetings, ~300ms for webinars)?
  - [ ] Is cloud recording required? Does E2EE need to be supported?
  - [ ] What are the geographic requirements (single-region vs multi-region)?
- [ ] List functional requirements (3-5 items):
  - [ ] Users can join/leave video meetings with audio and video
  - [ ] Support 2-person calls up to 1000-person webinars
  - [ ] Screen sharing as a separate video track
  - [ ] Cloud recording of meetings
  - [ ] Active speaker detection and adaptive gallery view
- [ ] List non-functional requirements (latency, availability, scale):
  - [ ] Glass-to-glass latency under ~150ms (no buffering, UDP transport)
  - [ ] High availability: recording failures must not affect live call quality
  - [ ] Scalability: 300M daily participants, ~10M peak concurrent
  - [ ] NAT traversal: must handle ~15-20% TURN relay connections
- [ ] State your scale estimates (users, bandwidth, infrastructure):
  - [ ] ~300M daily participants, ~10M peak concurrent
  - [ ] ~2.15 Mbps simulcast upload per participant
  - [ ] ~2.4 Mbps download per participant (active speaker layout)
  - [ ] ~21.5 Tbps ingress / ~24 Tbps egress to SFUs
  - [ ] ~5,400 SFU nodes at peak, ~6.8 Tbps TURN relay bandwidth

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw a simple box diagram: Client -> [Signaling Service (WS)] + [STUN/TURN] -> [SFU Cluster] -> [Recording Pipeline (Kafka -> Worker -> S3)]
- [ ] Identify the main operations and their access patterns:
  - [ ] `POST /api/rooms` — create a meeting room (write, low QPS)
  - [ ] `WS /api/signaling` — SDP/ICE exchange for connection setup (persistent, per-call)
  - [ ] `POST /api/rooms/{id}/recording/start` — start cloud recording (write, low QPS)
  - [ ] `GET /api/recordings/{id}` — retrieve recording (read, async)
- [ ] Note the signaling vs media plane separation:
  - [ ] Signaling: reliable WebSocket (TCP) for SDP offer/answer and room coordination
  - [ ] Media: UDP (SRTP) for all audio/video — cannot afford TCP retransmission delays
  - [ ] Recording: fully decoupled async pipeline, never on the live media path
- [ ] Present the diagram and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain media routing topology choice and justify:
  - [ ] P2P: O(n^2) connections, dead above 4 participants (upload bandwidth exceeded)
  - [ ] MCU: Server decodes+composites+encodes, CPU-heavy, adds 100-200ms latency
  - [ ] SFU: Forwards raw RTP packets, no decode/encode, 2-10ms latency, scales with bandwidth not compute
  - [ ] State your choice: SFU + simulcast (production standard used by Zoom, Meet, Teams)
- [ ] Define API endpoints with method, path, request/response:
  - [ ] `POST /api/rooms` -> `{"room_id": "...", "join_url": "..."}`
  - [ ] `GET /api/rooms/{id}` -> `{"room_id": "...", "status": "active", "participants": [...]}`
  - [ ] `WS /api/signaling` -> SDP offer/answer + ICE candidates
  - [ ] `POST /api/rooms/{id}/recording/start` -> `{"recording_id": "...", "status": "processing"}`
  - [ ] `GET /api/recordings/{id}` -> `{"s3_url": "...", "duration_sec": 3600}`
- [ ] Sketch the database schema:
  - [ ] Table `rooms`: `room_id (UUID)`, `host_id`, `status`, `max_participants`, `created_at`, `ended_at`, `recording_enabled`
  - [ ] Table `participants`: `participant_id`, `room_id (FK)`, `user_id`, `joined_at`, `left_at`, `sfu_node`
  - [ ] Table `recordings`: `recording_id (UUID)`, `room_id (FK)`, `s3_url`, `duration_sec`, `status`
- [ ] Discuss data store choices:
  - [ ] Rooms/participants: SQL (PostgreSQL) for transactional consistency on join/leave
  - [ ] SFU assignment state: Redis for fast room-to-node mapping and health tracking
  - [ ] Recording artifacts: S3/object storage; Kafka for buffering RTP frames
- [ ] Walk through the main flow end-to-end:
  - [ ] Join flow: client creates room -> gets join token -> WebSocket signaling -> SDP offer/answer -> ICE candidate gathering (host -> STUN -> TURN) -> media flows via SFU
  - [ ] Meeting flow: sender encodes 3 simulcast layers -> SFU receives all -> forwards appropriate layer per receiver based on TWCC bandwidth estimate
  - [ ] Recording flow: SFU taps RTP -> Kafka -> recording worker -> MP4 assembly -> S3

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Explain NAT traversal (ICE/STUN/TURN):
  - [ ] Host candidates (LAN IP, rarely useful), server-reflexive (STUN, ~80-85%), relay (TURN, ~15-20%)
  - [ ] Symmetric NAT problem: different external port per destination, forces TURN relay
  - [ ] Trickle ICE: run gathering and checks in parallel, reduces setup to 500ms-1s
- [ ] Explain adaptive bitrate with simulcast:
  - [ ] Sender encodes 3 layers: 720p/1.5 Mbps, 360p/0.5 Mbps, 180p/0.15 Mbps (total 2.15 Mbps upload)
  - [ ] TWCC feedback: receivers report arrival timestamps, SFU runs GCC for bandwidth estimation
  - [ ] SFU selects layer per receiver; on switch, sends RTCP PLI for keyframe
- [ ] Explain active speaker for large meetings:
  - [ ] SFU detects via RTCP audio level reports, maintains top 5-7 speakers
  - [ ] Forwards active speaker at 720p, others at 180p or suppressed
  - [ ] Client-side rendering decision (not server-side compositing)
- [ ] Address failure modes:
  - [ ] SFU failure: coordinator detects missed heartbeats -> reassigns rooms -> ICE restart (preserves DTLS/SRTP state, ~1s frozen video)
  - [ ] TURN overload: corporate VPN can push relay to 40-50%; over-provision 3-4x peak
  - [ ] Packet loss cascade: FEC (FlexFEC/RED+ULPFEC) adds 10-20% overhead, eliminates retransmission for isolated losses
  - [ ] Recording worker crash: Kafka replay from offset 0, idempotent rebuild, live call unaffected
- [ ] Discuss multi-region architecture:
  - [ ] Cascaded SFU: regional clusters connected via high-bandwidth backbone
  - [ ] Users connect to nearest regional SFU; SFUs exchange media inter-region
  - [ ] COTURN deployed in 20+ regions to minimize relay latency

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made and why (SFU over MCU, simulcast bandwidth cost, TURN expense)
- [ ] Mention what you would improve with more time (E2EE, breakout rooms, virtual backgrounds, ASR transcription)
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
