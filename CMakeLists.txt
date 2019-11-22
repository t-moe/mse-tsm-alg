cmake_minimum_required(VERSION 3.15)
project(Exercises2_CODE)

#set(CMAKE_C_STANDARD 11)

include_directories(.)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(demo
        tsp_greedy_insertion.c
        tsp_greedy_insertion.h
        tsp_test.c
        tsp_utilities.c
        tsp_utilities.h tsp_random_samp.cpp tsp_random_samp.h tsp_nearest_neighbor.cpp tsp_nearest_neighbor.h tsp_pilot.cpp tsp_pilot.h tsp_local_greedy.cpp tsp_local_greedy.h knapsack_test.cpp)

target_link_libraries(demo -lm)