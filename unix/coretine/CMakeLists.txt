if (NOT LINUX)
    message(STATUS "corotinue program can only run on linux.")
    return()
endif ()

add_executable(corotine main.cpp)
target_link_libraries(corotine)