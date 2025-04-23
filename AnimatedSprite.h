#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "Sprite.h"


class AnimatedSprite : public Sprite
{
public:
    AnimatedSprite();
    AnimatedSprite
    (
        const std::string& texturePath, 
        float x, 
        float y, 
        float height, 
        float width, 
        int textureCount, 
        int frameDuration
    );
    void draw(sf::RenderWindow& window) override;
    void updateTextures(const std::string& texturePath) override;
    void operator=(const I_Sprite& other) override;

private:
    std::vector <sf::Texture> m_textures;
    int m_currentTexture;
    int m_textureCount;
    int m_framesUntilNext;
    int m_frameDuration;
};

#endif