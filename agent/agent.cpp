#include <stdio.h>
#include <stdlib.h>
#include "packet_in.h"

const char flowCMD_mac_forward[] = "echo \"table_add dmac mac_forward %s => %d\" | simple_switch_CLI";
const char flowCMD_smac[] = "echo \"table_add smac NoAction %s => \" | simple_switch_CLI";


int main(int argc,char** argv) 
{ 
	int n_read;
	unsigned char buffer[MAXETHLEN];
	unsigned char* eth_frame;
	int sock_fd;
	eth_frame = buffer;
    eth eth_pack;
    packet_in packet_in_pack;

    char cmd[300];
    char srcMAC[20];


    if((sock_fd = socket(PF_PACKET,SOCK_RAW,htons(ETH_P_ALL))) < 0)
    {
        printf("error while creating raw socket :%d\n",sock_fd);
        return -1;
    }
    while(1)
    {
        n_read = recvfrom(sock_fd, buffer, MAXETHLEN, 0, NULL, NULL);
        n_read = 80; //  目前 packet_in 的长度小于46字节
        if(n_read < 46)
        {
            printf("Eth frame len < 46");
        }
        else{
            extract_eth(eth_frame,eth_pack);

            switch(eth_pack.eth_type_len){
                case ETHTYPE_PACKET_IN:
                    printf("-------Eth-------\n");
                    printf("Destination: %02x:%02x:%02x:%02x:%02x:%02x\n",eth_pack.dst_mac[0], eth_pack.dst_mac[1], eth_pack.dst_mac[2], eth_pack.dst_mac[3], eth_pack.dst_mac[4], eth_pack.dst_mac[5]);
                    printf("Source: %02x:%02x:%02x:%02x:%02x:%02x\n",eth_pack.src_mac[0], eth_pack.src_mac[1], eth_pack.src_mac[2], eth_pack.src_mac[3], eth_pack.src_mac[4], eth_pack.src_mac[5]);
                    printf("type: %u\n",eth_pack.eth_type_len);
                    extract_packet_in(eth_frame+ETHHEADLEN,packet_in_pack);
                    printf("ingress_port:%d \n",packet_in_pack.ingress_port);
                    mac2mac_str(eth_pack.src_mac,srcMAC);
                    snprintf(cmd,300,flowCMD_mac_forward,srcMAC,packet_in_pack.ingress_port);
                    // printf("%s\n",cmd);
                    system(cmd);

                    snprintf(cmd,300,flowCMD_smac,srcMAC);
                    system(cmd);
                    
                    break;
                default:
                    break;
            }

        }
        
    }
	
}
