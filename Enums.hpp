#ifndef TYPES_H
#define TYPES_H

#include <type_traits>

// clase cu rol in simplificarea comunicarii intre metode

enum class DirectieX
{
    LEFT,
    RIGHT,
    NONE
};

enum class DirectieY
{
    UP,
    DOWN,
    NONE
};

enum class OS
{
    WINDOWS,
    LINUX
};

enum MenuSelection
{
    CONTINUE,
    SOUNDONOFF,
    EXIT
};

// Overload ++ pentru MenuSelection
inline MenuSelection& operator++(MenuSelection& selection)
{
    using UnderlyingType = std::underlying_type_t<MenuSelection>;
    selection = 
        static_cast<MenuSelection>(static_cast<UnderlyingType>(selection) + 1);
    if (static_cast<int>(selection) > 2)
    {
        selection = CONTINUE;
    }
    return selection;
}

// Overload -- pentru MenuSelection
inline MenuSelection& operator--(MenuSelection& selection)
{
    using UnderlyingType = std::underlying_type_t<MenuSelection>;
    selection = 
        static_cast<MenuSelection>(static_cast<UnderlyingType>(selection) - 1);
    if (static_cast<int>(selection) < 0)
    {
        selection = EXIT;
    }
    return selection;
}

#endif // TYPES_H