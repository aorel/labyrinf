#include "playerEvent.h"

PlayerEvent::PlayerEvent(PressedKey k) : key(k) {
    generateMessage();
}

PressedKey PlayerEvent::getKey() const{
    return key;
}

void PlayerEvent::generateMessage(){

}
