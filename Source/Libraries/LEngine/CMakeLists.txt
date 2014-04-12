# Minimum cmake version (required)
cmake_minimum_required( VERSION 2.8.4 )

# Project name
project( LEngine )

 
set (PROJECT_INCLUDE_DIR 
	${PROJECT_SOURCE_DIR}/include

	${PROJECT_SOURCE_DIR}/../Util/include
)	

set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(PROJECT_SRCS 
	${PROJECT_SOURCE_DIR}/LEngine.cpp
	${PROJECT_SOURCE_DIR}/LGameBase.cpp
)

# Set the compiler flags (specifically the c++11 one)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
 
include_directories(
	"${PROJECT_BINARY_DIR}"
	"${PROJECT_INCLUDE_DIR}"
)

if (NOT TARGET SDLInterface)
	add_subdirectory(../SDLInterface "SDLInterface")
endif()

add_library(${PROJECT_NAME} ${PROJECT_SRCS})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

# Link project with SDL
target_link_libraries(${PROJECT_NAME} SDLInterface)