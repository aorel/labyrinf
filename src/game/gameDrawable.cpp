#include "gameDrawable.h"

GameDrawable::GameDrawable() :
        Game(new LabyrinthDrawable){
    players.emplace_back(new PlayerDrawable);
}

void GameDrawable::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{
    //TODO draw scope, time, top menu, etc
}

void GameDrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    drawCurrent(target, states);

    
        const LabyrinthDrawable* labyrinthDrawable = dynamic_cast<LabyrinthDrawable*>(labyrinth.get());
        target.draw(*labyrinthDrawable);
        for(const auto &player : players){
            const PlayerDrawable* playerDrawable = dynamic_cast<PlayerDrawable*>(player.get());
            target.draw(*playerDrawable);
        }
    
    if (!isGame)
    {
        sf::Image listImage;
        listImage.loadFromFile("../src/list.png");
        sf::Texture listTexture;
        listTexture.loadFromImage(listImage);
        sf::Sprite listSprite;
        listSprite.setTexture(listTexture);
        listSprite.setPosition(sf::Vector2f(80, 50));
        //listSprite.setScale(Vector2f(0.12f, 0.12f));
        target.draw(listSprite);
        sf::Font font;
        font.loadFromFile("../src/Bellico.ttf");
        sf::Text text("", font, 70);
        text.setString("NEW GAME\n    EXIT\n");
        text.setPosition(sf::Vector2f(130, 250));
        text.setColor(sf::Color::Red);
        target.draw(text);
    }
    
}
