#include "GamePanel.hpp"

GamePanel::GamePanel() // Constructor gol
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
    try
    {
        FileException checker("assets/Loading.png");
    }
    catch(const FileException& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    m_loadingScreenBackground.updateTexture("assets/Loading.png");
}
GamePanel::GamePanel // Constructor
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
        sf::VideoMode(windowSize.x, windowSize.y), 
        title, 
        sf::Style::Default, 
        settings
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
    try
    {
        FileException checker("assets/Loading.png");
    }
    catch(const FileException& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    m_loadingScreenBackground.updateTexture("assets/Loading.png");
}
void GamePanel::addSprite // metoda care adauga un sprite
(
    std::unique_ptr<I_Sprite> sprite, 
    const std::string& texturePath, 
    bool collision
)
{
    // cod pentru debugging
    std::cout << "Sprite-ul (" << m_sprites.size() << "/";
    std::cout << m_player.getSpriteCount() << ") a fost incarcat" << std::endl;
    // lungesc bara de progres (add sprite se intampla doar atunci cand se
    // incarca sprite-uri din fisier)
    m_player.raiseSpriteProgress(1);
    renderProgressBar();
    m_sprites.push_back(std::move(sprite));
    m_sprites[m_sprites.size() - 1]->setCollision(collision);
    m_sprites[m_sprites.size() - 1]->setDrawStatus(true);
    // sprite-urile animate trebuie tratate diferit
    AnimatedSprite* animatedS = dynamic_cast<AnimatedSprite*>(sprite.get());
    if (animatedS)
    {
        m_sprites[m_sprites.size() - 1]->updateTextures(texturePath);
    }
    else
    {
        m_sprites[m_sprites.size() - 1]->updateTexture(texturePath);
    }
}

// cod pentru eventuala stergere a sprite-urilor (deocamdata nu e folosit)
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

// cod pentru eventuala stergere a sprite-urilor (deocamdata nu e folosit)
// ar putea fi folosit daca adaug mai multe niveluri
void GamePanel::clearSprites()
{
    m_sprites.clear();
}

