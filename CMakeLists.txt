cmake_minimum_required(VERSION 3.20)
file(STRINGS "VERSION.md" VERSION_STRING)

project(cryper
        LANGUAGES CXX
        VERSION ${VERSION_STRING})

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler flags
include(CheckCXXCompilerFlag)
if (CMAKE_CXX_COMPILER_ID MATCHES "^(Apple)?Clang$" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(COMPILER_OPTIONS "-Werror -Wall -Wextra -Wpedantic")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILER_OPTIONS}")
endif()

# Set path to CMake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Configure result directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# CMake settings
include(IncludeLibraries)

# Include project directory
include_directories(${PROJECT_SOURCE_DIR}/include)

# Entry point for sources
add_subdirectory(src)

