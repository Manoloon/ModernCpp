cmake_minimum_required(VERSION 3.0)
project(ModernCpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(ModernCpp main.cpp main.cpp src/BasicThreads.h src/TimedMutex.h src/BasicModernCpp.h src/uniqueLock.h)
