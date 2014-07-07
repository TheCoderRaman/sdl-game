#-----------------------------------------------------------------
cmake_minimum_required( VERSION 2.8.4 )

add_subdirectory(Libraries/LEngine) 
add_subdirectory(Libraries/SDLInterface)
add_subdirectory(Libraries/Util)
add_subdirectory(Libraries/Ffiseg)
add_subdirectory(../Box2D build)
add_subdirectory(GameOne)
add_subdirectory(Platformer)