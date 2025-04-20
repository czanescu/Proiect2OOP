cmake_minimum_required(VERSION 3.10)

# Set the project name
project(gravity)

# Add the executable
add_executable(gravity main.cpp Delta.cpp Sprite.cpp GamePanel.cpp Player.cpp MovableSprite.cpp AnimatedSprite.cpp)

if (CMAKE_CROSSCOMPILING)
    # Cross-compiling on Linux for Windows
    # run with cmake -DCMAKE_TOOLCHAIN_FILE=mingw-toolchain.cmake ..
    message("CROSSCOMPILING block triggered")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    set(SFML_DIR "/home/cristi/libraries/SFML-2.5.0-win/lib/cmake/SFML")
    find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
    target_link_libraries(gravity sfml-graphics sfml-window sfml-system)
elseif (WIN32)
    # Native Windows build
    # run with cmake -G "MinGW Makefiles" ..
    message("WIN32 block triggered")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    set(SFML_DIR "C:/SFML-2.5.0/lib/cmake/SFML")
    find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
    target_link_libraries(gravity sfml-graphics sfml-window sfml-system)
elseif (UNIX)
    # Native Linux build
    # run with cmake ..
    message("UNIX block triggered")
    find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
    target_link_libraries(gravity sfml-graphics sfml-window sfml-system)
endif()