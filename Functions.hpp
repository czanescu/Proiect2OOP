#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

template<typename T>

inline T clamp(T value, T min, T max) {
    return (value < min) ? min : (value > max) ? max : value;
}

#endif