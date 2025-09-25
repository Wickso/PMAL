#!/usr/bin/env bash

# Fully acknowledge this build script can probably be written better

# FLAGS
# -r, -run = build + run : project creates a test .exe
# -c, -clean = clean build
# -d, -debug = build debug mode
# -rd, -releasedebug = build release with debug info
# if 'clang++', 'g++' or any cpp and/or c compiler then they will be explicitly set
# NOTE: release is default build type. Must expicitly state otherwise


# VARS

BUILD_C='\033[0;32m'
ERROR_C='\033[0;31m'
OPT_C='\033[0;33m'
NC='\033[0m'


args=($1 $2 $3 $4 $5)

compilers_cpp=('clang++' 'g++')
compilers_c=('clang' 'gcc')
cpp_compiler=''
c_compiler=''

run=0
clean=0
debug=0
releasedebug=0


cmake_debug_str=' -DCMAKE_BUILD_TYPE=Debug'
cmake_debugRelease_str=' -DCMAKE_BUILD_TYPE=RelWithDebInfo'
cmake_release_str=' -DCMAKE_BUILD_TYPE=Release'
cmake_bdir_release=" -B build/release"
cmake_bdir_debug=" -B build/debug"
cmake_bdir_rd=" -B build/development"
cmake_dir_release=" build/release"
cmake_dir_debug=" build/debug"
cmake_dir_rd=" build/development"
cmake_generator=''
cmake_CXX_compiler=' -DCMAKE_CXX_COMPILER='
cmake_C_compiler=' -DCMAKE_C_COMPILER='

cmake_gen_cmd='cmake'
cmake_build_cmd='cmake --build'

# DETERMINE GENERATOR (Preferred, otherwise platform default)

command -v ninja >/dev/null
if [ $? -eq 0 ]; then
    cmake_generator=' -G Ninja'
    echo -e "${OPT_C}[OPT]${NC} Project generator = Ninja"
    cmake_gen_cmd+=$cmake_generator
else
    echo -e "${ERROR_C}[ERROR]${NC} Ninja is not installed on system. Compile commands for clangd may not be generated (Unix Makefiles will work). If building to extract library then disregard message. -r flag may not work"
fi




# DETERMINE COMPILERS

# TODO: Add explicit compiler control flow

for ((i = 0 ; i < ${#compilers_cpp[@]} ; ++i)); do
    command -v ${compilers_cpp[$i]} >/dev/null
    if [ $? -eq 0 ]; then
        echo -e "${OPT_C}[OPT]${NC} CPP compiler = ${compilers_cpp[$i]}"
        cmake_CXX_compiler+=${compilers_cpp[$i]}
        break
    fi
done

for ((i = 0 ; i < ${#compilers_c[@]} ; ++i)); do
    command -v ${compilers_c[$i]} >/dev/null
    if [ $? -eq 0 ]; then
        echo -e "${OPT_C}[OPT]${NC} C compiler = ${compilers_c[$i]}"
        cmake_C_compiler+=${compilers_c[$i]}
        break
    fi
done


# DETERMINE FLAGS

for ((i = 0 ; i < ${#args[@]} ; ++i)); do
    if [ ${args[i]} == '-r' ] || [ ${args[i]} == '-run' ]; then
        run=1
        continue
    fi
    if [ ${args[i]} == '-c' ] || [ ${args[i]} == '-clean' ]; then
        clean=1
        continue
    fi
    if [ ${args[i]} == '-d' ] || [ ${args[i]} == '-debug' ] && [ $releasedebug -ne 1 ]; then
        debug=1
        continue
    fi
    if [ ${args[i]} == '-rd' ] || [ ${args[i]} == '-releasedebug' ] && [ $debug -ne 1 ]; then
        releasedebug=1
        continue
    fi
done


# BUILD COMMANDS

# clean
if [ $clean -eq 1 ]; then
    echo -e "${BUILD_C}[BUILD]${NC} Cleaning build directory"
    rm -rf ./build/debug
    rm -rf ./build/release
    rm -rf ./build/development
fi

# build type
if [ $debug -eq 1 ]; then
    cmake_gen_cmd+=$cmake_bdir_debug$cmake_debug_str
    cmake_build_cmd+=$cmake_dir_debug
    echo -e "${OPT_C}[OPT]${NC} Mode = debug"
elif [ $releasedebug -eq 1 ]; then
    cmake_gen_cmd+=$cmake_bdir_rd$cmake_debugRelease_str
    cmake_build_cmd+=$cmake_dir_rd
    echo -e "${OPT_C}[OPT]${NC} Mode = Release with debug information"
else
    cmake_gen_cmd+=$cmake_bdir_release$cmake_release_str
    cmake_build_cmd+=$cmake_dir_release
fi

cmake_gen_cmd+=$cmake_CXX_compiler$cmake_C_compiler

echo -e "${BUILD_C}[BUILD]${NC} Generating project"
$cmake_gen_cmd
echo -e "${BUILD_C}[BUILD]${NC} Building project"
$cmake_build_cmd

# NOTE: Important... Ensures compile_commands.json is always in project directory for clangd to see
if [ $debug -eq 1 ]; then
    cp ./build/debug/compile_commands.json .
elif [ $releasedebug -eq 1 ]; then
    cp ./build/development/compile_commands.json .
else
    cp ./build/release/compile_commands.json .
fi



if [ $run -eq 1 ]; then
    echo -e "${BUILD_C}[BUILD]${NC} Running application..."
    if [ $debug -eq 1 ]; then
        ./build/debug/test_app.exe
    elif [ $releasedebug -eq 1 ]; then
        ./build/development/test_app.exe
    else
        ./build/release/test_app.exe
    fi
fi



    



