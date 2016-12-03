xpGetExtern(externIncs externLibs PUBLIC boost)
include_directories(${externIncs} ${CMAKE_SOURCE_DIR})
add_library(AI
AI.hpp
AI.cpp
)
link_libraries(AI ${externLibs})
