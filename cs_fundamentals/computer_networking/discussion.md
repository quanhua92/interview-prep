# Computer Networking

OSI vs TCP/IP models, transport protocols, HTTP versions, DNS, TLS, CDN, and load balancing for SWE interviews.

## Key Concepts

- **OSI vs TCP/IP Model**: The OSI model has 7 layers (Physical, Data Link, Network, Transport, Session, Presentation, Application) and is a theoretical reference. The TCP/IP model has 4 layers (Link, Internet, Transport, Application) and is the practical model underlying the internet. TCP/IP merges OSI layers 5-7 into a single Application layer.
- **TCP vs UDP**: TCP provides reliable, ordered, error-checked delivery with flow and congestion control, at the cost of higher latency and overhead. UDP provides fast, connectionless delivery with no guarantees on order or reliability, making it ideal for real-time applications like video streaming and gaming.
- **DNS Resolution**: The Domain Name System translates human-readable domain names to IP addresses through a hierarchy of recursive and iterative queries: browser cache, OS cache, local DNS resolver, root server, TLD server, and authoritative name server.
- **TLS Handshake**: Transport Layer Security establishes a secure connection using asymmetric cryptography to exchange a session key, then switches to symmetric encryption for data transfer. TLS 1.3 simplifies this to a single round trip, improving performance over TLS 1.2.
- **CDN (Content Delivery Network)**: A geographically distributed network of proxy servers that caches and serves content closer to end users, reducing latency and origin server load. CDNs use DNS-based routing to direct users to the nearest edge server.

## Common Questions with Brief Answer Outlines

**Q: What happens when you type a URL into the browser?**
- Browser checks its cache for the URL; if not found, initiates DNS resolution to get the server IP.
- Browser establishes a TCP connection with the server (three-way handshake: SYN, SYN-ACK, ACK).
- If HTTPS, a TLS handshake follows to establish encryption and exchange session keys.
- Browser sends an HTTP request; the server processes it and returns a response.
- Browser parses the HTML, renders the DOM, and fetches additional resources (CSS, JS, images).

**Q: Compare HTTP/1.1, HTTP/2, and HTTP/3.**
- HTTP/1.1 uses text-based format, supports persistent connections (keep-alive), but has head-of-line blocking on each TCP connection.
- HTTP/2 introduces binary framing, multiplexing (multiple streams over one TCP connection), header compression (HPACK), and server push.
- HTTP/3 replaces TCP with QUIC (built on UDP), eliminating TCP-level head-of-line blocking, providing faster connection setup (0-RTT), and improved loss recovery.
- All three support TLS, but HTTP/3 mandates TLS 1.3.

**Q: How does TCP ensure reliable delivery?**
- Sequence numbers track byte order so the receiver can reassemble segments correctly.
- Acknowledgments (ACKs) confirm received data; unacknowledged segments are retransmitted.
- Flow control (sliding window) prevents the sender from overwhelming the receiver's buffer.
- Congestion control (slow start, congestion avoidance) adapts sending rate to network conditions.

**Q: How does load balancing work?**
- A load balancer distributes incoming traffic across multiple backend servers to improve availability and reliability.
- Common algorithms include round-robin, least connections, IP hash, and weighted distribution.
- Layer 4 (transport) load balancing routes based on IP/port; Layer 7 (application) load balancing can route based on HTTP headers, paths, or cookies.
- Health checks continuously monitor backend servers and remove unhealthy ones from rotation.

**Q: Explain the TLS handshake process.**
- Client sends a ClientHello with supported cipher suites and a random number.
- Server responds with ServerHello, its certificate, and its own random number.
- Client verifies the server's certificate against trusted CAs and generates a pre-master secret, encrypted with the server's public key.
- Both sides derive the session key from the pre-master secret and random numbers.
- TLS 1.3 reduces this to one round trip by combining steps and supporting 0-RTT resumption.

**Q: What is the difference between a socket and a port?**
- A port is a numerical identifier (0-65535) used to distinguish between multiple endpoints on a single machine; well-known ports include 80 (HTTP), 443 (HTTPS), 22 (SSH), and 3306 (MySQL).
- A socket is one endpoint of a two-way communication link between two programs, identified by the tuple (source IP, source port, destination IP, destination port, protocol). It is an API that applications use to send and receive data over the network.
- A port alone does not identify a communication session; a socket uniquely identifies a connection. A single port can have multiple sockets (e.g., multiple connections to a web server on port 443).

**Q: How does NAT (Network Address Translation) work and why is it used?**
- NAT allows multiple devices on a private network to share a single public IP address when accessing the internet.
- The NAT router maintains a translation table mapping (private IP, private port) to (public IP, public port). When a device sends a packet, the router rewrites the source IP/port; when a response arrives, it rewrites the destination and forwards to the correct internal device.
- It was created to mitigate IPv4 address exhaustion by allowing entire networks to use private address ranges (10.0.0.0/8, 192.168.0.0/16).
- Drawbacks: NAT breaks end-to-end connectivity (incoming connections require port forwarding), complicates peer-to-peer protocols, and adds processing overhead. IPv6 was designed to eliminate the need for NAT.

**Q: What are ARP, ICMP, and DHCP?**
- ARP (Address Resolution Protocol) maps an IP address to a MAC address on a local network. A host broadcasts an ARP request ("who has 192.168.1.5?") and the owner responds with its MAC address. Results are cached in the ARP table.
- ICMP (Internet Control Message Protocol) is used for diagnostic and error reporting. It powers tools like ping (echo request/reply) and traceroute (TTL exceeded messages). Routers send ICMP errors when a host is unreachable, a packet's TTL expires, or fragmentation is needed but not allowed.
- DHCP (Dynamic Host Configuration Protocol) automatically assigns IP addresses, subnet masks, default gateways, and DNS servers to devices joining a network. Devices broadcast a DHCP discover message; a DHCP server responds with an offer; the device requests the offered address; the server acknowledges.

## Quick Reference Table

| Feature | TCP | UDP |
|---|---|---|
| Connection | Connection-oriented (3-way handshake) | Connectionless |
| Reliability | Guaranteed delivery, ordering, error checking | Best-effort, no guarantees |
| Flow control | Sliding window mechanism | None |
| Speed | Slower due to overhead | Faster, lower latency |
| Use cases | Web browsing, email, file transfer | Streaming, gaming, DNS queries, VoIP |
| Header size | 20-60 bytes | 8 bytes |
