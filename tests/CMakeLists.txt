cmake_minimum_required(VERSION 3.7)

# compiler options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

project(socketer-tests)

set(SOCKETER_PARSER_SOURCES
    ../src/handler.cpp
    ../src/request.cpp
    ../src/route.cpp
    ../src/response.cpp
    ../src/socketer.cpp
)

set(CMAKE_THREAD_LIBS_INIT "-lpthread")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_library(CPP_UNIT_TEST libcpp-unit-test.a)
message(STATUS "Found cpp-unit-test: ${CPP_UNIT_TEST}")

include(FindPkgConfig)
pkg_check_modules(CURL libcurl REQUIRED)

include_directories(
    SYSTEM ${CURL_INCLUDE_DIRS}
    /usr/local/include
    ../include
)

add_executable(
    ${PROJECT_NAME} main.cpp
    ${SOCKETER_PARSER_SOURCES}
)

target_link_libraries(${PROJECT_NAME}
    ${CPP_UNIT_TEST}
    ${CURL_LIBRARIES}
)
