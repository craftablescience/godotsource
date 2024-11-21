add_library(kv SHARED
        "${CMAKE_CURRENT_LIST_DIR}/_kv.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/KeyValues.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/KeyValues.h")

target_link_libraries(kv PRIVATE sourcepp::kvpp)

godotsource_configure_library(kv)
