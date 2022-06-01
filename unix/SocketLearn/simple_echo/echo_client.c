/**
 * 描述：echo 程序的客户端
 * 命令行参数：[127.0.0.1]
 * 问题1：发-收-发-收 的模式 无法充分利用带宽。
 * 问题2：如果文件重定向到stdin，最后一行由于EOF，fgets返回NULL，因此不会被发送
 */

#include "../unp.h"

void str_cli(FILE *fp, int sockfd);

int main(int argc, char** argv) {

    int sock_fd;                    // 用于和服务器建立连接的套接字
    struct sockaddr_in servaddr;    // 服务器的地址结构

    if (argc != 2) {
        err_quit("usage: tcpcli <IPaddress>");
    }

    sock_fd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    Connect(sock_fd, (struct sockaddr*) &servaddr, sizeof(servaddr));
    str_cli(stdin, sock_fd);        // str_cli是echo客户端的功能实现

    exit(0);
}

/**
 * echo客户端的功能实现
 * 从流（stdin）中读取数据，发送到服务器，把服务器返回的数据输出至流stdout
 */
void str_cli(FILE *fp, int sockfd)
{
	char	sendline[MAXLINE], recvline[MAXLINE];

	while (Fgets(sendline, MAXLINE, fp) != NULL) {

		Writen(sockfd, sendline, strlen(sendline));

		if (Readline(sockfd, recvline, MAXLINE) == 0)
			err_quit("str_cli: server terminated prematurely");

		Fputs(recvline, stdout);
	}
}