void GamePanel::updateSprite(int index, std::unique_ptr<I_Sprite> sprite)
{
    try
    {
        IndexOutOfRangeException(index, m_sprites.size());
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
    }
    m_sprites[index] = std::move(sprite);
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

void GamePanel::endProgram()
{
    m_window.close();
    std::exit(0);
}

// meniul de pauza
void GamePanel::pauseMenu()
{
    float windowHeight = m_window.getSize().y;
    float windowWidth = m_window.getSize().x;
    float spriteWidth = windowWidth / 4;
    float spriteHeight = windowHeight / 10;
    float largeSpriteWidth = spriteWidth * 1.1f;
    float largeSpriteHeight = spriteHeight * 1.1f;
    Sprite pauseMenuBackground;
    pauseMenuBackground.updateTexture("assets/pauseMenu.png");
    pauseMenuBackground.setScale
    (
        windowWidth / pauseMenuBackground.getTexture().getSize().x, 
        windowHeight / pauseMenuBackground.getTexture().getSize().y
    );
    Sprite Exit, Continue;
    Exit.updateTexture("assets/exit.png");
    Continue.updateTexture("assets/continue.png");
    Exit.setScale
    (
        spriteWidth / Exit.getTexture().getSize().x, 
        spriteHeight / Exit.getTexture().getSize().y
    );
    Continue.setScale
    (
        spriteWidth / Continue.getTexture().getSize().x, 
        spriteHeight / Continue.getTexture().getSize().y
    );
    Exit.setPosition
    (
        windowWidth / 2 - spriteWidth / 2, 
        windowHeight / 2 - spriteHeight / 2
    );
    Continue.setPosition
    (
        windowWidth / 2 - spriteWidth / 2, 
        windowHeight / 2 - spriteHeight / 2 + spriteHeight * 1.5
    );
    MenuSelection menuSelection = CONTINUE;
    auto startTime = std::chrono::high_resolution_clock::now();
    while (1)
    {
        if (menuSelection == EXIT)
        {
            Exit.setScale
            (
                spriteWidth / Exit.getTexture().getSize().x * 1.1f, 
                spriteHeight / Exit.getTexture().getSize().y * 1.1f
            );
            Exit.setPosition
            (
                windowWidth / 2 - largeSpriteWidth / 2, 
                windowHeight / 2 - largeSpriteHeight / 2 + spriteHeight * 1.5f
            );
            Continue.setScale
            (
                spriteWidth / Continue.getTexture().getSize().x, 
                spriteHeight / Continue.getTexture().getSize().y
            );
            Continue.setPosition
            (
                windowWidth / 2 - spriteWidth / 2, 
                windowHeight / 2 - spriteHeight / 2
            );
        }
        else
        {
            Continue.setScale
            (
                spriteWidth / Continue.getTexture().getSize().x * 1.1f, 
                spriteHeight / Continue.getTexture().getSize().y * 1.1f
            );
            Continue.setPosition
            (
                windowWidth / 2 - largeSpriteWidth / 2, 
                windowHeight / 2 - largeSpriteHeight / 2
            );
            Exit.setScale
            (
                spriteWidth / Exit.getTexture().getSize().x, 
                spriteHeight / Exit.getTexture().getSize().y
            );
            Exit.setPosition
            (
                windowWidth / 2 - spriteWidth / 2, 
                windowHeight / 2 - spriteHeight / 2 + spriteHeight * 1.5f
            );
        }
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                m_window.close();
                std::exit(0);
            }
            if (event.type == sf::Event::KeyPressed ||
                event.type == sf::Event::JoystickMoved ||
                event.type == sf::Event::JoystickButtonPressed)
            {
                auto now = std::chrono::high_resolution_clock::now();
                auto elapsedTime = std::chrono::duration_cast
                    <std::chrono::milliseconds>(now - startTime);
                if ((event.key.code == sf::Keyboard::Escape ||
                    sf::Joystick::isButtonPressed(0, 9)) &&
                    elapsedTime.count() > 1000)
                    return;
                if (event.key.code == sf::Keyboard::Up ||
                    sf::Joystick::getAxisPosition
                    (0, static_cast<sf::Joystick::Axis>(7)) < -20)
                {
                    --menuSelection;
                }
                if (event.key.code == sf::Keyboard::Down ||
                    sf::Joystick::getAxisPosition
                    (0, static_cast<sf::Joystick::Axis>(7)) > 20)
                {
                    ++menuSelection;
                }
                if (event.key.code == sf::Keyboard::Enter ||
                    sf::Joystick::isButtonPressed(0, 0))
                {
                    if (menuSelection == MenuSelection::EXIT)
                    {
                        m_window.close();
                        std::exit(0);
                    }
                    else
                    {
                        return;
                    }
                }
            }
        }

        m_window.clear(m_backgroundColor);
        pauseMenuBackground.draw(m_window);
        Exit.draw(m_window);
        Continue.draw(m_window);
        m_window.display();
    }
}

void GamePanel::renderProgressBar()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        // cod pentru a permite x-ului din dreapta sus sa inchida fereastra
        if ((event.type == sf::Event::Closed)
        || event.type == sf::Event::KeyPressed
        && event.key.code == sf::Keyboard::Escape)
            endProgram();
    }
    float barWidth = 640.f * (m_window.getSize().x / 1920.f);
    float barHeight = 20.f * (m_window.getSize().y / 1080.f);
    float progress = static_cast<float>(m_player.getSpriteProgress()) 
                     / m_player.getSpriteCount();
    sf::RectangleShape outline(sf::Vector2f(barWidth+10.f, barHeight+10.f));
    sf::RectangleShape progressBar(sf::Vector2f(barWidth, barHeight));
    sf::Text progressText;
    progressText.setFont(m_font);
    progressText.setCharacterSize(24);
    progressText.setFillColor(sf::Color::White);
    progressText.setString
    (
        std::to_string(static_cast<int>(progress * 100)) + "%"
    );
    progressBar.setFillColor(sf::Color::Green);
    outline.setFillColor(sf::Color::White);
    progressBar.setPosition
    (
        m_window.getSize().x / 2 - barWidth / 2, 
        m_window.getSize().y / 3 * 2 - barHeight
            - 10.f * (m_window.getSize().y / 1080.f)
    );
    outline.setPosition
    (
        m_window.getSize().x / 2 - barWidth / 2 - 5.f, 
        m_window.getSize().y / 3 * 2 - barHeight 
            - 10.f * (m_window.getSize().y / 1080.f) - 5.f
    );
    progressText.setPosition
    (
        m_window.getSize().x / 2 - barWidth / 2 + barWidth / 2 - 20.f, 
        m_window.getSize().y / 3 * 2 - barHeight * 3 
            - 10.f * (m_window.getSize().y / 1080.f) - 5.f
    );
    progressBar.setScale(progress, 1.f);
    outline.setScale(1.f, 1.f);
    m_window.clear(m_backgroundColor);
    m_window.draw(m_loadingScreenBackground.getSprite());
    m_window.draw(outline);
    m_window.draw(progressBar);
    m_window.draw(progressText);
    m_window.display();
}

