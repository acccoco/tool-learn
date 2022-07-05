#include <mutex>
#include <string>
#include <thread>
#include <iostream>
#include <condition_variable>

/**
 * condition variable 只提供了等待队列和通知机制，需要借助 mutex 的互斥机制，mutex 保护的是 conditon variable 的队列。
 * 如果没有互斥机制，那么多个线程同时进行 wait 操作，一些线程可能无法正确的挂载到等待队列上。
 */


std::mutex              m;
std::condition_variable cv;
std::string             data;
bool                    ready     = false;
bool                    processed = false;

void worker_thread()
{
    // Wait until main() sends data
    std::unique_lock lk(m);
    cv.wait(lk, [] { return ready; });

    // after the wait, we own the lock.
    std::cout << "Worker thread is processing data\n";
    data += " after processing";

    // Send data back to main()
    processed = true;
    std::cout << "Worker thread signals data processing completed\n";

    // Manual unlocking is done before notifying, to avoid waking up
    // the waiting thread only to block again (see notify_one for details)
    lk.unlock();
    cv.notify_one();
}

int main()
{
    std::thread worker(worker_thread);

    data = "Example data";
    // send data to the worker thread
    {
        std::lock_guard lk(m);
        ready = true;
        std::cout << "main() signals data ready for processing\n";
    }
    cv.notify_one();

    // wait for the worker
    {
        std::unique_lock lk(m);
        cv.wait(lk, [] { return processed; });
    }
    std::cout << "Back in main(), data = " << data << '\n';

    worker.join();
}