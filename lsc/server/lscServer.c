#include <stdio.h>
#include <stdlib.h>
#include "lscExtract.h"


int main(int argc,char** argv) // 网卡名称
{ 


    int protocol;
	int n_read;
	unsigned char buffer[MAXETHLEN];
	unsigned char* eth_frame;
	int sock_fd;
	eth_frame = buffer;

    unsigned char src_mac[6];
    if (argc<=1){
        char *interface="h1-eth0"; // nic name 
        interface2mac(interface,src_mac);

    }else{
        char *interface=argv[1]; // nic name
        interface2mac(interface,src_mac);
    }
    FILE *f = fopen("serverMAC", "w");

    char fCache[4];
    for (int i=0;i<5;++i){
        printf("%02x:",src_mac[i]);
        sprintf(fCache,"%02x:",src_mac[i]);
        fputs(fCache,f);
    }
    printf("%02x",src_mac[5]);
    sprintf(fCache,"%02x",src_mac[5]);
    fputs(fCache,f);
    fclose(f);
    fflush(stdout); // 不加这个 printf 会在 recvfrom 之后执行，表现为有数据到达之后，才打印


    if((sock_fd = socket(PF_PACKET,SOCK_RAW,htons(ETH_P_ALL))) < 0)
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
            extract_eth(eth_frame);
        }
        
    }
	
}
