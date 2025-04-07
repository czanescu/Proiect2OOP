#ifndef PLAYER_H
#define PLAYER_H

#include "Sprite.h"
#include "Enums.h"

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
    void updateCalculationsX(DirectieX direction, double dt);
    void updateCalculationsY(DirectieY direction, double dt);
private:
    Delta m_speedX;
    Delta m_speedY;
    float m_jumpForce;
    float m_maxSpeedX;
    float m_accelX;
    float m_decelerationX;
    float mass;
};

#endif