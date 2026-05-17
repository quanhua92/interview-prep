# Design a Video Conferencing System

Source: [Video Conferencing (CalibreOS)](https://www.calibreos.com/learn/hld-video-conferencing)

## One-Liner
Design a real-time video conferencing platform supporting 300M daily participants and 1000-person meetings using SFU media routing, WebRTC signaling, and adaptive bitrate via simulcast.

## Functional Requirements
- Join/leave video meetings with audio and video streams
- Support meetings from 2-person calls up to 1000-person webinars
- Screen sharing as a separate video track
- Cloud recording of meetings
- Active speaker detection and gallery view rendering
- Support browser (WebRTC native), mobile (iOS/Android SDK), and desktop clients

## Non-Functional Requirements
- Glass-to-glass latency under ~150ms for conversational meetings (~300ms acceptable for webinars)
- Media transport over UDP (not TCP) — retransmission delays are unacceptable
- 300M daily meeting participants at peak (Zoom 2020 scale)
- ~10M peak concurrent participants
- Handle ~15-20% of connections requiring TURN relay due to NAT

## Key Scale Questions
- 300M daily participants, ~3.3B participant-minutes/day
- Peak concurrent: ~10M participants (30:1 daily-to-concurrent ratio)
- Bandwidth per participant: 2.15 Mbps simulcast upload, ~2.4 Mbps download (active speaker layout)
- Total ingress: ~21.5 Tbps to SFUs; total egress: ~24 Tbps from SFUs
- TURN relay at 15%: ~6.8 Tbps relay bandwidth (~$153K/hour at peak)
- SFU sizing: ~5,400 nodes at peak (1 node handles ~500 rooms at 4 Gbps throughput)

## Core Components
- **Signaling Service**: WebSocket-based (TCP) for SDP offer/answer exchange, room management, ICE coordination
- **SFU (Selective Forwarding Unit)**: Forwards raw RTP packets — no decode/encode. Reads only RTP headers (SSRC, sequence number, timestamp) for forwarding decisions
- **STUN Server**: Discovers public IP:port for NAT traversal. Resolves ~80-85% of connections
- **TURN Relay (COTURN)**: Relays all media when direct UDP fails. Required for ~15-20% of connections (symmetric NAT)
- **SFU Coordinator**: Redis-backed service tracking room-to-SFU assignment, health checks, and failover
- **Recording Pipeline**: RTP tap from SFU -> Kafka (at-least-once) -> Recording Worker -> S3. Fully decoupled from live media path
- **Media Service**: Handles screen sharing tracks as separate video streams

## Key Design Decisions

### Media Routing Topology: SFU over MCU and P2P
- **P2P**: Every participant sends to every other. O(n^2) connections. Upload per participant = (n-1) x 1.5 Mbps. Dead above 4 participants — exceeds home broadband limits
- **MCU**: Server decodes all streams, composites into one, re-encodes per participant. Minimal client bandwidth but server CPU is O(n) decode+encode. Adds 100-200ms latency. Used in legacy enterprise (Cisco, Polycom) and phone dial-in
- **SFU**: Forwards raw RTP packets without decode/encode. Server CPU scales with packet throughput, not transcoding. Adds only 2-10ms latency. Combined with simulcast, supports 1000+ participants per meeting

### Active Speaker and Gallery View
- SFU detects active speakers via RTCP audio level reports (server-side)
- Rendering decisions (which tiles, which resolution) are client-side
- SFU forwards active speaker at 720p, others at 180p or suppressed
- This is why SFU can serve 1000 participants: server never does compute proportional to participant count

### Adaptive Bitrate via Simulcast
- Sender encodes 3 layers simultaneously: high (720p @ 1.5 Mbps), medium (360p @ 0.5 Mbps), low (180p @ 0.15 Mbps)
- Total upload: 2.15 Mbps per sender
- SFU selects appropriate layer per receiver based on estimated bandwidth
- Layer switch requires IDR keyframe (RTCP PLI to sender)

### Bandwidth Estimation: TWCC over REMB
- TWCC (Transport-Wide Congestion Control): receivers report raw arrival timestamps every ~100ms
- SFU runs GCC (Google Congestion Control) algorithm server-side
- More accurate than legacy REMB, handles NAT path asymmetry

## API Endpoints
| Method | Path | Description |
|--------|------|-------------|
| POST | /api/rooms | Create a new meeting room |
| GET | /api/rooms/{id} | Get room info and join token |
| WS | /api/signaling | WebSocket for SDP offer/answer and ICE candidate exchange |
| POST | /api/rooms/{id}/recording/start | Start cloud recording |
| POST | /api/rooms/{id}/recording/stop | Stop cloud recording |
| GET | /api/recordings/{id} | Get recording metadata and download URL |

## Database Schema
| Column | Type | Notes |
|--------|------|-------|
| room_id | UUID | PK, meeting identifier |
| host_id | BIGINT | Meeting creator user ID |
| status | ENUM | active, ended, scheduled |
| max_participants | INT | Capacity limit (e.g., 1000) |
| created_at | TIMESTAMP | Room creation time |
| ended_at | TIMESTAMP | When meeting ended |
| recording_enabled | BOOLEAN | Whether cloud recording is active |

| Column | Type | Notes |
|--------|------|-------|
| participant_id | BIGINT | PK |
| room_id | UUID | FK to rooms |
| user_id | BIGINT | FK to users |
| joined_at | TIMESTAMP | When participant joined |
| left_at | TIMESTAMP | When participant left |
| sfu_node | VARCHAR | SFU node assigned for media |

| Column | Type | Notes |
|--------|------|-------|
| recording_id | UUID | PK |
| room_id | UUID | FK to rooms |
| s3_url | VARCHAR | Final recording file location |
| duration_sec | INT | Recording length |
| status | ENUM | processing, ready, failed |

## Deep Dive Topics
- **NAT Traversal (ICE/STUN/TURN)**: Three-phase connection: SDP signaling -> ICE candidate gathering (host, server-reflexive via STUN, relay via TURN) -> connectivity checks. Symmetric NAT forces TURN. Trickle ICE reduces setup from 2-5s to 500ms-1s
- **ICE Restart for SFU Failover**: On SFU node failure, coordinator reassigns rooms and sends ICE restart (new ice-ufrag/ice-pwd). Preserves DTLS/SRTP state. Users see ~1s frozen video, not full reconnect
- **FEC for Packet Loss**: XOR-based parity packets (FlexFEC/RED+ULPFEC) add 10-20% overhead but eliminate retransmission round-trips for isolated losses. Above 5% loss, NACK retransmission storms can cascade
- **Recording Pipeline Resilience**: Kafka with at-least-once delivery and 24h retention. If recording worker crashes, another replays the partition from offset 0 and rebuilds idempotently
- **Clock Drift and Lip Sync**: Each simulcast layer has independent RTP timestamp clock. RTCP SR (Sender Report) maps RTP timestamps to NTP wall clock for alignment
- **Cascaded SFU for Multi-Region**: Regional SFU clusters connected via high-bandwidth backbone. Users connect to nearest SFU; SFUs exchange media inter-region

## Follow-Up Variations
- How would you design end-to-end encryption (E2EE) given that the SFU must read RTP headers?
- How would you implement breakout rooms (splitting a meeting into sub-groups)?
- What changes for a broadcast-only virtual event with 100K viewers (HLS/DASH vs WebRTC)?
- How do you handle a participant on 3G joining a 50-person meeting (simulcast layer selection)?
- What is the cost impact if corporate VPN pushes TURN relay rates to 40-50% during all-hands meetings?
