xpGetExtern(externIncs externLibs PUBLIC boost wxWidgets)
include_directories(${externIncs} ${CMAKE_SOURCE_DIR})
add_library(GameLogic
SpadesLogic.cpp
HeartsGame.cpp
CrazyEightsLogic.cpp
SpadesLogic.hpp
HeartsGame.hpp
CrazyEightsLogic.hpp
)
link_libraries(GameLogic ${externLibs})
