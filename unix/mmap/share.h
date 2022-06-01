
/* 内存映射的文件名称 */
#define SHARED_FILE "./share"

/**
 * 内存映射区的公共数据结构
 */
typedef struct share {
    char key[256];
    char val[256];
} share_t;

