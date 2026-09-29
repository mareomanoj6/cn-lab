# Experiment 12: Static Routing (Figure 1)

## Topology Setup
1. Place three routers (e.g., 2621, 2501A, 2501B) and a PC.
2. Connect them as per Figure 1: `R1 <-> R2 <-> R3 <-> PC (172.16.30.0/24)`.

## IP Addressing Scheme (Example)
- **R1-R2 Link**: 10.0.0.0/30 (R1: .1, R2: .2)
- **R2-R3 Link**: 10.0.0.4/30 (R2: .5, R3: .6)
- **R3-LAN**: 172.16.30.0/24 (R3: .1, PC: .10)

## Configuration Steps
1. **Assign IPs**: Configure all interfaces and use `no shutdown`.
2. **Static Routes**:
   - **R1**: `ip route 172.16.30.0 255.255.255.0 [R2_IP]`
   - **R2**: `ip route 172.16.30.0 255.255.255.0 [R3_IP]`
   - **R3**: (Directly connected to LAN, no route needed for 172.16.30.0).
   - **Return Routes**: Add routes back to R1's network on R2 and R3 to ensure two-way communication.

## Verification
- Use `show ip route` to verify the static routes (`S` entries).
- `ping 172.16.30.10` from R1.
