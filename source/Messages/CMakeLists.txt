xpGetExtern(externIncs externLibs PUBLIC boost)
include_directories(${externIncs} ${CMAKE_SOURCE_DIR})
add_library(Messages
LobbyGame.hpp
LobbyGame.cpp
)
target_link_libraries(Messages ${externLibs} Game)
