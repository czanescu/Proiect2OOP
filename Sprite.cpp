#include "Sprite.h"

Sprite::Sprite()
    : m_sprite(),
      m_pozX(0, 0),
      m_pozY(0, 0),
      m_hitBoxX(0),
      m_hitBoxY(0),
      m_isDrawn(true)
{;}

Sprite::Sprite
(
    float x, 
    float y,
    float height,
    float width
)
  : m_pozX(x, x),
    m_pozY(y, y),
    m_hitBoxX(width),
    m_hitBoxY(height),
    m_isDrawn(true)
{
    m_sprite.setPosition(x, y);
    m_sprite.setScale
    (
        width / m_textura.getSize().x,
        height / m_textura.getSize().y
    );
}

Sprite::Sprite
(
    const std::string& texturePath,
    float x, 
    float y,
    float height,
    float width
)
  : m_pozX(x, x),
    m_pozY(y, y),
    m_hitBoxX(width),
    m_hitBoxY(height),
    m_isDrawn(true)
{
    try
    {
        m_textura.loadFromFile(texturePath);
    }
    catch(const FileException& e)
    {
        std::cerr << e.what() << '\n';
    }
    m_sprite.setTexture(m_textura);
    m_sprite.setPosition(x, y);
    m_sprite.setScale
    (
        width / m_textura.getSize().x,
        height / m_textura.getSize().y
    );
}

Sprite::Sprite(const Sprite& other)
    : m_sprite(other.m_sprite),
      m_pozX(other.m_pozX),
      m_pozY(other.m_pozY),
      m_hitBoxX(other.m_hitBoxX),
      m_hitBoxY(other.m_hitBoxY),
      m_textura(other.m_textura),
      m_isDrawn(other.m_isDrawn)
{
    m_sprite.setTexture(m_textura);
    m_sprite.setScale
    (
        m_hitBoxX / m_textura.getSize().x,
        m_hitBoxY / m_textura.getSize().y
    );
    m_sprite.setPosition(m_pozX.getActual(), m_pozY.getActual());
}

sf::Sprite Sprite::getSprite() const
{
    return m_sprite;
}

void Sprite::operator=(const I_Sprite& other)
{
    const Sprite* otherSprite = dynamic_cast<const Sprite*>(&other);
    if (!otherSprite) {
        throw std::invalid_argument("Assigned object is not of type Sprite");
    }

    m_sprite = otherSprite->m_sprite;
    m_textura = otherSprite->m_textura;
    m_pozX = otherSprite->m_pozX;
    m_pozY = otherSprite->m_pozY;
    m_hitBoxX = otherSprite->m_hitBoxX;
    m_hitBoxY = otherSprite->m_hitBoxY;
    m_isDrawn = otherSprite->m_isDrawn;
}

void Sprite::move(float x, float y)
{
    setPosition(m_sprite.getPosition().x + x, m_sprite.getPosition().y + y);
}

void Sprite::setPosition(float x, float y)
{
    m_sprite.setPosition(x, y);
    m_pozX.update(x);
    m_pozY.update(y);
}

void Sprite::setScale(float x, float y)
{
    m_sprite.setScale(x, y);
}

void Sprite::setHitBox(float x, float y)
{
    m_hitBoxX = x;
    m_hitBoxY = y;
    m_sprite.setScale
    (
        x / m_textura.getSize().x,
        y / m_textura.getSize().y
    );
}
void Sprite::draw(sf::RenderWindow& window)
{
    if (m_isDrawn)
    {
        window.draw(m_sprite);
    }
}

void Sprite::updateTexture(const std::string& texturePath)
{
    try
    {
        m_textura.loadFromFile(texturePath);
    }
    catch(const FileException& e)
    {
        std::cerr << e.what() << '\n';
    }
    m_sprite.setTexture(m_textura);
}

sf::Texture Sprite::getTexture() const
{
    return m_textura;
}

void Sprite::updatePosition(Delta& deltaX, Delta& deltaY)
{
    m_pozX.update(deltaX.getActual());
    m_pozY.update(deltaY.getActual());
    m_sprite.setPosition(m_pozX.getActual(), m_pozY.getActual());
}

void Sprite::changeDrawStatus()
{
    m_isDrawn = !m_isDrawn;
}
void Sprite::setDrawStatus(bool status)
{
    m_isDrawn = status;
}
void Sprite::setCollision(bool collision)
{
    m_collision = collision;
}
bool Sprite::getDrawStatus() const
{
    return m_isDrawn;
}
bool Sprite::getCollision() const
{
    return m_collision;
}
Delta Sprite::getPosX() const
{
    return m_pozX;
}
Delta Sprite::getPosY() const
{
    return m_pozY;
}
float Sprite::getWidth() const
{
    return m_hitBoxX;
}
float Sprite::getHeight() const
{
    return m_hitBoxY;
}
float Sprite::getScaleX() const
{
    return m_sprite.getScale().x;
}
float Sprite::getScaleY() const
{
    return m_sprite.getScale().y;
}
// MovableSprite methods
void Sprite::updateXSpeed(float newXSpeed)
{
    // Not applicable for base class
}
void Sprite::updateYSpeed(float newYSpeed)
{
    // Not applicable for base class
}
void Sprite::setXStartPoz(float newXStartPoz)
{
    // Not applicable for base class
}
void Sprite::setYStartPoz(float newYStartPoz)
{
    // Not applicable for base class
}
void Sprite::setXEndPoz(float newXEndPoz)
{
    // Not applicable for base class
}
void Sprite::setYEndPoz(float newYEndPoz)
{
    // Not applicable for base class
}
Delta Sprite::getXSpeed() const
{
    // Not applicable for base class
    return Delta(0, 0);
}
Delta Sprite::getYSpeed() const
{
    // Not applicable for base class
    return Delta(0, 0);
}
float Sprite::getXStartPoz() const
{
    // Not applicable for base class
    return 0;
}
float Sprite::getYStartPoz() const
{
    // Not applicable for base class
    return 0;
}
float Sprite::getXEndPoz() const
{
    // Not applicable for base class
    return 0;
}
float Sprite::getYEndPoz() const
{
    // Not applicable for base class
    return 0;
}
float Sprite::getAcceleration() const
{
    // Not applicable for base class
    return 0;
}
// AnimatedSprite methods
void Sprite::updateTextures(const std::string& texturePath)
{
    // Not applicable for base class
}