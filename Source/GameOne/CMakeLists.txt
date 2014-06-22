#-----------------------------------------------------------------
# CMAKE SETTINGS
cmake_minimum_required( VERSION 2.8 )

#-----------------------------------------------------------------
# PROJECT NAME
project( SDLGame )

#-----------------------------------------------------------------
# DIRECTORIES
set (PROJECT_INCLUDE_DIR 

	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/../Libraries/Util/include
	${CMAKE_CURRENT_SOURCE_DIR}/../Libraries/SDLInterface/include
	${CMAKE_CURRENT_SOURCE_DIR}/../Libraries/LEngine/include

)

set (PROJECT_SOURCE_DIR 
	${CMAKE_CURRENT_SOURCE_DIR}/src
)

#-----------------------------------------------------------------
# HEADER AND SOURCE FILES
SET(PROJECT_HEADERS
	${CMAKE_CURRENT_SOURCE_DIR}/include/GameOne.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/GameSprite.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/Banana.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/Paddle.h
)

set(PROJECT_SRCS 
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/GameOne.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/GameSprite.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Banana.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Paddle.cpp
)

#-----------------------------------------------------------------
# PULL IN DEPENDENCIES

#-----------------------------------------------------------------
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build/)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

#-----------------------------------------------------------------
include(../cmake/config.cmake)
include(../cmake/game.cmake)

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

# Set a couple of directories
set( SDL_LIB "${CMAKE_CURRENT_SOURCE_DIR}/../../SDL2/lib/x86/" )
set( MEDIA_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Media/" )
set( PROJECT_BINARY_DIR ${CMAKE_BINARY_DIR}/$<CONFIGURATION>)

# Convert these to native
file(TO_NATIVE_PATH ${SDL_LIB} SDL_LIB)
file(TO_NATIVE_PATH ${MEDIA_DIRECTORY} MEDIA_DIRECTORY)
file(TO_NATIVE_PATH ${PROJECT_BINARY_DIR} PROJECT_BINARY_DIR)

# on MSVC we need to copy over the SDL dll files
if ( MSVC )

	# Copy ALL the SDL dll files
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND copy ${SDL_LIB}\\*.dll ${PROJECT_BINARY_DIR}
	)

endif() 

# Copy the media folder
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${MEDIA_DIRECTORY} Media
)
