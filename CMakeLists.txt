cmake_minimum_required(VERSION 3.0)

project(count_primes)

set (source_dir "${PROJECT_SOURCE_DIR}/src/")
file(GLOB source_files "${source_dir}/*.cpp")

add_executable(count_primes ${source_files})
