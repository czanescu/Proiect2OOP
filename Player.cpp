#include "Player.hpp"
#include <iostream>
#include <iomanip>

const float GRAVITY = 981.0f; // constanta folosita pentru gravitate

// Constructor gol Player
Player::Player()
    : Sprite("mers-dr1.png", 0, 0, 100, 100),
      m_speedX(0, 0),
      m_speedY(0, 0),
      m_jumpForce(10),
      m_maxSpeedX(100),
      m_accelX(100),
      m_decelerationX(1000),
      m_mass(10),
      m_platformXSpeed(0, 0),
      m_platformYSpeed(0, 0)
{;}
// Constructor Player
Player::Player
(
    const std::string& texturePath,
    float x,
    float y, 
    float speedX, 
    float speedY, 
    float mass, 
    float jumpForce, 
    float height, 
    float width
)
  : Sprite(texturePath, x, y, height, width),
    m_speedX(speedX, speedX),
    m_speedY(speedY, speedY),
    m_jumpForce(jumpForce),
    m_maxSpeedX(700),
    m_accelX(1500),
    m_decelerationX(2000),
    m_mass(mass),
    m_platformXSpeed(0, 0),
    m_platformYSpeed(0, 0)
{;}

// functia care se ocupa cu calculele pe axa X
void Player::updateCalculationsX(DirectieX direction, double dt, float scaleX)
{
    int i; //setez i in functie de directie (pentru debug)
    if (direction == DirectieX::LEFT) i = -1;
    else if (direction == DirectieX::NONE) i = 0;
    else if (direction == DirectieX::RIGHT) i = 1;
    else i = 2;
    // if-uri care se ocupa cu miscarea stanga, dreapta si oprire
    if (direction == DirectieX::RIGHT && m_speedY.getActual() == 0)
    {
        updateTexture("assets/mers-dr1.png");
        if (m_speedX.getActual() > 0 || m_speedX.getActual() < m_maxSpeedX)
        {
            m_speedX.update(m_speedX.getActual() + m_accelX * dt);
        }
        else if (m_speedX.getActual() < 0)
        {
            m_speedX.update
            (
                m_speedX.getActual() + m_decelerationX * dt + m_accelX * dt
            );
        }
            
    }
    else if (direction == DirectieX::LEFT && m_speedY.getActual() == 0)
    {
        updateTexture("assets/mers-st1.png");
        if (m_speedX.getActual() < 0 || m_speedX.getActual() > -m_maxSpeedX)
        {
            m_speedX.update(m_speedX.getActual() - m_accelX * dt);
        }   
        else if (m_speedX.getActual() > 0)
        {
            m_speedX.update
            (
                m_speedX.getActual() - m_decelerationX * dt - m_accelX * dt
            );
        }
    }
    else if (direction == DirectieX::NONE && m_speedY.getActual() == 0)
    {
        if (m_speedX.getActual() > 0)
        {
            updateTexture("assets/mers-dr1.png");
            if (m_speedX.getActual() - m_decelerationX * dt < 0)
                m_speedX.update(0);
            else
                m_speedX.update(m_speedX.getActual() - m_decelerationX * dt);
        }
        else if (m_speedX.getActual() < 0)
        {
            updateTexture("assets/mers-st1.png");
            if (m_speedX.getActual() + m_decelerationX * dt > 0)
                m_speedX.update(0);
            else
                m_speedX.update(m_speedX.getActual() + m_decelerationX * dt);
        }
        if (m_speedX.getActual() < 20 and m_speedX.getActual() > -20)
        {
            m_speedX.update(0);
        }
    }
    // limitarea vitezei maxime
    if (m_speedX.getActual() > m_maxSpeedX)
        m_speedX.setActual(m_maxSpeedX);
    else if (m_speedX.getActual() < -m_maxSpeedX)
        m_speedX.setActual(-m_maxSpeedX);

    // calculul noii pozitii
    float newX = ((m_speedX.getActual() + m_speedX.getPrecedent()) / 2
        * scaleX + (m_platformXSpeed.getActual() 
        + m_platformXSpeed.getPrecedent()) / 2) * dt;

    // setez pozitia sprite-ului
    move(newX,0);
    m_pozX.update(m_sprite.getPosition().x);
    // cod pentru debugging
    std::cout << std::fixed << std::setprecision(6) 
          << "newX: " << newX
          << " m_speedX: "<< m_speedX.getActual()
          << " dt: " << dt
          << " directie: "<< i
          << " pozX " << m_pozX.getActual()<< ' ' << m_sprite.getPosition().x
          << std::endl;
}
// functia care se ocupa cu calculele pe axa Y
void Player::updateCalculationsY
(
    DirectieY direction, 
    double dt, 
    float scaleY,
    bool noColiziuneJos
)
{
    JumpSoundManager::getInstance().loadJumpSound("assets/jump_sound_effect.wav");
    const float gravityF = GRAVITY * m_mass;
    // daca nu exista vreun sprite sub player, acesta va cadea
    if (noColiziuneJos == 1)
    {
        m_speedY.update(m_speedY.getActual() + GRAVITY * dt);
    }
    else
    {
        if (m_speedY.getActual() == 0)
        {
            // verific daca player-ul trebuie sa sara
            if (direction == DirectieY::UP)
            {
                //setHitBox(100,100);
                JumpSoundManager::getInstance().playJumpSound();
                updateTexture("assets/salt.png");
                float actualJumpForce=-m_jumpForce+gravityF;
                m_speedY.update
                (
                    (actualJumpForce / m_mass * 0.01667)
                        + m_platformYSpeed.getActual()
                );
                m_platformYSpeed = Delta();
            }
        }
        else
        {
            m_speedY.update(m_speedY.getActual() + GRAVITY * dt);
        }
    }
    // noua pozitie
    float newY = 
        (m_speedY.getActual() + m_platformYSpeed.getActual()) * dt * scaleY;
    //cod pentru debugging
    int i;
    if (direction == DirectieY::DOWN) i = -1;
    else if (direction == DirectieY::NONE) i = 0;
    else if (direction == DirectieY::UP) i = 1;
    else i = 2;
    m_pozY.update(m_sprite.getPosition().y);
    std::cout << "newY: " << newY << "m_speedY: " << m_speedY.getActual()
              << "m_platformYSpeed: " << m_platformYSpeed.getActual()
              << "direction: " << i << "pozY: " << m_pozY.getActual()
              << m_sprite.getPosition().y << std::endl;
    // setez pozitia sprite-ului
    move(0, newY);
}
// getteri
const Delta<float> Player::getSpeedX() const
{
    return m_speedX;
}
const Delta<float> Player::getSpeedY() const
{
    return m_speedY;
}

