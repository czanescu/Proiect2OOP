#include <SFML/Graphics.hpp>
#include <chrono>
#include <string>
#include <stdexcept>


int main()
{
    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "Sprite Gravity");

    const double FRAME_RATE = 60.0;

    sf::Color backgroundColor(37,37,164,0.7);

    // Load font for frame counter
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        throw std::runtime_error("Failed to load font");
    }

    sf::Text frameCounter;
    frameCounter.setFont(font);
    frameCounter.setCharacterSize(24);
    frameCounter.setFillColor(sf::Color::White);
    frameCounter.setPosition(window.getSize().x - 150.0, 10.0); // Top-right corner

    // Timing variables
    const double fixedTimeStep = 1.0 / FRAME_RATE; // 60 updates per second
    double accumulator = 0.0;
    auto oldTime = std::chrono::high_resolution_clock::now();

    int frameCount = 0; // Frame counter
    double frameTimeAccumulator = 0.0; // Accumulator for frame time

    while (window.isOpen())
    {
        // Calculate deltaTime
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsedTime = currentTime - oldTime;
        double deltaTime = elapsedTime.count();
        oldTime = currentTime;
        accumulator += deltaTime;
        frameTimeAccumulator += deltaTime;

        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if ((event.type == sf::Event::Closed)
            || event.type == sf::Event::KeyPressed
            && event.key.code == sf::Keyboard::Escape)
                window.close();
        }

        // Fixed update loop
        while (accumulator >= fixedTimeStep)
        {
            frameCount++;
            accumulator -= fixedTimeStep;
        }

        // Cod pentru frame counter
        if (frameTimeAccumulator >= 1.0)
        {
            frameCounter.setString("FPS: " + std::to_string(frameCount));
            frameCount = 0;
            frameTimeAccumulator = 0.0;
        }

        // Render
        window.clear(backgroundColor);
        window.draw(frameCounter); // Draw frame counter
        window.display();
    }
}