#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "share.h"

int main(int argc, char *argv[])
{
    int      share_fd;
    void    *temp      = NULL;
    share_t *share_ptr = NULL;

    /* 打开文件 */
    share_fd = open(SHARED_FILE, O_RDWR | O_CREAT | O_TRUNC);
    if (share_fd < 0)
        fprintf(stderr, "open file failed: %s\n", SHARED_FILE);

    /* 向文件内写入初始数据，填充长度 */
    temp = malloc(sizeof(share_t));
    if (!temp)
    {
        fprintf(stderr, "malloc(%ld) failed.\n", sizeof(share_t));
        return 0;
    }
    memset(temp, 0, sizeof(share_t));
    write(share_fd, temp, sizeof(share_t));
    free(temp);

    /* 设置内存映射 */
    share_ptr = mmap(NULL, sizeof(share_t), PROT_READ | PROT_WRITE, MAP_SHARED, share_fd, 0);

    /* 可以关闭文件了 */
    close(share_fd);

    /* 向内存映射区写东西 */
    do
    {
        printf("input key: \n");
        scanf("%s", share_ptr->key);
        printf("input value: \n");
        scanf("%s", share_ptr->val);
    } while (0);

    munmap(share_ptr, sizeof(share_t));

    return 0;
}