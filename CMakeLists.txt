cmake_minimum_required(VERSION 3.26)
project(ModernCpp VERSION 0.2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wc++20-compat -fmodules-ts")
endif()

# Define the main source directory for clarity
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_executable(ModernCpp main.cpp)
target_include_directories(ModernCpp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)