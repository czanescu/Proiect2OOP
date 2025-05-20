#include "Delta.hpp"

// Remove the template argument list from the implementation file if this is not a template class implementation file.
// If Delta is a template class, make sure this file is included at the end of Delta.hpp and that Delta.hpp contains the template definition.

template <typename T>
Delta<T>::Delta()
    : m_precedent(0), m_actual(0)
{;}

template <typename T>
Delta<T>::Delta(T precedent, T actual)
    : m_precedent(precedent), m_actual(actual)
{;}

template <typename T>
Delta<T>::Delta(const Delta& other)
    : m_precedent(other.m_precedent), m_actual(other.m_actual)
{;}

template <typename T>
T Delta<T>::getPrecedent() const
{
    return m_precedent;
}

template <typename T>
T Delta<T>::getActual() const
{
    return m_actual;
}

template <typename T>
T Delta<T>::getAverage() const
{
    return (m_precedent + m_actual) / static_cast<T>(2);
}

template <typename T>
void Delta<T>::setPrecedent(T value)
{
    m_precedent = value;
}

template <typename T>
void Delta<T>::setActual(T value)
{
    m_actual = value;
}

template <typename T>
void Delta<T>::setDelta(T precedent, T actual)
{
    m_precedent = precedent;
    m_actual = actual;
}

template <typename T>
T Delta<T>::value() const
{
    return m_actual - m_precedent;
}

template <typename T>
void Delta<T>::update(T other)
{
    m_precedent = m_actual;
    m_actual = other;
}