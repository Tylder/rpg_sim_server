cmake_minimum_required(VERSION 3.22)
project(rpg_sim_server
        VERSION 0.0.1
        LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")

set(DEPENDENCIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(TEST_DIR ${CMAKE_CURRENT_LIST_DIR}/tests)

include_directories(${INC_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(
        rpg_sim_server
        main.cpp
)

## FASTNOISE2
set(FASTNOISE2_NOISETOOL OFF CACHE BOOL "Build Noise Tool" FORCE) #example if don't need the graph tool
add_subdirectory(./extern/FastNoise2)

## FLECS
set(FLECS_STATIC_LIBS ON)
add_subdirectory(./extern/flecs)

target_link_libraries(rpg_sim_server PUBLIC FastNoise flecs_static)