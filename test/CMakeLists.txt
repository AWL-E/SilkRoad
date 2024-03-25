
# cmake_minimum_required(VERSION 2.6)
 

# Link runTests with what we want to test and the GTest and pthread library
# add_executable(runTests tests.cpp)
# target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)


cmake_minimum_required(VERSION 3.16)  # If fast way

project(Simply_test  VERSION 1.0
                DESCRIPTION "Simply"
                LANGUAGES CXX)

add_compile_options("-Wno-deprecated-declarations")
add_compile_options("-Wno-inconsistent-missing-override")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS "Building ${CMAKE_BUILD_TYPE}")
IF(CMAKE_BUILD_TYPE MATCHES DEBUG)
    SET(CMAKE_C_FLAGS_DEBUG "-ggdb -O0")  # Tuning debugger for gdb and level 0 of optimisation
    SET(CMAKE_CXX_FLAGS_DEBUG "-ggdb -O0")  # Tuning debugger for gdb and level 0 of optimisation
ELSE()
    SET(CMAKE_C_FLAGS "-O3 -DNDEBUG")  # Tuning debugger for gdb and level 3 of optimisation
    SET(CMAKE_CXX_FLAGS "-O3 -DNDEBUG")  # Tuning for level 3 of optimisation
ENDIF(CMAKE_BUILD_TYPE MATCHES DEBUG)

IF(NOT DEFINED APP_NAME)
    set(APP_NAME "application")
    message(STATUS "Hack to provide default variable, APP_NAME to prevent an error message.")
ENDIF()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(TEST_APPLICATION_SRC 
    "proto/test_message_handler.cc"

    "algorithm/algorithm_manager.cc"
    "algorithm/power_exchange_detection.cc"
    "algorithm/charge_estimation.cc"

    "communication/test_curl_https_client.cc"
    "communication/test_database_interface.cc" 
    "communication/test_json_body_parser.cc"
)

add_executable(basic_test_application "main.cc" ${TEST_APPLICATION_SRC})

target_include_directories(basic_test_application PUBLIC "${PROJECT_SOURCE_DIR}/../src")
target_link_libraries(basic_test_application ${GTEST_LIBRARIES} pthread application_lib)

install(TARGETS basic_test_application)

add_test(NAME basic_test_application COMMAND basic_test_application)