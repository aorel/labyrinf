#pragma once

#include <SFML/Graphics.hpp>

namespace settings{
    const int server_defualt_port = 8080;
    const int server_buffer_size = 1024;

    const std::string windowName = {"Labyrinf"};
    const int windowSizeX = {800};
    const int windowSizeY = {800};
    const int windowPositionX = {500};
    const int windowPositionY = {100};

    const float gameFps = {60.0f};
    const sf::Time gameSpf = sf::seconds(1.f/gameFps);
    
    const float playerFps = {7.0f};
    const sf::Time playerSpf = sf::seconds(1.f/playerFps);
    const int playerStartPositionX = {10};
    const int playerStartPositionY = {10};

    const int labyrinthSizeX = {15};
    const int labyrinthSizeY = {17};

    const float cellSize = {40};
    const float cellOffsetX = {2};
    const float cellOffsetY = {2};

    const float playerRadius = {10};
    const float playerOffsetX = {cellOffsetX + float(35.0/4.0)};
    const float playerOffsetY = {cellOffsetY + float(35.0/4.0)};
}
