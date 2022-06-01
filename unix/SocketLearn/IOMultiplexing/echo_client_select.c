/**
 * 说明：echo 程序的客户端
 * 命令行参数：[127.0.0.1]。如果没有参数，默认使用本地回环地址
 * 在输入EOF之后会半关闭：发送FIN
 * 使用select 来等待stdin的输入和sockfd的相应，可以处理批量输入
 */


#include "../unp.h"
void str_cli(FILE *fp, int sockfd);

int main(int argc, char** argv) {

    int sock_fd;        // 用于和服务器建立连接的套接字
    struct sockaddr_in servaddr;    // 服务器的地址结构
    char ipAddrStr[16] = "127.0.0.1";
    char* ipAddrStrPtr;

    /* 命令行读取服务器IP地址 */
    if (argc == 1)
        ipAddrStrPtr = ipAddrStr;
    else
        ipAddrStrPtr = argv[1];

    /* 准备连接套接字 */
    sock_fd = Socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    Inet_pton(AF_INET, ipAddrStrPtr, &servaddr.sin_addr);


    Connect(sock_fd, (struct sockaddr*) &servaddr, sizeof(servaddr));
    str_cli(stdin, sock_fd);

    exit(0);
}

/**
 * echo客户端的功能实现
 * 参数：fp表示一个文件指针，从该文件指针中读取数据发送到服务器
 * 参数：sockfd表示与服务器连接的套接字描述符
 */
void str_cli(FILE *fp, int sockfd)
{
    int maxfdp1;            // 最大文件描述符+1
    int stdineof;           // stdin是否已经到达了EOF
    fd_set rset;            // 需要select的文件描述符的集合
    char buf[MAXLINE];      // read 和 write 使用的缓冲
    int n;                  // 缓冲 buf 的有效长度

    stdineof = 0;
    FD_ZERO(&rset);
    for (;;) {

        /* 进行select */
        if (stdineof == 0)
            FD_SET(fileno(fp), &rset);
        FD_SET(sockfd, &rset);
        maxfdp1 = max(fileno(fp), sockfd) + 1;
        Select(maxfdp1, &rset, NULL, NULL, NULL);   // 时间设置为NULL，表示阻塞

        /* sockfd已经可以读了 */
        if (FD_ISSET(sockfd, &rset)) {
            if((n = Read(sockfd, buf, MAXLINE)) == 0) {
                if (stdineof == 1)
                    return;
                else
                    err_quit("str_cli: server terminated permaturely");
            }
            Write(fileno(stdout), buf, n);
        }
        
        /* fp的数据已经准备好了 */
        if (FD_ISSET(fileno(fp), &rset)) {
            if ((n = Read(fileno(fp), buf, MAXLINE)) == 0) {
                stdineof = 1; 
                Shutdown(sockfd, SHUT_WR);  // 半关闭，不再写了，向服务器发送FIN
                FD_CLR(fileno(fp), &rset);
                continue;
            }
            Writen(sockfd, buf, n);
        }
    }
}