if (NOT LINUX)
    message(WARNING "[warning] corotinue program can only run on linux.")
    return()
endif ()

add_executable(corotine main.cpp)
target_link_libraries(corotine)