#include "../unp.h"

/**
 * echo服务器
 * 单线程使用select来处理多个连接
 * 使用client数组，存放已经建立连接的sockfd
 * 使用allset/rset，存放需要select - read的集合：包括一众客户端sockfd，以及服务器的listen sockfd
 */

int main(int argc, char**argv) {

    int client[FD_SETSIZE];         // 已经建立连接的客户端的 sockfd 的集合；-1表示没有使用
    int sockfd;                     // client 数组中的元素
    int i;                          // client 数组的临时下标
    int clientMaxIndex;             // client 数组中有效连接的最大下标

    fd_set rset;                    // 需要select 的一系列描述符。包括listen sockfd，以及客户端连接的 sockfd
    fd_set allset;                  // allset 是 rset 第一个副本。因为rset可能会被select函数改变
    int maxfd;                      // rset/allset 集合中最大的描述符编号
    int nready;                     // select 返回后，准备好的描述符的数量
    
    char buffer[MAXLINE];           // 存放临时数据的数组
    ssize_t bufferSize;             // 临时数据的大小

    int connfd;                     // listen 到的新连接
    int listenfd;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;

    /* 服务器Listen */
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    Bind(listenfd, (SA*)&servaddr, sizeof(servaddr));
    Listen(listenfd, LISTENQ);

    /* 初始化各个集合 */
    maxfd = listenfd;
    clientMaxIndex = -1;
    for (i = 0; i < FD_SETSIZE; i++) 
        client[i] = -1;
    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);


    for (;;) {
        rset = allset;
        nready = Select(maxfd + 1, &rset, NULL, NULL, NULL);
        /* 每次只会监听最多一个连接请求，和若干个客户端数据发送 */

        /* 监听到了客户端的连接请求 */
        if (FD_ISSET(listenfd, &rset)) {
            clilen = sizeof(cliaddr);
            connfd = Accept(listenfd, (SA*)&cliaddr, &clilen);

            /* 将客户端的sockfd 加入到 client集合中 */
            for (i = 0; i < FD_SETSIZE; i++) {
                if (client[i] < 0) {
                    client[i] = connfd;
                    break;
                }
            }
            if (i == FD_SETSIZE)
                err_quit("too many clients");

            /* 将客户端的 sockfd 加入 allset集合中。同时更新maxfd，maxi */
            FD_SET(connfd, &allset);
            if (connfd > maxfd)
                maxfd = connfd;
            if (i > clientMaxIndex)
                clientMaxIndex = i;

            if (--nready <= 0)
                continue;
        }

        /* 客户端发来了数据 */
        for (i = 0; i <= clientMaxIndex; i++) {     // 遍历整个client集合，才能找到是哪一个客户端发来了数据
            sockfd = client[i];
            if (sockfd < 0)
                continue;
            if (FD_ISSET(sockfd, &rset)) {
                bufferSize = Read(sockfd, buffer, MAXLINE);
                if (bufferSize == 0) {
                    Close(sockfd);
                    FD_CLR(sockfd, &allset);
                    client[i] = -1;
                }
                else
                    Writen(sockfd, buffer, bufferSize);

                if (--nready <= 0)
                    break;
            }
        }
    }
}