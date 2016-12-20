#include "gameDrawable.h"

GameDrawable::GameDrawable() :
        Game(new LabyrinthDrawable){
}

void GameDrawable::addLocalPlayer(){
    std::cout << "GameDrawable::addLocalPlayer()" << std::endl;
    //players.emplace_back(new PlayerDrawable);
    //players[localPlayer] = std::unique_ptr<Player>(new PlayerDrawable);
    addPlayer(localPlayer);
}

void GameDrawable::addPlayer(const int& playerIndex){
    std::cout << "GameDrawable::addPlayer() " << playerIndex << std::endl;
    if(players.find(playerIndex) == players.end()){
        players[playerIndex] = std::unique_ptr<Player>(new PlayerDrawable);
    }
    else{
        std::cout << "GameDrawable::addPlayer(): ERROR" << std::endl;
    }
}

void GameDrawable::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{
    //TODO draw scope, time, top menu, etc
}

void GameDrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    drawCurrent(target, states);

    const LabyrinthDrawable* labyrinthDrawable = dynamic_cast<LabyrinthDrawable*>(labyrinth.get());
    target.draw(*labyrinthDrawable);
    for(const auto &player : players){
        const PlayerDrawable* playerDrawable = dynamic_cast<PlayerDrawable*>(player.second.get());
        target.draw(*playerDrawable);
    }

    if (!isGame){
        sf::Image listImage;
        listImage.loadFromFile(settingsDrawable::imgPathList);
        sf::Texture listTexture;
        listTexture.loadFromImage(listImage);
        sf::Sprite listSprite;
        listSprite.setTexture(listTexture);
        listSprite.setPosition(sf::Vector2f(80, 50));
        //listSprite.setScale(Vector2f(0.12f, 0.12f));
        target.draw(listSprite);
        sf::Font font;
        font.loadFromFile(settingsDrawable::fontPathBellico);
        sf::Text text("", font, 70);
        text.setString("NEW GAME\n    EXIT\n");
        text.setPosition(settingsDrawable::textPosition);
        text.setColor(settingsDrawable::textColor);
        target.draw(text);
    }
}
