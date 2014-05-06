#-----------------------------------------------------------------
# CMAKE SETTINGS
cmake_minimum_required( VERSION 2.8.4 )

#-----------------------------------------------------------------
# PROJECT NAME
project( SDLGame )

#-----------------------------------------------------------------
# DIRECTORIES
set (PROJECT_INCLUDE_DIR 

	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/Libraries/Util/include
	${CMAKE_CURRENT_SOURCE_DIR}/Libraries/SDLInterface/include
	${CMAKE_CURRENT_SOURCE_DIR}/Libraries/LEngine/include

)

set (PROJECT_SOURCE_DIR 
	${CMAKE_CURRENT_SOURCE_DIR}/src
)

#-----------------------------------------------------------------
# HEADER AND SOURCE FILES
SET(PROJECT_HEADERS
	${CMAKE_CURRENT_SOURCE_DIR}/include/GameOne.h
)

set(PROJECT_SRCS 
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/GameOne.cpp
)

#-----------------------------------------------------------------
# PULL IN DEPENDENCIES

if (NOT TARGET LEngine)
	add_subdirectory(Libraries/LEngine) 
endif() 
if (NOT TARGET SDLInterface)
	add_subdirectory(Libraries/SDLInterface)
endif() 
if (NOT TARGET Util)
	add_subdirectory(Libraries/Util)
endif() 

#-----------------------------------------------------------------
# COMPILER FLAGS 
if ( NOT MSVC ) # Not needed with vc++
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif( NOT MSVC )

# flags for release and debug builds
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG_BUILD")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DRELEASE_BUILD")

# flags for windows builds
if ( MSCV )
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DWINDOWS_BUILD")
else ( MSCV )
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DLINUX_BUILD")
endif( MSVC )

#-----------------------------------------------------------------
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

#-----------------------------------------------------------------
# INCLUDES AND COMPILE
include_directories( ${PROJECT_INCLUDE_DIR} )

add_executable( ${PROJECT_NAME} ${PROJECT_SRCS} ${PROJECT_HEADERS} )

#-----------------------------------------------------------------
# LINKING
target_link_libraries( 
	${PROJECT_NAME}
	LEngine
	SDLInterface
	Util
)

#-----------------------------------------------------------------
# POST BUILD
if ( MSVC )
	file(TO_NATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../SDL2/lib/x86/SDL2.dll" SDL_DLL)

	add_custom_command(TARGET SDLGame POST_BUILD
		COMMAND copy ${SDL_DLL} $<CONFIGURATION>
	)
endif ( MSVC )