// functiile care seteaza pozitia in caz de coliziune
void Player::hitGround(float height)
{
    m_pozY.update(height - getHeight()); // Snap to the ground
    m_sprite.setPosition(m_sprite.getPosition().x, height - getHeight());
    m_speedY.update(0); // Stop vertical movement
}

void Player::hitCeiling(float height)
{
    m_pozY.update(height + getHeight()); // Snap to the ceiling
    m_sprite.setPosition(m_sprite.getPosition().x, height);
    m_speedY.update(-m_speedY.getActual()/2); // ricochet
    m_speedY.update(m_speedY.getActual());
}

void Player::hitLeft(float width)
{
    m_pozX.update(width); // Snap to the left wall
    m_pozX.update(width);
    m_sprite.setPosition(width, m_sprite.getPosition().y);
    // verific daca player-ul se misca spre stanga sau daca peretele se misca
    // spre dreapta
    if (m_speedX.getActual() < 0)
    {
        m_speedX.update(-m_speedX.getActual()/4);
        m_speedX.update(m_speedX.getActual());
    }
}

void Player::hitRight(float width)
{
    m_pozX.update(width - getWidth());
    m_pozX.update(width - getWidth());
    m_sprite.setPosition(width - getWidth(), m_sprite.getPosition().y);
    // verific daca player-ul se misca spre dreapta sau daca peretele se
    // misca spre stanga
    if (m_speedX.getActual() > 0)
    {
        m_speedX.update(-m_speedX.getActual()/4);
        m_speedX.update(m_speedX.getActual());
    }
}

// setter pentru viteza platformei (ca sa stiu cu cat misc player-ul)
void Player::setPlatformSpeed(Delta<float> speedX, Delta<float> speedY)
{
    m_platformXSpeed = speedX;
    m_platformYSpeed = speedY;
}

// getteri pentru viteza platformei
const Delta<float> Player::getXPlatformSpeed() const
{
    return m_platformXSpeed;
}
const Delta<float> Player::getYPlatformSpeed() const
{
    return m_platformYSpeed;
}
