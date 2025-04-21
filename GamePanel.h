#ifndef GAMEPANEL_H
#define GAMEPANEL_H

#include "Sprite.h"
#include "MovableSprite.h"
#include "AnimatedSprite.h"
#include "Player.h"
#include "Enums.h"
#include <vector>
#if defined(Win32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
#include <windows.h>
#else
#include <thread>
#endif

class GamePanel
{
public:
    GamePanel();
    GamePanel
    (
        Player& player,
        const std::string& title, 
        const sf::Color& backgroundColor, 
        const std::string& fontPath
    );

    void addSprite(const Sprite& sprite, const std::string& texturePath);
    void addCollisionlessSprite
    (
        const Sprite& sprite, 
        const std::string& texturePath
    );
    void addMovableSprite
    (
        const MovableSprite& sprite, 
        const std::string& texturePath
    );
    void addAnimatedSprite
    (
        const AnimatedSprite& sprite, 
        const std::string& texturePath
    );

    void setBackgroundTexture(const std::string& texturePath);

    void removeSprite(int index);
    void removeCollisionlessSprite(int index);
    void removeMovableSprite(int index);

    void clearSprites();
    void clearCollisionlessSprites();
    void clearMovableSprites();
    void clearAllSprites();

    void updateSprite(int index, const Sprite& sprite);
    void updateCollisionlessSprite(int index, const Sprite& sprite);
    void updateMovableSprite(int index, const MovableSprite& sprite);

    void renderFrame();
    void setBackgroundColor(const sf::Color& color);
    void setFont(const std::string& fontPath);
    void setFrameRate(float frameRate);
    void setWindowTitle(const std::string& title);
    void setWindowSize(int width, int height);
    void setFrameCounterValue(float value);
    void panelSleep (float seconds);

    bool isOpen();
    void close();
    void clear();

    bool pollEvent(sf::Event& event);

    sf::Vector2i loadConfigFromFile(const std::string& filePath);
    void loadSpritesFromFile(const std::string& filePath);
    void loadMovableSpritesFromFile(const std::string& filePath);
    void loadAnimatedSpritesFromFile(const std::string& filePath);

    void moveScreenUp(float playerLeft);
    void moveScreenDown(float playerLeft);
    void moveScreenLeft(float playerTop);
    void moveScreenRight(float playerTop);

    Player& getPlayer();
    const sf::Color getBackgroundColor() const;
    const sf::RenderWindow& getWindow() const;
    const std::vector<Sprite>& getSprites() const;
    const Sprite& getSprite(int index) const;
    const sf::Font& getFont() const;
    const sf::Text& getFrameCounter() const;
    const float getFrameRate() const;

    void checkPlayerCollision(float dt, float scaleY);
    void moveSprites(float dt);

    ~GamePanel();

private:
    std::vector<Sprite> m_sprites;
    std::vector<Sprite> m_noColSprites;
    std::vector<MovableSprite> m_movableSprites;
    std::vector<AnimatedSprite> m_animatedSprites;
    Sprite m_backgroundSprite;
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