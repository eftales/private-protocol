整个协议栈结构：

eth<-pp(type=0x0808)<-ip<-udp

# 字节序
两个字节的以上的整数才需要转换字节序！
1. 两个字节以上
2. char 和 char* 都不用转换
 
# 运行
```
make 
sudo ./ppServer "网卡mac"
sudo ./ppClient "网卡mac" "服务器的MAC" 
```