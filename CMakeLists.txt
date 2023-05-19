cmake_minimum_required (VERSION 3.8)

project (fse VERSION 1.0 LANGUAGES CXX)

configure_file(${CMAKE_CURRENT_LIST_DIR}/cmake/fseconfig.cpp.in ${CMAKE_CURRENT_LIST_DIR}/src/fseconfig.cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(JSON_MultipleHeaders OFF CACHE BOOL "" FORCE)
set(JSON_BuildTests OFF CACHE INTERNAL "")

include(FetchContent)

FetchContent_Declare(json
    GIT_REPOSITORY                 https://github.com/nlohmann/json.git
    GIT_TAG                        bc889afb4c5bf1c0d8ee29ef35eaaf4c8bef8a5d 
    USES_TERMINAL_DOWNLOAD TRUE)
FetchContent_MakeAvailable(json)

file(GLOB_RECURSE FSE_HEADERS "${CMAKE_CURRENT_LIST_DIR}/src/*.h")
file(GLOB_RECURSE FSE_SOURCES "${CMAKE_CURRENT_LIST_DIR}/src/*")

add_executable(${PROJECT_NAME} main.cpp ${FSE_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

enable_testing()
include(CTest)
add_subdirectory(test)