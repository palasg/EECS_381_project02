SET(BINARY ${CMAKE_PROJECT_NAME}_test)
include_directories("${CMAKE_SOURCE_DIR}/includes/String"
	"${CMAKE_SOURCE_DIR}")
file(GLOB TEST_SOURCES "src/*.cpp")
add_executable(${BINARY} ${TEST_SOURCES} ${PROJECT_SOURCE_DIR}/src/String/String.cpp)
target_link_libraries(${BINARY} PUBLIC
	gtest)
