#include "Delta.h"
#include "Sprite.h"
#include "GamePanel.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <string>
#include <stdexcept>
#include <iostream>

const float FRAME_RATE = 60.0;

Player player("sprite.png", 1000, 500, 0, 0, 10, 700000, 120, 120);

GamePanel Panel(player,"Sprite Gravity", 1920, 1080, sf::Color(37, 37, 164, 0.7), FRAME_RATE, "arial.ttf");

void calcule(double dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        Panel.getPlayer().updateCalculationsX(DirectieX::LEFT, dt);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        Panel.getPlayer().updateCalculationsX(DirectieX::RIGHT, dt);
    }
    else
    {
        Panel.getPlayer().updateCalculationsX(DirectieX::NONE, dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        Panel.getPlayer().updateCalculationsY(DirectieY::UP, dt);
    }
    else
    {
        Panel.getPlayer().updateCalculationsY(DirectieY::NONE, dt);
    }
    Panel.checkPlayerCollision(dt);
}

void sceneSetup(){
    Panel.loadSpritesFromFile("map.map");
}

int main()
{
    sf::Color backgroundColor(37,37,164,0.7);

    // Timing variables
    const double fixedTimeStep = 1.0 / Panel.getFrameRate(); // 60 updates per second
    double accumulator = 0.0;
    auto oldTime = std::chrono::high_resolution_clock::now();

    int frameCount = 0; // Frame counter
    double frameTimeAccumulator = 0.0; // Accumulator for frame time

    sceneSetup();

    while (Panel.isOpen())
    {
        // Calculate frameTime
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsedTime = currentTime - oldTime;
        double frameTime = elapsedTime.count();
        oldTime = currentTime;
        accumulator += frameTime;
        frameTimeAccumulator += frameTime;

        // Handle events
        sf::Event event;
        while (Panel.pollEvent(event))
        {
            if ((event.type == sf::Event::Closed)
            || event.type == sf::Event::KeyPressed
            && event.key.code == sf::Keyboard::Escape)
                Panel.close();
        }
        /// Scene setup

        // Fixed update loop
        while (accumulator >= fixedTimeStep)
        {
            frameCount++;
            accumulator -= fixedTimeStep;

            calcule(fixedTimeStep);

            // Cod pentru frame counter
            if (frameTimeAccumulator >= 1.0)
            {
                Panel.setFrameCounterValue(frameCount);
                frameCount = 0;
                frameTimeAccumulator = 0.0;
            }

            //Render
            Panel.renderFrame();
        }
    }
}