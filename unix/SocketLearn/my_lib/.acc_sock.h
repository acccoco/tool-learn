#ifndef ACC_SOCK
#define ACC_SOCK

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <strings.h>            // BSD 字节操作
#include <string.h>             // c 字节操作
#include <sys/socket.h>         // socket 相关的函数
#include <sys/types.h>          // 类型相关的定义
#include <netinet/in.h>         // 套接字地址结构的定义


#define LISTENQ 1024        // server connect conunt
#define SERV_PORT 9877      // server listen port
#define MAXLINE 4096        // read wirte max line

// socket related method
int Socket(int family, int type, int protocol);
void Connect(int fd, const struct sockaddr *sa, socklen_t salen);
void Bind(int fd, const struct sockaddr *sa, socklen_t salen);
void Listen(int fd, int backlog);
int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr);
void Close(int fd);

// echo server and client
void str_echo(int sockfd);
void str_cli(FILE *fp, int sockfd);

void Inet_pton(int family, const char *strptr, void *addrptr);

pid_t Fork(void);







#endif