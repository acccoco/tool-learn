#include "../unp.h"
# define OPEN_MAX 256       // <limits.h>中并没有OPEN_MAX的定义

/**
 * echo服务器
 * 单线程使用 poll 来处理多个连接
 * 使用 client 数组表示关心的xx
 */

int main(int argc, char**argv) {

    struct pollfd client[OPEN_MAX];
    int sockfd;                     // client 数组中的元素
    int i;                          // client 数组的临时下标
    int clientMaxValid_i;           // client 数组中有效连接的最大下标
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

    /* 初始化 client 集合 */
    client[0].fd = listenfd;
    client[0].events = POLLRDNORM;      // 关心 listenfd 是否可读
    for (i = 1; i < OPEN_MAX; i++)
        client[i].fd = -1;      // -1 表示poll不关心的描述符/无效的描述符
    clientMaxValid_i = 0;

    for (;;) {
        nready = Poll(client, clientMaxValid_i + 1, INFTIM);    // INFTIM表示无限阻塞
        /* 每次只会监听最多一个连接请求，和若干个客户端数据发送 */

        /* 监听到了客户端的连接请求 */
        if (client[0].revents & POLLRDNORM) {
            clilen = sizeof(cliaddr);
            connfd = Accept(listenfd, (SA*)&cliaddr, &clilen);

            /* 将客户端的sockfd 加入到 client集合中 */
            for (i = 0; i < OPEN_MAX; i++) {
                if (client[i].fd < 0) {
                    client[i].fd = connfd;
                    break;
                }
            }
            if (i == OPEN_MAX)
                err_quit("too many clients");

            /* 让 poll 关心这个sockfd */
            client[i].events = POLLRDNORM;
            if (i > clientMaxValid_i)
                clientMaxValid_i = i;

            if (--nready <= 0)
                continue;
        }

        /* 客户端发来了数据 */
        for (i = 0; i <= clientMaxValid_i; i++) {     // 遍历整个client集合，才能找到是哪一个客户端发来了数据
            sockfd = client[i].fd;
            if (sockfd < 0)
                continue;
            if (client[i].revents & (POLLRDNORM | POLLERR)) {
                bufferSize = Read(sockfd, buffer, MAXLINE);

                /* 客户端连接出现了错误 */
                if (bufferSize < 0) {
                    if (errno == ECONNRESET) {
                        Close(sockfd);
                        client[i].fd = -1;
                    }
                }

                /* 客户端连接 EOF */
                else if (bufferSize == 0) {
                    Close(sockfd);
                    client[i].fd = -1;
                }
                else
                    Writen(sockfd, buffer, bufferSize);

                if (--nready <= 0)
                    break;
            }
        }
    }
}