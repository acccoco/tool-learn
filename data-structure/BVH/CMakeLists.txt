find_package(OpenCV REQUIRED)
message(STATUS "OopenCV libs: ${OpenCV_LIBS}")
message(STATUS "OopenCV include: ${OpenCV_INCLUDE_DIRS}")

add_executable(${PRE}BVH main.cpp geometry.cpp utils.cpp BVH.cpp)

target_link_libraries(${PRE}BVH PRIVATE ${OpenCV_LIBS})
