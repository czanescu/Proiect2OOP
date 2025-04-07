#include "GamePanel.h"
#include <iomanip>
#include <sstream>

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
void GamePanel::addSprite(const Sprite& sprite)
{
    m_sprites.resize(m_sprites.size() + 1);
    m_sprites[m_sprites.size() - 1] = sprite;
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

GamePanel::~GamePanel()
{
    // Destructor implementation (needed)

}