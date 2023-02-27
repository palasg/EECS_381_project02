
if(BUILD_TESTING)
include(GoogleTest)
SET(BINARY ${CMAKE_PROJECT_NAME}_utest)
include_directories("${CMAKE_SOURCE_DIR}/includes/String"
	"${CMAKE_SOURCE_DIR}/includes/"
	"${CMAKE_SOURCE_DIR}"
	"${CMAKE_SOURCE_DIR}/libs/external/googletest/googletest/includes")
file(GLOB TEST_SOURCES "src/*.cpp")
file(GLOB PROJECT_SOURCES 
${PROJECT_SOURCE_DIR}/src/*/*.cpp
${PROJECT_SOURCE_DIR}/src/*.cpp
)
#to remove main function 
#gtest also provide main hence need to exclude
list(REMOVE_ITEM PROJECT_SOURCES "/home/palasg/cpp/git_repositories/eecs_381/EECS_381_project02/src/schedular_main.cpp")
message(${TEST_SOURCES})
#message(${PROJECT_SOURCES})

add_executable(${BINARY} ${TEST_SOURCES} ${PROJECT_SOURCES}
)
target_link_libraries(${BINARY}
 PUBLIC GTest::gtest_main
 PUBLIC cxx_setup
 )

gtest_discover_tests(${BINARY})
endif(BUILD_TESTING)
