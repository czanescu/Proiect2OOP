#include "Delta.h"
#include "Sprite.h"
#include "GamePanel.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <string>
#include <stdexcept>
#include <iostream>

const float FRAME_RATE = 60.0;

Player player("assets/sprite.png", 1000, 500, 0, 0, 10, 600000, 100, 100);

GamePanel Panel
(
    player,
    "Sprite Gravity", 
    1920, 
    1080, 
    sf::Color(37, 37, 164, 0.7),
    FRAME_RATE, 
    "assets/arial.ttf"
);

void calcule(double dt)
{
    Panel.moveSprites(dt);
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::A)) &&
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
    {
        Panel.getPlayer().updateCalculationsX(DirectieX::NONE, dt);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        Panel.getPlayer().updateCalculationsX(DirectieX::LEFT, dt);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
             sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        Panel.getPlayer().updateCalculationsX(DirectieX::RIGHT, dt);
    }
    else
    {
        Panel.getPlayer().updateCalculationsX(DirectieX::NONE, dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
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
    Panel.loadSpritesFromFile("assets/map1/map1.sprites");
    Panel.loadMovableSpritesFromFile("assets/map1/map1.movable");
    Panel.loadAnimatedSpritesFromFile("assets/map1/map1.animated");
}

int main()
{
    sf::Color backgroundColor(37,37,164,0.7);

    // Timing variables
    const double fixedTimeStep = 1.0 / Panel.getFrameRate();
    double accumulator = 0.0;
    auto oldTime = std::chrono::high_resolution_clock::now();

    int frameCount = 0; // Frame counter
    double frameTimeAccumulator = 0.0; // Accumulator for frame time
    float frameTimeForFrameRate;

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
        if 
        (
            fixedTimeStep > accumulator && 
            fixedTimeStep - accumulator > fixedTimeStep * 0.5
        )
        {
            double sleepTime = (fixedTimeStep - accumulator);
            std::this_thread::sleep_for(std::chrono::duration<double>(sleepTime));
            std::cout<<"Sleeping for: " << sleepTime << " seconds" << std::endl;
        }

        // Fixed update loop
        while (accumulator >= fixedTimeStep)
        {
            // Handle events
            sf::Event event;
            while (Panel.pollEvent(event))
            {
                if ((event.type == sf::Event::Closed)
                || event.type == sf::Event::KeyPressed
                && event.key.code == sf::Keyboard::Escape)
                    Panel.close();
            }

            frameCount++;
            frameTimeForFrameRate = accumulator;
            accumulator -= fixedTimeStep;

            calcule(fixedTimeStep);

            // Cod pentru frame counter
            if (frameTimeAccumulator >= 1.0)
            {
                Panel.setFrameCounterValue(1.f / frameTimeForFrameRate);
                frameCount = 0;
                frameTimeAccumulator = 0.0;
            }

            //Render
            Panel.renderFrame();
        }
    }
}