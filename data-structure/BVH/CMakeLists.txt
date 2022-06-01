find_package(OpenCV REQUIRED)
message(STATUS "OopenCV libs: ${OpenCV_LIBS}")
message(STATUS "OopenCV include: ${OpenCV_INCLUDE_DIRS}")

add_executable(BVH main.cpp geometry.cpp utils.cpp BVH.cpp)

target_link_libraries(BVH PRIVATE ${OpenCV_LIBS})
