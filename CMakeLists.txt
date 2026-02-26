cmake_minimum_required(VERSION 3.10)
project(JumpGame LANGUAGES CXX)

set(CMAKE_CXX_STANDART 20)
set(CMAKE_CXX_STANDART_REQUIRED ON)

file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS
    src/*.cpp
    src/*.h
)

add_subdirectory(vendor/SDL3)

add_executable(JumpGame ${APP_SOURCES})

target_include_directories(JumpGame PRIVATE src)

target_link_libraries(JumpGame PRIVATE SDL3::SDL3)