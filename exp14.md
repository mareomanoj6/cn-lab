# Experiment 14: OSPF Routing (Figure 1)

## Topology Setup
1. Use the same topology and IP addressing as Experiment 12.

## Configuration Steps
1. **Enable OSPF**:
   - On all routers:
     ```text
     router ospf 1
     network [network_address] [wildcard_mask] area 0
     ```
2. **Define Networks**:
   - **R1**: `network 10.0.0.0 0.0.0.3 area 0`
   - **R2**: `network 10.0.0.0 0.0.0.3 area 0`, `network 10.0.0.4 0.0.0.3 area 0`
   - **R3**: `network 10.0.0.4 0.0.0.3 area 0`, `network 172.16.30.0 0.0.0.255 area 0`

## Verification
- Use `show ip ospf neighbor` to check adjacencies.
- Use `show ip route` to verify OSPF routes (`O` entries).
- `ping 172.16.30.10` from R1.
