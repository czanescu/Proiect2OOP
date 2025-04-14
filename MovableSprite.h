#ifndef MOVABLESPRITE_H
#define MOVABLESPRITE_H

#include "Sprite.h"

class MovableSprite : public Sprite
{
    public:
        MovableSprite();
        MovableSprite
        (
            const std::string& fileName,
            float height,
            float width,
            float xStartPoz,
            float yStartPoz,
            float xEndPoz,
            float yEndPoz,
            float Acceleration
        );
        MovableSprite(const MovableSprite& other);
        MovableSprite& operator=(const MovableSprite& other);

        void updateXSpeed(float newXSpeed);
        void updateYSpeed(float newYSpeed);

        Delta getXSpeed() const;
        Delta getYSpeed() const;
        float getXStartPoz() const;
        float getYStartPoz() const;
        float getXEndPoz() const;
        float getYEndPoz() const;
        float getAcceleration() const;




    private:
        float m_xStartPoz;
        float m_yStartPoz;
        float m_xEndPoz;
        float m_yEndPoz;
        Delta m_xSpeed;
        Delta m_ySpeed;
        float m_Acceleration;
};

#endif