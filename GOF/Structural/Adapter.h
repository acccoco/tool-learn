//
// Created by charvl on 2020/5/31.
// 适配器模式
// 适配器模式：改变原有的接口
//

#ifndef GOF_ADAPTER_H
#define GOF_ADAPTER_H

#include "../common.h"

namespace Adapter {

    /**
     * 休伯利安使用的电源模块
     */
    class IElectricSource {
    public:
        /**
         * 电源模块需要输出电能
         */
        virtual void ElectricOutput() = 0;
    };

    /**
     * 崩坏结晶
     */
    class HoukaiCrystal {
    public:

        /**
         * 崩坏结晶以崩坏能的形式输出能量
         */
        void HoukaiOutput() {
            cout << "houkai crystal out: houkai energy" << endl;
        }
    };

    /**
     * 崩坏结晶的适配器
     * 将输出的崩坏能转化为电能
     */
    class HoukaiAdapter: public IElectricSource {
    private:
        HoukaiCrystal* _houkaiCrystal;
    public:
        HoukaiAdapter(HoukaiCrystal* houkaiCrystal) :_houkaiCrystal(houkaiCrystal){}
        void ElectricOutput() override {
            _houkaiCrystal->HoukaiOutput();
            cout << "houkai adapter: convert houkai energy into electric energy" << endl;
        }
    };

    /**
     * 核反应炉
     */
    class NuclearReactor {
    public:
        /**
         * 核反应炉以热能的形式输出能量
         */
        void HeatOutput() {
            cout << "nuclear reactor output: heat" << endl;
        }
    };

    /**
     * 核反应炉的适配器
     * 将核反应堆输出的热能转化为电能
     */
    class NuclearAdapter: public IElectricSource {
    private:
        NuclearReactor* _nuclearReactor;
    public:
        NuclearAdapter(NuclearReactor* nuclearReactor) :_nuclearReactor(nuclearReactor){}
        void ElectricOutput() override {
            _nuclearReactor->HeatOutput();
            cout << "nuclear adapter: convert heat energy into electric energy" << endl;
        }
    };

    /**
     * 休伯利安舰
     * 需要以电能为能源
     */
    class Huberian {
    public:
        void Run(IElectricSource* electricSource) {
            electricSource->ElectricOutput();
            cout << "Huberian run with the energy" << endl;
        }
    };

    /**
     * 适配器模式的测试
     */
    static void Test() {
        cout << endl << "------ adapter ------" << endl;

        Huberian huberian;
        IElectricSource* electricSource;

        /**
         * 为休伯利安使用崩坏能
         */
        HoukaiCrystal* houkaiCrystal = new HoukaiCrystal();
        electricSource = new HoukaiAdapter(houkaiCrystal);
        huberian.Run(electricSource);
        delete electricSource;
        delete houkaiCrystal;

        /**
         * 为休伯利安换上核反应堆
         */
        NuclearReactor* nuclearReactor = new NuclearReactor();
        electricSource = new NuclearAdapter(nuclearReactor);
        huberian.Run(electricSource);
        delete electricSource;
        delete nuclearReactor;
    };
}

#endif //GOF_ADAPTER_H
