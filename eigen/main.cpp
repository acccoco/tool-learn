#include <cmath>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <iostream>


/// 将点 P(2, 1)，先绕原点旋转 45°，再平移 (1, 2)，输出结果
void transform()
{
    Eigen::Vector2f p(2.f, 1.f);
    Eigen::Vector3f homo_p(p.x(), p.y(), 1.f);
    Eigen::Matrix3f m;
    m.setIdentity();
    Eigen::Matrix2f rotate    = Eigen::Rotation2Df(45.f / 180.f * M_PI).matrix();
    m.block(0, 0, 2, 2)       = rotate;
    Eigen::Vector2f translate = Eigen::Translation2f(1.f, 2.f).vector();
    m.block(0, 2, 2, 1)       = translate;

    std::cout << "P: " << std::endl << homo_p << std::endl;
    std::cout << "transform matrix" << std::endl << m << std::endl;
    std::cout << "after transform" << std::endl << m * homo_p << std::endl;
}


/// 向量的例子
void vector_example()
{
    // Example of vector
    std::cout << "Example of vector \n";
    // vector definition
    Eigen::Vector3f v(1.0f, 2.0f, 3.0f);
    Eigen::Vector3f w(1.0f, 0.0f, 0.0f);
    // vector output
    std::cout << "Example of output \n";
    std::cout << v << std::endl;
    // vector add
    std::cout << "Example of add \n";
    std::cout << v + w << std::endl;
    // vector scalar multiply
    std::cout << "Example of scalar multiply \n";
    std::cout << v * 3.0f << std::endl;
    std::cout << 2.0f * v << std::endl;

    /* vector: cdot */
    std::cout << "cdot" << std::endl;
    std::cout << v.dot(w) << std::endl;

    /* vector: cross */
    std::cout << "cross" << std::endl;
    std::cout << v.cross(w) << std::endl;

    /* vector: expand */
    std::cout << "vector: expand" << std::endl;
    std::cout << Eigen::Vector4f(v.x(), v.y(), v.z(), 1.f) << std::endl;
}


/// 矩阵的例子
void matrix_example()
{
    // Example of matrix
    std::cout << "Example of matrix \n";
    // matrix definition
    Eigen::Matrix3f i, j;
    i << 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0;
    j << 2.0, 3.0, 1.0, 4.0, 6.0, 5.0, 9.0, 7.0, 8.0;
    // matrix output
    std::cout << "Example of output \n";
    std::cout << i << std::endl;

    /* matrix: add */
    std::cout << "matrix: add" << std::endl;
    std::cout << (i + j) << std::endl;

    /* matrix: scalar multi */
    std::cout << "matrix: scalar multi" << std::endl;
    std::cout << 3.f * i << std::endl;
    std::cout << i * 2.f << std::endl;

    /* matrix: multi */
    std::cout << "matrix: multi" << std::endl;
    std::cout << i * i << std::endl;

    /* matrix: multi vector */
    std::cout << "matrix: multi vector" << std::endl;
    Eigen::Vector3f v(1.0f, 2.0f, 3.0f);
    std::cout << i * v << std::endl;

    /* matrix: inverse */
    std::cout << "matrix: inverse" << std::endl;
    std::cout << i.inverse() << std::endl;

    /* matrix: transpose */
    std::cout << "matrix: transpose" << std::endl;
    std::cout << i.transpose() << std::endl;
}

int main()
{
    vector_example();
    matrix_example();
    transform();

    return 0;
}