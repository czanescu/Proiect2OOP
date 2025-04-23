#include "Exceptii.hpp"

BaseException::BaseException(const std::string& msg) : m_message(msg) 
{;}
const char* BaseException::what() const noexcept
{
    return m_message.c_str();
}

FileException::FileException(const std::string& filename) 
    : BaseException("File error: " + filename) {
    // Verificăm dacă fișierul există și poate fi deschis
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw BaseException("File not found or cannot be opened: " + filename);
    }
    std::cout << "File " << filename << " loaded successfully.\n";
    file.close();
}

ConfigException::ConfigException(int frameRate, int width, int height) :
    BaseException("Invalid configuration: " + std::to_string(frameRate) +
    " FPS, " + std::to_string(width) + "x" + std::to_string(height))
{
    if (frameRate <= 0 || width <= 0 || height <= 0) {
        throw BaseException
        (
            "Invalid configuration values: frame rate and dimensions must be positive."
        );
    }
    std::cout << "Configuration is valid: " << frameRate;
    std::cout << " FPS, " << width << "x" << height << "\n";
}

IndexOutOfRangeException::IndexOutOfRangeException(int index, int size) : 
    BaseException("Index out of range: " + std::to_string(index) + 
    " (size: " + std::to_string(size) + ")") 
{
    if (index < 0 || index >= size) {
        throw BaseException("Index " + std::to_string(index) + 
        " is out of range for size " + std::to_string(size));
    }
    std::cout << "Index " << index << " is within range for size " << size << "\n";
}