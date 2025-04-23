#ifndef PLAYER_H
#define PLAYER_H

#include "Sprite.hpp"
#include "Enums.hpp"

class Player : public Sprite
{
public:
    Player();
    Player
    (
        const std::string& texturePath,
        float x, 
        float y, 
        float speedX, 
        float speedY, 
        float mass, 
        float jumpForce, 
        float height, 
        float width
    );
    void updateCalculationsX(DirectieX direction, double dt, float scaleX);
    void updateCalculationsY
    (
        DirectieY direction, 
        double dt,
        float scaleY, 
        bool noColiziuneJos = 0
    );
    const Delta getSpeedX() const;
    const Delta getSpeedY() const;
    void hitGround(float height);
    void hitCeiling(float height);
    void hitLeft(float width);
    void hitRight(float width);
    void setPlatformSpeed(Delta speedX, Delta speedY);
    const Delta getXPlatformSpeed() const;
    const Delta getYPlatformSpeed() const;
private:
    Delta m_speedX;
    Delta m_speedY;
    Delta m_platformXSpeed;
    Delta m_platformYSpeed;
    float m_jumpForce;
    float m_maxSpeedX;
    float m_accelX;
    float m_decelerationX;
    float m_mass;
};

#endif