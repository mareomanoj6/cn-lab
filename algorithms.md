# Algorithms - Networking Lab Experiments (q1 - q17)

## Q1 - Familiarizing Linux networking commands

1. Open a Linux terminal.
2. Execute the following commands one by one: `ifconfig`, `ifplugstatus`, `iftop`, `ping`, `ip`, `traceroute`, `mtr`, `netstat`, `whois`, `nmap`, `nmcli`, `speedtest-cli`, `bmon`, `nslookup`, and `tcpdump`.
3. Observe the output of each command to understand its purpose in network configuration, monitoring, and diagnostics.

## Q2 - HTTP Packet Analysis

1. Clear the web browser's cache memory.
2. Start a packet capture in Wireshark.
3. Visit any webpage to generate HTTP traffic.
4. Apply the `http` filter in Wireshark to isolate HTTP messages.
5. Stop the capture.
6. Analyze the first GET message to find:
    - Source and destination IP addresses.
    - Acceptable medium format, language, encoding, and character set.
    - Target URL and User-Agent string.
7. Analyze the first response message to find:
    - Source and destination IP addresses.
    - HTTP status code.
    - The `Last-Modified` timestamp of the HTML file.
    - The `Content-Length` value.
    - The HTTP version used by the browser.
8. Calculate the response time by subtracting the GET request timestamp from the response message timestamp.

## Q3 - SMTP Packet Analysis

1. Compose an e-mail to yourself but do not send it yet.
2. Start a packet capture in Wireshark.
3. Send the e-mail.
4. Apply the `smtp` filter in Wireshark.
5. Stop the capture.
6. Identify the client and server IP addresses from the packets.
7. Determine the SMTP client port (usually in the ephemeral range) and the SMTP server port (typically 25 or 587).
8. Examine the SMTP commands (e.g., HELO, MAIL FROM, RCPT TO, DATA) and the server's response codes.
9. Locate and extract the content of the Internet Message Format (IMF) packet encapsulated within the SMTP session.

## Q4 - DNS Packet Analysis

1. Flush the system DNS cache (`ipconfig/flushdns` on Windows or `systemd-resolve --flush-caches` on Linux).
2. Clear the web browser's cache.
3. Start a packet capture in Wireshark.
4. Visit the college website to trigger a DNS lookup.
5. Apply the `dns` filter in Wireshark.
6. Locate the first DNS query and its corresponding response; note their packet numbers and whether they used UDP or TCP.
7. Identify the source and destination ports and the destination IP address for the DNS query.
8. Compare the ID numbers of the query and response to verify they match.
9. Analyze the DNS flag field:
    - Determine its length.
    - Identify the bit that distinguishes a query from a response.
    - Identify bits used exclusively in response messages and their functions.
10. Count the number of question, answer, authority, and additional records in both the query and the response messages.

All experiments are single C files containing both the server and the
client. Run the file without arguments for the server and with the word
`client` for the client side (q10 is a standalone packet-capturing tool).

## Q5 - Matrix type detection (TCP)


1. The client asks the user for the order N, builds an N x N matrix with
   random integers in the range [1,50], prints it on screen, opens a TCP
   socket and connects to the server at port 8080.
2. The client sends N followed by all N*N matrix values over the socket.
3. The server accepts a connection, reads N and the matrix, then scans
   every element: it clears a flag `upper` if any element below the main
   diagonal is non-zero, and clears a flag `lower` if any element above
   the main diagonal is non-zero.
4. Based on the flags the server classifies the matrix as Diagonal, Upper
   Triangular, Lower Triangular, or Not triangular or diagonal.
5. The server sends this classification as a string back to the client,
   prints it in its own console, and closes the connection.
6. The client receives the string, prints the matrix type, and terminates.
7. The server continues listening and handles the next client.

## Q6 - Text translation to formal English (UDP)

1. The client reads a new-generation sentence (e.g. with `tbh`, `idk`,
   `asap`) from the user and sends it to the server at port 8001 over UDP.
2. The server, bound to port 8001, receives the sentence as one datagram.
3. It splits the sentence into words and, for each word, strips leading
   and trailing punctuation and converts it to lower case.
4. It looks the word up in a table of eleven abbreviations (tbh, ig, tbf,
   atm, irl, lol, asap, omg, ttyl, idk, nvm); if a match is found the word
   is replaced by its formal phrase, otherwise it is kept unchanged.
5. The translated words are joined back into a sentence, which is sent to
   the client's address as a single datagram.
6. The client receives the reply, prints it to the screen, and exits.

## Q7 - Multi-user chat server (TCP)

1. The server creates a TCP socket, binds it to port 8002, listens for
   connections, and sets up a shared client list guarded by a mutex.
2. For every accepted client the server stores its socket descriptor in
   the list (rejecting with a close if the list is full) and spawns a
   dedicated handler thread for it.
3. Each handler loops reading lines from its own client; every line is
   prefixed with the client id and broadcast to all other connected
   clients in the list.
4. When a read returns 0 the handler closes the socket, removes the id
   from the list, and the thread ends.
5. The client opens a TCP socket, connects to 127.0.0.1:8002, and creates
   a receiver thread that continuously prints messages arriving from the
   server.
