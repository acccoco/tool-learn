//
// Created by charvl on 2020/5/31.
// 代理模式
// 代理模式：不改变原有的接口。代理是透明的
//

#ifndef GOF_PROXY_H
#define GOF_PROXY_H

#include "../common.h"

namespace Proxy {

    /**
     * 天火圣裁
     */
    class IDivineVerdictOfHeavenFire {
    public:
        /**
         * 天火圣裁的武器技能：天火大剑
         */
        virtual void GreatSwordOfHeavenFire() = 0;
    };

    /**
     * 一把天火圣裁
     */
    class DivineVerdictOfHeavenFire: public IDivineVerdictOfHeavenFire {
    public:
        void GreatSwordOfHeavenFire() override {
            cout << "使用了天火圣裁" << endl;
            cout << "生命垂危" << endl;
        }
    };

    /**
     * 天火圣裁的代理模式
     */
    class DVHFProxy: public IDivineVerdictOfHeavenFire {
    private:
        DivineVerdictOfHeavenFire* _DVHF;
    public:
        DVHFProxy(DivineVerdictOfHeavenFire* DVHF):_DVHF(DVHF) {}
        void GreatSwordOfHeavenFire() override {
            _DVHF->GreatSwordOfHeavenFire();
            cout << "proxy: 生命回复" << endl;
        }
    };

    /**
     * 女武神-琪亚娜
     */
    class Kiana {
    public:
        /**
         * 使用家传技能：天火自裁
         */
        void DVHF(IDivineVerdictOfHeavenFire* dvhf) {
            dvhf->GreatSwordOfHeavenFire();
        }
    };

    /**
     * 代理模式的测试
     */
    static void Test() {
        cout << endl << "------ proxy ------" << endl;

        DivineVerdictOfHeavenFire* dvhf = new DivineVerdictOfHeavenFire();

        Kiana* kiana1 = new Kiana();
        kiana1->DVHF(dvhf);
        delete kiana1;
        cout << "kiana1 die" << endl << endl;

        Kiana* kiana2 = new Kiana();
        DVHFProxy* dvhfProxy = new DVHFProxy(dvhf);
        kiana2->DVHF(dvhfProxy);
        cout << "kiana is almost dead" << endl;

        delete kiana2;
        delete dvhfProxy;
        delete dvhf;
    };
}

#endif //GOF_PROXY_H
