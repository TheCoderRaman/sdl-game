#-----------------------------------------------------------------
# CMAKE SETTINGS
cmake_minimum_required( VERSION 2.8.4 )

#-----------------------------------------------------------------
# PROJECT NAME
project( LEngine )

#-----------------------------------------------------------------
#DIRECTORIES
set (PROJECT_INCLUDE_DIR
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/../Util/include
	${CMAKE_CURRENT_SOURCE_DIR}/../SDLInterface/include
)	

set (PROJECT_SOURCE_DIR
	${CMAKE_CURRENT_SOURCE_DIR}/src
)

#-----------------------------------------------------------------
# HEADER AND SOURCE FILES
SET(PROJECT_HEADERS
	${CMAKE_CURRENT_SOURCE_DIR}/include/LEngine.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/LGameBase.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/LUpdatable.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/LUpdatingList.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/LRenderer.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/LSprite.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/LEvents.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/LInput.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/LError.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/LAudio.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/LText.h
)

SET(PROJECT_SRCS
	${CMAKE_CURRENT_SOURCE_DIR}/src/LEngine.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/LGameBase.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/LUpdatingList.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/LRenderer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/LSprite.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/LInput.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/LAudio.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/LText.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/LUpdatable.cpp
)

#-----------------------------------------------------------------
include(../../cmake/config.cmake)
include(../../cmake/library.cmake)

#-----------------------------------------------------------------
# LINKING
target_link_libraries( ${PROJECT_NAME} 
	SDLInterface
	Util )