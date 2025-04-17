#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite()
    : m_currentTexture(0),
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
    for (int i = 0; i < textureCount; ++i)
    {
        m_textures[i].loadFromFile(texturePath + "/" + std::to_string(i) + ".png");
    }
    m_sprite.setTexture(m_textures[0]);
}

void AnimatedSprite::draw(sf::RenderWindow& window)
{
    m_framesUntilNext--;
    if (m_framesUntilNext <= 0)
    {
        m_currentTexture = (m_currentTexture + 1) % m_textureCount;
        m_sprite.setTexture(m_textures[m_currentTexture]);
        m_framesUntilNext = m_frameDuration; // Reset the frame counter
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
        m_textures[i].loadFromFile(texturePath + "/" + std::to_string(i) + ".png");
    }
}