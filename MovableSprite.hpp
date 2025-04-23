#ifndef MOVABLESPRITE_H
#define MOVABLESPRITE_H

#include "Sprite.hpp"

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

        void operator=(const I_Sprite& other) override;

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