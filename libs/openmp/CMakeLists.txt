find_package(OpenMP)
if (NOT ${OpenMP_CXX_FOUND})
    message(FATAL_ERROR "can not fidn OpenMP")
endif ()

add_executable(${PRE}openmp main.cpp)
target_link_libraries(${PRE}openmp OpenMP::OpenMP_CXX)