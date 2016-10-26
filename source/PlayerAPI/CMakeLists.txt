add_library(Game
card.cpp
game.hpp
player.hpp
)
add_executable(demo main.cpp)
target_link_libraries(demo Game)