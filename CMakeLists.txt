cmake_minimum_required(VERSION 3.10)

# Set the project name
project(gravity)

# Add the executable
add_executable(gravity main.cpp Delta.cpp Sprite.cpp GamePanel.cpp Player.cpp MovableSprite.cpp)

# Find and link SFML libraries
if (WIN32)
    # Windows-specific settings
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -static")
    set(SFML_DIR "C:/SFML-2.5.0/lib/cmake/SFML") # Updated path to SFMLConfig.cmake for Windows
    find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
    target_link_libraries(gravity sfml-graphics sfml-window sfml-system)
elseif (CMAKE_CROSSCOMPILING)
    # Linux cross-compilation for Windows
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -static")
    set(SFML_DIR "/home/cristi/libraries/SFML-2.5.1/lib/cmake/SFML") # Old path for Linux cross-compilation
    find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
    target_link_libraries(gravity sfml-graphics sfml-window sfml-system)
elseif (UNIX)
    # Linux-specific settings
    find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
    target_link_libraries(gravity sfml-graphics sfml-window sfml-system)
endif()