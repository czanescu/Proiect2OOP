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
            float xAcceleration,
            float yAcceleration
        );
        MovableSprite(const MovableSprite& other);
        MovableSprite& operator=(const MovableSprite& other);

        void updateXSpeed(float newXSpeed);
        void updateYSpeed(float newYSpeed);

        void setXStartPoz(float newXStartPoz);
        void setYStartPoz(float newYStartPoz);
        void setXEndPoz(float newXEndPoz);
        void setYEndPoz(float newYEndPoz);

        Delta getXSpeed() const;
        Delta getYSpeed() const;
        float getXStartPoz() const;
        float getYStartPoz() const;
        float getXEndPoz() const;
        float getYEndPoz() const;
        float getXAcceleration() const;
        float getYAcceleration() const;




    private:
        float m_xStartPoz;
        float m_yStartPoz;
        float m_xEndPoz;
        float m_yEndPoz;
        Delta m_xSpeed;
        Delta m_ySpeed;
        float m_xAcceleration;
        float m_yAcceleration;
};

#endif