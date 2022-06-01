/**
 * 描述：echo 程序的服务器
 * 命令行参数：无
 * 使用的IO模型：阻塞型；通过子进程来处理连接。
 * 注1：信号处理：捕获SIGCHLD信号，并使用waitpid而不是wait函数来处理，防止留下僵死进程；
 * 注2：重启被中断的系统调用accept；
 */

#include "../unp.h"

void sig_chld(int signo);

int main(int argc, char **argv)
{
    int listenfd;       // 监听请求的 sockfd
    int connfd;         // 表示客户端连接的 sockfd
    pid_t childpid;
    socklen_t clilen;               // 套接字地址结构的长度，用于 值-结果参数
    struct sockaddr_in cliaddr;     // 客户端的地址结构
    struct sockaddr_in servaddr;    // 服务器的地址结构，设为any

    /* 服务器监听指定端口 */
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    Bind(listenfd, (SA *)&servaddr, sizeof(servaddr));
    Listen(listenfd, LISTENQ);

    /* 注册SIGCHLD的信号处理函数 */
    Signal(SIGCHLD, sig_chld);

    for (;;)
    {
        /* 等待客户端的连接，在accept被中断后重启 */
        clilen = sizeof(cliaddr);
        connfd = accept(listenfd, (SA*)&cliaddr, &clilen);
        if (connfd < 0) {
            if (errno == EINTR)
                continue;
            else
                err_sys("accept error");
        }

        /* 使用子进程处理客户端的连接 */
        if ((childpid = Fork()) == 0)
        {
            Close(listenfd);        // 这个操作不会关闭 listenfd，只会让listenfd 的引用计数 -1
            str_echo(connfd);       // str_echo是echo的功能实现
            exit(0);
        }
        Close(connfd);
    }
}

/**
 * SIGCHLD的信号处理函数
 * 处理终止的子进程
 */
void sig_chld(int signo) {
    pid_t pid;
    int stat;

    /*
     * 使用while是为了处理信号不排队的情况
     * waitpid的第一个参数-1表示第一个终止的子进程
     * waitpid的第三个参数WNOHANG表示非阻塞
     */
    while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
        printf("child %d terminated\n", pid);
    
    return;
}