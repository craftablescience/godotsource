add_library(vcrypt SHARED
        "${CMAKE_CURRENT_LIST_DIR}/_vcrypt.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/VFONT.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/VFONT.h"
        "${CMAKE_CURRENT_LIST_DIR}/VICE.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/VICE.h")

target_link_libraries(vcrypt PRIVATE sourcepp::vcryptpp)

godotsource_configure_library(vcrypt)
