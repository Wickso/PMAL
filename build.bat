echo off
setlocal enabledelayedexpansion

REM =========================
REM Flags
REM =========================
set run=0
set clean=0
set debug=0
set releasedebug=0

REM Collect args
for %%A in (%*) do (
    if "%%A"=="-r" set run=1
    if "%%A"=="-run" set run=1
    if "%%A"=="-c" set clean=1
    if "%%A"=="-clean" set clean=1
    if "%%A"=="-d" if !releasedebug! NEQ 1 set debug=1
    if "%%A"=="-debug" if !releasedebug! NEQ 1 set debug=1
    if "%%A"=="-rd" if !debug! NEQ 1 set releasedebug=1
    if "%%A"=="-releasedebug" if !debug! NEQ 1 set releasedebug=1
)

REM =========================
REM Clean build dirs
REM =========================
if %clean%==1 (
    echo [BUILD] Cleaning build directories...
    rmdir /s /q build\debug 2>nul
    rmdir /s /q build\release 2>nul
    rmdir /s /q build\development 2>nul
)

REM =========================
REM Compiler detection
REM =========================
set cmake_gen_cmd=cmake
set cmake_build_cmd=cmake --build
set cmake_generator=
set cmake_CXX_compiler=
set cmake_C_compiler=

where ninja >nul 2>nul
if %errorlevel%==0 (
    echo [OPT] Project generator = Ninja
    set cmake_generator=-G Ninja
) else (
    echo [ERROR] Ninja not found. Using platform default.
)

REM Try C++ compiler
for %%C in (clang++ cl) do (
    where %%C >nul 2>nul
    if !errorlevel! == 0 (
        echo [OPT] CPP compiler = %%C
        set cmake_CXX_compiler=-DCMAKE_CXX_COMPILER=%%C
        goto :found_cpp
    )
)
:found_cpp

REM Try C compiler
for %%C in (clang cl) do (
    where %%C >nul 2>nul
    if !errorlevel! == 0 (
        echo [OPT] C compiler = %%C
        set cmake_C_compiler=-DCMAKE_C_COMPILER=%%C
        goto :found_c
    )
)
:found_c

REM =========================
REM Build type
REM =========================
if %debug%==1 (
    echo [OPT] Mode = Debug
    set cmake_gen_cmd=%cmake_gen_cmd% -B build/debug -DCMAKE_BUILD_TYPE=Debug
    set cmake_build_cmd=%cmake_build_cmd% build/debug
) else if %releasedebug%==1 (
    echo [OPT] Mode = Release with debug info
    set cmake_gen_cmd=%cmake_gen_cmd% -B build/development -DCMAKE_BUILD_TYPE=RelWithDebInfo
    set cmake_build_cmd=%cmake_build_cmd% build/development
) else (
    echo [OPT] Mode = Release
    set cmake_gen_cmd=%cmake_gen_cmd% -B build/release -DCMAKE_BUILD_TYPE=Release
    set cmake_build_cmd=%cmake_build_cmd% build/release
)

set cmake_gen_cmd=%cmake_gen_cmd% %cmake_generator% %cmake_CXX_compiler% %cmake_C_compiler%

REM =========================
REM Run CMake
REM =========================
echo [BUILD] Generating project...
%cmake_gen_cmd%
if %errorlevel% neq 0 exit /b %errorlevel%

echo [BUILD] Building project...
%cmake_build_cmd%
if %errorlevel% neq 0 exit /b %errorlevel%

REM =========================
REM Copy compile_commands.json
REM =========================
if %debug%==1 (
    copy /Y build\debug\compile_commands.json . >nul
) else if %releasedebug%==1 (
    copy /Y build\development\compile_commands.json . >nul
) else (
    copy /Y build\release\compile_commands.json . >nul
)

REM =========================
REM Run app if requested
REM =========================
if %run%==1 (
    echo [BUILD] Running application...
    if %debug%==1 (
        build\debug\test_app.exe
    ) else if %releasedebug%==1 (
        build\development\test_app.exe
    ) else (
        build\release\test_app.exe
    )
)

endlocal
exit /b 0
