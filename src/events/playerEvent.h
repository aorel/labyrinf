#pragma once

#include <string>
#include "pressedKey.h"

class PlayerEvent{
public:
    PlayerEvent(const PressedKey& k);
    PlayerEvent(const std::string& s);
    PressedKey getKey() const;
    std::string generateMessage() const;

private:
    PressedKey key;
};
