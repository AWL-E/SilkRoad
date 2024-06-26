cmake_minimum_required(VERSION 3.16.3)

project(Simply  VERSION 1.0
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

## Include external dependencies
find_package(Protobuf REQUIRED)
find_package(jsoncpp REQUIRED)
find_package(CURL REQUIRED) 
#find_package(aws-lambda-runtime)

# Include CURL

include_directories(${CURL_INCLUDE_DIR})
include_directories(${JSONCPP_INCLUDE_DIRS})
include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# List variable for help
message("   --> PROTOBUF INCLUDE: ${Protobuf_INCLUDE_DIRS}")

# Generate C++ files from the .proto file
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS proto/ProtoMessages.proto)

## PROTO SECTION END ## 

SET(APPLICATION_SOURCE_FILES 
    algorithm/AlgorithmInterface.cc
    algorithm/AlgorithmManager.cc
    algorithm/PowerExchangeDetection.cc
    algorithm/ChargeEstimation.cc
    
    asdk/generic/ErrorCodes.cc

    communication/CommunicationInterface.cc
    communication/OpenSearchClient.cc
    communication/OpenSearchInterface.cc
    communication/database/DatabaseInterface.cc
    communication/http/CURLHTTPClient.cc
    communication/http/HTTPClientInterface.cc
    communication/parsing/BodyParserInterface.cc
    communication/parsing/JSONDataBodyParser.cc

    util/logging.cc
    util/uuid.cc
)

SET(APPLICATION_INCLUDE_DIRS
    src
)

find_package (glog 0.5.0 REQUIRED)

# Compile library (to reuse with tests)
add_library(application_lib SHARED ${APPLICATION_SOURCE_FILES} ${PROTO_SRCS} ${PROTO_HDRS})
target_include_directories(application_lib PUBLIC ${APPLICATION_INCLUDE_DIRS})
target_link_libraries(application_lib glog::glog ${PROTOBUF_LIBRARIES} CURL::libcurl jsoncpp_lib)

# Compile Application
add_executable(application "main.cc")
target_link_libraries(application application_lib)

install(TARGETS application)