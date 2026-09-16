# PCCSL507 NETWORKS LAB (Common to CS/CD/CM/CB/CU/CI)
**SEMESTER S5**

| | | | |
|---|---|---|---|
| **Course Code** | PCCSL507 | **CIE Marks** | 50 |
| **Teaching Hours/Week (L:T:P:R)** | 0:0:3:0 | **ESE Marks** | 50 |
| **Credits** | 2 | **Exam Hours** | 2 Hrs. 30 Min. |
| **Prerequisites (if any)** | None | **Course Type** | Lab |

## Course Objectives:
1. To provide hands-on experience in network programming using Linux System calls and network monitoring tools.
2. To comprehend the implementation of network protocols and algorithms, and configuration of network layer services using network simulators.

---

## Experiments

### Warm up
**1. Familiarize Linux networking commands**
ifconfig, ifplugstatus, iftop, ping, ip, traceroute, mtr, netstat, whois, nmap, nmcli, speedtest-cli, bmon, nslookup, tcpdump

### Wireshark based
**2. HTTP Packet Analysis**
Start your web browser and clear the browser's cache memory. Open Wireshark and start capturing. Then visit any webpage of your choice. Type `http` in the filter field of the Wireshark and click Apply so that only HTTP messages are displayed. After enough packets have been captured, select the Capture from the pull-down menu and select Stop to stop capturing.
Using the captured information, determine the following:
* (a) the source IP address and destination IP address of the first GET message
* (b) the medium format, the language, the encoding, and the character set that the client can accept. (Use the first GET message)
* (c) the URL of the website and the user agent (Use the first GET message)
* (d) the source IP address and destination IP address of the first response message
* (e) the status codes for the first response message.
* (f) when the HTML file that you are retrieving was last modified at the server
* (g) value of the content-length field of the first response message
* (h) how long it took from the time the GET message was sent until the response message was received. (Use the timestamps of a GET message and that of the corresponding response message. By default, the time column's value is the amount of time in seconds since Wireshark tracing began.)
* (i) the HTTP version of your browser.

**3. SMTP Packet Analysis**
Compose an e-mail and address it to yourself, but do not send it yet. Open Wireshark and start capturing. Go to your e-mail user agent and send the e-mail. In the Wireshark window, type `smtp` in the filter field and click Apply. Stop capturing and save the captured file.
Using the captured information, answer the following:
* (a) All SMTP packets have the same two IP addresses. Which one is the IP address of your computer? Which host does the other IP address represent?
* (b) All SMTP packets have the same two port numbers. Which one is the port number of the SMTP client process? In which range is the client port number?
* (c) What is the port number of the SMTP server process?
* (d) Examine the SMTP commands or SMTP response codes in each SMTP packet and write down their meanings.
* (e) There is an IMF packet that is encapsulated inside an SMTP packet. What is the content of this packet?

**4. DNS Packet Analysis**
First, clear the DNS record from the cache memory of your computer. For this, use `ipconfig/flushdns` on Windows or `systemd-resolve --flush-caches` on Linux. Next, clear your browser's cache memory. Open Wireshark and start capturing. In your browser visit your college website. Wireshark starts to capture packets. Type `dns` in the filter field and press Apply so that only DNS messages are displayed. Stop capturing and save the captured file.
Using the captured information, answer the following questions:
* (a) Locate the first DNS query message resolving your college website. What is the packet number in the trace for the DNS query message?
* (b) Is this query message sent over UDP or TCP?
* (c) Now locate the corresponding DNS response to the initial DNS query. What is the packet number in the trace for the DNS response message? Is this response message received via UDP or TCP?
* (d) What are the source and destination port numbers for the DNS query message?
* (e) What are the source and destination port numbers for the DNS response message?
* (f) To what IP address is the DNS query message sent?
* (g) What is the query message ID number? What is the response message ID number? What is the purpose of this field?
* (h) What is the length of the flag field in a DNS message?
* (i) Which bit in the flag field determines whether the message is a query or a response?
* (j) Which bits are used only in the response message? What is the function of these bits in the response message?
* (k) How many question records, answer records, authority records, and additional records are present in the query message?
* (l) How many question records, answer records, authority records, and additional records are present in the response message?

### Socket programming based
**5. Client-Server communication using TCP:** 
The client inputs an integer N and creates a square matrix of order N by populating the matrix with random numbers in the range [1,50]. It then sends the matrix to the server which identifies the matrix type (upper triangular, lower triangular, diagonal). The server then informs the type (as a string) to the client which it prints.

**6. Client-Server communication using UDP:** 
Design a client-server application as follows: The client inputs a new-generation English sentence from the user and sends it to the server. The server then translates the received sentence to formal English and sends the translated sentence back to the client which it prints. You may consider only the following abbreviations: tbh, ig, tbf, atm, irl, lol, asap, omg, ttyl, idk, nvm.

**7.** Implement a multi-user chat server using TCP as the transport layer protocol.

**8.** Implement a concurrent Time Server application using UDP to execute the program at a remote server. The client sends a time request to the server which sends its system time back. The client then displays the received time value.

**9.** Develop a concurrent file server that will provide the file requested by the client if it exists. If not, the server sends an appropriate message to the client. The server should also send its process ID (PID) to clients for displaying along with the file contents or with the message.

**10.** Develop a packet-capturing application using raw sockets.

### Cisco's Packet tracer based
**11. Familiarizing router commands**
* (a) Knowing the current mode (user or privileged), switching to privileged mode
* (b) Switching to configuration mode
* (c) Obtaining router information such as type, OS, memory stats, interface details etc.
* (d) Viewing the status of any routing protocols currently configured
* (e) Showing the routing table
* (f) Saving the running configuration
* (g) Viewing the command history
* (h) Viewing the router clock
* (i) Viewing the list of hosts
* (j) Displaying the statistics for all the interfaces (Both detailed and brief views)
* (k) Knowing the controller type (DTE or DCE)
* (l) Configuring serial and ethernet interfaces enabling the interface, setting IP address, mask, and clock rate

```text
      Figure 1: A sample network
      (Reconstructed based on available text labels)
      
             F0/0         E0           S0           S0           E0/S1
      [Router 2621] ---- [Router 2501A] ----------- [Router 2501B] ---- (172.16.30.0/24)
```

**12.** Set up static routing for the network shown in Figure 1. Once the routes are set up, display the routing table and verify the connectivity using `ping`.

**13.** Implement RIPv2 routing for the network shown in Figure 1. Once the routes are set up, display the routing table and verify the connectivity using `ping`.

**14.** Implement OSPF routing for the network shown in Figure 1. Once the routes are set up, display the routing table and verify the connectivity using `ping`.

```text
      Figure 2: A portion of your college campus network
      
            Host_A                  Host_B                 Host_C
              |                       |                      |
              | F0/27                 | F0/2                 | F0/2
        +-------------+         +-------------+        +-------------+
        | Switch 1900 |         | Switch 2950 |==F0/4==| Switch 29.. |
        +-------------+         +-------------+==F0/5==+-------------+
              | F0/26                 | F0/1                 |
        172.16.10.0/24          172.16.30.0/24            ...
```

**15.** You are the network administrator of your college. A small portion of your campus network is shown in Figure 2. You want to allow only Host_B to communicate with the network 172.16.10.0. Verify your settings by the following checks:
* (a) Pinging Host_A from Host_B
* (b) Pinging Host_A from Lab_B and Lab_C

**16.** You are the network administrator of your college. The college is assigned a network address 140.80.0.0. There are 20 subnets in your college network. The Central Computing Facility (CCF) resides in the 4th subnet. The department of CSE is organizing an inter-department hackathon for which the registration closed yesterday. The registration was through the hackathon website hosted on a server which is assigned the 7th address in the 16th subnet. As the network administrator, your job now is to block students from accessing the hackathon website from CCF. [The server provides other services than the website hosting as well. Make sure you block only the website access. Other services should not be denied.]

```text
      Figure 3: An IPv6 network
      
      Subnet 1: 2001:DB8:1111:1::/64
         [Host A] (::11)
            |
            | G0/0 (::1)
          +----+ S0/0/0(::1)                      S0/0/1(::2) +----+ G0/0(::2)  Subnet (2001:D..)
          | R1 |----------------------------------------------| R2 |----------
          +----+              Subnet 4                        +----+
            | G0/1/0    (2001:DB8:1111:4::/64)
            |
         (Network Cloud)
            | G0/0/0 (::3)
          +----+
          | R3 |--- G0/0 (::3)
          +----+
```

**17.** Figure 3 shows an IPv6-based network. Interconnect the different subnets using RIPng.
