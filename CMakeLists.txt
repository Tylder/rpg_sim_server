cmake_minimum_required(VERSION 3.22)
project(rpg_sim_server
        VERSION 0.0.1
        LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")

set(DEPENDENCIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(TEST_DIR ${CMAKE_CURRENT_LIST_DIR}/tests)
set(FLECS_MODULE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/flecs_modules)

include_directories(${INC_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(
        rpg_sim_server
        main.cpp
)

add_executable(
        non_ecs
        nonECS/nonECS.cpp
)

add_library(speedTable STATIC
        ${INC_DIR}/SpeedTable/SpeedTable.cpp)

add_executable(
        speedTableRun
        ${INC_DIR}/SpeedTable/main.cpp
)

## EXAMPLES
add_library(examples_lib STATIC
        examples/speedComp.cpp)

add_executable(examples
        examples/main.cpp
        )
## EXAMPLES -- END

## FASTNOISE2 - FastNoise
set(FASTNOISE2_NOISETOOL OFF CACHE BOOL "Build Noise Tool" FORCE) #example if don't need the graph tool
add_subdirectory(${DEPENDENCIES_DIR}/FastNoise2)

## FLECS - flecs_static
set(FLECS_STATIC_LIBS ON)

## JSON NLOHMANN - nlohmann_json
add_subdirectory(${DEPENDENCIES_DIR}/json-nlohmann)
set(JSON_INCLUDE_DIR ${DEPENDENCIES_DIR}/nlohmann/include)
include_directories(${JSON_INCLUDE_DIR})

### CSV PARSER ### - csv
add_subdirectory(./extern/csv-parser)
set(CSV_INCLUDE_DIR ${DEPENDENCIES_DIR}/csv-parser/include)
include_directories(${CSV_INCLUDE_DIR})
### END OF CSV PARSER ###

add_library(flecs_net STATIC
        ${FLECS_MODULE_DIR}/net/components.cpp
        ${FLECS_MODULE_DIR}/net/inits.cpp
        ${FLECS_MODULE_DIR}/net/systems.cpp)

target_link_libraries(flecs_net PUBLIC flecs_static)

add_library(flecs_transform STATIC
        ${FLECS_MODULE_DIR}/transform/components.cpp
        ${FLECS_MODULE_DIR}/transform/systems.cpp)

target_link_libraries(flecs_transform PUBLIC flecs_static)

add_library(flecs_tile STATIC
        ${FLECS_MODULE_DIR}/tile/components.cpp
        ${FLECS_MODULE_DIR}/tile/inits.cpp
        ${FLECS_MODULE_DIR}/tile/systems.cpp)

target_link_libraries(flecs_tile PUBLIC flecs_static flecs_transform)

add_library(flecs_landscape STATIC
        ${FLECS_MODULE_DIR}/landscape/components.cpp
        ${FLECS_MODULE_DIR}/landscape/inits.cpp
        ${FLECS_MODULE_DIR}/landscape/systems.cpp)

target_link_libraries(flecs_landscape PUBLIC FastNoise flecs_static flecs_transform flecs_tile flecs_net)

## Specifying that is CPP
set_target_properties(flecs_transform flecs_landscape PROPERTIES LINKER_LANGUAGE CXX)


if (CMAKE_BUILD_TYPE EQUAL DEBUG)
    add_compile_definitions(FLECS_DEBUG)
endif ()

add_compile_definitions(
        FLECS_CUSTOM_BUILD
        FLECS_CPP
        FLECS_MODULE
        FLECS_PARSER
        FLECS_PLECS
        FLECS_RULES
        FLECS_SNAPSHOT
        FLECS_STATS
        FLECS_SYSTEM
        FLECS_PIPELINE
        FLECS_TIMER
        FLECS_META
        FLECS_META_C
        FLECS_UNITS
        FLECS_EXPR
        FLECS_JSON
        FLECS_DOC
        FLECS_COREDOC
        FLECS_LOG
        FLECS_APP
        FLECS_OS_API_IMPL
        #        FLECS_HTTP
        #        FLECS_REST
)
add_subdirectory(./extern/flecs)


target_link_libraries(rpg_sim_server PUBLIC
        FastNoise
        nlohmann_json
        csv
        flecs_static
        flecs_landscape
        flecs_transform
)

#target_link_libraries(examples PUBLIC FastNoise flecs_static csv)
target_link_libraries(examples PUBLIC FastNoise flecs_static)
