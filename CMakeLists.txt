cmake_minimum_required(VERSION 3.0)
project(zthread)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(STACK_SIZE 1024)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    add_compile_options(-O3 -flto=4 -march=native -pipe -mtune=native -falign-functions -falign-jumps -falign-loops -ftree-loop-optimize -ftree-vectorize -fuse-linker-plugin -fstrict-aliasing -freorder-blocks -finline-functions)
endif()

if (WIN32)
    target_link_options(MyExecutable PRIVATE -Wl,--stack,${STACK_SIZE})
elseif(UNIX AND NOT APPLE)
    target_link_options(MyExecutable PRIVATE -Wl,-z,stack-size=${STACK_SIZE})
endif()

set(SOURCE_FILES src/main.cpp)

add_executable(zt ${SOURCE_FILES})

install(TARGETS zt DESTINATION /usr/bin)
