xpGetExtern(externIncs externLibs PUBLIC boost)
include_directories(${externIncs} ${CMAKE_SOURCE_DIR})
add_library(NetworkInterface
ClientNetworkInterface.cpp
ClientNetworkInterface.hpp
GeneralMessage.cpp
GeneralMessage.hpp
NetworkInterface.cpp
NetworkInterface.hpp
PlayerNetworking.cpp
ServerNetworkInterface.cpp
ServerNetworkInterface.hpp
TCPConnection.cpp
TCPConnection.hpp
)
link_libraries(NetworkInterface ${externLibs})
