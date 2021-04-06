#include "packet_in.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



void extract_eth(unsigned char* eth_frame,eth &eth_pack){
    
    memcpy(&eth_pack,eth_frame,ETHHEADLEN);

    eth_pack.eth_type_len = ntohs(eth_pack.eth_type_len);//转换字节序



}


void extract_packet_in(unsigned char* packet_in_frame,packet_in &packet_in_pack){
    memcpy(&packet_in_pack,packet_in_frame,PACKETINLEN);
    packet_in_pack.ingress_port = ntohs(packet_in_pack.ingress_port);//转换字节序
}


int hex2dec(unsigned char hex) {
    if (hex - '0' <= 9) {
        return  hex - '0';
    }
    else {
        if (hex - '0' > 48) {
            return hex - 'a' + 10;
        }
        else {
            return hex - 'A' + 10;
        }
    }
}


void mac_str2mac(unsigned char* mac_str, unsigned char* mac) {
    int i = 0, k = 0;
    while (i < 17) {
        mac[k] = 16 * hex2dec(mac_str[i]) + hex2dec(mac_str[i + 1]);

        k += 1;
        i += 3;

    }
}

int dec2hex(unsigned char hex) {
    if (hex - '0' <= 9) {
        return  hex - '0';
    }
    else {
        if (hex - '0' > 48) {
            return hex - 'a' + 10;
        }
        else {
            return hex - 'A' + 10;
        }
    }
}


char hexnum2char(unsigned char c){
    switch(c){
        case 0:
        return '0';
        break;
        case 1:
        return '1';
        break;
        case 2:
        return '2';
        break;        
        case 3:
        return '3';
        break;        
        case 4:
        return '4';
        break;        
        case 5:
        return '5';
        break;        
        case 6:
        return '6';
        break;        
        case 7:
        return '7';
        break;        
        case 8:
        return '8';
        break;        
        case 9:
        return '9';
        break;        
        case 10:
        return 'a';
        break;        
        case 11:
        return 'b';
        break;        
        case 12:
        return 'c';
        break;        
        case 13:
        return 'd';
        break;        
        case 14:
        return 'e';
        break;        
        case 15:
        return 'f';
        break;
    }

}

void mac2mac_str(unsigned char src_mac[6], char* mac_str) {
    for (int i=0;i<6;++i){
        unsigned char high4 = (src_mac[i] & 0xf0) >> 4;
        unsigned char low4 = src_mac[i] & 0x0f;
        
        mac_str[3*i] = hexnum2char(high4);
        mac_str[3*i+1] = hexnum2char(low4);
        mac_str[3*i+2] = ':';
    }
    mac_str[17] = '\0';
}

#define IP_SIZE     16
// 获取本机ip
int get_local_ip(const char *eth_inf, char *ip)
{
    int sd;
    struct sockaddr_in sin;
    struct ifreq ifr;
 
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    if (-1 == sd)
    {
        printf("socket error: %s\n", strerror(errno));
        return -1;
    }
 
    strncpy(ifr.ifr_name, eth_inf, IFNAMSIZ);
    ifr.ifr_name[IFNAMSIZ - 1] = 0;
 
    // if error: No such device
    if (ioctl(sd, SIOCGIFADDR, &ifr) < 0)
    {
        printf("ioctl error: %s\n", strerror(errno));
        close(sd);
        return -1;
    }
 
    memcpy(&sin, &ifr.ifr_addr, sizeof(sin));
    snprintf(ip, IP_SIZE, "%s", inet_ntoa(sin.sin_addr));
 
    close(sd);
    return 0;
}