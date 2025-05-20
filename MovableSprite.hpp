#ifndef MOVABLESPRITE_H
#define MOVABLESPRITE_H

#include "Sprite.hpp"

class MovableSprite : public Sprite
{
    public:
        MovableSprite(); // Constructor gol
        MovableSprite // Constructor
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
        MovableSprite(const MovableSprite& other); // Constructor de copiere

        // Updateri (pentru tipul de date Delta)
        void updateXSpeed(float newXSpeed) override;
        void updateYSpeed(float newYSpeed) override;

        // Setteri
        void setXStartPoz(float newXStartPoz) override;
        void setYStartPoz(float newYStartPoz) override;
        void setXEndPoz(float newXEndPoz) override;
        void setYEndPoz(float newYEndPoz) override;

        // Getteri
        const Delta<float> getSpeedX() const override;
        const Delta<float> getSpeedY() const override;
        float getXStartPoz() const override;
        float getYStartPoz() const override;
        float getXEndPoz() const override;
        float getYEndPoz() const override;
        float getAcceleration() const override;

        // operator de atribuire
        void operator=(const I_Sprite& other) override;

    private:
        float m_xStartPoz;
        float m_yStartPoz;
        float m_xEndPoz;
        float m_yEndPoz;
        Delta<float> m_xSpeed;
        Delta<float> m_ySpeed;
        float m_Acceleration;
};

#endif