6. Meanwhile the main client loop reads lines typed by the user and sends
   them to the server, so every message typed is seen by all other clients.
7. Pressing Ctrl+D closes the client; the server keeps running and accepts
   the next client indefinitely.

## Q8 - Concurrent time server (UDP)

1. The server creates a UDP socket, binds it to port 8003, and loops
   waiting for time requests from any client.
2. On each received request the server forks a child process, so every
   request is handled concurrently while the parent keeps listening.
3. The child formats the current system time using the `time()` and
   `ctime()` calls, sends it back to the requesting client's address, and
   exits.
4. The client creates a UDP socket, sends a short "TIME" request datagram
   to the server address, and waits for the reply.
5. The client prints the received time string on screen and exits.

## Q9 - Concurrent file server (TCP)

1. The server creates a TCP socket, binds it to port 8004, and listens for
   connections; for each accepted client it forks a child process, giving
   concurrency.
2. The child reads the requested filename, sends a header line containing
   its own PID, and tries to open the named file from its working
   directory.
3. If the file exists the child sends the line "FOUND" followed by the
   file contents line by line; otherwise it sends "ERROR: file not found".
4. The child then closes the connection and exits, while the parent
   continues accepting new clients.
5. The client connects to the server, asks the user for a filename, and
   sends it over the socket.
6. The client reads and prints the "PID: <pid>" line, then the status
   line; if the status is "FOUND" it prints the streamed file contents
   verbatim, otherwise it prints the error message, and exits.

## Q10 - Packet capturing using raw sockets

1. The program opens a raw socket of type AF_PACKET / SOCK_RAW with
   protocol ETH_P_ALL, which requires root privileges (CAP_NET_RAW).
2. It enters an infinite loop and receives one network frame at a time
   into a large buffer.
3. It interprets the first 14 bytes as the Ethernet header and prints the
   source and destination MAC addresses and the EtherType.
4. If the EtherType is IPv4 it parses the IP header and prints the source
   and destination IP addresses and the protocol number.
5. If the IP protocol is TCP or UDP it reads the corresponding transport
   header and prints the source and destination port numbers.
6. Each captured frame is printed with a packet counter and its length;
   the program keeps capturing until stopped with Ctrl+C.

## Q11 - Familiarizing router commands

1. Use Cisco Packet Tracer to set up a basic router environment.
2. Execute commands to switch between user mode and privileged EXEC mode.
3. Enter global configuration mode to modify system settings.
4. Use `show` commands to inspect router hardware, OS version, memory, and interface status.
5. Examine the routing table and check configured routing protocols.
6. Save the current running configuration to NVRAM.
7. Review command history, the system clock, and the host list.
8. Inspect interface statistics and determine if the controller is DTE or DCE.
9. Configure serial and ethernet interfaces by assigning IP addresses, masks, and clock rates.

## Q12 - Static routing configuration

1. Construct the network topology consisting of three routers (2621, 2501A, 2501B) and connected networks.
2. Manually define static routes on each router to ensure every network is reachable.
3. Verify the entries in the routing table using `show ip route`.
4. Test connectivity between remote hosts using `ping`.

## Q13 - RIPv2 routing implementation

1. Construct the network topology consisting of three routers (2621, 2501A, 2501B) and connected networks.
2. Enable RIP version 2 on all routers and specify the networks to be advertised.
3. Allow the routers to exchange updates and populate their routing tables dynamically.
4. Verify the RIPv2 routes in the routing table and test connectivity with `ping`.

## Q14 - OSPF routing implementation

1. Construct the network topology consisting of three routers (2621, 2501A, 2501B) and connected networks.
2. Enable OSPF on all routers, defining the process ID and network areas.
3. Verify the formation of OSPF adjacencies and the population of the routing table.
4. Test end-to-end connectivity between hosts using `ping`.

## Q15 - Access Control Lists for Host Isolation

1. Set up a campus network topology with multiple switches and hosts.
2. Create a standard or extended ACL to permit traffic from Host_B to the 172.16.10.0 network.
3. Deny all other traffic from different hosts (Lab_B, Lab_C) to the same network.
4. Apply the ACL to the appropriate router interface.
5. Verify the restriction by attempting to ping Host_A from Host_B (success) and from Lab_B/C (failure).

## Q16 - Selective Traffic Blocking (Web Services)

1. Design a network with 20 subnets based on the 140.80.0.0 address.
2. Identify the 4th subnet (CCF) and the specific host IP in the 16th subnet (hackathon server).
3. Configure an extended ACL to block TCP traffic on port 80 (HTTP) and 443 (HTTPS) from the CCF subnet to the server IP.
4. Permit all other traffic to ensure other server services remain accessible.
5. Apply the ACL to the network gateway.

## Q17 - IPv6 Interconnection using RIPng

1. Set up an IPv6 network with three routers (R1, R2, R3) and associated subnets.
2. Assign global unicast IPv6 addresses to all router interfaces.
3. Enable IPv6 routing and configure RIPng on all routers.
4. Verify the IPv6 routing table to ensure all subnets are reachable.
5. Use `ping6` to verify connectivity between hosts across the IPv6 network.
