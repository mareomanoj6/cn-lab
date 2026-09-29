# Experiment 11: Familiarizing Router Commands

## Basic Mode Switching
- **User Mode to Privileged Mode**: `enable`
- **Privileged Mode to Configuration Mode**: `configure terminal`
- **Return to Privileged Mode**: `exit` or `end`

## Information Gathering
- **System Information**: `show version` (OS, memory, hardware)
- **Interface Status**: `show ip interface brief` (Summary of IPs and status)
- **Detailed Interface Stats**: `show interfaces`
- **Routing Table**: `show ip route`
- **Routing Protocol Status**: `show ip protocols`
- **Controller Type**: `show controllers [interface]` (Check if DTE/DCE)
- **System Clock**: `show clock`
- **Command History**: `show history`

## Configuration & Management
- **Interface Setup**: 
  ```text
  interface [interface_id]
  ip address [ip_address] [subnet_mask]
  no shutdown
  ```
- **Saving Configuration**: `write memory` or `copy running-config startup-config`
