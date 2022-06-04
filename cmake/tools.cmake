

# 查找当前文件夹下的所有子文件夹，将其添加为「子模块」
function(add_sub_dirs)

    # 设置 PRE 的变量
    get_filename_component(dir_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    set(PRE ${PRE}${dir_name}.)

    # 添加子文件夹到 build 中
    file(GLOB sub_dir_list RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)
    foreach (sub_dir ${sub_dir_list})
        if (NOT IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${sub_dir})
            continue()
        endif ()
        add_subdirectory(${sub_dir})
    endforeach ()
endfunction()