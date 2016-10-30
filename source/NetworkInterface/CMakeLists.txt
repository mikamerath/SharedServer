xpGetExtern(externIncs externLibs PUBLIC boost wxWidgets)
include_directories(${externIncs} ${CMAKE_SOURCE_DIR})
add_library(NetworkInterface
NetworkInterface.cpp
GeneralMessage.cpp
TCPConnection.cpp
NetworkInterface.h
GeneralMessage.h
TCPConnection.h
)
