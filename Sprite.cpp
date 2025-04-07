#include "Sprite.h"

Sprite::Sprite()
    : m_sprite(),
      m_pozX(0, 0),
      m_pozY(0, 0),
      m_hitBoxX(0),
      m_hitBoxY(0)
{;}

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
    m_hitBoxY(height)
{
    if (!m_textura.loadFromFile(texturePath))
    {
        throw std::runtime_error("Failed to load texture: " + texturePath);
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
      m_textura(other.m_textura)
{
    m_sprite.setTexture(m_textura);
    m_sprite.setScale
    (
        m_hitBoxX / m_textura.getSize().x,
        m_hitBoxY / m_textura.getSize().y
    );
    m_sprite.setPosition(m_pozX.getActual(), m_pozY.getActual());
}

const sf::Sprite Sprite::getSprite() const
{
    return m_sprite;
}

void Sprite::operator=(const Sprite& other)
{
    if (this != &other)
    {
        m_sprite = other.m_sprite;
        m_pozX = other.m_pozX;
        m_pozY = other.m_pozY;
        m_hitBoxX = other.m_hitBoxX;
        m_hitBoxY = other.m_hitBoxY;
        m_textura = other.m_textura;
    }
}

void Sprite::move(float x, float y)
{
    setPosition(m_sprite.getPosition().x + x, m_sprite.getPosition().y + y);
}

void Sprite::setPosition(float x, float y)
{
    m_sprite.setPosition(x, y);
}

void Sprite::draw(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}

void Sprite::updateTexture(const std::string& texturePath)
{
    if (!m_textura.loadFromFile(texturePath))
    {
        throw std::runtime_error("Failed to load texture: " + texturePath);
    }
    m_sprite.setTexture(m_textura);
}

void Sprite::updatePosition(Delta& deltaX, Delta& deltaY)
{
    m_pozX.update(deltaX.getActual());
    m_pozY.update(deltaY.getActual());
    m_sprite.setPosition(m_pozX.getActual(), m_pozY.getActual());
}