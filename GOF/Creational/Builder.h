//
// Created by charvl on 2020/5/31.
// 建造者模式
// 1. 一个复杂对象可以分解为许多个简单对象，每个简单对象可以灵活选择
// 2. 各部件经常发生变化，各部件之间的关系通常比较稳定
//

#ifndef GOF_BUILDER_H
#define GOF_BUILDER_H

#include "../common.h"

/**
 * - 抽象的复杂产品
 * - 一套套装
 */
class Suit {
private:
    string _weapon;     // 套装中的武器
    string _cloth;      // 套装中的衣服

public:
    void SetWeapon(string weapon) {
        this->_weapon = weapon;
    }
    void SetCloth(string cloth) {
        this->_cloth = cloth;
    }

    /**
     * 展示产品的信息
     */
    void Show() {
        cout << "suit details: " << endl;
        cout << "  weapon: " << this->_weapon << endl;
        cout << "  cloth: " << this->_cloth << endl;
    }
};

/**
 * - 抽象的建造者
 * - 生成套装
 */
class SuitBuilder {
protected:
    Suit* _suit = new Suit();

public:
    virtual void BuildWeapon() = 0;
    virtual void BuildCloth() = 0;
    Suit* GetResult() {
        return this->_suit;
    }
};

/**
 * - 建造的管理者
 * - 客户端直接使用这个类
 */
class BuildManager {
private:
    SuitBuilder* _builder;

public:
    BuildManager(SuitBuilder* builder): _builder(builder) {}
    Suit* Build() {
        _builder->BuildWeapon();
        _builder->BuildCloth();
        return _builder->GetResult();
    }
};

/**
 * - 具体的建造者
 * - 生产黑骑士套装
 */
class BlackSuitBuilder: public SuitBuilder {
public:
    void BuildWeapon() override {
        string weapon = "black";
        this->_suit->SetWeapon(weapon);
        cout << "build: weapon: " << weapon << endl;
    }

    void BuildCloth() override {
        string cloth = "black";
        this->_suit->SetCloth(cloth);
        cout << "build: cloth: " << cloth << endl;
    }
};

/**
 * Builder模式的测试
 */
class TestBuilder {
public:
    static void Test() {
        cout << endl << "------ builder ------" << endl;

        SuitBuilder* builder = new BlackSuitBuilder();
        BuildManager* manager = new BuildManager(builder);
        Suit* suit = manager->Build();

        suit->Show();

        delete suit;
        delete manager;
        delete builder;
    }
};

#endif //GOF_BUILDER_H
