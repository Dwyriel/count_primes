cmake_minimum_required(VERSION 3.0)

project(count_primes)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set (source_dir "src/")
file(GLOB source_files "${source_dir}/*.cpp" Stopwatch/stopwatch.cpp)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(BUILD_FOR_WIN TRUE)
endif()
option(STATIC_BUILD "Build a static binary." ${BUILD_FOR_WIN})

if (STATIC_BUILD)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a" CONFIG)
    set(BUILD_SHARED_LIBS OFF)
endif()

add_executable(count_primes ${source_files})
