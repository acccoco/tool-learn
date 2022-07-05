//
// Created by 漆正杰 on 2021/5/22.
//
#include <vector>
#include "./geometry.hpp"


float min3(float a, float b, float c) {
    return std::min(a, std::min(b, c));
}

float max3(float a, float b, float c) {
    return std::max(a, std::max(b, c));
}

Triangle::Triangle(const cv::Vec2f &a, const cv::Vec2f &b, const cv::Vec2f &c)
        : A(a), B(b), C(c), center(1.f / 3.f * (a + b + c)) {
    boundary.min_x = min3(a[0], b[0], c[0]);
    boundary.min_y = min3(a[1], b[1], c[1]);
    boundary.max_x = max3(a[0], b[0], c[0]);
    boundary.max_y = max3(a[1], b[1], c[1]);
}

std::shared_ptr<Rectangle> Triangle::boundary_box_gen(const std::vector<Triangle::ptr> &triangles) {
    assert(!triangles.empty());
    auto box = std::shared_ptr<Rectangle>(new Rectangle{FLT_MAX, FLT_MAX, 0.f, 0.f});
    for (const auto &triangle: triangles) {
        box->min_x = std::min(box->min_x, triangle->boundary.min_x);
        box->min_y = std::min(box->min_y, triangle->boundary.min_y);
        box->max_x = std::max(box->max_x, triangle->boundary.max_x);
        box->max_y = std::max(box->max_y, triangle->boundary.max_y);
    }
    return box;
}

void Triangle::draw(cv::Mat &canvas, const cv::Vec3f &color) const {
    cv::line(canvas, (cv::Point2f) A, (cv::Point2f) B, color);
    cv::line(canvas, (cv::Point2f) B, (cv::Point2f) C, color);
    cv::line(canvas, (cv::Point2f) C, (cv::Point2f) A, color);
}


Triangle::ptr Triangle::triangle_gen(const Rectangle &canvas, float min_size, float max_size) {
    float width = canvas.max_x - canvas.min_x;
    float height = canvas.max_y - canvas.min_y;

    // 参考的中心
    float center_x = canvas.min_x + width * random_float_get();
    float center_y = canvas.min_y + height * random_float_get();

    // 三角形的大小：最大为 min_size 倍的宽度，最小为 max_size 倍宽度
    float tri_size = std::min(width, height) * (random_float_get() * (max_size - min_size) + min_size);

    // 生成三个顶点
    std::array<cv::Vec2f, 3> points;
    for (auto &point: points) {
        point[0] = center_x + tri_size * (random_float_get() - .5f);
        point[1] = center_y + tri_size * (random_float_get() - .5f);
    }

    return std::make_shared<Triangle>(points[0], points[1], points[2]);
}


/**
 * 找到按序排列时，序号为 k 的三角形
 * @note 确保三角形个数大于 0，且 k 是有效的
 * @return 比第 k 个三角形小的三角形序列，第 k 个三角形，比第 k 个三角形大的序列，不保证有序
 */
std::tuple<std::vector<Triangle::ptr>, Triangle::ptr, std::vector<Triangle::ptr>>
split_tris_(const std::vector<Triangle::ptr> &triangles, Axial axial, size_t k) {
    assert(!triangles.empty() && k < triangles.size());

    /* 只有 1 个三角形的情况 */
    if (triangles.size() == 1) {
        return {{}, triangles[0], {}};
    }

    /* 按照标志三角形来切分三角形序列 */
    auto flag_triangle = triangles[0];      // 选择第一个三角形作为标记
    std::vector<std::shared_ptr<Triangle>> less, greater;
    for (size_t i = 1; i < triangles.size(); ++i) {
        auto triangle = triangles[i];
        bool is_less = (axial == Axial::X)
                       ? (triangle->center[0] <= flag_triangle->center[0])
                       : (triangle->center[1] <= flag_triangle->center[1]);
        if (is_less) less.push_back(triangle);
        else greater.push_back(triangle);
    }

    /* 递归地查找下去 */
    if (less.size() == k) {
        // [less], falg_triangle, [greater]
        return {less, flag_triangle, greater};
    } else if (less.size() > k) {
        // [less_less], less_flag, [less_greater], flag_triangle, [greater]
        auto[less_less, less_flag, less_greater] = split_tris_(less, axial, k);
        less_greater.push_back(flag_triangle);
        less_greater.insert(less_greater.end(), greater.begin(), greater.end());
        return {less_less, less_flag, less_greater};
    } else {
        // [less], flag_triangle, [greater_less], greater_flag, [greater_greater]
        auto[greater_less, greater_flag, greater_greater] = split_tris_(greater, axial, k - less.size() - 1);
        less.push_back(flag_triangle);
        less.insert(less.end(), greater_less.begin(), greater_less.end());
        return {less, greater_flag, greater_greater};
    }
}


std::array<std::vector<Triangle::ptr>, 2>
split_tris(const std::vector<Triangle::ptr> &triangles, Axial axial) {
    assert(triangles.size() > 1);

    auto[less, flag, greater] = split_tris_(triangles, axial, (triangles.size() - 1) / 2);
    less.push_back(flag);
    return {less, greater};
}


bool Rectangle::is_intersection(const Rectangle &box, const cv::Vec2f &orig, const cv::Vec2f &dir) {
    // 不支持和坐标轴垂直的方向
    if (dir[0] == 0 || dir[1] == 0) return false;

    float t_x_min = (box.min_x - orig[0]) / dir[0];
    float t_x_max = (box.max_x - orig[0]) / dir[0];
    if (t_x_min > t_x_max) std::swap(t_x_min, t_x_max);
    float t_y_min = (box.min_y - orig[1]) / dir[1];
    float t_y_max = (box.max_y - orig[1]) / dir[1];
    if (t_y_min > t_y_max) std::swap(t_y_min, t_y_max);

    float t_min = std::max(t_x_min, t_y_min);
    float t_max = std::min(t_x_max, t_y_max);

    return t_min < t_max;
}
