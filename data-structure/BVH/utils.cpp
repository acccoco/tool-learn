//
// Created by 漆正杰 on 2021/5/22.
//
#include "./utils.hpp"
#include <random>


float random_float_get() {
    std::random_device dev;
    std::mt19937 random_engine(dev());
    std::uniform_real_distribution<float> dist(0.f, 1.f);

    return dist(random_engine);
}


cv::Vec3f random_color_get() {
    return {random_float_get() * 255.f, random_float_get() * 255.f, random_float_get() * 255.f};
}
