#include <array>
#include <atomic>
#include <vector>
#include <thread>
#include <random>
#include <utility>
#include <iostream>
#include <semaphore>


/**
 * 这个例子可以检测出内存乱序。
 * 在 M1 Mac 中，大概有 10% 的几率内存乱序。
 */
int main()
{
    // semaphore
    std::binary_semaphore      sem1{0}, sem2{0};
    std::counting_semaphore<2> sem{0};

    // random num
    std::random_device                 rd;
    std::mt19937                       engine(rd());
    std::uniform_int_distribution<int> dist(0, std::numeric_limits<int>::max());

    int x, y;
    int r1, r2;

    std::thread t1([&]() {
        for (;;)
        {
            sem1.acquire();
            // 随机等待一段时间
            while (dist(engine) % 8 != 0)
                ;
            x = 1;
            asm volatile("" ::: "memory");    // prevent compiler reordering
            r1 = y;
            sem.release();
        }
    });

    std::thread t2([&]() {
        for (;;)
        {
            sem2.acquire();
            while (dist(engine) % 8 != 0)
                ;
            y = 1;
            asm volatile("" ::: "memory");    // prevent compiler reordering
            r2 = x;
            sem.release();
        }
    });

    int detected = 0;
    for (int iter = 0;; ++iter)
    {
        x = 0;
        y = 0;

        sem1.release();
        sem2.release();
        // thread run
        sem.acquire();
        sem.acquire();

        if (r1 == 0 && r2 == 0)
        {
            ++detected;
            std::cout << detected << " reorders detected after " << iter << " iterations: " << float(detected) / iter
                      << std::endl;
        }
    }
}
