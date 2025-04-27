#include "Delta.hpp"
#include "Sprite.hpp"
#include "GamePanel.hpp"
#include "Player.hpp"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <string>
#include <stdexcept>
#include <iostream>

typedef std::chrono::high_resolution_clock              HiResClock;
typedef std::chrono::high_resolution_clock::duration    HiResDuration;
typedef std::chrono::duration<double>                   ChrDurationDouble;                    

Player player("assets/sprite.png", 1000, 500, 0, 0, 10, 600000, 100, 100);

GamePanel Panel
(
    player,
    "Sprite Gravity", 
    sf::Color(37, 37, 164, 0.7),
    "assets/arial.ttf"
);
// functie calcule care ruleaza in fiecare frame
void calcule(double dt, float scaleX, float scaleY)
{
    // schimb pozitia sprite-urilor care se misca
    Panel.moveSprites(dt);
    // iau input de la tastatura
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::A)) &&
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
    {
        Panel.getPlayer().updateCalculationsX(DirectieX::NONE, dt, scaleX);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        Panel.getPlayer().updateCalculationsX(DirectieX::LEFT, dt, scaleX);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
             sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        Panel.getPlayer().updateCalculationsX(DirectieX::RIGHT, dt, scaleX);
    }
    else
    {
        Panel.getPlayer().updateCalculationsX(DirectieX::NONE, dt, scaleX);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        Panel.getPlayer().updateCalculationsY(DirectieY::UP, dt, scaleY);
    }
    else
    {
        Panel.getPlayer().updateCalculationsY(DirectieY::NONE, dt, scaleY);
    }
    // verific daca apare coliziune intre player si sprite-uri
    Panel.checkPlayerCollision(dt, scaleY);
    
}

// functie care incarca sprite-urile din fisier si afiseaza loading screen
void sceneSetup()
{
    Panel.calculateSpriteCount("assets/map1/map1");
    int spriteCount = Panel.getSpriteCount();
    std::cout << "Am inceput incarcarea sprite-urilor" << std::endl;
    Panel.loadSpritesFromFile("assets/map1/map1.sprites");
    std::cout << "Loaded sprites from file" << std::endl;
    Panel.loadMovableSpritesFromFile("assets/map1/map1.movable");
    std::cout << "Loaded movable sprites from file" << std::endl;
    Panel.loadAnimatedSpritesFromFile("assets/map1/map1.animated");
    std::cout << "Loaded animated sprites from file" << std::endl;
    Panel.renderFrame();
}

int main()
{
    // apelez incarcarea scenei
    sceneSetup();
    //setez variabilele pentru scale si framerate
    const float SCALE_X = Panel.getWindow().getSize().x / 1920.f;
    const float SCALE_Y = Panel.getWindow().getSize().y / 1080.f;
    const double fixedTimeStep = 1.0 / Panel.getFrameRate();
    double accumulator = 0.0;
    auto oldTime = HiResClock::now();
    //initializare variabile de timing din loop
    double frameTimeAccumulator = 0.0;
    float frameTimeForFrameRate;
    double actualSleeptime = 0.0;
    double sleepTime = 0.0;
    double pauseTime = 0.0;

    while (Panel.isOpen())
    {
        auto currentTime = HiResClock::now();
        ChrDurationDouble elapsedTime = currentTime - oldTime;
        double frameTime = elapsedTime.count();
        oldTime = currentTime;
        accumulator += frameTime;
        frameTimeAccumulator += frameTime;
        //sleep pentru a nu consuma CPU, panelSleep() face sleep insa doar pe
        //linux, deoarece implementarea de sleep pentru windows nu este
        //suficient de precisa pentru a putea face sleep mai puțin de un frame.
        //din acest motiv pe windows face Sleep(0), pentru a elibera măcar
        //threadul pentru alte task-uri. (busy wait)
        if 
        (
            fixedTimeStep > accumulator && 
            fixedTimeStep - accumulator > fixedTimeStep * 0.5
        )
        {
            sleepTime = (fixedTimeStep - accumulator);
            auto sleepTimeStart = HiResClock::now();
            Panel.panelSleep(sleepTime);
            auto sleepTimeEnd = HiResClock::now();
            actualSleeptime = 
                ChrDurationDouble(sleepTimeEnd - sleepTimeStart).count();
            // pentru debugging
            std::cout <<"Sleeping for: " << sleepTime << " seconds ";
            std::cout << "but actually its " << actualSleeptime << std::endl;
        }
        // loop-ul care ruleaza o data pentru fiecare frame
        while (accumulator >= fixedTimeStep)
        {
            // secventa necesara pentru a putea inchide fereastra si pentru a
            // putea intra in meniul de pauza (tasta escape)
            sf::Event event;
            while (Panel.pollEvent(event))
            {
                if ((event.type == sf::Event::Closed))
                {
                    Panel.close();
                }
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        auto beforePause = HiResClock::now();
                        Panel.pauseMenu();
                        auto afterPause = HiResClock::now();
                        pauseTime = ChrDurationDouble(afterPause
                             - beforePause).count();
                        oldTime += std::chrono::duration_cast<HiResDuration>
                        //adaug timpul de pauza la timpul de inceput pentru ca
                        //programul sa nu incerce sa prinda din urma frame-urile
                        //nedesenate în timpul pauzei
                        (ChrDurationDouble(pauseTime));
                    }
                }
            }
            frameTimeForFrameRate = accumulator;
            accumulator -= fixedTimeStep;

            // apelez functia care calculeaza pozitia a tuturor sprite-urilor
            calcule(fixedTimeStep, SCALE_X, SCALE_Y);

            // Cod pentru frame counter
            if (frameTimeAccumulator >= 1.0)
            {
                Panel.setFrameCounterValue(1.f / frameTimeForFrameRate);
                frameTimeAccumulator = 0.0;
            }
            // pentru debugging
            std::cout << "Frame time: " << fixedTimeStep << std::endl;

            //Render
            Panel.renderFrame();
        }
    }
}