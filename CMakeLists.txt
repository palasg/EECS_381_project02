cmake_minimum_required(VERSION 3.16)

project(Project_02)

set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} "-g -Wall -Wextra -Werror -Wshadow -Wconversion -Wunreachable-code -pedantic-errors
# -fsanitize=address -o0")


if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
endif()

# if(CMAKE_BUILD_TYPE STREQUAL Debug)
# 	message("debug mode")
#    	 set(CMAKE_CXX_FLAGS_DEBUG "-o0 -g -Wall -Wextra -Wshadow -Wconversion -Wunreachable-code -pedantic-errors -fsanitize=address -fno-omit-frame-pointer") 
#         #-fsanitize=address")

# else ()
#     message("release mode")
#     set(CMAKE_CXX_FLAGS_RELEASE "-O2")
# endif ()

add_library(cxx_setup INTERFACE)
target_compile_options(cxx_setup INTERFACE
-Wall -Wall -Wextra -Wshadow -Wconversion -Wunreachable-code -pedantic-errors -fsanitize=address -fno-omit-frame-pointer )
target_compile_features(cxx_setup INTERFACE cxx_std_17)
#linking to asan library is needed
target_link_options(cxx_setup INTERFACE -fsanitize=address) 

add_subdirectory(libs)
include(CTest)
add_subdirectory(tests)

include_directories(includes/
                    includes/String/)

file(GLOB SOURCES "src/*.cpp"
                    "src/**/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC cxx_setup)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set_target_properties( ${PROJECT_NAME}
PROPERTIES
RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

#message("${RUNTIME_OUTPUT_DIRECTORY}")

