#ifndef DELTA_H
#define DELTA_H

template <typename T = float>
class Delta
{
public:
    Delta(); // Constructor gol
    Delta(T precedent, T actual); // Constructor
    Delta(const Delta& other); // Constructor de copiere

    // getteri
    T getPrecedent() const;
    T getActual() const;
    T getAverage() const;

    // setteri
    void setPrecedent(T value);
    void setActual(T value);
    void setDelta(T precedent, T actual);

    // getter pentru diferenta dintre cele doua valori
    T value() const;

    // metoda pentru a actualiza precedentul si actualul
    void update(T other);

    // destructor
    ~Delta() = default;

private:
    T m_precedent;
    T m_actual;
};

#include "Delta.tpp"

#endif