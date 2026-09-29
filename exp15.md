# Experiment 15: Network Access Control (Figure 2)

## Topology Setup
1. Build Figure 2: `Host_A (172.16.10.0/24) <-> Switch 1900 <-> Router <-> Switch 2950 <-> Host_B (172.16.30.0/24)`.
2. Configure Host IPs and Default Gateways.

## Configuration Steps
1. **Define Requirement**: Allow only Host_B to access 172.16.10.0/24.
2. **Create Extended ACL**:
   - Assume Host_B IP: `172.16.30.10`
   - On the router:
     ```text
     access-list 101 permit ip host 172.16.30.10 172.16.10.0 0.0.0.255
     access-list 101 deny ip any 172.16.10.0 0.0.0.255
     access-list 101 permit ip any any
     ```
3. **Apply ACL**:
   - Apply to the interface closest to the source or destination:
     ```text
     interface [interface_to_Host_A]
     ip access-group 101 out
     ```

## Verification
- **Check (a)**: Ping Host_A from Host_B $\rightarrow$ Should succeed.
- **Check (b)**: Ping Host_A from Lab_B/C $\rightarrow$ Should fail.
