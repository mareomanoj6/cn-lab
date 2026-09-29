# Experiment 17: IPv6 Routing with RIPng (Figure 3)

## Topology Setup
1. Build Figure 3 with Routers R1, R2, R3 and Hosts.
2. Connect interfaces as labeled (G0/0, S0/0/0, etc.).

## Configuration Steps
1. **Enable IPv6 Routing**:
   - On all routers: `ipv6 unicast-routing`
2. **Assign IPv6 Addresses**:
   - Configure interfaces with given prefixes (e.g., `ipv6 address 2001:DB8:1111:1::1/64`).
3. **Configure RIPng**:
   - On all routers:
     ```text
     ipv6 router ripng
     ```
   - Enable RIPng on every participating interface:
     ```text
     interface [interface_id]
     ipv6 ripng enable
     ```

## Verification
- Check IPv6 routing table: `show ipv6 route`
- Verify connectivity: `ping ipv6 [destination_ipv6_address]`
