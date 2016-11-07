xpGetExtern(externIncs externLibs PUBLIC boost wxWidgets)
include_directories(${externIncs} ${CMAKE_SOURCE_DIR})
add_library(NetworkInterface
NetworkInterface.hpp
ServerNetworkInterface.hpp
ClientNetworkInterface.hpp
GeneralMessage.hpp
TCPConnection.hpp
ServerNetworkInterface.cpp
ClientNetworkInterface.cpp
NetworkInterface.cpp
GeneralMessage.cpp
TCPConnection.cpp
)


