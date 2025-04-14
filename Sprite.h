#ifndef SPRITE_H
#define SPRITE_H

#include <SFML/Graphics.hpp>
#include "Delta.h"
#include <string>
#include <stdexcept>

class Sprite
{
public:
    Sprite();
    Sprite(const std::string& texturePath, float x, float y, float height, float width);
    Sprite(const Sprite& other);
    const sf::Sprite getSprite() const;
    void move(float x, float y);
    void setPosition(float x, float y);
    void setScale(float x, float y);
    void draw(sf::RenderWindow& window);
    void updateTexture(const std::string& texturePath);
    void updatePosition(Delta& deltaX, Delta& deltaY);
    void operator=(const Sprite& other);
    virtual ~Sprite() = default;
    Delta getPosX() const;
    Delta getPosY() const;
    float getWidth() const;
    float getHeight() const;
    sf::Texture getTexture() const;
    bool getDrawStatus() const;
    void setDrawStatus(bool status);
    void changeDrawStatus();


protected:
    sf::Sprite m_sprite;
    Delta m_pozX;
    Delta m_pozY;

private:
    sf::Texture m_textura;
    
    float m_hitBoxX;
    float m_hitBoxY;
    bool m_isDrawn;
};

#endif // SPRITE_H