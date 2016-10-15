#include <iostream>

#include <SFML/Graphics.hpp>

#include "labyrinf/game.h"
#include "labyrinf/client.h"
#include "labyrinf/server.h"



int main()
{
    /*if(arg == ...){
        Server server(ip, port, ...);
    }
    else{
        Client client();
    }*/

    Game game;
    game.run();

    return 0;
}

















int main1()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    //sf::CircleShape shape(100.f);
    //shape.setFillColor(sf::Color::Green);
    sf::CircleShape triangle(25, 3);
    triangle.setFillColor(sf::Color::Blue);
    //float velocity = 10;

    float vel = 0.25;
    float vel_x = 0;
    float vel_y = 0;
    float pos_x = 50;
    float pos_y = 50;
    triangle.setPosition(pos_x, pos_y);

    while (window.isOpen())
    {
        sf::Event event;



/*
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                pos_x -= velocity;
                triangle.setPosition(pos_x, pos_y);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                pos_x += velocity;
                triangle.setPosition(pos_x, pos_y);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                pos_y -= velocity;
                triangle.setPosition(pos_x, pos_y);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                pos_y += velocity;
                triangle.setPosition(pos_x, pos_y);
            }
*/


        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }

            /*if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Left){
                    pos_x -= velocity;
                    triangle.setPosition(pos_x, pos_y);
                }
                else if(event.key.code == sf::Keyboard::Right){
                    pos_x += velocity;
                    triangle.setPosition(pos_x, pos_y);
                }
                else if(event.key.code == sf::Keyboard::Up){
                    pos_y -= velocity;
                    triangle.setPosition(pos_x, pos_y);
                }
                else if(event.key.code == sf::Keyboard::Down){
                    pos_y += velocity;
                    triangle.setPosition(pos_x, pos_y);
                }
                else{
                }
            }*/

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
        pos_x += vel_x;
        pos_y += vel_y;
        triangle.setPosition(pos_x, pos_y);




        window.clear();
        //window.draw(shape);
        window.draw(triangle);
        window.display();
    }

    return 0;
}
