xpGetExtern(externIncs externLibs PUBLIC boost wxWidgets)
add_library(CrazyEights, CrazyEightsLogic.cpp, CrazyEightsLogic.hpp)
target_link_libraries(CrazyEights ${
externLibs
} Game)
target_include_directories(CrazyEights ${externIncs})
