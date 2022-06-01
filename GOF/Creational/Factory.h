//
// Created by charvl on 2020/5/30.\
// 工厂模式
// 工厂模式的四个要素：抽象工厂，具体工厂，抽象产品，具体产品
//

#ifndef GOF_FACTORY_H
#define GOF_FACTORY_H

#include "../common.h"

/**
 * 抽象产品：为具体产品提供接口
 */
class AbstractProduct {
public:

    /**
     * - 展示产品的信息
     * - 产品需要具备的方法
     */
    virtual void ShowDetail() = 0;
};

/**
 * 抽象工厂：为具体工厂提供接口
 */
class AbstractFactory {
public:

    /**
     * - 创建一个产品
     * - 工厂需要具备的方法
     */
    virtual AbstractProduct* NewProduct() = 0;
};

/**
 * 具体产品：正方形
 */
class ProductSquare: public AbstractProduct {
public:
    void ShowDetail() override {
        cout << "I'm a square" << endl;
    }
};

/**
 * 具体工厂：生产正方形的工厂
 */
class FactorySquare: public AbstractFactory {
public:
    ProductSquare* NewProduct() override {
        cout << "create product: square" << endl;
        return new ProductSquare();
    }
};

/**
 * 具体产品：圆
 */
class ProductCircle: public AbstractProduct {
public:
    void ShowDetail() override {
        cout << "I'm a circle" << endl;
    }
};

/**
 * 具体工厂：生产圆的工厂
 */
class FactoryCircle: public AbstractFactory {
public:
    ProductCircle* NewProduct() override {
        cout << "create product: circle" << endl;
        return new ProductCircle();
    }
};

/**
 * 工厂模式的测试
 */
class TestFactory {
public:
    static void Test() {
        cout << endl << "------ factory ------" << endl;

        AbstractFactory* factory;
        AbstractProduct* product;

        factory = new FactorySquare();
        product = factory->NewProduct();
        product->ShowDetail();
        delete factory;
        delete product;

        factory = new FactoryCircle();
        product = factory->NewProduct();
        product->ShowDetail();
        delete factory;
        delete product;
    }
};

#endif //GOF_FACTORY_H
