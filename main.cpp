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

// Proiect 2+3 OOP (actual doar proiect 2)
// Aplicația reprezintă un joc 2D, în care un jucător
// (poate fi orice sprite patrat, dar actual este mario) se poate mișca stânga
// și dreapta atâta timp cât se află pe o platformă. Odată ce jucătorul sare,
// viteza laterală a acestuia rămâne constantă până când acesta aterizează pe
// o platformă, unde se aplică un algoritm de frânare dacă nu se apasă tasta
// aferentă mișcării actuale (simulez forța de frecare). Calculul săriturii
// jucătorului este bazat pe o simulare a săriturii (se simulează o viteză
// inițială de săritură, iar apoi atâta timp cât jucătorul nu se află pe o
// platformă, acesta va continua să cadă cu o accelerație constantă).

// Harta este formată din sprite-uri, care sunt încărcate dintr 3 fișiere
// separate (numele hărții + .sprites, .movable, .animated), sprite-urile
// trebuie să corespundă path-ului relativ din fișierul de hartă (dacă sunt
// toate sprite-urile dintr-un fișier hartă dintr-un director comun, path-ul
// relativ al directorului comun se pune la începutul fișierului). Sprite-urile
// animate din fisierul .animated se află într-un director cu numele fișierului
// și sunt numite 0.png, 1.png, 2.png etc. (numărul de sprite-uri animate
// trebuie să fie cel puțin egal cu numărul de frame-uri de animație din
// fișierul .animated). Coordonatele sprite-urilor din fișiere sunt relative la
// un sprite de început la coordonatele (0, 0), iar un sprite are inaltimea si
// latimea de o unitate (la rezoluția 1920x1080 asta inseamna 120x120px, 
// deoarece sunt mereu 9 sprite-uri pe inaltime si 16 sprite-uri pe latime).

// La fiecare rulare, încărcarea sprite-urilor poate lua (în funcție de 
// platformă) între 3 (linux) și 10 secunde (windows), probabil din cauza
// implementării librăriei SFML. Din acest motiv, am inclus un loading screen
// care se va afișa până când toate sprite-urile sunt încărcate. De asemenea,
// am inclus un meniu de pauză care poate fi accesat apăsând tasta Escape.

// Jocul utilizează sleep pentru a nu consuma CPU tot timpul, însă pe windows
// implementarea de sleep nu este suficient de precisă pentru a putea face
// sleep mai puțin de un frame. Din acest motiv, pe windows face Sleep(0),
// pentru a elibera măcar threadul pentru alte task-uri.

// Framerate-ul și rezoluția jocului pot fi setate din fișierul .config
// (înainte de rulare). Framerate-ul poate fi oricât de mare sau mic, însă
// dacă este mai mare decât poate rula calculatorul, jocul nu va rula corect.
// De adăugat că rezoluția poate fi si ea setata la aproximativ orice numar,
// insa, daca pe linux orice rezolutie mai mare decat rezolutia monitorului
// se comporta ca rezolutia monitorului, pe windows jocul va incerca sa
// deseneze la rezolutia setata, insa nu va reusi sa o faca, iar jocul va
// avea un comportament anormal la trecerea de la un "tablou de joc" la altul.
// De asemenea, jocul este gândit să ruleze la un aspect ratio de 16:9, deci
// dacă rezoluția nu este 16:9, jocul va fi streched.


/// DESCRIERE CERINTE COD

// moșteniri:
// clasele AnimatedSprite, MovableSprite și Player sunt derivate ale clasei
// Sprite (care este și ea derivată din interfața I_Sprite).

// funcții virtuale pure:
// Deoarece clasa I_Sprite este o interfață, aceasta conține funcții
// virtuale pure care trebuie implementate în clasele derivate.

// Apelarea constructorilor din clasele derivate:
// constructorul clasei MovableSprite de ex apelează constructorul
// clasei Sprite.

// Clasacu atribut de tip pointer la o clasa de baza cu derivate:
// clasa GamePanel are un atribut de tip pointer la clasa I_Sprite,
// care poate fi un pointer la orice clasă derivată din I_Sprite.

// Excepții:
// clasele de excepții sunt ținute în Exceptii.hpp și Exceptii.cpp

// Funcții și atribute statice:
// clasa Sprite are doua atribute statice care sunt folosite pentru a calcula
// progress bar-ul din loading screen. Clasa GamePanel are acces la ele prin
// câte două metode statice (getteri și setteri).

// STL
// folosesc STL pentru vectorul de sprite-uri de exemplu.


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