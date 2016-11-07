cmake_minimum_required(VERSION 3.3)
xpGetExtern(externIncs externLibs PUBLIC boost wxWidgets)
include_directories(${externIncs} ${CMAKE_SOURCE_DIR})
add_library(Spades
SpadesLogic.cpp
)
target_link_libraries(
Game
)