#include <stdio.h>
#include <stdlib.h>
#include "packet_in.h"


int main(int argc,char** argv) 
{ 
	int n_read;
	unsigned char buffer[MAXETHLEN];
	unsigned char* eth_frame;
	int sock_fd;
	eth_frame = buffer;
    eth eth_pack;
    packet_in packet_in_pack;

    char ip[16];
    get_local_ip("p4lo",ip);
    printf("listening at %s\n",ip);



    if((sock_fd = socket(PF_PACKET,SOCK_RAW,inet_addr(ip))) < 0)
    {
        printf("error while creating raw socket :%d\n",sock_fd);
        return -1;
    }
    while(1)
    {
        n_read = recvfrom(sock_fd, buffer, MAXETHLEN, 0, NULL, NULL);
        if(n_read < 46)
        {
            printf("Eth frame len < 46");
        }
        else{
            extract_eth(eth_frame,eth_pack);
            extract_packet_in(eth_frame+ETHHEADLEN,packet_in_pack);
            printf("ingress_port:%d \n",packet_in_pack.ingress_port);
        }
        
    }
	
}
