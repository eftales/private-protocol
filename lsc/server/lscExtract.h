#ifndef __LSCEXTRACT__
#define __LSCEXTRACT__

#pragma pack(1)

#include "lsc.h"

// data process
void process_data(unsigned char* data,int len);


// udp
/// --func
void extract_udp(unsigned char* udp_frame);

// ip
/// --func
void extract_ip(unsigned char* ip_frame);

// lsc
/// --func
void extract_lsc(unsigned char* lsc_frame);


// eth
/// --func
void extract_eth(unsigned char* eth_frame);
#endif