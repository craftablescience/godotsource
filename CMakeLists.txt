cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

# Create project
if (APPLE)
    set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE STRING "" FORCE)
endif()
project(godotsource)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include CMake libraries
include(CheckIPOSupported)

# Set up variables
set(GODOTSOURCE_ARCH ${CMAKE_SYSTEM_PROCESSOR})
if (APPLE)
    set(GODOTSOURCE_ARCH "universal")
endif()
set(GODOTSOURCE_OUT_DIR "${CMAKE_SYSTEM_NAME}_${GODOTSOURCE_ARCH}")

# Global CMake options
if(NOT PROJECT_IS_TOP_LEVEL)
    message(FATAL_ERROR "${PROJECT_NAME} must be built standalone!")
endif()

# Print a message
message(STATUS "Building ${PROJECT_NAME} for ${GODOTSOURCE_ARCH} on ${CMAKE_SYSTEM_NAME}")

# Set proper runpath
set(CMAKE_SKIP_BUILD_RPATH OFF)
set(CMAKE_BUILD_RPATH_USE_ORIGIN ON)
set(CMAKE_INSTALL_RPATH $ORIGIN)

# Compile with PIC
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Compile with LTO if supported
set(GODOTSOURCE_USE_LTO OFF)
if(NOT (CMAKE_BUILD_TYPE MATCHES "Debug"))
    check_ipo_supported(RESULT GODOTSOURCE_USE_LTO)
endif()
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ${GODOTSOURCE_USE_LTO})

# Hide everything by default
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

# godot-cpp
set(GODOT_CPP_SYSTEM_HEADERS ON CACHE BOOL "" FORCE)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/ext/godot-cpp")

# sourcepp
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/ext/sourcepp")

add_custom_target(${PROJECT_NAME})

# Macro to set up many things at once for a given GDExtension
function(godotsource_configure_library TARGET)
    # Define DEBUG macro
    target_compile_definitions(${TARGET} PRIVATE "$<$<CONFIG:Debug>:DEBUG>")

    # Set optimization flags
    if(CMAKE_BUILD_TYPE MATCHES "Debug")
        # Build with debug friendly optimizations and debug symbols (MSVC defaults are fine)
        if(UNIX OR MINGW)
            target_compile_options(${TARGET} PRIVATE -Og -g)
        endif()
        if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND NOT MSVC)
            target_compile_options(${TARGET} PRIVATE -fno-limit-debug-info)
        endif()
    else()
        # Build with optimizations and don't omit stack pointer for debugging (MSVC defaults are fine)
        if(UNIX OR MINGW)
            target_compile_options(${TARGET} PRIVATE -O2 -fno-omit-frame-pointer)
        endif()
    endif()

    # Set output directory
    set(${TARGET}_OUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/demo/lib/${TARGET}/${GODOTSOURCE_OUT_DIR}")
    set_target_properties(${TARGET} PROPERTIES
            LIBRARY_OUTPUT_DIRECTORY ${${TARGET}_OUT_DIR}
            RUNTIME_OUTPUT_DIRECTORY ${${TARGET}_OUT_DIR})
    message(STATUS "${TARGET} output directory is set to \"${${TARGET}_OUT_DIR}\"")

    # Remove lib prefix on MinGW
    if(MINGW)
        set_target_properties(${TARGET} PROPERTIES PREFIX "")
    endif()

    # Set debug postfix
    if(NOT DEFINED CMAKE_DEBUG_POSTFIX)
        set_target_properties(${TARGET} PROPERTIES DEBUG_POSTFIX "d")
    endif()

    # Copy template files
    if(NOT ((CMAKE_BUILD_TYPE MATCHES "Debug") OR (CMAKE_BUILD_TYPE MATCHES "Release")))
        message(FATAL_ERROR "Build type must be Debug or Release!")
    endif()
    add_custom_target(${TARGET}_gdextension SOURCES
            "${CMAKE_CURRENT_SOURCE_DIR}/res/gdextension/Debug.gdextension.in"
            "${CMAKE_CURRENT_SOURCE_DIR}/res/gdextension/Release.gdextension.in")
    add_dependencies(${TARGET} ${TARGET}_gdextension)
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/res/gdextension/${CMAKE_BUILD_TYPE}.gdextension.in" "${${TARGET}_OUT_DIR}/../${TARGET}.gdextension")

    # Link to godot-cpp
    target_link_libraries(${TARGET} PRIVATE godot-cpp)

    # Add to project target
    add_dependencies(${PROJECT_NAME} ${TARGET})
endfunction()

# kvpp_gd
if(SOURCEPP_USE_KVPP)
    include("${CMAKE_CURRENT_SOURCE_DIR}/src/kvpp/_kvpp.cmake")
endif()