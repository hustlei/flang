#指定最新版本
cmake_minimum_required(VERSION 3.16)

#设置项目名称
project(flang VERSION 0.0.0.1)

#设置普通变量，缓存变量或环境变量
set(CMAKE_C_COMPILER "clang")    #指定编译器
set(CMAKE_CXX_COMPILER "clang++")    #指定编译器
set(CMAKE_CXX_STANDARD 14)    #指定C++标准库版本
set(CMAKE_CXX_STANDARD_REQUIRED ON)    #True也可以，设置指定的C++版本是必须的

#显示基本信息

message(STATUS "Project_dir:${CMAKE_SOURCE_DIR}")
message(STATUS "Binary_dir: ${CMAKE_BINARY_DIR}")

message(STATUS "ZLIB_INC:${ZLIB_INCLUDE_DIR}")
#find_package(ZLIB REQUIRED)
#may be a bug, find_package doesn't work
set(ZLIB_LIBRARY "/usr/lib/x86_64-linux-gnu/libz.a") #or libz.so

#llvm设置
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
message(STATUS  "Using LLVM INCLUDE DIRS:${LLVM_INCLUDE_DIRS}")
# 设置编译选项
include_directories(${LLVM_INCLUDE_DIRS})    #c++头文件
#separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
#add_definitions(${LLVM_DEFINITIONS_LIST})    #-D 编译选项定义
add_definitions(${LLVM_DEFINITIONS})

#编译

##flex bison编译
add_subdirectory(Lex)
add_subdirectory(Parse)

##设置源文件和编译目标
include_directories(AST Lex Parse IRGen Base)
aux_source_directory(Lex lex)
aux_source_directory(Parse parse)
aux_source_directory(IRGen irgen)
aux_source_directory(Base base)
set(SOURCE ${lex} ${parse} ${irgen} ${base})
add_executable(compiler compiler.cpp ${SOURCE})

#链接设置
#llvm_libs变量设置为 LLVMAnalysis;LLVMCore;LLVMSupport 形式
llvm_map_components_to_libnames(llvm_libs
	Analysis
	irreader
	InstCombine
	Core
	ExecutionEngine
	Object
	OrcJIT
	Support
	native
	ExecutionEngine
	OrcJIT
	RuntimeDyld
	ScalarOpts
	TransformUtils
	)



# Link against LLVM libraries
target_link_libraries(compiler ${llvm_libs} reflex)
#target_link_libraries(compiler LLVM-10 reflex)
