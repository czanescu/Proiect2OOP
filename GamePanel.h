#ifndef GAMEPANEL_H
#define GAMEPANEL_H

#include "Sprite.h"
#include "Player.h"
#include "Enums.h"
#include <vector>

class GamePanel
{
public:
    GamePanel();
    GamePanel
    (
        Player& player,
        const std::string& title,
        int width,
        int height, 
        const sf::Color& backgroundColor, 
        float frameRate,
        const std::string& fontPath
    );

    void addSprite(const Sprite& sprite, const std::string& texturePath);
    void removeSprite(int index);
    void clearSprites();
    void updateSprite(int index, const Sprite& sprite);
    void renderFrame();
    void setBackgroundColor(const sf::Color& color);
    void setFont(const std::string& fontPath);
    void setFrameRate(float frameRate);
    void setWindowTitle(const std::string& title);
    void setWindowSize(int width, int height);
    void setFrameCounterValue(float value);
    bool isOpen();
    void close();
    bool pollEvent(sf::Event& event);
    void loadSpritesFromFile(const std::string& filePath);
    void clear();

    const sf::Color getBackgroundColor() const;
    const sf::RenderWindow& getWindow() const;
    const std::vector<Sprite>& getSprites() const;
    const Sprite& getSprite(int index) const;
    const sf::Font& getFont() const;
    const sf::Text& getFrameCounter() const;
    const float getFrameRate() const;
    void checkPlayerCollision(float dt);
    Player& getPlayer();

    ~GamePanel();

private:
    std::vector<Sprite> m_sprites;
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