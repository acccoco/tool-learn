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
    int share_fd;
    share_t *share_ptr = NULL;

    /* 打开文件 */
    share_fd = open(SHARED_FILE, O_RDONLY);
    if (share_fd < 0)
        fprintf(stderr, "open file failed: %s\n", SHARED_FILE);

    /* 设置内存映射 */
    share_ptr = mmap(NULL, sizeof(share_t),
        PROT_READ, MAP_SHARED, share_fd, 0);

    /* 可以关闭文件了 */
    close(share_fd);

    /* 从内存映射读取 */
    printf("mmap content is: \n");
    while(1) {
        printf("[key: %20s, value: %20s]\n", share_ptr->key, share_ptr->val);
        sleep(1);
    }

    munmap(share_ptr, sizeof(share_t));

    return 0;
}