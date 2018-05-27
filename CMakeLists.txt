cmake_minimum_required(VERSION 3.1)
project(InternetTraffice)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} ")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O2 -O3 -Wall")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include_directories(externals/metis/include)
include_directories(externals/GPTree)

add_subdirectory(externals/metis)
add_subdirectory(externals/GPTree)

add_subdirectory(src)
