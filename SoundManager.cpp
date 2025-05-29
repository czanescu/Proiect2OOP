#include "SoundManager.hpp"

JumpSoundManager& JumpSoundManager::getInstance() {
    static JumpSoundManager instance;
    return instance;
}

void JumpSoundManager::loadJumpSound(const std::string& filename) {
    buffer.loadFromFile(filename);
    sound.setBuffer(buffer);
}

void JumpSoundManager::playJumpSound() {
    sound.stop();
    sound.play();
}