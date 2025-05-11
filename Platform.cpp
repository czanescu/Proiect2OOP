#include "Platform.hpp"

// Singleton instance accessor
Platform& Platform::getInstance()
{
    static Platform instance;
    return instance;
}

// Constructor
Platform::Platform()
{
#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
    m_platform = OS::WINDOWS;
#else
    m_platform = OS::LINUX;
#endif
}

// Destructor
Platform::~Platform() = default;

// Get the platform
const OS& Platform::getPlatform() const
{
    return m_platform;
}