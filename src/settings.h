#pragma once

//#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

namespace settings{
    constexpr int server_defualt_port {8080};
    constexpr int server_buffer_size {1024};

    const std::string windowName {"Labyrinf"};
    constexpr int windowSizeX {800};
    constexpr int windowSizeY {800};
    constexpr int windowPositionX {500};
    constexpr int windowPositionY {100};

    constexpr float gameFps {60.0f};
    const sf::Time gameSpf {sf::seconds(1.f/gameFps)};

    constexpr int labyrinthSizeX {15};
    constexpr int labyrinthSizeY {17};

    constexpr float playerFps {7.0f};
    const sf::Time playerSpf {sf::seconds(1.f/playerFps)};
    constexpr int playerStartPositionX {1};
    constexpr int playerStartPositionY {1};

    const std::vector<std::vector<int>> testLabyrinth1 =
        {{1,1,1},
         {1,0,1},
         {1,0,1},
         {1,0,1},
         {1,1,1}};
}
