//
// Created by 漆正杰 on 2021/5/22.
//

#ifndef BVH_BVH_HPP
#define BVH_BVH_HPP

#include <random>
#include <memory>
#include "./utils.hpp"
#include "./geometry.hpp"

/**
 * 只有叶子节点会存放三角形，且只存放一个三角形
 */
class BVH2 {
public:
    typedef std::shared_ptr<BVH2> Ptr;

    /**
     * 根据一组三角形来构建一棵 BVH
     * @note 确保三角形的数量不为 0
     */
    static Ptr build(const std::vector<Triangle::ptr> &triangles);

    /**
     * 绘制和射线相交的最内层包围盒
     * @note 确保方向是合法的
     */
    static void draw_interaction_box(cv::Mat &canvas, const BVH2 &node, const cv::Vec2f &orig, const cv::Vec2f &dir);

public:
    [[maybe_unused]] std::vector<Triangle::ptr> triangls;
    Ptr l_child, r_child;
    std::shared_ptr<Rectangle> bounding_box;
    cv::Vec3f box_color;
};


#endif //BVH_BVH_HPP
