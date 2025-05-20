#ifndef I_SPRITE_H
#define I_SPRITE_H

#include <SFML/Graphics.hpp>
#include "Delta.hpp"
#include "Exceptii.hpp"
#include <string>
#include <stdexcept>

class I_Sprite {
public:
    virtual ~I_Sprite() = default;

    // Metode virtuale pure (interfață)
    
    virtual void draw(sf::RenderWindow& window) = 0;

    //diferit fata de setPosition pt ca primeste coord realtive
    virtual void move(float x, float y) = 0;

    // setteri
    virtual void setPosition(float x, float y) = 0;
    virtual void setScale(float x, float y) = 0;
    virtual void setHitBox(float x, float y) = 0;
    virtual void setDrawStatus(bool status) = 0;
    virtual void setCollision(bool collision) = 0;

    // getteri
    virtual sf::Sprite getSprite() const = 0;
    virtual sf::Texture getTexture() const = 0;
    virtual float getWidth() const = 0;
    virtual float getHeight() const = 0;
    virtual Delta<float> getPosX() const = 0;
    virtual Delta<float> getPosY() const = 0;
    virtual float getScaleX() const = 0;
    virtual float getScaleY() const = 0;
    virtual bool getDrawStatus() const = 0;
    virtual bool getCollision() const = 0;

    virtual void updateTexture(const std::string& texturePath) = 0;
    //diferit de setPosition pt ca primeste delta
    virtual void updatePosition(Delta<float>& deltaX, Delta<float>& deltaY) = 0;
    virtual void changeDrawStatus() = 0;

    // metode MovableSprite
    virtual void updateXSpeed(float newXSpeed) = 0;
    virtual void updateYSpeed(float newYSpeed) = 0;

    virtual void setXStartPoz(float newXStartPoz) = 0;
    virtual void setYStartPoz(float newYStartPoz) = 0;
    virtual void setXEndPoz(float newXEndPoz) = 0;
    virtual void setYEndPoz(float newYEndPoz) = 0;

    virtual const Delta<float> getSpeedX() const = 0;
    virtual const Delta<float> getSpeedY() const = 0;
    virtual float getXStartPoz() const = 0;
    virtual float getYStartPoz() const = 0;
    virtual float getXEndPoz() const = 0;
    virtual float getYEndPoz() const = 0;
    virtual float getAcceleration() const = 0;

    // metode AnimatedSprite
    virtual void updateTextures(const std::string& texturePath) = 0;

};

#endif