//
// Created by charvl on 2020/5/30.
// 原型模式
//

#ifndef GOF_PROTOTYPE_H
#define GOF_PROTOTYPE_H

#include "../common.h"

/**
 * 原型的接口：定义了clone方法
 */
class Prototype {
public:
    virtual Prototype* Clone() = 0;
};

/**
 * 具体的原型类：实现了clone方法
 */
class Square: public Prototype {
private:
    double _width;

public:
    Square(int width): _width(width) {
        cout << "draw a square with width: " << width << endl;
    }

    /**
     * 计算正方形的面积
     */
    void GetArea() {
        double area = _width * 4;
        cout << "the area of square is: " << area << endl;
    }

    Square* Clone() override {
        Square* obj = static_cast<Square*>(malloc(sizeof(Square)));
        obj->_width = this->_width;

        cout << "clone a circle with width: " << obj->_width << endl;

        return obj;
    }
};

/**
 * 原型模式的测试
 */
class TestPrototype {
public:
    static void Test() {
        cout << endl << "------ prototype ------" << endl;
        Square* obj1 = new Square(5);
        Square* obj2 = obj1->Clone();
        obj2->GetArea();

        delete obj1;
        delete obj2;
    }
};

#endif //GOF_PROTOTYPE_H
