#ifndef TYPES_H
#define TYPES_H

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

enum MenuSelection
{
    EXIT,
    CONTINUE
};

// Overload ++ for MenuSelection
inline MenuSelection& operator++(MenuSelection& selection)
{
    using UnderlyingType = std::underlying_type_t<MenuSelection>;
    selection = 
        static_cast<MenuSelection>(static_cast<UnderlyingType>(selection) + 1);
    if (static_cast<int>(selection) > 1)
    {
        selection = EXIT;
    }
    return selection;
}

// Overload -- for MenuSelection
inline MenuSelection& operator--(MenuSelection& selection)
{
    using UnderlyingType = std::underlying_type_t<MenuSelection>;
    selection = 
        static_cast<MenuSelection>(static_cast<UnderlyingType>(selection) - 1);
    if (static_cast<int>(selection) < 0)
    {
        selection = CONTINUE;
    }
    return selection;
}

#endif // TYPES_H