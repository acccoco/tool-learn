#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

/**
 * 加密函数，glib对jmp_buf进行了加密
 */
unsigned long PTR_MANGLE(unsigned long var)
{
    asm("movq %1, %%rdx \n"
        "xor    %%fs:0x30, %%rdx\n"
        "rol    $0x11,%%rdx\n"
        "movq %%rdx, %0\t\n"
        : "=r"(var)
        : "0"(var));
    return var;
}

/**
 * 解密函数，glib对jmp_buf进行了加密
 */
unsigned long PTR_DEMANGLE(unsigned long var)
{
    asm("ror $0x11, %0\n"
        "xor %%fs:0x30, %0"
        : "=r"(var)
        : "0"(var));
    return var;
}

/**
 * jmp_buf里面的内容
 */
typedef struct buffer
{
    unsigned long RBX;
    unsigned long RBP;     // 栈帧
    unsigned long R12;
    unsigned long R13;
    unsigned long R14;
    unsigned long R15;
    unsigned long RSP;     // 栈基址
    unsigned long PC;      // 接下来要从哪里运行
} buffer;

// struct task 的前向定义
struct task;

// 协程中运行的函数
typedef void (*task_func)(struct task *, void *arg);

// 代表一个协程任务
struct task
{
    unsigned char *stack; // 协程使用的栈，可以用作调试
    jmp_buf buf;          // 协程当前运行的地方
    jmp_buf caller_buf;   // 控制是从哪里跳转过来的
    task_func func;
    void *arg; // 协程里面函数运行所需的参数
};

// 栈的大小定义为4096
#define STACK_SIZE 4096

// 借助该全局变量来传递参数
struct task *__task;
/**
 * 该函数的主要作用是给task.func传递参数，该函数的栈应该是新分配的栈
 */
void __start()
{
    // 将参数保存在新分配的栈空间里面了
    struct task *t = __task;
    int res = setjmp(__task->buf);
    if (res == 0)
    {
        // 跳转回init函数里面
        longjmp(__task->caller_buf, 0);
    }

    // 从next函数跳转来
    // 不要再使用__task了，此时的cur_task已经不等于t了
    t->func(t, t->arg);

    // func执行结束了
    setjmp(t->buf);
    longjmp(t->caller_buf, 0);
}

void init(struct task *t, task_func func, void *arg)
{
    // 为协程分配栈
    t->stack = (unsigned char *)malloc(STACK_SIZE);
    t->arg = arg;
    t->func = func;

    // 初始化jmp_buf
    int res = setjmp(t->buf);
    if (res == 0)
    {
        memcpy((void *)t->caller_buf, (void *)t->buf, sizeof(t->buf));
        buffer *buf = (buffer *)t->buf;
        // 设置入口地址
        buf->PC = PTR_MANGLE((unsigned long)__start);
        // 设置栈指针和frame指针
        buf->RBP = buf->RSP = PTR_MANGLE((unsigned long)(t->stack + STACK_SIZE - 16));

        // 将任务结构体设置为全局变量，__start马上会用到
        __task = t;

        // 跳到__start那里去
        longjmp(t->buf, 0);
    }

    // 从__start跳转回来，表示参数已经保存在新的栈里面了
}

/**
 * 在函数里面调用
 * val 是函数内向外产出的信息
 */
int yield(struct task *t, int val)
{
    int res;
    res = setjmp(t->buf);
    if (res == 0)
    {
        // 跳转回调度器
        longjmp(t->caller_buf, val);
    }

    // 从调度器跳来
    return res;
}

/**
 * 进入协程的方法
 * val是要传入的值
 */
int next(struct task *t, int val)
{
    int res;
    res = setjmp(t->caller_buf);
    if (res == 0)
    {
        // 跳转到协程里面
        longjmp(t->buf, val);
    }

    // 从协程跳转过来
    return res;
}

// 一个协程函数的例子
// arg参数应该是一个数组：int arg[3]
void foo(struct task *t, void *arg)
{
    int out = 1;
    int i;
    for (i = 0; i < 3; ++i)
    {
        printf("%d-%d: hello", out, ((int *)arg)[i]);
        out = yield(t, 1);
    }
}

int main()
{
    // 初始化一个任务对象
    struct task *t1 = (struct task *)malloc(sizeof(struct task));
    int arg[3] = {233, 122, 999};
    init(t1, foo, (void *)arg);

    // 使用协程的特性
    for (int i = 6; i < 15; ++i)
    {
        next(t1, i);
        printf(" world\n");
    }
}



