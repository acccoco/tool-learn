#include <array>
#include <atomic>
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


int main()
{
    is_atomic_example();

    std::atomic<long long>   data{10};
    std::array<long long, 5> arr{};


    auto do_work = [&](int thread_num) {
        // 第二个参数是 std::memory_order
        arr[thread_num] = data.fetch_add(1, std::memory_order_relaxed);
    };
    {
        std::thread th0{do_work, 0};
        std::thread th1{do_work, 1};
        std::thread th2{do_work, 2};
        std::thread th3{do_work, 3};
        std::thread th4{do_work, 4};
        th0.join();
        th1.join();
        th2.join();
        th3.join();
        th4.join();
    }

    std::cout << "Result : " << data << '\n';

    for (long long val: arr)
    {
        std::cout << "Seen return value : " << val << std::endl;
    }
}