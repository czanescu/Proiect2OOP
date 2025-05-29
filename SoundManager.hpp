#ifndef JUMPSOUNDMANAGER_HPP
#define JUMPSOUNDMANAGER_HPP
#include <SFML/Audio.hpp>
#include <string>

class JumpSoundManager {
public:
    static JumpSoundManager& getInstance();

    void loadJumpSound(const std::string& filename);
    void playJumpSound();

    // Delete copy/move constructors and assignment operators
    JumpSoundManager(const JumpSoundManager&) = delete;
    JumpSoundManager& operator=(const JumpSoundManager&) = delete;
private:
    JumpSoundManager() = default;
    sf::SoundBuffer buffer;
    sf::Sound sound;
};
#endif