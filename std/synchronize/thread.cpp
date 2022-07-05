#include <vector>
#include <thread>
#include <iostream>


int main()
{
    // 允许同时执行的线程数量
    std::cout << "concurrent threads are suppored: " << std::thread::hardware_concurrency() << std::endl;


    std::vector<int> arr(2, 0);

    /// 构造完成后，线程立即执行
    std::thread t1([](std::vector<int> &arr, int val) { arr[0] = val; }, std::ref(arr), 2);
    std::thread t2([](std::vector<int> &arr, int val) { arr[1] = val; }, std::ref(arr), 3);

    t1.detach();    // 放任 t1 自己执行，执行完成后自动清理
    t2.join();      // 阻塞等待 t2 执行，执行后清理

    // 此时：可以确定 t2 执行完毕，并不知道 t1 的执行状态
    while (arr[0] != 2)
        ;
    std::cout << "arr: " << arr[0] << ", " << arr[1] << std::endl;
    return 0;
}