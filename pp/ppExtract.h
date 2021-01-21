#ifndef __PPEXTRACT__
#define __PPEXTRACT__

#pragma pack(1)

#include "pp.h"

// data process
void process_data(unsigned char* data,int len);


// udp
/// --func
void extract_udp(unsigned char* udp_frame);

// ip
/// --func
void extract_ip(unsigned char* ip_frame);

// pp
/// --func
void extract_pp(unsigned char* pp_frame);


// eth
/// --func
void extract_eth(unsigned char* eth_frame);
#endif