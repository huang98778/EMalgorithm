cmake_minimum_required(VERSION 2.8)
project(EMalgorithm)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++0x")

if(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Debug)
endif()
message("Build type: " ${CMAKE_BUILD_TYPE})

# find_package(gflags REQUIRED)
# include_directories( /src)
# find_package(Boost REQUIRED COMPONENTS system signals python thread program_options filesystem )

find_package(Eigen3 REQUIRED)
include_directories( ${EIGEN3_INCLUDE_DIRS})
message("eigen dir: " ${EIGEN3_INCLUDE_DIRS})

set(EM_SRC
        src/main.cpp
        src/DataHelper.cpp
        src/EMalgorithm.cpp)

add_executable(EMalgorithm ${EM_SRC})

target_link_libraries(EMalgorithm glog
                                -lboost_system
                                -lboost_filesystem
                                # -lboost_program_options
                                )
