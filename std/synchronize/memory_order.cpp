#include <array>
#include <atomic>
#include <vector>
#include <thread>
#include <utility>
#include <iostream>


/**
 * release-acquire 的常见用法
 */
void release_acquire_order()
{
    std::atomic<std::string *> ptr;
    int                        data;

    std::thread producer([&]() {
        auto *p = new std::string("Hello");
        data    = 42;
        ptr.store(p, std::memory_order_release);
    });

    std::thread consumer([&]() {
        std::string *p;
        while (!(p = ptr.load(std::memory_order_acquire)))
            ;
        // 以下的 assert 一定不会被触发
        assert(*p == "Hello");
        assert(data == 42);
    });


    producer.join();
    consumer.join();
}


/**
 * 利用 CAS(compare and swap) 的原子性，实现了多个线程对 std::vector 的同时 push_back
 * data race 发生在 std::atomic<bool> busy 身上，arr 直接依赖于 busy，因此不用考 memory order，直接使用 relaxed 就好
 */
void rmw_example()
{
    std::vector<int>  arr;
    std::atomic<bool> busy{false};

    auto do_work = [&](int thread_num) {
        for (int i = 0; i < 100000; ++i)
        {
            // test and set
            bool temp = false;
            while (!busy.compare_exchange_weak(temp, true, std::memory_order_relaxed))
                temp = false;

            arr.push_back(i * thread_num);

            busy.store(false, std::memory_order_relaxed);
        }
    };

    std::vector<std::thread> ts;
    for (int i = 0; i < 8; ++i)
        ts.emplace_back(do_work, i + 1);

    for (auto &t: ts)
        t.join();

    assert(arr.size() == 800000);
}


int main()
{
    for (int i = 0; i < 10000; ++i)
        release_acquire_order();

    rmw_example();

    return 0;
}