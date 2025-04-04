#include "delta.h"

Delta::Delta() : precedent(0), actual(0)
{;}

Delta::Delta(double precedent, double actual)
    : precedent(precedent), actual(actual)
{;}

Delta::Delta(const Delta& other)
    : precedent(other.precedent), actual(other.actual)
{;}

double Delta::getPrecedent() const
{
    return precedent;
}

double Delta::getActual() const
{
    return actual;
}

void Delta::setPrecedent(double value)
{
    precedent = value;
}

void Delta::setActual(double value)
{
    actual = value;
}

double Delta::value() const
{
    return actual - precedent;
}

void Delta::update(double other)
{
    precedent = actual;
    actual = other;
}