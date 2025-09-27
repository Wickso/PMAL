cmake_minimum_required(VERSION 3.30)
project(PMAL)

# SETTINGS
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)


# SOURCES

set(SRC_LIB
    "./src/PMAL/memory_manager.cpp"
)
set(SRC_EXE 
    "src/main.cpp"
)

# TARGETS AND INLCUDE DIRS

# TODO: Add control flow for platforms if needed
add_library(PMAL STATIC ${SRC_LIB})
add_executable(test_app.exe ${SRC_EXE})


target_include_directories(PMAL
    PUBLIC 
    "src/"
    "src/allocators"
    "src/PMAL"
)

# LINKING

target_link_libraries(test_app.exe
    PUBLIC PMAL
)
