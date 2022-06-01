/***********************************************************
* 动态显示进度条
* 有 2 种实现方法
*  方法1:通过退格（\b）实现
*  方法2:通过回车（\r）实现
* 注：由于输出使用了行缓冲，如果需要线程睡眠，那么
*  - cout 应该使用 cout.flush() 来立即输出结果
*  - printf 应该使用 fflush(stdout) 来立即输出结果
**********************************************************/

#include <thread>
#include <chrono>
#include <stdio.h>
#include <iostream>

/* 通过 回车 \r 实现的进度条 */
void update_progress_r()
{
   printf("\n");
   for (int i = 0; i < 10; ++i)
   {
       printf("\r progress: %d", i);
       fflush(stdout);
       std::this_thread::sleep_for(std::chrono::milliseconds(500));
   }
}

/* 通过 退格 \b 实现的进度条 */
void update_progress_b()
{
   std::cout << std::endl
             << "progress: x";
   for (int i = 0; i < 10; ++i)
   {
       std::cout << "\b";
       std::cout << i;
       std::cout.flush();
       std::this_thread::sleep_for(std::chrono::milliseconds(500));
   }
}

int main(int argc, char *argv[])
{
   update_progress_r();
   update_progress_b();
   return 0;
}
