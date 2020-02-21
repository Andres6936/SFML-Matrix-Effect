cmake_minimum_required(VERSION 3.0)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose debug or release" FORCE)
endif()

set(CMAKE_CXX_STANDARD 17)

project(sfml-matrix)

## Set Module Path
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

## Get the files
file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(Matrix ${SOURCES})

## Add and link libraries
find_package(SFML 2.5.1 REQUIRED graphics system)
target_link_libraries(Matrix sfml-graphics)

## Copy resources
file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ${CMAKE_BINARY_DIR})