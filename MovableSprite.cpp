#include "MovableSprite.hpp"

// Constructor gol MovableSprite
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
// Constructor MovableSprite
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
// Constructor de copiere MovableSprite
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

// getteri
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
//  updateri (pentru tipul de date Delta)
void MovableSprite::updateXSpeed(float newXSpeed)
{
    m_xSpeed.update(newXSpeed);
}
void MovableSprite::updateYSpeed(float newYSpeed)
{
    m_ySpeed.update(newYSpeed);
}
// setteri
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
// operator de atribuire
void MovableSprite::operator=(const I_Sprite& other)
{
    const MovableSprite* otherMS = dynamic_cast<const MovableSprite*>(&other);
    if (!otherMS) {
        throw std::invalid_argument
        (
            "Assigned object is not of type MovableSprite"
        );
    }

    Sprite::operator=(other);
    m_xStartPoz = otherMS->m_xStartPoz;
    m_yStartPoz = otherMS->m_yStartPoz;
    m_xEndPoz = otherMS->m_xEndPoz;
    m_yEndPoz = otherMS->m_yEndPoz;
    m_xSpeed = otherMS->m_xSpeed;
    m_ySpeed = otherMS->m_ySpeed;
    m_Acceleration = otherMS->m_Acceleration;
}