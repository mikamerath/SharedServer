xpGetExtern(externIncs externLibs PUBLIC boost wxWidgets)
include_directories(${externIncs} ${CMAKE_SOURCE_DIR})
add_library(SpadesLogic
SpadesLogic.cpp
SpadesLogic.hpp
)
link_libraries(SpadesLogic ${externLibs})
