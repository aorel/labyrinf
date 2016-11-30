cmake_minimum_required(VERSION 2.6)
project (labyrinf)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror")


add_library(libLabyrinth SHARED

    src/events/playerEvent.cpp

    src/network/socket.cpp

    src/game/game.cpp
    src/game/labyrinth.cpp
    src/game/cell.cpp
    src/game/player.cpp

    src/server.cpp
    src/client.cpp
)
add_library(libLabyrinthDrawable SHARED
    src/game/gameDrawable.cpp
    src/game/labyrinthDrawable.cpp
    src/game/cellDrawable.cpp
    src/game/playerDrawable.cpp
)


add_executable(main main.cpp)
add_executable(server server.cpp src/chat_server.cpp src/network/chat_message.cpp)
add_executable(client client.cpp src/chat_client.cpp src/network/chat_message.cpp)


target_link_libraries(main sfml-graphics sfml-window sfml-system sfml-network libLabyrinth libLabyrinthDrawable)
target_link_libraries(server boost_system pthread)
target_link_libraries(client boost_system pthread)

#target_link_libraries(server sfml-graphics sfml-window sfml-system sfml-network labyrinth_lib)
#target_link_libraries(client sfml-graphics sfml-window sfml-system sfml-network labyrinth_lib)
