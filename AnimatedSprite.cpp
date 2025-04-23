#include "AnimatedSprite.hpp"
#include <iostream>

AnimatedSprite::AnimatedSprite()
    : Sprite(),
      m_currentTexture(0),
      m_textureCount(0),
      m_framesUntilNext(0),
      m_frameDuration(0)
{;}

AnimatedSprite::AnimatedSprite
(
    const std::string& texturePath,
    float x,
    float y,
    float height,
    float width,
    int textureCount,
    int frameDuration
)
    : m_textureCount(textureCount),
      m_framesUntilNext(frameDuration),
      m_frameDuration(frameDuration),
      m_currentTexture(0)
{
    m_textures.resize(textureCount);
    m_hitBoxX = width;
    m_hitBoxY = height;
    m_sprite.setPosition(x, y);
    setPosition(x, y);
    for (int i = 0; i < textureCount; ++i)
    {
        try
        {
            m_textures[i].loadFromFile(texturePath + "/" + std::to_string(i) + ".png");
        } catch (const FileException& e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    m_sprite.setScale
    (
        width / m_textures[0].getSize().x,
        height / m_textures[0].getSize().y
    );
    m_sprite.setTexture(m_textures[0]);
}

const std::vector<sf::Texture>& AnimatedSprite::getTextures() const
{
    return m_textures;
}
const sf::Texture& AnimatedSprite::getCurrentTexture() const
{
    return m_textures[m_currentTexture];
}

void AnimatedSprite::draw(sf::RenderWindow& window)
{
    m_framesUntilNext--;
    m_sprite.setTexture(m_textures[m_currentTexture]);
    if (m_framesUntilNext <= 0)
    {
        m_currentTexture = (m_currentTexture + 1) % m_textureCount;
        m_framesUntilNext = m_frameDuration; // Reset the frame counter
        m_sprite.setScale
        (
            m_hitBoxX / m_textures[m_currentTexture].getSize().x,
            m_hitBoxY / m_textures[m_currentTexture].getSize().y
        );
    }
    if (m_isDrawn)
    {
        window.draw(m_sprite);
    }
}

void AnimatedSprite::updateTextures(const std::string& texturePath)
{
    for (int i = 0; i < m_textureCount; ++i)
    {
        m_textures[i].loadFromFile
        (
            texturePath + "/" + std::to_string(i) + ".png"
        );
    }
    m_sprite.setTexture(m_textures[m_currentTexture]);
}
void AnimatedSprite::operator=(const I_Sprite& other)
{
    const AnimatedSprite* otherSprite = dynamic_cast<const AnimatedSprite*>(&other);
    if (!otherSprite)
    {
        throw std::runtime_error("Invalid assignment to AnimatedSprite");
    }
    Sprite::operator=(other);
    m_currentTexture = otherSprite->m_currentTexture;
    m_textureCount = otherSprite->m_textureCount;
    m_framesUntilNext = otherSprite->m_framesUntilNext;
    m_frameDuration = otherSprite->m_frameDuration;
    m_textures = otherSprite->m_textures;
    m_sprite.setTexture(m_textures[m_currentTexture]);
    m_sprite.setScale
    (
        m_hitBoxX / m_textures[m_currentTexture].getSize().x,
        m_hitBoxY / m_textures[m_currentTexture].getSize().y
    );
}