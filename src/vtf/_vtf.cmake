add_library(vtf SHARED
        "${CMAKE_CURRENT_LIST_DIR}/_vtf.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/ImageLoaderVTF.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/ImageLoaderVTF.h")

target_link_libraries(vtf PRIVATE vtfpp)

godotsource_configure_library(vtf)
