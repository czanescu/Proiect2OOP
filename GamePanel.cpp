#include "GamePanel.h"
#include <iomanip>
#include <sstream>
#include <iostream>
#include <fstream>

GamePanel::GamePanel()
    : m_window(sf::VideoMode(1920,1080), "Game Panel"),
      m_backgroundColor(sf::Color::Black),
      m_frameRate(60.0),
      m_sprites()
{
    if (!m_font.loadFromFile("arial.ttf"))
    {
        throw std::runtime_error("Failed to load font");
    }
    m_frameCounter.setFont(m_font);
    m_frameCounter.setCharacterSize(24);
    m_frameCounter.setFillColor(sf::Color::White);
    m_frameCounter.setPosition(m_window.getSize().x - 150.0, 10.0);
}
GamePanel::GamePanel
(
    Player& player,
    const std::string& title,
    int width,
    int height, 
    const sf::Color& backgroundColor, 
    float frameRate,
    const std::string& fontPath
)
    : m_window(sf::VideoMode(width, height), title),
      m_player(player),
      m_backgroundColor(backgroundColor),
      m_frameRate(frameRate),
      m_sprites()
{
    if (!m_font.loadFromFile(fontPath))
    {
        throw std::runtime_error("Failed to load font");
    }
    m_frameCounter.setFont(m_font);
    m_frameCounter.setCharacterSize(24);
    m_frameCounter.setFillColor(sf::Color::White);
    m_frameCounter.setPosition(m_window.getSize().x - 150.0, 10.0);
}
void GamePanel::addSprite(const Sprite& sprite, const std::string& texturePath)
{
    m_sprites.resize(m_sprites.size() + 1);
    m_sprites[m_sprites.size() - 1]=sprite;
    m_sprites[m_sprites.size() - 1].setPosition(sprite.getSprite().getPosition().x, sprite.getSprite().getPosition().y);
    m_sprites[m_sprites.size() - 1].updateTexture(texturePath);
}
void GamePanel::removeSprite(int index)
{
    if (index < 0 || index >= (m_sprites.size()))
    {
        throw std::out_of_range("Index out of range");
    }
    m_sprites.erase(m_sprites.begin() + index);
}
void GamePanel::clearSprites()
{
    m_sprites.clear();
}
void GamePanel::updateSprite(int index, const Sprite& sprite)
{
    if (index < 0 || index >= (m_sprites.size()))
    {
        throw std::out_of_range("Index out of range");
    }
    m_sprites[index] = sprite;
}
void GamePanel::setBackgroundColor(const sf::Color& color)
{
    m_backgroundColor = color;
}
void GamePanel::setFrameCounterValue(float value)
{
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(1) << value;
    m_frameCounter.setString("FPS: " + stream.str());
}
void GamePanel::setFont(const std::string& fontPath)
{
    if (!m_font.loadFromFile("arial.ttf"))
    {
        throw std::runtime_error("Failed to load font");
    }
}

void GamePanel::setFrameRate(float framerate)
{
    m_frameRate=framerate;
}

void GamePanel::renderFrame()
{
    m_window.clear(m_backgroundColor);
    for (int i = 0; i < m_sprites.size(); ++i)
    {
        m_sprites[i].draw(m_window);
    }
    m_player.draw(m_window);
    m_window.draw(m_frameCounter);
    m_window.display();
}
void GamePanel::setWindowTitle(const std::string& title)
{
    m_window.setTitle(title);
}
void GamePanel::setWindowSize(int width, int height)
{
    m_window.setSize(sf::Vector2u(width, height));
}
bool GamePanel::isOpen()
{
    return m_window.isOpen();
}
void GamePanel::close()
{
    m_window.close();
}
bool GamePanel::pollEvent(sf::Event& event)
{
    return m_window.pollEvent(event);
}
void GamePanel::clear()
{
    m_window.clear(m_backgroundColor);
}
Player& GamePanel::getPlayer()
{
    return m_player;
}
const sf::Color GamePanel::getBackgroundColor() const
{
    return m_backgroundColor;
}
const sf::RenderWindow& GamePanel::getWindow() const
{
    return m_window;
}
const std::vector<Sprite>& GamePanel::getSprites() const
{
    return m_sprites;
}
const Sprite& GamePanel::getSprite(int index) const
{
    if (index < 0 || index >= (m_sprites.size()))
    {
        throw std::out_of_range("Index out of range");
    }
    return m_sprites[index];
}
const sf::Font& GamePanel::getFont() const
{
    return m_font;
}

