#pragma once

#include <SFML/Graphics.hpp>
#include "labyrinth.h"
#include "player.h"

class Game
{
private:
    //Labirinth labirinth;
    //Players players;


    sf::RenderWindow window;
    sf::Event event;


    sf::CircleShape player;
    float vel = 0.25;
    float vel_x = 0;
    float vel_y = 0;
    float pos_x = 50;
    float pos_y = 50;

public:
    Game() :
    window(sf::VideoMode(800, 800), "SFML works!"),
    player(25){//player(25, 3)
        player.setFillColor(sf::Color::Blue);
        player.setPosition(pos_x, pos_y);
    };
    void run()
    {
        while (window.isOpen())
        {
            processEvents();
            update();
            render();
        }
    }
private:
    void processEvents()
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }

            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Left){
                    vel_x = -vel;
                }
                else if(event.key.code == sf::Keyboard::Right){
                    vel_x = vel;
                }
                else if(event.key.code == sf::Keyboard::Up){
                    vel_y = -vel;
                }
                else if(event.key.code == sf::Keyboard::Down){
                    vel_y = vel;
                }
                else{
                }
            }
            if(event.type == sf::Event::KeyReleased){
                if(event.key.code == sf::Keyboard::Left){
                    vel_x = 0;
                }
                else if(event.key.code == sf::Keyboard::Right){
                    vel_x = 0;
                }
                else if(event.key.code == sf::Keyboard::Up){
                    vel_y = 0;
                }
                else if(event.key.code == sf::Keyboard::Down){
                    vel_y = 0;
                }
                else{
                }
            }
        }
    }
    void update()
    {
        pos_x += vel_x;
        pos_y += vel_y;
        player.setPosition(pos_x, pos_y);
    }
    void render()
    {
        window.clear();
        window.draw(player);
        window.display();
    }
};
