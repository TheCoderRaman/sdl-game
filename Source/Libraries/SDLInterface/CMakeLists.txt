#-----------------------------------------------------------------
# CMAKE SETTINGS
cmake_minimum_required( VERSION 2.8.4 )

#-----------------------------------------------------------------
# PROJECT NAME
project( SDLInterface )

#-----------------------------------------------------------------
# Package Search
if ( NOT MSVC )
	find_package(PkgConfig)
	pkg_search_module( SDL2 REQUIRED sdl2 )
endif() 

set (PROJECT_INCLUDE_DIR 
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/../Util/include
	${CMAKE_CURRENT_SOURCE_DIR}/../../../SDL2/include	# SDL headers
)	

set (PROJECT_SOURCE_DIR 
	${CMAKE_CURRENT_SOURCE_DIR}/src
)

#-----------------------------------------------------------------
# HEADER AND SOURCE FILES
SET(PROJECT_HEADERS
	${CMAKE_CURRENT_SOURCE_DIR}/include/SDLMain.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/SDLWindow.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/SDLEventLoop.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/SDLRenderer.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/SDLHelper.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/SDLTimer.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/SDLThread.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/SDLMutex.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/SDLSurface.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/SDLTexture.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/SDLRect.h
)

set(PROJECT_SRCS 
	${CMAKE_CURRENT_SOURCE_DIR}/src/SDLMain.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/SDLWindow.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/SDLEventLoop.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/SDLRenderer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/SDLHelper.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/SDLTimer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/SDLThread.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/SDLMutex.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/SDLSurface.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/SDLTexture.cpp
)

#-----------------------------------------------------------------
# COMPILER FLAGS 
if ( NOT MSVC ) # Not needed with vc++
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()
 
 # flags for release and debug builds
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG_BUILD")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DRELEASE_BUILD")

# flags for windows builds
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DWINDOWS_BUILD")


#-----------------------------------------------------------------
# PULL IN DEPENDENCIES
if ( MSVC )
	set(SDL2_LIBRARIES ${CMAKE_CURRENT_SOURCE_DIR}/../../../SDL2/lib/x86/SDL2.lib)
	add_library(SDL2 SHARED IMPORTED)
	set_property(TARGET SDL2 PROPERTY IMPORTED_LOCATION ${SDL2_LIBRARIES})

	set(SDL2_IMAGE_LIBRARIES ${CMAKE_CURRENT_SOURCE_DIR}/../../../SDL2/lib/x86/SDL2_image.lib)
	add_library(SDL2_IMAGE SHARED IMPORTED)
	set_property(TARGET SDL2 PROPERTY IMPORTED_LOCATION ${SDL2_IMAGE_LIBRARIES})
endif()

if (NOT TARGET Util)
	add_subdirectory(../Util "Util")
endif()

#-----------------------------------------------------------------
# INCLUDES AND COMPILE
include_directories(${PROJECT_INCLUDE_DIR})

add_library(${PROJECT_NAME} ${PROJECT_SRCS} ${PROJECT_HEADERS})

#-----------------------------------------------------------------
# SET THE PROPERTIES
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)


if( NOT MSVC )
	set( SDL2_IMAGE_LIBRARIES SDL2_image )
endif()

# Link project with SDL
target_link_libraries(${PROJECT_NAME} 
	${SDL2_LIBRARIES}
	${SDL2_IMAGE_LIBRARIES}
	Util 
)

