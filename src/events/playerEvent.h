#pragma once

#include <string>
#include "pressedKey.h"

class PlayerEvent{
public:
    PlayerEvent(PressedKey key);
    PressedKey getKey() const;
    std::string generateMessage() const;

private:
    PressedKey key;
};
