
#ifndef BVH_GEOMETRY_HPP
#define BVH_GEOMETRY_HPP

#include <opencv2/opencv.hpp>
#include "./utils.hpp"


/* 坐标轴方向的枚举 */
enum class Axial {
    X, Y,
};


/* 矩形包围盒 */
class Rectangle {
public:
    float min_x, min_y, max_x, max_y;

    /* 判断直线是否和包围盒相交 */
    static bool is_intersection(const Rectangle &box, const cv::Vec2f &orig, const cv::Vec2f &dir);
};


class Triangle {
public:
    typedef std::shared_ptr<Triangle> ptr;

    /* 三个顶点 */
    cv::Vec2f A, B, C;
    /* 重心 */
    cv::Vec2f center;
    /* 边界 */
    Rectangle boundary{};

    /* 建立三角形：会初始化重心和边界盒 */
    Triangle(const cv::Vec2f &a, const cv::Vec2f &b, const cv::Vec2f &c);

    /* 绘制当前三角形 */
    void draw(cv::Mat &canvas, const cv::Vec3f &color) const;

    /**
     * 在一定范围内生成一个三角形
     * @param canvas 限定的范围
     * @param min_size 最小尺寸，0-1
     * @param max_size 最大的尺寸 0-1
     * @return
     */
    static ptr triangle_gen(const Rectangle &canvas, float min_size, float max_size) ;

    /**
     * 计算一组三角形的包围盒
     * @note 确保三角形的数量大于 1
     */
    static std::shared_ptr<Rectangle> boundary_box_gen(const std::vector<std::shared_ptr<Triangle>> &triangles);
};


/**
 * 对半切分，可以确保切分结果是平衡的
 * @note 确保三角形个数大于 1
 */
std::array<std::vector<Triangle::ptr>, 2>
split_tris(const std::vector<Triangle::ptr> &triangles, Axial axial);

#endif //BVH_GEOMETRY_HPP
