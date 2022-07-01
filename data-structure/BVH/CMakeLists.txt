find_package(OpenCV REQUIRED)
message(DEBUG "OpenCV libs: ${OpenCV_LIBS}")
message(DEBUG "OpenCV include: ${OpenCV_INCLUDE_DIRS}")

add_executable(${PRE}BVH main.cpp geometry.cpp utils.cpp BVH.cpp)

target_link_libraries(${PRE}BVH PRIVATE ${OpenCV_LIBS})
