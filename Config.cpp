#include "Config.hpp"

Config& Config::getInstance() {
    static Config instance;
    return instance;
}

Config::Config()
{
    std::ifstream in (".config");
    std::string line;
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
                m_windowWidth = std::stof(value);
            }
            else if (key == "Y_RESOLUTION")
            {
                m_windowHeight = std::stof(value);
            }
            else if (key == "SOUND")
            {
                if (value == "OFF") m_soundEnabled = false;
                else m_soundEnabled = true;
            }
        }
    }
    in.close();
}

Config::~Config() = default;

int Config::getWindowWidth() const {
    return m_windowWidth;
}

int Config::getWindowHeight() const {
    return m_windowHeight;
}

int Config::getFrameRate() const {
    return m_frameRate;
}

bool Config::isSoundEnabled() const {
    return m_soundEnabled;
}

void Config::setWindowWidth(int width) {}

void Config::setWindowHeight(int height) {}

void Config::setFrameRate(int rate) {}

void Config::setSoundEnabled(bool enabled) {
    m_soundEnabled = enabled;
}