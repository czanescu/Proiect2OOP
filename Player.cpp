#include "Player.h"
#include <iostream>
#include <iomanip>

const float GRAVITY = 981.0f; // Gravity constant

Player::Player()
    : Sprite("sprite.png", 0, 0, 100, 100),
      m_speedX(0, 0),
      m_speedY(0, 0),
      m_jumpForce(10),
      m_maxSpeedX(100),
      m_accelX(100),
      m_decelerationX(1000),
      m_mass(10),
      m_platformSpeed(0, 0)
{;}
Player::Player
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
)
  : Sprite(texturePath, x, y, height, width),
    m_speedX(speedX, speedX),
    m_speedY(speedY, speedY),
    m_jumpForce(jumpForce),
    m_maxSpeedX(700),
    m_accelX(1500),
    m_decelerationX(2000),
    m_mass(mass),
    m_platformSpeed(0, 0)
{;}
void Player::updateCalculationsX(DirectieX direction, double dt)
{
    int i;
    if (direction == DirectieX::LEFT) i = -1;
    else if (direction == DirectieX::NONE) i = 0;
    else if (direction == DirectieX::RIGHT) i = 1;
    else i = 2;
    if (m_speedX.getActual() < 20 and m_speedX.getActual() > -20)
    {
        m_speedX.setActual(0);
    }
    if (direction == DirectieX::RIGHT && m_speedY.getActual() == 0)
    {
        if (m_speedX.getActual()>0 || m_speedX.getActual() < m_maxSpeedX)
            m_speedX.update(m_speedX.getActual()+m_accelX*dt);
        else if (m_speedX.getActual() < 0)
            m_speedX.update(m_speedX.getActual()+m_decelerationX*dt + m_accelX*dt);
    }
    else if (direction == DirectieX::LEFT && m_speedY.getActual() == 0)
    {
        if (m_speedX.getActual()<0 || m_speedX.getActual() > -m_maxSpeedX)
            m_speedX.update(m_speedX.getActual()-m_accelX*dt);
        else if (m_speedX.getActual() > 0)
            m_speedX.update(m_speedX.getActual()-m_decelerationX*dt - m_accelX*dt);
    }
    else if (direction == DirectieX::NONE && m_speedY.getActual() == 0)
    {
        if (m_speedX.getActual() > 0)
        {
            if (m_speedX.getActual()-m_decelerationX*dt < 0)
                m_speedX.update(0);
            else
                m_speedX.update(m_speedX.getActual()-m_decelerationX*dt);
        }
        else if (m_speedX.getActual() < 0)
        {
            if (m_speedX.getActual()+m_decelerationX*dt > 0)
                m_speedX.update(0);
            else
                m_speedX.update(m_speedX.getActual()+m_decelerationX*dt);
        }
        if (m_speedX.getActual() < 20 and m_speedX.getActual() > -20)
        {
            m_speedX.update(0);
        }
    }
    if (m_speedX.getActual() > m_maxSpeedX)
        m_speedX.setActual(m_maxSpeedX);
    else if (m_speedX.getActual() < -m_maxSpeedX)
        m_speedX.setActual(-m_maxSpeedX);
    float newX = ((m_speedX.getActual()+m_speedX.getPrecedent())/2 + (m_platformSpeed.getActual()+m_platformSpeed.getPrecedent())/2) * dt;
    move(newX,0);
    m_pozX.update(m_sprite.getPosition().x);
    std::cout << std::fixed << std::setprecision(6) 
          << "newX: " << newX
          << " m_speedX: "<< m_speedX.getActual()
          << " dt: " << dt
          << " directie: "<< i
          << " pozX "<< m_pozX.getActual()<< ' ' << m_sprite.getPosition().x
          <<std::endl;
}
void Player::updateCalculationsY(DirectieY direction, double dt, bool noColiziuneJos)
{
    const float gravityF = GRAVITY * m_mass;
    if (noColiziuneJos == 1)
    {
        m_speedY.update(m_speedY.getActual() + GRAVITY * dt);
    }
    else
    {
    if (m_speedY.getActual() == 0)
    {
        if (direction == DirectieY::UP)
        {
            
            float actualJumpForce=-m_jumpForce+gravityF;
            m_speedY.update(actualJumpForce / m_mass * dt);
        }
    }
    else
    {
        m_speedY.update(m_speedY.getActual() + GRAVITY * dt);
    }
    }
    float newY = m_speedY.getActual() * dt;
    int i;
    if (direction == DirectieY::DOWN) i = -1;
    else if (direction == DirectieY::NONE) i = 0;
    else if (direction == DirectieY::UP) i = 1;
    else i = 2;
    m_pozY.update(m_sprite.getPosition().y);
    std::cout<<"newY: "<<newY<<"m_speedY: "<<m_speedY.getActual()
             <<"direction: "<<i
             <<"pozY: "<<m_pozY.getActual()<<m_sprite.getPosition().y<<std::endl;

    ///aici trebuie verificata coliziunea

    move(0, newY);
}
const Delta Player::getSpeedX() const
{
    return m_speedX;
}
const Delta Player::getSpeedY() const
{
    return m_speedY;
}

void Player::hitGround(float height)
{
    m_pozY.update(height - getHeight()); // Snap to the ground
    m_sprite.setPosition(m_sprite.getPosition().x, height - getHeight());
    m_speedY.update(0); // Stop vertical movement
}

void Player::hitCeiling(float height)
{
    m_pozY.update(height + getHeight()); // Snap to the ceiling
    m_sprite.setPosition(m_sprite.getPosition().x, height);
    m_speedY.update(-m_speedY.getActual()/2); // ricochet
    m_speedY.update(m_speedY.getActual());
}

void Player::hitLeft(float width)
{
    m_pozX.update(width); // Snap to the left wall
    m_pozX.update(width);
    m_sprite.setPosition(width, m_sprite.getPosition().y);
    m_speedX.update(-m_speedX.getActual()/4); // Stop horizontal movement
    m_speedX.update(m_speedX.getActual());
}

void Player::hitRight(float width)
{
    m_pozX.update(width - getWidth());
    m_pozX.update(width - getWidth());
     // Snap to the right wall
    m_sprite.setPosition(width - getWidth(), m_sprite.getPosition().y);
    m_speedX.update(-m_speedX.getActual()/4); // Stop horizontal movement
    m_speedX.update(m_speedX.getActual()); // Stop vertical movement
}

void Player::setPlatformSpeed(Delta speed)
{
    m_platformSpeed = speed;
}