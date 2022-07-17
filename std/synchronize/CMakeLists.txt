set(PRE ${PRE}sync.)


file(GLOB source_list RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
foreach (source ${source_list})
    # 获取文件名，不要 directory，不要最后的扩展名
    get_filename_component(name ${source} NAME_WLE)
    add_executable(${PRE}${name} ${source})
endforeach ()
