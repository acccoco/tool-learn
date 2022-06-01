
/**
 * BVH 的学习
 * 功能1：绘制BVH所有的包围盒
 * 功能2：发出射线，利用BVH计算相交的三角形
 */


#include <tuple>
#include <random>
#include <opencv2/opencv.hpp>

#include "./BVH.hpp"


/* 当前按下的按键 */
int g_cur_key;

/* 射线的原点和方向 */
std::vector<cv::Point2f> g_points;

/* 鼠标事件：获得点击的位置 */
void mouse_handler(int event, int x, int y, int, void *) {
    if (event != cv::EVENT_LBUTTONDOWN) return;
    if (g_points.size() >= 2) g_points.clear();
    g_points.emplace_back(x, y);
}


int main() {
    /* window */
    std::string window_name = "canvas";
    cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);

    /* mouse callback */
    cv::setMouseCallback(window_name, mouse_handler, nullptr);

    /* framebuffer */
    int width = 800, height = 600;
    cv::Mat framebuffer = cv::Mat(height, width, CV_8UC3, cv::Scalar(0));
    cv::cvtColor(framebuffer, framebuffer, cv::COLOR_BGR2RGB);

    /* 生成很多的三角形 */
    std::vector<Triangle::ptr> triangles(50);
    auto canvas = Rectangle{20, 20, 600, 600};
    for (auto & triangle : triangles) {
        triangle = Triangle::triangle_gen(canvas, 0.1f, 0.3f);
    }

    /* 构建 BVH */
    auto root = BVH2::build(triangles);

    while (g_cur_key != K_ESC) {
        /* keyboard */
        g_cur_key = cv::waitKey(10);

        /* 清空画布 */
        cv::rectangle(framebuffer, cv::Point2f(0, 0), cv::Point2i(width, height), cv::Vec3f(0, 0, 0), -1);

        /* 先绘制所有的三角形 */
        for (const auto &tri: triangles) {
            tri->draw(framebuffer, COLOR_GRAY);
        }

        /* 绘制表示射线的直线 */
        for (const auto &p : g_points) {
            cv::circle(framebuffer, p, 2, COLOR_GRAY, 1);
        }
        if (g_points.size() == 2) {
            /* 判断交点，绘制包围盒 */
            auto dir = g_points[1] - g_points[0];
            if (dir.x != 0.f && dir.y != 0.f) {
                cv::line(framebuffer, g_points[0] + 1000 * dir, g_points[0] - 1000 * dir, COLOR_RED, 2);
                BVH2::draw_interaction_box(framebuffer, *root, g_points[0], dir);
            }
        }

        /* show image */
        cv::imshow(window_name, framebuffer);
    }
}
