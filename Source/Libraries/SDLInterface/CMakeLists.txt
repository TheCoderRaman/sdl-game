# Minimum cmake version (required)
cmake_minimum_required( VERSION 2.8.4 )

# Project name
project( sdlinterface )

# Find SDL2
include( FindPkgConfig )
pkg_search_module( SDL2 REQUIRED sdl2 )

add_library(SDL2 STATIC IMPORTED)
set_property(TARGET SDL2 PROPERTY IMPORTED_LOCATION ${SDL2_LIBRARIES})
 
set (PROJECT_INCLUDE_DIR 
	${SDL2_INCLUDE_DIRS}	# SDL headers
	${PROJECT_SOURCE_DIR}/include

	${PROJECT_SOURCE_DIR}/../Util/include
)	

set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(PROJECT_SRCS 
	${PROJECT_SOURCE_DIR}/SDLMain.cpp
	${PROJECT_SOURCE_DIR}/SDLWindow.cpp
	${PROJECT_SOURCE_DIR}/SDLEventLoop.cpp
)

# Set the compiler flags (specifically the c++11 one)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
 
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_INCLUDE_DIR}")

if (NOT TARGET util)
	add_subdirectory(../Util "${CMAKE_CURRENT_BINARY_DIR}/util/build")
endif() 
 
add_library(${PROJECT_NAME} SHARED ${PROJECT_SRCS})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)


# Link project with SDL
target_link_libraries(${PROJECT_NAME} 
	SDL2
#	Util # Temporary disable while it has no source to build
)