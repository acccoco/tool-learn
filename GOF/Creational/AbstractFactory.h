//
// Created by charvl on 2020/5/31.
// 抽象工厂
//

#ifndef GOF_ABSTRACTFACTORY_H
#define GOF_ABSTRACTFACTORY_H

/**
 * - 抽象产品
 * - 喵喵崩坏兽
 */
class AbstractMeow {
public:

    /* 猫叫 */
    virtual void SayMeow() = 0;
};

/**
 * - 抽象产品
 * - 泰坦
 */
class AbstractTitan {
public:

    /* 泰坦机甲拳击攻击 */
    virtual void Box() = 0;
};

/**
 * - 抽象工厂
 * - 创建各种类型的崩坏兽
 */
class DestroyerFactory {
public:
    virtual AbstractMeow* CreateMeow() = 0;
    virtual AbstractTitan* CreateTitan() = 0;
};

/**
 * - 具体产品
 * - 傲娇系崩坏兽-喵喵
 */
class TsundereMeow : public AbstractMeow {
public:
    void SayMeow() override {
        cout << "傲娇系崩坏兽-Meow: Meow" << endl;
    }
};

/**
 * - 具体产品
 * - 傲娇系崩坏兽-泰坦
 */
class TsundereTitan: public AbstractTitan {
public:
    void Box() override {
        cout << "傲娇系崩坏兽-Titan：锤你胸口" << endl;
    }
};

/**
 * - 具体工厂
 * - 生产傲娇系崩坏兽
 */
class TsundereDestroyerFactory: public DestroyerFactory {
public:
    TsundereMeow* CreateMeow() override {
        cout << "创建傲娇系崩坏兽: " << "Meow" << endl;
        return new TsundereMeow();
    }
    TsundereTitan* CreateTitan() override {
        cout << "创建傲娇系崩坏兽: " << "Titan" << endl;
        return new TsundereTitan();
    }
};

/**
 * - 具体产品
 * - 高冷系崩坏兽：Meow
 */
class HighcoolMeow: public AbstractMeow {
public:
    void SayMeow() override {
        cout << "高冷系崩坏兽-Meow: Meow" << endl;
    }
};

/**
 * -具体产品
 * - 高冷系崩坏兽：Titan
 */
class HighcoolTitan: public AbstractTitan {
public:
    void Box() override {
        cout << "高冷系崩坏兽-Titan：锤你胸口" << endl;
    }
};

/**
 * - 具体工厂
 * - 创造出高冷系崩坏兽
 */
class HighcoolDestroyerFactory: public DestroyerFactory {
public:
    HighcoolMeow* CreateMeow() override {
        cout << "创建高冷系崩坏兽: " << "Meow" << endl;
        return new HighcoolMeow();
    }
    HighcoolTitan* CreateTitan() override {
        cout << "创建高冷系崩坏兽: " << "Titan" << endl;
        return new HighcoolTitan();
    }
};


/**
 * 抽象工厂模式的测试
 */
class TestAbstractFatory {
public:
    static void Test() {
        cout << endl << "------ abstract factory ------" << endl;

        DestroyerFactory* destroyerFactory;

        destroyerFactory = new TsundereDestroyerFactory();
        CreateAndUseDestroyers(destroyerFactory);
        delete destroyerFactory;

        destroyerFactory = new HighcoolDestroyerFactory();
        CreateAndUseDestroyers(destroyerFactory);
        delete destroyerFactory;
    }

    /**
     * 创造崩坏兽，然后使用崩坏兽
     */
    static void CreateAndUseDestroyers(DestroyerFactory* factory) {
        AbstractMeow* meow = factory->CreateMeow();
        AbstractTitan* titan = factory->CreateTitan();

        meow->SayMeow();
        titan->Box();

        delete meow;
        delete titan;
    }
};

#endif //GOF_ABSTRACTFACTORY_H
