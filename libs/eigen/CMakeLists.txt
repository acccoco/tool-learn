find_package(Eigen3 REQUIRED)


add_executable (${PRE}eigen-test main.cpp)
target_link_libraries(${PRE}eigen-test Eigen3::Eigen)