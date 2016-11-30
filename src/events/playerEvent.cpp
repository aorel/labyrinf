#include "playerEvent.h"

PlayerEvent::PlayerEvent(PressedKey k) : key(k) {
    generateMessage();
}

PressedKey PlayerEvent::getKey() const{
    return key;
}

std::string PlayerEvent::generateMessage() const{
    if(key == PressedKey::Up){
        return "up";
    }
    else if(key == PressedKey::Down){
        return "down";
    }
    else if(key == PressedKey::Left){
        return "left";
    }
    else if(key == PressedKey::Right){
        return "right";
    }
    else{
        return "unknown";
    }
}
