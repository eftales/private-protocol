#ifndef __PPENCAPSULATE__
#define __PPENCAPSULATE__

#pragma pack(1)

#include "pp.h"

void interface2mac(char* interface,char* src_mac);

// udp
/// --func
char* encapsulate_udp(udp *udp_pack,unsigned char* data,int len);

// ip
/// --func
char* encapsulate_ip(ip *ip_pack,unsigned char* udp,int len);

// pp
/// --func
char* encapsulate_pp(pp* pp_pack,unsigned char* ip,int len);


// eth
/// --func
char* encapsulate_eth(eth* eth_pack,unsigned char* pp,int len);

void send_frame(char* interface,char* frame,int len);
#endif