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
void GamePanel::addCollisionlessSprite(const Sprite& sprite, const std::string& texturePath)
{
    m_collisionlessSprites.resize(m_collisionlessSprites.size() + 1);
    m_collisionlessSprites[m_collisionlessSprites.size() - 1]=sprite;
    m_collisionlessSprites[m_collisionlessSprites.size() - 1].setPosition(sprite.getSprite().getPosition().x, sprite.getSprite().getPosition().y);
    m_collisionlessSprites[m_collisionlessSprites.size() - 1].updateTexture(texturePath);
}
void GamePanel::addMovableSprite(const MovableSprite& sprite, const std::string& texturePath)
{
    m_movableSprites.resize(m_movableSprites.size() + 1);
    m_movableSprites[m_movableSprites.size() - 1]=sprite;
    m_movableSprites[m_movableSprites.size() - 1].setPosition(sprite.getSprite().getPosition().x, sprite.getSprite().getPosition().y);
    m_movableSprites[m_movableSprites.size() - 1].updateTexture(texturePath);
}
void GamePanel::removeSprite(int index)
{
    if (index < 0 || index >= (m_sprites.size()))
    {
        throw std::out_of_range("Index out of range");
    }
    m_sprites.erase(m_sprites.begin() + index);
}
void GamePanel::removeCollisionlessSprite(int index)
{
    if (index < 0 || index >= (m_collisionlessSprites.size()))
    {
        throw std::out_of_range("Index out of range");
    }
    m_collisionlessSprites.erase(m_collisionlessSprites.begin() + index);
}
void GamePanel::removeMovableSprite(int index)
{
    if (index < 0 || index >= (m_movableSprites.size()))
    {
        throw std::out_of_range("Index out of range");
    }
    m_movableSprites.erase(m_movableSprites.begin() + index);
}
void GamePanel::clearSprites()
{
    m_sprites.clear();
}
void GamePanel::clearCollisionlessSprites()
{
    m_collisionlessSprites.clear();
}
void GamePanel::clearMovableSprites()
{
    m_movableSprites.clear();
}
void GamePanel::clearAllSprites()
{
    m_sprites.clear();
    m_collisionlessSprites.clear();
    m_movableSprites.clear();
}
void GamePanel::updateSprite(int index, const Sprite& sprite)
{
    if (index < 0 || index >= (m_sprites.size()))
    {
        throw std::out_of_range("Index out of range");
    }
    m_sprites[index] = sprite;
}
void GamePanel::updateCollisionlessSprite(int index, const Sprite& sprite)
{
    if (index < 0 || index >= (m_collisionlessSprites.size()))
    {
        throw std::out_of_range("Index out of range");
    }
    m_collisionlessSprites[index] = sprite;
}
void GamePanel::updateMovableSprite(int index, const MovableSprite& sprite)
{
    if (index < 0 || index >= (m_movableSprites.size()))
    {
        throw std::out_of_range("Index out of range");
    }
    m_movableSprites[index] = sprite;
}
void GamePanel::setBackgroundColor(const sf::Color& color)
{
    m_backgroundColor = color;
}
void GamePanel::setBackgroundTexture(const std::string& texturePath)
{
    m_backgroundSprite.updateTexture(texturePath);
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
    m_window.draw(m_backgroundSprite.getSprite());
    for (int i = 0; i < m_collisionlessSprites.size(); ++i)
    {
        m_collisionlessSprites[i].draw(m_window);
    }
    for (int i = 0; i < m_sprites.size(); ++i)
    {
        m_sprites[i].draw(m_window);
    }
    for (int i = 0; i < m_movableSprites.size(); ++i)
    {
        m_movableSprites[i].draw(m_window);
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
    // Collision check for m_sprites
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
            Delta zero(0,0);
            m_player.setPlatformSpeed(zero);
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

    // Collision check for m_movableSprites
    for (const auto& sprite : m_movableSprites)
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
            m_player.setPlatformSpeed(sprite.getXSpeed());
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
    // Handle climbing above the screen
    if ((playerTop+playerBottom)/2 < 0)
    {
        std::cout << "Player climbed above the screen. Applying offset." << std::endl;
        m_verticalOffset += m_window.getSize().y; // Increase the vertical offset
        m_player.setPosition(playerLeft, m_window.getSize().y - m_player.getHeight()); // Reset player to bottom of the screen

        // Apply the offset to all sprites
        for (auto& sprite : m_sprites)
        {
            sprite.setPosition(sprite.getPosX().getActual(), sprite.getPosY().getActual() + m_window.getSize().y);
        }
        //Apply offset to all collisionless sprites
        for (auto& sprite : m_collisionlessSprites)
        {
            sprite.setPosition(sprite.getPosX().getActual(), sprite.getPosY().getActual() + m_window.getSize().y);
        }
        //Apply offset to the background sprite
        m_backgroundSprite.setPosition(m_backgroundSprite.getPosX().getActual(), m_backgroundSprite.getPosY().getActual() + m_window.getSize().y);
    }

    // Handle falling below the screen
    if ((playerBottom+playerTop)/2 > m_window.getSize().y)
    {
        std::cout << "Player fell below the screen. Removing offset." << std::endl;
        m_verticalOffset -= m_window.getSize().y; // Decrease the vertical offset
        m_player.setPosition(playerLeft, 0); // Reset player to the top of the screen

        // Apply the offset to all sprites
        for (auto& sprite : m_sprites)
        {
            sprite.setPosition(sprite.getPosX().getActual(), sprite.getPosY().getActual() - m_window.getSize().y);
        }
        //Apply offset to all collisionless sprites
        for (auto& sprite : m_collisionlessSprites)
        {
            sprite.setPosition(sprite.getPosX().getActual(), sprite.getPosY().getActual() - m_window.getSize().y);
        }
        //Apply offset to the background sprite
        m_backgroundSprite.setPosition(m_backgroundSprite.getPosX().getActual(), m_backgroundSprite.getPosY().getActual() - m_window.getSize().y);
    }
    // Handle moving beyond the left of the screen
    if ((playerLeft+playerRight)/2 < 0)
    {
        std::cout << "Player moved beyond the left side. Applying offset." << std::endl;
        m_horizontalOffset += m_window.getSize().x; // Increase the vertical offset
        m_player.setPosition(m_window.getSize().x-m_player.getWidth()/2, playerTop); // Reset player to bottom of the screen

        // Apply the offset to all sprites
        for (auto& sprite : m_sprites)
        {
            sprite.setPosition(sprite.getPosX().getActual()+m_window.getSize().x, sprite.getPosY().getActual());
        }
        //Apply offset to all collisionless sprites
        for (auto& sprite : m_collisionlessSprites)
        {
            sprite.setPosition(sprite.getPosX().getActual()+m_window.getSize().x, sprite.getPosY().getActual());
        }
        //Apply offset to the background sprite
        m_backgroundSprite.setPosition(m_backgroundSprite.getPosX().getActual()+m_window.getSize().x, m_backgroundSprite.getPosY().getActual());
    }

    // Handle moving beyond the right of the screen
    if ((playerLeft+playerRight)/2 > m_window.getSize().x)
    {
        std::cout << "Player moved beyond the right side. Removing offset." << std::endl;
        m_horizontalOffset -= m_window.getSize().x; // Decrease the vertical offset
        m_player.setPosition(0-m_player.getWidth()/2, playerTop); // Reset player to bottom of the screen

        // Apply the offset to all sprites
        for (auto& sprite : m_sprites)
        {
            sprite.setPosition(sprite.getPosX().getActual()-m_window.getSize().x, sprite.getPosY().getActual());
        }
        //Apply offset to all collisionless sprites
        for (auto& sprite : m_collisionlessSprites)
        {
            sprite.setPosition(sprite.getPosX().getActual()-m_window.getSize().x, sprite.getPosY().getActual());
        }
        //Apply offset to the background sprite
        m_backgroundSprite.setPosition(m_backgroundSprite.getPosX().getActual()-m_window.getSize().x, m_backgroundSprite.getPosY().getActual());
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
    in >> texturePath;
    if (in.fail())
    {
        throw std::runtime_error("Invalid file format");
    }
    m_backgroundSprite.updateTexture(texturePath);
    m_backgroundSprite.setDrawStatus(true);
    sf::Vector2u textureSize = m_backgroundSprite.getTexture().getSize();
    sf::Vector2u windowSize = m_window.getSize();
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    m_backgroundSprite.setScale(2 * scaleX, 2 * scaleX); // Uniform scaling
    m_backgroundSprite.setPosition(0, windowSize.y - textureSize.y * 2 * scaleX); // Set position to top-left corner
    int startX, startY, count;
    bool collision;
    while (in >> texturePath >> startX >> startY >> count >> collision)
    {
        if (in.fail())
        {
            throw std::runtime_error("Invalid file format");
        }
        // Convert starting coordinates from grid to pixel positions
        float pixelX = startX * 120.0f; // Bottom-right origin
        float pixelY = m_window.getSize().y - (startY + 1) * 120.0f; // Bottom-right origin

        if (count < 0)
        {
            count *= -1;
            for (int i = 0; i < count; ++i)
            {
                Sprite sprite(texturePath, pixelX, pixelY - i * 120.0f, 120.0f, 120.0f);
                if (collision == 1) addSprite(sprite, texturePath);
                else addCollisionlessSprite(sprite, texturePath);
            }
        }
        else
        {
            for (int i = 0; i < count; ++i)
            {
                Sprite sprite(texturePath, pixelX + i * 120.0f, pixelY, 120.0f, 120.0f);
                if (collision == 1) addSprite(sprite, texturePath);
                else addCollisionlessSprite(sprite, texturePath);
            }
        }
    }

    in.close();
}

void GamePanel::loadMovableSpritesFromFile(const std::string& filePath)
{
    std::ifstream in(filePath);
    if (!in.is_open())
    {
        throw std::runtime_error("Failed to open file: " + filePath);
    }
    std::string texturePath;
    int startX, startY, endX, endY, acceleration;
    bool collision;
    while (in >> texturePath >> startX >> startY >> endX >> endY >> acceleration >> collision)
    {
        if (in.fail())
        {
            throw std::runtime_error("Invalid file format");
        }
        // Convert starting coordinates from grid to pixel positions
        float pixelX = startX * 120.0f; // Bottom-right origin
        float pixelY = m_window.getSize().y - (startY + 1) * 120.0f; // Bottom-right origin

        float pixelEndX = endX * 120.0f; // Bottom-right origin
        float pixelEndY = m_window.getSize().y - (endY + 1) * 120.0f; // Bottom-right origin
        MovableSprite sprite(texturePath, 120.0f, 120.0f, pixelX, pixelY, pixelEndX, pixelEndY, acceleration);
        addMovableSprite(sprite, texturePath);
    }
}

void GamePanel::moveSprites(float dt)
{
    for (auto& sprite : m_movableSprites)
    {
        if (sprite.getXSpeed().getActual() == 0 && sprite.getYSpeed().getActual() == 0)
        {
            if (sprite.getXStartPoz()<sprite.getXEndPoz())
            {
                sprite.updateXSpeed(sprite.getAcceleration()*dt);
            }
            else sprite.updateXSpeed(-sprite.getAcceleration()*dt);
        }
        else if (sprite.getXStartPoz()<sprite.getXEndPoz())
        {
            if (sprite.getPosX().getActual() < (sprite.getXStartPoz() + sprite.getXEndPoz())/2)
            {
                sprite.updateXSpeed(sprite.getXSpeed().getAverage() + sprite.getAcceleration()*dt);
            }
            else if (sprite.getPosX().getActual() > (sprite.getXStartPoz() + sprite.getXEndPoz())/2)
            {
                sprite.updateXSpeed(sprite.getXSpeed().getAverage() - sprite.getAcceleration()*dt);
            }
        }
        else
        {
            if (sprite.getPosX().getActual() > (sprite.getXStartPoz() + sprite.getXEndPoz())/2)
            {
                sprite.updateXSpeed(sprite.getXSpeed().getAverage() - sprite.getAcceleration()*dt);
            }
            else if (sprite.getPosX().getActual() < (sprite.getXStartPoz() + sprite.getXEndPoz())/2)
            {
                sprite.updateXSpeed(sprite.getXSpeed().getAverage() + sprite.getAcceleration()*dt);
            }
        }
        float pozX=sprite.getPosX().getActual();
        float pozY = sprite.getPosY().getActual();
        float newPosX = pozX + sprite.getXSpeed().getAverage() * dt;
        float newPosY = pozY + sprite.getYSpeed().getAverage() * dt;
        Delta newPosXDelta(pozX, newPosX);
        Delta newPosYDelta(pozY, newPosY);
        sprite.updatePosition(newPosXDelta, newPosYDelta);
    }
}

GamePanel::~GamePanel()
{
    // Destructor implementation (needed)

}