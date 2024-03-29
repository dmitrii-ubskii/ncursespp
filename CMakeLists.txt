cmake_minimum_required(VERSION 3.16)

### Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

project(libncursespp VERSION 0.0.0
    DESCRIPTION "C++ wrapper for ncurses"
    LANGUAGES CXX)

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
endif()

add_library(ncursespp STATIC
    src/ncurses.cpp
    src/window.cpp
)

target_compile_features(ncursespp PRIVATE cxx_std_20)

find_package(Curses REQUIRED)

target_include_directories(ncursespp
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/extern/deeyou/include>
        $<INSTALL_INTERFACE:include>
        ${CURSES_INCLUDE_DIRS}
)

