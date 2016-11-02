xpGetExtern(externIncs externLibs PUBLIC boost wxWidgets)
include_directories(${externIncs} ${CMAKE_SOURCE_DIR})
add_library(NetworkInterface
NetworkInterface.hpp
GeneralMessage.hpp
TCPConnection.hpp
)
