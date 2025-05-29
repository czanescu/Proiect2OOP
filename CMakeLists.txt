cmake_minimum_required(VERSION 3.10)

# Setez numele proiectului (pe windows are si extensia .exe)
project(gravity)

# lista de fisiere sursa si executabilul
add_executable(gravity main.cpp Sprite.cpp GamePanel.cpp Player.cpp MovableSprite.cpp AnimatedSprite.cpp Exceptii.cpp Platform.cpp SoundManager.cpp Config.cpp)

if (CMAKE_CROSSCOMPILING)
    # Cross-compiling de pe linux pentru windows
    # rulez cu cmake -DCMAKE_TOOLCHAIN_FILE=mingw-toolchain.cmake ..
    message("CROSSCOMPILING block triggered")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    #path-ul meu local catre librariile SFML de windows
    set(SFML_DIR "/home/cristi/libraries/SFML-2.5.0-win/lib/cmake/SFML")
    find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)
    target_link_libraries(gravity sfml-graphics sfml-window sfml-system sfml-audio)
elseif (WIN32)
    # Compilare nativa pe Windows
    # rulez cu cmake -G "MinGW Makefiles" ..
    message("WIN32 block triggered")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    #path-ul meu local catre librariile SFML de windows
    set(SFML_DIR "C:/SFML-2.5.0/lib/cmake/SFML")
    find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)
    target_link_libraries(gravity sfml-graphics sfml-window sfml-system sfml-audio)
elseif (UNIX)
    # Compilare nativa pe Linux
    # rulez cu cmake ..
    message("UNIX block triggered")
    # pentru compilare si rulare a executabilului
    # pe linux trebuie instalate librariile SFML
    # sudo apt install libsfml-dev (am testat doar pe linux mint)
    find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)
    target_link_libraries(gravity sfml-graphics sfml-window sfml-system sfml-audio)
endif()