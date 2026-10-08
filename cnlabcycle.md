## List of Experiments

### Warm up
*   **Expt 1:** Familiarize Linux networking commands: ifconfig, ifplugstatus, iftop, whois, nmap, nmcli, ping, ip, traceroute, mtr, netstat, speedtest-cli, bmon, nslookup, tcpdump.

### Wireshark Based
*   **Expt 2:** Use Wireshark to capture HTTP packets by clearing the browser cache, visiting a webpage, and applying the `http` filter. Extract information such as IP addresses, status codes, content-length, URL, HTTP version, and time taken from the first GET and response messages.
*   **Expt 3:** Compose and send an email to yourself while capturing packets with Wireshark using the `smtp` filter. Analyze IP addresses, port numbers, SMTP commands, and IMF packet contents.
*   **Expt 4:** Clear DNS cache (using `ipconfig/flushdns` on Windows or `systemd-resolve --flush-caches` on Linux) and browser cache. Capture packets while visiting the college website, filter for `dns`, and analyze DNS queries and responses over UDP/TCP, packet numbers, port numbers, flag fields, and record counts.

### Socket Programming Based
*   **Expt 5 (TCP Client-Server):** The client sends a randomly populated N x N matrix (values [1,50]) to the server. The server identifies if it is upper triangular, lower triangular, or diagonal, and returns the type as a string.
*   **Expt 6 (UDP Client-Server):** A client sends a sentence with "new generation" abbreviations (tbh, ig, tbf, atm, irl, lol, asap, omg, ttyl, idk, nvm) to a server. The server translates it to formal English and sends it back.
*   **Expt 7:** Implement a multi-user chat server using TCP.
*   **Expt 8:** Implement a concurrent Time Server application using UDP.
*   **Expt 9:** Develop a concurrent file server that provides a requested file or an appropriate message if missing, along with the server's process ID (PID).
*   **Expt 10:** Develop a packet-capturing application using raw sockets.

### Cisco Packet Tracer Based
*   **Expt 11:** Familiarize with router commands including switching modes, obtaining router info, viewing routing protocols and tables, saving configurations, viewing history and clock, displaying host lists and interface statistics, and configuring serial and ethernet interfaces.
*   **Expt 12:** Set up static routing for the network in Figure 1, display the routing table, and verify connectivity using `ping`.
*   **Expt 13:** Implement RIPv2 routing for the network in Figure 1 and verify connectivity using `ping`.
*   **Expt 14:** Implement OSPF routing for the network in Figure 1 and verify connectivity using `ping`.
*   **Expt 15:** Configure access so only `Host_B` can communicate with network `172.16.10.0` in Figure 2. Verify by pinging `Host_A` from `Host_B`, and `Host_A` from `Lab_B` and `Lab_C`.
*   **Expt 16:** Block students from accessing a hackathon website (assigned the 7th address in the 16th subnet) from the Central Computing Facility (4th subnet) within the college network `140.80.0.0` (20 subnets total) without denying other services.
*   **Expt 17:** Interconnect different subnets using RIPng for the IPv6-based network in Figure 3.

---

## Network Diagrams & Tables (ASCII Converted)

**Figure 1 Table: Router Interfaces**
| router | Interface | IP address |
| :--- | :--- | :--- |
| 2621 | F0/0 | 172.16.10.1 |
| 2501A | E0 | 172.16.10.2 |
| 2501A | S0 | 172.16.20.1 |
| 2501B | E0 | 172.16.30.1 |
| 2501B | S0 | 172.16.20.2 |
| 2501B | S1 | 172.16.40.1 |
| 2501C | S0 | 172.16.40.2 |
| 2501C | E0 | 172.16.50.1 |

**Figure 2: Portion of college campus network**
      Host_A                  Host_B                  Host_C
        |                       | |                     | |
     [F0/27]                [F0/2][F0/3]            [F0/2][F0/3]
    +-------+               +----------+            +----------+
    | 1900  |               |   2950   |--[F0/4]----|   2950   |
    +-------+               +----------+--[F0/5]----+----------+
     [F0/26]                   [F0/1]                  [F0/1]
 172.16.10.0/24            172.16.30.0/24          172.16.50.0/24
        |                       |                       |
      [F0/0]                  [F0/0]                  [F0/0]
   +---------+             +---------+             +---------+
   |  Lab A  |             |  Lab B  |             |  Lab C  |
   +---------+             +---------+             +---------+
      [S0/0]                  [S0/0]                  [S0/0]
         | 172.16.20.0/24        |                       |
         +-----------------------+(DCE)                  |
                               [S0/1]                    |
                                 |    172.16.40.0/24     |
                                 +-----------------------+(DCE)

**Figure 3: An IPv6 network**
       [Subnet 1: 2001:DB8:1111:1::/64]
                   |
Host A [::11] --- G0/0 [::1] 
                   |
                +----+
                | R1 |
                +----+
          S0/0/0/    \ G0/1/0
       [::1]   /      \  [::1]
              /        \
             /          \
[Subnet 4]  /            \ [Subnet 5]
           /              \
          / [::2]          \ [::3]
    S0/0/1                  G0/0/0
    +----+                  +----+
    | R2 |                  | R3 |
    +----+                  +----+
      | G0/0 [::2]            | G0/0 [::3]
      |                       |
Host B [::22]           Host C [::33]
[Subnet 2]              [Subnet 3]

---

