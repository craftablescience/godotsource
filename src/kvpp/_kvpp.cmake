add_library(kvpp_gd SHARED
        "${CMAKE_CURRENT_LIST_DIR}/_kvpp.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/KeyValues.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/KeyValues.h")

target_link_libraries(kvpp_gd PRIVATE kvpp)

godotsource_configure_library(kvpp_gd)
