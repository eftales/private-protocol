#ifndef __LSCEXTRACT__
#define __LSCEXTRACT__

#pragma pack(1)


// socket head files
#include <netdb.h>            // struct addrinfo
#include <sys/types.h>        // needed for socket(), uint8_t, uint16_t, uint32_t
#include <sys/socket.h>       // needed for socket()
#include <netinet/in.h>       // IPPROTO_ICMP, INET_ADDRSTRLEN
#include <netinet/ip.h>       // struct ip and IP_MAXPACKET (which is 65535)
#include <arpa/inet.h>        // inet_pton() and inet_ntop()
#include <sys/ioctl.h>        // macro ioctl is defined
#include <bits/ioctls.h>      // defines values for argument "request" of ioctl.
#include <net/if.h>           // struct ifreq
#include <linux/if_ether.h>   // ETH_P_IP = 0x0800, ETH_P_IPV6 = 0x86DD
#include <linux/if_packet.h>  // struct sockaddr_ll (see man 7 packet)
#include <net/ethernet.h>

// linux head files
#include <unistd.h>
#include <errno.h>            // errno, perror()

// const
#define MAXETHLEN 1600
#define ETHER_LSC 0x09ab
#define ETHTYPE_PACKET_IN 0x09ad

#define ETHHEADLEN 14
#define PACKETINLEN 2

// packet_in 
/// --struct
typedef struct
{
    unsigned short ingress_port;
}packet_in;

// eth
/// --struct
typedef struct
{
    unsigned char dst_mac[6];
	unsigned char src_mac[6];
    unsigned short eth_type_len;
}eth;

// tools

/// mac字符串转换为mac地址
void mac_str2mac(unsigned char* mac_str, unsigned char* mac);

/// 
int get_local_ip(const char *eth_inf, char *ip);


///
int hex2dec(unsigned char hex);

/// 
void mac2mac_str(unsigned char src_mac[6], char* mac_str);


// packet_in
/// --func
void extract_packet_in(unsigned char* packet_in_frame,packet_in &packet_in_pack);


// eth
/// --func
void extract_eth(unsigned char* eth_frame,eth &eth_pack);
#endif