#include <thread>
#include <vector>
#include <chrono>
#include <iostream>
#include <semaphore>


/**
 * semaphore 内部有一个计数器
 *  - 执行 acquire() 时，计数器减少
 *  - 执行 release() 时，计数器增加
 *  当计数器为 0 时，acquire() 会被阻塞
 *  std::binary_semaphore 就是 std::countint_semaphore<1>
 */


int main()
{
    std::counting_semaphore<16> sema_push_done(0);
    std::counting_semaphore<16> sema_pop_done(1);
    std::vector<int>            arr;
    bool                        terminate = false;


    std::thread worker([&]() {
        while (true)
        {
            sema_push_done.acquire();
            if (terminate)
                break;
            std::cout << arr.back() << std::endl;
            sema_pop_done.release();
        }
    });

    for (int i = 0; i < 10; ++i)
    {
        sema_pop_done.acquire();
        arr.push_back(i);
        sema_push_done.release();
    }
    sema_pop_done.acquire();
    terminate = true;
    sema_push_done.release();

    worker.join();
}