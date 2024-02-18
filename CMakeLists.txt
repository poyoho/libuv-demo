cmake_minimum_required(VERSION 3.14)

project(libuv-demo LANGUAGES C)

include(ExternalProject)
include(GNUInstallDirs)

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE "Release")
endif()
message(STATUS "Building in ${CMAKE_BUILD_TYPE} mode")
message(STATUS "Building with ${CMAKE_C_COMPILER_ID} ${CMAKE_C_COMPILER_VERSION} on ${CMAKE_SYSTEM}")


set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_C_STANDARD 11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(deps/libuv EXCLUDE_FROM_ALL)

add_executable(libuv-demo
    src/http-server.c
)

set_target_properties(libuv-demo PROPERTIES
    C_STANDARD 11
    C_STANDARD_REQUIRED ON
)

target_include_directories(libuv-demo PRIVATE ${CURL_INCLUDE_DIRS})
target_link_libraries(libuv-demo uv_a ${CURL_LIBRARIES})

