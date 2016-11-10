xpGetExtern(externIncs externLibs PUBLIC boost)

add_library(Hearts HeartsGame.cpp HeartsGame.hpp)

target_link_libraries(Hearts ${externLibs} Game)

target_include_directories(Hearts ${externIncs} ../PlayerAPI)