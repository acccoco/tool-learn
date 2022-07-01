find_package(spdlog)

set(target_name ${PRE}spdlog)

add_executable(${target_name} main.cpp)
target_link_libraries(${target_name} spdlog::spdlog)