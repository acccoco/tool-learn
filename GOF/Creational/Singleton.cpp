//
// Created by charvl on 2020/5/30.
//

#include "Singleton.h"

SingletonLazy* SingletonLazy::instance = nullptr;
SingletonHungry* SingletonHungry::instance = new SingletonHungry();
