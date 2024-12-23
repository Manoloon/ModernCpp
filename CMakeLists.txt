cmake_minimum_required(VERSION 3.20)
project(ModernCpp VERSION 0.2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wc++20-compat")

# if(CMAKE_BUILD_TYPE STREQUAL "Debug")
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=signed-integer-overflow")
# endif()

# Define the main source directory for clarity
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
add_executable(ModernCpp main.cpp ${SOURCE_DIR})
