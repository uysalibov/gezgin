# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.20)

# Set the project name
project(gezgin)

# Set build type to Debug
set(CMAKE_BUILD_TYPE Debug)

# Set the project directory
set(PROJECT_DIR ${CMAKE_SOURCE_DIR})

# Include FetchContent module for downloading dependencies
include(FetchContent)

# Define the version of Raylib to use
set(RAYLIB_VERSION 5.0)

# Declare Raylib as a dependency and specify its download URL
FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    FIND_PACKAGE_ARGS ${RAYLIB_VERSION}
)

# Set build examples option to off
set(BUILD_EXAMPLES OFF CACHE INTERNAL "")

# Make Raylib available for the project
FetchContent_MakeAvailable(raylib)

# Include the Renderer subdirectory for building
add_subdirectory(Renderer)

# Define project sources
set(PROJECT_SOURCES main.cpp)

# Create an executable with the specified sources
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# Link the executable with Renderer and Raylib libraries
target_link_libraries(${PROJECT_NAME} Renderer raylib)

# Additional settings for macOS
if (APPLE)
    # Link necessary frameworks for macOS
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
