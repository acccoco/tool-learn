#include <array>
#include <atomic>
#include <vector>
#include <thread>
#include <utility>
#include <iostream>


/**
 * 原子对象可以使用 mutex 和各种 lock 机制实现，也可以用 CPU 的 lock-free atomic instruction 实现
 * 对象的内存对齐情况会影响原子对象是否无锁
 */

struct Arr1 {
    int val[1];
};
struct Arr2 {
    int val[2];
};
struct Arr3 {
    int val[3];
};
struct Arr4 {
    int val[4];
};
struct Arr5 {
    int val[5];
};


void is_atomic_example()
{
    std::cout << std::boolalpha;
    std::cout << "struct{int[1]} is atomic: " << std::atomic<Arr1>{}.is_lock_free() << std::endl;
    std::cout << "struct{int[2]} is atomic: " << std::atomic<Arr2>{}.is_lock_free() << std::endl;
    std::cout << "struct{int[3]} is atomic: " << std::atomic<Arr3>{}.is_lock_free() << std::endl;
    std::cout << "struct{int[4]} is atomic: " << std::atomic<Arr4>{}.is_lock_free() << std::endl;
    std::cout << "struct{int[5]} is atomic: " << std::atomic<Arr5>{}.is_lock_free() << std::endl;
}


/**
 * std::memory_order_relaxed 只适合用来实现原子计数器
 */
void increment_counter()
{
    std::atomic<int> counter{0};

    auto do_work = [&](int thread_num) {
        for (int i = 0; i < 10; ++i)
            counter.fetch_add(1, std::memory_order_relaxed);
    };

    std::vector<std::thread> threads;
    int                      thread_cnt = 10;
    for (int i = 0; i < thread_cnt; ++i)
        threads.emplace_back(do_work, i);
    for (int i = 0; i < thread_cnt; ++i)
        threads[i].join();


    std::cout << "final counter value: " << counter.load() << std::endl;
}


int main()
{
    is_atomic_example();
    increment_counter();
}