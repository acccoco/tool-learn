find_package(Eigen3 REQUIRED)
add_executable (eigen-test main.cpp)
target_link_libraries(eigen-test Eigen3::Eigen)