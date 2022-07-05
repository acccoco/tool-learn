#include <iostream>
#include <chrono>
#include <thread>


// yield 可以向 OS 发出 hint，允许先调度其他 thread 允许，这又叫做 "busy sleep".
void little_sleep(std::chrono::microseconds us)
{
    auto start = std::chrono::high_resolution_clock::now();
    auto end   = start + us;
    do
    {
        std::this_thread::yield();
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        std::cout << "cur: " << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count() << std::endl;
    } while (std::chrono::high_resolution_clock::now() < end);
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    little_sleep(std::chrono::microseconds(100));

    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    std::cout << "waited for " << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count()
              << " microseconds\n";
}