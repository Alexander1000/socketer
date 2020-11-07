cmake_minimum_required(VERSION 3.7)

# compiler options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

project(socketer-tests)

set(SOCKETER_PARSER_SOURCES
    ../src/handler.cpp
    ../src/request.cpp
    ../src/route.cpp
    ../src/socketer.cpp
)

find_library(CPP_UNIT_TEST libcpp-unit-test.a)
message(STATUS "Found cpp-unit-test: ${CPP_UNIT_TEST}")

include_directories(/usr/local/include)

add_executable(
    ${PROJECT_NAME} main.cpp
    ${YAML_PARSER_SOURCES}
)

target_link_libraries(${PROJECT_NAME}
    ${CPP_UNIT_TEST}
)
