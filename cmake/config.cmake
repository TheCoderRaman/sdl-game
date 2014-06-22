#-----------------------------------------------------------------
cmake_minimum_required( VERSION 2.8.4 )

# COMPILER FLAGS 
if ( NOT MSVC ) # Not needed with vc++
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

# flags for release and debug builds
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG_BUILD")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DRELEASE_BUILD")

# flags for windows builds
if ( MSVC )
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DWINDOWS_BUILD")
else ()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUNIX_BUILD")
endif()