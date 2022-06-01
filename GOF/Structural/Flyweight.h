//
// Created by charvl on 2020/6/9.
// 享元模式：可以支持细粒度大量对象的共享
// 设想这样一个场景：NieR中，经常出现大量机器人同屏的情况。
// 这些机器人的机体是相同的，位置姿态是不同的。
// 可以将机器人的机体设置为享元的内部状态（可以共享），将位置，姿态设置为外部状态
//

#ifndef GOF_FLYWEIGHT_H
#define GOF_FLYWEIGHT_H
#include <utility>

#include "../common.h"

namespace Flyweight {
    /**
 * 非享元角色-外部状态-机器人的运动状态
 */
    class MotionState {
    public:
        MotionState(string position, string gesture): Position(std::move(position)), Gesture(std::move(gesture)) {}
        string Position;        // 位置
        string Gesture;         // 姿态
    };

/**
 * 机器人的抽象类
 */
    class IAndroid {
    public:

        // 根据机器人的位置和姿态在屏幕上绘制
        virtual void DrawGraphics(MotionState state) = 0;
    };

/**
 * 通用型号机器人
 */
    class Android : public IAndroid {
    private:
        string _type;
    public:
        explicit Android(string type) : _type(std::move(type)) {}
        void DrawGraphics(MotionState state) override {
            cout << "Android " << _type << ", at " << state.Position << ", is " << state.Gesture << endl;
        }
    };

/**
 * 机器人“工厂”
 */
    class AndroidFactory {
    private:
        unordered_map<string, Android*> _flyweights;      // 享元仓库
    public:
        Android* GetAndroid(const string& key) {
            auto iter = _flyweights.find(key);
            Android* result;
            if (iter == _flyweights.end()) {
                cout << "not found Android " << key << endl;
                result = new Android(key);
                _flyweights.emplace(key, result);
            }
            else {
                cout << "found Android " << key << endl;
                result = iter->second;
            }
            return result;
        }
    };

    static void Test() {
        cout << endl << "------ Flyweight ------" << endl;

        AndroidFactory factory;
        factory.GetAndroid("01")->DrawGraphics(MotionState("破败高楼", "瞄准"));
        factory.GetAndroid("01")->DrawGraphics(MotionState("广场", "掩护"));
    }
}

#endif //GOF_FLYWEIGHT_H
