#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "Sprite.hpp"

class AnimatedSprite : public Sprite
{
public:
    AnimatedSprite(); // Constructor gol
    AnimatedSprite // Constructor
    (
        const std::string& texturePath, 
        float x, 
        float y, 
        float height, 
        float width, 
        int textureCount, 
        int frameDuration
    );
    const std::vector <sf::Texture>& getTextures() const; // getter vector
    const sf::Texture& getCurrentTexture() const; // getter textura curenta

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