//
// Created by charvl on 2020/5/30.
// 单例模式
// 1. 单例类只有一个实例对象 该对象由单例类自己创建
// 2. 单例类对外提供单例对象的访问点
//

#ifndef GOF_SINGLETON_H
#define GOF_SINGLETON_H

#include "../common.h"

/**
 * lazy 的单例模式
 * @描述 只有在第一次调用 GetInstance()时才会创建这个单例
 */
class SingletonLazy {
private:

    /**
     * 保证外界无法调用构造函数
     */
    SingletonLazy() {
        std::cout << "create Singleton-Lazy" << std::endl;
    }
    static SingletonLazy* instance;

public:
    static SingletonLazy* GetInstance() {
        if (instance == nullptr) {
            instance = new SingletonLazy();
        }
        return instance;
    }

    /**
     * 销毁单例对象
     */
    static void Destroy() {
        if (instance != nullptr) {
            delete instance;
            instance = nullptr;
        }
    }
};

/**
 * hungry 单例模式
 * @details 类一旦被加载 就会创建单例对象
 */
class SingletonHungry {
private:
    static SingletonHungry* instance;

    /**
     * 保证外界无法调用构造函数
     */
    SingletonHungry() {

        std::cout << "create Singleton-Hungry" << std::endl;
    }

public:
    static SingletonHungry* GetInstance() {
        return instance;
    }

    /**
     * 销毁单例对象
     */
    static void Destroy() {
        if (instance != nullptr) {
            delete instance;
            instance = nullptr;
        }
    }
};

/**
 * 单例模式的测试
 */
class TestSingleton {
public:
    static void Test() {
        cout << endl << "------ singleton ------" << endl;
        cout << "first time to use singleton" << endl;

        auto singletonLazy = SingletonLazy::GetInstance();
        auto singletonHungry = SingletonHungry::GetInstance();

        SingletonLazy::Destroy();
        SingletonHungry::Destroy();
    }
};

#endif //GOF_SINGLETON_H
