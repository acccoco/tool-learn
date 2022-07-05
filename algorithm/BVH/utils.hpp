
#ifndef BVH_UTILS_HPP
#define BVH_UTILS_HPP

#include <opencv2/opencv.hpp>


/* 键盘编号 */
const int K_ESC = 27;
const int K_LEFT = 37;
const int K_UP = 38;
const int K_RIGHT = 39;
const int K_DOWN = 40;


/* 颜色定义 */
const cv::Vec3f COLOR_GRAY{150.f, 150.f, 150.f};
const cv::Vec3f COLOR_RED{230.f, 20.f, 20.f};


/* 生成 0 到 1 的浮点随机数 */
float random_float_get();


/* 生成随机的颜色 */
cv::Vec3f random_color_get();


#endif //BVH_UTILS_HPP
