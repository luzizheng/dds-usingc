
cmake_minimum_required(VERSION 3.15)


# 编译架构：x86 arm64
set(ARCHITECTURE x86)


if(${ARCHITECTURE} STREQUAL "arm64")
message(STATUS "this is arm64 compiler")
# 交叉编译arm64
set(CMAKE_CXX_COMPILER /opt/gnu-arch64/bin/aarch64-linux-gnu-g++)
set(CMAKE_C_COMPILER /opt/gnu-arch64/bin/aarch64-linux-gnu-gcc)
# 告诉cmake是进行交叉编译
set(CMAKE_CROSSCOMPILING TRUE) 
else()
message(STATUS "this is x86_64 compiler")
set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_CROSSCOMPILING FALSE) 
endif()

set(CMAKE_SYSTEM_NAME "Linux")


# set(CMAKE_POSITION_INDEPENDENT_CODE ON)

project(ddsexample VERSION 1 LANGUAGES C)


# dds头文件
include_directories(${PROJECT_SOURCE_DIR}/include)


file(GLOB_RECURSE SRC_C "${PROJECT_SOURCE_DIR}/src/*.c")


#lib 文件
if(${ARCHITECTURE} STREQUAL "arm64")
link_directories(${PROJECT_SOURCE_DIR}/lib_arm64)
elseif(${ARCHITECTURE} STREQUAL "x86")
link_directories(${PROJECT_SOURCE_DIR}/lib_x86)
endif()


add_executable(${PROJECT_NAME} ${SRC_C})


target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<AND:$<NOT:$<BOOL:${WIN32}>>,$<STREQUAL:"${CMAKE_BUILD_TYPE}","Debug">>:__DEBUG>
    $<$<BOOL:${INTERNAL_DEBUG}>:__INTERNALDEBUG> # Internal debug activated.
)

target_link_libraries(${PROJECT_NAME} ddsc dds crypto ssl pthread -lrt -ldl)
