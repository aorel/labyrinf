#pragma once

#include <SFML/Graphics.hpp>

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

    constexpr float cellSize {40.0};
    constexpr float cellOffsetX {0.0};//2;
    constexpr float cellOffsetY {0.0};//2;
    constexpr float cellOutlineThickness {0.0};
    const sf::Color cellTypeWall {sf::Color(35, 35, 35)};
    const sf::Color cellTypeGround {sf::Color(50, 50, 50)};
    const sf::Color cellTypeWater {sf::Color(50, 50, 75)};
    const sf::Color cellTypeFire {sf::Color(75, 50, 50)};

    constexpr float playerFps {7.0f};
    const sf::Time playerSpf {sf::seconds(1.f/playerFps)};
    constexpr int playerStartPositionX {1};
    constexpr int playerStartPositionY {1};
    constexpr float playerRadius {10.0};
    const sf::Color playerColor {sf::Color(25, 25, 244)};
    constexpr float playerOffsetX {cellOffsetX + (cellSize - 2.0*playerRadius)/2.0};//float(35.0/4.0);
    constexpr float playerOffsetY {cellOffsetY + (cellSize - 2.0*playerRadius)/2.0};//float(35.0/4.0);
    
    const std::vector<std::vector<int>> testLabyrinth1 =
        {{1,1,1},
         {1,0,1},
         {1,0,1},
         {1,0,1},
         {1,1,1}};
}
