#ifndef SPRITE_H
#define SPRITE_H

#include "I_Sprite.hpp"

class Sprite : public I_Sprite {
public:
    Sprite(); // Constructor gol
    // Constructor fara textura
    Sprite(float x, float y, float height, float width); 
    Sprite // Constructor
    (
        const std::string& texturePath, 
        float x, 
        float y, 
        float height, 
        float width
    );
    Sprite(const Sprite& other); // Constructor de copiere

    // Implementarea metodelor I_Sprite
    void draw(sf::RenderWindow& window) override;
    void move(float x, float y) override;
    void setPosition(float x, float y) override;
    void setScale(float x, float y) override;
    void setHitBox(float x, float y) override;
    void setDrawStatus(bool status) override;
    void setCollision(bool collision) override;

    sf::Sprite getSprite() const override;
    sf::Texture getTexture() const override;
    float getWidth() const override;
    float getHeight() const override;
    Delta getPosX() const override;
    Delta getPosY() const override;
    float getScaleX() const override;
    float getScaleY() const override;
    bool getDrawStatus() const override;
    bool getCollision() const override;

    void updateTexture(const std::string& texturePath) override;
    void updatePosition(Delta& deltaX, Delta& deltaY) override;
    void changeDrawStatus() override;

    static int getSpriteCount();
    static int getSpriteProgress();
    static void raiseSpriteCount(int count);
    static void raiseSpriteProgress(int count);

    // Metodele MovableSprite trebuie sa fie mentionate,
    // implementarea este insa goala
    void updateXSpeed(float newXSpeed) override;
    void updateYSpeed(float newYSpeed) override;
    void setXStartPoz(float newXStartPoz) override;
    void setYStartPoz(float newYStartPoz) override;
    void setXEndPoz(float newXEndPoz) override;
    void setYEndPoz(float newYEndPoz) override;
    Delta getXSpeed() const override;
    Delta getYSpeed() const override;
    float getXStartPoz() const override;
    float getYStartPoz() const override;
    float getXEndPoz() const override;
    float getYEndPoz() const override;
    float getAcceleration() const override;

    // alcelasi lucri pentru AnimatedSprite
    void updateTextures(const std::string& texturePath) override;

    // operator de atribuire
    virtual void operator=(const I_Sprite& other);

    // Destructor
    virtual ~Sprite() = default;

protected:
    sf::Sprite m_sprite;
    Delta m_pozX;
    Delta m_pozY;
    float m_hitBoxX;
    float m_hitBoxY;
    bool m_isDrawn;
    bool m_collision;
    sf::Texture m_textura;
    static int m_spriteCount;
    static int m_spriteProgress;
};

#endif