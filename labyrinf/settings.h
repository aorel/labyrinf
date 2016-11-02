#pragma once

#include <SFML/Graphics.hpp>

namespace settings{
    const int server_defualt_port = 8080;
    const int server_buffer_size = 1024;

    const std::string windowName = {"Labyrinf"};
    const int windowSizeX = 800;
    const int windowSizeY = 800;
    const int windowPositionX = 500;
    const int windowPositionY = 100;

    const float gameFps = 60.0f;
    const sf::Time gameSpf = sf::seconds(1.f/gameFps);

    const int labyrinthSizeX = 15;
    const int labyrinthSizeY = 17;

    const float cellSize = 40.0;
    const float cellOffsetX = 0.0;//2;
    const float cellOffsetY = 0.0;//2;
    const float cellOutlineThickness = 0.0;
    const sf::Color cellTypeWall = sf::Color(35, 35, 35);
    const sf::Color cellTypeGround = sf::Color(50, 50, 50);
    const sf::Color cellTypeWater = sf::Color(50, 50, 75);
    const sf::Color cellTypeFire = sf::Color(75, 50, 50);

    const float playerFps = 7.0f;
    const sf::Time playerSpf = sf::seconds(1.f/playerFps);
    const int playerStartPositionX = 1;
    const int playerStartPositionY = 1;
    const float playerRadius = 10.0;
    const float playerOffsetX = cellOffsetX + (cellSize - 2.0*playerRadius)/2.0;//float(35.0/4.0);
    const float playerOffsetY = cellOffsetY + (cellSize - 2.0*playerRadius)/2.0;//float(35.0/4.0);
}
