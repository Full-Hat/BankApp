cmake_minimum_required(VERSION 3.26)

set(CMAKE_TOOLCHAIN_FILE ./vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")

project(BankApp)

set(CMAKE_CXX_STANDARD 20)

add_executable(BankApp main.cpp)
