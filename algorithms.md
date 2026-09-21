# Algorithms - Socket Programming Experiments (q5 - q10)

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