// metoda care randeaza un frame
void GamePanel::renderFrame()
{
    m_window.clear(m_backgroundColor);
    m_window.draw(m_backgroundSprite.getSprite());
    for (int i = 0; i < m_sprites.size(); ++i)
    {
        m_sprites[i]->draw(m_window);
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
const I_Sprite& GamePanel::getSprite(int index) const
{
    try
    {
        IndexOutOfRangeException(index, m_sprites.size());
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return *m_sprites[index];
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
// metoda care calculeaza numarul de sprite-uri
// (in variabila statica m_spriteCount)
const void GamePanel::calculateSpriteCount(const std::string& filePath) const
{
    try
    {
        FileException checker(filePath + ".sprites");
        FileException checker2(filePath + ".movable");
        FileException checker3(filePath + ".animated");
    }
    catch(const BaseException& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    std::ifstream spr (filePath + ".sprites");
    std::ifstream mov (filePath + ".movable");
    std::ifstream ani (filePath + ".animated");

    std::string line;
    int number, number2;
    spr>>line>>line>>number>>number2;
    mov>>line;
    ani>>line;
    while (spr >> line >> number >> number >> number2 >> number)
    {
        m_player.raiseSpriteCount(abs(number2));
    }
    while 
    (
        mov >> line >> number >> number >> number >> number >> number >> number
    )
    {
        m_player.raiseSpriteCount(1);
    }
    while (ani >> line >> number >> number >> number >> number >> number)
    {
        m_player.raiseSpriteCount(1);
    }
    spr.close();
    mov.close();
    ani.close();
}
const int GamePanel::getSpriteCount() const
{
    return m_player.getSpriteCount();
}

//metoda care descopera coliziunile dintre player si sprite-uri
void GamePanel::checkPlayerCollision(float dt, float scaleY)
{
    float playerLeft = m_player.getPosX().getActual();
    float playerTop = m_player.getPosY().getActual();
    float playerRight = playerLeft + m_player.getWidth();
    float playerBottom = playerTop + m_player.getHeight();

    // variabila steag care verifica daca jucatorul este pe sol
    bool isOnGround = false; 
    // check de coliziuni pt fiecare sprite
    for (const auto& sprite : m_sprites)
    {
        // verific daca sprite-ul este desenat (momentan toate sunt)
        if (sprite->getDrawStatus() == 0)
            continue;
        // verific daca sprite-ul are coliziune
        if (sprite->getCollision() == 0)
            continue;
        // obtin coordonatele sprite-ului
        float spriteLeft = sprite->getPosX().getActual();
        float spriteTop = sprite->getPosY().getActual();
        float spriteRight = spriteLeft + sprite->getWidth();
        float spriteBottom = spriteTop + sprite->getHeight();

        // 0. check de proximitate (jucatorul este pe un sprite)
        if(((playerBottom <= spriteTop &&
             playerBottom + 5 >= spriteTop) ||
             playerBottom >= spriteTop &&
             playerBottom - 5 <= spriteTop) &&
             playerRight > spriteLeft &&
             playerLeft < spriteRight)
        {
            // cod de debugging
            std::cout 
            << "Proximity Check Passed!"
            << "Player is close to sprite below. Sprite Top: " 
            << spriteTop << ' ' << playerBottom << std::endl;
            MovableSprite* movableS = dynamic_cast<MovableSprite*>(sprite.get());
            // daca sprite-ul este mobil, setez viteza platformei
            if (movableS)
            {
                m_player.setPlatformSpeed
                (
                    sprite->getXSpeed(), 
                    sprite->getYSpeed()
                );
                std::cout << "Player is on a movable sprite." << std::endl;
                m_player.setPosition
                (
                    playerLeft, 
                    spriteTop - m_player.getHeight() - 1
                );
            }
            // altfel setez viteza platformei la 0
            else
            {
                Delta zero(0,0);
                m_player.setPlatformSpeed(zero,zero);
            }
            isOnGround = true; // Player is considered on the ground
        }

        // 1. coliziune cu solul (player-ul cade pe un sprite)
        if (m_player.getSpeedY().getActual() > 0) // doar cand jucatorul cade
        {
            if (((playerBottom >= spriteTop &&
                playerBottom <= spriteTop + (m_player.getSpeedY().getActual()
                    + m_player.getSpeedY().getPrecedent()) / 2 * dt) ||
                (playerBottom >= spriteTop &&
                playerBottom <= (spriteTop + spriteBottom) / 2)) &&
                playerRight > spriteLeft &&
                playerLeft < spriteRight)
            {
                isOnGround = true;
                // cod de debugging
                std::cout << "Ground Collision Detected! Sprite Top: " 
                << spriteTop << std::endl;
                m_player.hitGround(spriteTop);
                break;
            }
        }

        // 2. coliziune cu tavanul (player-ul sare in sus)
        if (m_player.getSpeedY().getActual() < 0) // saritura
        {
            if(((playerTop >= spriteBottom &&
                playerTop <= spriteBottom - (m_player.getSpeedY().getActual()
                    + m_player.getSpeedY().getPrecedent()) / 2 * dt) ||
                (playerTop <= spriteBottom &&
                playerTop >= (spriteTop + spriteBottom) / 2)) &&
                playerRight > spriteLeft &&
                playerLeft < spriteRight)
            {
                
                m_player.hitCeiling(spriteBottom);
                break;
            }
        }

        // 3. coliziune cu peretele stang (player-ul se misca spre stanga
        //    sau sprite-ul se misca spre dreapta)
        if 
        (
            m_player.getSpeedX().getActual() < 0 || 
            m_player.getXPlatformSpeed().getActual() < 0
        )
        {
            if (((playerLeft >= spriteRight &&
                playerLeft <= spriteRight - (m_player.getSpeedX().getActual() 
                    + m_player.getSpeedX().getPrecedent()) / 2 * dt) ||
                (playerLeft <= spriteRight && 
                playerLeft >= (spriteLeft + spriteRight) / 2)) &&
                playerBottom > spriteTop &&
                playerTop < spriteBottom)
            {
                m_player.hitLeft(spriteRight);
                break;
            }
        }

        // 4. coliziune cu peretele drept (player-ul se misca spre dreapta
        //    sau sprite-ul se misca spre stanga)
        if 
        (
            m_player.getSpeedX().getActual() > 0 || 
            m_player.getXPlatformSpeed().getActual() > 0
        ) 
        {
            if (((playerRight <= spriteLeft &&
                playerRight >= spriteLeft - (m_player.getSpeedX().getActual()
                    + m_player.getSpeedX().getPrecedent()) / 2 * dt) ||
                (playerRight >= spriteLeft &&
                playerRight <= (spriteLeft + spriteRight) / 2)) &&
                playerBottom > spriteTop &&
                playerTop < spriteBottom)
            {
                m_player.hitRight(spriteLeft);
                break;
            }
        }
    }

    // daca nici-un srite nu este sub jucator, il las sa cada
    if (!isOnGround && m_player.getSpeedY().getActual() == 0)
    {
        std::cout << "No sprite under the player. Triggering fall.";
        std::cout << std::endl;
        // aplic gravitatia
        m_player.updateCalculationsY(DirectieY::NONE, dt, scaleY, 1);
        // setez viteza platformei la 0
        Delta zero(0, 0);
        m_player.setPlatformSpeed(m_player.getXPlatformSpeed(), zero);
    }
    // verific daca jucatorul este deasupra ecranului
    if ((playerTop + playerBottom) / 2 < 0)
    {
        moveScreenUp(playerLeft);
    }
    // verific daca jucatorul este sub ecran
    if ((playerBottom + playerTop) / 2 > m_window.getSize().y)
    {
        moveScreenDown(playerLeft);
    }
    // verific daca jucatorul este la stanga ecranului
    if ((playerLeft + playerRight) / 2 < 0)
    {
        moveScreenLeft(playerTop);
    }
    // verific daca jucatorul este la dreapta ecranului
    if ((playerLeft + playerRight) / 2 > m_window.getSize().x)
    {
        moveScreenRight(playerTop);
    }
}

// metoda care incarca configuratia programului din fisier
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
        if (line.empty() || line.find('=') == std::string::npos)
            continue;

        std::istringstream lineStream(line);
        std::string key, value;
        if 
        (
            std::getline(lineStream, key, '=') && 
            std::getline(lineStream, value)
        )
        {
            key.erase(key.find_last_not_of(" \t") + 1);
            key.erase(0, key.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));

            if (key == "FRAME_RATE")
            {
                m_frameRate = std::stof(value);
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


// metoda care incarca sprite-urile simple,
// background-ul si pozitia jucatorului din fisier
void GamePanel::loadSpritesFromFile(const std::string& filePath)
{
    try {
        FileException checker(filePath);
    } catch (const BaseException& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return;
    }

    std::ifstream in(filePath);

    // incarc path-ul sprite-urilor
    std::string path, texturePath;
    in >> path >> texturePath;
    if (path == "/") path = "";

    
    m_backgroundSprite.updateTexture(path + texturePath);
    m_backgroundSprite.setDrawStatus(true);

    // calculez scala cu care trebuie sa incarc background-ul
    sf::Vector2u windowSize = m_window.getSize();
    sf::Vector2u textureSize = m_backgroundSprite.getTexture().getSize();
    float backgroundScale = 
        static_cast<float>(windowSize.x * 2.f) / (textureSize.x);

    // aplic scala pe background
    m_backgroundSprite.setScale(backgroundScale, backgroundScale);
    m_backgroundSprite.setPosition
    (
        0,
        windowSize.y - (textureSize.y * backgroundScale)
    );
    std::cout << "Background loaded" << std::endl;

    // calculez factoii de scala pentru sprite-uri si jucator
    const float referenceWidth = 1920.0f;
    const float referenceHeight = 1080.0f;
    float spriteScaleX = static_cast<float>(windowSize.x) / referenceWidth;
    float spriteScaleY = static_cast<float>(windowSize.y) / referenceHeight;

    // incarc pozitia jucatorului
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

    // incarc restul sprite-urilor
    while (in >> texturePath >> startX >> startY >> count >> collision)
    {
        // convertesc coordonatele din grid in coordonate pixel
        float pixelX = startX * 120.0f * spriteScaleX;
        float pixelY = windowSize.y - (startY + 1) * 120.0f * spriteScaleY;

        if (count < 0)
        {
            count *= -1;
            for (int i = 0; i < count; ++i)
            {
                std::unique_ptr<I_Sprite> sprite = std::make_unique<Sprite>(
                    path + texturePath,
                    pixelX,
                    pixelY - i * 120.0f * spriteScaleY,
                    120.0f * spriteScaleY,
                    120.0f * spriteScaleX
                );
                
                // adaug sprite-ul in vector
                addSprite(std::move(sprite), path + texturePath, collision);
            }
        }
        else
        {
            for (int i = 0; i < count; ++i)
            {
                std::unique_ptr<I_Sprite> sprite = std::make_unique<Sprite>(
                    path + texturePath,
                    pixelX + i * 120.0f * spriteScaleX,
                    pixelY,
                    120.0f * spriteScaleY,
                    120.0f * spriteScaleX
                );
                addSprite(std::move(sprite), path + texturePath, collision);
            }
        }
    }

    in.close();
}

// metoda care incarca sprite-urile mobile din fisier
void GamePanel::loadMovableSpritesFromFile(const std::string& filePath)
{
    try
    {
        FileException checker(filePath);
    }
    catch (const BaseException& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return;
    }
    std::ifstream in(filePath);

    // incarc path-ul sprite-urilor
    std::string path, texturePath;
    in >> path;
    if (path == "/") path = "";

    int startX, startY, endX, endY, acceleration;
    bool collision;
    // calculez scala cu care trebuie sa incarc sprite-urile
    sf::Vector2u windowSize = m_window.getSize();
    const float referenceWidth = 1920.0f;
    const float referenceHeight = 1080.0f;
    float spriteScaleX = static_cast<float>(windowSize.x) / referenceWidth;
    float spriteScaleY = static_cast<float>(windowSize.y) / referenceHeight;
    // incarc sprite-urile
    while 
    (
        in >> texturePath >> startX >> startY 
           >> endX >> endY >> acceleration >> collision
    )
    {
        // convertesc coordonatele din grid in coordonate pixel
        float pixelX = startX * 120.0f * spriteScaleX;
        float pixelY = windowSize.y - (startY + 1) * 120.0f * spriteScaleY;
        float pixelEndX = endX * 120.0f * spriteScaleX;
        float pixelEndY = windowSize.y - (endY + 1) * 120.0f * spriteScaleY;

        // creez un sprite mobil
        std::unique_ptr<I_Sprite> sprite = std::make_unique<MovableSprite>(
            path + texturePath,
            120.0f * spriteScaleY, // Width
            120.0f * spriteScaleX, // Height
            pixelX,
            pixelY,
            pixelEndX,
            pixelEndY,
            acceleration
        );
        // adaug sprite-ul in vector
        addSprite(std::move(sprite), path + texturePath, collision);
    }

    in.close();
}

// metoda care incarca sprite-urile animate din fisier
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
    // incarc path-ul sprite-urilor
    std::string path, texturePath;
    in >> path;
    if (path == "/") path = "";

    int x, y, textureCount, frameDuration, collision;
    // calculez scala cu care trebuie sa incarc sprite-urile
    sf::Vector2u windowSize = m_window.getSize();
    const float referenceWidth = 1920.0f;
    const float referenceHeight = 1080.0f;
    float spriteScaleX = static_cast<float>(windowSize.x) / referenceWidth;
    float spriteScaleY = static_cast<float>(windowSize.y) / referenceHeight;
    // incarc sprite-urile
    while 
    (
        in >> texturePath >> x >> y 
           >> textureCount >> frameDuration >> collision
    )
    {
        // modific frameduration-ul in functie de frame rate
        frameDuration = static_cast<int>(frameDuration * m_frameRate / 60.0f);
        // convertesc coordonatele din grid in coordonate pixel
        float pixelX = x * 120.0f * spriteScaleX;
        float pixelY = windowSize.y - (y + 1) * 120.0f * spriteScaleY;

        // creez un sprite animat
        std::unique_ptr <I_Sprite> sprite = std::make_unique<AnimatedSprite>(
            path + texturePath,
            pixelX,
            pixelY,
            120.0f * spriteScaleY, // Width
            120.0f * spriteScaleX, // Height
            textureCount,
            frameDuration
        );
        // adaug sprite-ul in vector
        addSprite(std::move(sprite), path + texturePath, collision);
    }

    in.close();
}

// metoda care se ocupa cu miscarea sprite-urilor
void GamePanel::moveSprites(float dt)
{
    // trec prin fiecare sprite
    for (auto& sprite : m_sprites)
    {
        // verific daca sprite-ul se misca
        MovableSprite* movableS = dynamic_cast<MovableSprite*>(sprite.get());
        if (!movableS) continue; // Skip if not a MovableSprite
        bool not_movingX = false;
        bool not_movingY = false;
        if (sprite->getXStartPoz() == sprite->getXEndPoz())
        {
            sprite->setPosition
            (
                sprite->getXStartPoz(), 
                sprite->getPosY().getActual()
            );
            not_movingX = true;
        }
        if (sprite->getYStartPoz() == sprite->getYEndPoz())
        {
            sprite->setPosition
            (
                sprite->getPosX().getActual(), 
                sprite->getYStartPoz()
            );
            not_movingY = true;
        }
        // calculez acceleratia pe Y
        float distantaX = sprite->getXEndPoz() - sprite->getXStartPoz();
        float distantaY = sprite->getYEndPoz() - sprite->getYStartPoz();
        float acceleratieX, acceleratieY;
        if (distantaX == 0)
        {
            acceleratieX = 0;
            acceleratieY = sprite->getAcceleration();
        }
        else
        {
            acceleratieX = sprite->getAcceleration();
            acceleratieY = abs(acceleratieX * distantaY / distantaX);
        } 
        //calcule pentru X si Y
        if 
        (
            sprite->getXSpeed().getActual() == 0 && 
            sprite->getYSpeed().getActual() == 0
        )
        {
            if (sprite->getXStartPoz() < sprite->getXEndPoz())
            {
                sprite->updateXSpeed(acceleratieX * dt);
            }
            else sprite->updateXSpeed(-acceleratieX * dt);
            if (sprite->getYStartPoz()<sprite->getYEndPoz())
            {
                sprite->updateYSpeed(acceleratieY * dt);
            }
            else sprite->updateYSpeed(-acceleratieY * dt);
        }
        else
        {
            //calcule pentru X
            if (!not_movingX)
            {
                if (sprite->getXStartPoz()<sprite->getXEndPoz())
                {
                    if 
                    (
                        sprite->getPosX().getActual() < 
                        (sprite->getXStartPoz() + sprite->getXEndPoz()) / 2
                    )
                    {
                        sprite->updateXSpeed
                        (
                            sprite->getXSpeed().getAverage() + 
                            acceleratieX * dt
                        );
                    }
                    else if 
                    (
                        sprite->getPosX().getActual() > 
                        (sprite->getXStartPoz() + sprite->getXEndPoz()) / 2
                    )
                    {
                        sprite->updateXSpeed
                        (
                            sprite->getXSpeed().getAverage() - 
                            acceleratieX * dt
                        );
                    }
                }
                else
                {
                    if 
                    (
                        sprite->getPosX().getActual() > 
                        (sprite->getXStartPoz() + sprite->getXEndPoz()) / 2
                    )
                    {
                        sprite->updateXSpeed
                        (
                            sprite->getXSpeed().getAverage() - 
                            acceleratieX * dt
                        );
                    }
                    else if 
                    (
                        sprite->getPosX().getActual() < 
                        (sprite->getXStartPoz() + sprite->getXEndPoz()) / 2
                    )
                    {
                        sprite->updateXSpeed
                        (
                            sprite->getXSpeed().getAverage() + 
                            acceleratieX * dt
                        );
                    }
                }
            }
            //calcule pentru Y
            if (!not_movingY)
            {
                if (sprite->getYStartPoz()<sprite->getYEndPoz())
                {
                    if 
                    (
                        sprite->getPosY().getActual() < 
                        (sprite->getYStartPoz() + sprite->getYEndPoz()) / 2
                    )
                    {
                        sprite->updateYSpeed
                        (
                            sprite->getYSpeed().getAverage() + 
                            acceleratieY * dt
                        );
                    }
                    else if 
                    (
                        sprite->getPosY().getActual() > 
                        (sprite->getYStartPoz() + sprite->getYEndPoz()) / 2
                    )
                    {
                        sprite->updateYSpeed
                        (
                            sprite->getYSpeed().getAverage() - 
                            acceleratieY * dt
                        );
                    }
                }
                else
                {
                    if 
                    (
                        sprite->getPosY().getActual() > 
                        (sprite->getYStartPoz() + sprite->getYEndPoz()) / 2
                    )
                    {
                        sprite->updateYSpeed
                        (
                            sprite->getYSpeed().getAverage() - 
                            acceleratieY * dt
                        );
                    }
                    else if 
                    (
                        sprite->getPosY().getActual() < 
                        (sprite->getYStartPoz() + sprite->getYEndPoz()) / 2
                    )
                    {
                        sprite->updateYSpeed
                        (
                            sprite->getYSpeed().getAverage() + 
                            acceleratieY * dt
                        );
                    }
                }
            }
        }
        float pozX=sprite->getPosX().getActual();
        float pozY = sprite->getPosY().getActual();
        float newPosX = pozX + sprite->getXSpeed().getActual() * dt;
        float newPosY = pozY + sprite->getYSpeed().getActual() * dt;
        Delta newPosXDelta(pozX, newPosX);
        Delta newPosYDelta(pozY, newPosY);
        sprite->updatePosition(newPosXDelta, newPosYDelta);
    }
}

// metodele care se ocupa cu miscarea ecranului
void GamePanel::moveScreenUp(float playerLeft){
    std::cout << "Player climbed above the screen. Applying offset.";
    std::cout << std::endl;
    // modific offset-ul
    m_verticalOffset += m_window.getSize().y;
    // setez noua pozitie a jucatorului
    m_player.setPosition
    (
        playerLeft, 
        m_window.getSize().y - m_player.getHeight()
    ); 

    // aplic offset-ul la toate sprite-urile
    for (auto& sprite : m_sprites)
    {
        sprite->setPosition
        (
            sprite->getPosX().getActual(), 
            sprite->getPosY().getActual() + m_window.getSize().y
        );
        MovableSprite* movableS = dynamic_cast<MovableSprite*>(sprite.get());
        if (movableS)
        {
            movableS->setYStartPoz
            (
                movableS->getYStartPoz() + m_window.getSize().y
            );
            movableS->setYEndPoz
            (
                movableS->getYEndPoz() + m_window.getSize().y
            );
        }
    }
    // aplic offset-ul la background
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
    // modific offset-ul
    m_verticalOffset -= m_window.getSize().y;
    // setez noua pozitie a jucatorului
    m_player.setPosition(playerLeft, 0); 

    // aplic offset-ul la toate sprite-urile
    for (auto& sprite : m_sprites)
    {
        sprite->setPosition
        (
            sprite->getPosX().getActual(), 
            sprite->getPosY().getActual() - m_window.getSize().y
        );
        MovableSprite* movableS = dynamic_cast<MovableSprite*>(sprite.get());
        if (movableS)
        {
            movableS->setYStartPoz
            (
                movableS->getYStartPoz() - m_window.getSize().y
            );
            movableS->setYEndPoz
            (
                movableS->getYEndPoz() - m_window.getSize().y
            );
        }
    }
    // aplic offset-ul la background
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
    // modific offset-ul
    m_horizontalOffset += m_window.getSize().x;
    // setez noua pozitie a jucatorului
    m_player.setPosition
    (
        m_window.getSize().x-m_player.getWidth()/2, 
        playerTop
    );

    // aplic offset-ul la toate sprite-urile
    for (auto& sprite : m_sprites)
    {
        sprite->setPosition
        (
            sprite->getPosX().getActual()+m_window.getSize().x, 
            sprite->getPosY().getActual()
        );
        MovableSprite* movableS = dynamic_cast<MovableSprite*>(sprite.get());
        if (movableS)
        {
            movableS->setXStartPoz
            (
                movableS->getXStartPoz() + m_window.getSize().x
            );
            movableS->setXEndPoz
            (
                movableS->getXEndPoz() + m_window.getSize().x
            );
        }
    }
    // aplic offset-ul la background
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
    // modific offset-ul
    m_horizontalOffset -= m_window.getSize().x;
    // setez noua pozitie a jucatorului
    m_player.setPosition
    (
        0-m_player.getWidth()/2, 
        playerTop
    );

    // aplic offset-ul la toate sprite-urile
    for (auto& sprite : m_sprites)
    {
        sprite->setPosition
        (
            sprite->getPosX().getActual()-m_window.getSize().x, 
            sprite->getPosY().getActual()
        );
        MovableSprite* movableS = dynamic_cast<MovableSprite*>(sprite.get());
        if (movableS)
        {
            movableS->setXStartPoz
            (
                movableS->getXStartPoz() - m_window.getSize().x
            );
            movableS->setXEndPoz
            (
                movableS->getXEndPoz() - m_window.getSize().x
            );
        }
    }
    // aplic offset-ul la background
    m_backgroundSprite.setPosition
    (
        m_backgroundSprite.getPosX().getActual()-m_window.getSize().x, 
        m_backgroundSprite.getPosY().getActual()
    );
}

// metoda care se ocupe de sleep
void GamePanel::panelSleep(float seconds)
{
    #if defined(Win32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
        Sleep(0);
    #else // as fi folosit clasa Platforma, dar numai asa pot scrie functii pe
    // linux fara eroare de compilare
        std::this_thread::sleep_for(std::chrono::duration<double>(seconds));
    #endif
}