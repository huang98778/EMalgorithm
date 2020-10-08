cmake_minimum_required(VERSION 2.8)
project(EMalgorithm)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++0x")

if(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Debug)
endif()
message("Build type: " ${CMAKE_BUILD_TYPE})

# include_directories( /src)

set(EM_SRC
        src/main.cpp
        src/DataHelper.cpp
        src/EMalgorithm.cpp)

add_executable(EMalgorithm ${EM_SRC})
