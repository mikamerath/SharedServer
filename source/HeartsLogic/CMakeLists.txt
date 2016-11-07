xpGetExtern(externIncs externLibs PUBLIC boost)

add_executable(TestHearts HeartsGame.cpp HeartsGame.hpp main.cpp)
target_link_libraries(TestHearts ${externLibs} Game)
target_include_directories(TestHearts ${externIncs} ${CMAKE_CURRENT_LIST_DIR}/../PlayerAPI)
