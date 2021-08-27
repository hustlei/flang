#指定最新版本
cmake_minimum_required(VERSION 3.16)

#设置项目名称
project(flang VERSION 0.0.0.1)

#设置普通变量，缓存变量或环境变量
set(CMAKE_C_COMPILER "clang")    #指定编译器
set(CMAKE_CXX_COMPILER "clang++")    #指定编译器
set(CMAKE_CXX_STANDARD 14)    #指定为C++11版本
set(CMAKE_CXX_STANDARD_REQUIRED ON)    #True也可以，设置指定的C++版本是必须的

#显示基本信息
message(STATUS "Project_DIR:${CMAKE_SOURCE_DIR)")
message(STATUS "Binary_DIR: ${CMAKE_BINARY_DIR)")

add_subdirectory(src)