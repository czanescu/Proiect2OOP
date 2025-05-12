#ifndef GAMEPANEL_H
#define GAMEPANEL_H

#include "I_Sprite.hpp"
#include "Player.hpp"
#include "Sprite.hpp"
#include "MovableSprite.hpp"
#include "AnimatedSprite.hpp"
#include "Platform.hpp"
#include <vector>
#include <memory>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <chrono>

class GamePanel {
public:
    GamePanel(); // Constructor gol
    GamePanel // Constructor
    (
        Player& player,
        const std::string& title,
        const sf::Color& backgroundColor,
        const std::string& fontPath
    );

    // adaug sprite-uri de orice fel
    void addSprite
    (
        std::unique_ptr<I_Sprite> sprite, 
        const std::string& texturePath,
        bool collision
    );
    void removeSprite(int index);
    void clearSprites();
    void updateSprite(int index, std::unique_ptr<I_Sprite> sprite);

    void renderFrame();

    void setBackgroundColor(const sf::Color& color);
    void setBackgroundTexture(const std::string& texturePath);
    void setFont(const std::string& fontPath);
    void setFrameRate(float frameRate);
    void setWindowTitle(const std::string& title);
    void setWindowSize(int width, int height);
    void setFrameCounterValue(float value);

    // metoda care face sleep de seconds pe linux si 0 pe windows
    void panelSleep(float seconds);

    bool isOpen();
    void close();
    void clear();
    bool pollEvent(sf::Event& event);

    // metode care incarca sprite-uri din fisiere
    sf::Vector2i loadConfigFromFile(const std::string& filePath);
    void loadSpritesFromFile(const std::string& filePath);
    void loadMovableSpritesFromFile(const std::string& filePath);
    void loadAnimatedSpritesFromFile(const std::string& filePath);

    // metode care muta camera in functie de pozitia player-ului
    void moveScreenUp(float playerLeft);
    void moveScreenDown(float playerLeft);
    void moveScreenLeft(float playerTop);
    void moveScreenRight(float playerTop);

    Player& getPlayer();
    const I_Sprite& getSprite(int index) const;
    const sf::Color getBackgroundColor() const;
    const sf::RenderWindow& getWindow() const;
    const sf::Font& getFont() const;
    const sf::Text& getFrameCounter() const;
    const float getFrameRate() const;
    const void calculateSpriteCount(const std::string& filePath) const;
    const int getSpriteCount() const;

    void checkPlayerCollision(float dt, float scaleY);
    void moveSprites(float dt);

    // metoda care afiseaza un loading screen
    void renderProgressBar();

    // metoda care afiseaza un meniu de pauza
    void pauseMenu();

    bool isPlayerOnGround();

    // metoda care inchide programul
    void endProgram();

    ~GamePanel() = default;

private:
    std::vector<std::unique_ptr<I_Sprite>> m_sprites;
    Sprite m_backgroundSprite;
    Sprite m_loadingScreenBackground;
    Player m_player;
    sf::Color m_backgroundColor;
    sf::RenderWindow m_window;
    sf::Font m_font;
    sf::Text m_frameCounter;
    float m_frameRate;
    float m_verticalOffset = 0.0f;
    float m_horizontalOffset = 0.0f;
};

#endif