xpGetExtern(externIncs externLibs PUBLIC boost wxWidgets)
include_directories(${externIncs} ${CMAKE_SOURCE_DIR})
add_library(Game
Card.hpp
Card.cpp
Game.hpp
Player.hpp
Player.cpp
)
