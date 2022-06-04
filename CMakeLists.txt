cmake_minimum_required(VERSION 3.19)
project(tool-learn)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(cmake/tools.cmake)


# 找到所有的子文件夹，加入到 build 中
file(GLOB sub_dir_list RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)
list(FILTER sub_dir_list EXCLUDE REGEX cmake-build-debug)
list(FILTER sub_dir_list EXCLUDE REGEX cmake)
list(FILTER sub_dir_list EXCLUDE REGEX build)
list(FILTER sub_dir_list EXCLUDE REGEX .vscode)
list(FILTER sub_dir_list EXCLUDE REGEX .idea)
list(FILTER sub_dir_list EXCLUDE REGEX .git)
foreach (sub_dir ${sub_dir_list})
    # 排除文件夹
    if (NOT IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${sub_dir})
        continue()
    endif ()
    add_subdirectory(${sub_dir})
endforeach ()
