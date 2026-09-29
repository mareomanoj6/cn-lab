# Experiment 16: Specific Service Blocking

## Problem Analysis
- **Network**: 140.80.0.0/8
- **Subnets**: 20 subnets $\rightarrow$ Mask /13 (255.248.0.0)
- **Subnet 4 (CCF)**: 140.24.0.0/13
- **Subnet 16 (Target)**: 140.120.0.0/13
- **Target Server**: 7th address in subnet 16 $\rightarrow$ 140.120.0.7
- **Goal**: Block HTTP (Port 80) and HTTPS (Port 443) from CCF to Server.

## Configuration Steps
1. **Create Extended ACL**:
   - On the router controlling CCF traffic:
     ```text
     access-list 102 deny tcp 140.24.0.0 0.7.255.255 host 140.120.0.7 eq 80
     access-list 102 deny tcp 140.24.0.0 0.7.255.255 host 140.120.0.7 eq 443
     access-list 102 permit ip any any
     ```
2. **Apply ACL**:
   - Apply to the interface facing the CCF network:
     ```text
     interface [CCF_Interface]
     ip access-group 102 in
     ```

## Verification
- Try to access the website (HTTP/HTTPS) from CCF $\rightarrow$ Should fail.
- Try to ping the server or use other services (e.g., SSH) $\rightarrow$ Should succeed.
