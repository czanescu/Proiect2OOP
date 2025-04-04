cmake_minimum_required(VERSION 3.10)

# Set the project name
project(nume_executabil)

# Find the SFML library
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add the executable
add_executable(gravity main.cpp delta.cpp)

# Link SFML libraries
target_link_libraries(gravity sfml-graphics sfml-window sfml-system)