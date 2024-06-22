add_library(vice SHARED
        "${CMAKE_CURRENT_LIST_DIR}/_vice.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/VICE.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/VICE.h")

target_link_libraries(vice PRIVATE vicepp)

godotsource_configure_library(vice)
