#include "playerEvent.h"

PlayerEvent::PlayerEvent(const PressedKey& k) : key(k) {
}

PlayerEvent::PlayerEvent(const std::string& s) {
    if(s == settings::playerEventKeyUp){
        key = PressedKey::Up;
    }
    else if(s == settings::playerEventKeyDown){
        key = PressedKey::Down;
    }
    else if(s == settings::playerEventKeyLeft){
        key = PressedKey::Left;
    }
    else if(s == settings::playerEventKeyRight){
        key = PressedKey::Right;
    }
}

PressedKey PlayerEvent::getKey() const{
    return key;
}

std::string PlayerEvent::generateMessage() const{
    if(key == PressedKey::Up){
        return settings::playerEventKeyUp;
    }
    else if(key == PressedKey::Down){
        return settings::playerEventKeyDown;
    }
    else if(key == PressedKey::Left){
        return settings::playerEventKeyLeft;
    }
    else if(key == PressedKey::Right){
        return settings::playerEventKeyRight;
    }
    else{
        return settings::playerEventKeyUnknown;
    }
}
