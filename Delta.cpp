#include "Delta.h"

Delta::Delta() : m_precedent(0), m_actual(0)
{;}

Delta::Delta(float precedent, float actual)
    : m_precedent(precedent), m_actual(actual)
{;}

Delta::Delta(const Delta& other)
    : m_precedent(other.m_precedent), m_actual(other.m_actual)
{;}

float Delta::getPrecedent() const
{
    return m_precedent;
}

float Delta::getActual() const
{
    return m_actual;
}

void Delta::setPrecedent(float value)
{
    m_precedent = value;
}

void Delta::setActual(float value)
{
    m_actual = value;
}

void Delta::setDelta(float precedent, float actual)
{
    m_precedent = precedent;
    m_actual = actual;
}

float Delta::value() const
{
    return m_actual - m_precedent;
}

void Delta::update(float other)
{
    m_precedent = m_actual;
    m_actual = other;
}