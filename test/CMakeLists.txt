cmake_minimum_required (VERSION 3.8)

file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

FetchContent_Declare(googletest
    GIT_REPOSITORY                 https://github.com/google/googletest.git
    GIT_TAG                        b796f7d44681514f58a683a3a71ff17c94edb0c1 
    USES_TERMINAL_DOWNLOAD TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

macro(add_fse_test TEST_NAME)
    add_executable(${TEST_NAME}_tests ${TEST_NAME}_tests.cpp ${FSE_SOURCES})
    target_include_directories(${TEST_NAME}_tests PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/../src
        ${gtest_SOURCE_DIR}/include 
        ${gtest_SOURCE_DIR}
    )

    target_link_libraries(${TEST_NAME}_tests
        PRIVATE 
            gtest_main
            nlohmann_json::nlohmann_json
    )

    add_test(NAME ${TEST_NAME}_tests COMMAND ${TEST_NAME}_tests)
    gtest_discover_tests(${TEST_NAME}_tests)
endmacro()

include(GoogleTest)

add_fse_test(textparser)
add_fse_test(invertedindex)
add_fse_test(searcher)
add_fse_test(fse)