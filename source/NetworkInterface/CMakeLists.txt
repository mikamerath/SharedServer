xpGetExtern(externIncs externLibs PUBLIC boost wxWidgets)
include_directories(${externIncs} ${CMAKE_SOURCE_DIR})
add_library(NetworkInterface
NetworkInterface.cpp
NetworkInterface.hpp
ClientNetworkInterface.cpp
ClientNetworkInterface.hpp
GeneralMessage.cpp
GeneralMessage.hpp
PlayerNetworking.cpp
ServerNetworkInterface.cpp
ServerNetworkInterface.hpp
TCPConnection.cpp
TCPConnection.hpp
)
