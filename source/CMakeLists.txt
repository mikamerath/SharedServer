xpGetExtern(externIncs externLibs PUBLIC boost wxWidgets)
include_directories(${externIncs} ${CMAKE_SOURCE_DIR})
add_subdirectory(PlayerAPI)
add_subdirectory(NetworkInterface)
add_subdirectory(HeartsLogic)
add_subdirectory(CrazyEightsLogic)
add_subdirectory(SpadesLogic)
add_executable(Server
main.cpp
)