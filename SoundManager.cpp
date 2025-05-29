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

CollisionSoundManager& CollisionSoundManager::getInstance() {
    static CollisionSoundManager instance;
    return instance;
}
void CollisionSoundManager::loadCollisionSound(const std::string& filename) {
    buffer.loadFromFile(filename);
    sound.setBuffer(buffer);
}
void CollisionSoundManager::playCollisionSound() {
    sound.stop();
    sound.play();
}