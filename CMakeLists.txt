cmake_minimum_required(VERSION 3.20)

project(Project_02)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")


if(CMAKE_BUILD_TYPE STREQUAL DEBUG)
    set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -Werror -Wshadow -Wconversion -Wunreachable-code")
else ()
    message("release mode")
    set(CMAKE_CXX_FLAGS "-Wall 03")
endif ()


include_directories(includes)

file(GLOB SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

set_target_properties( ${PROJECT_NAME}
PROPERTIES
RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
