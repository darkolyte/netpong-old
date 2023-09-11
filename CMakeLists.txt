# Set Minimum CMake Version
cmake_minimum_required (VERSION 3.24)

# Set C++ Standard, do not use GNU extensions
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set Project Name and Version
set(PROJECT_NAME NetPong)
set(PROJECT_VERSION 0.2.0)

# Setting flags for debug and release builds
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

# Setup Project
project(${PROJECT_NAME} VERSION ${PROJECT_VERSION} LANGUAGES CXX)

# Add include directory
include_directories(inc)

# Add Subdirectories
add_subdirectory(lib)
add_subdirectory(src)