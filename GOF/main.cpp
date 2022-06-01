
#include "common.h"

/**
 * 创建型设计模式的头文件
 */
#include "Creational/Singleton.h"
#include "Creational/Prototype.h"
#include "Creational/Factory.h"
#include "Creational/AbstractFactory.h"
#include "Creational/Builder.h"

/**
 * 创建型设计模式
 */
void Creational() {
    cout << endl << "====== Creational ======" << endl;

    TestSingleton::Test();
    TestPrototype::Test();
    TestFactory::Test();
    TestAbstractFatory::Test();
    TestBuilder::Test();
    TestBuilder::Test();
}

/**
 * 结构型设计模式的头文件
 */
#include "Structural/Proxy.h"
#include "Structural/Adapter.h"
#include "Structural/Decorator.h"
#include "Structural/Flyweight.h"

/**
 * 结构型设计模式
 */
void Structural() {
    cout << endl << "====== Structural ======" << endl;

    Proxy::Test();
    Adapter::Test();
    Decorator::Test();
    Flyweight::Test();
}


int main() {

    Creational();
    Structural();

    return 0;
}
