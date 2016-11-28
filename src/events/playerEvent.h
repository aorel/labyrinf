#pragma once

#include "pressedKey.h"

class PlayerEvent{
public:
    PlayerEvent(PressedKey key);
    PressedKey getKey() const;

private:
    PressedKey key;

    void generateMessage();
};