const sf::Text& GamePanel::getFrameCounter() const
{
    return m_frameCounter;
}
const float GamePanel::getFrameRate() const
{
    return m_frameRate;
}
void GamePanel::checkPlayerCollision(float dt)
{
    float playerLeft = m_player.getPosX().getActual();
    float playerTop = m_player.getPosY().getActual();
    float playerRight = playerLeft + m_player.getWidth();
    float playerBottom = playerTop + m_player.getHeight();

    bool isOnGround = false; // Flag to check if the player is on the ground

    for (const auto& sprite : m_sprites)
    {
        float spriteLeft = sprite.getPosX().getActual();
        float spriteTop = sprite.getPosY().getActual();
        float spriteRight = spriteLeft + sprite.getWidth();
        float spriteBottom = spriteTop + sprite.getHeight();

        // 0. Proximity Check (Player is close to a sprite below)
        if (playerBottom <= spriteTop &&
            playerBottom + 1 >= spriteTop &&
            playerRight > spriteLeft &&
            playerLeft < spriteRight)
        {
            std::cout << "Proximity Check Passed! Player is close to sprite below. Sprite Top: " << spriteTop << ' ' << playerBottom << std::endl;
            isOnGround = true; // Player is considered on the ground
        }

        // 1. Ground Collision (Player falling onto a sprite below)
        if (m_player.getSpeedY().getActual() > 0) // Falling
        {
            if (((playerBottom >= spriteTop &&
                playerBottom <= spriteTop + (m_player.getSpeedY().getActual()+m_player.getSpeedY().getPrecedent())/2*dt)||(
                playerBottom >= spriteTop && playerBottom <= (spriteTop + spriteBottom)/2)) &&
                playerRight > spriteLeft &&
                playerLeft < spriteRight)
            {
                isOnGround = true;
                std::cout << "Ground Collision Detected! Sprite Top: " << spriteTop << std::endl;
                m_player.hitGround(spriteTop);
                break; // Stop checking after the first collision
            }
        }

        // 2. Ceiling Collision (Player jumping into a sprite above)
        if (m_player.getSpeedY().getActual() < 0) // Jumping
        {
            if (((playerTop >= spriteBottom &&
                playerTop <= spriteBottom - (m_player.getSpeedY().getActual()+m_player.getSpeedY().getPrecedent())/2*dt)||
                (playerTop <= spriteBottom  && playerTop >= (spriteTop + spriteBottom)/2)) &&
                playerRight > spriteLeft &&
                playerLeft < spriteRight)
            {
                
                m_player.hitCeiling(spriteBottom);
                break; // Stop checking after the first collision
            }
        }

        // 3. Left Wall Collision (Player moving left into a sprite)
        if (m_player.getSpeedX().getActual() < 0) // Moving left
        {
            if (((playerLeft >= spriteRight &&
                playerLeft <= spriteRight - (m_player.getSpeedX().getActual()+m_player.getSpeedX().getPrecedent())/2*dt)||
                (playerLeft <= spriteRight && playerLeft >= (spriteLeft + spriteRight)/2)) &&
                playerBottom > spriteTop &&
                playerTop < spriteBottom)
            {
                m_player.hitLeft(spriteRight);
                break; // Stop checking after the first collision
            }
        }

        // 4. Right Wall Collision (Player moving right into a sprite)
        if (m_player.getSpeedX().getActual() > 0) // Moving right
        {
            if (((playerRight <= spriteLeft &&
                playerRight >= spriteLeft - (m_player.getSpeedX().getActual()+m_player.getSpeedX().getPrecedent())/2*dt)||
                (playerRight >= spriteLeft && playerRight <= (spriteLeft + spriteRight)/2)) &&
                playerBottom > spriteTop &&
                playerTop < spriteBottom)
            {
                m_player.hitRight(spriteLeft);
                break; // Stop checking after the first collision
            }
        }
    }

    // If no sprite is directly under the player, trigger falling
    if (!isOnGround && m_player.getSpeedY().getActual() == 0)
    {
        std::cout << "No sprite under the player. Triggering fall." << std::endl;
        m_player.updateCalculationsY(DirectieY::NONE, dt, 1); // Apply gravity to make the player fall
    }
}

void GamePanel::loadSpritesFromFile(const std::string& filePath)
{
    std::ifstream in(filePath);
    if (!in.is_open())
    {
        throw std::runtime_error("Failed to open file: " + filePath);
    }

    std::string texturePath;
    int startX, startY, count;
    while (in >> texturePath >> startX >> startY >> count)
    {
        if (in.fail())
        {
            throw std::runtime_error("Invalid file format");
        }

        // Convert starting coordinates from grid to pixel positions
        float pixelX = startX * 120.0f; // Bottom-right origin
        float pixelY = m_window.getSize().y - (startY + 1) * 120.0f; // Bottom-right origin

        for (int i = 0; i < count; ++i)
        {
            Sprite sprite(texturePath, pixelX + i * 120.0f, pixelY, 120.0f, 120.0f);
            addSprite(sprite, texturePath);
        }
    }

    in.close();
}
GamePanel::~GamePanel()
{
    // Destructor implementation (needed)

}