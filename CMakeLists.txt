cmake_minimum_required(VERSION 2.6)
project (labyrinf)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror")

add_executable(
main main.cpp
src/network/socket.cpp
src/server.cpp
src/client.cpp
src/game/game.cpp
src/game/gameDrawable.cpp
src/game/labyrinth.cpp
src/game/labyrinthDrawable.cpp
src/game/cell.cpp
src/game/cellDrawable.cpp
src/game/player.cpp
src/game/playerDrawable.cpp)

target_link_libraries(main sfml-graphics sfml-window sfml-system)
