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
	pkg_search_module( SDL2_IMAGE REQUIRED SDL2_image )
	pkg_search_module( SDL2_MIXER REQUIRED SDL2_mixer )
	pkg_search_module( SDL2_TTF REQUIRED SDL2_ttf )
endif() 

# Set the include directories
set (PROJECT_INCLUDE_DIR 
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/../Util/include
)	

# Set the include directories for SDL
if ( MSVC )
	set (PROJECT_INCLUDE_DIR 
		${PROJECT_INCLUDE_DIR}
		${CMAKE_CURRENT_SOURCE_DIR}/../../../SDL2/include
		${SDL2_INCLUDE_DIRS}
	)
else()
	set (PROJECT_INCLUDE_DIR 
		${PROJECT_INCLUDE_DIR}
		${SDL2_INCLUDE_DIRS}
		${SDL2_IMAGE_INCLUDE_DIRS}
		${SDL2_MIXER_INCLUDE_DIRS}
		${SDL2_TTF_INCLUDE_DIRS}
	)
endif()

set (PROJECT_SOURCE_DIR 
	${CMAKE_CURRENT_SOURCE_DIR}/src
)

#-----------------------------------------------------------------
# HEADER AND SOURCE FILES
SET(PROJECT_HEADERS
	${CMAKE_CURRENT_SOURCE_DIR}/include/SDLMain.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/SDLWindow.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/SDLEventLoop.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/SDLEventHandling.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/SDLRenderer.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/SDLHelper.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/SDLTimer.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/SDLThread.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/SDLMutex.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/SDLSurface.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/SDLTexture.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/SDLRect.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/SDLError.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/SDLCommon.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/SDLAudio.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/SDLText.h
)

set(PROJECT_SRCS 
	${CMAKE_CURRENT_SOURCE_DIR}/src/SDLMain.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/SDLWindow.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/SDLEventLoop.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/SDLEventHandling.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/SDLRenderer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/SDLHelper.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/SDLTimer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/SDLThread.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/SDLMutex.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/SDLSurface.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/SDLTexture.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/SDLAudio.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/SDLText.cpp
)

#-----------------------------------------------------------------
# PULL IN DEPENDENCIES
if ( MSVC )
	set(SDL2_LIBRARIES ${CMAKE_CURRENT_SOURCE_DIR}/../../../SDL2/lib/x86/SDL2.lib)
	add_library(SDL2 SHARED IMPORTED)
	set_property(TARGET SDL2 PROPERTY IMPORTED_LOCATION ${SDL2_LIBRARIES})

	set(SDL2_IMAGE_LIBRARIES ${CMAKE_CURRENT_SOURCE_DIR}/../../../SDL2/lib/x86/SDL2_image.lib)
	add_library(SDL2_IMAGE SHARED IMPORTED)
	set_property(TARGET SDL2 PROPERTY IMPORTED_LOCATION ${SDL2_IMAGE_LIBRARIES})

	set(SDL2_MIXER_LIBRARIES ${CMAKE_CURRENT_SOURCE_DIR}/../../../SDL2/lib/x86/SDL2_mixer.lib)
	add_library(SDL2_MIXER SHARED IMPORTED)
	set_property(TARGET SDL2 PROPERTY IMPORTED_LOCATION ${SDL2_MIXER_LIBRARIES})

	set(SDL2_TTF_LIBRARIES ${CMAKE_CURRENT_SOURCE_DIR}/../../../SDL2/lib/x86/SDL2_ttf.lib)
	add_library(SDL2_TTF SHARED IMPORTED)
	set_property(TARGET SDL2 PROPERTY IMPORTED_LOCATION ${SDL2_TTF_LIBRARIES})
endif()

#-----------------------------------------------------------------
include(../../cmake/config.cmake)
include(../../cmake/library.cmake)

#-----------------------------------------------------------------
if( NOT MSVC )
	set( SDL2_IMAGE_LIBRARIES SDL2_image )
	set( SDL2_MIXER_LIBRARIES SDL2_mixer )
	set( SDL2_TTF_LIBRARIES SDL2_ttf )
endif()

# Link project with SDL
target_link_libraries(${PROJECT_NAME} 
	${SDL2_LIBRARIES}
	${SDL2_IMAGE_LIBRARIES}
	${SDL2_MIXER_LIBRARIES}
	${SDL2_TTF_LIBRARIES}
	Util 
)
