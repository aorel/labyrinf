#pragma once

#include <SFML/Graphics.hpp>

namespace settings{
    constexpr float cellDrawableSize {40.0};
    constexpr float cellDrawableOffsetX {0.0};//2;
    constexpr float cellDrawableOffsetY {0.0};//2;
    constexpr float cellDrawableOutlineThickness {0.0};
    const sf::Color cellDrawableTypeWall {sf::Color(35, 35, 35)};
    const sf::Color cellDrawableTypeGround {sf::Color(50, 50, 50)};
    const sf::Color cellDrawableTypeWater {sf::Color(50, 50, 75)};
    const sf::Color cellDrawableTypeFire {sf::Color(75, 50, 50)};

    constexpr float playerDrawableRadius {10.0};
    const sf::Color playerDrawableColor {sf::Color(25, 25, 244)};
    constexpr float playerDrawableOffsetX {cellDrawableOffsetX + (cellDrawableSize - 2.0*playerDrawableRadius)/2.0};//float(35.0/4.0);
    constexpr float playerDrawableOffsetY {cellDrawableOffsetY + (cellDrawableSize - 2.0*playerDrawableRadius)/2.0};//float(35.0/4.0);
}
