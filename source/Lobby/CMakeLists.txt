xpGetExtern(externIncs externLibs PUBLIC boost)
include_directories(${externIncs} ${CMAKE_SOURCE_DIR})
add_library(Lobby
Lobby.cpp
Lobby.hpp
)
