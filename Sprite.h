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
    void draw(sf::RenderWindow& window);
    void updateTexture(const std::string& texturePath);
    void updatePosition(Delta& deltaX, Delta& deltaY);
    void operator=(const Sprite& other);
    virtual ~Sprite() = default;
    Delta getPosX() const
    {
        return m_pozX;
    }
    Delta getPosY() const
    {
        return m_pozY;
    }
    float getWidth() const
    {
        return m_hitBoxX;
    }
    float getHeight() const
    {
        return m_hitBoxY;
    }

protected:
    sf::Sprite m_sprite;
    Delta m_pozX;
    Delta m_pozY;

private:
    sf::Texture m_textura;
    
    float m_hitBoxX;
    float m_hitBoxY;
};

#endif // SPRITE_H