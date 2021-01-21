# private-protocol
用SOCK_RAW实现自定义协议栈

Implement private-protocol stack by using sock_ Raw

## 注意
1. 只适用于Linux系统

2. 用管理员权限执行

## 如何使用代码
- 对于没有socket编程经验的好兄弟

    建议先看一下 standardUDP/ 文件夹下如何用UDP协议实现客户端和服务端之间的通信，熟悉 socket 函数的基本用法

- 对于网络编程上手

    直接看 pp/ 文件夹下的代码

子文件夹下由更详细的说明

## 参考

1. https://blog.csdn.net/dean_gdp/article/details/34088435

2. https://github.com/CarolineCheng233/row_socket 

    emmm 这个仓库的源代码由很多错误，我稍作修改让他可以编译通过了...  
    修改后的文件存放在 sockRaw/ 文件夹下

 
