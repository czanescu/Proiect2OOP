#include "GamePanel.h"

GamePanel::GamePanel()
    : m_window(sf::VideoMode(1920,1080), "Game Panel"),
      m_backgroundColor(sf::Color::Black),
      m_frameRate(60.0),
      m_sprites()
{
    try
    {
        m_font.loadFromFile("arial.ttf");
    }
    catch (const FileException& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
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
    const sf::Color& backgroundColor,
    const std::string& fontPath
)
    : m_player(player),
      m_backgroundColor(backgroundColor),
      m_sprites()
{
    sf::Vector2i windowSize = loadConfigFromFile(".config");
    // Create context settings
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0; // Optional: Set antialiasing level

    // Create the window with DPI scaling disabled
    m_window.create
    (
        sf::VideoMode(windowSize.x, windowSize.y), title, sf::Style::Default, settings
    );
    try
    {
        m_font.loadFromFile(fontPath);
    }
    catch (const FileException& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    m_frameCounter.setFont(m_font);
    m_frameCounter.setCharacterSize(24);
    m_frameCounter.setFillColor(sf::Color::White);
    m_frameCounter.setPosition(m_window.getSize().x - 150.0, 10.0);
}
void GamePanel::addSprite(const Sprite& sprite, const std::string& texturePath)
{
    std::cout << "Sprite-ul " << m_sprites.size() << " a fost incarcat" << std::endl;
    m_sprites.resize(m_sprites.size() + 1);

    m_sprites[m_sprites.size() - 1]=sprite;
    m_sprites[m_sprites.size() - 1].setPosition
    (
        sprite.getSprite().getPosition().x, 
        sprite.getSprite().getPosition().y
    );
    m_sprites[m_sprites.size() - 1].updateTexture(texturePath);
}
void GamePanel::addCollisionlessSprite
(
    const Sprite& sprite, 
    const std::string& texturePath
)
{
    std::cout << "Sprite-ul collissionless " << m_noColSprites.size() << " a fost incarcat" << std::endl;
    m_noColSprites.resize(m_noColSprites.size() + 1);

    m_noColSprites[m_noColSprites.size() - 1]=sprite;
    m_noColSprites[m_noColSprites.size() - 1].setPosition
    (
        sprite.getSprite().getPosition().x, 
        sprite.getSprite().getPosition().y
    );
    m_noColSprites[m_noColSprites.size() - 1].updateTexture(texturePath);
}
void GamePanel::addMovableSprite
(
    const MovableSprite& sprite, 
    const std::string& texturePath
)
{
    std::cout << "Sprite-ul movable " << m_movableSprites.size() << " a fost incarcat" << std::endl;
    m_movableSprites.resize(m_movableSprites.size() + 1);

    m_movableSprites[m_movableSprites.size() - 1]=sprite;
    m_movableSprites[m_movableSprites.size() - 1].setPosition
    (
        sprite.getSprite().getPosition().x,
        sprite.getSprite().getPosition().y
    );
    m_movableSprites[m_movableSprites.size() - 1].updateTexture(texturePath);
}
void GamePanel::addAnimatedSprite
(
    const AnimatedSprite& sprite, 
    const std::string& texturePath
)
{
    std::cout << "Sprite-ul animated " << m_animatedSprites.size() << " a fost incarcat" << std::endl;
    m_animatedSprites.resize(m_animatedSprites.size() + 1);

    m_animatedSprites[m_animatedSprites.size() - 1]=sprite;
    m_animatedSprites[m_animatedSprites.size() - 1].setPosition
    (
        sprite.getSprite().getPosition().x, 
        sprite.getSprite().getPosition().y
    );
    m_animatedSprites[m_animatedSprites.size() - 1].updateTextures(texturePath);
}
void GamePanel::removeSprite(int index)
{
    try
    {
        IndexOutOfRangeException(index, m_sprites.size());
    }
    catch (const IndexOutOfRangeException& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    m_sprites.erase(m_sprites.begin() + index);
}
void GamePanel::removeCollisionlessSprite(int index)
{
    try
    {
        IndexOutOfRangeException(index, m_noColSprites.size());
    }
    catch (const IndexOutOfRangeException& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    m_noColSprites.erase(m_noColSprites.begin() + index);
}
void GamePanel::removeMovableSprite(int index)
{
    try
    {
        IndexOutOfRangeException(index, m_movableSprites.size());
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error:" << e.what() << '\n';
    }
    
    m_movableSprites.erase(m_movableSprites.begin() + index);
}
void GamePanel::clearSprites()
{
    m_sprites.clear();
}
void GamePanel::clearCollisionlessSprites()
{
    m_noColSprites.clear();
}
void GamePanel::clearMovableSprites()
{
    m_movableSprites.clear();
}
void GamePanel::clearAllSprites()
{
    m_sprites.clear();
    m_noColSprites.clear();
    m_movableSprites.clear();
}
void GamePanel::updateSprite(int index, const Sprite& sprite)
{
    try
    {
        IndexOutOfRangeException(index, m_sprites.size());
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
    }
    
    m_sprites[index] = sprite;
}
void GamePanel::updateCollisionlessSprite(int index, const Sprite& sprite)
{
    try
    {
        IndexOutOfRangeException(index, m_noColSprites.size());
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
    }
    m_noColSprites[index] = sprite;
}
void GamePanel::updateMovableSprite(int index, const MovableSprite& sprite)
{
    try
    {
        IndexOutOfRangeException(index, m_movableSprites.size());
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
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
    try
    {
        m_font.loadFromFile(fontPath);
    }
    catch (const FileException& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
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
    for (int i = 0; i < m_noColSprites.size(); ++i)
    {
        m_noColSprites[i].draw(m_window);
    }
    for (int i = 0; i < m_sprites.size(); ++i)
    {
        m_sprites[i].draw(m_window);
    }
    for (int i = 0; i < m_movableSprites.size(); ++i)
    {
        m_movableSprites[i].draw(m_window);
    }
    for (int i = 0; i < m_animatedSprites.size(); ++i)
    {
        m_animatedSprites[i].draw(m_window);
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
    try
    {
        IndexOutOfRangeException(index, m_sprites.size());
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
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
void GamePanel::checkPlayerCollision(float dt, float scaleY)
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
            std::cout 
            << "Proximity Check Passed!"
            << "Player is close to sprite below. Sprite Top: " 
            << spriteTop << ' ' << playerBottom << std::endl;
            isOnGround = true; // Player is considered on the ground
            Delta zero(0,0);
            m_player.setPlatformSpeed(zero,zero);
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
                std::cout << "Ground Collision Detected! Sprite Top: " 
                << spriteTop << std::endl;
                m_player.hitGround(spriteTop);
                break; // Stop checking after the first collision
            }
        }

        // 2. Ceiling Collision (Player jumping into a sprite above)
        if (m_player.getSpeedY().getActual() < 0) // Jumping
        {
            if(((playerTop >= spriteBottom &&
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
        if 
        (
            m_player.getSpeedX().getActual() < 0 || 
            m_player.getXPlatformSpeed().getActual() < 0
        ) // Moving left
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
        if 
        (
            m_player.getSpeedX().getActual() > 0 || 
            m_player.getXPlatformSpeed().getActual() > 0
        ) // Moving right
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
            playerLeft < spriteRight
            || ( playerBottom -1 <= spriteTop &&
            playerBottom + 1 >= spriteTop &&
            playerRight > spriteLeft &&
            playerLeft < spriteRight))
        {
            std::cout 
            << "Proximity Check Passed!"
            << " Player is close to sprite below. Sprite Top: "
            << spriteTop << ' ' << playerBottom << std::endl;
            isOnGround = true; // Player is considered on the ground
            m_player.setPlatformSpeed(sprite.getXSpeed(), sprite.getYSpeed());
        }

        // 1. Ground Collision (Player falling onto a sprite below)
        if 
        (
            m_player.getSpeedY().getActual() > 0 || 
            m_player.getYPlatformSpeed().getActual() != 0
        ) // Falling
        {
            if (playerBottom >= spriteTop && 
                playerBottom <= (spriteTop + spriteBottom)/2 &&
                playerRight > spriteLeft &&
                playerLeft < spriteRight)
            {
                isOnGround = true;
                std::cout 
                << "Ground Collision Detected! Sprite Top: " 
                << spriteTop << std::endl;
                m_player.hitGround(spriteTop);
                break; // Stop checking after the first collision
            }
        }

        // 2. Ceiling Collision (Player jumping into a sprite above)
        if (m_player.getSpeedY().getActual() < 0) // Jumping
        {
            if (playerTop <= spriteBottom && 
                playerTop >= (spriteTop + spriteBottom)/2 &&
                playerRight > spriteLeft &&
                playerLeft < spriteRight)
            {
                
                m_player.hitCeiling(spriteBottom);
                break; // Stop checking after the first collision
            }
        }

        // 3. Left Wall Collision (Player moving left into a sprite, or sprite moving right)
        if (m_player.getSpeedX().getActual() < 0) // Moving left
        {
            if (playerLeft <= spriteRight && 
                playerLeft >= (spriteLeft + spriteRight)/2 &&
                playerBottom > spriteTop &&
                playerTop < spriteBottom)
            {
                m_player.hitLeft(spriteRight);
                break; // Stop checking after the first collision
            }
        }
        if (sprite.getXSpeed().getActual() > 0)
        {
            if (playerLeft <= spriteRight && 
                playerLeft >= (spriteLeft + spriteRight)/2 &&
                playerBottom > spriteTop &&
                playerTop < spriteBottom)
            {
                m_player.setPlatformSpeed(sprite.getXSpeed(), sprite.getYSpeed());
                break; // Stop checking after the first collision
            }
        }

        // 4. Right Wall Collision (Player moving right into a sprite, or sprite moving left)
        if (m_player.getSpeedX().getActual() > 0) // Moving right
        {
            if (playerRight >= spriteLeft && 
                playerRight <= (spriteLeft + spriteRight)/2 &&
                playerBottom > spriteTop &&
                playerTop < spriteBottom)
            {
                m_player.hitRight(spriteLeft);
                break; // Stop checking after the first collision
            }
        }
        if (sprite.getXSpeed().getActual() < 0) //Sprite moving left
        {
            if (playerRight >= spriteLeft && 
                playerRight <= (spriteLeft + spriteRight)/2 &&
                playerBottom > spriteTop &&
                playerTop < spriteBottom)
            {
                m_player.setPlatformSpeed(sprite.getXSpeed(), sprite.getYSpeed());
                break;
            }
        }
    }

    // If no sprite is directly under the player, trigger falling
    if (!isOnGround && m_player.getSpeedY().getActual() == 0)
    {
        std::cout << "No sprite under the player. Triggering fall.";
        std::cout << std::endl;
        // Apply gravity to make the player fall
        m_player.updateCalculationsY(DirectieY::NONE, dt, scaleY, 1);
        Delta zero(0,0);
        m_player.setPlatformSpeed(m_player.getXPlatformSpeed(), zero);
    }
    // Handle climbing above the screen
    if ((playerTop+playerBottom)/2 < 0)
    {
        moveScreenUp(playerLeft);
    }
    // Handle falling below the screen
    if ((playerBottom+playerTop)/2 > m_window.getSize().y)
    {
        moveScreenDown(playerLeft);
    }
    // Handle moving beyond the left of the screen
    if ((playerLeft+playerRight)/2 < 0)
    {
        moveScreenLeft(playerTop);
    }
    // Handle moving beyond the right of the screen
    if ((playerLeft+playerRight)/2 > m_window.getSize().x)
    {
        moveScreenRight(playerTop);
    }
}

sf::Vector2i GamePanel::loadConfigFromFile(const std::string& filePath)
{
    try
    {
        FileException checker(filePath);
    }
    catch(const BaseException& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::ifstream in (filePath);
    std::string line;
    sf::Vector2i windowSize; 
    while (std::getline(in, line))
    {
        // Ignore empty lines or lines without '='
        if (line.empty() || line.find('=') == std::string::npos)
            continue;

        // Split the line into key and value
        std::istringstream lineStream(line);
        std::string key, value;
        if 
        (
            std::getline(lineStream, key, '=') && 
            std::getline(lineStream, value)
        )
        {
            // Trim whitespace from key and value
            key.erase(key.find_last_not_of(" \t") + 1);
            key.erase(0, key.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));

            // Parse the key-value pairs
            if (key == "FRAME_RATE")
            {
                m_frameRate = std::stof(value); // Convert to float
            }
            else if (key == "X_RESOLUTION")
            {
                windowSize = sf::Vector2i(std::stof(value), windowSize.y);
            }
            else if (key == "Y_RESOLUTION")
            {
                windowSize = sf::Vector2i(windowSize.x, std::stof(value));
            }
        }
    }

    in.close();
    return windowSize;
}


void GamePanel::loadSpritesFromFile(const std::string& filePath)
{
    try {
        // Use FileException to validate the file
        FileException checker(filePath);
    } catch (const BaseException& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return; // Exit the function if the file cannot be opened
    }
    std::ifstream in(filePath);

    std::string path, texturePath;
    in >> path >> texturePath;
    if (path == "/") path = "";

    // Update background sprite
    m_backgroundSprite.updateTexture(path + texturePath);
    m_backgroundSprite.setDrawStatus(true);

    // Calculate scaling factors for the background
    sf::Vector2u windowSize = m_window.getSize();
    sf::Vector2u textureSize = m_backgroundSprite.getTexture().getSize();
    float backgroundScale = static_cast<float>(windowSize.x * 2.f) / (textureSize.x); // Twice the width of the background

    // Apply scaling to the background sprite
    m_backgroundSprite.setScale(backgroundScale, backgroundScale);
    m_backgroundSprite.setPosition(0, windowSize.y - (textureSize.y * backgroundScale));
    std::cout << "Background loaded" << std::endl;

    // Calculate scaling factors for sprites and the player
    const float referenceWidth = 1920.0f;
    const float referenceHeight = 1080.0f;
    float spriteScaleX = static_cast<float>(windowSize.x) / referenceWidth;
    float spriteScaleY = static_cast<float>(windowSize.y) / referenceHeight;

    // Load player initial position
    int startX, startY, count;
    bool collision;
    in >> startX >> startY;
    m_player.setPosition(
        startX * 120.0f * spriteScaleX, 
        windowSize.y - (startY + 1) * 120.0f * spriteScaleY
    );
    float playerScaleX = windowSize.x / referenceWidth * m_player.getScaleX();
    float playerScaleY = windowSize.y / referenceHeight * m_player.getScaleY();
    m_player.setScale(playerScaleX, playerScaleY);
    m_player.setHitBox(100.0f * spriteScaleX, 100.0f * spriteScaleY);

    // Load other sprites
    while (in >> texturePath >> startX >> startY >> count >> collision)
    {
        // Convert starting coordinates from grid to pixel positions
        float pixelX = startX * 120.0f * spriteScaleX;
        float pixelY = windowSize.y - (startY + 1) * 120.0f * spriteScaleY;

        if (count < 0)
        {
            count *= -1;
            for (int i = 0; i < count; ++i)
            {
                Sprite sprite(
                    path + texturePath,
                    pixelX,
                    pixelY - i * 120.0f * spriteScaleY,
                    120.0f * spriteScaleY,
                    120.0f * spriteScaleX
                );
                if (collision == 1)
                    addSprite(sprite, path + texturePath);
                else
                    addCollisionlessSprite(sprite, path + texturePath);
            }
        }
        else
        {
            for (int i = 0; i < count; ++i)
            {
                Sprite sprite(
                    path + texturePath,
                    pixelX + i * 120.0f * spriteScaleX,
                    pixelY,
                    120.0f * spriteScaleY,
                    120.0f * spriteScaleX
                );
                if (collision == 1)
                    addSprite(sprite, path + texturePath);
                else
                    addCollisionlessSprite(sprite, path + texturePath);
            }
        }
    }

    in.close();
}

void GamePanel::loadMovableSpritesFromFile(const std::string& filePath)
{
    try
    {
        FileException checker(filePath);
    }
    catch (const BaseException& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return; // Exit the function if the file cannot be opened
    }
    std::ifstream in(filePath);

    std::string path, texturePath;
    in >> path;
    if (path == "/") path = "";

    int startX, startY, endX, endY, acceleration;
    bool collision = 1;
    sf::Vector2u windowSize = m_window.getSize();
    const float referenceWidth = 1920.0f;
    const float referenceHeight = 1080.0f;
    float spriteScaleX = static_cast<float>(windowSize.x) / referenceWidth;
    float spriteScaleY = static_cast<float>(windowSize.y) / referenceHeight;

    while (in >> texturePath >> startX >> startY >> endX >> endY >> acceleration)
    {
        // Convert starting and ending coordinates from grid to pixel positions
        float pixelX = startX * 120.0f * spriteScaleX;
        float pixelY = windowSize.y - (startY + 1) * 120.0f * spriteScaleY;
        float pixelEndX = endX * 120.0f * spriteScaleX;
        float pixelEndY = windowSize.y - (endY + 1) * 120.0f * spriteScaleY;

        // Create and add the movable sprite
        MovableSprite sprite(
            path + texturePath,
            120.0f * spriteScaleY, // Width
            120.0f * spriteScaleX, // Height
            pixelX,
            pixelY,
            pixelEndX,
            pixelEndY,
            acceleration
        );

        addMovableSprite(sprite, path + texturePath);
    }

    in.close();
}

void GamePanel::loadAnimatedSpritesFromFile(const std::string& filePath)
{
    try
    {
        FileException checker(filePath);
    }
    catch (const BaseException& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return; // Exit the function if the file cannot be opened
    }
    std::ifstream in(filePath);

    std::string path, texturePath;
    in >> path;
    if (path == "/") path = "";

    int x, y, textureCount, frameDuration;
    sf::Vector2u windowSize = m_window.getSize();
    const float referenceWidth = 1920.0f;
    const float referenceHeight = 1080.0f;
    float spriteScaleX = static_cast<float>(windowSize.x) / referenceWidth;
    float spriteScaleY = static_cast<float>(windowSize.y) / referenceHeight;

    while (in >> texturePath >> x >> y >> textureCount >> frameDuration)
    {

        // Convert starting coordinates from grid to pixel positions
        float pixelX = x * 120.0f * spriteScaleX;
        float pixelY = windowSize.y - (y + 1) * 120.0f * spriteScaleY;

        // Create and add the animated sprite
        AnimatedSprite sprite(
            path + texturePath,
            pixelX,
            pixelY,
            120.0f * spriteScaleY, // Width
            120.0f * spriteScaleX, // Height
            textureCount,
            frameDuration
        );

        addAnimatedSprite(sprite, path + texturePath);
    }

    in.close();
}

void GamePanel::moveSprites(float dt)
{
    for (auto& sprite : m_movableSprites)
    {
        bool not_movingX = false;
        bool not_movingY = false;
        if (sprite.getXStartPoz() == sprite.getXEndPoz())
        {
            sprite.setPosition
            (
                sprite.getXStartPoz(), 
                sprite.getPosY().getActual()
            );
            not_movingX = true;
        }
        if (sprite.getYStartPoz() == sprite.getYEndPoz())
        {
            sprite.setPosition
            (
                sprite.getPosX().getActual(), 
                sprite.getYStartPoz()
            );
            not_movingY = true;
        }
        // calculez acceleratia pe Y
        float distantaX = sprite.getXEndPoz() - sprite.getXStartPoz();
        float distantaY = sprite.getYEndPoz() - sprite.getYStartPoz();
        float acceleratieX = sprite.getAcceleration();
        float acceleratieY = -acceleratieX * distantaY / distantaX;
        //calcule pentru X si Y
        if 
        (
            sprite.getXSpeed().getActual() == 0 && 
            sprite.getYSpeed().getActual() == 0
        )
        {
            if (sprite.getXStartPoz()<sprite.getXEndPoz())
            {
                sprite.updateXSpeed(acceleratieX*dt);
            }
            else sprite.updateXSpeed(-acceleratieX*dt);
            if (sprite.getYStartPoz()<sprite.getYEndPoz())
            {
                sprite.updateYSpeed(acceleratieY*dt);
            }
            else sprite.updateYSpeed(-acceleratieY*dt);
        }
        else
        {
            //calcule pentru X
            if (!not_movingX)
            {
                if (sprite.getXStartPoz()<sprite.getXEndPoz())
                {
                    if 
                    (
                        sprite.getPosX().getActual() < 
                        (sprite.getXStartPoz() + sprite.getXEndPoz())/2
                    )
                    {
                        sprite.updateXSpeed
                        (
                            sprite.getXSpeed().getAverage() + 
                            acceleratieX*dt
                        );
                    }
                    else if 
                    (
                        sprite.getPosX().getActual() > 
                        (sprite.getXStartPoz() + sprite.getXEndPoz())/2
                    )
                    {
                        sprite.updateXSpeed
                        (
                            sprite.getXSpeed().getAverage() - 
                            acceleratieX*dt
                        );
                    }
                }
                else
                {
                    if 
                    (
                        sprite.getPosX().getActual() > 
                        (sprite.getXStartPoz() + sprite.getXEndPoz())/2
                    )
                    {
                        sprite.updateXSpeed
                        (
                            sprite.getXSpeed().getAverage() - 
                            acceleratieX*dt
                        );
                    }
                    else if 
                    (
                        sprite.getPosX().getActual() < 
                        (sprite.getXStartPoz() + sprite.getXEndPoz())/2
                    )
                    {
                        sprite.updateXSpeed
                        (
                            sprite.getXSpeed().getAverage() + 
                            acceleratieX*dt
                        );
                    }
                }
            }
            //calcule pentru Y
            if (!not_movingY)
            {
                if (sprite.getYStartPoz()<sprite.getYEndPoz())
                {
                    if 
                    (
                        sprite.getPosY().getActual() < 
                        (sprite.getYStartPoz() + sprite.getYEndPoz())/2
                    )
                    {
                        sprite.updateYSpeed
                        (
                            sprite.getYSpeed().getAverage() + 
                            acceleratieY*dt
                        );
                    }
                    else if 
                    (
                        sprite.getPosY().getActual() > 
                        (sprite.getYStartPoz() + sprite.getYEndPoz())/2
                    )
                    {
                        sprite.updateYSpeed
                        (
                            sprite.getYSpeed().getAverage() - 
                            acceleratieY*dt
                        );
                    }
                }
                else
                {
                    if 
                    (
                        sprite.getPosY().getActual() > 
                        (sprite.getYStartPoz() + sprite.getYEndPoz())/2
                    )
                    {
                        sprite.updateYSpeed
                        (
                            sprite.getYSpeed().getAverage() - 
                            acceleratieY*dt
                        );
                    }
                    else if 
                    (
                        sprite.getPosY().getActual() < 
                        (sprite.getYStartPoz() + sprite.getYEndPoz())/2
                    )
                    {
                        sprite.updateYSpeed
                        (
                            sprite.getYSpeed().getAverage() + 
                            acceleratieY*dt
                        );
                    }
                }
            }
        }
        float pozX=sprite.getPosX().getActual();
        float pozY = sprite.getPosY().getActual();
        float newPosX = pozX + sprite.getXSpeed().getActual() * dt;
        float newPosY = pozY + sprite.getYSpeed().getActual() * dt;
        Delta newPosXDelta(pozX, newPosX);
        Delta newPosYDelta(pozY, newPosY);
        sprite.updatePosition(newPosXDelta, newPosYDelta);
    }
}

void GamePanel::moveScreenUp(float playerLeft){
    std::cout << "Player climbed above the screen. Applying offset.";
    std::cout << std::endl;
    // Increase the vertical offset
    m_verticalOffset += m_window.getSize().y;
    // Reset player to bottom of the screen
    m_player.setPosition
    (
        playerLeft, 
        m_window.getSize().y - m_player.getHeight()
    ); 

    // Apply the offset to all sprites
    for (auto& sprite : m_sprites)
    {
        sprite.setPosition
        (
            sprite.getPosX().getActual(), 
            sprite.getPosY().getActual() + m_window.getSize().y
        );
    }
    //Apply offset to all collisionless sprites
    for (auto& sprite : m_noColSprites)
    {
        sprite.setPosition
        (
            sprite.getPosX().getActual(), 
            sprite.getPosY().getActual() + m_window.getSize().y
        );
    }
    //Apply offset to all movable sprites
    for (auto& sprite : m_movableSprites)
    {
        sprite.setPosition
        (
            sprite.getPosX().getActual(), 
            sprite.getPosY().getActual() + m_window.getSize().y
        );
        sprite.setYStartPoz(sprite.getYStartPoz() + m_window.getSize().y);
        sprite.setYEndPoz(sprite.getYEndPoz() + m_window.getSize().y);
    }
    //Apply offset to all animated sprites
    for (auto& sprite : m_animatedSprites)
    {
        sprite.setPosition
        (
            sprite.getPosX().getActual(), 
            sprite.getPosY().getActual() + m_window.getSize().y
        );
    }
    //Apply offset to the background sprite
    m_backgroundSprite.setPosition
    (
        m_backgroundSprite.getPosX().getActual(), 
        m_backgroundSprite.getPosY().getActual() + m_window.getSize().y
    );
}

void GamePanel::moveScreenDown(float playerLeft)
{
    std::cout << "Player fell below the screen. Removing offset.";
    std::cout << std::endl;
    // Decrease the vertical offset
    m_verticalOffset -= m_window.getSize().y;
    // Reset player to the top of the screen 
    m_player.setPosition(playerLeft, 0); 

    // Apply the offset to all sprites
    for (auto& sprite : m_sprites)
    {
        sprite.setPosition
        (
            sprite.getPosX().getActual(), 
            sprite.getPosY().getActual() - m_window.getSize().y
        );
    }
    //Apply offset to all collisionless sprites
    for (auto& sprite : m_noColSprites)
    {
        sprite.setPosition
        (
            sprite.getPosX().getActual(),
            sprite.getPosY().getActual() - m_window.getSize().y
        );
    }
    //Apply offset to all movable sprites
    for (auto& sprite : m_movableSprites)
    {
        sprite.setPosition
        (
            sprite.getPosX().getActual(), 
            sprite.getPosY().getActual() - m_window.getSize().y
        );
        sprite.setYStartPoz(sprite.getYStartPoz() - m_window.getSize().y);
        sprite.setYEndPoz(sprite.getYEndPoz() - m_window.getSize().y);
    }
    //Apply offset to all animated sprites
    for (auto& sprite : m_animatedSprites)
    {
        sprite.setPosition
        (
            sprite.getPosX().getActual(), 
            sprite.getPosY().getActual() - m_window.getSize().y
        );
    }
    //Apply offset to the background sprite
    m_backgroundSprite.setPosition
    (
        m_backgroundSprite.getPosX().getActual(), 
        m_backgroundSprite.getPosY().getActual() - m_window.getSize().y
    );
}

void GamePanel::moveScreenLeft(float playerTop)
{
    std::cout << "Player moved beyond the left side. Applying offset.";
    std::cout << std::endl;
    m_horizontalOffset += m_window.getSize().x; // Increase the vertical offset
    m_player.setPosition
    (
        m_window.getSize().x-m_player.getWidth()/2, 
        playerTop
    ); // Reset player to bottom of the screen

    // Apply the offset to all sprites
    for (auto& sprite : m_sprites)
    {
        sprite.setPosition
        (
            sprite.getPosX().getActual()+m_window.getSize().x, 
            sprite.getPosY().getActual()
        );
    }
    //Apply offset to all collisionless sprites
    for (auto& sprite : m_noColSprites)
    {
        sprite.setPosition
        (
            sprite.getPosX().getActual()+m_window.getSize().x, 
            sprite.getPosY().getActual()
        );
    }
    //Apply offset to all movable sprites
    for (auto& sprite : m_movableSprites)
    {
        sprite.setPosition
        (
            sprite.getPosX().getActual()+m_window.getSize().x, 
            sprite.getPosY().getActual()
        );
        sprite.setXStartPoz(sprite.getXStartPoz() + m_window.getSize().x);
        sprite.setXEndPoz(sprite.getXEndPoz() + m_window.getSize().x);
    }
    //Apply offset to all animated sprites
    for (auto& sprite : m_animatedSprites)
    {
        sprite.setPosition
        (
            sprite.getPosX().getActual()+m_window.getSize().x, 
            sprite.getPosY().getActual()
        );
    }
    //Apply offset to the background sprite
    m_backgroundSprite.setPosition
    (
        m_backgroundSprite.getPosX().getActual()+m_window.getSize().x, 
        m_backgroundSprite.getPosY().getActual()
    );
}

void GamePanel::moveScreenRight(float playerTop)
{
    std::cout << "Player moved beyond the right side. Removing offset.";
    std::cout << std::endl;
    m_horizontalOffset -= m_window.getSize().x; // Decrease the vertical offset
    m_player.setPosition
    (
        0-m_player.getWidth()/2, 
        playerTop
    ); // Reset player to bottom of the screen

    // Apply the offset to all sprites
    for (auto& sprite : m_sprites)
    {
        sprite.setPosition
        (
            sprite.getPosX().getActual()-m_window.getSize().x, 
            sprite.getPosY().getActual()
        );
    }
    //Apply offset to all collisionless sprites
    for (auto& sprite : m_noColSprites)
    {
        sprite.setPosition
        (
            sprite.getPosX().getActual()-m_window.getSize().x, 
           sprite.getPosY().getActual()
        );
    }
    //Apply offset to all movable sprites
    for (auto& sprite : m_movableSprites)
    {
        sprite.setPosition
        (
            sprite.getPosX().getActual()-m_window.getSize().x, 
            sprite.getPosY().getActual()
        );
        sprite.setXStartPoz(sprite.getXStartPoz() - m_window.getSize().x);
        sprite.setXEndPoz(sprite.getXEndPoz() - m_window.getSize().x);
    }
    //Apply offset to all animated sprites
    for (auto& sprite : m_animatedSprites)
    {
        sprite.setPosition
        (
            sprite.getPosX().getActual()-m_window.getSize().x, 
            sprite.getPosY().getActual()
        );
    }
    //Apply offset to the background sprite
    m_backgroundSprite.setPosition
    (
        m_backgroundSprite.getPosX().getActual()-m_window.getSize().x, 
        m_backgroundSprite.getPosY().getActual()
    );
}

void GamePanel::panelSleep(float seconds)
{
    #if defined(Win32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
        Sleep(0); // Sleep for the specified number of seconds
    #else
        std::this_thread::sleep_for(std::chrono::duration<double>(seconds));
    #endif
}

GamePanel::~GamePanel()
{
    // Destructor implementation (needed)

}