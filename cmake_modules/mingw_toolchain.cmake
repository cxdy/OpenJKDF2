set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_PROCESSOR x86_64)
set(TOOLCHAIN_PREFIX x86_64-w64-mingw32)

set(CMAKE_C_COMPILER   "${TOOLCHAIN_PREFIX}-gcc" CACHE STRING "C compiler" FORCE)
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_PREFIX}-g++" CACHE STRING "C++ compiler" FORCE)
set(CMAKE_RC_COMPILER  "${TOOLCHAIN_PREFIX}-windres" CACHE STRING "rc compiler" FORCE)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(WIN32 TRUE)
set(MINGW TRUE)
set(PLAT_MINGW_X86_64 TRUE CACHE BOOL "MinGW Win64 target")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")

set(OPENAL_LIBRARY "${PROJECT_SOURCE_DIR}/3rdparty/openal-soft/bin/Win64/soft_oal.dll")
set(OPENAL_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/3rdparty/openal-soft/include/AL")

#set(SDL2_LIBRARIES "${PROJECT_SOURCE_DIR}/3rdparty/SDL2/x86_64-w64-mingw32/lib/libSDL2.la ${PROJECT_SOURCE_DIR}/3rdparty/SDL2/x86_64-w64-mingw32/lib/libSDL2main.la")
#set(SDL2_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/3rdparty/SDL2/x86_64-w64-mingw32/include")

#set(SDL2_DIR "${CMAKE_SOURCE_DIR}/3rdparty/SDL2/x86_64-w64-mingw32/lib/cmake/SDL2")
#find_package(SDL2 REQUIRED)

message( STATUS "MinGW cross-compile toolchain invoked" )
