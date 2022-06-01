//
// Created by charvl on 2020/6/2.
// 装饰模式
//

#ifndef GOF_DECORATOR_H
#define GOF_DECORATOR_H
#include "../common.h"

namespace Decorator {

    /**
     * 八重樱
     */
    class IYaeSakura {
    public:
        virtual void Skill() = 0;
    };

    /**
     * 八重樱：初始形态——巫女
     */
    class Witch: public IYaeSakura {
    public:
        void Skill() override {
            cout << "呼唤卡莲" << endl;
        }
    };

    /**
     * 八重樱-巫女的装饰器
     */
    class YaeSakuraDecorator: public IYaeSakura {
    private:
        Witch _witch;
    public:
        YaeSakuraDecorator(Witch witch): _witch(witch) {}
        void Skill() override {
            _witch.Skill();
        }
    };

    /**
     * 八重樱：冰八
     */
    class NotForget : public YaeSakuraDecorator {
    public:
        NotForget(Witch witch) :YaeSakuraDecorator(witch){}
        void Skill() override {
            YaeSakuraDecorator::Skill();
            IceSakura();
        }
        void IceSakura() {
            cout << "寒樱斩" << endl;
        }
    };

    /**
     * 八重樱：炎八
     */
    class FireSoul: public YaeSakuraDecorator {
    public:
        FireSoul(Witch witch): YaeSakuraDecorator(witch){}
        void Skill() override {
            YaeSakuraDecorator::Skill();
            Fire();
        }
        void Fire() {
            cout << "八重火垣" << endl;
        }
    };

    static void Test() {
        cout << endl << "------ Decorator ------" << endl;

        cout << "八重樱: " << endl;
        Witch witch;
        witch.Skill();

        cout << "冰八: " << endl;
        NotForget iceYae(witch);
        iceYae.Skill();

        cout << "炎八: " << endl;
        FireSoul fireYae(witch);
        fireYae.Skill();
    }
}

#endif //GOF_DECORATOR_H
