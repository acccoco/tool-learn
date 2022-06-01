//
// Created by 漆正杰 on 2021/5/23.
//

#include "./BVH.hpp"


void BVH2::draw_interaction_box(cv::Mat &canvas, const BVH2 &node, const cv::Vec2f &orig, const cv::Vec2f &dir) {
    assert(dir[0] != 0.f || dir[1] != 0.f);

    /* 射线是否和当前包围盒相交 */
    if (!Rectangle::is_intersection(*node.bounding_box, orig, dir)) return;

    /* 已经是最内层包围盒 */
    if (!node.l_child || !node.r_child) {
        cv::rectangle(canvas,
                      cv::Point2f(node.bounding_box->min_x, node.bounding_box->min_y),
                      cv::Point2f(node.bounding_box->max_x, node.bounding_box->max_y),
                      node.box_color);
    }
    else {  // 当前节点不是最内层，应该绘制子节点
        draw_interaction_box(canvas, *node.l_child, orig, dir);
        draw_interaction_box(canvas, *node.r_child, orig, dir);
    }
}


BVH2::Ptr BVH2::build(const std::vector<Triangle::ptr> &triangles)  {
    assert(!triangles.empty());

    auto box = Triangle::boundary_box_gen(triangles);

    /* 当前节点只有一个三角形，当前节点是叶子节点 */
    if (triangles.size() == 1) {
        return std::shared_ptr<BVH2>(
                new BVH2{triangles, nullptr, nullptr, box, random_color_get()});
    }

    /* 按最长方向切分三角形，一定可以切分出两个非空组 */
    Axial axial = (box->max_x - box->min_x >= box->max_y - box->min_y)
                  ? Axial::X
                  : Axial::Y;
    auto[less, greater] = split_tris(triangles, axial);

    /* 构建子节点 */
    auto l = build(less);
    auto r = build(greater);
    return std::shared_ptr<BVH2>(
            new BVH2{{}, l, r, box, random_color_get()});
}


