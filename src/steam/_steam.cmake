add_library(steam SHARED
        "${CMAKE_CURRENT_LIST_DIR}/_steam.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Steam.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Steam.h")

target_link_libraries(steam PRIVATE sourcepp::steampp)

godotsource_configure_library(steam)
