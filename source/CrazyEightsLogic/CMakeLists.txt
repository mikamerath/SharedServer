xpGetExtern(externIncs externLibs PUBLIC boost)
include_directories(${externIncs} ${CMAKE_SOURCE_DIR})
add_library(CrazyEights
CrazyEightsLogic.cpp
CrazyEightsLogic.hpp
)
link_libraries(CrazyEights ${externLibs})