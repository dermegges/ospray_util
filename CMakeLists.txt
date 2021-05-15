cmake_minimum_required(VERSION 3.5.1)
project(ospray_util)
set(CMAKE_CXX_STANDARD 11)

option(BUILD_SHARED_LIBS "Build shared libraries." ON)

add_subdirectory(src)
