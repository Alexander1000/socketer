cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOCKETER_SOURCES
    src/socketer.cpp
    src/route.cpp
    src/request.cpp
    src/handler.cpp
)

if(NOT DEFINED CMAKE_INSTALL_INCLUDEDIR)
    set(CMAKE_INSTALL_INCLUDEDIR include)
endif(NOT DEFINED CMAKE_INSTALL_INCLUDEDIR)

install(DIRECTORY include/socketer DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#----------------#
# Static library #
#----------------#

project(socketer VERSION 0.0.1 DESCRIPTION "socketer")

add_library(${PROJECT_NAME} STATIC ${SOCKETER_SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION 1)
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER include/socketer.h)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "socketer")
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS -fPIC)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PRIVATE src)

# find_library(IO_BUFFER libio-buffer.a)
# message(STATUS "Found io-buffer library: ${IO_BUFFER}")

include_directories(/usr/local/include)

# target_link_libraries(${PROJECT_NAME} ${IO_BUFFER})

install (TARGETS ${PROJECT_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    PUBLIC_HEADER DESTINATION include
    COMPONENT library
)
