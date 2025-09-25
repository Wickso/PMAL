cmake_minimum_required(VERSION 3.30)
project(PMAL)

# SETTINGS
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

set(SRC "src/main.cpp")

add_executable(test_app.exe ${SRC})
