cmake_minimum_required(VERSION 2.6)
project (labyrinf)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -g")

add_library(libLabyrinth SHARED
    src/events/playerEvent.cpp
    src/game/game.cpp
    src/game/labyrinth.cpp
    src/game/cell.cpp
    src/game/player.cpp
)
add_library(libLabyrinthDrawable SHARED
    src/game/gameDrawable.cpp
    src/game/labyrinthDrawable.cpp
    src/game/cellDrawable.cpp
    src/game/playerDrawable.cpp
)

add_executable(server server.cpp src/server.cpp src/network/server_connection.cpp src/network/chat_message.cpp)
add_executable(client client.cpp src/client.cpp src/network/client_connection.cpp src/network/chat_message.cpp)

target_link_libraries(server boost_system pthread sfml-system libLabyrinth)
target_link_libraries(client boost_system pthread sfml-system sfml-window sfml-graphics libLabyrinth libLabyrinthDrawable)
