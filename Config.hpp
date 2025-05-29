#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <fstream>
#include <SFML/Graphics.hpp>
#include <sstream>

class Config {
public:
    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;
    
    static Config& getInstance();

    int getWindowWidth() const;
    int getWindowHeight() const;
    int getFrameRate() const;
    bool isSoundEnabled() const;
    
    void setWindowWidth(int width);
    void setWindowHeight(int height);
    void setFrameRate(int rate);
    void setSoundEnabled(bool enabled);

private:
    Config();
    ~Config();
    int m_windowWidth;
    int m_windowHeight;
    int m_frameRate;
    bool m_soundEnabled;
};

#endif