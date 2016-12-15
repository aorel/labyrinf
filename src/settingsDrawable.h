#pragma once

#include <SFML/Graphics.hpp>

namespace settingsDrawable{
    constexpr float cellDrawableSize {40.0};
    constexpr float cellDrawableOffsetX {0.0};
    constexpr float cellDrawableOffsetY {0.0};
    constexpr float cellDrawableOutlineThickness {0.0};
    const sf::Color cellDrawableTypeWall {35, 35, 35};
    const sf::Color cellDrawableTypeGround {50, 50, 50};
    const sf::Color cellDrawableTypeWater {50, 50, 75};
    const sf::Color cellDrawableTypeFire {75, 50, 50};

    constexpr float playerDrawableRadius {10.0};
    const sf::Color playerDrawableColor {25, 25, 244};
    constexpr float playerDrawableOffsetX {cellDrawableOffsetX + (cellDrawableSize - 2.0*playerDrawableRadius)/2.0};
    constexpr float playerDrawableOffsetY {cellDrawableOffsetY + (cellDrawableSize - 2.0*playerDrawableRadius)/2.0};

    const std::string imgPathHeart {"../src/game/img/heart.png"};
    const sf::Vector2f imgScaleHeart {0.4f, 0.4f};

    const std::string imgPathFire {"../src/game/img/fire.jpg"};
    const sf::Color imgMaskColorFire {255, 255, 255};
    const sf::Vector2f imgScaleFire {0.12f, 0.12f};

    const std::string imgPathWater {"../src/game/img/water.jpg"};
}
