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
    Sprite(float x, float y, float height, float width);
    Sprite
    (
        const std::string& texturePath, 
        float x, 
        float y, 
        float height, 
        float width
    );
    Sprite(const Sprite& other);
    const sf::Sprite getSprite() const;
    void move(float x, float y);
    void setPosition(float x, float y);
    void setScale(float x, float y);
    void setHitBox(float x, float y);
    virtual void draw(sf::RenderWindow& window);
    void updateTexture(const std::string& texturePath);
    void updatePosition(Delta& deltaX, Delta& deltaY);
    void operator=(const Sprite& other);
    virtual ~Sprite() = default;
    Delta getPosX() const;
    Delta getPosY() const;
    float getWidth() const;
    float getHeight() const;
    float getScaleX() const;
    float getScaleY() const;
    sf::Texture getTexture() const;
    bool getDrawStatus() const;
    void setDrawStatus(bool status);
    void changeDrawStatus();


protected:
    sf::Sprite m_sprite;
    Delta m_pozX;
    Delta m_pozY;
    float m_hitBoxX;
    float m_hitBoxY;
    bool m_isDrawn;

private:
    sf::Texture m_textura;
};

#endif // SPRITE_H