# Minimum cmake version (required)
cmake_minimum_required( VERSION 2.8.4 )

# Project name
project( SDLGame )

set (PROJECT_INCLUDE_DIR 

	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/Libraries/Util/include
	${PROJECT_SOURCE_DIR}/Libraries/SDLInterface/include
	${PROJECT_SOURCE_DIR}/Libraries/LEngine/include

)

set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Include directories 
# Act as header search paths
include_directories( "${PROJECT_INCLUDE_DIR}" )
include_directories( "${PROJECT_SOURCE_DIR}" )

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Sub projects
if (NOT TARGET LEngine)
	add_subdirectory(Libraries/LEngine) 
endif() 
if (NOT TARGET SDLInterface)
	add_subdirectory(Libraries/SDLInterface)
endif() 

# Stuff to compile
add_executable(

	# name of excecutable
	${PROJECT_NAME}

	# main
	src/main.cpp
	src/GameOne.cpp

)

# Set the compiler flags (specifically the c++11 one)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

target_link_libraries( 
	${PROJECT_NAME}
	LEngine
	SDLInterface
)

add_custom_command(TARGET SDLGame POST_BUILD
    COMMAND copy "C:\\VSDev\\SDL2\\lib\\x86\\SDL2.dll" $<CONFIGURATION>
)