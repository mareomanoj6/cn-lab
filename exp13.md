# Experiment 13: RIPv2 Routing (Figure 1)

## Topology Setup
1. Use the same topology and IP addressing as Experiment 12.

## Configuration Steps
1. **Enable RIPv2**:
   - On all routers:
     ```text
     router rip
     version 2
     no auto-summary
     network [directly_connected_network_address]
     ```
2. **Define Networks**:
   - **R1**: `network 10.0.0.0`
   - **R2**: `network 10.0.0.0`, `network 10.0.0.4` (or appropriate range)
   - **R3**: `network 10.0.0.4`, `network 172.16.30.0`

## Verification
- Use `show ip route` to verify routes learned via RIP (`R` entries).
- `ping 172.16.30.10` from R1.
