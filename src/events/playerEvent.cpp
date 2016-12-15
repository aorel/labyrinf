#include "playerEvent.h"

PlayerEvent::PlayerEvent(const PressedKey& k) : key(k) {
    generateMessage();
}

PlayerEvent::PlayerEvent(const std::string& s) {
    if(s == "up"){
        key = PressedKey::Up;
    }
    else if(s == "down"){
        key = PressedKey::Down;
    }
    else if(s == "left"){
        key = PressedKey::Left;
    }
    else if(s == "right"){
        key = PressedKey::Right;
    }
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
