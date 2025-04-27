#include "Delta.hpp"
// clasa Delta este folosita pentru a lucra
// mai usor cu pozitii/viteze/timp/acceleratii

// constructor gol Delta
Delta::Delta() : m_precedent(0), m_actual(0)
{;}

// constructor Delta
Delta::Delta(float precedent, float actual)
    : m_precedent(precedent), m_actual(actual)
{;}

// constructor de copiere Delta
Delta::Delta(const Delta& other)
    : m_precedent(other.m_precedent), m_actual(other.m_actual)
{;}

// getter pentru precedent
float Delta::getPrecedent() const
{
    return m_precedent;
}

// getter pentru actual
float Delta::getActual() const
{
    return m_actual;
}

// getter pentru medie
float Delta::getAverage() const
{
    return (m_precedent + m_actual) / 2;
}

// setter pentru precedent
void Delta::setPrecedent(float value)
{
    m_precedent = value;
}

// setter pentru actual
void Delta::setActual(float value)
{
    m_actual = value;
}

// setter pentru ambele valori
void Delta::setDelta(float precedent, float actual)
{
    m_precedent = precedent;
    m_actual = actual;
}

// getter pentru diferenta dintre cele doua valori
float Delta::value() const
{
    return m_actual - m_precedent;
}

// metoda pentru a actualiza precedentul si actualul
void Delta::update(float other)
{
    m_precedent = m_actual;
    m_actual = other;
}