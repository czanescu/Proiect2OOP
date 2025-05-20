#ifndef PLAYER_H
#define PLAYER_H

#include "Sprite.hpp"
#include "Enums.hpp"

class Player : public Sprite
{
public:
    Player(); // Constructor gol
    Player // Constructor
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
    // Calcule
    void updateCalculationsX(DirectieX direction, double dt, float scaleX);
    void updateCalculationsY
    (
        DirectieY direction, 
        double dt,
        float scaleY, 
        bool noColiziuneJos = 0
    );
    // Getteri
    const Delta<float> getSpeedX() const override;
    const Delta<float> getSpeedY() const override;
    const Delta<float> getXPlatformSpeed() const;
    const Delta<float> getYPlatformSpeed() const;
    // Coliziuni
    void hitGround(float height);
    void hitCeiling(float height);
    void hitLeft(float width);
    void hitRight(float width);
    // Setter pentru viteza platformei
    void setPlatformSpeed(Delta<float> speedX, Delta<float> speedY);
private:
    Delta<float> m_speedX;
    Delta<float> m_speedY;
    Delta<float> m_platformXSpeed;
    Delta<float> m_platformYSpeed;
    float m_jumpForce;
    float m_maxSpeedX;
    float m_accelX;
    float m_decelerationX;
    float m_mass;
};

#endif