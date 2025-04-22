#include "MovableSprite.h"

MovableSprite::MovableSprite()
  : Sprite(),
    m_xStartPoz(0), 
    m_yStartPoz(0), 
    m_xEndPoz(0),
    m_yEndPoz(0), 
    m_xSpeed(), 
    m_ySpeed(), 
    m_Acceleration(0)
{;}
MovableSprite::MovableSprite
(
    const std::string& fileName,
    float height,
    float width,
    float xStartPoz,
    float yStartPoz,
    float xEndPoz,
    float yEndPoz,
    float Acceleration
)
    : Sprite(fileName, xStartPoz, yStartPoz, height, width),
      m_xStartPoz(xStartPoz),
      m_yStartPoz(yStartPoz),
      m_xEndPoz(xEndPoz),
      m_yEndPoz(yEndPoz),
      m_xSpeed(0, 0),
      m_ySpeed(0, 0),
      m_Acceleration(Acceleration)
{;}
MovableSprite::MovableSprite(const MovableSprite& other)
    : Sprite(other),
      m_xStartPoz(other.m_xStartPoz),
      m_yStartPoz(other.m_yStartPoz),
      m_xEndPoz(other.m_xEndPoz),
      m_yEndPoz(other.m_yEndPoz),
      m_xSpeed(other.m_xSpeed),
      m_ySpeed(other.m_ySpeed),
      m_Acceleration(other.m_Acceleration)
{;}
MovableSprite& MovableSprite::operator=(const MovableSprite& other)
{
    if (this != &other)
    {
        Sprite::operator=(other);
        m_xStartPoz = other.m_xStartPoz;
        m_yStartPoz = other.m_yStartPoz;
        m_xEndPoz = other.m_xEndPoz;
        m_yEndPoz = other.m_yEndPoz;
        m_xSpeed = other.m_xSpeed;
        m_ySpeed = other.m_ySpeed;
        m_Acceleration = other.m_Acceleration;
    }
    return *this;
}

Delta MovableSprite::getXSpeed() const
{
    return m_xSpeed;
}
Delta MovableSprite::getYSpeed() const
{
    return m_ySpeed;
}
float MovableSprite::getXStartPoz() const
{
    return m_xStartPoz;
}
float MovableSprite::getYStartPoz() const
{
    return m_yStartPoz;
}
float MovableSprite::getXEndPoz() const
{
    return m_xEndPoz;
}
float MovableSprite::getYEndPoz() const
{
    return m_yEndPoz;
}
float MovableSprite::getAcceleration() const
{
    return m_Acceleration;
}
void MovableSprite::updateXSpeed(float newXSpeed)
{
    m_xSpeed.update(newXSpeed);
}
void MovableSprite::updateYSpeed(float newYSpeed)
{
    m_ySpeed.update(newYSpeed);
}
void MovableSprite::setXStartPoz(float newXStartPoz)
{
    m_xStartPoz = newXStartPoz;
}
void MovableSprite::setYStartPoz(float newYStartPoz)
{
    m_yStartPoz = newYStartPoz;
}
void MovableSprite::setXEndPoz(float newXEndPoz)
{
    m_xEndPoz = newXEndPoz;
}
void MovableSprite::setYEndPoz(float newYEndPoz)
{
    m_yEndPoz = newYEndPoz;
}