#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>
#include <linux/if_ether.h>
#include <sys/socket.h>

#define BUFSZ 65536

int main(void) {
    int raw = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (raw < 0) {
        perror("socket(AF_PACKET)");
        printf("Run as root.\n");
        return 1;
    }

    printf("Sniffing... (Ctrl+C to stop)\n");

    unsigned char buf[BUFSZ];
    int count = 0;

    while (1) {
        ssize_t n = recvfrom(raw, buf, sizeof(buf), 0, NULL, NULL);
        if (n < 14) continue;

        struct ethhdr *eth = (struct ethhdr *)buf;
        unsigned short ethertype = ntohs(eth->h_proto);

        printf("Packet %d (len %zd):\n", ++count, n);
        printf("  MAC  src %02x:%02x:%02x:%02x:%02x:%02x  dst %02x:%02x:%02x:%02x:%02x:%02x\n",
               eth->h_source[0], eth->h_source[1], eth->h_source[2],
               eth->h_source[3], eth->h_source[4], eth->h_source[5],
               eth->h_dest[0], eth->h_dest[1], eth->h_dest[2],
               eth->h_dest[3], eth->h_dest[4], eth->h_dest[5]);

        if (ethertype == ETH_P_IP) {
            struct iphdr *ip = (struct iphdr *)(buf + 14);
            int iphlen = ip->ihl * 4;
            char s4[16], d4[16];
            inet_ntop(AF_INET, &ip->saddr, s4, sizeof(s4));
            inet_ntop(AF_INET, &ip->daddr, d4, sizeof(d4));
            printf("  IPv4 src %s  dst %s  proto %u\n", s4, d4, ip->protocol);

            if (ip->protocol == IPPROTO_TCP) {
                struct tcphdr *tcp = (struct tcphdr *)(buf + 14 + iphlen);
                printf("    TCP sport %u  dport %u\n", ntohs(tcp->source), ntohs(tcp->dest));
            } else if (ip->protocol == IPPROTO_UDP) {
                struct udphdr *udp = (struct udphdr *)(buf + 14 + iphlen);
                printf("    UDP sport %u  dport %u\n", ntohs(udp->source), ntohs(udp->dest));
            }
        } else {
            printf("  EtherType 0x%04x\n", ethertype);
        }
    }
}