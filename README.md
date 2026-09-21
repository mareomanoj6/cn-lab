# Networks Lab - Socket Programs (PCCSL507, Experiments 5-10)

Plain C files, no build system needed. Each source file contains both the
server and the client; run with no argument for the server and `client` for
the client (q10 is a single program).

## Compile & run

```sh
gcc q5.c -o q5            gcc q5.c -o q5 && ./q5
gcc q6.c -o q6
gcc q7.c -o q7 -pthread
gcc q8.c -o q8
gcc q9.c -o q9
gcc q10.c -o q10
```

Then, in two terminals:

```sh
./q5            # terminal 1 (server)
./q5 client     # terminal 2 (client)
```

## Programs

| File       | Experiment                                                                              | Transport | Port |
|------------|-----------------------------------------------------------------------------------------|-----------|------|
| `q5.c`     | Matrix type: client sends an N x N matrix (random in [1,50]); server says if it is upper/lower triangular or diagonal | TCP | 8080 |
| `q6.c`     | Translation: client sends a sentence with chat abbreviations; server rewrites it in formal English (tbh, ig, tbf, atm, irl, lol, asap, omg, ttyl, idk, nvm) | UDP | 8001 |
| `q7.c`     | Multi-user chat server (thread per client, messages broadcast to all)                  | TCP | 8002 |
| `q8.c`     | Concurrent time server: client requests the time; server replies (fork per request)     | UDP | 8003 |
| `q9.c`     | Concurrent file server: client requests a file; server sends its PID + contents, or an error | TCP | 8004 |
| `q10.c`    | Packet-capturing (raw sockets): prints Ethernet, IPv4 and TCP/UDP info                 | Raw  | -    |

## Notes

- All programs talk to `127.0.0.1`. Each pair has its own port so every
  experiment can run at the same time.
- q5: values are random in [1,50] (never zero), so the usual answer is
  "Not triangular or diagonal". Set a few entries to 0 to see the other cases.
- q6: example -
  `tbh, idk the answer irl asap` -> `to be honest I don't know the answer in real life as soon as possible`
- q9: the server serves files from its current directory; e.g. request
  `cnlabcycle.md`, or a non-existent name to see the error message.
- q10: must be run as root (`sudo ./q10`) because it opens an `AF_PACKET`
  raw socket (Linux only).