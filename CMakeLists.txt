cmake_minimum_required(VERSION "3.18.0")

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_LIST_DIR}/cmake/Toolchains/AVRGCC.cmake")

project("camera_control"
    LANGUAGES CXX
    VERSION "0.0.1"
    DESCRIPTION "An AVR based controller for digital cameras"
)

# Plaform

add_library("platform" INTERFACE)

target_compile_features("platform" INTERFACE
    "cxx_std_20"
)

target_compile_options("platform" INTERFACE
    "-mmcu=atmega32u4"
    "-Wall"
    "-Wextra"
    "-Werror"
    "-pedantic-errors"
)

target_link_options("platform" INTERFACE
    "-mmcu=atmega32u4"
)

target_include_directories("platform" SYSTEM INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

add_library("CameraControl::Platform" ALIAS "platform")

# Firmware

add_executable("camera_control"
    "src/firmware/main.cpp"
)

target_link_libraries("camera_control"
    "CameraControl::Platform"
)

set_target_properties("camera_control" PROPERTIES
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS OFF
    INTERPROCEDURAL_OPTIMIZATION_MINSIZEREL YES
)