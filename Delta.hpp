#ifndef DELTA_H
#define DELTA_H

class Delta
{
public:
    Delta(); // Constructor gol
    Delta(float precedent, float actual); // Constructor
    Delta(const Delta& other); // Constructor de copiere

    // getteri
    float getPrecedent() const;
    float getActual() const;
    float getAverage() const;

    // setteri
    void setPrecedent(float value);
    void setActual(float value);
    void setDelta(float precedent, float actual);

    // getter pentru diferenta dintre cele doua valori
    float value() const;

    // metoda pentru a actualiza precedentul si actualul
    void update(float other);

    // destructor
    ~Delta() = default;

private:
    float m_precedent;
    float m_actual;
};

#endif