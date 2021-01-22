#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppEncapsulate.h"

int main(int argc,char** argv) // 网卡名称 目的主机mac
{
    if (argc<2){
        printf("命令行参数过少");
        return -1;
    }
    unsigned char src_mac[6],dst_mac[6];
    char *interface=argv[1]; // nic name
    unsigned char* data = "12345678901234567890123456789012345678901234567890";


    interface2mac(interface,src_mac);
    for (int i=0;i<6;++i){
        printf("%02x:",src_mac[i]);
    }
    mac_str2mac(argv[2],dst_mac);


    udp udp_pack = {
        .src_port = htons(2333),
        .dst_port = htons(2333),
        .len = htons(UDPHEADLEN+50),
        .checksum = 0
    };

    char* udp_frame = encapsulate_udp(&udp_pack,data,50);

    ip ip_pack = {
        .hl = 4,
        .v = 4,
        .tos = 0,
        .len = htons(IPHEADLEN + UDPHEADLEN + 50),
        .id = 0,
        .off = 0,
        .flags = 0,
        .ttl = htons(255),
        .pro = 17

    };
    char* ip_frame = encapsulate_ip(&ip_pack,udp_frame,UDPHEADLEN + 50);
    free(udp_frame);

    pp pp_pack = {
        .lsc_dst = 1,
        .lsc_src = 0
    };
    char* pp_frame = encapsulate_pp(&pp_pack,ip_frame,IPHEADLEN+UDPHEADLEN + 50);
    free(ip_frame);

    eth eth_pack;
    memcpy(&eth_pack.dst_mac,dst_mac,6);
    memcpy(&eth_pack.src_mac,src_mac,6);
    eth_pack.eth_type_len = htons(ETHERTYPE);

    char* eth_frame = encapsulate_eth(&eth_pack,pp_frame,PPHEADLEN+IPHEADLEN+UDPHEADLEN + 50);
    free(pp_frame);

    send_frame(interface,eth_frame,ETHHEADLEN+PPHEADLEN+IPHEADLEN+UDPHEADLEN + 50);
    return 0;
}